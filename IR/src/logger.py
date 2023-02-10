
class Logger:
	def __init__(self, network):
		self.network = network

	def log(self, message):
		url = self.network.get_url('log')
		self.network.put(url, message)