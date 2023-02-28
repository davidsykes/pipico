import sys
sys.path.append('../src/io')
sys.path.append('../src/wave_forms')
from ir_transmitter import IrTransmitter
from waveform import Waveform

class MockPin:
	def __init__(self, system):
		self.system = system
		self.start_time = system.time
		self.trace = []
	def value(self, value):
		time = self.system.time - self.start_time
		self.trace.append((time,value))

class MockSystem:
	def __init__(self):
		self.time = 12345
	def ticks_us(self):
		self.time = self.time + 1
		return self.time

class TestIrTransmitter:
	def setup_method(self, test_method):
		self.system = MockSystem()
		self.pin = MockPin(self.system)
		self.tranmitter = IrTransmitter(self.system, self.pin)

	def test_transmission(self):
		test_waveform = Waveform({'code': 2911, 'waveform': [{'t': 0, 'v': 0}, {'t': 10, 'v': 1}, {'t': 20, 'v': 0}]})

		self.tranmitter.transmit(test_waveform)

		assert(len(self.pin.trace) == 3)
		assert(self.pin.trace[0] == (1,0))
		assert(self.pin.trace[1] == (11,1))
		assert(self.pin.trace[2] == (31,0))
