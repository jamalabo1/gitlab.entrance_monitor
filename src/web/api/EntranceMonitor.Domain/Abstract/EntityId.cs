namespace EntranceMonitor.Domain.Abstract;

public readonly struct EntityId : IComparable<EntityId>, IEquatable<EntityId>
{
    public override bool Equals(object? obj)
    {
        return obj is EntityId other && Equals(other);
    }

    public override int GetHashCode()
    {
        return Value.GetHashCode();
    }

    private Guid Value { get; }

    public EntityId(Guid value)
    {
        Value = value;
    }

    public Guid GetValue()
    {
        return Value;
    }

    public int CompareTo(EntityId other)
    {
        return ((Guid)this).CompareTo((Guid)other);
    }

    public bool Equals(EntityId other)
    {
        return ((Guid)this).Equals((Guid)other);
    }

    public static EntityId Create(Guid id)
    {
        return new EntityId(id);
    }

    public static EntityId Create()
    {
        return Create(Guid.NewGuid());
    }

    public static EntityId Create(string id)
    {
        return Create(Guid.Parse(id));
    }

    public override string ToString()
    {
        return ((Guid)this).ToString();
    }

    public static bool operator ==(EntityId left, EntityId right)
    {
        return (Guid)left == (Guid)right;
    }

    public static bool operator !=(EntityId left, EntityId right)
    {
        return (Guid)left != (Guid)right;
    }

    public static implicit operator EntityId(Guid guid)
    {
        return Create(guid);
    }

    public static explicit operator Guid(EntityId id)
    {
        return id.GetValue();
    }

    public static implicit operator EntityId(string id)
    {
        return Create(id);
    }

    public static implicit operator string(EntityId id)
    {
        return id.ToString();
    }
}