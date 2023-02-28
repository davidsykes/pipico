import sys
import json
sys.path.append('../src/service')
from service_access import ServiceAccess

class MockNetwork:
    def __init__(self):
        self.connected = True
    def put(self,url, headers, data):
        self.put_url = url
        self.put_headers = headers
        self.put_data = json.dumps(data)

class TestServiceAccess:
    def setup_method(self, test_method):
        self.mock_network = MockNetwork()
        self.access = ServiceAccess(self.mock_network, 'base url')

    def test_get_url(self):
        url = self.access.get_url('url path')

        assert(url == 'base url/url path')

    def test_send_ir_code_sends_ir_code_in_waveforem_format(self):
        wave_data = [[0,1],[2,3],[4,5]]

        self.access.send_ir_code(123, wave_data)

        assert(self.mock_network.put_url == 'base url' + '/ircode')
        assert(self.mock_network.put_headers == {'content-type': 'application/json'})
        assert(self.mock_network.put_data == '{"code": "123", "wavepoints": [[0, 1], [2, 3], [4, 5]]}')