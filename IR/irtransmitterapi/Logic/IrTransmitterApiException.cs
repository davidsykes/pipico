namespace Logic
{
    public class IrTransmitterApiException : Exception
    {
        public IrTransmitterApiException()
        {
        }

        public IrTransmitterApiException(string message)
            : base(message)
        {
        }

        public IrTransmitterApiException(string message, Exception inner)
            : base(message, inner)
        {
        }
    }
}