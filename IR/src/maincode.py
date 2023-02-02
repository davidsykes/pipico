from pinwatcher import PinWatcher
from waveanalyser import WaveAnalyser
from network_wrapper import Network

led = None

def blink(timer):
    global led
    led.toggle()

def maincode(system, network_layer):
    global led
    led = system.MakeOutputPin("LED")
    ir = system.MakeOutputPin(10)
    ir.on()
    timer = system.MakeTimer()
    button = system.MakeInputPin(15)
    watcher = PinWatcher(system, button)
    analyser = WaveAnalyser()
    network = None

    switch1 = system.MakeInputPin(5)    #   Enable flash
    switch2 = system.MakeInputPin(4)    #   Enable network
    switch3 = system.MakeInputPin(3)    #   Enable ir detector
    switch4 = system.MakeInputPin(2)
    print('Switches', switch1.value(), switch2.value(), switch3.value(), switch4.value())

    if (switch1.value()):
        system.init_timer(timer, 0.5, blink)

    network_options = None
    if (switch2.value()):
        network = Network(network_layer)
        network.initialise()
        network_options = network.get_network_options()

    if (switch3.value()):
        while True:
            print("Value = ", watcher.value())
            watcher.wait_for_change()
            signal_values = [watcher.value()]
            signal_times = [0]
            receiving = True
            while(receiving):
                ctime = watcher.get_time_of_change(25000)
                if (ctime is not None):
                    signal_values.append(watcher.value())
                    signal_times.append(ctime)
                else:
                    if (len(signal_values) > 1):
                        analyse(signal_times, signal_values, analyser, network)
                        #print(len(signal_values), "values")
                        #print('[', end='')
                        #for i in range(0, len(signal_values)):
                        #    print('[',signal_times[i], ',', signal_values[i],']', end='')
                        #    if (i < len(signal_values)-1):
                        #        print(',', end='')
                        #print(']')
                        #print()
                    receiving = False

def analyse(signal_times, signal_values, analyser, network):
    data = []
    for i in range(0, len(signal_times)):
        d = []
        d.append(signal_times[i])
        d.append(signal_values[i])
        data.append(d)
    print('ddd', data)
    result = analyser.analyse(data)
    print('result', result)
    network.put('key', result, data)