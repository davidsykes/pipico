using Logic.DataObjects;
using Logic.Logic;

namespace Logic.Trace
{
    public class ScopeTraceDirectory : IScopeTraceDirectory
    {
        private readonly string _tracePath;
        private readonly ISystemWrapper _systemWrapper;

        public ScopeTraceDirectory(string tracePath, ISystemWrapper systemWrapper)
        {
            _tracePath = tracePath;
            _systemWrapper = systemWrapper;
        }

        public IEnumerable<ScopeTraceDetails> GetTraceDetails()
        {
            var details = new List<ScopeTraceDetails>();
            var files = _systemWrapper.EnumerateFiles(_tracePath);

            foreach (var file in files)
            {
                details.Add(GetTraceDefinition(file));
            }

            return details.OrderBy(m => m.tracename);
        }

        private ScopeTraceDetails GetTraceDefinition(string tracePath)
        {
            var scopeData = GetRawScopeTraceData(tracePath);

            return GetScopeTraceDetailsFromRawScopeTraceData(tracePath, scopeData);
        }

        private RawScopeTraceData GetRawScopeTraceData(string tracePath)
        {
            var filePath = Path.Combine(_tracePath, tracePath);
            var json = _systemWrapper.FileReadAllText(filePath);
            if (json == null)
            {
                RaiseNonExistentFileException(tracePath);
            }
            return RawScopeTraceData.DeserialiseMessage(json!);
        }

        private static ScopeTraceDetails GetScopeTraceDetailsFromRawScopeTraceData(string tracePath, RawScopeTraceData rawScopeTraceData)
        {
            return new ScopeTraceDetails
            {
                tracepath = Path.GetFileName(tracePath),
                tracename = Path.GetFileNameWithoutExtension(tracePath),
                tracecount = rawScopeTraceData.Values.Count,
                tracelength = rawScopeTraceData.Values.Last()[0]
            };
        }

        public void DeleteTrace(string path)
        {
            _systemWrapper.DeleteFile(Path.Combine(_tracePath, path));
        }

        public ScopeTraceDataWithDetails GetScopeTraceDataWithDetails(string tracePath)
        {
            var scopeData = GetRawScopeTraceData(tracePath);
            var traceDetails = GetScopeTraceDetailsFromRawScopeTraceData(tracePath, scopeData);
            return new ScopeTraceDataWithDetails
            {
                RawScopeTraceData = scopeData,
                ScopeTraceDetails = traceDetails
            };
        }

        private static void RaiseNonExistentFileException(string traceFileName)
        {
            throw new ScopeWebApiException($"Scope trace '{traceFileName}' could not be found.");
        }

        public ScopeTraceDataWithDetails GetCurrentTraceData()
        {
            return new ScopeTraceDataWithDetails();
        }
    }
}
