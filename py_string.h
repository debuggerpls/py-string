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

    String copy() const
    {
        return String(str);
    }

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
        if (empty())
            return *this;

        str[0] = std::toupper(str[0]);
        for (unsigned i = 1; i < size(); ++i)
            str[i] = std::tolower(str[i]);

        return *this;
    }

    String& casefold()
    {
        for (auto& c : str)
            c = std::tolower(c);
        return *this;
    }

    bool contains(const char* string) const
    {
        if (!strlen(string))
            return false;

        return (str.find(string) != Not_found);
    }

    bool contains(const std::string& string) const
    {
        if (string.empty())
            return false;

        return (str.find(string) != Not_found);
    }

    bool contains(const String& string) const
    {
        if (string.empty())
            return false;

        return (str.find(string.str) != Not_found);
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

    size_type index(const char* value) const
    {
        return find(value);
    }

    size_type index(const std::string& value) const
    {
        return find(value);
    }

    size_type index(const String& value) const
    {
        return find(value);
    }

    bool isalpha() const
    {
        if (empty())
            return false;

        for (auto c : str)
            if (!std::isalpha(c))
                return false;

        return true;
    }

    bool isdigit() const
    {
        if (empty())
            return false;

        for (auto c : str)
            if (!std::isdigit(c))
                return false;

        return true;
    }

    bool isalnum() const
    {
        if (empty())
            return false;

        for (auto c : str)
            if (!std::isalnum(c))
                return false;

        return true;
    }

    bool islower() const
    {
        if (empty())
            return false;

        bool contains_lower = false;

        for (auto c : str) {
            contains_lower |= std::islower(c);
            if (!std::islower(c) && !std::isdigit(c) && !std::isspace(c) && !std::ispunct(c))
                return false;
        }

        return contains_lower;
    }

    bool isupper() const
    {
        if (empty())
            return false;

        bool contains_upper = false;

        for (auto c : str) {
            contains_upper |= std::isupper(c);
            if (!std::isupper(c) && !std::isdigit(c) && !std::isspace(c) && !std::ispunct(c))
                return false;
        }

        return contains_upper;
    }

    bool isspace() const
    {
        if (empty())
            return false;

        for (auto c : str) {
            if (!std::isspace(c))
                return false;
        }

        return true;
    }

    String& lower()
    {
        return casefold();
    }

    String& replace(const char* oldvalue, const char* newvalue)
    {
        for (size_type pos = 0; str.npos != (pos = str.find(oldvalue, pos, strlen(oldvalue))); pos += strlen(newvalue)) {
            str.replace(pos, strlen(oldvalue), newvalue, strlen(newvalue));
        }

        return *this;
    }

    size_type rfind(const char* value) const
    {
        return str.rfind(value);
    }

    size_type rfind(const std::string& value) const
    {
        return str.rfind(value);
    }

    size_type rfind(const String& value) const
    {
        return str.rfind(value.str);
    }

    size_type rindex(const char* value) const
    {
        return rfind(value);
    }

    size_type rindex(const std::string& value) const
    {
        return rfind(value);
    }

    size_type rindex(const String& value) const
    {
        return rfind(value);
    }

    bool startswith(const char* value) const
    {
        return str.find(value) == 0;
    }

    bool startswith(const std::string& value) const
    {
        return str.find(value) == 0;
    }

    bool startswith(const String& value) const
    {
        return str.find(value.c_str()) == 0;
    }

    String& lstrip(const char ch = ' ')
    {
        if (empty())
            return *this;

        auto pos = str.find_first_not_of(ch);
        if (pos != Not_found && pos != 0) {
            auto sz = size() - pos;
            str.replace(0, size(), str.c_str() + pos, sz);
        } else if (pos == Not_found && str.find_first_of(ch) != Not_found) {
            str.clear();
        }

        return *this;
    }

    String& lstrip(const char* string)
    {
        if (empty())
            return *this;

        auto pos = str.find_first_not_of(string);
        if (pos != Not_found && pos != 0) {
            auto sz = size() - pos;
            str.replace(0, size(), str.c_str() + pos, sz);
        } else if (pos == Not_found && str.find_first_of(string) != Not_found) {
            str.clear();
        }

        return *this;
    }

    String& lstrip(const std::string& string)
    {
        if (empty())
            return *this;

        auto pos = str.find_first_not_of(string);
        if (pos != Not_found && pos != 0) {
            auto sz = size() - pos;
            str.replace(0, size(), str.c_str() + pos, sz);
        } else if (pos == Not_found && str.find_first_of(string) != Not_found) {
            str.clear();
        }

        return *this;
    }

    String& lstrip(const String& string)
    {
        if (empty())
            return *this;

        auto pos = str.find_first_not_of(string.str);
        if (pos != Not_found && pos != 0) {
            auto sz = size() - pos;
            str.replace(0, size(), str.c_str() + pos, sz);
        } else if (pos == Not_found && str.find_first_of(string.str) != Not_found) {
            str.clear();
        }

        return *this;
    }

    String& rstrip(const char ch = ' ')
    {
        if (empty())
            return *this;

        auto pos = str.find_last_not_of(ch);
        if (pos != Not_found) {
            str.resize(pos + 1);
        } else if (str.find_first_of(ch) != Not_found) {
            str.clear();
        }

        return *this;
    }

    String& rstrip(const char* string)
    {
        if (empty())
            return *this;

        auto pos = str.find_last_not_of(string);
        if (pos != Not_found) {
            str.resize(pos + 1);
        } else if (str.find_first_of(string) != Not_found) {
            str.clear();
        }

        return *this;
    }

    String& rstrip(const std::string& string)
    {
        if (empty())
            return *this;

        auto pos = str.find_last_not_of(string);
        if (pos != Not_found) {
            str.resize(pos + 1);
        } else if (str.find_first_of(string) != Not_found) {
            str.clear();
        }

        return *this;
    }

    String& rstrip(const String& string)
    {
        if (empty())
            return *this;

        auto pos = str.find_last_not_of(string.str);
        if (pos != Not_found) {
            str.resize(pos + 1);
        } else if (str.find_first_of(string.str) != Not_found) {
            str.clear();
        }

        return *this;
    }

    String& strip(const char ch = ' ')
    {
        lstrip(ch);
        rstrip(ch);

        return *this;
    }

    String& strip(const char* string)
    {
        lstrip(string);
        rstrip(string);

        return *this;
    }

    String& strip(const std::string& string)
    {
        lstrip(string);
        rstrip(string);

        return *this;
    }

    String& strip(const String& string)
    {
        lstrip(string);
        rstrip(string);

        return *this;
    }

    String& swapcase()
    {
        for (auto& c : str) {
            if (std::isupper(c)) {
                c = std::tolower(c);
            } else if (std::islower(c)) {
                c = std::toupper(c);
            }
        }

        return *this;
    }

    String& upper()
    {
        for (auto& c : str)
            c = std::toupper(c);
        return *this;
    }

    String& zfill(size_type len)
    {
        if (len < size())
            return *this;

        auto sz = size();
        str.resize(len);
        str.replace(len - sz, sz, str.c_str(), sz);
        for (unsigned i = 0; i < len - sz; ++i)
            str[i] = '0';

        return *this;
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
