import sys
sys.path.append('../src/logic')
sys.path.append('../src/server')
from url_request_decoder import UrlRequestDecoder
from ir_exception import IrException

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

    def test_none_request_raises_irexception(self):
        request = None
        exception = None
        try:
            self._decoder.decode_request(request)
        except IrException as e:
            exception = str(e)
        assert(exception == 'Url Request is None')

    def test_empty_request_raises_irexception(self):
        request = ''
        exception = None
        try:
            self._decoder.decode_request(request)
        except IrException as e:
            exception = str(e)
        assert(exception == 'Url Request is empty')
