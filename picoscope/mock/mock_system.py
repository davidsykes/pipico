

class UART:
    def __init__(self):
        self.data = None
    def write(self, data):
        self.data = data
        print('Uart write', data)
    def any(self):
        return self.data is not None
    def read(self):
        if self.data is not None:
            data = self.data
            self.data = None
            return data

class MockSystem:
    def initialise_uart(self, uart):
        return UART()
    def sleep(self, time):
        pass