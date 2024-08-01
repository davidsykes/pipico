using Logic;
using Logic.DataObjects;
using System.Text.Json;


public class RawScopeTraceData
{
    public int InitialValue { get; set; }
    public List<List<int>> Values { get; set; }

    public RawScopeTraceData()
    {
        Values = new List<List<int>>();
    }

    public static RawScopeTraceData DeserialiseMessage(string jsonString)
    {
        try
        {
            var traceData = JsonSerializer.Deserialize<RawScopeTraceData>(jsonString);

            if (traceData != null)
                return traceData;
        }
        catch (JsonException)
        {
        }
        throw new IrTransmitterApiException("The trace data has not been recognised.");
    }
}

namespace Logic.Codes
{
    public class TraceJsonToIrCodeDefinitionConverter
    {

        public static IRCodeDefinition Convert(string jsonString)
        {
            var trace = RawScopeTraceData.DeserialiseMessage(jsonString);
            var irCode = new IRCodeDefinition
            {
                Code = "New Code",
                Waveform = trace.Values.Select(x => new WavePoint
                {
                    T = x[0],
                    V = x[1]
                }).ToList()
            };
            return irCode;
        }
    }
}
