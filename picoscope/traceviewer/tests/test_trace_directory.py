import sys
sys.path.append('../src')
from trace_directory import TraceDirectory

data = '[{"traceName":"20230525055427","traceCount":301,"traceLength":53344},{"traceName":"20230525055404","traceCount":93,"traceLength":5531},{"traceName":"20230523054639","traceCount":247,"traceLength":6766}]'

class MockSystem:
    def get(self, url):
        if url == 'url/tracenames':
            return data

class TestTraceDirectory:
    def setup_method(self, test_method):
        mock_system = MockSystem()
        self.dir = TraceDirectory(mock_system, 'url')

    def test_get_trace_list(self):
        list = self.dir.get_trace_list()

        assert(list[0]['traceName'] == '20230523054639')
        assert(list[0]['traceCount'] == 247)
        assert(list[0]['traceLength'] == 6766)
        assert(list[1]['traceName'] == '20230525055404')
        assert(list[1]['traceCount'] == 93)
        assert(list[1]['traceLength'] == 5531)
        assert(list[2]['traceName'] == '20230525055427')
        assert(list[2]['traceCount'] == 301)
        assert(list[2]['traceLength'] == 53344)
