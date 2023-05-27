from urllib.request import urlopen, Request

class System:
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
        # from urllib import request, parse
        # data = parse.urlencode(<your data dict>).encode()
        # req =  request.Request(<your url>, data=data) # this will make the method "POST"
        # resp = request.urlopen(req)

        url = ''.join([self._server_url, '/', url])
        print('Post', url)
        req = Request(url, method='POST')
        resp = urlopen(req)
        print(resp)
