using Logic.DataObjects;

namespace Logic.Trace
{
    public interface IScopeTraceDirectory
    {
        IList<TraceDetails> GetTraceDetails();
        void DeleteTrace(string path);
        IList<TraceDataPoint> GetTraceData(string traceFileName);
    }
}
