import json
from waveform import Waveform
from ir_exception import IrException

class WaveformsManager:
	def __init__(self, network):
		self.network = network
		self.load_sequence_data()

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

	def load_sequence_data(self):
		sequences_url = self.network.get_url('sequences')
		sequences_json = self.network.get(sequences_url)
		sequences = json.loads(sequences_json)['sequences']

		self.sequences = {}
		for s in sequences:
			self.sequences[s['name']] = s['codes']

	def get_sequence_names(self):
		return list(self.sequences.keys())

	def get_sequence(self, sequence_name):
		return self.sequences[sequence_name]

	def get_code(self, code):
		if code in self.codes:
			return self.codes[code]
		raise IrException(''.join(["Code '", code, "' not found'"]))

	def get_code_names(self):
		return self.names