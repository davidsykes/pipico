from receiver import Receiver
from poster import Poster
from machine import Pin

class MainCode:
    def maincode(self, system, connection_values):
        system.sleep(0.5)
        uart = system.initialise_uart(0)
        uart.write(b'Hello World')
        server_ip = connection_values['server_ip']

        self.receiver = Receiver(system)
        self.poster = Poster(system, server_ip)

        led = Pin("LED", Pin.OUT)
        led.value(1)

        while True:
            if uart.any():
                led.value(0)
                data = self.receiver.receive(uart)
                self.poster.post_data(data)
                led.value(1)
            else:
                system.sleep(0.1)