using Logic.DataObjects;
using System.Text;

namespace Logic.Codes
{
    public class CodeFormatter : ICodeFormatter
    {
        public string FormatCodeCPlusPlus(IRCodeDefinition code)
        {
            StringBuilder s = new StringBuilder();

            s.Append($"char CodeName{code.Code}[] = \"{code.Code}\";\n");

            s.Append($"int CodeSize{code.Code} = {code.Waveform.Count};\n");

            s.Append($"int CodeTimes{code.Code}[] = {{");
            for (int i = 0; i < code.Waveform.Count; i++)
            {
                if (i > 0)
                    s.Append(", ");
                s.Append(code.Waveform[i].T);
            }
            s.Append($"}};\n");

            s.Append($"int CodeValues{code.Code}[] = {{");
            for (int i = 0; i < code.Waveform.Count; i++)
            {
                if (i > 0)
                    s.Append(", ");
                s.Append(code.Waveform[i].V);
            }
            s.Append($"}};\n");

            return s.ToString();
        }
    }
}
