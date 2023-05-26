from urllib.request import urlopen

class System:
    def get(self, url):
        print('Get', url)
        #try:
        if(True):
            with urlopen(url) as x:
                data = x.read().decode('utf-8')
            return data