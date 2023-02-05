class Listener:
	def __init__(self, network):
		self.network = network
		codes_url = network.get_url('codes')
		codes_json = network.get(codes_url)
		self.codes = json.loads(codes_json)

	def listen(self):
		self.network.listen()