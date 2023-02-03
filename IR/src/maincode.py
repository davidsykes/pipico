from pinwatcher import PinWatcher
from waveanalyser import WaveAnalyser
from network_wrapper import Network

class MainCode:
    led = None

    def blink(self, timer):
        self.led.toggle()

    def maincode(self, system, network_layer):
        self.led = system.MakeOutputPin("LED")
        ir = system.MakeOutputPin(10)
        ir.on()
        timer = system.MakeTimer()
        button = system.MakeInputPin(15)
        watcher = PinWatcher(system, button)
        analyser = WaveAnalyser()
        network = None

        switch1 = system.MakeInputPin(5, False)    #   Enable flash
        switch2 = system.MakeInputPin(4, False)    #   Enable network
        switch3 = system.MakeInputPin(3, False)    #   Enable ir detector
        switch4 = system.MakeInputPin(2, False)    #   Send raw IR to the server
        print('Switches', switch1.value(), switch2.value(), switch3.value(), switch4.value())

        if (switch1.value()):
            system.init_timer(timer, 0.5, self.blink)

        network_options = None
        if (switch2.value()):
            self.network = Network(network_layer)
            self.network.initialise()
            network_options = self.network.get_network_options()

        if (switch3.value()):
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
                        if (len(signal_values) > 1):
                            if (switch4.value()):
                                self.dump_ir(signal_times, signal_values)
                            else:
                                self.analyse(signal_times, signal_values, analyser)
                        receiving = False

    def analyse(self, signal_times, signal_values, analyser):
        data = self.convert_data(signal_times, signal_values)
        result = analyser.analyse(data)
        self.network.put('key', result)

    def dump_ir(self, signal_times, signal_values):
        data = self.convert_data(signal_times, signal_values)
        self.network.put('dump', data)

    def convert_data(self, signal_times, signal_values):
        data = []
        for i in range(0, len(signal_times)):
            d = []
            d.append(signal_times[i])
            d.append(signal_values[i])
            data.append(d)
        return data