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

    char& operator[](int i)
    {
        return i < 0 ? str[str.size() + i] : str[i];
    }

    const char& operator[](int i) const
    {
        return i < 0 ? str[str.size() + i] : str[i];
    }

    /* from and to indexes are included */
    String slice(int from, int to) const
    {
        return from > to ? String() : String(str.substr(static_cast<size_type>(from >= 0 ? from : len() + from), static_cast<size_type>(to >= 0 ? to + 1 : len() + to + 1)));
    }

    String operator()(int from, int to) const
    {
        return slice(from, to);
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
