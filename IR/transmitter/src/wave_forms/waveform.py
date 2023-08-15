class WaveformPoint:
	def __init__(self, time, value):
		self.time = time
		self.value = value

class Waveform:
	def __init__(self, data):
		self.code = str(data['code'])
		points = data['waveform']
		self.points = [WaveformPoint(p['t'], p['v']) for p in points]
