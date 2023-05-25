#import json
from urllib.request import urlopen
#from urllib.error import HTTPError
#from urllib.error import URLError

def network_api_get(self, url):
    print('Get', url)
    #try:
    if(True):
        with urlopen(url) as x:
            data = x.read().decode('utf-8')
        return data
    #except HTTPError as e:
    #    raise IrException(''.join(['HTTPError ', str(e.code), ' error accessing url ', url]))
    #except URLError as e:
    #    raise IrException(''.join(['URLError error accessing url ', url]))



print(network_api_get('blbl', 'http://192.168.1.142/tracenames'))