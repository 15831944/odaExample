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
// Copyright(c) 2016 Alexander Dalshov.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

#if defined(_WIN32)

#include "base_sink.h"
#include "../details/null_mutex.h"

#include <winbase.h>

#include <mutex>
#include <string>

namespace spdlog
{
namespace sinks
{
/*
* MSVC sink (logging using OutputDebugStringA)
*/
template<class Mutex>
class msvc_sink : public base_sink < Mutex >
{
public:
    explicit msvc_sink()
    {
    }



protected:
    void _sink_it(const details::log_msg& msg) override
    {
        OutputDebugStringA(msg.formatted.c_str());
    }

    void _flush() override
    {}
};

typedef msvc_sink<std::mutex> msvc_sink_mt;
typedef msvc_sink<details::null_mutex> msvc_sink_st;

}
}

#endif
