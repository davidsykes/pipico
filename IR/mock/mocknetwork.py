import json
from urllib.request import urlopen

class MockClientConnection:
    def send(self, data):
        print('Client send', data)
    def close(self):
        print('Client close')

class MockNetwork:
    def __init__(self):
        self.commands = ['GET /', 'GET /code/527199']
        self.next = 0
    def initialise(self):
        print('Start the internet')
        return True

    def get_url(self, path):
        return 'url for ' + path
    
    def get(self, url):
        print('Get', url)
        with urlopen(url) as x:
            data = x.read().decode('utf-8')
        return data

    def put(self, url, headers, body):
        print('Put to ', url)
        print(headers)
        print(json.dumps(body))

#    def listen(self, action):
#        print("Listen to the network")
#        action("""GET / HTTP/1.1
#Host: 192.168.1.75
#Connection: keep-alive""")

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