import sys
sys.path.append('./src')
sys.path.append('./src/commands')
sys.path.append('./src/logic')
from trace_directory import TraceDirectory
from command_processor import CommandProcessor
from program_quit_exception import ProgramQuitException
from system_wrapper import SystemWrapper
from argument_analyser import ArgumentAnalyser
from trace_deletor import TraceDeletor
from trace_plotter import TracePlotter
from command_d import CommandD
from command_p import CommandP
from command_l import CommandL
from command_c import CommandC

surl = 'http://192.168.1.87:5000'
#surl = 'http://localhost:5042'

system_wrapper = SystemWrapper(surl)
trace_directory = TraceDirectory(system_wrapper)
argument_analyser = ArgumentAnalyser()
command_processor = CommandProcessor(system_wrapper, argument_analyser)
trace_deletor = TraceDeletor(trace_directory, system_wrapper)
command_d = CommandD(trace_deletor)
command_processor.add_command('d', command_d, 'Delete trace file(s)')
trace_plotter = TracePlotter(trace_directory)
command_p = CommandP(trace_plotter)
command_processor.add_command('p', command_p, 'Plot trace file(s)')
command_l = CommandL(trace_directory)
command_processor.add_command('l', command_l, 'List trace file(s)')
command_c = CommandC(trace_directory);
command_processor.add_command('c', command_c, 'Show trace in a format fit for a pico')


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
