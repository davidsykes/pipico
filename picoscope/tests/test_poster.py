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
        self.poster = Poster(self.mock_system, 'server url')

    def test_post_data_posts_to_the_server_in_json(self):
        self.poster.post_data(b'Hello World')

        assert(self.mock_system.put_url == 'server url/trace')
        assert(self.mock_system.put_data == '{"title": "Yo", "trace": "SGVsbG8gV29ybGQ="}')