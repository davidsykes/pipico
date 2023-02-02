from machine import Pin, Timer
import time
from maincode import maincode
from pico_network import PicoNetwork


class SystemWrapper:
    def MakeOutputPin(self, name):
        return Pin(name, Pin.OUT)

    def MakeInputPin(self, name, pull = None):
        if (pull is None):
            return Pin(name, Pin.IN)
        return Pin(name, Pin.IN, Pin.PULL_UP if pull else Pin.PULL_DOWN)

    def MakeTimer(self):
        return Timer()

    def ticks_us(self):
        return time.ticks_us()

    def init_timer(self, timer, freq, callbackfn):
        timer.init(freq=freq, mode=Timer.PERIODIC, callback=callbackfn)


network = PicoNetwork()
system = SystemWrapper()
maincode(system, network)