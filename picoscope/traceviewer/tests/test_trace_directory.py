import sys
sys.path.append('../src')
from trace_directory import TraceDirectory

data = """[
{"tracename":"20230525055427","tracepath":"20230525055427.trc","tracecount":301,"tracelength":53344},
{"tracename":"20230525055404","tracepath":"20230525055404.trc","tracecount":93,"tracelength":5531},
{"tracename":"20230523054639","tracepath":"20230523054639.trc","tracecount":247,"tracelength":6766}]"""

trace_2_data = '"data for trace 2"'

class MockSystem:
    def get(self, url):
        if url == 'tracenames':
            return data
        elif url == 'trace/20230525055404.trc':
            return trace_2_data
        else:
            raise Exception('Invalid url: ' + url)

class TestTraceDirectory:
    def setup_method(self, test_method):
        mock_system = MockSystem()
        self.dir = TraceDirectory(mock_system)

    def test_update_trace_list(self):
        list = self.dir.update_trace_list()

        assert(list[0]['tracename'] == '20230523054639')
        assert(list[0]['tracepath'] == '20230523054639.trc')
        assert(list[0]['tracecount'] == 247)
        assert(list[0]['tracelength'] == 6766)
        assert(list[1]['tracename'] == '20230525055404')
        assert(list[1]['tracepath'] == '20230525055404.trc')
        assert(list[1]['tracecount'] == 93)
        assert(list[1]['tracelength'] == 5531)
        assert(list[2]['tracename'] == '20230525055427')
        assert(list[2]['tracepath'] == '20230525055427.trc')
        assert(list[2]['tracecount'] == 301)
        assert(list[2]['tracelength'] == 53344)

    def test_get_trace_path_by_number_gets_path_from_index_offset_by_1(self):
        self.dir.update_trace_list()
        path = self.dir.get_trace_path_by_number(2)

        assert(path == '20230525055404.trc')

    def test_get_trace_data_by_number_gets_a_trace_from_its_number(self):
        self.dir.update_trace_list()
        trace = self.dir.get_trace_data_by_number(2)

        assert(trace == 'data for trace 2')
