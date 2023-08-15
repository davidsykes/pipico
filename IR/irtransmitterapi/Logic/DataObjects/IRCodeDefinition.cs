#nullable disable
namespace Logic.DataObjects
{
    public class IRCodeDefinition
    {
        public string Code { get; set; }
        public IList<WavePoint> Waveform { get; set; }
    }
}
