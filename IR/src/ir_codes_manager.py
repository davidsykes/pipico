import json

class IrCodesManager:
	def __init__(self, network):
		self.network = network

		codes_url = self.network.get_url('codes')
		codes_json = self.network.get(codes_url)
		codes = json.loads(codes_json)

		self.codes = {}
		for code in codes:
			self.codes[str(code['code'])] =  code['waveform']

	def get_code(self, code):
		return self.codes[code]