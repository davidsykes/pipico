namespace Logic.Logic
{
    public interface ISystemWrapper
    {
        IEnumerable<string> EnumerateFiles(string directoryPath);
        byte[] FileReadAllBytes(string path);
        byte[] ReadBytes(string path, int byteCount);
    }
}
