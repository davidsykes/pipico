import sys
sys.path.append('../src')
sys.path.append('../src/logic')
from url_request_decoder import UrlRequestDecoder

class TestUrlRequestProcessor:
    def setup_method(self, test_method):
        self._decoder = UrlRequestDecoder()

    def test_root_request(self):
        request = """GET / HTTP/1.1
Host: 192.168.1.75
Connection: keep-alive"""

        result = self._decoder.decode_request(request)

        assert(result.type == 'GET')
        assert(result.url == '/')

