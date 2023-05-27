namespace Logic.Logic
{
    public class SystemWrapper : ISystemWrapper
    {
        public IEnumerable<string> EnumerateFiles(string directoryPath)
        {
            return Directory.EnumerateFiles(directoryPath);
        }

        public byte[] FileReadAllBytes(string path)
        {
            return File.ReadAllBytes(path);
        }

        public byte[] ReadBytes(string path, int byteCount)
        {
            using FileStream fs = new(path, FileMode.Open, FileAccess.Read);
            byte[] buffer = new byte[byteCount];
            var bytes_read = fs.Read(buffer, 0, buffer.Length);
            fs.Close();
            return buffer;
        }

        public void DeleteFile(string filePath)
        {
            File.Delete(filePath);
        }
    }
}
