class UrlRequest:
    def __init__(self, type, url):
        self.type = type
        self.url = url

class UrlRequestProcessor:
    def process_request(self, request):
        lines = request.splitlines()
        words = lines[0].split()
        return UrlRequest(words[0], words[1])