

class Flasher:
	def __init__(self, system):
		self.system = system
		self.led = self.system.make_output_pin("LED")
		self.timer = self.system.make_timer()
		self.system.init_timer(self.timer, 5, self.blink)
		self.set_sequence([1,1])

	def blink(self, timer):
		self.led.toggle()

	def flash_slow(self):
		self.system.init_timer(self.timer, 0.5, self.blink)

	def set_sequence(self, sequence):
		self.sequence = sequence
		self.current_step = 0
		self.current_count = 0