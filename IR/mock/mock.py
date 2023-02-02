import sys
from mocksystem import MockSystem
from mocknetwork import MockNetwork
sys.path.append('../src')
from maincode import MainCode

system = MockSystem()
network = MockNetwork()
maincode = MainCode()
maincode.maincode(system, network)