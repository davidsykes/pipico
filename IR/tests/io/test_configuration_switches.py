import sys
sys.path.append('../src/io')
from configuration_switches import ConfigurationSwitches

class MockPin:
	def __init__(self, value):
		self._value = value
	def value(self):
		return self._value

class MockSystem:
	def __init__(self):
		self.id = 'id'
		self.pins_values = {}
		self.pins_values[5] = 0
		self.pins_values[4] = 0
		self.pins_values[3] = 0
		self.pins_values[2] = 0
	def make_input_pin(self, name, _):
		return MockPin(self.pins_values[name])

class MockServiceAccess:
	def __init__(self):
		self.options = {}
	def get_option(self, option):
		if option in self.options:
			return self.options[option]
		return ''
	def log(self, m):
		pass

class TestConfigurationSwitches:
	def setup_method(self, test_method):
		self.system = MockSystem()
		self.access = MockServiceAccess()

	def create_test_object(self):
		return ConfigurationSwitches(self.system, self.access)

	def test_off_values(self):
		s = self.create_test_object()

		assert(s.are_we_ir_transmitter == False)
		assert(s.dump_raw_ir_codes == False)

	def test_pin_4_is_ir_mode(self):
		self.system.pins_values[4] = 1

		s = self.create_test_object()

		assert(s.are_we_ir_transmitter == True)

	def test_pin_3_is_ir_dump_mode(self):
		self.system.pins_values[3] = 1

		s = self.create_test_object()

		assert(s.dump_raw_ir_codes == True)

	def test_override_with_ir_transmitter(self):
		self.access.options['id.function'] = 'irtransmitter'

		s = self.create_test_object()

		assert(s.are_we_ir_transmitter == True)
		assert(s.dump_raw_ir_codes == False)

	def test_override_with_ir_receiver(self):
		self.access.options['id.function'] = 'irreceiver'

		s = self.create_test_object()

		assert(s.are_we_ir_transmitter == False)
		assert(s.dump_raw_ir_codes == False)
