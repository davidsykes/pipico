#pragma once
#include <string>

[[noreturn]] void Assert(const char* message);
void AssertTrue(bool value);
void AssertFalse(bool value);
void AssertEqual(const char* value, const char* expected);
void AssertEqual(std::string value, const char* expected);
void AssertEqual(std::string value, std::string expected);
void AssertEqual(const size_t value, const size_t expected);
void AssertEqualNonWhitespace(const char* value, const char* expected);
