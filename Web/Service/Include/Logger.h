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

#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

#ifdef _MSC_VER
#define M_FUNCTION_DESCRIPTION_ __FUNCSIG__
#else
#define M_FUNCTION_DESCRIPTION_ __PRETTY_FUNCTION__
#endif

namespace OdWeb {

  class LogStream : public std::stringstream {
  public:
    enum class LogLevel {
      Info = 0,
      Error
    };

    static std::ofstream* g_logFilePtr;

    LogStream(const char* fileName, const char* functionName, long number, LogStream::LogLevel level, bool logFunction = true) {
      m_fileName = fileName;
      m_functionName = functionName;
      m_lineNumber = number;
      m_level = level;
      m_logFunction = logFunction;
    }

    ~LogStream() {
      switch (m_level) {
      case LogLevel::Info:
        g_logFilePtr == nullptr ? std::cout << "INFO - " : (*g_logFilePtr) << "INFO - ";
        break;
      case LogLevel::Error:
        g_logFilePtr == nullptr ? std::cout << "Error - " : (*g_logFilePtr) << "Error - ";
        break;
      }

      auto t = std::time(nullptr);
      auto tm = *std::localtime(&t);

      if (m_logFunction) {
        g_logFilePtr == nullptr ?

          std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << " - " << m_fileName << " - "
          << m_functionName << " - " << m_lineNumber << " - " << str() << std::endl :

          (*g_logFilePtr) << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << " - " << m_fileName << " - "
          << m_functionName << " - " << m_lineNumber << " - " << str() << std::endl;
      }
      else {
        g_logFilePtr == nullptr ?
          std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << " - " << str() << std::endl :
          (*g_logFilePtr) << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << " - " << str() << std::endl;
      }
    }

  private:
    std::string m_fileName;
    std::string m_functionName;
    long        m_lineNumber;
    LogLevel    m_level;
    std::string m_timePoint;
    bool m_logFunction;
  };

#define LogInfo()  LogStream(__FILE__, M_FUNCTION_DESCRIPTION_, __LINE__, LogStream::LogLevel::Info)
#define LogError() LogStream(__FILE__, M_FUNCTION_DESCRIPTION_, __LINE__, LogStream::LogLevel::Error)
#define LogInfoArg(logFunctionDesc)  LogStream(__FILE__, M_FUNCTION_DESCRIPTION_, __LINE__, LogStream::LogLevel::Info, logFunctionDesc)
#define LogErrorArg(logFunctionDesc)  LogStream(__FILE__, M_FUNCTION_DESCRIPTION_, __LINE__, LogStream::LogLevel::Error, logFunctionDesc)
}