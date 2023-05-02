import json

class Poster:
    def __init__(self, system, server_ip):
        self.system = system
        self.server_ip = server_ip

    def post_data(self, data):
        url = self.server_ip + '/trace'
        hex_data = data.hex()
        body = {'title': 'Yo', 'trace' : hex_data}
        body_json = json.dumps(body)
        self.system.put_json(url, body_json)