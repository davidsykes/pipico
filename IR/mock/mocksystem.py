from mockpin import MockPin

class MockTimer:
    def __init__(self):
        pass

    def init(self, freq, mode, callback):
        pass

class MockSystem:
    _ticks = 0

    def MakeOutputPin(self, name):
        return MockPin(name, self)

    def MakeInputPin(self, name, pullup=None):
        return MockPin(name, self)

    def MakeTimer(self):
        return MockTimer()

    def ticks_us(self):
        self._ticks = self._ticks + 1
        return self._ticks

    def init_timer(self, timer, freq, callback):
        pass