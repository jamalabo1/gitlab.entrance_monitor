using EntranceMonitor.API.Application.SignalR.Models;
using EntranceMonitor.EventBus.Abstractions;
using EntranceMonitor.ViewModels;
using Microsoft.AspNetCore.SignalR;

namespace EntranceMonitor.API.Application.EventHandlers;

public class FrameViewEventHandler : IIntegrationEventHandler
{
    private readonly IHubContext<ClientSubscriptionHub, ISubscriptionClient> _clientHub;
    private readonly ILogger<FrameViewEventHandler> _logger;

    public FrameViewEventHandler(IHubContext<ClientSubscriptionHub, ISubscriptionClient> clientHub,
        ILogger<FrameViewEventHandler> logger)
    {
        _clientHub = clientHub;
        _logger = logger;
    }

    public async Task Handle(byte[] body)
    {
        _logger.LogTrace("Received message with body-length {BodyLength}", body.Length);
        var @event = FrameView.Parser.ParseFrom(body);
        var buffer = @event.FrameData.ToByteArray();
        _logger.LogTrace("Sending encoded frame buffer to clients");
        await _clientHub.Clients.Group("frames.{1}").ReceiveFrame(buffer);
    }
}