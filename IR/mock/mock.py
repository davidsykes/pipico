import sys
sys.path.append('../src')
sys.path.append('../src/wave_forms')
sys.path.append('../src/service')
sys.path.append('../src/io')
sys.path.append('../src/logic')
from mocksystem import MockSystem
from mocknetwork import MockNetwork
from maincode import MainCode

system = MockSystem()
network = MockNetwork()
maincode = MainCode()
maincode.maincode(system, network)