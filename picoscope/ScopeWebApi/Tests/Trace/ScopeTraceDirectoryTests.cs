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
                    TraceName = "Trace 1",
                    TraceCount = 101,
                    TraceLength = 102
                },
                new TraceDefinition
                {
                    TraceName = "Trace 2",
                    TraceCount = 201,
                    TraceLength = 202
                },
                new TraceDefinition
                {
                    TraceName = "Trace 3",
                    TraceCount = 301,
                    TraceLength = 302
                }
            };
        }

        protected override void SetUpExpectations()
        {
            base.SetUpExpectations();

            _mockSystemWrapper.Setup(m => m.EnumerateFiles("trace path"))
                .Returns(_traceData.Select(m => m.TraceName));
            _mockSystemWrapper.Setup(m => m.ReadBytes("trace path\\Trace 1", 12))
                .Returns(MakeBytes(_traceData.Single(m => m.TraceName == "Trace 1")));
            _mockSystemWrapper.Setup(m => m.ReadBytes("trace path\\Trace 2", 12))
                .Returns(MakeBytes(_traceData.Single(m => m.TraceName == "Trace 2")));
            _mockSystemWrapper.Setup(m => m.ReadBytes("trace path\\Trace 3", 12))
                .Returns(MakeBytes(_traceData.Single(m => m.TraceName == "Trace 3")));
        }

        private static byte[] MakeBytes(TraceDefinition traceDefinition)
        {
            return Add(BitConverter.GetBytes(0x12345678),
                Add(
                    BitConverter.GetBytes(traceDefinition.TraceCount),
                    BitConverter.GetBytes(traceDefinition.TraceLength)));
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