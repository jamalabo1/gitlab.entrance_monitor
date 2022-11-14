namespace EntranceMonitor.EventBusRabbitMQ;

public class EventBusRabbitMQ : IEventBus, IDisposable
{
    private const string AUTOFAC_SCOPE_NAME = "event_bus";
    private readonly ILifetimeScope _autofac;
    private readonly ILogger<EventBusRabbitMQ> _logger;

    private readonly IRabbitMQPersistentConnection _persistentConnection;
    private readonly IEventBusSubscriptionsManager _subsManager;
    private IModel _consumerChannel;

    // is set by internalSubscription
    private string _queueName;

    public EventBusRabbitMQ(IRabbitMQPersistentConnection persistentConnection, ILogger<EventBusRabbitMQ> logger,
        ILifetimeScope autofac)
    {
        //IEventBusSubscriptionsManager subsManager
        _persistentConnection = persistentConnection ?? throw new ArgumentNullException(nameof(persistentConnection));
        _logger = logger ?? throw new ArgumentNullException(nameof(logger));
        _subsManager = new InMemoryEventBusSubscriptionsManager();
        _consumerChannel = CreateConsumerChannel();
        _autofac = autofac;
        _subsManager.OnEventRemoved += SubsManager_OnEventRemoved;
    }

    public void Dispose()
    {
        if (_consumerChannel != null) _consumerChannel.Dispose();

        _subsManager.Clear();
    }

    public void Subscribe<TH>(string exchangeName)
        where TH : IIntegrationEventHandler
    {
        DoInternalSubscription(exchangeName);

        _logger.LogInformation("Subscribing to exchange {exchangeName} with {EventHandler}", exchangeName,
            typeof(TH).GetGenericTypeName());

        _subsManager.AddSubscription<TH>(exchangeName);
        StartBasicConsume();
    }

    public void Unsubscribe<T, TH>()
        where T : IntegrationEvent
        where TH : IIntegrationEventHandler<T>
    {
        var exchangeName = _subsManager.GetEventKey<T>();

        _logger.LogInformation("Unsubscribing from event {exchangeName}", exchangeName);

        _subsManager.RemoveSubscription<T, TH>();
    }

    private void SubsManager_OnEventRemoved(object sender, string exchangeName)
    {
        if (!_persistentConnection.IsConnected) _persistentConnection.TryConnect();

        using var channel = _persistentConnection.CreateModel();

        // channel.
        // channel.QueueUnbind(_queueName,
        // BROKER_NAME,
        // exchangeName);

        if (_subsManager.IsEmpty)
            // _queueName = string.Empty;
            _consumerChannel.Close();
    }

    private void DoInternalSubscription(string exchangeName)
    {
        // var containsKey = _subsManager.HasSubscriptionsForEvent(exchangeName);
        // if (!containsKey)
        // {
        if (!_persistentConnection.IsConnected) _persistentConnection.TryConnect();

        var result = _consumerChannel.QueueDeclare();
        if (result == null) return;
        _queueName = result.QueueName;

        _consumerChannel.QueueBind(_queueName,
            exchangeName,
            "/");

        // }
    }

    private void StartBasicConsume()
    {
        _logger.LogTrace("Starting RabbitMQ basic consume");

        if (_consumerChannel != null)
        {
            var consumer = new AsyncEventingBasicConsumer(_consumerChannel);

            consumer.Received += Consumer_Received;

            _consumerChannel.BasicConsume(
                _queueName,
                false,
                consumer);
        }
        else
        {
            _logger.LogError("StartBasicConsume can't call on _consumerChannel == null");
        }
    }

    private async Task Consumer_Received(object sender, BasicDeliverEventArgs eventArgs)
    {
        var exchangeName = eventArgs.Exchange;
        var message = eventArgs.Body.ToArray();

        try
        {
            await ProcessEvent(exchangeName, message);
        }
        catch (Exception ex)
        {
            _logger.LogWarning(ex, "----- ERROR Processing message \"{Message}\"", message);
        }

        // Even on exception we take the message off the queue.
        // in a REAL WORLD app this should be handled with a Dead Letter Exchange (DLX). 
        // For more information see: https://www.rabbitmq.com/dlx.html
        _consumerChannel.BasicAck(eventArgs.DeliveryTag, false);
    }

    private IModel CreateConsumerChannel()
    {
        if (!_persistentConnection.IsConnected) _persistentConnection.TryConnect();

        _logger.LogTrace("Creating RabbitMQ consumer channel");

        var channel = _persistentConnection.CreateModel();

        // channel.ExchangeDeclare(BROKER_NAME,
        //     "direct");
        //
        // channel.QueueDeclare(_queueName,
        //     true,
        //     false,
        //     false,
        //     null);

        channel.CallbackException += (sender, ea) =>
        {
            _logger.LogWarning(ea.Exception, "Recreating RabbitMQ consumer channel");

            _consumerChannel.Dispose();
            _consumerChannel = CreateConsumerChannel();
            StartBasicConsume();
        };

        return channel;
    }

    private async Task ProcessEvent(string exchangeName, byte[] message)
    {
        _logger.LogTrace("Processing RabbitMQ event: {exchangeName}", exchangeName);

        if (_subsManager.HasSubscriptionsForExchange(exchangeName))
        {
            _logger.LogTrace("Creating scope for event handlers for exchange {ExchangeName}", exchangeName);
            await using var scope = _autofac.BeginLifetimeScope(AUTOFAC_SCOPE_NAME);
            var subscriptions = _subsManager.GetHandlersForExchange(exchangeName);
            foreach (var subscription in subscriptions)
            {
                _logger.LogTrace("Resolving handler for {ExchangeName} with type {HandlerType}", exchangeName,
                    subscription.HandlerType);
                // if (subscription.IsDynamic)
                // {
                //     if (scope.ResolveOptional(subscription.HandlerType) is not IDynamicIntegrationEventHandler handler)
                //         continue;
                //     using dynamic eventData = JsonDocument.Parse(message);
                //     await Task.Yield();
                //     await handler.Handle(eventData);
                // }
                // else
                // {
                if (scope.ResolveOptional(subscription.HandlerType) is not IIntegrationEventHandler handler) continue;
                // var eventType = _subsManager.GetEventTypeByName(exchangeName);
                // var integrationEvent = JsonSerializer.Deserialize(message, eventType,
                // new JsonSerializerOptions { PropertyNameCaseInsensitive = true });
                // var concreteType = typeof(IIntegrationEventHandler<>).MakeGenericType(eventType);

                await Task.Yield();
                _logger.LogTrace("Invoking `handle()` on handler {HandlerName}", handler.GetType().Name);
                await handler.Handle(message);
                // await (Task)concreteType.GetMethod("Handle").Invoke(handler, new[] { integrationEvent });
                // }
            }
        }
        else
        {
            _logger.LogWarning("No subscription for RabbitMQ event: {exchangeName}", exchangeName);
        }
    }
}