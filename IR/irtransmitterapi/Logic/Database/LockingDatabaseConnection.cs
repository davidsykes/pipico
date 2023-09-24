using SQLiteLibrary;

namespace Logic.Database
{
    internal class LockingDatabaseConnection : IDatabaseConnection
    {
        private readonly IDatabaseConnection _databaseConnection;

        public LockingDatabaseConnection(IDatabaseConnection databaseConnection)
        {
            _databaseConnection = databaseConnection;
        }

        public void AddLogger(LogSQLiteCommandDelegate logger)
        {
            lock (_databaseConnection)
            {
                _databaseConnection.AddLogger(logger);
            }
        }

        public void RunInTransaction(Action<IDatabaseTransaction> action)
        {
            lock (_databaseConnection)
            {
                _databaseConnection.RunInTransaction(action);
            }
        }

        public void RunInTransaction<TParam>(Action<IDatabaseTransaction, TParam> action, TParam parameters)
        {
            lock (_databaseConnection)
            {
                _databaseConnection.RunInTransaction(action, parameters);
            }
        }

        public IList<T> Select<T>(string? query = null, string? where = null, string? endWith = null,
            object? parameters = null) where T : new()
        {
            lock (_databaseConnection)
            {
                return _databaseConnection.Select<T>(query, where, endWith, parameters);
            }
        }
    }
}
