#include <sstream>
#include "percent_decoder.h"

static int hexToInt(const char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	return -1;
}

std::string PercentDecoder::Decode(const std::string& value)
{
	std::ostringstream os;
	const char* st = value.c_str();

	while (*st)
	{
		if (*st == '%')
		{
			int asciiValue = -1;
			if (st[1])
			{
				int asciiHigh = hexToInt(st[1]);
				if (asciiHigh >= 0 && st[2])
				{
					int asciiLow = hexToInt(st[2]);
					if (asciiLow >= 0)
					{
						asciiValue = asciiHigh * 16 + asciiLow;
					}
				}
			}
			if (asciiValue >= 0)
			{
				os << char(asciiValue);
				st += 3;
			}
			else
			{
				os << *st++;
			}
		}
		else
		{
			os << *st++;
		}
	}

	return os.str();
}
