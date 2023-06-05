import sys
from service_access import ServiceAccess
from flasher import Flasher
from configuration_retriever import ConfigurationRetriever

IR_RECEIVE_PIN = 15
IR_TRANSMIT_PIN = 14
ServerUrl = 'http://192.168.1.142:5001'

class MainCode:
    def maincode(self, system):
        self.system = system
        self.set_up_flasher()
        self.service_access = ServiceAccess(system, ServerUrl)

        self.flasher.set_status(1)
        configuration = ConfigurationRetriever(self.service_access).retrieve_configuration()

        if configuration == 'irrecorder':
            self.service_access.log('IR recorder')
            from ir_recorder import IRRecorder
            recorder = IRRecorder(system, self.service_access, IR_RECEIVE_PIN)
            recorder.record(configuration_switches.dump_raw_ir_codes)
        else:
            self.service_access.log('IR Transmitter')
            from controller import Controller
            ir_output = self.system.make_output_pin(IR_TRANSMIT_PIN)
            controller = Controller(self.system,
                        self.service_access,
                        ir_output)
            controller.control()

    def set_up_flasher(self):
        self.flasher = Flasher(self.system)
