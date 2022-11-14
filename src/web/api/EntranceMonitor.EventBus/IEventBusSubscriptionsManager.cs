using EntranceMonitor.EventBus.Abstractions;
using EntranceMonitor.EventBus.Events;

namespace EntranceMonitor.EventBus;

public interface IEventBusSubscriptionsManager
{
    bool IsEmpty { get; }
    event EventHandler<string> OnEventRemoved;
 
    void AddSubscription<TH>(string exchangeName)
        where TH : IIntegrationEventHandler;

    void RemoveSubscription<T, TH>()
            where TH : IIntegrationEventHandler<T>
            where T : IntegrationEvent;
 
     bool HasSubscriptionsForExchange(string eventName);
     void Clear();
     IEnumerable<SubscriptionInfo> GetHandlersForExchange(string eventName);
    string GetEventKey<T>();
}
