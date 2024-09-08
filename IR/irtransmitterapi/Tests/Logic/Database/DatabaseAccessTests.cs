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
        readonly DateTime _initialTime = new(2020, 3, 15, 1, 2, 3);
        DateTime _now2;
        Mock<ISystemWrapper> _mockSystemWrapper;

        #region Codes

        [Test]
        public void GetCodeRetrievesTheCode()
        {
            var code = _db.GetCode("123");

            code.Code.Should().Be("123");
        }

        [Test]
        public void GetNonExistentCodeReturnsNull()
        {
            var code = _db.GetCode("non existent");

            code.Should().BeNull();
        }

        #endregion

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
                        new() { T = 0, V = 0 },
                        new() { T = 11, V = 1 },
                        new() { T = 22, V = 0 }
                    }
                },
                new IRCodeDefinition
                {
                    Code = "456",
                    Waveform = new List<WavePoint>
                    {
                        new() { T = 0, V = 0 },
                        new() { T = 111, V = 1 },
                        new() { T = 122, V = 0 }
                    }
                }
            });
        }

        [Test]
        public void UpdateIrCodeDefinitionTest()
        {
            var testCode = new IRCodeDefinition
            {
                Code = "3772793023",
                Waveform = new List<WavePoint>
                    {
                        new() { T = 0, V = 0 },
                        new() { T = 4526, V = 1 },
                        new() { T = 9026, V = 0 },
                        new() { T = 9572, V = 1 },
                        new() { T = 11270, V = 0 }
                    }
            };

            _db.UpdateIrCodeDefinition(testCode);

            var codes = _db.GetCodes();
            codes.Count.Should().Be(3);
            codes.Single(m => m.Code == "3772793023")
                .Should().BeEquivalentTo(testCode);
        }

        [Test]
        public void UpdatingAnExistingCodeRemovesOldData()
        {
            var testCode1 = new IRCodeDefinition
            {
                Code = "3772793023",
                Waveform = new List<WavePoint>
                    {
                        new() { T = 0, V = 0 },
                        new() { T = 4526, V = 1 },
                        new() { T = 9026, V = 0 },
                        new() { T = 9572, V = 1 },
                        new() { T = 11270, V = 0 }
                    }
            };

            _db.UpdateIrCodeDefinition(testCode1);

            var testCode2 = new IRCodeDefinition
            {
                Code = "3772793023",
                Waveform = new List<WavePoint>
                    {
                        new() { T = 0, V = 0 },
                        new() { T = 4527, V = 1 },
                        new() { T = 9027, V = 0 },
                        new() { T = 9573, V = 1 },
                        new() { T = 11271, V = 0 }
                    }
            };

            _db.UpdateIrCodeDefinition(testCode2);

            var codes = _db.GetCodes();
            codes.Count.Should().Be(3);
            codes.Single(m => m.Code == "3772793023")
                .Should().BeEquivalentTo(
                new IRCodeDefinition
                {
                    Code = "3772793023",
                    Waveform = new List<WavePoint>
                    {
                        new() { T = 0, V = 0 },
                        new() { T = 4527, V = 1 },
                        new() { T = 9027, V = 0 },
                        new() { T = 9573, V = 1 },
                        new() { T = 11271, V = 0 }
                    }
                }
                );
        }

        [Test]
        public void UpdateCodeNameUpdatesTheCodeName()
        {
            var testCode = new IRCodeDefinition
            {
                Code = "3772793023",
                Waveform = new List<WavePoint>
                    {
                        new() { T = 0, V = 0 },
                        new() { T = 4526, V = 1 },
                        new() { T = 9026, V = 0 },
                        new() { T = 9572, V = 1 },
                        new() { T = 11270, V = 0 }
                    }
            };

            _db.UpdateIrCodeDefinition(testCode);

            _db.UpdateCodeName("3772793023", "Code 1");
            testCode.Code = "Code 1";

            var codes = _db.GetCodes();
            
            codes.Single(m => m.Code == "Code 1")
                .Should().BeEquivalentTo(testCode);
        }

        [Test]
        public void DeleteCodeDeletesTheCode()
        {
            _db.DeleteCodeRows("123");

            var codes = _db.GetCodes();

            codes.Should().BeEquivalentTo(new List<IRCodeDefinition>
            {
                new IRCodeDefinition
                {
                    Code = "456",
                    Waveform = new List<WavePoint>
                    {
                        new() { T = 0, V = 0 },
                        new() { T = 111, V = 1 },
                        new() { T = 122, V = 0 }
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

            var logs = _db.GetLogs(1);
            logs.Should().BeEquivalentTo(new List<DBOLog>
            {
                new() {
                    Time = _initialTime,
                    Text = "Message",
                }
            });
        }

        [Test]
        public void LogReturnsTheStoredLogObject()
        {
            var log = _db.Log("Message");

            log.Should().BeEquivalentTo(new DBOLog { Time = _now2, Text = "Message"});
        }

        [Test]
        public void LogsReturnsTheSpecifiedMostRecentNumberOfLogMessages()
        {
            Log("Message1");
            Log("Message2");
            Log("Message3");
            Log("Message4");
            Log("Message5");

            var logs = _db.GetLogs(3);

            logs.Should().BeEquivalentTo(new List<DBOLog>
            {
                new() {
                    Time = _initialTime.AddSeconds(2),
                    Text = "Message3",
                },
                new() {
                    Time = _initialTime.AddSeconds(3),
                    Text = "Message4",
                },
                new() {
                    Time = _initialTime.AddSeconds(4),
                    Text = "Message5",
                },
            }, o => o.WithStrictOrdering());
        }

        [Test]
        public void IfMoreLogsAreRequestedThanHaveBeenLoggedThenAllLogsAreReturned()
        {
            Log("Message1");
            Log("Message2");
            Log("Message3");
            Log("Message4");

            var logs = _db.GetLogs(4000);

            logs.Should().BeEquivalentTo(new List<DBOLog>
            {
                new() {
                    Time = _initialTime,
                    Text = "Message1",
                },
                new() {
                    Time = _initialTime.AddSeconds(1),
                    Text = "Message2",
                },
                new() {
                    Time = _initialTime.AddSeconds(2),
                    Text = "Message3",
                },
                new() {
                    Time = _initialTime.AddSeconds(3),
                    Text = "Message4",
                },
            });
        }

        [Test]
        public void ClearLogsRemovesAllLogs()
        {
            _db.Log("Message");
            _db.Log("Message");

            _db.ClearLogs();

            _db.GetLogs(2).Should().BeEmpty();
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
            _mockSystemWrapper.Setup(m => m.Now).Returns(_initialTime);
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
            _now2 = _initialTime;
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

        private void Log(string message)
        {
            _db.Log(message);
            _now2 = _now2.AddSeconds(1);
            _mockSystemWrapper.Setup(m => m.Now).Returns(_now2);
        }

        #endregion
    }
}