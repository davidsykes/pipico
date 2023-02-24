from pinwatcher import PinWatcher
from waveanalyser import WaveAnalyser
from localsettings import LocalSettings
from service_access import ServiceAccess
from flasher import Flasher
from toggler import Toggler
from configuration_switches import ConfigurationSwitches

IR_RECEIVE_PIN = 15
IR_TRANSMIT_PIN = 14

class MainCode:
    def maincode(self, system):
        self.flasher = Flasher(system)
        ir_output = system.make_output_pin(IR_TRANSMIT_PIN)
        self.toggler = Toggler(system, ir_output)
        ir_receive_pin = system.make_input_pin(IR_RECEIVE_PIN)
        watcher = PinWatcher(system, ir_receive_pin)
        analyser = WaveAnalyser()
        network_options = None

        self.flasher.set_status(1)
        configuration_switches = ConfigurationSwitches(system)

        if configuration_switches.is_network_enabled:
            self.flasher.set_status(2)
            network = system.initialise_network()
            self.flasher.set_status(3)
            server_url = LocalSettings.ServerUrl
            self.service_access = ServiceAccess(network, server_url)
            if network.connected:
                self.flasher.set_status(4)
                self.service_access.log('Internet connected on ip ' + network.ip_address)
            else:
                return
            network_options = self.service_access.get_network_options()
            self.flasher.set_sequence([10,10])

        if configuration_switches.are_we_a_listener:
            print('do the control')
            from controller import Controller
            controller = Controller(system,
                        network,
                        self.service_access,
                        ir_output)
            controller.control()
        else:
            print('dont do the control')
            self.service_access.log('Wait for an ir code')
            print("Wait for code")
            while True:
                watcher.wait_for_change()
                signal_values = [watcher.value()]
                signal_times = [0]
                receiving = True
                while(receiving):
                    ctime = watcher.get_time_of_change(10000)
                    if (ctime is not None):
                        signal_values.append(watcher.value())
                        signal_times.append(ctime)
                    else:
                        if (len(signal_values) > 4):
                            if configuration_switches.dump_raw_ir_codes:
                                self.dump_ir(signal_times, signal_values)
                            else:
                                self.analyse(signal_times, signal_values, analyser)
                        receiving = False

    def analyse(self, signal_times, signal_values, analyser):
        wave_data = self.convert_data(signal_times, signal_values)
        result = analyser.analyse(wave_data)
        print('Put data for code', result)
        self.service_access.send_ir_code(result, wave_data)

    def dump_ir(self, signal_times, signal_values):
        wave_data = self.convert_data(signal_times, signal_values)
        self.service_access.send_ir_code(0, wave_data)

    def convert_data(self, signal_times, signal_values):
        data = []
        for i in range(0, len(signal_times)):
            d = []
            d.append(signal_times[i])
            d.append(signal_values[i])
            data.append(d)
        return data