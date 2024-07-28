using Logic.Logic;
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
    var traceFilesPath = programParameters.GetParameter("TraceFilesPath");
    var scopeTraceHandler = new ScopeTraceHandler(traceFilesPath);
    ISystemWrapper systemWrapper = new SystemWrapper();
    IScopeTraceDirectory scopeTraceDirectory = new ScopeTraceDirectory(traceFilesPath, systemWrapper);

    app.MapPut("/trace", async delegate (HttpContext context)
    {
        string jsonString = await Tools.GetJSONString(context);

        try
        {
            var response = scopeTraceHandler.HandleTrace(jsonString);
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

    app.MapGet("/tracedetails", () =>
    {
        return scopeTraceDirectory.GetTraceDetails();
    })
   .WithName("TraceNames")
   .WithTags("Traces");

    // app.MapPost("/delete/{path}", (string path) =>
    // {
    //     scopeTraceDirectory.DeleteTrace(path);
    //     Console.WriteLine($"Delete trace {path}");
    //     return path;
    // })
    //.WithName("Delete")
    //.WithTags("Traces");

    // app.MapGet("/trace/{path}", (string path) =>
    // {
    //     var trace_data = scopeTraceDirectory.GetTraceData(path);
    //     return trace_data;
    // })
    //.WithName("Trace")
    //.WithTags("Traces");

    // app.MapGet("/currenttrace", () =>
    // {
    //     var trace_data = scopeTraceDirectory.GetCurrentTraceData();
    //     return trace_data;
    // })
    //.WithName("Current Trace")
    //.WithTags("Traces");

    Console.WriteLine("===== Started =====");
    app.Run();
}
catch (Exception ex)
{
    Console.WriteLine(ex.Message);
}
