import sys
sys.path.append('../src')
#sys.path.append('../Mock')
#from listener import Listener
#from mocknetwork import MockNetwork
from client_action_router import ClientActionRouter

#class MockTransmitter:
#    def __init__(self):
#        self.transmitted_code = None
#
class MockAction:
    def action(self, action):
        self.action = action
#    def __init__(self, codes):
#        self.codes = codes
#    def get_codes(self):
#        return self.codes

class MockClientAction:
    pass

class TestListener:
    def setup_method(self, test_method):
        self.codes_action = MockAction();
        self.router = ClientActionRouter(self.codes_action)

    def test_code_request(self):
        self.router.action('GET', '/code/527199')

        assert(self.codes_action.action == '/code/527199')