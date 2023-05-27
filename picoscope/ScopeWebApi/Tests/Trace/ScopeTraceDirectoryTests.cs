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
        IList<TraceDefinition> _traceData;

        [Test]
        public void GetTraceDetailsReturnsTraceNamesAndDetails()
        {
            var traces = _dir.GetTraceDetails();

            traces.Should().BeEquivalentTo(_traceData);
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
            _traceData = new List<TraceDefinition>
            {
                new TraceDefinition
                {
                    tracename = "Trace 1",
                    tracepath = "Trace 1.trc",
                    tracecount = 101,
                    tracelength = 102
                },
                new TraceDefinition
                {
                    tracename = "Trace 2",
                    tracepath = "Trace 2.trc",
                    tracecount = 201,
                    tracelength = 202
                },
                new TraceDefinition
                {
                    tracename = "Trace 3",
                    tracepath = "Trace 3.trc",
                    tracecount = 301,
                    tracelength = 302
                }
            };
        }

        protected override void SetUpExpectations()
        {
            base.SetUpExpectations();

            _mockSystemWrapper.Setup(m => m.EnumerateFiles("trace path"))
                .Returns(MakeTracePaths());
            _mockSystemWrapper.Setup(m => m.ReadBytes("C:\\trace path\\Trace 1.trc", 12))
                .Returns(MakeBytes(_traceData.Single(m => m.tracename == "Trace 1")));
            _mockSystemWrapper.Setup(m => m.ReadBytes("C:\\trace path\\Trace 2.trc", 12))
                .Returns(MakeBytes(_traceData.Single(m => m.tracename == "Trace 2")));
            _mockSystemWrapper.Setup(m => m.ReadBytes("C:\\trace path\\Trace 3.trc", 12))
                .Returns(MakeBytes(_traceData.Single(m => m.tracename == "Trace 3")));
        }

        private IEnumerable<string> MakeTracePaths()
        {
            return _traceData.Select(m => $"C:\\trace path\\{m.tracename}.trc");
        }

        private static byte[] MakeBytes(TraceDefinition traceDefinition)
        {
            return Add(BitConverter.GetBytes(0x12345678),
                Add(
                    BitConverter.GetBytes(traceDefinition.tracecount),
                    BitConverter.GetBytes(traceDefinition.tracelength)));
        }

        private static byte[] Add(byte[] bytes1, byte[] bytes2)
        {
            var newArray = new byte[bytes1.Length + bytes2.Length];
            bytes1.CopyTo(newArray, 0);
            bytes2.CopyTo(newArray, bytes1.Length);
            return newArray;
        }

        #endregion
    }
}