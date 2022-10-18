namespace EntranceMonitor.API.Models;

public interface IApiResponse
{
    public HttpStatusCode Status { get; }
}

public interface IApiResponse<out T> : IApiResponse
{
    public T Response { get; }
}