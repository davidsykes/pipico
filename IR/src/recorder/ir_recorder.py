from pinwatcher import PinWatcher
from waveanalyser import WaveAnalyser


class IRRecorder:
    def __init__(self, system, service_access, ir_receive_pin_number):
        self.service_access = service_access
        ir_receive_pin = system.make_input_pin(ir_receive_pin_number)
        self.watcher = PinWatcher(system, ir_receive_pin)
        self.analyser = WaveAnalyser()

    def record(self, dump_raw_ir_codes):
        print('Wait for ir codes')
        self.service_access.log('Wait for an ir code')
        print("Wait for code")
        while True:
            self.watcher.wait_for_change()
            signal_values = [self.watcher.value()]
            signal_times = [0]
            receiving = True
            while(receiving):
                ctime = self.watcher.get_time_of_change(10000)
                if (ctime is not None):
                    signal_values.append(self.watcher.value())
                    signal_times.append(ctime)
                else:
                    if (len(signal_values) > 4):
                        if dump_raw_ir_codes:
                            self.dump_ir(signal_times, signal_values)
                        else:
                            self.analyse(signal_times, signal_values, self.analyser)
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
