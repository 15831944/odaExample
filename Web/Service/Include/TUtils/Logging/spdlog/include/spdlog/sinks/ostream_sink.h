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

#include "../details/null_mutex.h"
#include "base_sink.h"

#include <ostream>
#include <mutex>

namespace spdlog
{
namespace sinks
{
template<class Mutex>
class ostream_sink: public base_sink<Mutex>
{
public:
    explicit ostream_sink(std::ostream& os, bool force_flush=false) :_ostream(os), _force_flush(force_flush) {}
    ostream_sink(const ostream_sink&) = delete;
    ostream_sink& operator=(const ostream_sink&) = delete;
    virtual ~ostream_sink() = default;

protected:
    void _sink_it(const details::log_msg& msg) override
    {
        _ostream.write(msg.formatted.data(), msg.formatted.size());
        if (_force_flush)
            _ostream.flush();
    }

    void _flush() override
    {
        _ostream.flush();
    }

    std::ostream& _ostream;
    bool _force_flush;
};

typedef ostream_sink<std::mutex> ostream_sink_mt;
typedef ostream_sink<details::null_mutex> ostream_sink_st;
}
}
