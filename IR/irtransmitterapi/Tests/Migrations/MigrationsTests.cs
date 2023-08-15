using Logic.Database;
using Logic.Database.DatabaseObjects;
using Logic.Database.DatabaseObjects.IR;
using SQLiteLibrary;
using TestHelpers;

#nullable disable
namespace Tests.Logic
{
    public class MigrationsTests : TestBase
    {
        IDatabaseConnection _dbConnection;

        [Test]
        public void TheFirstMigrationCreatesTheOptionsWavePointsAndLogsTables()
        {
            var migrations = IrTransmitterApiMigrations.Migrations.Take(1).ToList();

            IrTransmitterApiMigrations.RunMigrations(_dbConnection, migrations);

            _dbConnection.Select<DBOOption>();
            _dbConnection.Select<DBOLog>();
        }

        [Test]
        public void TheSecondMigrationCorrectsTheWavePointsTableName()
        {
            var migrations = IrTransmitterApiMigrations.Migrations.Take(2).ToList();

            IrTransmitterApiMigrations.RunMigrations(_dbConnection, migrations);

            _dbConnection.Select<DBOWavePoint>();
        }

        #region Support Code

        protected override void SetUpData()
        {
            base.SetUpData();
            _dbConnection = new DBServices().OpenMemoryDatabase();
            //_dbConnection = new DBServices().OpenFileConnection("D:\\SQLite\\TestDb.sql");
        }

        #endregion
    }
}