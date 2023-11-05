using Logic.DataObjects;

namespace Logic.Trace
{
    public interface IScopeTraceDirectory
    {
        IEnumerable<TraceDetails> GetTraceDetails();
        void DeleteTrace(string path);
        IList<TraceDataPoint> GetTraceData(string traceFileName);
        IList<TraceDataPoint> GetCurrentTraceData();
    }
}
