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

static void Assert(const char* message)
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

void AssertEqual(const char* value, const char* expected)
{
	if (strcmp(value, expected) != 0)
	{
		throw AssertException("Values differ");
	}
}

void AssertEqual(std::string value, const char* expected) { AssertEqual(value.c_str(), expected); }
void AssertEqual(std::string value, std::string expected) { AssertEqual(value.c_str(), expected.c_str()); }

void AssertEqual(const char value, const char expected)
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

void AssertEqualNonWhitespace(const char* value, const char* expected)
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