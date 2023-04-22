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
maincode.maincode(system)

raise NotImplementedError

from mock_system_functions import MockSystemFunctions
system = MockSystemFunctions()
maincode.maincode(system)