from url_request_decoder import UrlRequestDecoder

class Listener:
	def __init__(self, network, transmitter, codes):
		self.network = network
		self.request_decoder = UrlRequestDecoder()
		self.codes = codes

	def listen(self):
		self.listen2(self.code)

	def listen2(self, action):
		socket = self.network.open_socket()

		# Listen for connections
		while True:
			try:
				cl, addr = self.network.accept(socket)
				print('==================================')
				print('client connected from', addr)

				request = self.network.recv(cl)
				print('Request',request)

				html = action(request)
				#print(html)

				if html is None:
					cl.send('HTTP/1.0 404 Bad Request\r\nContent-type: text/html\r\n\r\n')
				else:
					cl.send('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
					cl.send(html)
        
			except OSError as e:
				print('connection closed')
			except KeyboardInterrupt as e:
				print("Close socket")
				socket.close()
				raise
			finally:
				cl.close()

	def code(self, http_request):
		request = self.request_decoder.decode_request(http_request)
		print("ACTION", request.type, request.url)
		return self.action(request.type, request.url)

	def action(self, type, url):
		if type == 'GET' and url == '/':
			html = """<!DOCTYPE html>
				<html>
					<head> <link rel="icon" href="data:,"> <title>Hello Oliver</title> </head>
					<body> <h1>Hello Oliver</h1>
"""
			for code in self.codes:
				#print(code)
				html = html + '<p><a href="/code/' + str(code['code']) + '">Code ' + str(code['code']) + '</a></p>' + "\n"

			html = html + """</body>
				</html>
			"""
			#print(html)
			return html
		print('INVALID REQUEST', type, url)