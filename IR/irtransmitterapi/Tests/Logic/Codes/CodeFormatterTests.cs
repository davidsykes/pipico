using FluentAssertions;
using Logic.Codes;
using Logic.DataObjects;
using TestHelpers;

#nullable disable
namespace Tests.Logic.Codes
{
    public class CodeFormatterTests : TestBase
    {
        ICodeFormatter _formatter;


        [Test]
        public void TheCodeCanBeFormattedToInlineCPlusPlus()
        {
            IRCodeDefinition code = new()
            {
                Code = "Code",
                Waveform = new List<WavePoint>
                    {
                        new() { T = 0, V = 0 },
                        new() { T = 11, V = 1 },
                        new() { T = 22, V = 0 }
                    }
            };

            var result = _formatter.FormatCodeCPlusPlus(code);

            result.Should().NotBeNull();
        }

        #region Support Code

        protected override void SetUpObjectUnderTest()
        {
            base.SetUpObjectUnderTest();
            _formatter = new CodeFormatter();
        }

        #endregion
    }
}