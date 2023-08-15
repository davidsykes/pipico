using FluentAssertions;
using Logic;
using Logic.Database;
using Logic.Database.DatabaseObjects;
using Logic.Database.DatabaseObjects.IR;
using Logic.DataObjects;
using Moq;
using SQLiteLibrary;
using SystemWrapper;
using TestHelpers;

#nullable disable
namespace Tests.Logic
{
    public class DatabaseAccessTests : TestBase
    {
        IDatabaseAccess _db;

        IDatabaseConnection _dbConnection;
        readonly DateTime _now = new(2020, 3, 15, 1, 2, 3);
        Mock<ISystemWrapper> _mockSystemWrapper;

        #region Options

        [Test]
        public void GetOptionRetrievesTheOption()
        {
            var option = _db.GetOption("Option Name");

            option.Should().Be("Option Value");
        }

        [Test]
        public void TheOptionCanBeUpdated()
        {
            _db.SetOption("Option Name", "New Value");

            _db.GetOption("Option Name").Should().Be("New Value");
        }

        [Test]
        public void ANewOptionCanBeCreated()
        {
            _db.SetOption("New Option", "New Option Value");

            _db.GetOption("New Option").Should().Be("New Option Value");
        }

        [Test]
        public void MissingOptionsDefaultToEmpty()
        {
            var option = _db.GetOption("Missing Option");

            option.Should().Be("");
        }

        #endregion

        #region WavePoints

        [Test]
        public void GetCodesGetsTheIrCodeDefinitions()
        {
            var codes = _db.GetCodes();

            codes.Should().BeEquivalentTo(new List<IRCodeDefinition>
            {
                new IRCodeDefinition
                {
                    Code = "123",
                    Waveform = new List<WavePoint>
                    {
                        new WavePoint { T = 0, V = 0 },
                        new WavePoint { T = 11, V = 1 },
                        new WavePoint { T = 22, V = 0 }
                    }
                },
                new IRCodeDefinition
                {
                    Code = "456",
                    Waveform = new List<WavePoint>
                    {
                        new WavePoint { T = 0, V = 0 },
                        new WavePoint { T = 111, V = 1 },
                        new WavePoint { T = 122, V = 0 }
                    }
                }
            });
        }

        [Test]
        public void SetIrCodeWavePointsSetsTheCodeDefinitionFromJSON()
        {
            var data = "{\"code\": \"3772793023\", \"wavepoints\": [[0, 0], [4526, 1], [4500, 0], [546, 1], [1698, 0]]}";

            var code = _db.SetIrCodeWavePoints(data);

            var codes = _db.GetCodes();
            code.Should().Be("3772793023");
            codes.Count.Should().Be(3);
            codes.Single(m => m.Code == "3772793023")
                .Should().BeEquivalentTo(
                new IRCodeDefinition
                {
                    Code = "3772793023",
                    Waveform = new List<WavePoint>
                    {
                        new WavePoint { T = 0, V = 0 },
                        new WavePoint { T = 4526, V = 1 },
                        new WavePoint { T = 9026, V = 0 },
                        new WavePoint { T = 9572, V = 1 },
                        new WavePoint { T = 11270, V = 0 }
                    }
                }
                );
        }

        [Test]
        public void SetIrCodeWavePointsWithInvalidJSONThrowsAnException()
        {
            var data = "{ 'type': 'code', 'something': 'code' }";

            var action = () => _db.SetIrCodeWavePoints(data);

            action.Should().Throw<IrTransmitterApiException>()
                .WithMessage("Invalid data for SetIrCode");
        }

        [Test]
        public void UpdatingAnExistingCodeRemovesOldData()
        {
            _db.SetIrCodeWavePoints("{\"code\": \"3772793023\", \"wavepoints\": [[0, 0], [4526, 1], [4500, 0], [546, 1], [1698, 0]]}");

            _db.SetIrCodeWavePoints("{\"code\": \"3772793023\", \"wavepoints\": [[0, 0], [4527, 1], [4500, 0], [546, 1], [1698, 0]]}");

            var codes = _db.GetCodes();
            codes.Count.Should().Be(3);
            codes.Single(m => m.Code == "3772793023")
                .Should().BeEquivalentTo(
                new IRCodeDefinition
                {
                    Code = "3772793023",
                    Waveform = new List<WavePoint>
                    {
                        new WavePoint { T = 0, V = 0 },
                        new WavePoint { T = 4527, V = 1 },
                        new WavePoint { T = 9027, V = 0 },
                        new WavePoint { T = 9573, V = 1 },
                        new WavePoint { T = 11271, V = 0 }
                    }
                }
                );
        }

        [Test]
        public void UpdateCodeNameUpdatesTheCodeName()
        {
            _db.SetIrCodeWavePoints("{\"code\": \"3772793023\", \"wavepoints\": [[0, 0], [4526, 1], [4500, 0], [546, 1], [1698, 0]]}");
            _db.SetIrCodeWavePoints("{\"code\": \"3772793024\", \"wavepoints\": [[0, 0], [4526, 1], [4500, 0], [546, 1], [1698, 0]]}");

            _db.UpdateCodeName("3772793023", "Code 1");

            _db.GetCodes().Single(m => m.Code == "Code 1")
                .Should().BeEquivalentTo(
                new IRCodeDefinition
                {
                    Code = "Code 1",
                    Waveform = new List<WavePoint>
                    {
                        new WavePoint { T = 0, V = 0 },
                        new WavePoint { T = 4526, V = 1 },
                        new WavePoint { T = 9026, V = 0 },
                        new WavePoint { T = 9572, V = 1 },
                        new WavePoint { T = 11270, V = 0 }
                    }
                }
                );
        }

