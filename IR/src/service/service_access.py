import json

class ServiceAccess:
    options_url = 'option?option=system'

    def __init__(self, system, base_url):
        self.system = system
        self.base_url = base_url

    def get_url(self, url):
        return self.base_url + '/' + url

    def get(self, url):
        return self.system.get(url)

    def get_option(self, name):
        url = self.get_url('option?option=' + name)
        opt = self.get(url)
        return opt

    def put(self, url, data):
        json_data = json.dumps(data)
        self.system.put_json(url, headers, json_data)

    def log(self, message):
        print(message)
        url = self.get_url('log')
        self.put(url, message)

    def send_ir_code(self, code, wave_data):
        url = self.get_url('ircode')
        data = {'code': str(code), 'wavepoints' : wave_data}
        json_data = json.dumps(data)
        self.system.put_json(url, json_data)