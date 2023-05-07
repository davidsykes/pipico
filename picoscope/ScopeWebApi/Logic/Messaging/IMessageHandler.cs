namespace Logic.Messaging
{
    public interface IMessageHandler
    {
        bool ProcessMessage(byte[] bytes);
    }
}
