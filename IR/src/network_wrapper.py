class Network:
    options_url = 'http://192.168.1.125:5004/weatherforecast'

    def __init__(self, network_layer):
        self._network_layer = network_layer

    def initialise(self):
        self._network_layer.initialise()

    def get_network_options(self):
        options = self._network_layer.get(self.options_url)
        print('options', options)