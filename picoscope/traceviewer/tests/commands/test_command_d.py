import sys
sys.path.append('../src/commands')
from command_d import CommandD

class MockDeletor:
    def delete_traces(self, args):
        self.deleted_items = args

class TestCommandD:
    def setup_method(self, test_method):
        self.mock_deletor = MockDeletor()
        self.command = CommandD(self.mock_deletor)
        self.mock_arguments = [1,2,3]

    def test_command_d_passes_arguments_to_deletor(self):
        self.command.process_command(self.mock_arguments)

        assert(self.mock_deletor.deleted_items == self.mock_arguments)
