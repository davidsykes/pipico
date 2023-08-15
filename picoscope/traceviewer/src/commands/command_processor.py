from command_exception import CommandException
from program_quit_exception import ProgramQuitException

class CommandProcessor:
    def __init__(self, pico_system, argument_analyser):
        self._pico_system = pico_system
        self._argument_analyser = argument_analyser
        self._commands = {}
        self._commandinfo = {}

    def add_command(self, command_letter, command, command_info):
        self._commands[command_letter] = command
        self._commandinfo[command_letter] = command_info

    def process_command(self, cmd):
        if cmd:
            command = cmd[0]
            arguments = cmd[1:]
            analysed_arguments = self._argument_analyser.analyse_arguments(arguments)

            if command in self._commands:
                self._commands[command].process_command(analysed_arguments)
            elif command == 'q':
                raise ProgramQuitException()
            elif command == '?':
                self.show_usage()
            else:
                raise CommandException(''.join(["Invalid command '", command, "'."]))
        return True

    def show_usage(self):
        for key, value in self._commandinfo.items():
            self._pico_system.print(''.join([key, ': ', value]))
        print('Reference traces by numbers or ranges a-b')