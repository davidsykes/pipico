import sys
sys.path.append('../src')
from receiver import Receiver

class MockUart:
	def __init__(self):
		self.current_line = 0
		self.current_char = 0

	def any(self):
		return self.there_is_data_left_to_read()

	def read(self):
		if self.there_is_data_left_to_read():
			return self.read_next_character()

	def there_is_data_left_to_read(self):
		return self.current_char < len(self.buffer[self.current_line])

	def read_next_character(self):
		char = self.buffer[self.current_line][self.current_char:self.current_char+1]
		self.move_to_next_character()
		return char
	
	def move_to_next_character(self):
		if self.current_char < len(self.buffer[self.current_line]):
			self.current_char = self.current_char + 1

	def next(self):
		if self.current_line < (len(self.buffer)-1):
			self.current_line = self.current_line + 1
			self.current_char = 0

class MockSystem:
	def __init__(self, uart):
		self.uart = uart
	def sleep(self, s):
		if s >= 0.1:
			self.uart.next()

class TestReceiver:
	def setup_method(self, test_method):
		self.mock_uart = MockUart()
		self.mock_system = MockSystem(self.mock_uart)
		self.receiver = Receiver(self.mock_system)

	def test_receive_retrieves_all_data_from_the_uart(self):
		self.mock_uart.buffer = [b'Hello World']

		data = self.receiver.receive(self.mock_uart)

		assert(data == b'Hello World')

	def test_receiver_waits_for_further_data(self):
		self.mock_uart.buffer = [b'Hello ', b'World']

		data = self.receiver.receive(self.mock_uart)

		assert(data == b'Hello World')