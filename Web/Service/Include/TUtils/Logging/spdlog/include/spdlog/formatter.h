///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance").
// All rights reserved.
//
// This software and its documentation and related materials are owned by
// the Alliance. The software may only be incorporated into application
// programs owned by members of the Alliance, subject to a signed
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable
// trade secrets of the Alliance and its suppliers. The software is also
// protected by copyright law and international treaty provisions. Application
// programs incorporating this software must include the following statement
// with their copyright notices:
//
//   This application incorporates Open Design Alliance software pursuant to a
//   license agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance.
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

#include "details/log_msg.h"

#include <vector>
#include <string>
#include <memory>

namespace spdlog
{
namespace details
{
class flag_formatter;
}

class formatter
{
public:
    virtual ~formatter() {}
    virtual void format(details::log_msg& msg) = 0;
};

class pattern_formatter SPDLOG_FINAL : public formatter
{

public:
    explicit pattern_formatter(const std::string& pattern, pattern_time_type pattern_time = pattern_time_type::local, const std::string& eol = spdlog::details::os::default_eol);
    pattern_formatter(const pattern_formatter&) = delete;
    pattern_formatter& operator=(const pattern_formatter&) = delete;
    void format(details::log_msg& msg) override;
private:
    const std::string _eol;
    const std::string _pattern;
    const pattern_time_type _pattern_time;
    std::vector<std::unique_ptr<details::flag_formatter>> _formatters;
    std::tm get_time(details::log_msg& msg);
    void handle_flag(char flag);
    void compile_pattern(const std::string& pattern);
};
}

#include "details/pattern_formatter_impl.h"

