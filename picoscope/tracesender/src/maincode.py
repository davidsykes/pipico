from receiver import Receiver
from poster import Poster

class MainCode:
    def maincode(self, system, connection_values):
        uart = system.initialise_uart(0)
        uart.write(b'Hello World')
        server_ip = connection_values['server_ip']

        self.receiver = Receiver(system)
        self.poster = Poster(system, server_ip)

        while True:
            if uart.any():
                data = self.receiver.receive(uart)
                self.poster.post_data(data)
            else:
                system.sleep(0.1)