using Logic.Logic;
using Logic.Messaging;
using Logic.Trace;
using ScopeWebApi;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Configure the HTTP request pipeline.
//if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

try
{
    var programParameters = new ProgramParameters();
    var messageRouter = new MessageRouter();
    var traceFilesPath = programParameters.GetParameter("TraceFilesPath");
    var scopeTraceHandler = new ScopeTraceHandler(traceFilesPath);
    messageRouter.AddHandler("trace", scopeTraceHandler);
    ISystemWrapper systemWrapper = new SystemWrapper();
    IScopeTraceDirectory scopeTraceDirectory = new ScopeTraceDirectory(traceFilesPath, systemWrapper);

    app.MapPut("/scope", async delegate (HttpContext context)
    {
        string jsonstring = await Tools.GetJSONString(context);

        try
        {
            var response = messageRouter.Route(jsonstring);
            return response ? "Ok" : "Not Ok";
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error processing scope: {ex.Message}");
            Console.WriteLine(jsonstring);
            return "Not Ok";
        }
    })
    .WithName("Scope");

    app.MapPut("/test", () =>
    {
        var jsonString = @"{""data"": ""48656c6c6f20576f726c64"", ""type"": ""trace""}";
        try
        {
            var response = messageRouter.Route(jsonString);
            return response ? "Ok" : "Not Ok";
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error processing scope: {ex.Message}");
            Console.WriteLine(jsonString);
            return "Not Ok";
        }
    })
    .WithName("Test");

    app.MapGet("/tracenames", () =>
    {
        return scopeTraceDirectory.GetTraceDetails();
    })
   .WithName("TraceNames")
   .WithTags("Traces");

    app.Run();
}
catch (Exception ex)
{
    Console.WriteLine(ex.Message);
}
