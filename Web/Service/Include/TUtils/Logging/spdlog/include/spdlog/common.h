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

#define SPDLOG_VERSION "0.16.3"

#include "tweakme.h"

#include <string>
#include <initializer_list>
#include <chrono>
#include <memory>
#include <atomic>
#include <exception>
#include<functional>

#if defined(_WIN32) && defined(SPDLOG_WCHAR_FILENAMES)
#include <codecvt>
#include <locale>
#endif

#include "details/null_mutex.h"

//visual studio upto 2013 does not support noexcept nor constexpr
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define SPDLOG_NOEXCEPT throw()
#define SPDLOG_CONSTEXPR
#else
#define SPDLOG_NOEXCEPT noexcept
#define SPDLOG_CONSTEXPR constexpr
#endif

// final keyword support. On by default. See tweakme.h
#if defined(SPDLOG_NO_FINAL)
#define SPDLOG_FINAL
#else
#define SPDLOG_FINAL final
#endif

#if defined(__GNUC__)  || defined(__clang__)
#define SPDLOG_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define SPDLOG_DEPRECATED __declspec(deprecated)
#else
#define SPDLOG_DEPRECATED
#endif

#include "fmt/fmt.h"

namespace spdlog
{

class formatter;

namespace sinks
{
class sink;
}

using log_clock = std::chrono::system_clock;
using sink_ptr = std::shared_ptr < sinks::sink >;
using sinks_init_list = std::initializer_list < sink_ptr >;
using formatter_ptr = std::shared_ptr<spdlog::formatter>;
#if defined(SPDLOG_NO_ATOMIC_LEVELS)
using level_t = details::null_atomic_int;
#else
using level_t = std::atomic<int>;
#endif

using log_err_handler = std::function<void(const std::string &err_msg)>;

//Log level enum
namespace level
{
typedef enum
{
    trace = 0,
    debug = 1,
    info = 2,
    warn = 3,
    err = 4,
    critical = 5,
    off = 6
} level_enum;

#if !defined(SPDLOG_LEVEL_NAMES)
#define SPDLOG_LEVEL_NAMES { "trace", "debug", "info",  "warning", "error", "critical", "off" }
#endif
static const char* level_names[] SPDLOG_LEVEL_NAMES;

static const char* short_level_names[] { "T", "D", "I", "W", "E", "C", "O" };

inline const char* to_str(spdlog::level::level_enum l)
{
    return level_names[l];
}

inline const char* to_short_str(spdlog::level::level_enum l)
{
    return short_level_names[l];
}
using level_hasher = std::hash<int>;

} //level


//
// Async overflow policy - block by default.
//
enum class async_overflow_policy
{
    block_retry, // Block / yield / sleep until message can be enqueued
    discard_log_msg // Discard the message it enqueue fails
};

//
// Pattern time - specific time getting to use for pattern_formatter.
// local time by default
//
enum class pattern_time_type
{
    local, // log localtime
    utc    // log utc
};

//
// Log exception
//
namespace details
{
namespace os
{
std::string errno_str(int err_num);
}
}
class spdlog_ex: public std::exception
{
public:
    spdlog_ex(const std::string& msg):_msg(msg)
    {}
    spdlog_ex(const std::string& msg, int last_errno)
    {
        _msg = msg + ": " + details::os::errno_str(last_errno);
    }
    const char* what() const SPDLOG_NOEXCEPT override
    {
        return _msg.c_str();
    }
private:
    std::string _msg;

};

//
// wchar support for windows file names (SPDLOG_WCHAR_FILENAMES must be defined)
//
#if defined(_WIN32) && defined(SPDLOG_WCHAR_FILENAMES)
using filename_t = std::wstring;
#else
using filename_t = std::string;
#endif


} //spdlog
