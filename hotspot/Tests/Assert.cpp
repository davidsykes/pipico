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

void AssertEqual(const std::string& value, const std::string& expected)
{
	if (value != expected)
	{
		throw AssertException("Values differ");;
	}
}