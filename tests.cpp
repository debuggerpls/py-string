#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "py_string.h"

#include <cstdio>
#include <iostream>

using namespace py_str;

TEST_CASE("Construct, compare and print strings")
{
    std::string str1 { "String \t123!.," };

    // TODO: add move constructors and assignments
    String py_str1 { str1 };
    String py_str2 = str1;
    String py_str3 { str1 };
    REQUIRE(!py_str1.empty());
    REQUIRE(!py_str2.empty());
    REQUIRE(!py_str3.empty());

    SUBCASE("Compare strings")
    {
        CHECK(py_str1 == py_str2);
        CHECK(py_str1 == str1);
        CHECK(py_str2 == str1);
        CHECK(str1 == py_str1);
        CHECK(str1 == py_str2);
        CHECK(py_str1 == py_str3);
    }

    SUBCASE("Print strings")
    {
        CHECK(printf("Testing print: %s\n", py_str1.c_str()) > 0);
        std::cout << "Testing print: " << py_str1 << std::endl;
    }
}

TEST_CASE("Indexing strings")
{
    String py_str { "Hello world" };

    SUBCASE("Positive indexes") {
        CHECK(py_str[0] == 'H');
        CHECK(py_str[4] == 'o');
    }

    SUBCASE("Negative indexes") {
        CHECK(py_str[-1] == 'd');
        CHECK(py_str[-5] == 'w');
    }
}