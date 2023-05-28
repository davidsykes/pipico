from system import System
import sys
sys.path.append('./src')
from plot_system import PlotSystem
from trace_directory import TraceDirectory
from command_processor import CommandProcessor
from argument_analyser import ArgumentAnalyser
from trace_deletor import TraceDeletor
from trace_plotter import TracePlotter

surl = 'http://192.168.1.142:5000'
surl = 'http://localhost:5042'

system = System(surl)
plot_system = PlotSystem()
trace_directory = TraceDirectory(system)
argument_analyser = ArgumentAnalyser()
trace_deletor = TraceDeletor(trace_directory, system)
trace_plotter = TracePlotter(trace_directory, plot_system)
command_processor = CommandProcessor(argument_analyser, trace_deletor, trace_plotter)

traces = trace_directory.update_trace_list()

for i in range(len(traces)):
    trace = traces[i]
    print(''.join([str(i+1), ': ', trace['tracename'], ' (', str(trace['tracecount']), ' - ', str(trace['tracelength']/1000), 'ms)']))

for i in range(1, len(sys.argv)):
    command_processor.process_command(sys.argv[i])

repeat = True
while repeat:
    cmd = input("What now? ")
    repeat = command_processor.process_command(cmd)
