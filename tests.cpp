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

        for (auto it = py_str.begin(); it != py_str.end(); ++it) {
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

    SUBCASE("Insert char at str_index")
    {
        CHECK(py_str.insert(5, ',') == "Hello, world");
    }

    SUBCASE("Insert char* at str_index")
    {
        CHECK(py_str.insert(6, "dear ") == "Hello dear world");
    }

    SUBCASE("Insert String at str_index")
    {
        CHECK(py_str.insert(6, String("dear ")) == "Hello dear world");
    }

    SUBCASE("Insert std::string at str_index")
    {
        CHECK(py_str.insert(6, std::string("dear ")) == "Hello dear world");
    }

    SUBCASE("Delete character at str_index")
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

TEST_CASE("Casefold a string")
{
    CHECK(String("Hello world 123").casefold() == "hello world 123");
}

TEST_CASE("Count value appearings in string")
{
    CHECK(String("I like apples, my favourite food is apples").count("apples") == 2);
    CHECK(String("I like apples, my favourite food is apples").count("!") == 0);
    CHECK(String("I like apples, my favourite food is apples").count(String("apples")) == 2);
    CHECK(String("I like apples, my favourite food is apples").count(std::string("apples")) == 2);
}

TEST_CASE("Endswith method")
{
    CHECK(String("Hello world.").endswith(".") == true);
    CHECK(String("Hello world.").endswith("world.") == true);
    CHECK(String("Hello world.").endswith("!") == false);
    CHECK(String("Hello world.").endswith(std::string("ld.")) == true);
    CHECK(String("Hello world.").endswith(String(".")) == true);
}

TEST_CASE("Find value in string")
{
    CHECK(String("").find("hi") == Not_found);
    CHECK(String("Hello world").find("worl") == 6);
    CHECK(String("Hello world").find(String("worl")) == 6);
    CHECK(String("Hello world").find(std::string("worl")) == 6);

    CHECK(String("").index("hi") == Not_found);
    CHECK(String("Hello world").index("worl") == 6);
}

TEST_CASE("Check if all chars are in the alphabet")
{
    SUBCASE("No special chars like spaces")
    {
        CHECK(String("hello").isalpha() == true);
        CHECK(String("TesLa").isalpha() == true);
    }

    SUBCASE("Special chars like spaces")
    {
        CHECK(String("hello world").isalpha() == false);
        CHECK(String("").isalpha() == false);
        CHECK(String("\n\t").isalpha() == false);
    }
}

TEST_CASE("Check if all chars are digits")
{
    CHECK(String("hello").isdigit() == false);
    CHECK(String().isdigit() == false);
    CHECK(String("123455").isdigit() == true);
}

TEST_CASE("Check if all chars are alphanumeric")
{
    CHECK(String().isalnum() == false);
    CHECK(String("123455aZd").isalnum() == true);
    CHECK(String("! 2131").isalnum() == false);
}

TEST_CASE("Check if all chars are lowercase")
{
    CHECK(String().islower() == false);
    CHECK(String(" ").islower() == false);
    CHECK(String("123455aZd").islower() == false);
    CHECK(String("hello world!").islower() == true);
    CHECK(String("hello123").islower() == true);
}

TEST_CASE("Check if all chars are uppercase")
{
    CHECK(String().isupper() == false);
    CHECK(String(" ").isupper() == false);
    CHECK(String("123455aZd").isupper() == false);
    CHECK(String("HELLO WORLD!").isupper() == true);
    CHECK(String("HELLO123.").isupper() == true);
}
