import matplotlib.pyplot as plt

class TracePlotter:
    def __init__(self, trace_directory):
        self._trace_directory = trace_directory

    def plot_traces(self, list_of_traces_to_plot):
        fig, ax = plt.subplots()
        trace_count = len(list_of_traces_to_plot)
        current_trace = 0
        for trace_number in list_of_traces_to_plot:
            trace_data = self._trace_directory.get_trace_data_by_number(trace_number)
            sample_count = len(trace_data)
            x = []
            y = []
            previous_value = trace_data[0]['value']
            for s in trace_data:
                new_value = s['value'] + current_trace * 300
                x.append(s['time'])
                y.append(previous_value)
                x.append(s['time'])
                y.append(new_value)
                previous_value = new_value
            ax.plot(x, y)
            current_trace = current_trace + 1
        plt.show()