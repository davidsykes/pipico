import sys
sys.path.append('../../src/commands')
from command_p import CommandP

class MockPlotter:
    def plot_traces(self, args):
        self.plotted_items = args

class TestCommandP:
    def setup_method(self, test_method):
        self.mock_plotter = MockPlotter()
        self.command = CommandP(self.mock_plotter)
        self.mock_arguments = [1,2,3]

    def test_command_passes_parameters_to_plotter(self):
        self.command.process_command(self.mock_arguments)

        assert(self.mock_plotter.plotted_items == self.mock_arguments)

