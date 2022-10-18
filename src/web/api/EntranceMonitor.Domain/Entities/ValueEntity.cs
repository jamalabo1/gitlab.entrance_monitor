using System.Text.Json.Serialization;

namespace EntranceMonitor.Domain.Entities;

public class ValueEntity : IValueEntity
{
    public ValueEntity()
    {
        Id = EntityId.Create();
    }

    [JsonInclude] public EntityId Id { get; protected set; }


    protected static bool EqualOperator(ValueEntity left, ValueEntity right)
    {
        if (ReferenceEquals(left, null) ^ ReferenceEquals(right, null)) return false;
        return ReferenceEquals(left, null) || left.Equals(right);
    }

    protected static bool NotEqualOperator(ValueEntity left, ValueEntity right)
    {
        return !EqualOperator(left, right);
    }

    protected virtual IEnumerable<object> GetEqualityComponents()
    {
        var types =
            GetType()
                .GetProperties()
                .Where(x => x.GetAccessors().All(m => !m.IsVirtual));

        return types.Select(x => x.GetValue(this));
    }

    public override bool Equals(object obj)
    {
        if (obj == null || !obj.GetType().IsAssignableTo(typeof(ValueEntity))) return false;

        var other = (ValueEntity)obj;

        return GetEqualityComponents().SequenceEqual(other.GetEqualityComponents());
    }

    public override int GetHashCode()
    {
        return GetEqualityComponents()
            .Select(x => x != null ? x.GetHashCode() : 0)
            .Aggregate((x, y) => x ^ y);
    }

    public ValueEntity GetCopy()
    {
        return MemberwiseClone() as ValueEntity;
    }
}