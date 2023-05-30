import pytest
import sys
sys.path.append('../src')
sys.path.append('../src/logic')
from command_processor import CommandProcessor
from command_exception import CommandException
from program_quit_exception import ProgramQuitException

class MockArgumentAnalyser:
    def analyse_arguments(self, args):
        return 'analysed ' + args

class MockCommand:
    def process_command(self, args):
        self.processed_command = args

class MockPicoSystem:
    def __init__(self):
        self.printed = ''
    def print(self, p):
        self.printed = self.printed + p + '\n'

class TestCommandProcessor:
    def setup_method(self, test_method):
        self.mock_system = MockPicoSystem()
        self.mock_analyser = MockArgumentAnalyser()
        self.processor = CommandProcessor(self.mock_system, self.mock_analyser)

    def test_an_added_commmand_can_be_called(self):
        command = MockCommand()
        self.processor.add_command('c', command, 'c')

        self.processor.process_command('carguments')

        assert(command.processed_command == 'analysed arguments')

    def test_multiple_commmands_can_be_called(self):
        commandc = MockCommand()
        self.processor.add_command('c', commandc, 'c')
        commandd = MockCommand()
        self.processor.add_command('d', commandd, 'd')
        commande = MockCommand()
        self.processor.add_command('e', commande, 'e')

        self.processor.process_command('eearguments')
        self.processor.process_command('ccarguments')
        self.processor.process_command('ddarguments')

        assert(commandc.processed_command == 'analysed carguments')
        assert(commandd.processed_command == 'analysed darguments')
        assert(commande.processed_command == 'analysed earguments')

    def test_an_invalid_command_throws_a_command_exception(self):
        with pytest.raises(CommandException):
            self.processor.process_command('xarguments')

    def test_an_empty_command_does_nothing(self):
        self.processor.process_command('')
        self.processor.process_command(None)

    def test_command_q_throws_a_quit_exception(self):
        with pytest.raises(ProgramQuitException):
            self.processor.process_command('qarguments')

    def test_command_question_produces_a_list_of_instructions(self):
        self.processor.add_command('c', MockCommand(), 'how to use c')
        self.processor.add_command('d', MockCommand(), 'how to use d')
        self.processor.add_command('e', MockCommand(), 'how to use e')

        self.processor.process_command('?whatever')

        assert(self.mock_system.printed == 'c: how to use c\nd: how to use d\ne: how to use e\n')
