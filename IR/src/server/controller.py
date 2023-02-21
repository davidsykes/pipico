import sys
from listener import Listener
from ir_transmitter import IrTransmitter
from waveforms_manager import WaveformsManager
from client_action_home import ClientActionHome
from client_action_codes import ClientActionCodes
from client_action_router import ClientActionRouter
from localsettings import LocalSettings

class Controller:
	def __init__(self, system, network, service_access, ir_output):
		self.system = system
		self.network = network
		self.service_access = service_access
		self.ir_output = ir_output

	def control(self):
		try:
			waveforms = WaveformsManager(self.service_access)
			home_action = ClientActionHome(waveforms)
			transmitter = IrTransmitter(self.system, self.ir_output)
			codes_action = ClientActionCodes(waveforms, transmitter, home_action)
			router = ClientActionRouter(home_action, codes_action, self.service_access)
			listener = Listener(self.network, router, self.service_access)
			listener.listen()
		except Exception as e:
			self.log_exception('Exception', e)

	def log_exception(self, message, e):
			if LocalSettings.LogExceptions:
				self.system.log_exception(self.service_access, message, e)
			else:
				import traceback
				print(message)
				print(traceback.format_exc())