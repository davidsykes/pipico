class Receiver:
    def __init__(self, system):
        self.system = system

    def receive(self, uart):
        data = []
        while uart.any():
            while uart.any():
                data.append(uart.read())
            self.system.sleep(0.1)
        return b''.join(data)