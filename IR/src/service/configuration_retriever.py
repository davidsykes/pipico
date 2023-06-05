class ConfigurationRetriever:
    def __init__(self, service_access, pico_id):
        self.service_access = service_access
        self.url = 'option?option=configuration.' + pico_id

    def retrieve_configuration(self):
        return self.service_access.network_api_get(self.url)
