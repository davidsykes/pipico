import sys
sys.path.append('../src')
from maincode import MainCode

from mock_system import MockSystem
system = MockSystem()
maincode = MainCode()
maincode.maincode(system)
