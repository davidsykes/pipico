from listener import Listener
from ir_transmitter import IrTransmitter
from ir_codes_manager import IrCodesManager
from client_action_home import ClientActionHome
from client_action_codes import ClientActionCodes
from client_action_router import ClientActionRouter

class Controller:
	def __init__(self, network, logger):
		self.network = network
		self.logger = logger
	def control(self):
		try:
			transmitter = IrTransmitter()
			codes = IrCodesManager(self.network)
			home_action = ClientActionHome(codes)
			transmitter = IrTransmitter()
			codes_action = ClientActionCodes(codes, transmitter, home_action)
			router = ClientActionRouter(home_action, codes_action)
			listener = Listener(self.network, router)
			listener.listen()
		except Exception as e:
			self.logger.log('Exception: '+ str(e))