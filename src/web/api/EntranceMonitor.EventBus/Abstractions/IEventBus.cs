using EntranceMonitor.EventBus.Events;

namespace EntranceMonitor.EventBus.Abstractions;

public interface IEventBus
{
    void Subscribe<TH>(string exchangeName)
        where TH : IIntegrationEventHandler;

    void Unsubscribe<T, TH>()
        where TH : IIntegrationEventHandler<T>
        where T : IntegrationEvent;
}
