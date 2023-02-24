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
		self.pins_values = {}
		self.pins_values[5] = 0
		self.pins_values[4] = 0
		self.pins_values[3] = 0
		self.pins_values[2] = 0
	def make_input_pin(self, name, _):
		return MockPin(self.pins_values[name])


class TestConfigurationSwitches:
	def setup_method(self, test_method):
		self.system = MockSystem()

	def test_off_values(self):
		s = ConfigurationSwitches(self.system)

		assert(s.be_a_temperature_sensor == False)
		assert(s.are_we_a_listener == False)
		assert(s.dump_raw_ir_codes == False)

	def test_pin_5_is_temperature_sensor(self):
		self.system.pins_values[5] = 1

		s = ConfigurationSwitches(self.system)

		assert(s.be_a_temperature_sensor == True)

	def test_pin_4_is_ir_mode(self):
		self.system.pins_values[4] = 1

		s = ConfigurationSwitches(self.system)

		assert(s.are_we_a_listener == True)

	def test_pin_3_is_ir_dump_mode(self):
		self.system.pins_values[3] = 1

		s = ConfigurationSwitches(self.system)

		assert(s.dump_raw_ir_codes == True)
