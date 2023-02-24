import sys
sys.path.append('../src')
sys.path.append('../src/wave_forms')
sys.path.append('../src/service')
sys.path.append('../src/io')
sys.path.append('../src/logic')
sys.path.append('../src/server')
sys.path.append('../src/recorder')
sys.path.append('../src/temperature')
from mocksystem import MockSystem
from maincode import MainCode

system = MockSystem()
maincode = MainCode()
maincode.maincode(system)