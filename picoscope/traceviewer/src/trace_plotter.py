import matplotlib.pyplot as plt

class TracePlotter:
    def __init__(self, trace_directory):
        self._trace_directory = trace_directory

    def plot_traces(self, list_of_traces_to_plot):
        fig, ax = plt.subplots()
        trace_count = len(list_of_traces_to_plot)
        trace_separation = 0
        current_trace = 0
        for trace_number in list_of_traces_to_plot:
            trace_details = self._trace_directory.get_trace_data_by_number(trace_number)
            trace_data = trace_details['rawScopeTraceData']
            sample_count = len(trace_data)
            x = []
            y = []
            previous_value = trace_data['initialValue'] + current_trace * trace_separation
            for s in trace_data['values']:
                new_value = s[1] + current_trace * trace_separation
                x.append(s[0])
                y.append(previous_value)
                x.append(s[0])
                y.append(new_value)
                previous_value = new_value
            ax.plot(x, y)
            current_trace = current_trace + 1
        plt.show()