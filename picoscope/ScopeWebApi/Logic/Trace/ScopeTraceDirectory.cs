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

        public IEnumerable<TraceDetails> GetTraceDetails()
        {
            var details = new List<TraceDetails>();
            var files = _systemWrapper.EnumerateFiles(_tracePath);

            foreach (var file in files)
            {
                details.Add(GetTraceDefinition(file));
            }

            return details.OrderBy(m => m.tracename);
        }

        private TraceDetails GetTraceDefinition(string tracePath)
        {
            var header = _systemWrapper.ReadBytes(tracePath, 12);
            using var r = new BinaryReader(new MemoryStream(header));
            var h = r.ReadInt32();
            var count = r.ReadInt32();
            var us = r.ReadInt32();

            return new TraceDetails
            {
                tracename = Path.GetFileNameWithoutExtension(tracePath),
                tracepath = Path.GetFileName(tracePath),
                tracecount = count,
                tracelength = us
            };
        }

        public void DeleteTrace(string path)
        {
            _systemWrapper.DeleteFile(Path.Combine(_tracePath, path));
        }

        public IList<TraceDataPoint> GetTraceData(string traceFileName)
        {
            var filePath = Path.Combine(_tracePath, traceFileName);
            if (!_systemWrapper.FileExists(filePath)) { RaiseNonExistentFileException(traceFileName); 
            }
            var binary_data = _systemWrapper.FileReadAllBytes(filePath);
            using var r = new BinaryReader(new MemoryStream(binary_data));

            var header = r.ReadInt32();
            var sample_count = r.ReadInt32();
            var total_time = r.ReadInt32();
            var points = new List<TraceDataPoint>();
            for (int i = 0; i < sample_count; i++)
            {
                points.Add(new TraceDataPoint
                {
                    time = r.ReadInt32(),
                    value = r.ReadByte()
                });
            }
            return points;
        }

        private static void RaiseNonExistentFileException(string traceFileName)
        {
            throw new ScopeWebApiException($"Scope trace '{traceFileName}' could not be found.");
        }

        public IList<TraceDataPoint> GetCurrentTraceData()
        {
            var traceDetails = GetTraceDetails().ToList();
            if (traceDetails.Count > 0)
            {
                var latestTracePath = traceDetails.Last().tracepath;
                return GetTraceData(latestTracePath);
            }

            return new List<TraceDataPoint>();
        }
    }
}
