class MockPin:
    pass

class SimplestMockSystem:
    def __init__(self):
        self.id = 'pico id'
    def make_output_pin(self, name):
        return MockPin()
    def make_timer(self):
        return None
    def init_timer(self, timer, freq, callback):
        pass
    def network_api_get(self, url):
        if url == 'server ip/option?option=configuration.pico id':
            return 'configuration'
        if url == 'server ip/sequences':
            return '{"sequences":[{"name":"Sequence","codes":["Code"]}]}'
        if url == 'server ip/codes':
            return '[{"code":"Test","waveform":[{"t":0,"v":0}]}]'
        print('GET', url)
    def put_json(self, url, data):
        print('put_json:', url, data)
    def open_socket(self):
        pass
    def accept(self, socket):
        return 1,2
    def connection_receive_string(self, connection):
        return 'GET /'
