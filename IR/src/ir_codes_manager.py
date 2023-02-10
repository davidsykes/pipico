import json

class IrCodesManager:
	def __init__(self, network):
		self.network = network

		codes_url = self.network.get_url('codes')
		codes_json = self.network.get(codes_url)
		codes = json.loads(codes_json)

		self.codes = {}
		self.names = []
		for code in codes:
			name = str(code['code'])
			self.names.append(name)
			self.codes[name] =  code['waveform']

	def get_code(self, code):
		return self.codes[code]

	def get_code_names(self):
		return self.names