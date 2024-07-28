using Logic.DataObjects;

namespace Logic.Trace
{
    public interface IScopeTraceDirectory
    {
        IEnumerable<ScopeTraceDetails> GetTraceDetails();
        void DeleteTrace(string path);
        ScopeTraceDataWithDetails GetScopeTraceDataWithDetails(string traceFileName);
        ScopeTraceDataWithDetails GetCurrentTraceData();
    }
}
