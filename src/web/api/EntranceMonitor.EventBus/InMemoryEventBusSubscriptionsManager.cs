using EntranceMonitor.EventBus.Abstractions;
using EntranceMonitor.EventBus.Events;

namespace EntranceMonitor.EventBus;

public partial class InMemoryEventBusSubscriptionsManager : IEventBusSubscriptionsManager
{


    private readonly Dictionary<string, List<SubscriptionInfo>> _handlers;

    public InMemoryEventBusSubscriptionsManager()
    {
        _handlers = new Dictionary<string, List<SubscriptionInfo>>();
    }

    public event EventHandler<string> OnEventRemoved;

    public bool IsEmpty => _handlers is { Count: 0 };

    public void Clear()
    {
        _handlers.Clear();
    }


    public void AddSubscription<TH>(string exchangeName)
        where TH : IIntegrationEventHandler
    {
        DoAddSubscription(typeof(TH), exchangeName, false);
    }


    public void RemoveSubscription<T, TH>()
        where TH : IIntegrationEventHandler<T>
        where T : IntegrationEvent
    {
        var handlerToRemove = FindSubscriptionToRemove<T, TH>();
        var eventName = GetEventKey<T>();
        DoRemoveHandler(eventName, handlerToRemove);
    }


    public IEnumerable<SubscriptionInfo> GetHandlersForExchange(string exchangeName)
    {
        return _handlers[exchangeName];
    }


    public bool HasSubscriptionsForExchange(string exchangeName)
    {
        return _handlers.ContainsKey(exchangeName);
    }

    public string GetEventKey<T>()
    {
        return typeof(T).Name;
    }

    private void DoAddSubscription(Type handlerType, string exchangeName, bool isDynamic)
    {
        if (!HasSubscriptionsForExchange(exchangeName)) _handlers.Add(exchangeName, new List<SubscriptionInfo>());

        if (_handlers[exchangeName].Any(s => s.HandlerType == handlerType))
            throw new ArgumentException(
                $"Handler Type {handlerType.Name} already registered for '{exchangeName}'", nameof(handlerType));

        if (isDynamic)
            _handlers[exchangeName].Add(SubscriptionInfo.Dynamic(handlerType));
        else
            _handlers[exchangeName].Add(SubscriptionInfo.Typed(handlerType));
    }


    private void DoRemoveHandler(string eventName, SubscriptionInfo subsToRemove)
    {
        if (subsToRemove != null)
        {
            _handlers[eventName].Remove(subsToRemove);
            if (!_handlers[eventName].Any())
            {
                _handlers.Remove(eventName);
                RaiseOnEventRemoved(eventName);
            }
        }
    }

    private void RaiseOnEventRemoved(string eventName)
    {
        var handler = OnEventRemoved;
        handler?.Invoke(this, eventName);
    }


    private SubscriptionInfo FindDynamicSubscriptionToRemove<TH>(string eventName)
        where TH : IDynamicIntegrationEventHandler
    {
        return DoFindSubscriptionToRemove(eventName, typeof(TH));
    }


    private SubscriptionInfo FindSubscriptionToRemove<T, TH>()
        where T : IntegrationEvent
        where TH : IIntegrationEventHandler<T>
    {
        var eventName = GetEventKey<T>();
        return DoFindSubscriptionToRemove(eventName, typeof(TH));
    }

    private SubscriptionInfo DoFindSubscriptionToRemove(string eventName, Type handlerType)
    {
        if (!HasSubscriptionsForExchange(eventName)) return null;

        return _handlers[eventName].SingleOrDefault(s => s.HandlerType == handlerType);
    }
}