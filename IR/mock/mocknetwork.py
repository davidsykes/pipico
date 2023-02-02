from urllib.request import urlopen

class MockNetwork:
    def initialise(self):
        print('Start the internet')
        return True
    
    def get(self, url):
        with urlopen(url) as x:
            data = x.read().decode('utf-8')
        print (data)
        return data

    def put(self, url, headers, body):
        print('Put to ', url)
        print(headers)
        print(body)