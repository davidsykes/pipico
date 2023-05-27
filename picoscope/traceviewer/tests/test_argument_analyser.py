import pytest
import sys
sys.path.append('../src')
from argument_analyser import ArgumentAnalyser


class TestArgumentAnalyser:
    def setup_method(self, test_method):
        self.analyser = ArgumentAnalyser()

    def test_a_simple_value_is_returned(self):
        args = self.analyser.analyse_arguments('3')

        assert(len(args) == 1)
        assert(args[0] == '3')