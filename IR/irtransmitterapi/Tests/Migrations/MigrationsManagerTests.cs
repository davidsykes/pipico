using FluentAssertions;
using Migrations;
using Migrations.DatabaseObjects;
using SQLiteLibrary;
using SQLiteLibrary.Attributes;
using TestHelpers;

#nullable disable
namespace Tests.Logic
{
    [TableName("TestTable")]
    internal class DBOTestRecord
    {
        [PrimaryKey]
        public string Text { get; internal set; }
    }

    public class MigrationsManagerTests : TestBase
    {
        IMigrationsManager _manager;

        IList<MigrationDefinition> _migrationDefinitions;
        IDatabaseConnection _dbConnection;

        [Test]
        public void TheMigrationsTableIsCreatedIfItDoesNotExists()
        {
            _manager.RunMigrations(_migrationDefinitions);

            var tables = _dbConnection.Select<DBOTableName>(
                $"SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'Migrations';");
            tables.Single().name.Should().Be("Migrations");
        }

        [Test]
        public void TheMigrationsTableIsNotCreatedTwice()
        {
            _manager.RunMigrations(_migrationDefinitions);
            _manager.RunMigrations(_migrationDefinitions);

            var tables = _dbConnection.Select<DBOTableName>(
                $"SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'Migrations';");
            tables.Single().name.Should().Be("Migrations");
        }

        [Test]
        public void AMigrationIsRunIfItHasNotBeenRunAlready()
        {
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration",
                Migration = ((IDatabaseTransaction t) => t.CreateTable<DBOTestRecord>())
            });

            _manager.RunMigrations(_migrationDefinitions);

            var tables = _dbConnection.Select<DBOTableName>(
                $"SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'TestTable';");
            tables.Single().name.Should().Be("TestTable");
        }

        [Test]
        public void AnExceptionIsThrownWhenAMigrationThrowsAnException()
        {
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration",
                Migration = (IDatabaseTransaction t) =>
                {
                    t.CreateTable<DBOTestRecord>();
                    throw new Exception("oops");
                }
            });

            var action = () => _manager.RunMigrations(_migrationDefinitions);

            action.Should().Throw<Exception>().WithMessage("oops");
        }

        [Test]
        public void AMigrationIsRolledBackWhenAnExceptionIsThrown()
        {
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration",
                Migration = (IDatabaseTransaction t) =>
                {
                    t.CreateTable<DBOTestRecord>();
                    throw new Exception("oops");
                }
            });

            var action = () => _manager.RunMigrations(_migrationDefinitions);

            action.Should().Throw<Exception>();

            var tables = _dbConnection.Select<DBOTableName>(
                $"SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'TestTable';");
            tables.Count.Should().Be(0);
        }

        [Test]
        public void MigrationsAreRunInOrder()
        {
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration 1",
                Migration = (IDatabaseTransaction t) => t.CreateTable<DBOTestRecord>()
            });
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration 2",
                Migration = (IDatabaseTransaction t) => t.InsertRows(new List<DBOTestRecord>
                {
                    new DBOTestRecord { Text = "Record 1" },
                    new DBOTestRecord { Text = "Record 2" }
                })
            });
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration 3",
                Migration = (IDatabaseTransaction t) => t.DeleteRow(new DBOTestRecord { Text = "Record 2" })
            });

            _manager.RunMigrations(_migrationDefinitions);

            _dbConnection.Select<DBOTestRecord>().Should().BeEquivalentTo(new List<DBOTestRecord>
            {
                new DBOTestRecord { Text = "Record 1" }
            });
        }

        [Test]
        public void MigrationNamesAreAddedToTheMigrationsTable()
        {
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration 1",
                Migration = (IDatabaseTransaction t) => t.CreateTable<DBOTestRecord>()
            });
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration 2",
                Migration = (IDatabaseTransaction t) => t.InsertRows(new List<DBOTestRecord>
                {
                    new DBOTestRecord { Text = "Record 1" },
                    new DBOTestRecord { Text = "Record 2" }
                })
            });
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration 3",
                Migration = (IDatabaseTransaction t) => t.DeleteRow(new DBOTestRecord { Text = "Record 2" })
            });

            _manager.RunMigrations(_migrationDefinitions);

            _dbConnection.Select<DBOMigration>().Should().BeEquivalentTo(new List<DBOMigration>
            {
                new DBOMigration { MigrationName = "Migration 1" },
                new DBOMigration { MigrationName = "Migration 2" },
                new DBOMigration { MigrationName = "Migration 3" }
            });
        }

        [Test]
        public void IfAMigrationFailsSubsequentMigrationsAreNotRun()
        {
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration 1",
                Migration = (IDatabaseTransaction t) => t.CreateTable<DBOTestRecord>()
            });
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration 2",
                Migration = (IDatabaseTransaction t) => throw new Exception("Oops")
            }); ;
            _migrationDefinitions.Add(new MigrationDefinition
            {
                Name = "Migration 3",
                Migration = (IDatabaseTransaction t) => t.DeleteRow(new DBOTestRecord { Text = "Record 2" })
            });

            Action action = () =>_manager.RunMigrations(_migrationDefinitions);
            action.Should().Throw<Exception>();

            _dbConnection.Select<DBOMigration>().Should().BeEquivalentTo(new List<DBOMigration>
            {
                new DBOMigration { MigrationName = "Migration 1" }
            });
        }

        #region Support Code

        protected override void SetUpObjectUnderTest()
        {
            base.SetUpObjectUnderTest();
            _manager = new MigrationsManager(_dbConnection);
        }

        protected override void SetUpData()
        {
            base.SetUpData();
            _dbConnection = new DBServices().OpenMemoryDatabase();
            //_dbConnection = new DBServices().OpenFileConnection("D:\\SQLite\\TestDb.sql");
            _migrationDefinitions = new List<MigrationDefinition>();
        }

        #endregion
    }
}