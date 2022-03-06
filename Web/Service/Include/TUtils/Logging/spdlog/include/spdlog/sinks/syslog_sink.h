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

#include "../common.h"

#ifdef SPDLOG_ENABLE_SYSLOG

#include "sink.h"
#include "../details/log_msg.h"

#include <array>
#include <string>
#include <syslog.h>


namespace spdlog
{
namespace sinks
{
/**
 * Sink that write to syslog using the `syscall()` library call.
 *
 * Locking is not needed, as `syslog()` itself is thread-safe.
 */
class syslog_sink : public sink
{
public:
    //
    syslog_sink(const std::string& ident = "", int syslog_option=0, int syslog_facility=LOG_USER):
        _ident(ident)
    {
        _priorities[static_cast<int>(level::trace)] = LOG_DEBUG;
        _priorities[static_cast<int>(level::debug)] = LOG_DEBUG;
        _priorities[static_cast<int>(level::info)] = LOG_INFO;
        _priorities[static_cast<int>(level::warn)] = LOG_WARNING;
        _priorities[static_cast<int>(level::err)] = LOG_ERR;
        _priorities[static_cast<int>(level::critical)] = LOG_CRIT;
        _priorities[static_cast<int>(level::off)] = LOG_INFO;

        //set ident to be program name if empty
        ::openlog(_ident.empty()? nullptr:_ident.c_str(), syslog_option, syslog_facility);
    }
    ~syslog_sink()
    {
        ::closelog();
    }

    syslog_sink(const syslog_sink&) = delete;
    syslog_sink& operator=(const syslog_sink&) = delete;

    void log(const details::log_msg &msg) override
    {
        ::syslog(syslog_prio_from_level(msg), "%s", msg.raw.str().c_str());
    }

    void flush() override
    {
    }


private:
    std::array<int, 7> _priorities;
    //must store the ident because the man says openlog might use the pointer as is and not a string copy
    const std::string _ident;

    //
    // Simply maps spdlog's log level to syslog priority level.
    //
    int syslog_prio_from_level(const details::log_msg &msg) const
    {
        return _priorities[static_cast<int>(msg.level)];
    }
};
}
}

#endif
