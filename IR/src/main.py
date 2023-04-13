import sys
sys.path.append('./wave_forms')
sys.path.append('./service')
sys.path.append('./io')
sys.path.append('./logic')
sys.path.append('./server')
sys.path.append('./recorder')

import time
from machine import Pin, Timer, ADC, unique_id
from uio import StringIO
from maincode import MainCode
from system_functions import SystemFunctions


s = unique_id()
id = ''
for b in s:
    id = id + hex(b)[2:]
print('Pico id', id)

system = SystemFunctions(id)
maincode = MainCode()
maincode.maincode(system)