using Logic.DataObjects;

namespace Logic.Codes
{
    public interface ICodeFormatter
    {
        string FormatCodeCPlusPlus(IRCodeDefinition code);
    }
}
