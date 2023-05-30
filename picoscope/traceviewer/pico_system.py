from urllib.request import urlopen, Request

class PicoSystem:
    def __init__(self, server_url):
        self._server_url = server_url

    def get(self, url):
        url = ''.join([self._server_url, '/', url])
        print('Get', url)
        #try:
        if(True):
            with urlopen(url) as x:
                data = x.read().decode('utf-8')
            return data

    def post(self, url):
        url = ''.join([self._server_url, '/', url])
        print('Post', url)
        req = Request(url, method='POST')
        resp = urlopen(req)
        print(resp)

    def print(self, p):
        print(p)
