using Logic.Logic;
using System.Text.Json;

namespace Logic.Trace
{
    class TraceData
    {
        public int InitialValue { get; set; }
        public List<List<int>> Values { get; set; }

        public TraceData()
        {
            Values = new List<List<int>>();
        }
    }

    public class ScopeTraceHandler2
    {
        private readonly string _traceFilePath;

        public ScopeTraceHandler2(string traceFilePath)
        {
            _traceFilePath = traceFilePath;
        }

        public string HandleTrace(string json)
        {
            if (string.IsNullOrEmpty(json))
            {
                var exampleTraceData = new TraceData();
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

            DeserialiseMessage(json);
            Console.WriteLine("Trace Received");

            var fileName = DateTime.Now.ToString("yyyyMMddHHmmss") + ".trc";
            var filePath = Path.Combine(_traceFilePath, fileName);
            Console.WriteLine($"Write data to {filePath}");
            File.WriteAllText(filePath, json);

            return "";
        }

        private static TraceData DeserialiseMessage(string jsonString)
        {
            try
            {
                var traceData = JsonSerializer.Deserialize<TraceData>(jsonString);

                if (traceData != null)
                    return traceData;
            }
            catch (JsonException)
            {
            }
            throw new ScopeWebApiException("The trace data has not been recognised.");
        }
    }
}
