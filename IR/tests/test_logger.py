import sys
sys.path.append('../src')
from logger import Logger

class MockNetwork:
	def get_url(self, url):
		return 'ip+'+url
	def put(self, url, message):
		if (url == 'ip+log'):
			self.logged = message

class TestLogger:
	def setup_method(self, test_method):
		self.mock_network = MockNetwork()
		self.logger = Logger(self.mock_network)

	def test_log(self):
		self.logger.log('message')

		assert(self.mock_network.logged == 'message')
