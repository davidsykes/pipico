#include <exception>
#include "Assert.h"
using namespace std;


class myexception : public exception
{
	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
} myex;

void AssertEqual(std::string& value, std::string& expected)
{
	if (value != expected)
	{
		throw myex;
	}
}