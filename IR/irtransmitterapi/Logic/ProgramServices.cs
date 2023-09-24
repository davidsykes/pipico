using DSLogging;
using DSLogging.Loggers;
using Logic.Database;
using SQLiteLibrary;

namespace Logic
{
    public class ProgramServices
    {
        public IDSLogger Logger { get; private set; }
        public IDatabaseAccess DatabaseAccess { get; private set; }

        public ProgramServices(ProgramParameters parameters)
        {
            Logger = SetUpLogging(parameters);
            var databasePath = parameters.GetParameter("DatabasePath");
            var databaseConnection = new DBServices().OpenFileConnection(databasePath);
            IrTransmitterApiMigrations.RunMigrations(databaseConnection);
            var lockingDatabaseConnection = new LockingDatabaseConnection(databaseConnection);
            var systemWrapper = new SystemWrapper.SystemWrapper();
            DatabaseAccess = new DatabaseAccess(lockingDatabaseConnection, systemWrapper);
        }

        private static IDSLogger SetUpLogging(ProgramParameters parameters)
        {
            var logPath = parameters.GetParameter("LogFilePath");
            Console.WriteLine($"Log file: {logPath}");
            var fileLogger = new FileLogger(logPath);
            return new LogTimeStamp(fileLogger);
        }
    }
}
