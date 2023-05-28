class TracePlotter:
    def __init__(self, trace_directory, plot_system):
        self._trace_directory = trace_directory
        self._plot_system = plot_system

    def plot_traces(self, list_of_traces_to_plot):
        for trace_number in list_of_traces_to_plot:
            trace_data = self._trace_directory.get_trace_data_by_number(trace_number)
            sample_count = len(trace_data)
            print('Sample count:', sample_count)
            for s in trace_data:
                print(s)