        [Test]
        public void DeleteCodeDeletesTheCode()
        {
            _db.DeleteCode("123");

            var codes = _db.GetCodes();

            codes.Should().BeEquivalentTo(new List<IRCodeDefinition>
            {
                new IRCodeDefinition
                {
                    Code = "456",
                    Waveform = new List<WavePoint>
                    {
                        new WavePoint { T = 0, V = 0 },
                        new WavePoint { T = 111, V = 1 },
                        new WavePoint { T = 122, V = 0 }
                    }
                }
            });
        }

        #endregion

        #region Logs

        [Test]
        public void LogLogsTextWithTheCurrentTimeStamp()
        {
            _db.Log("Message");

            var logs = _db.GetLogs();
            logs.Should().BeEquivalentTo(new List<DBOLog>
            {
                new DBOLog
                {
                    Time = _now,
                    Text = "Message",
                }
            });
        }

        [Test]
        public void LogReturnsTheStoredLogObject()
        {
            var log = _db.Log("Message");

            log.Should().BeEquivalentTo(new DBOLog { Time = _now, Text = "Message"});
        }

        [Test]
        public void ClearLogsRemovesAllLogs()
        {
            _db.Log("Message");
            _db.Log("Message");

            _db.ClearLogs();

            _db.GetLogs().Should().BeEmpty();
        }

        #endregion

        #region Sequences

        [Test]
        public void SequencesCanBeAddedDeletedAndFetched()
        {
            CreateSequencesData();

            var sequences = _db.GetSequences();
            sequences.Should().BeEquivalentTo(new IRSequences
            {
                Sequences = new List<IRSequence>
                {
                    new IRSequence
                    {
                        Name = "Sequence 1",
                        Codes = new List<string> { "First", "Third"}
                    },
                    new IRSequence
                    {
                        Name = "Sequence 2",
                        Codes = new List<string> { "First", "Second", "Third"}
                    }
                }
            });
        }

        [Test]
        public void SequencesAreOrderedByPosition()
        {
            CreateSequencesData();

            var sequence2 = _db.GetSequences().Sequences.Single(c => c.Name == "Sequence 2");

            sequence2.Codes[0].Should().Be("First");
            sequence2.Codes[1].Should().Be("Second");
            sequence2.Codes[2].Should().Be("Third");
        }

        #endregion

        #region Support Code

        protected override void SetUpMocks()
        {
            base.SetUpMocks();
            _mockSystemWrapper = new Mock<ISystemWrapper>();
        }

        protected override void SetUpExpectations()
        {
            base.SetUpExpectations();
            _mockSystemWrapper.Setup(m => m.Now).Returns(_now);
        }

        protected override void SetUpObjectUnderTest()
        {
            base.SetUpObjectUnderTest();
            _db = new DatabaseAccess(_dbConnection, _mockSystemWrapper.Object);
            _dbConnection.RunInTransaction(SetUpDatabaseData);
            _db.SetOption("Option Name", "Option Value");
        }

        protected override void SetUpData()
        {
            base.SetUpData();
            _dbConnection = new DBServices().OpenMemoryDatabase();
            //_dbConnection = new DBServices().OpenFileConnection("D:\\SQLite\\TestDb.sql");
        }

        private void SetUpDatabaseData(IDatabaseTransaction t)
        {
            t.CreateTable<DBOOption>();
            t.CreateTable<DBOWavePoint>();
            t.CreateTable<DBOLog>();
            t.CreateTable<DBOSequence>();
            var wavePoints = new List<DBOWavePoint>
            {
                new DBOWavePoint { Code = "123", Time = 11, Value = 1},
                new DBOWavePoint { Code = "456", Time = 111, Value = 1},
                new DBOWavePoint { Code = "123", Time = 22, Value = 0},
                new DBOWavePoint { Code = "456", Time = 122, Value = 0},
                new DBOWavePoint { Code = "123", Time = 0, Value = 0},
                new DBOWavePoint { Code = "456", Time = 0, Value = 0}
            };
            t.InsertRows(wavePoints);
        }

        private void CreateSequencesData()
        {
            _db.UpdateSequence("Sequence 1", "First", 1);
            _db.UpdateSequence("Sequence 2", "Third", 3);
            _db.UpdateSequence("Sequence 1", "Second", 2);
            _db.UpdateSequence("Sequence 2", "First", 1);
            _db.UpdateSequence("Sequence 1", "Third", 3);
            _db.UpdateSequence("Sequence 2", "Second", 2);

            _db.DeleteSequence("Sequence 1", "First", 2);
            _db.DeleteSequence("Sequence 1", "Second", 2);
            _db.DeleteSequence("Sequence 1", "Third", 2);
        }

        #endregion
    }
}