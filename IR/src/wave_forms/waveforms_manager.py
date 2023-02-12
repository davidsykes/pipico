import json
from waveform import Waveform

class WaveformsManager:
	def __init__(self, network):
		self.network = network

		codes_url = self.network.get_url('codes')
		codes_json = self.network.get(codes_url)
		codes = json.loads(codes_json)

		self.codes = {}
		self.names = []
		for code in codes:
			waveform = Waveform(code)
			name = waveform.code
			self.codes[name] = waveform
			self.names.append(name)

	def get_code(self, code):
		return self.codes[code]

	def get_code_names(self):
		return self.names