from url_parser import UrlParser

class ClientActionHome:
	def __init__(self, waveforms):
		self.waveforms = waveforms
		self.sequences = waveforms.get_sequence_names()
		self.codes = waveforms.get_sequence_names()
	def action(self):
		html = '<h1>Push My Button</h1>'
		for sequence in self.waveforms.get_sequence_names():
			sequence_quoted = UrlParser.quote(sequence)
			html = html + ''.join(['<p style="font-size:70pt"><a href="/sequence/', sequence_quoted, '">', sequence, '</a></p>'])
		for code in self.waveforms.get_code_names():
			code_quoted = UrlParser.quote(code)
			html = html + ''.join(['<p style="font-size:30pt"><a href="/code/', code_quoted, '">', code, '</a></p>'])
		return html