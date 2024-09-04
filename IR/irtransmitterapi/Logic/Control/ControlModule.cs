
using System.Net.Http;

namespace Logic.Control
{
    public class ControlModule
    {
        public void Record()
        {
            var httpClient = new HttpClient();
            var r = GetAsync(httpClient, "http://192.168.1.92/record").Result;
            Console.WriteLine(r.ToString());
        }

        public void UploadCodes()
        {
            var httpClient = new HttpClient();
            var r = GetAsync(httpClient, "http://192.168.1.92/bla").Result;
            Console.WriteLine(r.ToString());
        }

        private async Task<string> GetAsync(HttpClient _httpClient, string url)
        {
            var response = await _httpClient.GetAsync(url);
            var responseContent = response.Content;
            using var reader = new StreamReader(await responseContent.ReadAsStreamAsync());
            var responseText = await reader.ReadToEndAsync();
            return responseText;
        }
    }
}
