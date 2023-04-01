from ir_exception import IrException

class UrlRequest:
    def __init__(self, type, url):
        self.type = type
        self.url = url

class UrlRequestDecoder:
    def decode_request(self, request):
        if request is None:
            raise IrException('Url Request is None')
        lines = request.splitlines()
        if lines is None or len(lines) < 1:
            raise IrException('Url Request is empty')
        words = lines[0].split()
        if (len(words) < 2):
            raise IrException("Invalid request url: '" + lines[0] + "'")
        return UrlRequest(words[0], words[1])