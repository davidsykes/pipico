class CommandC:
    def __init__(self, trace_directory):
        self._trace_directory = trace_directory

    def process_command(self, arguments=None):
        trace_details = self._trace_directory.get_trace_data_by_number(arguments[0])
        tracecount = trace_details['scopeTraceDetails']['tracecount']
        print('char CodeName[] = "";')
        print ('int CodeSize = ' + str(tracecount) + ';')
        times = 'int CodeTimes[] = { '
        values = 'char CodeValues[] = { '

        for index, x in enumerate(trace_details['rawScopeTraceData']['values']):
            if (index > 0):
                times = times + ', '
                values = values + ', '
            times = times + str(x[0])
            value = '1' if x[1] == 0 else '0'
            values = values + value
        times = times + ' };'
        values = values + ' };'
        print(times)
        print(values)
