using Logic.DataObjects;
using System.Text.Json;

namespace Logic.Trace
{

    public class ScopeTraceHandler
    {
        private readonly string _traceFilePath;

        public ScopeTraceHandler(string traceFilePath)
        {
            _traceFilePath = traceFilePath;
        }

        public string HandleTrace(string json)
        {
            if (string.IsNullOrEmpty(json))
            {
                var exampleTraceData = new RawScopeTraceData();
                exampleTraceData.InitialValue = 2;
                exampleTraceData.Values.Add(new List<int>());
                exampleTraceData.Values[0].Add(1);
                exampleTraceData.Values[0].Add(2);
                exampleTraceData.Values.Add(new List<int>());
                exampleTraceData.Values[1].Add(1);
                exampleTraceData.Values[1].Add(2);

                Console.WriteLine(JsonSerializer.Serialize(exampleTraceData));

                return "Not ok";
            }

            RawScopeTraceData.DeserialiseMessage(json);
            Console.WriteLine("Trace Received");

            var fileName = DateTime.Now.ToString("yyyyMMddHHmmss") + ".trc";
            var filePath = Path.Combine(_traceFilePath, fileName);
            Console.WriteLine($"Write data to {filePath}");
            File.WriteAllText(filePath, json);

            return "";
        }
    }
}
