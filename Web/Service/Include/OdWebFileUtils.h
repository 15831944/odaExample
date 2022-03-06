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
#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <locale>
#include <iomanip>
#include <codecvt>

#include <stdio.h>

#if defined(_WIN32)
#include <direct.h>
#include <stdlib.h>
#include <windows.h>    //GetModuleFileNameW
#define GetCurrentDir _getcwd
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <unistd.h>     //readlink
#define GetCurrentDir getcwd
#endif

#include "OdWebStringUtils.h"

using namespace std;

namespace OdWeb {
  class FileUtils {
  public:
    static void copyFile(const std::string& originalPath, const std::string& copyPath) {
      ifstream source(originalPath, ios::binary);
      ofstream dest(copyPath, ios::binary);

      dest << source.rdbuf();

      source.close();
      dest.close();
    }

    static bool isFileExits(const std::string& path) {
      ifstream file;
      file.open(path);
      bool res = file.is_open();
      file.close();
      return res;
    }

    static std::string getFileExtension(const std::string& filePath) {
      auto tokens = StringUtils::split(filePath, '.');
      return tokens.empty() ? "" : tokens.back();
    }

    static bool checkExistsDirectory(const std::string& path) {
#if defined(_WIN32)
      struct _stat info;
      std::wstring_convert<codecvt_utf8<wchar_t>> converter;
      if (_wstat(converter.from_bytes(path).c_str(), &info) == 0) {
        return info.st_mode & S_IFDIR;
      }
      return false;
#else
      struct stat info;
      if (stat(path.c_str(), &info) == 0)
        return S_ISDIR(info.st_mode);
      return false;
#endif
    }

    static bool createDirectory(const std::string& path) {
#if defined(_WIN32)
      std::wstring_convert<codecvt_utf8<wchar_t>> converter;
      return _wmkdir(converter.from_bytes(path).c_str()) == 0;
#else
      return mkdir(path.c_str(), 0733) == 0;
#endif
    }

    static bool removeDirectory(const std::string& path) {
#if defined(_WIN32)
      std::wstring_convert<codecvt_utf8<wchar_t>> converter;
      return _wrmdir(converter.from_bytes(path).c_str()) == 0;
#else
      return rmdir(path.c_str()) == 0;
#endif
    }

    static void removeFiles(const std::string& folder, const std::vector<std::string>& files) {
      for (auto& file : files) {
        remove((folder + "/" + file).c_str());
      }
    }

    static std::string getDirnameFromPath(const std::string& fname)
    {
      size_t pos = fname.find_last_of("\\/");
      return (std::string::npos == pos)
        ? ""
        : fname.substr(0, pos);
    }

    static std::string getCurrentWorkingDir() {
      std::string workingDir = "";

#ifdef _WIN32
      char path[260] = { 0 };
      GetModuleFileNameA(NULL, path, 260);
      workingDir = path;
#else
      char result[PATH_MAX];
      ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
      workingDir = std::string(result, (count > 0) ? count : 0);
#endif

      string::size_type pos = workingDir.find_last_of("\\/");

      return workingDir.substr(0, pos);
    }
  };
}