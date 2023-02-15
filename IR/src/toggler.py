

class Toggler:
	def __init__(self, system, pin):
		self.system = system
		self.pin = pin
		self.timer = self.system.make_timer()
		self.system.init_timer(self.timer, 50, self.blink)

	def blink(self, timer):
		self.pin.toggle()
