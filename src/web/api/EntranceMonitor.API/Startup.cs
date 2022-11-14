using System.ComponentModel;
using EntranceMonitor.API.Application.EventHandlers;
using EntranceMonitor.API.Infrastructure.AutofacModules;
using EntranceMonitor.EventBus.Abstractions;
using EntranceMonitor.EventBusRabbitMQ.Modules;

namespace EntranceMonitor.API;

public class Startup
{
    public Startup(IConfiguration configuration)
    {
        // In ASP.NET Core 3.x, using `Host.CreateDefaultBuilder` (as in the preceding Program.cs snippet) will
        // set up some configuration for you based on your appsettings.json and environment variables. See "Remarks" at
        // https://docs.microsoft.com/en-us/dotnet/api/microsoft.extensions.hosting.host.createdefaultbuilder for details.
        Configuration = configuration;
    }

    private IConfiguration Configuration { get; }

    public void ConfigureContainer(ContainerBuilder builder)
    {
        builder.RegisterModule(new HandlersModule());


        // register rabbitmq event bus implementation
        builder.RegisterModule(new EventBusRabbitMqModule());
        // builder
    }

    public void ConfigureServices(IServiceCollection services)
    {
        // add custom entity-id to/from string converter
        TypeDescriptor.AddAttributes(typeof(EntityId), new TypeConverterAttribute(typeof(EntityIdTypeConverter)));

        services
            .AddCustomMvc()
            .AddHealthChecks(Configuration)
            .AddCustomSwagger(Configuration)
            .AddCustomConfiguration(Configuration)
            .AddSignalR();
    }


    public void Configure(IApplicationBuilder app, IWebHostEnvironment env, ILoggerFactory loggerFactory)
    {
        //loggerFactory.AddAzureWebAppDiagnostics();
        //loggerFactory.AddApplicationInsights(app.ApplicationServices, LogLevel.Trace);

        var pathBase = Configuration["PATH_BASE"];
        if (!string.IsNullOrEmpty(pathBase))
        {
            loggerFactory.CreateLogger<Startup>().LogDebug("Using PATH BASE '{pathBase}'", pathBase);
            app.UsePathBase(pathBase);
        }

        // app.UseHttpsRedirection();

        app.UseSwagger()
            .UseSwaggerUI(c =>
            {
                c.SwaggerEndpoint(
                    $"{(!string.IsNullOrEmpty(pathBase) ? pathBase : string.Empty)}/swagger/v1/swagger.json",
                    "EntranceMonitor.API V1");
                c.OAuthClientId("entrance-monitor-swaggerui");
                c.OAuthAppName("Entrance Monitor Swagger UI");
            });

        app.UseCors("AllowCorsPolicy");
        app.UseRouting();
        app.ConfigureAuth();

        app.UseEndpoints(endpoints =>
        {
            endpoints.MapDefaultControllerRoute();
            endpoints.MapControllers();
            endpoints.MapHealthChecks("/hc", new HealthCheckOptions
            {
                Predicate = _ => true,
                ResponseWriter = UIResponseWriter.WriteHealthCheckUIResponse
            });
            endpoints.MapHealthChecks("/liveness", new HealthCheckOptions
            {
                Predicate = r => r.Name.Contains("self")
            });
            endpoints.MapHub<ClientSubscriptionHub>("/subscribe");
        });

        app.ConfigureHubs();

        app.ConfigureEventBus();
    }
}

internal static class CustomExtensionsMethods
{
    public static IApplicationBuilder ConfigureAuth(this IApplicationBuilder app)
    {
        return app.UseAuthentication().UseAuthorization();
    }

    public static IApplicationBuilder ConfigureEventBus(this IApplicationBuilder app)
    {
        var eventBus = app.ApplicationServices.GetRequiredService<IEventBus>();

        eventBus.Subscribe<FrameViewEventHandler>("frames.{1}");

        return app;
    }

    public static IApplicationBuilder ConfigureHubs(this IApplicationBuilder app)
    {
        return app;
    }

    public static IServiceCollection AddCustomMvc(this IServiceCollection services)
    {
        // Add framework services.
        services.AddControllers(options =>
            {
                // options.Filters.Add(typeof(HttpGlobalExceptionFilter));
            })
            // Added for functional tests
            // .AddApplicationPart(typeof(StudentOrderingController).Assembly)
            // .AddApplicationPart(typeof(StudentsController).Assembly)
            .AddJsonOptions(options =>
            {
                options.JsonSerializerOptions.WriteIndented = true;
                options.JsonSerializerOptions.Converters.Add(new JsonStringEnumConverter());
                options.JsonSerializerOptions.Converters.Add(new EntityIdJsonConverter());
            });

        services
            .AddSingleton<IHttpContextAccessor, HttpContextAccessor>();


        services.AddCors(options =>
        {
            options.AddPolicy("AllowCorsPolicy",
                builder => builder
                    // .SetIsOriginAllowed(host => true)
                    .AllowAnyMethod()
                    .AllowAnyHeader()
                    .SetIsOriginAllowed(origin => true) // allow any origin
                    .AllowCredentials());
        });

        return services;
    }

    public static IServiceCollection AddHealthChecks(this IServiceCollection services, IConfiguration configuration)
    {
        var hcBuilder = services.AddHealthChecks();

        hcBuilder.AddCheck("self", () => HealthCheckResult.Healthy());

        return services;
    }


    public static IServiceCollection AddCustomSwagger(this IServiceCollection services, IConfiguration configuration)
    {
        services.AddSwaggerGen();

        return services;
    }


    public static IServiceCollection AddCustomConfiguration(this IServiceCollection services,
        IConfiguration configuration)
    {
        services.AddOptions();
        services.Configure<ApiBehaviorOptions>(options =>
        {
            options.InvalidModelStateResponseFactory = context =>
            {
                var problemDetails = new ValidationProblemDetails(context.ModelState)
                {
                    Instance = context.HttpContext.Request.Path,
                    Status = StatusCodes.Status400BadRequest,
                    Detail = "Please refer to the errors property for additional details."
                };

                return new BadRequestObjectResult(problemDetails)
                {
                    ContentTypes = { "application/problem+json", "application/problem+xml" }
                };
            };
        });

        return services;
    }
}