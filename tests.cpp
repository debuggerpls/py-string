#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "py_string.h"

using namespace py_str;

TEST_CASE("Construct, compare and print strings")
{
    std::string str1 { "String \n123!.," };

    String py_str1 { str1 };
    String py_str2 = str1;
    String py_str3 { str1 };
    REQUIRE(!py_str1.empty());
    REQUIRE(!py_str2.empty());

    SUBCASE("Compare strings")
    {
        CHECK(py_str1 == py_str2);
        CHECK(py_str1 == str1);
        CHECK(py_str2 == str1);
        CHECK(str1 == py_str1);
        CHECK(str1 == py_str2);
        CHECK(py_str1 == py_str3);
    }
}