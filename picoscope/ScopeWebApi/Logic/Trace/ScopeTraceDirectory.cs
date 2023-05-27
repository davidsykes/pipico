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

        public IList<TraceDefinition> GetTraceDetails()
        {
            var details = new List<TraceDefinition>();
            var files = _systemWrapper.EnumerateFiles(_tracePath);

            foreach (var file in files)
            {
                details.Add(GetTraceDefinition(file));
            }

            return details;
        }

        private TraceDefinition GetTraceDefinition(string tracePath)
        {
            var traceName = Path.GetFileNameWithoutExtension(tracePath);
            var traceFileName = Path.GetFileName(tracePath);

            var header = _systemWrapper.ReadBytes(tracePath, 12);
            using var r = new BinaryReader(new MemoryStream(header));
            var h = r.ReadInt32();
            var count = r.ReadInt32();
            var us = r.ReadInt32();

            return new TraceDefinition
            {
                tracename = traceName,
                tracepath = traceFileName,
                tracecount = count,
                tracelength = us
            };
        }

        public void DeleteTrace(string path)
        {
            _systemWrapper.DeleteFile(Path.Combine(_tracePath, path));
        }
    }
}
