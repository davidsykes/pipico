using Logic.Database.DatabaseObjects;
using Logic.DataObjects;

namespace Logic.Database
{
    public interface IDatabaseAccess
    {
        IList<IRCodeDefinition> GetCodes();
        string GetOption(string optionName);
        DBOLog Log(string text);
        IList<DBOLog> GetLogs();
        void ClearLogs();
        string SetIrCodeWavePoints(string irCodeJson);
        void SetOption(string optionName, string optionValue);
        void UpdateCodeName(string code, string newName);
        void UpdateSequence(string sequence, string code, int position);
        void DeleteSequence(string sequence, string code, int position);
        IRSequences GetSequences();
        void DeleteCode(string code);
    }
}
