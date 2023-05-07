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
        Mock<IHexDataConverter> _mockHexDataConverter;
        byte[] _binaryData = Encoding.ASCII.GetBytes("Hello World");

        [Test]
        public void TheMessageRouterPassesTheMessageToARegisteredHandler()
        {
            var message = "{\"Type\": \"type\", \"Data\": \"hex data\"}";

            _router.Route(message);

            _mockMessageHandler.Verify(m => m.ProcessMessage(It.IsAny<byte[]>()));
        }

        [Test]
        public void TheMessageRouteConvertsTheMessageDataToBinary()
        {
            var message = "{\"Type\": \"type\", \"Data\": \"hex data\"}";

            _router.Route(message);

            _mockMessageHandler.Verify(m => m.ProcessMessage(_binaryData));
        }

        [Test]
        public void IfTheHandlerReturnsTrueTheRouterReturnsTrue()
        {
            var message = "{\"Type\": \"type\", \"Data\": \"hex data\"}";
            _mockMessageHandler.Setup(m => m.ProcessMessage(It.IsAny<byte[]>())).Returns(true);

            var result = _router.Route(message);

            result.Should().BeTrue();
        }

        [Test]
        public void IfTheHandlerReturnsFalseTheRouterReturnsFalse()
        {
            var message = "{\"Type\": \"type\", \"Data\": \"hex data\"}";
            _mockMessageHandler.Setup(m => m.ProcessMessage(It.IsAny<byte[]>())).Returns(false);

            var result = _router.Route(message);

            result.Should().BeFalse();
        }

        [Test]
        public void IfTheHandlerIsNotRegisteredAnExceptionIsThrown()
        {
            var message = "{\"Type\": \"unknown\", \"Data\": \"hex data\"}";

            Action action = () => _router.Route(message);

            action.Should().Throw<ScopeWebApiException>()
                .WithMessage("The handler for messages with type 'unknown' was not found.");
        }

        [Test]
        public void IfTheDataIsNotHexAnExceptionIsThrown()
        {
            var message = "{\"Type\": \"type\", \"Data\": \"non hex data\"}";

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
            _mockHexDataConverter = new Mock<IHexDataConverter>();
        }

        protected override void SetUpExpectations()
        {
            base.SetUpExpectations();
            _mockHexDataConverter.Setup(m => m.HexStringToBinary("hex data")).Returns(_binaryData);
        }

        protected override void SetUpObjectUnderTest()
        {
            base.SetUpObjectUnderTest();
            _router = new MessageRouter(_mockHexDataConverter.Object);
            _router.AddHandler("type", _mockMessageHandler.Object);
        }

        //protected override void SetUpData()
        //{
        //    base.SetUpData();
        //    _dbConnection = new DBServices().OpenMemoryDatabase();
        //    //_dbConnection = new DBServices().OpenFileConnection("D:\\SQLite\\TestDb.sql");
        //}

        #endregion
    }
}