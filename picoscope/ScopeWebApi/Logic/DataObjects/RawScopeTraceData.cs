using Logic.Logic;
using System.Text.Json;

namespace Logic.DataObjects
{
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
            throw new ScopeWebApiException("The trace data has not been recognised.");
        }
    }
}
