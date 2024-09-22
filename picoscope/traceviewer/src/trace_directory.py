import sys
import json
sys.path.append('./src/logic')
from command_exception import CommandException

class TraceDirectory:
    def __init__(self, system):
        self._system = system
        self._traces = []

    def _trace_key(self, item):
        return item['tracename']

    def update_trace_list(self):
        url = 'tracedetails'
        traces_json = self._system.get(url)
        self._traces = json.loads(traces_json)
        self._traces.sort(key=self._trace_key)
        return self._traces
    
    def get_trace_path_by_number(self, number):
        index = int(number) - 1
        if (index >= len(self._traces)):
            raise CommandException('Trace index ' + str(number) + ' out of range')
        return self._traces[index]['tracepath']
    
    def get_trace_data_by_number(self, number):
        path = self.get_trace_path_by_number(number)
        url = 'trace/' + path
        #print('get trace', url)
        trace_json = self._system.get(url)
        #print('got trace', trace_json)
        trace = json.loads(trace_json)
        return trace