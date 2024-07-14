using FluentAssertions;
using Logic.DataObjects;
using Logic.Logic;
using Logic.Trace;
using Moq;
using TestHelpers;

#nullable disable
namespace Tests.Messaging
{
    public class ScopeTraceDirectoryTests : TestBase
    {
        IScopeTraceDirectory _dir;

        Mock<ISystemWrapper> _mockSystemWrapper;
        IList<TraceDetails> _traceDetails;
        IList<TraceDataPoint> _exampleTraceData;

        [Test]
        public void GetTraceDetailsReturnsTraceNamesAndDetailsSortedByName()
        {
            var traces = _dir.GetTraceDetails();

            traces.Should().BeEquivalentTo(_traceDetails.OrderBy(m => m.tracename),
                options => options.WithStrictOrdering());
        }

        [Test]
        public void GetTraceDetailsReturnsAnEmptyListWhenNoTracesExist()
        {
            _mockSystemWrapper.Setup(m => m.EnumerateFiles("trace path"))
                .Returns(new List<string>());

            var traces = _dir.GetTraceDetails();

            traces.ToList().Should().BeEmpty();
        }

        [Test]
        public void DeleteTraceDeletesTheTrace()
        {
            _dir.DeleteTrace("trace file name");

            _mockSystemWrapper.Verify(m => m.DeleteFile("trace path\\trace file name"));
        }

        [Test]
        public void DeleteNonExistentTraceTraceTriesToDeletesTheTrace()
        {
            _dir.DeleteTrace("non existent trace file name");

            _mockSystemWrapper.Verify(m => m.DeleteFile("trace path\\non existent trace file name"));
        }

        [Test]
        public void GetTraceDataGetsTraceData()
        {
            _mockSystemWrapper.Setup(m => m.FileReadAllBytes("trace path\\Trace 2.trc"))
                .Returns(MakeTraceDataFile());

            var trace_data = _dir.GetTraceData("Trace 2.trc");

            trace_data.Should().BeEquivalentTo(_exampleTraceData);
        }

        [Test]
        public void GetTraceDataThrowsExceptionIfNoTraceExists()
        {
            Action action = () => _dir.GetTraceData("non existent trace file name");

            action.Should().Throw<ScopeWebApiException>()
                .WithMessage("Scope trace 'non existent trace file name' could not be found.");
        }

        [Test]
        public void GetCurrentTraceDataGetsTheMostRecentTraceData()
        {
            _mockSystemWrapper.Setup(m => m.FileReadAllBytes("trace path\\Trace 3.trc"))
                .Returns(MakeTraceDataFile());

            var trace_data = _dir.GetCurrentTraceData();

            trace_data.Should().BeEquivalentTo(_exampleTraceData);
        }

        [Test]
        public void GetCurrentTraceDataReturnsEmptyListIfThereIsNoTrace()
        {
            _mockSystemWrapper.Setup(m => m.EnumerateFiles("trace path"))
                .Returns(new List<string>());

            var trace_data = _dir.GetCurrentTraceData();

            trace_data.Should().BeEmpty();
        }

        #region Support Code

        protected override void SetUpMocks()
        {
            base.SetUpMocks();
            _mockSystemWrapper = new Mock<ISystemWrapper>();
        }

        protected override void SetUpObjectUnderTest()
        {
            base.SetUpObjectUnderTest();
            _dir = new ScopeTraceDirectory("trace path", _mockSystemWrapper.Object);
        }

        protected override void SetUpData()
        {
            base.SetUpData();
            _traceDetails = new List<TraceDetails>
            {
                new() {
                    tracename = "Trace 1",
                    tracepath = "Trace 1.trc",
                    tracecount = 101,
                    tracelength = 102
                },
                new() {
                    tracename = "Trace 3",
                    tracepath = "Trace 3.trc",
                    tracecount = 301,
                    tracelength = 302
                },
                new() {
                    tracename = "Trace 2",
                    tracepath = "Trace 2.trc",
                    tracecount = 201,
                    tracelength = 202
                },
            };

            _exampleTraceData = new List<TraceDataPoint>
            {
                new()
                {
                    time = 101,
                    value = 11
                },
                new()
                {
                    time = 202,
                    value = 22
                },
                new()
                {
                    time = 303,
                    value = 33
                }
            };
        }

        protected override void SetUpExpectations()
        {
            base.SetUpExpectations();

            _mockSystemWrapper.Setup(m => m.EnumerateFiles("trace path"))
                .Returns(MakeTracePaths());
            _mockSystemWrapper.Setup(m => m.FileExists(It.IsAny<string>())).Returns(false);
            SetUpMockFile("Trace 1");
            SetUpMockFile("Trace 2");
            SetUpMockFile("Trace 3");
        }

        private void SetUpMockFile(string name)
        {
            _mockSystemWrapper.Setup(m => m.ReadBytes($"C:\\trace path\\{name}.trc", 12))
                .Returns(MakeBytes(_traceDetails.Single(m => m.tracename == name)));
            _mockSystemWrapper.Setup(m => m.FileExists($"trace path\\{name}.trc")).Returns(true);
        }

        private IEnumerable<string> MakeTracePaths()
        {
            return _traceDetails.Select(m => $"C:\\trace path\\{m.tracename}.trc");
        }

        private static byte[] MakeBytes(TraceDetails traceDefinition)
        {
            return AddTwoByteArrays(BitConverter.GetBytes(0x12345678),
                AddTwoByteArrays(
                    BitConverter.GetBytes(traceDefinition.tracecount),
                    BitConverter.GetBytes(traceDefinition.tracelength)));
        }

        private static byte[] AddTwoByteArrays(byte[] bytes1, byte[] bytes2)
        {
            var newArray = new byte[bytes1.Length + bytes2.Length];
            bytes1.CopyTo(newArray, 0);
            bytes2.CopyTo(newArray, bytes1.Length);
            return newArray;
        }

        private byte[] MakeTraceDataFile()
        {
            using MemoryStream stream = new();
            using (BinaryWriter writer = new(stream))
            {
                writer.Write(0x12345678);
                writer.Write(3);
                writer.Write(3);
                foreach (var s in _exampleTraceData)
                {
                    writer.Write(s.time);
                    writer.Write(s.value);
                }
            }
            stream.Flush();
            byte[] bytes = stream.GetBuffer();
            return bytes;
        }

        #endregion
    }
}