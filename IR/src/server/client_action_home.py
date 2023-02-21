from urllib.parse import quote

class ClientActionHome:
	def __init__(self, codes):
		self.sequences = codes.get_sequence_names()
	def action(self):
		html = '<h1>Push My Button</h1>'
		for sequence in self.sequences:
			seqeunce_quoted = quote(sequence)
			html = html + ''.join(['<p><a href="/sequence/', seqeunce_quoted, '">', sequence, '</a></p>'])
		return html