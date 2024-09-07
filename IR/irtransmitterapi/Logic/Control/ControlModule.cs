using Logic.Codes;
using Logic.Database;
using Logic.Network;

namespace Logic.Control
{
    public class ControlModule
    {
        readonly IHttpClientWrapper _httpClient;
        readonly IDatabaseAccess _databaseAccess;

        public ControlModule(IHttpClientWrapper _httpClient, IDatabaseAccess databaseAccess)
        {
            this._httpClient = _httpClient;
            this._databaseAccess = databaseAccess;
        }

        public void Record()
        {
            var json = _httpClient.Get("http://192.168.1.92/record");

            try
            {
                var irCodeDefinition = PicoRecordJsonToIrCodeDefinitionConverter.Convert(json);
                _databaseAccess.UpdateIrCodeDefinition(irCodeDefinition);
            }
            catch (Exception ex)
            {
                string message = $"Invalid response from pico: {json}";
                _databaseAccess.Log(message);
            }
        }
    }
}
