#include <exception>
#include "Assert.h"
using namespace std;


class AssertException : public exception
{
	const char* _message;

	virtual const char* what() const throw()
	{
		return "My exception happened";
	}

public:
	AssertException(const char* message)
	{
		_message = message;
	}
};

void Assert(const char* message)
{
	throw new AssertException(message);
}

void AssertTrue(bool value)
{
	if (!value)
	{
		Assert("Assert fails");
	}
}

void AssertFalse(bool value)
{
	AssertTrue(!value);
}

void AssertEqual(const char* expected, const char* value)
{
	if (strcmp(value, expected) != 0)
	{
		const char* cexpected = expected;
		const char* cvalue = value;
		while (*cexpected == *cvalue)
		{
			++cexpected;
			++cvalue;
		}
		throw AssertException("Values differ");
	}
}

void AssertEqual(std::string expected, const char* value) { AssertEqual(expected.c_str(), value); }
void AssertEqual(std::string expected, std::string value) { AssertEqual(expected.c_str(), value.c_str()); }

void AssertEqual(const size_t expected, const size_t value)
{
	if (value != expected)
	{
		throw AssertException("Values differ");
	}
}

static const char* SkipWhitespace(const char* p)
{
	++p;
	while (*p && isspace(*p)) ++p;
	return p;
}

void AssertEqualNonWhitespace(const char* expected, const char* value)
{
	const char* valuep = value;
	const char* expectedp = expected;
	while (*valuep && *expectedp)
	{
		AssertEqual(*valuep, *expectedp);

		valuep = SkipWhitespace(valuep);
		expectedp = SkipWhitespace(expectedp);
	}
	AssertEqual(*valuep, *expectedp);
}