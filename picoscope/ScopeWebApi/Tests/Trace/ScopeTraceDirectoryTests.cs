using FluentAssertions;
using Logic.DataObjects;
using Logic.Logic;
using Logic.Trace;
using Moq;
using System.Text.Json;
using TestHelpers;

#nullable disable
namespace Tests.TraceDirectory
{
    public class ScopeTraceDirectoryTests : TestBase
    {
        IScopeTraceDirectory _dir;

        Mock<ISystemWrapper> _mockSystemWrapper;
        IList<ScopeTraceDetails> _traceDetails;

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
        public void GetTraceDataWithDetailsGetsTraceDataWithDetails()
        {
            var scopeDataWithDetails = MakeScopeTraceDataWithDetails();

            _mockSystemWrapper.Setup(m => m.FileReadAllText("trace path\\Trace 2.trc"))
                .Returns(JsonSerializer.Serialize(scopeDataWithDetails.RawScopeTraceData));

            var trace_data = _dir.GetScopeTraceDataWithDetails("Trace 2.trc");

            trace_data.Should().BeEquivalentTo(scopeDataWithDetails);
        }

        [Test]
        public void GetTraceDataThrowsExceptionIfNoTraceExists()
        {
            Action action = () => _dir.GetScopeTraceDataWithDetails("non existent trace file name");

            action.Should().Throw<ScopeWebApiException>()
                .WithMessage("Scope trace 'non existent trace file name' could not be found.");
        }

        [Test]
        public void GetCurrentTraceDataGetsTheMostRecentTraceData()
        {
            var scopeDataWithDetails = MakeScopeTraceDataWithDetails();

            var trace_data = _dir.GetCurrentTraceData();

            trace_data.Should().BeEquivalentTo(scopeDataWithDetails);
        }

        [Test]
        public void GetCurrentTraceDataReturnsEmptyListIfThereIsNoTrace()
        {
            _mockSystemWrapper.Setup(m => m.EnumerateFiles("trace path"))
                .Returns(new List<string>());

            var trace_data = _dir.GetCurrentTraceData();

            trace_data.ScopeTraceDetails.tracecount.Should().Be(0);
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
            _traceDetails = new List<ScopeTraceDetails>
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
            _mockSystemWrapper.Setup(m => m.FileReadAllText($"C:\\trace path\\{name}.trc"))
                .Returns(MakeSerialisedRawTraceDataFromDetails(_traceDetails.Single(m => m.tracename == name)));
            _mockSystemWrapper.Setup(m => m.FileExists($"trace path\\{name}.trc")).Returns(true);
        }

        private static string MakeSerialisedRawTraceDataFromDetails(ScopeTraceDetails traceDetails)
        {
            return JsonSerializer.Serialize(MakeRawTraceDataFromDetails(traceDetails));
        }

        private static RawScopeTraceData MakeRawTraceDataFromDetails(ScopeTraceDetails traceDetails)
        {
            var scopeData = new RawScopeTraceData();
            for (int i = 0; i < traceDetails.tracecount; i++)
            {
                scopeData.Values.Add(new List<int> { i, i });
            }
            scopeData.Values.Last()[0] = traceDetails.tracelength;
            return scopeData;
        }

        private ScopeTraceDataWithDetails MakeScopeTraceDataWithDetails()
        {
            ScopeTraceDetails traceDetails = new ScopeTraceDetails
            {
                tracename = "Trace 2",
                tracepath = "Trace 2.trc",
                tracecount = 6,
                tracelength = 16
            };
            var rawData = MakeRawTraceDataFromDetails(traceDetails);
            return new ScopeTraceDataWithDetails
            {
                ScopeTraceDetails = traceDetails,
                RawScopeTraceData = rawData
            };
        }

        private IEnumerable<string> MakeTracePaths()
        {
            return _traceDetails.Select(m => $"C:\\trace path\\{m.tracename}.trc");
        }

        #endregion
    }
}