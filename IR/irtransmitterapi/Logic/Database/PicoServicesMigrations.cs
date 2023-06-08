using Logic.Database.DatabaseObjects;
using Logic.Database.DatabaseObjects.IR;
using Migrations;
using SQLiteLibrary;
using SQLiteLibrary.Attributes;

namespace Logic.Database
{
    internal class IrTransmitterApiMigrations
    {
        internal static IList<MigrationDefinition> Migrations = new List<MigrationDefinition>
            {
            new MigrationDefinition
            {
                Name = "Initial Migration",
                Migration = InitialMigration
            },
            new MigrationDefinition
            {
                Name = "Rename IRRWavePoints table",
                Migration = RenameIRRWavePoints
            },
            new MigrationDefinition
            {
                Name = "Create Sequences table",
                Migration = CreateSequencesTable
            }
        };

        public static void RunMigrations(IDatabaseConnection connection)
        {
            RunMigrations(connection, Migrations);
        }

        internal static void RunMigrations(IDatabaseConnection connection, IList<MigrationDefinition> migrations)
        {
            var manager = new MigrationsManager(connection);

            manager.RunMigrations(migrations);
        }

        [TableName("IRRWavePoints")]
        internal class DBOWavePoint_0
        {
            public string Code { get; set; } = string.Empty;
            public int Time { get; set; }
            public int Value { get; set; }
        }

        private static void InitialMigration(IDatabaseTransaction t)
        {
            t.CreateTable<DBOOption>();
            t.CreateTable<DBOWavePoint_0>();
            t.CreateTable<DBOLog>();
        }

        private static void RenameIRRWavePoints(IDatabaseTransaction t)
        {
            t.ExecuteNonQuery("ALTER TABLE 'IRRWavePoints' RENAME TO 'IRWavePoints'");
        }

        private static void CreateSequencesTable(IDatabaseTransaction t)
        {
            t.CreateTable<DBOSequence>();
        }
    }
}