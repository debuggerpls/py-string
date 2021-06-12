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
    String(std::string str)
        : str(std::move(str))
    {
    }

    bool empty() const
    {
        return str.empty();
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

}
