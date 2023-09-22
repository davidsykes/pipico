using Logic.Database.DatabaseObjects;
using Logic.Database.DatabaseObjects.IR;
using Logic.DataObjects;
using SQLiteLibrary;
using System.Text.Json;
using SystemWrapper;

namespace Logic.Database
{
    internal class DatabaseAccess : IDatabaseAccess
    {
        private readonly IDatabaseConnection _databaseConnection;
        private readonly ISystemWrapper _systemWrapper;

        public DatabaseAccess(IDatabaseConnection databaseConnection, ISystemWrapper systemWrapper)
        {
            _databaseConnection = databaseConnection;
            _systemWrapper = systemWrapper;
        }

        public IList<IRCodeDefinition> GetCodes()
        {
            var wavePoints = _databaseConnection.Select<DBOWavePoint>();

            var results = from p in wavePoints
                          group p by p.Code into g
                          select new { Code = g.Key, WavePoints = g.ToList() };

            return results.Select(m
                => new IRCodeDefinition
                {
                    Code = m.Code.ToString(),
                    Waveform = m.WavePoints.OrderBy(s => s.Time)
                    .Select(i => new WavePoint { T = i.Time, V = i.Value }).ToList()
                }).ToList();
        }

        public DBOLog Log(string text)
        {
            var log = new DBOLog
            {
                Time = _systemWrapper.Now,
                Text = text
            };

            _databaseConnection.RunInTransaction((IDatabaseTransaction t)
                => t.InsertRow(log)
            );

            return log;
        }

        public IList<DBOLog> GetLogs(int count)
        {
            var logs =  _databaseConnection.Select<DBOLog>(endWith: $"ORDER BY Time DESC LIMIT {count}");
            logs.Reverse();
            return logs;
        }

        public void ClearLogs()
        {
            _databaseConnection.RunInTransaction((IDatabaseTransaction t)
                => t.DeleteRows<DBOLog>("1=1", new { }));
        }

        public string GetOption(string optionName)
        {
            var options = _databaseConnection.Select<DBOOption>(
                null,
                "Name=@Name",
                null,
                new { Name = optionName }
            );
            return options.SingleOrDefault()?.Value ?? "";
        }

        public string SetIrCodeWavePoints(string irCodeJSON)
        {
            try
            {
                var irCode = JsonSerializer.Deserialize<WaveDefinitionFromPico>(irCodeJSON)
                    ?? throw new IrTransmitterApiException("Invalid data for SetIrCode");
                var code = irCode.code;
                var time = 0;
                var wavePoints = irCode.wavepoints
                    .Select(w =>
                    {
                        time += w[0];
                        return
                    new DBOWavePoint
                    {
                        Code = code.ToString(),
                        Time = time,
                        Value = w[1]
                    };
                    }
                    );

                UpdateIrCodeWavePoints(code, wavePoints);

                return code;
            }
            catch (JsonException)
            {
                throw new IrTransmitterApiException("Invalid data for SetIrCode");
            }
        }

        private void UpdateIrCodeWavePoints(string code, IEnumerable<DBOWavePoint> wavePoints)
        {
            _databaseConnection.RunInTransaction((IDatabaseTransaction t)
                => {
                    DeleteCode(t, code);
                    t.InsertRows(wavePoints);
                });
        }

        public void SetOption(string optionName, string optionValue)
        {
            _databaseConnection.RunInTransaction((IDatabaseTransaction t) =>
            t.UpdateRow(new DBOOption { Name = optionName, Value = optionValue }
            ));
        }

        public void UpdateCodeName(string code, string name)
        {
            _databaseConnection.RunInTransaction((IDatabaseTransaction t)
                => t.ExecuteNonQuery(
                    "UPDATE IRWavePoints SET Code=@NewName WHERE Code=@CurrentName",
                    new { CurrentName = code, NewName = name}));
        }

        public void UpdateSequence(string sequence, string code, int position)
        {
            _databaseConnection.RunInTransaction((IDatabaseTransaction t)
                => t.UpdateRow(new DBOSequence
                {
                    Sequence = sequence,
                    Code = code,
                    Position = position
                }));
        }

        public void DeleteSequence(string sequence, string code, int position)
        {
            _databaseConnection.RunInTransaction((IDatabaseTransaction t)
                => t.DeleteRow(new DBOSequence
                {
                    Sequence = sequence,
                    Code = code,
                    Position = position
                }));
        }

        public IRSequences GetSequences()
        {
            var sequences = _databaseConnection.Select<DBOSequence>();

            var grouped = from s in sequences
                    group s by s.Sequence
                    into g
                    select new IRSequence
                    {
                        Name = g.Key,
                        Codes = g
                        .OrderBy(i => i.Position)
                        .Select(h => h.Code).ToList(),
                    }
                    ;

            return new IRSequences
            {
                Sequences = grouped.ToList()
            };
        }

        public void DeleteCode(string code)
        {
            _databaseConnection.RunInTransaction((IDatabaseTransaction t)
            => DeleteCode(t, code));
        }

        private void DeleteCode(IDatabaseTransaction t, string code)
        {
            t.DeleteRows<DBOWavePoint>("Code=@Code", new { Code = code });
        }
    }
}
