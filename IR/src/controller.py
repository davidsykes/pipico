import sys
import io
from listener import Listener
from ir_transmitter import IrTransmitter
from waveforms_manager import WaveformsManager
from client_action_home import ClientActionHome
from client_action_codes import ClientActionCodes
from client_action_router import ClientActionRouter
from localsettings import LocalSettings
from logger import Logger

class Controller:
	def __init__(self, system, network, service_access, ir_output):
		self.system = system
		self.network = network
		self.service_access = service_access
		self.logger = Logger(service_access)
		self.ir_output = ir_output

	def control(self):
		try:
			waveforms = WaveformsManager(self.service_access)
			home_action = ClientActionHome(waveforms)
			transmitter = IrTransmitter(self.system, self.ir_output)
			codes_action = ClientActionCodes(waveforms, transmitter, home_action)
			router = ClientActionRouter(home_action, codes_action, self.logger)
			listener = Listener(self.network, router)
			listener.listen()
		except Exception as e:
			if LocalSettings.LogExceptions:
				string_stream = io.StringIO('')
				sys.print_exception(e, string_stream)
				self.logger.log('Exception: '+ string_stream.getvalue())
			else:
				import traceback
				print(traceback.format_exc())