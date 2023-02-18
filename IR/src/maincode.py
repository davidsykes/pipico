from pinwatcher import PinWatcher
from waveanalyser import WaveAnalyser
from localsettings import LocalSettings
#from network_wrapper import Network
from service_access import ServiceAccess
from flasher import Flasher
from toggler import Toggler

SWITCH_1_PIN = 5
SWITCH_2_PIN = 4
SWITCH_3_PIN = 3
SWITCH_4_PIN = 2
IR_RECEIVE_PIN = 15

class MainCode:
    def maincode(self, system, network_layer):
        self.flasher = Flasher(system)
        ir_output = system.make_output_pin(14)
        self.toggler = Toggler(system, ir_output)
        ir_receive_pin = system.make_input_pin(IR_RECEIVE_PIN)
        watcher = PinWatcher(system, ir_receive_pin)
        analyser = WaveAnalyser()

        # Check configuration switches
        network_switch = system.make_input_pin(SWITCH_1_PIN, False)       #   Enable network
        network_type_switch = system.make_input_pin(SWITCH_2_PIN, False)  #   0 = dumper, 1 = listener
        switch3 = system.make_input_pin(SWITCH_3_PIN, False)              #
        switch4 = system.make_input_pin(SWITCH_4_PIN, False)              #
        print('Switches', network_switch.value(), network_type_switch.value(), switch3.value(), switch4.value())

        network_options = None
        if (network_switch.value()):
            server_url = LocalSettings.ServerUrl
            self.service_access = ServiceAccess(network_layer, server_url)
            self.flasher.set_sequence([1,5])
            if network_layer.connected:
                self.flasher.set_sequence([1,1,1,5])
                self.service_access.log('Internet connected')
            else:
                return
            network_options = self.service_access.get_network_options()
            self.flasher.set_sequence([10,10])

        if (network_type_switch.value()):
            from controller import Controller
            controller = Controller(system,
                        network_layer,
                        self.service_access,
                        ir_output)
            controller.control()
        else:
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
                            if (switch4.value()):
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