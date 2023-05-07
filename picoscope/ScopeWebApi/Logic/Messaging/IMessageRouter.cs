namespace Logic.Messaging
{
    public interface IMessageRouter
    {
        void AddHandler(string type, IMessageHandler handler);
        bool Route(string message);
    }
}
