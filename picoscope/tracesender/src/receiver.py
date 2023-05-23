class Receiver:
    def __init__(self, system):
        self.system = system
        self.maximum_wait_time = 0.1
        self.wait_time_increment = 0.001

    def receive(self, uart):
        data = []
        time_since_last_data = 0
        while time_since_last_data < self.maximum_wait_time or uart.any():
            while uart.any():
                data.append(uart.read())
                time_since_last_data = 0
            self.system.sleep(self.wait_time_increment)
            time_since_last_data += self.wait_time_increment
        return b''.join(data)