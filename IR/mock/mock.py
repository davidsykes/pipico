import sys
from mocksystem import MockSystem
from mocknetwork import MockNetwork
sys.path.append('../src')
from maincode import maincode

system = MockSystem()
network = MockNetwork()

maincode(system, network)