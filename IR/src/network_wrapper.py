class Network:
    options_url = 'http://192.168.1.87:5000/option?option=oli'
    #put_url = "http://192.168.1.87:5000/message"
    connected = False

    def __init__(self, network_layer, base_url):
        self._network_layer = network_layer
        self.base_url = base_url

    def initialise(self):
        self.connected = self._network_layer.initialise()
        print('Internet connected' if self.connected else 'Internet connection failed')

    def get_url(self, url):
        return self.base_url + '/' + url

    def get(self, url):
        if (self.connected):
            return self._network_layer.get(url)

    def get_network_options(self):
        if (self.connected):
            options = self._network_layer.get(self.options_url)
            print('Network options', options)

    def put(self, type, data):
        if (self.connected):
            url = self.get_url('message')
            headers = {'content-type': 'application/json'}
            body = {'type': type, 'data' : data}
            self._network_layer.put(url, headers, body)

    def listen(self):
        self._network_layer.listen()