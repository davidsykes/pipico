using Logic.DataObjects;

namespace Logic.Trace
{
    public interface IScopeTraceDirectory
    {
        IList<TraceDefinition> GetTraceDetails();
    }
}
