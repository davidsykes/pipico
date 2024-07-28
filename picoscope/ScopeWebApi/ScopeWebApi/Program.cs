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

Console.WriteLine("===== Starting =====");

try
{
    var programParameters = new ProgramParameters();
    var messageRouter = new MessageRouter();
    var traceFilesPath = programParameters.GetParameter("TraceFilesPath");
    var scopeTraceHandler = new ScopeTraceHandler(traceFilesPath);
    var scopeTraceHandler2 = new ScopeTraceHandler2(traceFilesPath);
    messageRouter.AddHandler("trace", scopeTraceHandler);
    ISystemWrapper systemWrapper = new SystemWrapper();
    IScopeTraceDirectory scopeTraceDirectory = new ScopeTraceDirectory(traceFilesPath, systemWrapper);

    app.MapPut("/scope", async delegate (HttpContext context)
    {
        string jsonString = await Tools.GetJSONString(context);

        // Message Format
        // {"type":"trace","data":"785634120102030442"}
        // data format:
        //  78563412        - 0x12345678
        //  xxxx            - Number of samples
        //  llll            - Length of sample (us)
        //   tttt           - Sample time
        //   v              - Sample value
        //  xxxxxxxx        - Terminating value
        // jsonString = "{\"type\":\"trace\",\"data\":\"7856341202000000320000000300000005150000000921436587\"}";

        try
        {
            var response = messageRouter.Route(jsonString);
            return response ? "Ok" : "Not Ok";
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error processing legacy scope url: {ex.Message}");
            Console.WriteLine(jsonString);
            return "Not Ok";
        }
    })
    .WithName("Scope");

    app.MapPut("/trace", async delegate (HttpContext context)
    {
        string jsonString = await Tools.GetJSONString(context);

        try
        {
            var response = scopeTraceHandler2.HandleTrace(jsonString);
            return string.IsNullOrEmpty(response) ? "Ok" : $"Not Ok: {response}";
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error processing trace data: {ex.Message}");
            Console.WriteLine(jsonString);
            return "Not Ok";
        }
    })
    .WithName("Create Trace");

    app.MapPut("/log", async delegate (HttpContext context)
    {
        string jsonString = await Tools.GetJSONString(context);
        Console.WriteLine($"--- Log {DateTime.Now} ---");
        Console.WriteLine(jsonString);
        Console.WriteLine($"--- Log end ---");
        return "Ok";
    })
    .WithName("Log");

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
            Console.WriteLine($"Error processing log: {ex.Message}");
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

    app.MapPost("/delete/{path}", (string path) =>
    {
        scopeTraceDirectory.DeleteTrace(path);
        Console.WriteLine($"Delete trace {path}");
        return path;
    })
   .WithName("Delete")
   .WithTags("Traces");

    app.MapGet("/trace/{path}", (string path) =>
    {
        var trace_data = scopeTraceDirectory.GetTraceData(path);
        return trace_data;
    })
   .WithName("Trace")
   .WithTags("Traces");

    app.MapGet("/currenttrace", () =>
    {
        var trace_data = scopeTraceDirectory.GetCurrentTraceData();
        return trace_data;
    })
   .WithName("Current Trace")
   .WithTags("Traces");

    Console.WriteLine("===== Started =====");
    app.Run();
}
catch (Exception ex)
{
    Console.WriteLine(ex.Message);
}
