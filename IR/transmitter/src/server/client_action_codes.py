import re
from url_parser import UrlParser

class ClientActionCodes:
	def __init__(self, codes, transmitter, home_action):
		self.codes = codes
		self.transmitter = transmitter
		self.home_action = home_action
	def action(self, url):
		x = re.search('/code/(.+)', url)
		if x:
			code_name_quoted = x.group(1)
			code_name = UrlParser.unquote(code_name_quoted)
			code = self.codes.get_code(code_name)
			self.transmitter.transmit(code)
			return self.home_action.action()
		return ''.join(['<h1>INVALID CODE ', url, '</h1>'])
