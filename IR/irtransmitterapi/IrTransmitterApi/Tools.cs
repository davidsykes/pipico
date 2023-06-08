using System.Text;

namespace IrTransmitterApi
{
    public class Tools
    {
        internal static async Task<string> GetJSONString(HttpContext context)
        {
            using (StreamReader reader = new(context.Request.Body, Encoding.UTF8))
            {
                var JSONString = await reader.ReadToEndAsync();
                return JSONString;
            }
        }
    }
}
