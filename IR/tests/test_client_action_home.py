import sys
sys.path.append('../src/server')
from client_action_home import ClientActionHome

class MockCodes:
	def get_code_names(self):
		return ['527199','2911']

class TestClientActionHome:
	def setup_method(self, test_method):
		self.action = ClientActionHome(MockCodes())

	def test_action(self):
		response = self.action.action()

		assert(response == '<h1>Push My Button</h1><p><a href="/code/527199">Code 527199</a></p><p><a href="/code/2911">Code 2911</a></p>')