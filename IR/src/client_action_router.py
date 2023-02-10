class ClientActionRouter:
	def __init__(self, home_action, codes_action):
		self.home_action = home_action
		self.codes_action = codes_action
	def action(self, type, url):
		if (url == '/'):
			return self.home_action.action()
		elif (url[0:5] == '/code'):
			return self.codes_action.action(url)
		print('INVALID REQUEST', type, url)
