import pytest
import sys
sys.path.append('../src/server')
from connection_handler import ConnectionHandler
from ir_exception import IrException

class MockSystem:
	def __init__(self, connection, request):
		self.connection = connection
		self.request = request
	def connection_receive_string(self, client):
		if (client == self.connection):
			return self.request

class MockDecoder:
	def __init__(self, raw, decoded):
		self.raw = raw
		self.decoded = decoded
	def decode_request(self, request):
		self.raw_request = request
		return self.decoded if request == self.raw else None

class MockRouter:
	def __init__(self):
		self.routed_request = None
		self.response = None
		self.throw_exception = False
	def action(self, request):
		self.routed_request = request
		if self.throw_exception:
			raise Exception('oops')
		return self.response

class MockConnection:
	def send(self, html):
		self.request_response = html

class TestConnectionHandler:
	def setup_method(self, test_method):
		self.mock_raw_client_request = 'raw client request'
		self.mock_decoded_client_request = 'decoded client request'
		self.mock_connection = MockConnection()
		self.mock_system = MockSystem(self.mock_connection, self.mock_raw_client_request)
		self.mock_decoder = MockDecoder(self.mock_raw_client_request, self.mock_decoded_client_request)
		self.mock_router = MockRouter()
		self.handler = ConnectionHandler(self.mock_system, self.mock_decoder, self.mock_router)

	def test_the_request_is_passed_to_the_decoder(self):
		self.handler.request(self.mock_connection)

		assert(self.mock_decoder.raw_request == self.mock_raw_client_request)

	def test_the_decoded_request_is_passed_to_the_router(self):
		self.handler.request(self.mock_connection)

		assert(self.mock_router.routed_request == self.mock_decoded_client_request)

	def test_the_router_response_is_sent_to_the_client_with_http_ok(self):
		self.mock_router.response = 'action response'
		self.handler.request(self.mock_connection)

		assert(self.mock_connection.request_response == 'HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\naction response')

	def test_if_the_router_returns_no_response_it_is_sent_to_the_client_with_http_fail(self):
		self.handler.request(self.mock_connection)

		assert(self.mock_connection.request_response == 'HTTP/1.0 404 Bad Request\r\nContent-type: text/html\r\n\r\n')

	def test_if_an_exception_occurs_an_error_response_is_sent(self):
		self.mock_router.throw_exception = True
		with pytest.raises(Exception):
			self.handler.request(self.mock_connection)

		assert(self.mock_connection.request_response == 'HTTP/1.0 404 Bad Request\r\nContent-type: text/html\r\n\r\n')
