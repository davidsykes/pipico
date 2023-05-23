import sys
sys.path.append('../src')
from receiver import Receiver

class MockUart:
	def __init__(self):
		self.current_time = 0
		self.current_packet = 0
		self.current_char = 0

	def set_buffer(self, data):
		self.buffer = data

	def any(self):
		return self.is_there_data_left_to_read()

	def read(self):
		if self.is_there_data_left_to_read():
			return self.read_next_character()
		
	def get_current_packet_data(self):
		return self.buffer[self.current_packet][1]

	def is_there_data_left_to_read(self):
		packet_data = self.get_current_packet_data()
		return self.current_char < len(packet_data)

	def read_next_character(self):
		packet_data = self.get_current_packet_data()
		char = packet_data[self.current_char:self.current_char+1]
		self.move_to_next_character()
		return char
	
	def move_to_next_character(self):
		packet_data = self.get_current_packet_data()
		if self.current_char < len(packet_data):
			self.current_char = self.current_char + 1

	def check_for_next_packet(self, sleep_time):
		self.current_time += sleep_time
		if self.current_packet < (len(self.buffer)-1):
			time_of_next_packet = self.buffer[self.current_packet+1][0]
			if self.current_time >= time_of_next_packet:
				self.current_packet = self.current_packet + 1
				self.current_char = 0

class MockSystem:
	def __init__(self, uart):
		self.uart = uart
	def sleep(self, s):
		self.uart.check_for_next_packet(s)

class TestReceiver:
	def setup_method(self, test_method):
		self.mock_uart = MockUart()
		self.mock_system = MockSystem(self.mock_uart)
		self.receiver = Receiver(self.mock_system)

	def test_receive_retrieves_data_from_the_uart(self):
		self.mock_uart.set_buffer([[0, b'Hello World']])

		data = self.receiver.receive(self.mock_uart)

		assert(data == b'Hello World')

	def test_receiver_waits_up_to_100ms_for_further_data(self):
		self.mock_uart.set_buffer([[0, b'Hello '], [0.1, b'World']])

		data = self.receiver.receive(self.mock_uart)

		assert(data == b'Hello World')

	def test_receiver_waits_only_100ms_for_further_data(self):
		self.mock_uart.set_buffer([[0, b'Hello '], [0.101, b'World']])

		data = self.receiver.receive(self.mock_uart)

		assert(data == b'Hello ')

	def test_receiver_waits_up_to_100ms_from_last_packet_for_further_data(self):
		self.mock_uart.set_buffer([[0, b'Hell'], [0.1, b'o '], [0.2, b'World']])

		data = self.receiver.receive(self.mock_uart)

		assert(data == b'Hello World')

	def test_receiver_waits_only_100ms_from_last_packet_for_further_data(self):
		self.mock_uart.set_buffer([[0, b'Hell'], [0.1, b'o '], [0.201, b'World']])

		data = self.receiver.receive(self.mock_uart)

		assert(data == b'Hello ')