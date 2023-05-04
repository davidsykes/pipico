namespace Logic
{
    public class MessageLogger : IMessageLogger
    {
        private readonly ProgramParameters _programParameters;

        public MessageLogger(ProgramParameters programParameters)
        {
            _programParameters = programParameters;
        }

        public string LogMessage(string jsonstring)
        {
            throw new NotImplementedException();
        }
    }
}
