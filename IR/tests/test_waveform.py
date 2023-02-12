import sys
sys.path.append('../src/wave_forms')
from waveform import Waveform

class TestWaveform:
	def setup_method(self, test_method):
		test_data = {'code': 2911, 'waveform': [{'t': 0, 'v': 0}, {'t': 2416, 'v': 1}, {'t': 2973, 'v': 0}]}
		self.waveform = Waveform(test_data)

	def test_initialisation(self):
		assert(self.waveform.code == '2911')
		assert(self.waveform.points[0].time == 0)
		assert(self.waveform.points[0].value == 0)
		assert(self.waveform.points[1].time == 2416)
		assert(self.waveform.points[1].value == 1)
		assert(self.waveform.points[2].time == 2973)
		assert(self.waveform.points[2].value == 0)
