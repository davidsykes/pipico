class IrTransmitter:
	def __init__(self, system, output_pin):
		self.system = system
		self.output_pin = output_pin

	def transmit(self, waveform):
		start_time = self.system.ticks_us()
		points = waveform.points
		point_count = len(points)
		current_point = 0
		while current_point < point_count:
			next_time = start_time + points[current_point].time
			while self.system.ticks_us() < next_time:
				pass
			self.output_pin.value(points[current_point].value)
			current_point = current_point + 1