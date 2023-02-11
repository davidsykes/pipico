

class Flasher:
	def __init__(self, system):
		self.system = system
		self.led = self.system.MakeOutputPin("LED")
		self.timer = self.system.MakeTimer()
		self.system.init_timer(self.timer, 5, self.blink)

	def blink(self, timer):
		self.led.toggle()

	def flash_slow(self):
		self.system.init_timer(self.timer, 0.5, self.blink)
		