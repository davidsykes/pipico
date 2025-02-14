#include <iostream>
#include "../rest/tests/RestLibraryTests.h"

int main()
{
    std::cout << "Running tests...\n";
    RestLibraryTests().RunTests();
    std::cout << "Tests Complete.\n";
};

