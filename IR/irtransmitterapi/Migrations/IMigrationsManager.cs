namespace Migrations
{
    public interface IMigrationsManager
    {
        void RunMigrations(IList<MigrationDefinition> migrationDefinitions);
    }
}
