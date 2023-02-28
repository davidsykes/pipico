import sys
sys.path.append('../src/io')
from flasher import Flasher

class MockPin:
	def __init__(self, system):
		self.system = system
		self.state = 0
	def toggle(self):
		self.state = 1 - self.state
	def value(self, value):
		self.state = value

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

	def test_a_sequence_begins_with_the_led_on(self):
		self.mock_system.pin.state = 0
		self.flasher.set_sequence([1,1])

		self.mock_system.trigger()
		self.mock_system.trigger()

		assert(self.mock_system.sequence == [1,0])

	def test_more_complex_sequence(self):
		self.flasher.set_sequence([1,2,3,4])

		for _ in range(11):
			self.mock_system.trigger()

		assert(self.mock_system.sequence == [1,0,0,1,1,1,0,0,0,0,1])

	def test_an_empty_sequence_does_nothing(self):
		self.flasher.set_sequence([])

		for _ in range(3):
			self.mock_system.trigger()

		assert(self.mock_system.sequence == [0,0,0])

	def test_a_none_sequence_does_nothing(self):
		self.flasher.set_sequence(None)

		for _ in range(3):
			self.mock_system.trigger()

		assert(self.mock_system.sequence == [0,0,0])

	def test_set_status_1_flashes_once(self):
		self.flasher.set_status(1)

		assert(self.flasher.sequence == [1,5])

	def test_set_status_3_flashes_three_times(self):
		self.flasher.set_status(3)

		assert(self.flasher.sequence == [1,1,1,1,1,5])

	def test_set_status_0_flashes_once(self):
		self.flasher.set_status(0)

		assert(self.flasher.sequence == [1,5])