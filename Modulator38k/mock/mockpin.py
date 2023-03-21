class MockInputPin:
    def __init__(self, on):
        self._value = 1 if on else 0
    def value(self):
        return self._value

class MockOutputPin:
    def value(self, value=None):
        pass
