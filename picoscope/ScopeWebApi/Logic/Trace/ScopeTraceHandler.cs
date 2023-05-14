using Logic.Messaging;

namespace Logic.Trace
{
    public class ScopeTraceHandler : IMessageHandler
    {
        public bool ProcessMessage(byte[] bytes)
        {
            Console.WriteLine($"Received {bytes.Length} bytes");

            var fileName = DateTime.Now.ToString("yyyyMMddHHmmss") + ".bin";
            Console.WriteLine($"Write data to {fileName}");
            var file = File.Open(fileName, FileMode.Create);
            file.Write(bytes);
            file.Close();

            return true;
        }
    }
}
