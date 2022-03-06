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
//
// base sink templated over a mutex (either dummy or real)
// concrete implementation should only override the _sink_it method.
// all locking is taken care of here so no locking needed by the implementers..
//

#include "sink.h"
#include "../formatter.h"
#include "../common.h"
#include "../details/log_msg.h"

#include <mutex>

namespace spdlog
{
namespace sinks
{
template<class Mutex>
class base_sink:public sink
{
public:
    base_sink():_mutex() {}
    virtual ~base_sink() = default;

    base_sink(const base_sink&) = delete;
    base_sink& operator=(const base_sink&) = delete;

    void log(const details::log_msg& msg) SPDLOG_FINAL override
    {
        std::lock_guard<Mutex> lock(_mutex);
        _sink_it(msg);
    }
    void flush() SPDLOG_FINAL override
    {
        std::lock_guard<Mutex> lock(_mutex);
        _flush();
    }

protected:
    virtual void _sink_it(const details::log_msg& msg) = 0;
    virtual void _flush() = 0;
    Mutex _mutex;
};
}
}
