class UrlRequest:
    def __init__(self, type, url):
        self.type = type
        self.url = url

class UrlRequestDecoder:
    def decode_request(self, request):
        lines = request.splitlines()
        words = lines[0].split()
        if (len(words) < 2):
            from ir_exception import IrException
            raise IrException("Invalid request url: '" + lines[0] + "'")
        return UrlRequest(words[0], words[1])