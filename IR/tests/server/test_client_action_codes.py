import sys
sys.path.append('../src/server')
from client_action_codes import ClientActionCodes

class MockCodes:
	def __init__(self, data):
		self.xmit_data = data
	def get_code(self, code):
		if code == '527199':
			return self.xmit_data
		raise AssertionError

class MockTransmitter:
	def __init__(self):
		self.xmit = None
	def transmit(self, code):
		self.xmit = code

class MockClientActionHome:
	def action(self):
		return 'home action'

class TestClientActionCodes:
	def setup_method(self, test_method):
		self.xmit_data = [{'t': 0, 'v': 0}, {'t': 2382, 'v': 1}, {'t': 2981, 'v': 0}, {'t': 4181, 'v': 1}, {'t': 4759, 'v': 0}, {'t': 5372, 'v': 1}, {'t': 5954, 'v': 0}, {'t': 6581, 'v': 1}, {'t': 7162, 'v': 0}, {'t': 7775, 'v': 1}, {'t': 8318, 'v': 0}, {'t': 8982, 'v': 1}, {'t': 9571, 'v': 0}, {'t': 10160, 'v': 1}, {'t': 10735, 'v': 0}, {'t': 11357, 'v': 1}, {'t': 11940, 'v': 0}, {'t': 12559, 'v': 1}, {'t': 13151, 'v': 0}, {'t': 14355, 'v': 1}, {'t': 14937, 'v': 0}, {'t': 15523, 'v': 1}, {'t': 16108, 'v': 0}, {'t': 17314, 'v': 1}, {'t': 17899, 'v': 0}, {'t': 19138, 'v': 1}, {'t': 19690, 'v': 0}, {'t': 20318, 'v': 1}, {'t': 20905, 'v': 0}, {'t': 22114, 'v': 1}, {'t': 22697, 'v': 0}, {'t': 23320, 'v': 1}, {'t': 23872, 'v': 0}, {'t': 25105, 'v': 1}, {'t': 25689, 'v': 0}, {'t': 26894, 'v': 1}, {'t': 27489, 'v': 0}, {'t': 28695, 'v': 1}, {'t': 29277, 'v': 0}, {'t': 30482, 'v': 1}, {'t': 31066, 'v': 0}, {'t': 32273, 'v': 1}]
		self.mock_codes = MockCodes(self.xmit_data)
		self.mock_transmitter = MockTransmitter()
		self.action = ClientActionCodes(self.mock_codes, self.mock_transmitter, MockClientActionHome())

	def test_action(self):
		self.action.action('/code/527199')

		assert(self.mock_transmitter.xmit == self.xmit_data)

	def test_response(self):
		response = self.action.action('/code/527199')

		assert(response == 'home action')

	def test_invalid_action(self):
		response = self.action.action('/coode/527199')

		assert(response == '<h1>INVALID CODE /coode/527199</h1>')