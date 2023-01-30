from urllib.request import urlopen

class MockNetwork:
    def initialise(self):
        print('Start the internet')
    
    def get(self, url):
        with urlopen(url) as x:
            data = x.read().decode('utf-8')
        print (data)
        return data