#include <exception>
#include "Assert.h"
using namespace std;


class MyException : public exception
{
	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
} myex;

void AssertEqual(const std::string& value, const std::string& expected)
{
	if (value != expected)
	{
		throw myex;
	}
}