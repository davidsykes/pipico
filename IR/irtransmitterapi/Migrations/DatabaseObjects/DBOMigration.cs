using SQLiteLibrary.Attributes;

#nullable disable
namespace Migrations.DatabaseObjects
{
    [TableName("Migrations")]
    internal class DBOMigration
    {
        [PrimaryKey]
        public string MigrationName { get; set; }
    }
}
