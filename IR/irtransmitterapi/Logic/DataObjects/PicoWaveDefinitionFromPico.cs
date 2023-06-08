#nullable disable
namespace Logic.DataObjects
{
    internal class WaveDefinitionFromPico
    {
        public string code { get; set; }
        public IList<int[]> wavepoints { get; set; }
    }
}