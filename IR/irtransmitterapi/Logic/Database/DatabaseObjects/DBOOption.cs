#nullable disable
using SQLiteLibrary.Attributes;

namespace Logic.Database.DatabaseObjects
{
    [TableName("Options")]
    public class DBOOption
    {
        [PrimaryKey]
        public string Name { get; internal set; }
        public string Value { get; internal set; }
    }
}
