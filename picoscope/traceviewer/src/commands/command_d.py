class CommandD:
    def __init__(self, deletor):
        self._deletor = deletor

    def process_command(self, arguments):
        self._deletor.delete_traces(arguments)