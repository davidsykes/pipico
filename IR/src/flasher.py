

class Flasher:
	def __init__(self, system):
		self.led = system.MakeOutputPin("LED")
		timer = system.MakeTimer()
		system.init_timer(timer, 0.5, self.blink)

	def blink(self, timer):
		self.led.toggle()

	def flash_slow(self):
		pass
		