class CommandL:
    def __init__(self, trace_directory):
        self._trace_directory = trace_directory

    def process_command(self, arguments=None):
        traces = self._trace_directory.update_trace_list()
        for i in range(len(traces)):
            trace = traces[i]
            print(''.join([str(i+1), ': ', trace['tracename'], ' (', str(trace['tracecount']), ' - ', str(trace['tracelength']/1000), 'ms)']))
