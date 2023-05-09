using FluentAssertions;
using Logic.Logic;
using Logic.Messaging;
using Moq;
using System.Text;
using TestHelpers;

#nullable disable
namespace Tests.Messaging
{
    public class MessageRouterTests : TestBase
    {
        IMessageRouter _router;

        Mock<IMessageHandler> _mockMessageHandler;
        readonly byte[] _binaryData = Encoding.ASCII.GetBytes("Hello World");

        [Test]
        public void TheMessageRouterPassesTheMessageToARegisteredHandler()
        {
            var message = "{\"type\": \"type\", \"data\": \"48656c6c6f20576f726c64\"}";

            _router.Route(message);

            _mockMessageHandler.Verify(m => m.ProcessMessage(It.IsAny<byte[]>()));
        }

        [Test]
        public void TheMessageRouteConvertsTheMessageDataToBinary()
        {
            var message = "{\"type\": \"type\", \"data\": \"48656c6c6f20576f726c64\"}";

            _router.Route(message);

            _mockMessageHandler.Verify(m => m.ProcessMessage(_binaryData));
        }

        [Test]
        public void IfTheHandlerReturnsTrueTheRouterReturnsTrue()
        {
            var message = "{\"type\": \"type\", \"data\": \"48656c6c6f20576f726c64\"}";
            _mockMessageHandler.Setup(m => m.ProcessMessage(It.IsAny<byte[]>())).Returns(true);

            var result = _router.Route(message);

            result.Should().BeTrue();
        }

        [Test]
        public void IfTheHandlerReturnsFalseTheRouterReturnsFalse()
        {
            var message = "{\"type\": \"type\", \"data\": \"48656c6c6f20576f726c64\"}";
            _mockMessageHandler.Setup(m => m.ProcessMessage(It.IsAny<byte[]>())).Returns(false);

            var result = _router.Route(message);

            result.Should().BeFalse();
        }

        [Test]
        public void IfTheHandlerIsNotRegisteredAnExceptionIsThrown()
        {
            var message = "{\"type\": \"unknown\", \"data\": \"48656c6c6f20576f726c64\"}";

            Action action = () => _router.Route(message);

            action.Should().Throw<ScopeWebApiException>()
                .WithMessage("The handler for messages with type 'unknown' was not found.");
        }

        [Test]
        public void IfTheDataIsNotHexAnExceptionIsThrown()
        {
            var message = "{\"type\": \"type\", \"data\": \"non hex data\"}";

            Action action = () => _router.Route(message);

            action.Should().Throw<ScopeWebApiException>()
                .WithMessage("The message data could not be converted.");
        }

        [Test]
        public void IfTheMessageIsNotRecognisedAnExceptionIsThrown()
        {
            var message = "Alien message";

            Action action = () => _router.Route(message);

            action.Should().Throw<ScopeWebApiException>()
                .WithMessage("The message has not been recognised.");
        }

        [Test]
        public void IfTheMessageIsEmptyAnExceptionIsThrown()
        {
            var message = "";

            Action action = () => _router.Route(message);

            action.Should().Throw<ScopeWebApiException>()
                .WithMessage("The message has not been recognised.");
        }

        #region Support Code

        protected override void SetUpMocks()
        {
            base.SetUpMocks();
            _mockMessageHandler = new Mock<IMessageHandler>();
        }

        protected override void SetUpObjectUnderTest()
        {
            base.SetUpObjectUnderTest();
            _router = new MessageRouter();
            _router.AddHandler("type", _mockMessageHandler.Object);
        }

        #endregion
    }
}