import json

class ServiceAccess:
    options_url = 'option?option=system'

    def __init__(self, system, base_url):
        self.system = system
        self.base_url = base_url

    def format_url(self, url):
        return self.base_url + '/' + url

    def network_api_get(self, url):
        url = self.format_url(url)
        try:
            return self.system.network_api_get(url)
        except OSError as e:
            self.log('OSError: ' + str(e))
            raise

    def get_option(self, name):
        url = self.format_url('option?option=' + name)
        opt = self.network_api_get(url)
        return opt

    def put(self, url, data):
        json_data = json.dumps(data)
        self.system.put_json(url, json_data)

    def log(self, message):
        print(message)
        url = self.format_url('log')
        self.put(url, message)

    def send_ir_code(self, code, wave_data):
        url = self.format_url('ircode')
        data = {'code': str(code), 'wavepoints' : wave_data}
        json_data = json.dumps(data)
        self.system.put_json(url, json_data)