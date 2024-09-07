using Logic.Codes;

namespace Logic.Network
{
    internal class HttpClientWrapper : IHttpClientWrapper
    {
        public string Get(string url)
        {
            var httpClient = new HttpClient();
            var json = GetAsync(httpClient, "http://192.168.1.92/record").Result;
            return json;
        }

        private static async Task<string> GetAsync(HttpClient _httpClient, string url)
        {
            var response = await _httpClient.GetAsync(url);
            var responseContent = response.Content;
            using var reader = new StreamReader(await responseContent.ReadAsStreamAsync());
            var responseText = await reader.ReadToEndAsync();
            return responseText;
        }
    }
}
