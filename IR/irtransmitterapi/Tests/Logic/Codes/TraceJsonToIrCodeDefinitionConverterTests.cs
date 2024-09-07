using FluentAssertions;
using Logic.Codes;
using TestHelpers;

#nullable disable
namespace Tests.Logic.Codes
{
    internal class TraceJsonToIrCodeDefinitionConverterTests : TestBase
    {

        [Test]
        public void ASimpleCodeCanBeConverted()
        {
            var code = TraceJsonToIrCodeDefinitionConverter.Convert("{\"InitialValue\":2,\"Values\":[[1,2],[3,4]]}");

            code.Code.Should().Be("New Code");
            code.Waveform[0].T.Should().Be(1);
            code.Waveform[0].V.Should().Be(2);
            code.Waveform[1].T.Should().Be(3);
            code.Waveform[1].V.Should().Be(4);
        }
    }
}