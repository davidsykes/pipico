import sys
sys.path.append('./wave_forms')
sys.path.append('./service')
sys.path.append('./io')
sys.path.append('./logic')
sys.path.append('./server')
from machine import Pin, Timer
import time
from maincode import MainCode
from pico_network import PicoNetwork
from uio import StringIO


class SystemWrapper:
    def make_output_pin(self, name):
        return Pin(name, Pin.OUT)

    def make_input_pin(self, name, pull = None):
        if (pull is None):
            return Pin(name, Pin.IN)
        return Pin(name, Pin.IN, Pin.PULL_UP if pull else Pin.PULL_DOWN)

    def make_timer(self):
        return Timer()

    def ticks_us(self):
        return time.ticks_us()

    def init_timer(self, timer, freq, callbackfn):
        timer.init(freq=freq, mode=Timer.PERIODIC, callback=callbackfn)

    def initialise_network(self):
        return PicoNetwork()

    def log_exception(self, service_access, message, e):
        string_stream = StringIO('')
        sys.print_exception(e, string_stream)
        service_access.log(''.join([message, ': ', string_stream.getvalue()]))


system = SystemWrapper()
maincode = MainCode()
maincode.maincode(system)