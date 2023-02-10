import sys
sys.path.append('../src')
from client_action_router import ClientActionRouter

class MockAction:
    def action(self, action=None):
        self.action = action
        return 'action ' + ('' if action is None else action)

class TestClientActionRouter:
    def setup_method(self, test_method):
        self.codes_action = MockAction();
        self.home_action = MockAction();
        self.router = ClientActionRouter(self.home_action, self.codes_action)

    def test_home_response(self):
        response = self.router.action('GET', '/')
        assert(response == 'action ')

    def test_code_request(self):
        response = self.router.action('GET', '/code/527199')

        assert(self.codes_action.action == '/code/527199')
        assert(response == 'action /code/527199')

    def test_invalid_route(self):
        response = self.router.action('GET', '/cude/527199')

        assert(response is None)

    def test_favicon(self):
        response = self.router.action('GET', '/favicon.ico')

        assert(response is None)