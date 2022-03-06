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

// Helper class for file sink
// When failing to open a file, retry several times(5) with small delay between the tries(10 ms)
// Throw spdlog_ex exception on errors

#include "../details/os.h"
#include "../details/log_msg.h"

#include <chrono>
#include <cstdio>
#include <string>
#include <thread>
#include <tuple>
#include <cerrno>

namespace spdlog
{
namespace details
{

class file_helper
{

public:
    const int open_tries = 5;
    const int open_interval = 10;

    explicit file_helper() :
        _fd(nullptr)
    {}

    file_helper(const file_helper&) = delete;
    file_helper& operator=(const file_helper&) = delete;

    ~file_helper()
    {
        close();
    }


    void open(const filename_t& fname, bool truncate = false)
    {

        close();
        auto *mode = truncate ? SPDLOG_FILENAME_T("wb") : SPDLOG_FILENAME_T("ab");
        _filename = fname;
        for (int tries = 0; tries < open_tries; ++tries)
        {
            if (!os::fopen_s(&_fd, fname, mode))
                return;

            details::os::sleep_for_millis(open_interval);
        }

        throw spdlog_ex("Failed opening file " + os::filename_to_str(_filename) + " for writing", errno);
    }

    void reopen(bool truncate)
    {
        if (_filename.empty())
            throw spdlog_ex("Failed re opening file - was not opened before");
        open(_filename, truncate);

    }

    void flush()
    {
        std::fflush(_fd);
    }

    void close()
    {
        if (_fd)
        {
            std::fclose(_fd);
            _fd = nullptr;
        }
    }

    void write(const log_msg& msg)
    {
        size_t msg_size = msg.formatted.size();
        auto data = msg.formatted.data();
        if (std::fwrite(data, 1, msg_size, _fd) != msg_size)
            throw spdlog_ex("Failed writing to file " + os::filename_to_str(_filename), errno);
    }

    size_t size() const
    {
        if (!_fd)
            throw spdlog_ex("Cannot use size() on closed file " + os::filename_to_str(_filename));
        return os::filesize(_fd);
    }

    const filename_t& filename() const
    {
        return _filename;
    }

    static bool file_exists(const filename_t& fname)
    {
        return os::file_exists(fname);
    }

    //
    // return file path and its extension:
    //
    // "mylog.txt" => ("mylog", ".txt")
    // "mylog" => ("mylog", "")
    // "mylog." => ("mylog.", "")
    // "/dir1/dir2/mylog.txt" => ("/dir1/dir2/mylog", ".txt")
    //
    // the starting dot in filenames is ignored (hidden files):
    //
    // ".mylog" => (".mylog". "")
    // "my_folder/.mylog" => ("my_folder/.mylog", "")
    // "my_folder/.mylog.txt" => ("my_folder/.mylog", ".txt")
    static std::tuple<filename_t, filename_t> split_by_extenstion(const spdlog::filename_t& fname)
    {
        auto ext_index = fname.rfind('.');

        // no valid extension found - return whole path and empty string as extension
        if (ext_index == filename_t::npos || ext_index == 0 || ext_index == fname.size() - 1)
            return std::make_tuple(fname, spdlog::filename_t());

        // treat casese like "/etc/rc.d/somelogfile or "/abc/.hiddenfile"
        auto folder_index = fname.rfind(details::os::folder_sep);
        if (folder_index != fname.npos && folder_index >= ext_index - 1)
            return std::make_tuple(fname, spdlog::filename_t());

        // finally - return a valid base and extension tuple
        return std::make_tuple(fname.substr(0, ext_index), fname.substr(ext_index));
    }
private:
    FILE* _fd;
    filename_t _filename;
};
}
}
