using FluentAssertions;
using Logic;
using Logic.Codes;
using Logic.Database;
using Logic.DataObjects;
using Moq;
using TestHelpers;

#nullable disable
namespace Tests.Logic.Codes
{
    public class CodeNameChangerTests : TestBase
    {
        ICodeNameChanger _changer;

        Mock<IDatabaseAccess> _mockDatabaseAccess;

        [Test]
        public void UpdateCodeNameUpdatesTheCodeName()
        {
            _changer.UpdateCodeName("CurrentName", "NewName");

            _mockDatabaseAccess.Verify(m => m.UpdateCodeName("CurrentName", "NewName"));
        }

        [Test]
        public void IfTheCodeDoesNotExistAnExceptionIsThrown()
        {
            Action action = () => _changer.UpdateCodeName("MissingName", "NewName");

            action.Should().Throw<IrTransmitterApiException>()
                .WithMessage("Code 'MissingName' not found.");
        }

        [Test]
        public void NonAlphanumericCharactersAreRemovedFromTheName()
        {
            _changer.UpdateCodeName("CurrentName", "New Name!!!!");

            _mockDatabaseAccess.Verify(m => m.UpdateCodeName("CurrentName", "NewName"));
        }

        [Test]
        public void IfTheNewNameIsEmptyAnExceptionIsThrown()
        {
            Action action = () => _changer.UpdateCodeName("CurrentName", "");

            action.Should().Throw<IrTransmitterApiException>()
                .WithMessage("New code name is empty.");
        }

        [Test]
        public void IfTheNewNameIsNotValidAnExceptionIsThrown()
        {
            Action action = () => _changer.UpdateCodeName("CurrentName", "!!  *^");

            action.Should().Throw<IrTransmitterApiException>()
                .WithMessage("New code name is empty.");
        }

        #region Support Code

        protected override void SetUpMocks()
        {
            base.SetUpMocks();
            _mockDatabaseAccess = new Mock<IDatabaseAccess>();
        }

        protected override void SetUpExpectations()
        {
            base.SetUpExpectations();

            _mockDatabaseAccess.Setup(m => m.GetCodes())
                .Returns(new List<IRCodeDefinition>
                {
                    new IRCodeDefinition
                    {
                        Code = "CurrentName",
                        Waveform = new List<WavePoint>()
                    }
                });
        }

        protected override void SetUpObjectUnderTest()
        {
            base.SetUpObjectUnderTest();
            _changer = new CodeNameChanger(_mockDatabaseAccess.Object);
        }

        #endregion
    }
}