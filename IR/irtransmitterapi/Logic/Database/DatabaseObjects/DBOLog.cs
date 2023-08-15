#nullable disable
using SQLiteLibrary.Attributes;

namespace Logic.Database.DatabaseObjects
{
    [TableName("Logs")]
    public class DBOLog
    {
        public DateTime Time { get; internal set; }
        public string Text { get; internal set; }
    }
}
