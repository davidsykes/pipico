#nullable disable
namespace Logic.DataObjects
{
    public class IRSequence
    {
        public string Name { get; set; }
        public IList<string> Codes { get; set; }
    }

    public class IRSequences
    {
        public IList<IRSequence> Sequences {  get; set; }
    }
}
