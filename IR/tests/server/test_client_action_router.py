import sys
sys.path.append('../src/server')
from client_action_router import ClientActionRouter
from url_request_decoder import UrlRequest

class MockAction:
    def __init__(self, name):
        self.name = name
    def action(self, action=None):
        self.action = action
        return self.name + ' action ' + ('' if action is None else action)

class MockLogger:
    def __init__(self):
        self.logs = []
    def log(self, message):
        self.logs.append(message)

class TestClientActionRouter:
    def setup_method(self, test_method):
        self.home_action = MockAction('home')
        self.sequences_action = MockAction('sequence')
        self.codes_action = MockAction('codes')
        self.mock_logger = MockLogger()
        self.router = ClientActionRouter(self.home_action, self.sequences_action, self.codes_action, self.mock_logger)

    def test_home_response(self):
        response = self.router.action(UrlRequest('GET', '/'))
        assert(response == 'home action ')
        assert(len(self.mock_logger.logs) == 0)

    def test_sequence_request(self):
        response = self.router.action(UrlRequest('GET', '/sequence/Sequence%201'))

        assert(self.sequences_action.action == '/sequence/Sequence%201')
        assert(response == 'sequence action /sequence/Sequence%201')
        assert(len(self.mock_logger.logs) == 0)

    def test_code_request(self):
        response = self.router.action(UrlRequest('GET', '/code/527199'))

        assert(self.codes_action.action == '/code/527199')
        assert(response == 'codes action /code/527199')
        assert(len(self.mock_logger.logs) == 0)

    def test_invalid_route(self):
        response = self.router.action(UrlRequest('GET', '/cude/527199'))

        assert(response is None)
        assert(len(self.mock_logger.logs) == 1)
        assert(self.mock_logger.logs[0] == 'Invalid request: GET /cude/527199')

    def test_favicon(self):
        response = self.router.action(UrlRequest('GET', '/favicon.ico'))

        assert(response is None)
        assert(len(self.mock_logger.logs) == 0)
