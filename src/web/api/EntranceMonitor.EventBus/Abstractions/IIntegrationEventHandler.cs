using EntranceMonitor.EventBus.Events;

namespace EntranceMonitor.EventBus.Abstractions;

public interface IIntegrationEventHandler<in TIntegrationEvent> : IIntegrationEventHandler
    where TIntegrationEvent : IntegrationEvent
{
}

public interface IIntegrationEventHandler
{
    Task Handle(byte[] @event);
}
