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

// Async Logger implementation
// Use an async_sink (queue per logger) to perform the logging in a worker thread

#include "../details/async_log_helper.h"
#include "../async_logger.h"

#include <string>
#include <functional>
#include <chrono>
#include <memory>

template<class It>
inline spdlog::async_logger::async_logger(const std::string& logger_name,
        const It& begin,
        const It& end,
        size_t queue_size,
        const  async_overflow_policy overflow_policy,
        const std::function<void()>& worker_warmup_cb,
        const std::chrono::milliseconds& flush_interval_ms,
        const std::function<void()>& worker_teardown_cb) :
    logger(logger_name, begin, end),
    _async_log_helper(new details::async_log_helper(_formatter, _sinks, queue_size, _err_handler, overflow_policy, worker_warmup_cb, flush_interval_ms, worker_teardown_cb))
{
}

inline spdlog::async_logger::async_logger(const std::string& logger_name,
        sinks_init_list sinks_list,
        size_t queue_size,
        const  async_overflow_policy overflow_policy,
        const std::function<void()>& worker_warmup_cb,
        const std::chrono::milliseconds& flush_interval_ms,
        const std::function<void()>& worker_teardown_cb) :
    async_logger(logger_name, sinks_list.begin(), sinks_list.end(), queue_size, overflow_policy, worker_warmup_cb, flush_interval_ms, worker_teardown_cb) {}

inline spdlog::async_logger::async_logger(const std::string& logger_name,
        sink_ptr single_sink,
        size_t queue_size,
        const  async_overflow_policy overflow_policy,
        const std::function<void()>& worker_warmup_cb,
        const std::chrono::milliseconds& flush_interval_ms,
        const std::function<void()>& worker_teardown_cb) :
    async_logger(logger_name,
{
    single_sink
}, queue_size, overflow_policy, worker_warmup_cb, flush_interval_ms, worker_teardown_cb) {}


inline void spdlog::async_logger::flush()
{
    _async_log_helper->flush(true);
}

// Error handler
inline void spdlog::async_logger::set_error_handler(spdlog::log_err_handler err_handler)
{
    _err_handler = err_handler;
    _async_log_helper->set_error_handler(err_handler);

}
inline spdlog::log_err_handler spdlog::async_logger::error_handler()
{
    return _err_handler;
}


inline void spdlog::async_logger::_set_formatter(spdlog::formatter_ptr msg_formatter)
{
    _formatter = msg_formatter;
    _async_log_helper->set_formatter(_formatter);
}

inline void spdlog::async_logger::_set_pattern(const std::string& pattern, pattern_time_type pattern_time)
{
    _formatter = std::make_shared<pattern_formatter>(pattern, pattern_time);
    _async_log_helper->set_formatter(_formatter);
}


inline void spdlog::async_logger::_sink_it(details::log_msg& msg)
{
    try
    {
#if defined(SPDLOG_ENABLE_MESSAGE_COUNTER)
        _incr_msg_counter(msg);
#endif
        _async_log_helper->log(msg);
        if (_should_flush_on(msg))
            _async_log_helper->flush(false); // do async flush
    }
    catch (const std::exception &ex)
    {
        _err_handler(ex.what());
    }
    catch(...)
    {
        _err_handler("Unknown exception in logger " + _name);
        throw;
    }

}
