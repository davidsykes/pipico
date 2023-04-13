import sys
from service_access import ServiceAccess
from flasher import Flasher
from configuration_switches import ConfigurationSwitches

IR_RECEIVE_PIN = 15
IR_TRANSMIT_PIN = 14
ServerUrl = 'http://192.168.1.87:5000'

class MainCode:
    def maincode(self, system):
        self.system = system
        self.set_up_flasher()
        self.service_access = ServiceAccess(system, ServerUrl)

        self.flasher.set_status(1)
        configuration_switches = ConfigurationSwitches(self.system, self.service_access)

        self.log_configuration_switches(configuration_switches.string_format)

        if configuration_switches.are_we_ir_transmitter:
            self.service_access.log('IR Transmitter')
            from controller import Controller
            ir_output = self.system.make_output_pin(IR_TRANSMIT_PIN)
            controller = Controller(self.system,
                        self.service_access,
                        ir_output)
            controller.control()
        else:
            self.service_access.log('IR recorder')
            from ir_recorder import IRRecorder
            recorder = IRRecorder(system, self.service_access, IR_RECEIVE_PIN)
            recorder.record(configuration_switches.dump_raw_ir_codes)

    def set_up_flasher(self):
        self.flasher = Flasher(self.system)

    def log_configuration_switches(self, switches):
        self.service_access.log('Configuration switches: ' + switches)