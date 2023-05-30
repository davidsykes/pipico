import sys
sys.path.append('./src')
sys.path.append('./src/commands')
sys.path.append('./src/logic')
from pico_system import PicoSystem
from plot_system import PlotSystem
from trace_directory import TraceDirectory
from command_processor import CommandProcessor
from program_quit_exception import ProgramQuitException
from argument_analyser import ArgumentAnalyser
from trace_deletor import TraceDeletor
from trace_plotter import TracePlotter
from command_d import CommandD
from command_p import CommandP
from command_l import CommandL

surl = 'http://192.168.1.142:5000'
#surl = 'http://localhost:5042'

pico_system = PicoSystem(surl)
plot_system = PlotSystem()
trace_directory = TraceDirectory(pico_system)
argument_analyser = ArgumentAnalyser()
command_processor = CommandProcessor(pico_system, argument_analyser)
trace_deletor = TraceDeletor(trace_directory, pico_system)
command_d = CommandD(trace_deletor)
command_processor.add_command('d', command_d, 'Delete trace file(s)')
trace_plotter = TracePlotter(trace_directory, plot_system)
command_p = CommandP(trace_plotter)
command_processor.add_command('p', command_p, 'Plot trace file(s)')
command_l = CommandL(trace_directory)
command_processor.add_command('l', command_l, 'List trace file(s)')


for i in range(1, len(sys.argv)):
    command_processor.process_command(sys.argv[i])

command_l.process_command()

try:
    while True:
        cmd = input("What now? ")
        command_processor.process_command(cmd)
        trace_directory.update_trace_list()
except ProgramQuitException:
    pass
