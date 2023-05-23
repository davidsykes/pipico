import sys
sys.path.append('../src')
from poster import Poster

class MockSystem:
    def put_json(self, url, data):
        self.put_url = url
        self.put_data = data

class TestPoster:
    def setup_method(self, test_method):
        self.mock_system = MockSystem()
        self.poster = Poster(self.mock_system, 'server ip')

    def test_post_data_posts_to_http_url(self):
        self.poster.post_data(b'Hello World')

        assert(self.mock_system.put_url == 'http://server ip/scope')

    def test_post_data_posts_to_the_server_in_json(self):
        self.poster.post_data(b'Hello World')

        assert(self.mock_system.put_data == '{"type": "trace", "data": "48656c6c6f20576f726c64"}')
