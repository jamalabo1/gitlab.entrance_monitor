namespace EntranceMonitor.API.Infrastructure.Converters;

public class EntityIdJsonConverter : JsonConverter<EntityId>
{
    public override EntityId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
    {
        var value = reader.GetString();
        return EntityId.Create(value);
    }

    public override void Write(Utf8JsonWriter writer, EntityId value, JsonSerializerOptions options)
    {
        writer.WriteStringValue(value.GetValue());
    }
}