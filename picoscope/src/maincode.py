from receiver import Receiver
from poster import DataPoster

class MainCode:
    def maincode(self, system):
        uart = system.initialise_uart(0)
        uart.write(b'Hello World')

        self.receiver = Receiver(system)
        self.poster = DataPoster()

        while True:
            if uart.any():
                data = self.receiver.receive(uart)
                self.poster.post_data(data)
            else:
                self.system.sleep(0.1)