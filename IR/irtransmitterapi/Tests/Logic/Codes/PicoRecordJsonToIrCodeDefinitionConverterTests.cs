using FluentAssertions;
using Logic.Codes;
using TestHelpers;

#nullable disable
namespace Tests.Logic.Codes
{
    internal class PicoRecordJsonToIrCodeDefinitionConverterTests : TestBase
    {
        [Test]
        public void ASimpleCodeCanBeConverted()
        {
            string json = "{\"InitialValue\":4,\"Values\":[[0,0],[4510,4],[9027,0],[9579,4],[11271,0],[11822,4],[13515,0],[14068,4],[15760,0],[16314,4],[16908,0],[17434,4],[18031,0],[18556,4],[19154,0],[19679,4],[20274,0],[20801,4],[21398,0],[21948,4],[23616,0],[24167,4],[25860,0],[26414,4],[28104,0],[28657,4],[29252,0],[29779,4],[30375,0],[30925,4],[31497,0],[32023,4],[32619,0],[33144,4],[33742,0],[34267,4],[35959,0],[36511,4],[37108,0],[37657,4],[39325,0],[39877,4],[41570,0],[42122,4],[42718,0],[43270,4],[43842,0],[44368,4],[44963,0],[45489,4],[46086,0],[46636,4],[47207,0],[47756,4],[49426,0],[49978,4],[50574,0],[51102,4],[51697,0],[52246,4],[53914,0],[54466,4],[56159,0],[56712,4],[58404,0],[58956,4],[60649,0],[61201,4]]}";
            var code = PicoRecordJsonToIrCodeDefinitionConverter.Convert(json);

            code.Code.Should().Be("New Code");
            code.Waveform[0].T.Should().Be(0);
            code.Waveform[0].V.Should().Be(1);
            code.Waveform[1].T.Should().Be(4510);
            code.Waveform[1].V.Should().Be(0);
            code.Waveform[2].T.Should().Be(9027);
            code.Waveform[2].V.Should().Be(1);
            code.Waveform[3].T.Should().Be(9579);
            code.Waveform[3].V.Should().Be(0);
        }

    }
}