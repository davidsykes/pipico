from mockpin import MockInputPin, MockOutputPin, MockIrReceivePin
from mocknetwork import MockNetwork

class MockTimer:
    def __init__(self):
        pass

    def init(self, freq, mode, callback):
        pass

class MockInternalTemperatureSensor:
    def read_u16(self):
        return 33

class MockSystem:
    _ticks = 0
    be_a_temperature_sensor = True
    transmit_ir_codes = True
    dump_ir_codes = False

    def __init__(self):
        self.id = 'MockSystem'
        self.pins = {}
        self.pins['LED'] = MockOutputPin()
        self.pins['14'] = MockOutputPin()
        self.pins['15'] = MockIrReceivePin(self)
        self.pins['5'] = MockInputPin(self.be_a_temperature_sensor)
        self.pins['4'] = MockInputPin(self.transmit_ir_codes)
        self.pins['3'] = MockInputPin(self.dump_ir_codes)
        self.pins['2'] = MockInputPin(False)

    def initialise_network(self):
        return MockNetwork()

    def make_output_pin(self, name):
        return self.make_pin(name)

    def make_input_pin(self, name, pullup=None):
        return self.make_pin(name)

    def make_pin(self, name):
        name = str(name)
        if name in self.pins:
            return self.pins[name]
        raise Exception(''.join(['Pin ', name, ' has not been defined']))

    def make_timer(self):
        return MockTimer()

    def ticks_us(self):
        self._ticks = self._ticks + 1
        return self._ticks

    def init_timer(self, timer, freq, callback):
        pass

    def get_internal_temperature_sensor(self):
        return MockInternalTemperatureSensor()