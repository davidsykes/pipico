import sys
sys.path.append('../src')
from network_wrapper import Network

class TestNetworkWrapper:
    def setup_method(self, test_method):
        self.network = Network(None, 'base url')

    def test_get_url(self):
        url = self.network.get_url('url path')

        assert(url == 'base url/url path')

