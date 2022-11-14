using EntranceMonitor.API.Application.SignalR.Messages;
using Microsoft.AspNetCore.SignalR;
using EntranceMonitor.API.Application.SignalR.Models;

namespace EntranceMonitor.API.Application.SignalR;

[Route("/subscribe")]
public class ClientSubscriptionHub : Hub<ISubscriptionClient>
{
    public async Task SubscribeToTopic(SubscribeToTopicMessage message)
    {
        await Groups.AddToGroupAsync(Context.ConnectionId, message.TopicName);
    }
}