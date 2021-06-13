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
constexpr auto Not_found = std::string::npos;

struct String {
    using size_type = std::string::size_type;

    String(std::string str)
        : str(std::move(str))
    {
    }

    String(const char* str)
        : str(str)
    {
    }

    String() = default;

    size_type str_index(int rel_pos) const
    {
        return static_cast<size_type>(rel_pos >= 0 ? rel_pos : size() + rel_pos);
    }

    bool empty() const
    {
        return str.empty();
    }

    size_type size() const
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
        return str[str_index(pos)];
    }

    const char& operator[](int pos) const
    {
        return str[str_index(pos)];
    }

    const char* begin() const
    {
        return &str[0];
    }

    const char* end() const
    {
        return &str[size()];
    }

    char* begin()
    {
        return &str[0];
    }

    char* end()
    {
        return &str[size()];
    }

    /* from and to indexes are included */
    String slice(int from, int to) const
    {
        return from > to ? String() : String(str.substr(str_index(from), str_index(to) + 1));
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
        str.insert(str_index(pos), 1, c);
        return *this;
    }

    String& insert(int pos, const char* string)
    {
        str.insert(str_index(pos), string);
        return *this;
    }

    String& insert(int pos, const String& string)
    {
        str.insert(str_index(pos), string.c_str());
        return *this;
    }

    String& insert(int pos, const std::string& string)
    {
        str.insert(str_index(pos), string);
        return *this;
    }

    String& del(int pos)
    {
        str.erase(str_index(pos), 1);
        return *this;
    }

    String& capitalize()
    {
        if (!empty())
            str[0] = std::toupper(str[0]);
        return *this;
    }

    String& casefold()
    {
        for (auto& c : str)
            c = tolower(c);
        return *this;
    }

    size_type count(const char* value, int start_pos = 0) const
    {
        if (empty())
            return 0;

        size_type cnt = 0;
        size_type pos = str_index(start_pos);
        auto npos = std::string::npos;
        while (pos != npos) {
            pos = str.find(value, pos);
            if (pos != npos) {
                ++cnt;
                pos += strlen(value);
            }
        }

        return cnt;
    }

    size_type count(const String& value, int start_pos = 0) const
    {
        return count(value.c_str(), start_pos);
    }

    size_type count(const std::string& value, int start_pos = 0) const
    {
        return count(value.c_str(), start_pos);
    }

    bool endswith(const char* value) const
    {
        return str.rfind(value) == str.size() - strlen(value);
    }

    bool endswith(const std::string& value) const
    {
        return str.rfind(value) == str.size() - value.size();
    }

    bool endswith(const String& value) const
    {
        return str.rfind(value.c_str()) == str.size() - value.size();
    }

    size_type find(const char* value) const
    {
        return str.find(value);
    }

    size_type find(const std::string& value) const
    {
        return str.find(value);
    }

    size_type find(const String& value) const
    {
        return str.find(value.str);
    }

    std::string str {};
};

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

}
