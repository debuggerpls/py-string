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
        CHECK(String { "test" } == "test");
    }

    SUBCASE("Size")
    {
        CHECK(String("hello").size() == 5);
        CHECK(String("hello").len() == 5);
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

    SUBCASE("Positive indexes")
    {
        CHECK(py_str[0] == 'H');
        CHECK(py_str[4] == 'o');
    }

    SUBCASE("Negative indexes")
    {
        CHECK(py_str[-1] == 'd');
        CHECK(py_str[-5] == 'w');
    }

    SUBCASE("Looping through string")
    {
        for (auto c : py_str) {
            CHECK(typeid(c) == typeid(char));
        }

        for (auto& c : py_str) {
            c += 1;
            CHECK(typeid(c) == typeid(char));
        }

        for (auto it = begin(py_str); it != end(py_str); ++it) {
            CHECK(typeid(*it) == typeid(char));
        }
    }
}

TEST_CASE("Slicing strings")
{
    String py_str { "Hello world" };

    SUBCASE("Using slice methods")
    {
        CHECK(py_str.slice(0, 4) == "Hello");
        CHECK(py_str.slice(-2, -1) == "ld");
        CHECK(py_str.slice(3, 2) == "");
    }

    SUBCASE("Using operator()")
    {
        CHECK(py_str(0, 4) == "Hello");
        CHECK(py_str(-2, -1) == "ld");
        CHECK(py_str(3, 2) == "");
    }
}

TEST_CASE("Appending, inserting and deleting characters")
{
    String py_str { "Hello world" };

    SUBCASE("Append character or string")
    {
        std::string s { "s" };
        py_str += 's';
        CHECK(py_str == "Hello worlds");
        py_str += "s";
        CHECK(py_str == "Hello worldss");
        py_str += s;
        CHECK(py_str == "Hello worldsss");
    }

    SUBCASE("Add strings or characters together")
    {
        std::string s { "s" };
        CHECK((py_str + 's') == "Hello worlds");
        CHECK(('s' + py_str) == "sHello world");
        CHECK((py_str + String("!")) == "Hello world!");
        CHECK((py_str + s) == "Hello worlds");
        CHECK((s + py_str) == "sHello world");
    }

    SUBCASE("Insert char at index")
    {
        CHECK(py_str.insert(5, ',') == "Hello, world");
    }

    SUBCASE("Insert char* at index")
    {
        CHECK(py_str.insert(6, "dear ") == "Hello dear world");
    }

    SUBCASE("Insert String at index")
    {
        CHECK(py_str.insert(6, String("dear ")) == "Hello dear world");
    }

    SUBCASE("Insert std::string at index")
    {
        CHECK(py_str.insert(6, std::string("dear ")) == "Hello dear world");
    }

    SUBCASE("Delete character at index")
    {
        CHECK(py_str.del(5) == "Helloworld");
        CHECK(py_str.del(-1) == "Helloworl");
    }
}

TEST_CASE("Capitalize string")
{
    CHECK(String("hello world").capitalize() == "Hello world");
    CHECK(String("123 number").capitalize() == "123 number");
    CHECK(String().capitalize() == "");
}
