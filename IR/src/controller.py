import traceback
import sys
from listener import Listener
from ir_transmitter import IrTransmitter
from ir_codes_manager import IrCodesManager
from client_action_home import ClientActionHome
from client_action_codes import ClientActionCodes
from client_action_router import ClientActionRouter
from localsettings import LocalSettings

class Controller:
	def __init__(self, system, network, logger, ir_output, ir_input):
		self.system = system
		self.network = network
		self.logger = logger
		self.ir_output = ir_output
		self.ir_input = ir_input
	def control(self):
		try:
			codes = IrCodesManager(self.network)
			home_action = ClientActionHome(codes)
			transmitter = IrTransmitter(self.system, self.ir_output, self.ir_input)
			codes_action = ClientActionCodes(codes, transmitter, home_action)
			router = ClientActionRouter(home_action, codes_action)
			listener = Listener(self.network, router)
			listener.listen()
		except Exception as e:
			trace = traceback.format_exc()
			if LocalSettings.LogExceptions:
				self.logger.log('Exception: '+ trace)
			else:
				print(trace)
