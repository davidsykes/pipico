import sys
from listener import Listener
from ir_transmitter import IrTransmitter
from waveforms_manager import WaveformsManager
from client_action_home import ClientActionHome
from client_action_sequences import ClientActionSequences
from client_action_codes import ClientActionCodes
from client_action_router import ClientActionRouter

class Controller:
	def __init__(self, system, service_access, ir_output):
		self.system = system
		self.service_access = service_access
		self.ir_output = ir_output

	def control(self):
		print('Set up the ir controller')
		try:
			waveforms = WaveformsManager(self.service_access)
			home_action = ClientActionHome(waveforms)
			transmitter = IrTransmitter(self.system, self.ir_output)
			sequences_action = ClientActionSequences(waveforms, transmitter, home_action)
			codes_action = ClientActionCodes(waveforms, transmitter, home_action)
			router = ClientActionRouter(home_action, sequences_action, codes_action, self.service_access)
			listener = Listener(self.system, router, self.service_access)
			self.service_access.log('Wait for sequence requests')
			listener.listen()
		except Exception as e:
			self.log_exception('Exception', e)

	def log_exception(self, message, e):
			self.system.log_exception(self.service_access, message, e)
