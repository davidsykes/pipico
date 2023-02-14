

class Flasher:
	def __init__(self, system):
		self.system = system
		self.led = self.system.make_output_pin("LED")
		self.timer = self.system.make_timer()
		self.system.init_timer(self.timer, 5, self.blink)
		self.set_sequence([1,1])

	def blink(self, timer):
		if self.sequence is None:
			return
		if len(self.sequence) == 0:
			return

		if self.does_the_sequence_need_initialising():
			self.led.value(1)
			self.current_step = 0
			self.current_count = 0
		else:
			self.current_count = self.current_count + 1
			if self.have_we_reached_the_end_of_this_step():
				self.led.toggle()
				self.move_to_next_sequence()

	def does_the_sequence_need_initialising(self):
		return self.current_step is None

	def have_we_reached_the_end_of_this_step(self):
		return self.current_count >= self.sequence[self.current_step]

	def move_to_next_sequence(self):
		self.current_step = self.current_step + 1
		if self.current_step >= len(self.sequence):
			self.current_step = 0
		self.current_count = 0

	def set_sequence(self, sequence):
		self.sequence = sequence
		self.current_step = None
