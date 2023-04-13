import json
from urllib.request import urlopen
from urllib.error import HTTPError
from urllib.error import URLError
from ir_exception import IrException
from mockpin import MockInputPin, MockOutputPin, MockIrReceivePin

class MockTimer:
    def __init__(self):
        pass

    def init(self, freq, mode, callback):
        pass

class MockClientConnection:
    def __init__(self):
        self.commands = ['GET /', 'GET /sequence/Sequence%201', 'GET /code/Code%202']
        self.next = 0
        self.ip_address = 'mock connection'
    def send(self, data):
        print(''.join(['Client send "', data, '"']))
    def close(self):
        print('Client close')

    def next_request(self):
        if (self.next < len(self.commands)):
            request = self.commands[self.next]
            self.next = self.next + 1
            return request
        exit()

class MockSystemFunctions:
    _ticks = 0
    transmit_ir_codes = True
    dump_ir_codes = False

    def __init__(self):
        self.id = 'MockSystem'
        self.pins = {}
        self.pins['LED'] = MockOutputPin()
        self.pins['14'] = MockOutputPin()
        self.pins['15'] = MockIrReceivePin(self)
        self.pins['5'] = MockInputPin(False)
        self.pins['4'] = MockInputPin(self.transmit_ir_codes)
        self.pins['3'] = MockInputPin(self.dump_ir_codes)
        self.pins['2'] = MockInputPin(False)
        self.client_connection = MockClientConnection()

    def make_output_pin(self, name):
        return self.make_pin(name)

    def make_input_pin(self, name, pullup=None):
        return self.make_pin(name)

    def make_pin(self, name):
        name = str(name)
        if name in self.pins:
            return self.pins[name]
        raise Exception(''.join(['Pin ', name, ' has not been defined']))

    def make_timer(self):
        return MockTimer()

    def ticks_us(self):
        self._ticks = self._ticks + 1
        return self._ticks

    def init_timer(self, timer, freq, callback):
        pass

    def get_url(self, path):
        return 'url for ' + path
    
    def get(self, url):
        print('Get', url)
        try:
            with urlopen(url) as x:
                data = x.read().decode('utf-8')
            return data
        except HTTPError as e:
            raise IrException(''.join(['HTTPError ', str(e.code), ' error accessing url ', url]))
        except URLError as e:
            raise IrException(''.join(['URLError error accessing url ', url]))

    def put(self, url, headers, body):
        print('Put to', url)
        print(json.dumps(body))

    def open_socket(self):
        print('Open Socket for listening')

    def accept(self, socket):
        print('Socket accept')
        return self.client_connection,'Mock'

    def recv(self, cl):
        return cl.next_request()
