import json
from urllib.request import urlopen
from urllib.error import HTTPError
from ir_exception import IrException

class MockClientConnection:
    def send(self, data):
        print('Client send', data)
    def close(self):
        print('Client close')

class MockNetwork:
    def __init__(self):
        self.commands = ['GET /', 'GET /code/527199']
        self.next = 0
        self.connected = True

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

    def put(self, url, headers, body):
        print('Put to ', url)
        print(headers)
        print(json.dumps(body))

    def put2(self, url, headers, body):
        print('Put to ', url)
        print(headers)
        print(body)

    def open_socket(self):
        print('Open Socket for listening')
    def accept(self, socket):
        print('Socket accept')
        return MockClientConnection(),'ip address'
    def recv(self, cl):
        if self.next < len(self.commands):
            command = self.commands[self.next]
            self.next = self.next + 1
            return command
        exit()