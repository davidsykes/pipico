class IrTransmitter:
	def __init__(self, system, output_pin):
		self.system = system
		self.output_pin = output_pin

	def transmit(self, waveform):
		points = waveform.points
		point_count = len(points)
		times = []
		values = []
		for i in range(point_count):
			times.append(points[i].time)
			values.append(points[i].value)
			print(i, times[i], values[i])

		current_point = 0
		start_time = self.system.ticks_us()
		while current_point < point_count:
			next_time = start_time + times[current_point]
			while self.system.ticks_us() < next_time:
				pass
			self.output_pin.value(values[current_point])
			current_point = current_point + 1