import sys
sys.path.append('../src')
from flasher import Flasher

class MockPin:
	def __init__(self, system):
		self.system = system
		self.state = 0
	def toggle(self):
		self.state = 1 - self.state

class MockSystem:
	def __init__(self):
		self.sequence = []
	def make_output_pin(self, name):
		self.pin = MockPin(self)
		return self.pin
	def make_timer(self):
		return None
	def init_timer(self, timer, frequency, callback):
		self.callback = callback
	def trigger(self):
		self.callback(None)
		self.sequence.append(self.pin.state)

class TestFlasher:
	def setup_method(self, test_method):
		self.mock_system = MockSystem()
		self.flasher = Flasher(self.mock_system)

	def test_initial_sequence_is_a_simple_on_off_flash(self):
		self.mock_system.trigger()
		self.mock_system.trigger()
		self.mock_system.trigger()
		self.mock_system.trigger()
		self.mock_system.trigger()
		self.mock_system.trigger()

		assert(self.mock_system.sequence == [1,0,1,0,1,0])
