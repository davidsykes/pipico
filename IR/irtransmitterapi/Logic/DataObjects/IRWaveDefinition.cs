#nullable disable
namespace Logic.DataObjects
{
    internal class IRWaveDefinition
    {
        public string code { get; set; }
        public IList<int[]> wavepoints { get; set; }
    }
}