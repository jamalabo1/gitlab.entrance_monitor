namespace EntranceMonitor.Domain.AggregateRoot.ServiceStream;

public class ServiceStream : ValueEntity
{
    public ServiceStream(EntityId id, string key)
    {
        Id = id;
        Key = key;
    }

    public string Key { get; }
}