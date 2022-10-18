namespace EntranceMonitor.API.Controllers;

[ApiController]
[Route("[controller]")]
public class StreamsController : Controller
{
    [HttpGet("all")]
    public IApiResponse<List<ServiceStream>> GetAll()
    {
        var list = new List<ServiceStream>
        {
            new("9c026d85-7a7d-4959-a744-fe902dcec31a", "frames.{1}"),
            new("b9771db0-ce7e-45fc-bc0a-98d6d8d4fa16", "detections.{1}"),
            new("7226476f-7430-4638-bcff-0ffe62900e27", "blocking.{1}"),
            new("a6d189c6-abb8-4f52-884a-c72f39ba78a5", "results.{1}")
        };
        return new ApiResponse<List<ServiceStream>>(HttpStatusCode.OK, list);
    }
}