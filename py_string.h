/* Copyright (c) 2021 Deividas Puplauskas
 *
 * Distributed under the MIT Software License
 * See accompanying file LICENSE.txt or copy at
 * https://opensource.org/licenses/MIT
 */

#pragma once

#include <string>
#include <utility>

namespace py_str {

struct String {

    using size_type = std::string::size_type;

    String(std::string str)
        : str(std::move(str))
    {
    }

    String() = default;

    size_type index(int pos) const
    {
        return static_cast<size_type>(pos >= 0 ? pos : size() + pos);
    }

    bool empty() const
    {
        return str.empty();
    }

    std::string::size_type size() const
    {
        return str.size();
    }

    size_type len() const
    {
        return size();
    }

    const char* c_str() const
    {
        return str.c_str();
    }

    char& operator[](int pos)
    {
        return str[index(pos)];
    }

    const char& operator[](int pos) const
    {
        return str[index(pos)];
    }

    /* from and to indexes are included */
    String slice(int from, int to) const
    {
        return from > to ? String() : String(str.substr(index(from), index(to) + 1));
    }

    String operator()(int from, int to) const
    {
        return slice(from, to);
    }

    String& operator+=(char c)
    {
        str += c;
        return *this;
    }

    String& operator+=(const char* string)
    {
        str += string;
        return *this;
    }

    String& operator+=(const std::string& string)
    {
        str += string;
        return *this;
    }

    String& insert(int pos, char c)
    {
        str.insert(index(pos), 1, c);
        return *this;
    }

    String& insert(int pos, const char* string)
    {
        str.insert(index(pos), string);
        return *this;
    }

    String& insert(int pos, const String& string)
    {
        str.insert(index(pos), string.c_str());
        return *this;
    }

    String& insert(int pos, const std::string& string)
    {
        str.insert(index(pos), string);
        return *this;
    }

    String& del(int pos)
    {
        str.erase(index(pos), 1);
        return *this;
    }

    String& capitalize()
    {
        if (!empty())
            str[0] = std::toupper(str[0]);
        return *this;
    }

    std::string str {};
};

bool operator==(const String& lhs, const std::string& rhs)
{
    return lhs.str == rhs;
}

bool operator==(const std::string& lhs, const String& rhs)
{
    return lhs == rhs.str;
}

bool operator==(const String& lhs, const String& rhs)
{
    return lhs.str == rhs.str;
}

std::ostream& operator<<(std::ostream& out, const String& string)
{
    out << string.str;
    return out;
}

String operator+(const String& lhs, const String& rhs)
{
    return String(lhs.str + rhs.str);
}

String operator+(const String& lhs, const std::string& rhs)
{
    return String(lhs.str + rhs);
}

String operator+(const String& lhs, const char& rhs)
{
    return String(lhs.str + rhs);
}

String operator+(const char lhs, const String& rhs)
{
    return String(lhs + rhs.str);
}

const char* begin(const String& string)
{
    return &string[0];
}

const char* end(const String& string)
{
    return &string[string.len()];
}

char* begin(String& string)
{
    return &string[0];
}

char* end(String& string)
{
    return &string[string.len()];
}

}
