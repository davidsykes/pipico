import sys
sys.path.append('../src/server')
sys.path.append('../src/logic')
from client_action_home import ClientActionHome

class MockCodes:
	def get_sequence_names(self):
		return ['Sequence 1', 'Sequence 2']
	def get_code_names(self):
		return ['Code 1', 'Code 2']

class TestClientActionHome:
	def setup_method(self, test_method):
		self.action = ClientActionHome(MockCodes())

	def test_action(self):
		response = self.action.action()

		assert(response == '<h1>Push My Button</h1>' + \
	 '<p style="font-size:70pt"><a href="/sequence/Sequence%201">Sequence 1</a></p><p style="font-size:70pt"><a href="/sequence/Sequence%202">Sequence 2</a></p>' + \
	 '<p style="font-size:30pt"><a href="/code/Code%201">Code 1</a></p><p style="font-size:30pt"><a href="/code/Code%202">Code 2</a></p>')