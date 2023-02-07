import sys
sys.path.append('../src')
from url_request_processor import UrlRequestProcessor

class TestUrlRequestProcessor:
    def setup_method(self, test_method):
        self._processor = UrlRequestProcessor()

    def test_root_request(self):
        request = """GET / HTTP/1.1
Host: 192.168.1.75
Connection: keep-alive"""

        result = self._processor.process_request(request)

        assert(result.type == 'GET')
        assert(result.url == '/')

