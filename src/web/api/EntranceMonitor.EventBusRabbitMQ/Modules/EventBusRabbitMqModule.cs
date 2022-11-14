namespace EntranceMonitor.EventBusRabbitMQ.Modules;

public class EventBusRabbitMqModule : Module
{
    protected override void Load(ContainerBuilder builder)
    {
        builder.RegisterType<EventBusRabbitMQ>()
            .As<IEventBus>()
            .SingleInstance();

        builder.Register(sp =>
            {
                var logger = sp.Resolve<ILogger<DefaultRabbitMQPersistentConnection>>();

                var factory = new ConnectionFactory
                {
                    Uri = new Uri(
                        "amqps://fztujanq:LtL-9vJpnvMm8wEHYsdKCnJBIQi_ogjN@sparrow.rmq.cloudamqp.com/fztujanq"),
                    DispatchConsumersAsync = true,
                    ClientProvidedName = "app:audit component:event-consumer"
                };

                const int retryCount = 5;

                return new DefaultRabbitMQPersistentConnection(factory, logger);
            })
            .As<IRabbitMQPersistentConnection>()
            .InstancePerLifetimeScope();
    }
}