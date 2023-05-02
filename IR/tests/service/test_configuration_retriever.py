import sys
sys.path.append('../src/service')
from configuration_retriever import ConfigurationRetriever

class MockServiceAccess:
	def network_api_get(self, url):
		if url == 'option?option=configuration':
			return 'configuration value'

class TestConfigurationRetriever:
	def setup_method(self, test_method):
		self.access = MockServiceAccess()
		self.retriever = ConfigurationRetriever(self.access)

	def test_retrieve_configuration_retrieves_configuration_from_the_server(self):
		configuration = self.retriever.retrieve_configuration()

		assert(configuration == 'configuration value')

