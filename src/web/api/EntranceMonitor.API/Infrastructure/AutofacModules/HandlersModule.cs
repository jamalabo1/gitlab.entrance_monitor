using EntranceMonitor.API.Application.EventHandlers;
using EntranceMonitor.EventBus.Abstractions;

namespace EntranceMonitor.API.Infrastructure.AutofacModules;

public class HandlersModule : Module
{
    protected override void Load(ContainerBuilder builder)
    {
        builder
            .RegisterAssemblyTypes(typeof(FrameViewEventHandler).Assembly)
            .InNamespace("EntranceMonitor.API.Application.EventHandlers")
            // .AsClosedTypesOf(typeof(IIntegrationEventHandler))
            .AsSelf()
            .AsImplementedInterfaces();
    }
}