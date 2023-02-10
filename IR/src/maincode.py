from pinwatcher import PinWatcher
from waveanalyser import WaveAnalyser
from network_wrapper import Network
from flasher import Flasher

SWITCH_1_PIN = 5
SWITCH_2_PIN = 4
SWITCH_3_PIN = 3
SWITCH_4_PIN = 2

class MainCode:

    def maincode(self, system, network_layer):
        self.flasher = Flasher(system)
        ir = system.MakeOutputPin(14)
        ir.on()
        button = system.MakeInputPin(15)
        watcher = PinWatcher(system, button)
        analyser = WaveAnalyser()
        network = None

        network_switch = system.MakeInputPin(SWITCH_1_PIN, False)       #   Enable network
        network_type_switch = system.MakeInputPin(SWITCH_2_PIN, False)  #   0 = dumper, 1 = listener
        switch3 = system.MakeInputPin(SWITCH_3_PIN, False)              #   
        switch4 = system.MakeInputPin(SWITCH_4_PIN, False)              #   Send raw IR to the server
        print('Switches', network_switch.value(), network_type_switch.value(), switch3.value(), switch4.value())

        network_options = None
        if (network_switch.value()):
            self.network = Network(network_layer, 'http://192.168.1.87:5000')
            self.network.initialise()
            network_options = self.network.get_network_options()
            self.flasher.flash_slow()

        if (network_type_switch.value()):
            from controller import Controller
            Controller(self.network, Logger(self.network).control()
        else:
            while True:
                print("Value = ", watcher.value())
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
        url = self.get_url('ir')
        data = {'code': result, 'wavepoints' : wave_data}
        self.network.put(url, data)

    def dump_ir(self, signal_times, signal_values):
        wave_data = self.convert_data(signal_times, signal_values)
        url = self.get_url('irdump')
        data = {'code': 0, 'wavepoints' : wave_data}
        self.network.put(url, data)

    def convert_data(self, signal_times, signal_values):
        data = []
        for i in range(0, len(signal_times)):
            d = []
            d.append(signal_times[i])
            d.append(signal_values[i])
            data.append(d)
        return data