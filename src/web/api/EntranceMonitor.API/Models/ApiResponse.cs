namespace EntranceMonitor.API.Models;

public class ApiResponse : IApiResponse
{
    public ApiResponse(HttpStatusCode status)
    {
        Status = status;
    }

    public HttpStatusCode Status { get; }
}

public class ApiResponse<T> : IApiResponse<T>
{
    public ApiResponse(HttpStatusCode status, T response)
    {
        Status = status;
        Response = response;
    }

    public HttpStatusCode Status { get; }
    public T Response { get; }
}