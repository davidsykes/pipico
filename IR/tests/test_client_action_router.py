import sys
sys.path.append('../src/server')
from client_action_router import ClientActionRouter

class MockAction:
    def action(self, action=None):
        self.action = action
        return 'action ' + ('' if action is None else action)

class MockLogger:
    def __init__(self):
        self.logs = []
    def log(self, message):
        self.logs.append(message)

class TestClientActionRouter:
    def setup_method(self, test_method):
        self.codes_action = MockAction();
        self.home_action = MockAction();
        self.mock_logger = MockLogger()
        self.router = ClientActionRouter(self.home_action, self.codes_action, self.mock_logger)

    def test_home_response(self):
        response = self.router.action('GET', '/')
        assert(response == 'action ')
        assert(len(self.mock_logger.logs) == 0)

    def test_code_request(self):
        response = self.router.action('GET', '/code/527199')

        assert(self.codes_action.action == '/code/527199')
        assert(response == 'action /code/527199')
        assert(len(self.mock_logger.logs) == 0)

    def test_invalid_route(self):
        response = self.router.action('GET', '/cude/527199')

        assert(response is None)
        assert(len(self.mock_logger.logs) == 1)
        assert(self.mock_logger.logs[0] == 'Invalid request: GET /cude/527199')

    def test_favicon(self):
        response = self.router.action('GET', '/favicon.ico')

        assert(response is None)
        assert(len(self.mock_logger.logs) == 0)
