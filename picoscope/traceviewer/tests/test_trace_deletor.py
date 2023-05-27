import pytest
import sys
sys.path.append('../src')
from trace_deletor import TraceDeletor

class MockTraceDirectory:
    def get_trace_path(self, trace):
        return 'trace#' + str(trace+10)

class MockRestSystem:
    def __init__(self):
        self.post_calls = []
    def post(self, url):
        self.post_calls.append(url)

class TestTraceDeletor:
    def setup_method(self, test_method):
        self.mock_trace_directory = MockTraceDirectory()
        self.mock_rest_system = MockRestSystem()
        self.deletor = TraceDeletor(self.mock_trace_directory, self.mock_rest_system)

    def test_traces_are_deleted(self):
        self.deletor.delete_traces(['1', '3', '7'])

        assert(len(self.mock_rest_system.post_calls) == 3)
        assert(self.mock_rest_system.post_calls[0] == 'delete/trace#11')
        assert(self.mock_rest_system.post_calls[1] == 'delete/trace#13')
        assert(self.mock_rest_system.post_calls[2] == 'delete/trace#17')