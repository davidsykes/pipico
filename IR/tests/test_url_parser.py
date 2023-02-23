import sys
sys.path.append('../src/logic')
from url_parser import UrlParser

class TestUrlParser:

	def test_quote_converts_spaces_to_percent20(self):
		result = UrlParser.quote('url with spaces')

		assert(result == 'url%20with%20spaces')

	def test_unquote_converts_percent20_to_spaces(self):
		result = UrlParser.unquote('url%20with%20spaces')

		assert(result == 'url with spaces')