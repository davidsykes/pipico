class CommandP:
    def __init__(self, plotter):
        self._plotter = plotter

    def process_command(self, arguments):
        self._plotter.plot_traces(arguments)