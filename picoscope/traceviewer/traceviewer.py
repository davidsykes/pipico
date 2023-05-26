#import json
#from urllib.error import HTTPError
#from urllib.error import URLError
from system import System
import sys
sys.path.append('./src')
from trace_directory import TraceDirectory

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


system = System()
trace_directory = TraceDirectory(system, 'http://192.168.1.142:5000')

traces = trace_directory.get_trace_list()

for i in range(len(traces)):
    trace = traces[i]
    print(''.join([str(i), ': ', trace['traceName'], ' (', str(trace['traceCount']), ' - ', str(trace['traceLength']/1000), 'ms)']))

print()

#print(network_api_get('blbl', 'http://192.168.1.142:5000/tracenames'))
