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

#include <cstdio>
#include <memory>
#include <mutex>

namespace spdlog
{
namespace sinks
{

template <class Mutex>
class stdout_sink SPDLOG_FINAL : public base_sink<Mutex>
{
    using MyType = stdout_sink<Mutex>;
public:
    stdout_sink()
    {}
    static std::shared_ptr<MyType> instance()
    {
        static std::shared_ptr<MyType> instance = std::make_shared<MyType>();
        return instance;
    }
protected:
    void _sink_it(const details::log_msg& msg) override
    {
        fwrite(msg.formatted.data(), sizeof(char), msg.formatted.size(), stdout);
        _flush();
    }

    void _flush() override
    {
        fflush(stdout);
    }
};

typedef stdout_sink<details::null_mutex> stdout_sink_st;
typedef stdout_sink<std::mutex> stdout_sink_mt;


template <class Mutex>
class stderr_sink SPDLOG_FINAL : public base_sink<Mutex>
{
    using MyType = stderr_sink<Mutex>;
public:
    stderr_sink()
    {}
    static std::shared_ptr<MyType> instance()
    {
        static std::shared_ptr<MyType> instance = std::make_shared<MyType>();
        return instance;
    }
protected:
    void _sink_it(const details::log_msg& msg) override
    {
        fwrite(msg.formatted.data(), sizeof(char), msg.formatted.size(), stderr);
        _flush();
    }

    void _flush() override
    {
        fflush(stderr);
    }
};

typedef stderr_sink<std::mutex> stderr_sink_mt;
typedef stderr_sink<details::null_mutex> stderr_sink_st;
}
}
