import base64
import json

class Poster:
    def __init__(self, system, server_ip):
        self.system = system
        self.server_ip = server_ip

    def post_data(self, data):
        url = self.server_ip + '/trace'
        base64_data = base64.b64encode(data).decode('ascii')
        body = {'title': 'Yo', 'trace' : base64_data}
        body_json = json.dumps(body)
        self.system.put_json(url, body_json)