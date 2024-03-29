class ClientActionRouter:
	def __init__(self, home_action, sequences_action, codes_action, logger):
		self.home_action = home_action
		self.sequences_action = sequences_action
		self.codes_action = codes_action
		self.logger = logger
	def action(self, action):
		type = action.type
		url = action.url
		if (url == '/'):
			return self.home_action.action()
		elif (url[0:9] == '/sequence'):
			return self.sequences_action.action(url)
		elif (url[0:5] == '/code'):
			return self.codes_action.action(url)
		elif (url == '/favicon.ico'):
			return None
		self.logger.log(''.join(['Invalid request: ', type, ' ', url]))
