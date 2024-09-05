using FluentAssertions;
using Logic.DataObjects;
using TestHelpers;

#nullable disable
namespace Tests.Logic
{
    public class PicoWaveDefinitionFromPicoTests : TestBase
    {
        //IDatabaseAccess _db;

        //IDatabaseConnection _dbConnection;
        //readonly DateTime _initialTime = new(2020, 3, 15, 1, 2, 3);
        //DateTime _now2;
        //Mock<ISystemWrapper> _mockSystemWrapper;

        //#region Options

        [Test]
        public void ACodeCanBeConverted()
        {
            string json = "{\"InitialValue\":4,\"Values\":[[0,0],[4510,4],[9027,0],[9579,4],[11271,0],[11822,4],[13515,0],[14068,4],[15760,0],[16314,4],[16908,0],[17434,4],[18031,0],[18556,4],[19154,0],[19679,4],[20274,0],[20801,4],[21398,0],[21948,4],[23616,0],[24167,4],[25860,0],[26414,4],[28104,0],[28657,4],[29252,0],[29779,4],[30375,0],[30925,4],[31497,0],[32023,4],[32619,0],[33144,4],[33742,0],[34267,4],[35959,0],[36511,4],[37108,0],[37657,4],[39325,0],[39877,4],[41570,0],[42122,4],[42718,0],[43270,4],[43842,0],[44368,4],[44963,0],[45489,4],[46086,0],[46636,4],[47207,0],[47756,4],[49426,0],[49978,4],[50574,0],[51102,4],[51697,0],[52246,4],[53914,0],[54466,4],[56159,0],[56712,4],[58404,0],[58956,4],[60649,0],[61201,4]]}";
            var wave = WaveDefinitionFromPico.DeserialiseMessage(json);

            wave.InitialValue.Should().Be(4);
            wave.Values[0][0].Should().Be(0);
            wave.Values[0][1].Should().Be(0);
            wave.Values[1][0].Should().Be(4510);
            wave.Values[1][1].Should().Be(4);
        }

        #region Support Code

        //protected override void SetUpMocks()
        //{
        //    base.SetUpMocks();
        //    _mockSystemWrapper = new Mock<ISystemWrapper>();
        //}

        //protected override void SetUpExpectations()
        //{
        //    base.SetUpExpectations();
        //    _mockSystemWrapper.Setup(m => m.Now).Returns(_initialTime);
        //}

        //protected override void SetUpObjectUnderTest()
        //{
        //    base.SetUpObjectUnderTest();
        //    _db = new DatabaseAccess(_dbConnection, _mockSystemWrapper.Object);
        //    _dbConnection.RunInTransaction(SetUpDatabaseData);
        //    _db.SetOption("Option Name", "Option Value");
        //}

        //protected override void SetUpData()
        //{
        //    base.SetUpData();
        //    _dbConnection = new DBServices().OpenMemoryDatabase();
        //    //_dbConnection = new DBServices().OpenFileConnection("D:\\SQLite\\TestDb.sql");
        //    _now2 = _initialTime;
        //}

        //private void SetUpDatabaseData(IDatabaseTransaction t)
        //{
        //    t.CreateTable<DBOOption>();
        //    t.CreateTable<DBOWavePoint>();
        //    t.CreateTable<DBOLog>();
        //    t.CreateTable<DBOSequence>();
        //    var wavePoints = new List<DBOWavePoint>
        //    {
        //        new DBOWavePoint { Code = "123", Time = 11, Value = 1},
        //        new DBOWavePoint { Code = "456", Time = 111, Value = 1},
        //        new DBOWavePoint { Code = "123", Time = 22, Value = 0},
        //        new DBOWavePoint { Code = "456", Time = 122, Value = 0},
        //        new DBOWavePoint { Code = "123", Time = 0, Value = 0},
        //        new DBOWavePoint { Code = "456", Time = 0, Value = 0}
        //    };
        //    t.InsertRows(wavePoints);
        //}

        //private void CreateSequencesData()
        //{
        //    _db.UpdateSequence("Sequence 1", "First", 1);
        //    _db.UpdateSequence("Sequence 2", "Third", 3);
        //    _db.UpdateSequence("Sequence 1", "Second", 2);
        //    _db.UpdateSequence("Sequence 2", "First", 1);
        //    _db.UpdateSequence("Sequence 1", "Third", 3);
        //    _db.UpdateSequence("Sequence 2", "Second", 2);

        //    _db.DeleteSequence("Sequence 1", "First", 2);
        //    _db.DeleteSequence("Sequence 1", "Second", 2);
        //    _db.DeleteSequence("Sequence 1", "Third", 2);
        //}

        //private void Log(string message)
        //{
        //    _db.Log(message);
        //    _now2 = _now2.AddSeconds(1);
        //    _mockSystemWrapper.Setup(m => m.Now).Returns(_now2);
        //}

        #endregion
    }
}