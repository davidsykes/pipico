import pytest
import sys
sys.path.append('../src')
from command_processor import CommandProcessor
from command_exception import CommandException

class MockArgumentAnalyser:
    def analyse_arguments(self, args):
        return 'analysed ' + args

class MockDeletor:
    def delete_traces(self, args):
        self.deleted_items = args

class TestCommandProcessor:
    def setup_method(self, test_method):
        self.mock_analyser = MockArgumentAnalyser()
        self.mock_deletor = MockDeletor()
        self.processor = CommandProcessor(self.mock_analyser, self.mock_deletor)

    def test_d_analyses_parameters_and_passes_to_deletor(self):
        self.processor.process_command('darguments')

        assert(self.mock_deletor.deleted_items == 'analysed arguments')

    def test_an_empty_command_does_nothing(self):
        self.processor.process_command('')
        self.processor.process_command(None)

    def test_an_invalid_command_throws_a_command_exception(self):
        with pytest.raises(CommandException):
            self.processor.process_command('xarguments')