using Logic.Logic;
using System.Text.Json;

namespace Logic.Messaging
{
    public class MessageRouter : IMessageRouter
    {
        private readonly IDictionary<string, IMessageHandler> _handlers = new Dictionary<string, IMessageHandler>();

        public void AddHandler(string type, IMessageHandler handler)
        {
            _handlers[type] = handler;
        }

        public bool Route(string jsonString)
        {
            var messageObject = DeserialiseMessage(jsonString);

            if (_handlers.ContainsKey(messageObject.type))
            {
                var data = ConvertHexData(messageObject.data);

                return _handlers.First().Value.ProcessMessage(data);
            }

            throw new ScopeWebApiException($"The handler for messages with type '{messageObject.type}' was not found.");
        }

        private static Message DeserialiseMessage(string jsonString)
        {
            try
            {
                var message = JsonSerializer.Deserialize<Message>(jsonString);

                if (message != null)
                    return message;
            }
            catch (JsonException)
            {
            }
            throw new ScopeWebApiException("The message has not been recognised.");
        }

        private static byte[] ConvertHexData(string hexData)
        {
            try
            {
                var data = Convert.FromHexString(hexData);
                return data;
            }
            catch (FormatException)
            {
                throw new ScopeWebApiException("The message data could not be converted.");
            }
        }
    }
}
