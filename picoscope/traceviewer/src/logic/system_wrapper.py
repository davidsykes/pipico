from urllib.request import urlopen, Request

class SystemWrapper:
    def __init__(self, server_url):
        self._server_url = server_url

    def get(self, url):
        url = ''.join([self._server_url, '/', url])
        #print('Get', url)
        #try:
        if(True):
            with urlopen(url) as x:
                data = x.read().decode('utf-8')
            return data

    def post(self, url):
        url = ''.join([self._server_url, '/', url])
        #print('Post', url)
        req = Request(url, method='POST')
        resp = urlopen(req)
        if (resp.status != 200):
            print('Post response status', resp.status)
            print('Post url', url)
            print('Reason', resp.reason)

    def print(self, p):
        print(p)
