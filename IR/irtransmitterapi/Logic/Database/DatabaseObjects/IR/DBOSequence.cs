#nullable disable
using SQLiteLibrary.Attributes;

namespace Logic.Database.DatabaseObjects.IR
{
    [TableName("Sequences")]
    internal class DBOSequence
    {
        [PrimaryKey]
        public string Sequence { get; internal set; }
        [PrimaryKey]
        public string Code { get; internal set; }
        [PrimaryKey]
        public int Position { get; internal set; }
    }
}
