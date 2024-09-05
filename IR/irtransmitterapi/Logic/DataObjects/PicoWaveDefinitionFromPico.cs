#nullable disable
using System.Text.Json;

namespace Logic.DataObjects
{
    internal class WaveDefinitionFromPico
    {
        public int InitialValue { get; set; }
        public IList<int[]> Values { get; set; }

        public static WaveDefinitionFromPico DeserialiseMessage(string jsonString)
        {
            try
            {
                var traceData = JsonSerializer.Deserialize<WaveDefinitionFromPico>(jsonString);

                if (traceData != null)
                    return traceData;
            }
            catch (JsonException)
            {
            }
            throw new IrTransmitterApiException("The trace data has not been recognised.");
        }
    }
}