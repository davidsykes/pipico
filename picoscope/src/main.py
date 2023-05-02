import sys
sys.path.append('./wifi')

from machine import unique_id
from maincode import MainCode
from system_functions import SystemFunctions
from network_initialiser import NetworkInitialiser

connection_values = NetworkInitialiser().initialise()

s = unique_id()
id = ''
for b in s:
    id = id + hex(b)[2:]
print('Pico id', id)

system = SystemFunctions(id)
maincode = MainCode()
maincode.maincode(system, connection_values)