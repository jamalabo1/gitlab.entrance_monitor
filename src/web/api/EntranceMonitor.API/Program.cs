using Serilog;
using ILogger = Serilog.ILogger;

namespace EntranceMonitor.API;

public class Program
{
    private static readonly string Namespace = typeof(Program).Namespace;

    private static readonly string AppName =
        Namespace[(Namespace.LastIndexOf('.', Namespace.LastIndexOf('.') - 1) + 1)..];

    public static int Main(string[] args)
    {
        var configuration = GetConfiguration();
        Log.Logger = CreateSerilogLogger(configuration);

        try
        {
            Log.Information("Configuring web host ({ApplicationContext})...", AppName);
            var host = BuildWebHost(args);

            Log.Information("Starting web host ({ApplicationContext})...", AppName);
            host.Run();

            return 0;
        }
        catch (Exception ex)
        {
            Log.Fatal(ex, "Program terminated unexpectedly ({ApplicationContext})!", AppName);
            return 1;
        }
        finally
        {
            Log.CloseAndFlush();
        }
    }

    private static IHost BuildWebHost(string[] args)
    {
        return CreateHostBuilder(args).Build();
    }

    public static IHostBuilder CreateHostBuilder(string[] args)
    {
        return Host.CreateDefaultBuilder(args)
            .UseServiceProviderFactory(new AutofacServiceProviderFactory())
            .ConfigureWebHostDefaults(configure =>
            {
                configure
                    .CaptureStartupErrors(false)
                    .UseSerilog()
                    .UseStartup<Startup>();
            })
            .UseContentRoot(Directory.GetCurrentDirectory())
            .UseSerilog();
    }

    private static ILogger CreateSerilogLogger(IConfiguration configuration)
    {
        return new LoggerConfiguration()
            .MinimumLevel.Verbose()
            .Enrich.WithProperty("ApplicationContext", AppName)
            .Enrich.FromLogContext()
            .WriteTo.Console()
            .ReadFrom.Configuration(configuration)
            .CreateLogger();
    }

    private static IConfiguration GetConfiguration()
    {
        var builder = new ConfigurationBuilder()
            .SetBasePath(Directory.GetCurrentDirectory())
            .AddJsonFile("appsettings.json", false, true)
            .AddJsonFile("appsettings.development.json", true)
            .AddEnvironmentVariables();

        return builder.Build();
    }
}