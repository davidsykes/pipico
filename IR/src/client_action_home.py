class ClientActionHome:
	def __init__(self, codes):
		self.codes = codes.get_code_names()
	def action(self):
		html = '<h1>Push My Button</h1>'
		for code in self.codes:
			html = html + ''.join(['<p><a href="/code/', code, '">Code ', code, '</a></p>'])
		return html