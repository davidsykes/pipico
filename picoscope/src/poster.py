import json

class Poster:
    def __init__(self, system, server_ip):
        self.system = system
        self.server_url = self.make_server_url(server_ip)

    def make_server_url(self, server_ip):
        return ''.join(['http://', server_ip, '/scope'])

    def post_data(self, data):
        hex_data = data.hex()
        body = {'type': 'trace', 'data' : hex_data}
        body_json = json.dumps(body)
        self.system.put_json(self.server_url, body_json)
