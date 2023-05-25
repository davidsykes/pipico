using ApplicationParameters;

namespace ScopeWebApi
{
    public class ProgramParameters
    {
        readonly IApplicationParametersManager _programParameters;

        public ProgramParameters()
        {
            var definitions = new List<ApplicationParameterDefinition>
            {
                new ApplicationParameterDefinition
                {
                    Name = "TraceFilesPath",
                    Type = ApplicationParameterType.RequiredParameter,
                    UsageMessage = "The path to write the trace files"
                }
            };

            _programParameters = ApplicationParametersFactory.CreateApplicationParameters(
                "How to use the application",
                definitions
                );
        }

        public string GetParameter(string name)
        {
            return _programParameters.GetRequiredParameter<string>(name);
        }
    }
}
