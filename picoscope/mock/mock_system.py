from exit_mock_system_exception import ExitMockSystemException

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
    def __init__(self):
        self.time_to_run = 1
        self.time_since_start = 0
    def initialise_uart(self, uart):
        return UART()
    def sleep(self, time):
        self.time_since_start += time
        if self.time_since_start >= self.time_to_run:
            raise ExitMockSystemException
    def put_json(self, url, data):
        print('Put json to', url, ':', data)