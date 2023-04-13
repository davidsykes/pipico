import urequests as requests
import json
import socket
import time
from ir_exception import IrException

class SystemFunctions:
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

    def log_exception(self, service_access, message, e):
        string_stream = StringIO('')
        sys.print_exception(e, string_stream)
        service_access.log(''.join([message, ': ', string_stream.getvalue()]))

    def get(self, url):
        response = requests.get(url)
        status_code = response.status_code
        text = response.text
        response.close()
        if status_code == 200:
            return text
        raise IrException(''.join(['Error ', str(status_code), ' accessing url ', url]))

    def put(self, url, headers, data):
        jsonObj = json.dumps(data)
        try:
            response = requests.put(url, data=jsonObj, headers=headers)
        except:
            response = requests.put(url, data=jsonObj, headers=headers)
        status_code = response.status_code
        response.close()
        if (status_code != 200):
            print('put response', status_code)
        return status_code

    def open_socket(self):
        addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
        s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(addr)
        s.listen(1)
        return s

    def accept(self, s):
        return s.accept()

    def recv(self, cl):
        request = cl.recv(1024)
        request_string = ''.join([chr(int(x)) for x in request])
        return request_string

