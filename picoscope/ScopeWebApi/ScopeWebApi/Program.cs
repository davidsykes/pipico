using Logic.Logic;
using Logic.Messaging;
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
    var hexDataConverter = new HexDataConverter();
    var messageRouter = new MessageRouter(hexDataConverter);

    app.MapPut("/scope", async delegate (HttpContext context)
    {
        string jsonstring = await Tools.GetJSONString(context);

        try
        {
            var response = messageRouter.Route(jsonstring);
            Console.WriteLine(response);
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

    app.MapPut("/test", (string jsonstring) =>
    {
        try
        {
            jsonstring = @"{""data"": ""fe48656c6c6f20576f726c64"", ""type"": ""trace""}";
            var response = messageRouter.Route(jsonstring);
            Console.WriteLine(response);
            return response ? "Ok" : "Not Ok";
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error processing scope: {ex.Message}");
            Console.WriteLine(jsonstring);
            return "Not Ok";
        }
    })
    .WithName("Test");

    app.Run();
}
catch (Exception ex)
{
    Console.WriteLine(ex.Message);
}
