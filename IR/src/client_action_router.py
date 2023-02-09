class ClientActionRouter:
	def __init__(self, codes):
		self.codes = codes
	def action(self, type, url):
		self.codes.action(url)