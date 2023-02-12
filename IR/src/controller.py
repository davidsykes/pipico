import sys
from listener import Listener
from ir_transmitter import IrTransmitter
from waveforms_manager import WaveformsManager
from client_action_home import ClientActionHome
from client_action_codes import ClientActionCodes
from client_action_router import ClientActionRouter
from localsettings import LocalSettings

class Controller:
	def __init__(self, system, network, logger, ir_output):
		self.system = system
		self.network = network
		self.logger = logger
		self.ir_output = ir_output
	def control(self):
		try:
			waveforms = WaveformsManager(self.network)
			home_action = ClientActionHome(waveforms)
			transmitter = IrTransmitter(self.system, self.ir_output)
			codes_action = ClientActionCodes(waveforms, transmitter, home_action)
			router = ClientActionRouter(home_action, codes_action, self.logger)
			listener = Listener(self.network, router)
			listener.listen()
		except Exception as e:
			if LocalSettings.LogExceptions:
				#self.logger.log('Exception: '+ trace)
				sys.print_exception(e)
			else:
				sys.print_exception(e)
