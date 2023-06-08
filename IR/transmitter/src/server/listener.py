from ir_exception import IrException

class Listener:
	def __init__(self, system, connection_handler, logger):
		self.system = system
		self.connection_handler = connection_handler
		self.logger = logger

	def listen(self):
		socket = self.system.open_socket()

		# Listen for connections
		cl = None
		while True:
			try:
				cl, addr = self.system.accept(socket)
				print('==================================')
				print('client connected from', addr)

				self.connection_handler.request(cl)
       
			except OSError as e:
				print('Connection closed')
				raise
			except KeyboardInterrupt as e:
				print("Close socket")
				socket.close()
				raise
			except IrException as e:
				self.logger.log(''.join(['Request exception: ', str(e)]))
			finally:
				if (cl is not None):
					cl.close()
