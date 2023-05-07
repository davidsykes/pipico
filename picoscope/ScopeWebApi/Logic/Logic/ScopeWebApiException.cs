namespace Logic.Logic
{
    public class ScopeWebApiException : Exception
    {
        public ScopeWebApiException()
        {
        }

        public ScopeWebApiException(string message)
            : base(message)
        {
        }

        public ScopeWebApiException(string message, Exception inner)
            : base(message, inner)
        {
        }
    }
}
