from mockpin import MockPin

class MockTimer:
    def __init__(self):
        pass

    def init(self, freq, mode, callback):
        pass

class MockSystem:
    _ticks = 0

    def make_output_pin(self, name):
        return MockPin(name, self)

    def make_input_pin(self, name, pullup=None):
        return MockPin(name, self)

    def make_timer(self):
        return MockTimer()

    def ticks_us(self):
        self._ticks = self._ticks + 1
        return self._ticks

    def init_timer(self, timer, freq, callback):
        pass