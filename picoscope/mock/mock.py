import sys
sys.path.append('../src')
from maincode import MainCode
from exit_mock_system_exception import ExitMockSystemException

connection_options = {'serverip': 'server ip'}

from mock_system import MockSystem
system = MockSystem()
maincode = MainCode()
try:
    maincode.maincode(system, connection_options)
except ExitMockSystemException:
    pass