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

class MockPlotter:
    def plot_traces(self, args):
        self.plotted_items = args

class TestCommandProcessor:
    def setup_method(self, test_method):
        self.mock_analyser = MockArgumentAnalyser()
        self.mock_deletor = MockDeletor()
        self.mock_plotter = MockPlotter()
        self.processor = CommandProcessor(self.mock_analyser, self.mock_deletor, self.mock_plotter)

    def test_command_d_analyses_parameters_and_passes_to_deletor(self):
        self.processor.process_command('darguments')

        assert(self.mock_deletor.deleted_items == 'analysed arguments')

    def test_command_d_returns_true(self):
        result = self.processor.process_command('darguments')

        assert(result is True)

    def test_an_empty_command_does_nothing(self):
        self.processor.process_command('')
        self.processor.process_command(None)

    def test_an_empty_command_returns_true(self):
        result = self.processor.process_command('')
        assert(result is True)

    def test_an_invalid_command_throws_a_command_exception(self):
        with pytest.raises(CommandException):
            self.processor.process_command('xarguments')

    def test_command_q_returns_false(self):
        result = self.processor.process_command('qarguments')

        assert(result is False)

    def test_command_p_analyses_parameters_and_passes_to_plotter(self):
        self.processor.process_command('parguments')

        assert(self.mock_plotter.plotted_items == 'analysed arguments')

    def test_command_p_returns_true(self):
        result = self.processor.process_command('parguments')

        assert(result is True)