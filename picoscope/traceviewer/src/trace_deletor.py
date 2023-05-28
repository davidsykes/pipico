class TraceDeletor:
    def __init__(self, trace_directory, rest_system):
        self._trace_directory = trace_directory
        self._rest_system = rest_system

    def delete_traces(self, list_of_traces_to_delete):
        for trace_number in list_of_traces_to_delete:
            trace_name = self._trace_directory.get_trace_path_by_number(trace_number)
            url = 'delete/' + trace_name
            self._rest_system.post(url)