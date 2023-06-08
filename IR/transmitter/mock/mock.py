import sys
sys.path.append('../src')
sys.path.append('../src/wave_forms')
sys.path.append('../src/service')
sys.path.append('../src/io')
sys.path.append('../src/logic')
sys.path.append('../src/server')
sys.path.append('../src/recorder')
from maincode import MainCode

maincode = MainCode()

from mock_system_simple import SimplestMockSystem
system = SimplestMockSystem()
connection_values = {'server_ip': 'server ip'}
maincode.maincode(system, connection_values)

from mock_system_functions import MockSystemFunctions
system = MockSystemFunctions()
connection_values = {'server_ip': 'http://192.168.1.142:5001'}
maincode.maincode(system, connection_values)