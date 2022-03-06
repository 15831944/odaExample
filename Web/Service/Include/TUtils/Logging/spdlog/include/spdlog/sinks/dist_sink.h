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
// Copyright (c) 2015 David Schury, Gabi Melman
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

#include "../details/log_msg.h"
#include "../details/null_mutex.h"
#include "base_sink.h"
#include "sink.h"

#include <algorithm>
#include <mutex>
#include <memory>
#include <vector>

// Distribution sink (mux). Stores a vector of sinks which get called when log is called

namespace spdlog
{
namespace sinks
{
template<class Mutex>
class dist_sink: public base_sink<Mutex>
{
public:
    explicit dist_sink() :_sinks() {}
    dist_sink(const dist_sink&) = delete;
    dist_sink& operator=(const dist_sink&) = delete;
    virtual ~dist_sink() = default;

protected:
    std::vector<std::shared_ptr<sink>> _sinks;

    void _sink_it(const details::log_msg& msg) override
    {
        for (auto &sink : _sinks)
        {
            if( sink->should_log( msg.level))
            {
                sink->log(msg);
            }
        }
    }

    void _flush() override
    {
        for (auto &sink : _sinks)
            sink->flush();
    }

public:


    void add_sink(std::shared_ptr<sink> sink)
    {
        std::lock_guard<Mutex> lock(base_sink<Mutex>::_mutex);
        _sinks.push_back(sink);
    }

    void remove_sink(std::shared_ptr<sink> sink)
    {
        std::lock_guard<Mutex> lock(base_sink<Mutex>::_mutex);
        _sinks.erase(std::remove(_sinks.begin(), _sinks.end(), sink), _sinks.end());
    }
};

typedef dist_sink<std::mutex> dist_sink_mt;
typedef dist_sink<details::null_mutex> dist_sink_st;
}
}
