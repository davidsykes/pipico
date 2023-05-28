from command_exception import CommandException

class CommandProcessor:
    def __init__(self, argument_analyser, trace_deletor, trace_plotter):
        self._argument_analyser = argument_analyser
        self._trace_deletor = trace_deletor
        self._trace_plotter = trace_plotter

    def process_command(self, cmd):
        if cmd:
            command = cmd[0]
            arguments = cmd[1:]
            analysed_arguments = self._argument_analyser.analyse_arguments(arguments)
            if command == 'd':
                self._trace_deletor.delete_traces(analysed_arguments)
            elif command == 'p':
                self._trace_plotter.plot_traces(analysed_arguments)
            elif command == 'q':
                return False
            else:
                raise CommandException(''.join(["Invalid command '", command, "'."]))
        return True
