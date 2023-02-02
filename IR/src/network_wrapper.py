class Network:
    options_url = 'http://192.168.1.87:5000/option?option=oli'
    connected = False

    def __init__(self, network_layer):
        self._network_layer = network_layer

    def initialise(self):
        self.connected = self._network_layer.initialise()
        print('Internet connected' if self.connected else 'Internet connection failed')

    def get_network_options(self):
        if (self.connected):
            options = self._network_layer.get(self.options_url)
            print('Network options', options)

    def put(self, type, name, value):
        if (self.connected):
            url = "http://192.168.1.87:5000/message"
            headers = {'content-type': 'application/json'}
            data = {'type': type, 'name' : name, 'value' : value}
            self._network_layer.put(url, headers, data)
