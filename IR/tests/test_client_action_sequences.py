import sys
sys.path.append('../src/server')
from client_action_sequences import ClientActionSequences

class MockTransmitter:
	def __init__(self):
		self.xmit = []
	def transmit(self, code):
		self.xmit.append(code)

class MockClientActionHome:
	def action(self):
		return 'home action'

class MockWaveFormManager:
	def __init__(self):
		self.codes = {}
		self.codes['Code 1'] = 'Code 1 data'
		self.codes['Code 2'] = 'Code 2 data'
	def get_sequence(self, name):
		if name == 'Sequence 1':
			return ['Code 1','Code 2']
	def get_code(self, code_name):
		return self.codes[code_name]

class TestClientActionCodes:
	def setup_method(self, test_method):
		self.mock_waveform_manager = MockWaveFormManager()
		self.mock_transmitter = MockTransmitter()
		self.mock_home_action = MockClientActionHome()
		self.action = ClientActionSequences(self.mock_waveform_manager, self.mock_transmitter, self.mock_home_action)

	def test_action(self):
		self.action.action('/sequence/Sequence%201')

		assert(self.mock_transmitter.xmit == ['Code 1 data', 'Code 2 data'])

	def test_response(self):
		response = self.action.action('/sequence/Sequence%201')

		assert(response == 'home action')

	def test_invalid_action(self):
		response = self.action.action('/seequence/Sequence%201')

		assert(response == '<h1>INVALID SEQUENCE /seequence/Sequence%201</h1>')