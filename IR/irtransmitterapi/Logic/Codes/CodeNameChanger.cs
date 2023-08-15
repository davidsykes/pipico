using Logic.Database;
using System.Text.RegularExpressions;

namespace Logic.Codes
{
    internal class CodeNameChanger : ICodeNameChanger
    {
        readonly IDatabaseAccess _db;

        public CodeNameChanger(IDatabaseAccess db)
        {
            _db = db;
        }

        public void UpdateCodeName(string currentName, string newName)
        {
            Regex rgx = new Regex("[^a-zA-Z0-9_]");
            newName = rgx.Replace(newName, "");
            if (string.IsNullOrEmpty(newName))
            {
                throw new IrTransmitterApiException("New code name is empty.");
            }

            var codes = _db.GetCodes();

            if (codes.Any(c => c.Code == currentName))
            {
                _db.UpdateCodeName(currentName, newName);
            }
            else
            {
                throw new IrTransmitterApiException($"Code '{currentName}' not found.");
            }
        }
    }
}
