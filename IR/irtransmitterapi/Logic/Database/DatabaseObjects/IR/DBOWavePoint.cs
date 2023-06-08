using SQLiteLibrary.Attributes;
#nullable disable
namespace Logic.Database.DatabaseObjects.IR
{
    [TableName("IRWavePoints")]
    internal class DBOWavePoint
    {
        public string Code { get; set; }
        public int Time { get; set; }
        public int Value { get; set; }
    }
}
