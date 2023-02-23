class UrlParser:
	@staticmethod
	def quote(string):
		return string.replace(' ', '%20')

	@staticmethod
	def unquote(string):
		return string.replace('%20', ' ')