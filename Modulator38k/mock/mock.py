import sys
sys.path.append('../src')
from mocksystem import MockSystem
from maincode import MainCode

system = MockSystem()
maincode = MainCode()
maincode.maincode(system)