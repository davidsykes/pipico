from ir_exception import IrException

class UrlRequest:
    def __init__(self, type, url):
        self.type = type
        self.url = url

class UrlRequestDecoder:
    def decode_request(self, request):
        lines = request.splitlines()
        if lines is None or len(lines) < 1:
            raise IrException("Invalid request url: '" + lines[0] + "'")
        words = lines[0].split()
        if (len(words) < 2):
            raise IrException("Invalid request url: '" + lines[0] + "'")
        return UrlRequest(words[0], words[1])