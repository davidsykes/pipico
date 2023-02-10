import re

class ClientActionCodes:
	def __init__(self, codes, transmitter, home_action):
		self.codes = codes
		self.transmitter = transmitter
		self.home_action = home_action
	def action(self, url):
		x = re.search('/code/([\\w]+)', url)
		if x:
			code_name = x.group(1)
			code = self.codes.get_code(code_name)
			self.transmitter.transmit(code)
			return self.home_action.action()
		return ''.join(['<h1>INVALID CODE ', url, '</h1>'])
