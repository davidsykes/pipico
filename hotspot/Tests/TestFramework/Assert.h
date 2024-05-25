#pragma once
#include <string>

void AssertTrue(bool value);
void AssertFalse(bool value);
void AssertEqual(const char* value, const char* expected);
void AssertEqual(std::string &value, const char* expected);
void AssertEqual(std::string &value, std::string &expected);
void AssertEqual(const char value, const char expected);
void AssertEqualNonWhitespace(const char* value, const char* expected);
