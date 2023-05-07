using Logic.Logic;
using System.Text.Json;

namespace Logic.Messaging
{
    public class MessageRouter : IMessageRouter
    {
        readonly IHexDataConverter _hexDataConverter;

        private IDictionary<string, IMessageHandler> _handlers = new Dictionary<string, IMessageHandler>();

        public void AddHandler(string type, IMessageHandler handler)
        {
            _handlers[type] = handler;
        }

        public MessageRouter(IHexDataConverter hexDataConverter)
        {
            _hexDataConverter = hexDataConverter;
        }

        public bool Route(string jsonstring)
        {
            var messageObject = DeserialiseMessage(jsonstring);

            if (_handlers.ContainsKey(messageObject.Type))
            {
                var data = _hexDataConverter.HexStringToBinary(messageObject.Data);

                if (data.Length > 0)
                {
                    return _handlers.First().Value.ProcessMessage(data);
                }
                throw new ScopeWebApiException("The message data could not be converted.");
            }

            throw new ScopeWebApiException($"The handler for messages with type '{messageObject.Type}' was not found.");
        }

        private static Message DeserialiseMessage(string jsonstring)
        {
            try
            {
                var message = JsonSerializer.Deserialize<Message>(jsonstring);

                if (message != null)
                    return message;
            }
            catch (JsonException)
            {
            }
            throw new ScopeWebApiException("The message has not been recognised.");
        }
    }
}
