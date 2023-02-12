from url_request_decoder import UrlRequestDecoder

class Listener:
	def __init__(self, network, router):
		self.network = network
		self.request_decoder = UrlRequestDecoder()
		self.router = router

	def listen(self):
		socket = self.network.open_socket()

		# Listen for connections
		cl = None
		while True:
			try:
				cl, addr = self.network.accept(socket)
				print('==================================')
				print('client connected from', addr)

				request = self.network.recv(cl)

				html = self.code(request)

				if html is None:
					cl.send('HTTP/1.0 404 Bad Request\r\nContent-type: text/html\r\n\r\n')
				else:
					cl.send('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
					cl.send(html)
        
			except OSError as e:
				print('Connection closed')
				raise
			except KeyboardInterrupt as e:
				print("Close socket")
				socket.close()
				raise
			finally:
				if (cl is not None):
					cl.close()

	def code(self, http_request):
		request = self.request_decoder.decode_request(http_request)
		print("ACTION", request.type, request.url)
		return self.router.action(request.type, request.url)
