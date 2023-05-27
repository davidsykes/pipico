import json

class TraceDirectory:
    def __init__(self, system):
        self._system = system
        self._traces = []

    def _trace_key(self, item):
        return item['tracename']

    def update_trace_list(self):
        url = 'tracenames'
        traces_json = self._system.get(url)
        self._traces = json.loads(traces_json)
        self._traces.sort(key=self._trace_key)
        return self._traces
    
    def get_trace_path(self, index):
        return self._traces[index-1]['tracepath']