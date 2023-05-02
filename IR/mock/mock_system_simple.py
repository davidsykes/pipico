class MockPin:
    pass

class SimplestMockSystem:
    def make_output_pin(self, name):
        return MockPin()
    def make_timer(self):
        return None
    def init_timer(self, timer, freq, callback):
        pass
    def network_api_get(self, url):
        if url == 'http://192.168.1.87:5000/option?option=configuration':
            return 'configuration'
        print('GET', url)