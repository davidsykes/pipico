class PinWatcher:
    def __init__(self, system, pin):
        self._system = system
        self._pin = pin
        self._value = pin.value()
        self._time_of_last_change = self._system.ticks_us()

    def wait_for_change(self, timeout=None):
        start_time = self._system.ticks_us()
        while (True):
            if (self._value != self._pin.value()):
                self._time_of_last_change = self._system.ticks_us()
                self._value = self._pin.value()
                return self._value
            if (timeout is not None):
                t = self._system.ticks_us() - start_time
                if (t >= timeout):
                    return None

    def get_time_of_change(self, timeout=None):
        last_change_time = self._time_of_last_change
        val = self.wait_for_change(timeout)
        if (val is None):
            return None
        return self._time_of_last_change - last_change_time
        
    def value(self):
        self._value = self._pin.value()
        return self._value