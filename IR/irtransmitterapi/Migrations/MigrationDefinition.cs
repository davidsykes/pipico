using SQLiteLibrary;

#nullable disable
namespace Migrations
{
    public class MigrationDefinition
    {
        public string Name { get; set; }
        public Action<IDatabaseTransaction> Migration { get; set; }
    }
}
