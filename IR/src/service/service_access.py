import json

class ServiceAccess:
    options_url = 'option?option=network'

    def __init__(self, network, base_url):
        self.network = network
        self.base_url = base_url

    def get_url(self, url):
        return self.base_url + '/' + url

    def get(self, url):
        if (self.network.connected):
            return self.network.get(url)

    def get_option(self, name):
        if (self.network.connected):
            url = self.get_url('option?option=' + name)
            opt = self.get(url)
            return opt

    def put(self, url, data):
        if (self.network.connected):
            headers = {'content-type': 'application/json'}
            self.network.put(url, headers, data)

    def log(self, message):
        print(message)
        if (self.network.connected):
            url = self.get_url('log')
            self.put(url, message)

    def send_ir_code(self, code, wave_data):
        if (self.network.connected):
            url = self.get_url('ircode')
            headers = {'content-type': 'application/json'}
            data = {'code': str(code), 'wavepoints' : wave_data}
            self.network.put(url, headers, data)