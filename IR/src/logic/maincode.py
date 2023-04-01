import sys
from localsettings import LocalSettings
from service_access import ServiceAccess
from flasher import Flasher
from toggler import Toggler
from configuration_switches import ConfigurationSwitches

IR_RECEIVE_PIN = 15
IR_TRANSMIT_PIN = 14

class MainCode:
    def maincode(self, system):
        self.system = system
        self.set_up_flasher()
        network_options = None
        self.set_up_network()

        self.flasher.set_status(1)
        configuration_switches = ConfigurationSwitches(self.system, self.service_access)

        self.log_configuration_switches(configuration_switches.string_format)

        if configuration_switches.be_a_temperature_sensor:
            self.service_access.log('Be a temperature sensor')
            from temperature_sensor import TemperatureSensor
            sensor = TemperatureSensor(system)
            sensor.sense()
        elif configuration_switches.are_we_a_listener:
            self.service_access.log('Be a listener')
            from controller import Controller
            ir_output = self.system.make_output_pin(IR_TRANSMIT_PIN)
            self.toggler = Toggler(self.system, ir_output)
            controller = Controller(self.system,
                        self.network,
                        self.service_access,
                        ir_output)
            controller.control()
        else:
            self.service_access.log('Be a recorder')
            from ir_recorder import IRRecorder
            recorder = IRRecorder(system, self.service_access, IR_RECEIVE_PIN)
            recorder.record(configuration_switches.dump_raw_ir_codes)

    def set_up_flasher(self):
        self.flasher = Flasher(self.system)

    def set_up_network(self):
        self.flasher.set_status(2)
        self.network = self.system.initialise_network()
        self.flasher.set_status(3)
        server_url = LocalSettings.ServerUrl
        self.service_access = ServiceAccess(self.network, server_url)
        if self.network.connected:
            self.flasher.set_status(4)
            try:
                self.service_access.log('Pico available on ip ' + self.network.ip_address)
            except OSError as e:
                print('The service may be down:', e)
                sys.exit()
        else:
            return
        network_options = self.service_access.get_network_options()
        self.flasher.set_sequence([10,10])

    def log_configuration_switches(self, switches):
        self.service_access.log('Configuration switches: ' + switches)