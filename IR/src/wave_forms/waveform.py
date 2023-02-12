class WaveFormPoint:
	def __init__(self, time, value):
		self.time = time
		self.value = value

class WaveForm:
	def __init__(self, data):
		self.code = data['code']
		points = data['waveform']
		self.points = [WaveFormPoint(p['t'], p['v']) for p in points]
