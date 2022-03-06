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

// Thread safe logger (except for set_pattern(..), set_formatter(..) and set_error_handler())
// Has name, log level, vector of std::shared sink pointers and formatter
// Upon each log write the logger:
// 1. Checks if its log level is enough to log the message
// 2. Format the message using the formatter function
// 3. Pass the formatted message to its sinks to performa the actual logging

#include "sinks/base_sink.h"
#include "common.h"

#include <vector>
#include <memory>
#include <string>

namespace spdlog
{

class logger
{
public:
    logger(const std::string& logger_name, sink_ptr single_sink);
    logger(const std::string& name, sinks_init_list);
    template<class It>
    logger(const std::string& name, const It& begin, const It& end);

    virtual ~logger();
    logger(const logger&) = delete;
    logger& operator=(const logger&) = delete;


    template <typename... Args> void log(level::level_enum lvl, const char* fmt, const Args&... args);
    template <typename... Args> void log(level::level_enum lvl, const char* msg);
    template <typename Arg1, typename... Args> void trace(const char* fmt, const Arg1&, const Args&... args);
    template <typename Arg1, typename... Args> void debug(const char* fmt, const Arg1&, const Args&... args);
    template <typename Arg1, typename... Args> void info(const char* fmt, const Arg1&, const Args&... args);
    template <typename Arg1, typename... Args> void warn(const char* fmt, const Arg1&, const Args&... args);
    template <typename Arg1, typename... Args> void error(const char* fmt, const Arg1&, const Args&... args);
    template <typename Arg1, typename... Args> void critical(const char* fmt, const Arg1&, const Args&... args);


#ifdef SPDLOG_WCHAR_TO_UTF8_SUPPORT
    template <typename... Args> void log(level::level_enum lvl, const wchar_t* msg);
    template <typename... Args> void log(level::level_enum lvl, const wchar_t* fmt, const Args&... args);
    template <typename... Args> void trace(const wchar_t* fmt, const Args&... args);
    template <typename... Args> void debug(const wchar_t* fmt, const Args&... args);
    template <typename... Args> void info(const wchar_t* fmt, const Args&... args);
    template <typename... Args> void warn(const wchar_t* fmt, const Args&... args);
    template <typename... Args> void error(const wchar_t* fmt, const Args&... args);
    template <typename... Args> void critical(const wchar_t* fmt, const Args&... args);
#endif // SPDLOG_WCHAR_TO_UTF8_SUPPORT

    template <typename T> void log(level::level_enum lvl, const T&);
    template <typename T> void trace(const T&);
    template <typename T> void debug(const T&);
    template <typename T> void info(const T&);
    template <typename T> void warn(const T&);
    template <typename T> void error(const T&);
    template <typename T> void critical(const T&);

    bool should_log(level::level_enum) const;
    void set_level(level::level_enum);
    level::level_enum level() const;
    const std::string& name() const;
    void set_pattern(const std::string&, pattern_time_type = pattern_time_type::local);
    void set_formatter(formatter_ptr);

    // automatically call flush() if message level >= log_level
    void flush_on(level::level_enum log_level);

    virtual void flush();

    const std::vector<sink_ptr>& sinks() const;

    // error handler
    virtual void set_error_handler(log_err_handler);
    virtual log_err_handler error_handler();

protected:
    virtual void _sink_it(details::log_msg&);
    virtual void _set_pattern(const std::string&, pattern_time_type);
    virtual void _set_formatter(formatter_ptr);

    // default error handler: print the error to stderr with the max rate of 1 message/minute
    virtual void _default_err_handler(const std::string &msg);

    // return true if the given message level should trigger a flush
    bool _should_flush_on(const details::log_msg&);

    // increment the message count (only if defined(SPDLOG_ENABLE_MESSAGE_COUNTER))
    void _incr_msg_counter(details::log_msg &msg);

    const std::string _name;
    std::vector<sink_ptr> _sinks;
    formatter_ptr _formatter;
    spdlog::level_t _level;
    spdlog::level_t _flush_level;
    log_err_handler _err_handler;
    std::atomic<time_t> _last_err_time;
    std::atomic<size_t> _msg_counter;
};
}

#include "details/logger_impl.h"
