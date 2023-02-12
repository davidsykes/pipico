import sys
sys.path.append('../src')
from ir_transmitter import IrTransmitter

class MockOutputPin:
	pass

class MockInputPin:
	def __init__(self, input_pin):
		self.input_pin = input_pin
		self.trace = []

class TestIrTransmitter:
	def setup_method(self, test_method):
		self.ir_out = MockOutputPin()
		self.ir_in = MockInputPin(self.ir_out)
		self.tranmitter = IrTransmitter()

	def test_transmission(self):
		test_data = [{'t': 0, 'v': 0}, {'t': 10, 'v': 1}, {'t': 20, 'v': 0}, {'t': 40, 'v': 1}]
		expected = [{'t': 0, 'v': 0}, {'t': 10, 'v': 1}, {'t': 30, 'v': 0}, {'t': 70, 'v': 1}]

		self.tranmitter.transmit(test_data)

		assert(self.ir_in.trace == expected)