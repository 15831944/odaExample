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

#include "../details/log_msg.h"

namespace spdlog
{
namespace sinks
{
class sink
{
public:
    sink()
    {
        _level = level::trace;
    }

    virtual ~sink() {}
    virtual void log(const details::log_msg& msg) = 0;
    virtual void flush() = 0;

    bool should_log(level::level_enum msg_level) const;
    void set_level(level::level_enum log_level);
    level::level_enum level() const;

private:
    level_t _level;

};

inline bool sink::should_log(level::level_enum msg_level) const
{
    return msg_level >= _level.load(std::memory_order_relaxed);
}

inline void sink::set_level(level::level_enum log_level)
{
    _level.store(log_level);
}

inline level::level_enum sink::level() const
{
    return static_cast<spdlog::level::level_enum>(_level.load(std::memory_order_relaxed));
}

}
}

