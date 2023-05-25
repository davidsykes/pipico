import json

class TraceDirectory:
    def __init__(self, system, url):
        self._system = system
        self._url = url

    def _trace_key(self, item):
        return item['traceName']

    def get_trace_list(self):
        url = self._url + '/tracenames'
        traces_json = self._system.get(url)
        traces = json.loads(traces_json)
        traces.sort(key=self._trace_key)
        return traces