from ir_exception import IrException

class ConnectionHandler:
    def __init__(self, system, request_decoder, router):
        self.system = system
        self.request_decoder = request_decoder
        self.router = router
        self.http_ok = 'HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n'
        self.http_error = 'HTTP/1.0 404 Bad Request\r\nContent-type: text/html\r\n\r\n'

    def request(self, connection):
        try:
            raw_request = self.system.connection_receive_string(connection)
            decoded_request = self.request_decoder.decode_request(raw_request)
            action_response = self.router.action(decoded_request)
            html_response = self.make_html_response(action_response)
            connection.send(html_response)
        except Exception as e:
            connection.send(self.http_error)
            raise

    def make_html_response(self, action_response):
        return self.http_error if action_response is None else self.http_ok + action_response