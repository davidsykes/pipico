import re
from url_parser import UrlParser

class ClientActionSequences:
	def __init__(self, waveform_manager, transmitter, home_action):
		self.waveform_manager = waveform_manager
		self.transmitter = transmitter
		self.home_action = home_action
	def action(self, url):
		x = re.search('/sequence/(.+)', url)
		if x:
			sequence_name_quoted = x.group(1)
			sequence_name = UrlParser.unquote(sequence_name_quoted)
			sequence_codes = self.waveform_manager.get_sequence(sequence_name)
			for code_name in sequence_codes:
				code = self.waveform_manager.get_code(code_name)
				self.transmitter.transmit(code)
			return self.home_action.action()
		return ''.join(['<h1>INVALID SEQUENCE ', url, '</h1>'])