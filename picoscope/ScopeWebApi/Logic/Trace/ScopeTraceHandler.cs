using Logic.Messaging;

namespace Logic.Trace
{
    public class ScopeTraceHandler : IMessageHandler
    {
        private readonly string _traceFilePath;

        public ScopeTraceHandler(string traceFilePath)
        {
            _traceFilePath = traceFilePath;
        }

        public bool ProcessMessage(byte[] bytes)
        {
            Console.WriteLine($"Received {bytes.Length} bytes");

            if (bytes.Length >= 4)
            {
                var fileName = DateTime.Now.ToString("yyyyMMddHHmmss") + ".bin";
                var filePath = Path.Combine(_traceFilePath, fileName);
                Console.WriteLine($"Write data to {filePath}");
                var file = File.Open(filePath, FileMode.Create);
                file.Write(bytes);
                file.Close();


                var r = new BinaryReader(new MemoryStream(bytes));

                var id = r.ReadInt32();
                Console.WriteLine($"First int is {id:X}");
                if (id == 0x12345678)
                {
                    Decompose(r);
                }
                else
                {
                    for (int i = 0; i < bytes.Length && i < 100; i++)
                    {
                        var b = bytes[i];
                        if (b < 32 || b > 127)
                        {
                            Console.Write(Convert.ToHexString(bytes, i, 1));
                        }
                        else
                        {
                            Console.Write(Convert.ToChar(b));
                        }
                    }
                    Console.WriteLine("");
                }
            }
            return true;
        }

        private static void Decompose(BinaryReader r)
        {
            try
            {
                var count = r.ReadInt32();
                Console.WriteLine($"Found {count} samples");
                var length = r.ReadInt32();
                Console.WriteLine($"Sample is {length} uS long");
                for (int i = 0; i < count; i++)
                {
                    var t = r.ReadInt32();
                    int v = r.ReadByte();
                    Console.WriteLine($"v={t} - {v}");
                }
                var e = r.ReadInt32();
                Console.WriteLine($"e={e:x}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception {ex.Message}");
            }
        }
    }
}
