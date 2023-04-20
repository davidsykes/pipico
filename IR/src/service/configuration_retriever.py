class ConfigurationRetriever:
    def __init__(self, service_access):
        self.service_access = service_access

    def retrieve_configuration(self):
        url = 'option?option=configuration'
        print(self.service_access)
        return self.service_access.get(url)
