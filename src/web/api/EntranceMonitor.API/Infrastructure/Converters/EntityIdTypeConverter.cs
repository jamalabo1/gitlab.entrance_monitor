using System.ComponentModel;
using System.Globalization;

namespace EntranceMonitor.API.Infrastructure.Converters;

public class EntityIdTypeConverter : TypeConverter
{
    private readonly IHttpContextAccessor _httpContextAccessor;

    public EntityIdTypeConverter(IHttpContextAccessor httpContextAccessor)
    {
        _httpContextAccessor = httpContextAccessor;
    }

    public EntityIdTypeConverter()
    {
    }


    public override bool CanConvertFrom(ITypeDescriptorContext context, Type sourceType)
    {
        if (sourceType == typeof(string) || sourceType == typeof(string)) return true;
        return base.CanConvertFrom(context, sourceType);
    }

    public override object ConvertFrom(ITypeDescriptorContext context, CultureInfo culture, object value)
    {
        if (value is string s) return EntityId.Create(s);
        return base.ConvertFrom(context, culture, value);
    }

    public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
    {
        return destinationType == typeof(string) || base.CanConvertTo(context, destinationType);
    }

    public override object ConvertTo(ITypeDescriptorContext context, CultureInfo culture, object value,
        Type destinationType)
    {
        if (destinationType == typeof(string) && value is EntityId id) return id.ToString();

        return base.ConvertTo(context, culture, value, destinationType);
    }
}