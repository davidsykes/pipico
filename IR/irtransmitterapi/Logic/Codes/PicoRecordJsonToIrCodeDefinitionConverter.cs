using Logic.DataObjects;
using System.Text.Json;


namespace Logic.Codes
{
    internal class WaveDefinitionFromPico
    {
        public int InitialValue { get; set; }
        public IList<int[]>? Values { get; set; }
    }

    public class PicoRecordJsonToIrCodeDefinitionConverter
    {

        public static IRCodeDefinition Convert(string jsonString)
        {
            var trace = JsonSerializer.Deserialize<WaveDefinitionFromPico>(jsonString);
            if (trace != null)
            {
                var initialValue = trace.InitialValue;
                var irCode = new IRCodeDefinition
                {
                    Code = "New Code",
                    Waveform = trace.Values!.Select(x => new WavePoint
                    {
                        T = x[0],
                        V = x[1] == initialValue ? 0 : 1,
                    }).ToList()
                };
                return irCode;
            }
            else
            {
                throw new IrTransmitterApiException("Invalid json from pico");
            }
        }
    }
}
