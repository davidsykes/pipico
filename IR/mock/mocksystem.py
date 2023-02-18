from mockpin import MockInputPin, MockOutputPin, MockIrReceivePin

class MockTimer:
    def __init__(self):
        pass

    def init(self, freq, mode, callback):
        pass

class MockSystem:
    _ticks = 0
    enable_network = True
    transmit_ir_codes = True

    def __init__(self):
        self.pins = {}
        self.pins['LED'] = MockOutputPin()
        self.pins['14'] = MockOutputPin()
        self.pins['15'] = MockIrReceivePin(self)
        self.pins['5'] = MockInputPin(self.enable_network)
        self.pins['4'] = MockInputPin(self.transmit_ir_codes)
        self.pins['3'] = MockInputPin(False)
        self.pins['2'] = MockInputPin(False)

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