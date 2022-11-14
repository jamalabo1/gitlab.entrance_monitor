namespace EntranceMonitor.API.Application.SignalR.Models;

public interface ISubscriptionClient
{
    Task ReceiveFrame(byte[] buffer);
}