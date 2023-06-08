using Migrations.DatabaseObjects;
using SQLiteLibrary;

namespace Migrations
{
    public class MigrationsManager : IMigrationsManager
    {
        private IDatabaseConnection _connection;

        public MigrationsManager(IDatabaseConnection connection)
        {
            _connection = connection;
        }

        public void RunMigrations(IList<MigrationDefinition> migrationDefinitions)
        {
            CreateMigrationsTableIfNecessary();

            var migrationsAlreadyRun = GetMigrationsThatHaveAlreadyBeenRun();

            foreach (var migration in migrationDefinitions)
            {
                RunMigrationIfItHasNotAlreadyBeenRun(migration, migrationsAlreadyRun);
            }
        }

        private void CreateMigrationsTableIfNecessary()
        {
            var table_name = "Migrations";
            var migrationTables = _connection.Select<DBOTableName>(
                $"SELECT name FROM sqlite_master WHERE type = 'table' AND name = '{table_name}';");

            if (!migrationTables.Any())
            {
                _connection.RunInTransaction((IDatabaseTransaction t) => t.CreateTable<DBOMigration>());
            }
        }

        private HashSet<string> GetMigrationsThatHaveAlreadyBeenRun()
        {
            var migrations = _connection.Select<DBOMigration>();
            return migrations.Select(m => m.MigrationName).ToHashSet();
        }

        private void RunMigrationIfItHasNotAlreadyBeenRun(
            MigrationDefinition migrationDefinition, HashSet<string> migrationsAlreadyRun)
        {
            if (!migrationsAlreadyRun.Contains(migrationDefinition.Name))
            {
                RunMigration(migrationDefinition);
            }
        }

        private void RunMigration(MigrationDefinition migrationDefinition)
        {
            _connection.RunInTransaction((IDatabaseTransaction t)
                =>
            {
                migrationDefinition.Migration(t);
                t.InsertRow(new DBOMigration { MigrationName = migrationDefinition.Name });
            });
        }
    }
}