using DSLogging;
using DSLogging.Loggers;
using Logic;
using IrTransmitterApi;
using ApplicationParameters;

IDSLogger logger = new ConsoleLogger();

try
{
    var builder = WebApplication.CreateBuilder(args);

    // Add services to the container.
    // Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
    builder.Services.AddEndpointsApiExplorer();
    builder.Services.AddSwaggerGen();

    var app = builder.Build();

    // Configure the HTTP request pipeline.
    //if (app.Environment.IsDevelopment())
    //{
    app.UseSwagger();
    app.UseSwaggerUI();
    //}

    var programParameters = new ProgramParameters();
    var programServices = new ProgramServices(programParameters);
    logger = programServices.Logger;
    programServices.DatabaseAccess.Log("Micro service started");

    AddOptionEndpoints(app, programServices);

    AddCodeEndpoints(app, programServices);

    AddSequenceEndpoints(app, programServices);

    AddLoggingEndpoints(app, programServices);

    app.Run();
}
catch (IrTransmitterApiException ex)
{
    logger.Log(DSLogLevel.Error, ex.Message);
    Console.WriteLine(ex.Message);
}
catch (ApplicationParameterException ex)
{
    logger.Log(DSLogLevel.Error, ex.Message);
    Console.WriteLine(ex.Message);
}

static void AddLoggingEndpoints(WebApplication app, ProgramServices programServices)
{
    app.MapPut("/log", async delegate (HttpContext context)
    {
        string JSONString = await Tools.GetJSONString(context);
        var log = programServices.DatabaseAccess.Log(JSONString);
        Console.WriteLine($"LOG: {log.Time} - {log.Text}");
        return "Ok";
    })
    .WithName("Log")
    .WithTags("Logs");

    app.MapGet("/logs", (int count) =>
    {
        var logs = programServices.DatabaseAccess.GetLogs(count);
        return logs;
    })
    .WithName("Logs")
    .WithTags("Logs");

    app.MapPut("/clearlogs", async delegate (HttpContext context)
    {
        programServices.DatabaseAccess.ClearLogs();
        return "Ok";
    })
    .WithName("ClearLogs")
    .WithTags("Logs");
}

static void AddCodeEndpoints(WebApplication app, ProgramServices programServices)
{
    app.MapGet("/codes", () =>
    {
        var codes = programServices.DatabaseAccess.GetCodes();
        return codes;
    })
   .WithName("Codes")
   .WithTags("Codes");

    app.MapPut("/trace", async delegate (HttpContext context)
    {
        string jsonString = await Tools.GetJSONString(context);
        return CreateNewIrCode(jsonString, programServices);
    })
    .WithName("Trace")
    .WithTags("Codes");

    app.MapPut("/manualsetcodedata", (string jsonString) =>
    {
        return CreateNewIrCode(jsonString, programServices);
    })
    .WithName("SetCodeNameManually")
    .WithTags("Codes");

    app.MapPut("/setcodename", (string code, string name) =>
    {
        programServices.DatabaseAccess.UpdateCodeName(code, name);
        Console.WriteLine($"Set code {code} to {name}");
    })
    .WithName("SetCodeName")
    .WithTags("Codes");

    app.MapPut("/deletecode", (string code) =>
    {
        programServices.DatabaseAccess.DeleteCode(code);
    })
    .WithName("DeleteCode")
    .WithTags("Codes");
}

static string CreateNewIrCode(string jsonString, ProgramServices programServices)
{
    try
    {
        var irCodeDefinition = Logic.Codes.TraceJsonToIrCodeDefinitionConverter.Convert(jsonString);

        programServices.DatabaseAccess.UpdateIrCodeDefinition(irCodeDefinition);
        Console.WriteLine($"Updated ir code {irCodeDefinition.Code}.");
        programServices.Logger.Log(DSLogLevel.Information, $"Updated ir code {irCodeDefinition.Code}");
        programServices.DatabaseAccess.Log($"Updated ir code {irCodeDefinition.Code}");
        return "Ok";
    }
    catch (Exception ex)
    {
        Console.WriteLine($"Error processing ircode: {ex.Message}");
        Console.WriteLine("\"" + jsonString + "\"");
    }

    return jsonString;
}

static void AddSequenceEndpoints(WebApplication app, ProgramServices programServices)
{
    app.MapPut("/setsequence", (string sequence, string code, int position) =>
    {
        programServices.DatabaseAccess.UpdateSequence(sequence, code, position);
        Console.WriteLine($"Set sequence {sequence} {code} {position}");
    })
    .WithName("SetSequence")
    .WithTags("Sequences");

    app.MapPut("/deletesequence", (string sequence, string code, int position) =>
    {
        programServices.DatabaseAccess.DeleteSequence(sequence, code, position);
        Console.WriteLine($"Delete sequence {sequence} {code} {position}");
    })
    .WithName("DeleteSequence")
    .WithTags("Sequences");

    app.MapGet("/sequences", () =>
    {
        var value = programServices.DatabaseAccess.GetSequences();
        return value;
    })
    .WithName("Sequences")
    .WithTags("Sequences");
}

static void AddOptionEndpoints(WebApplication app, ProgramServices programServices)
{
    app.MapGet("/option", (string option) =>
    {
        var value = programServices.DatabaseAccess.GetOption(option);
        programServices.Logger.Log(DSLogLevel.Information, $"Fetch option {option}={value}");
        programServices.DatabaseAccess.Log($"Fetch option {option}={value}");
        return value;
    })
    .WithName("Option")
    .WithTags("Options");

    app.MapPut("/setoption", (string name, string value) =>
    {
        programServices.Logger.Log(DSLogLevel.Information, $"Set option {name}={value}");
        programServices.DatabaseAccess.Log($"Set option {name}={value}");
        programServices.DatabaseAccess.SetOption(name, value);
        Console.WriteLine($"Set option {name} {value}");
    })
    .WithName("SetOption")
    .WithTags("Options");
}
