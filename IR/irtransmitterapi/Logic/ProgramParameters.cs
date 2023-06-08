using ApplicationParameters;

namespace Logic
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
                    Name = "DatabasePath",
                    Type = ApplicationParameterType.RequiredParameter,
                    UsageMessage = "The path to the database"
                },
                new ApplicationParameterDefinition
                {
                    Name = "LogFilePath",
                    Type = ApplicationParameterType.RequiredParameter,
                    UsageMessage = "The path to the application log file"
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
