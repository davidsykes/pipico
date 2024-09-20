class CommandC:
    def __init__(self, trace_directory):
        self._trace_directory = trace_directory

    def process_command(self, arguments=None):
        print('argu', arguments)
        trace_details = self._trace_directory.get_trace_data_by_number(arguments[0])
