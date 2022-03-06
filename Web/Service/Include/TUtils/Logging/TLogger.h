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

#ifdef _MSC_VER 
#define M_FUNCTION_DESCRIPTION_ __FUNCSIG__
#else
#define M_FUNCTION_DESCRIPTION_ __PRETTY_FUNCTION__
#endif

#ifdef __linux__
#define SPDLOG_ENABLE_SYSLOG
#endif

#include "OdaCommon.h"
#include "spdlog.h"
#include "TError.hpp"
#include "CloudLibTools.h"
#include <sstream>

namespace OdWeb {

  enum LogLevel
  {
    Info = 0,
    Error,
    Debug
  };

struct CLOUD_UTILS_EXPORT TLoggerSetting {
  std::string name;
  std::string ip;
  std::string filePath;
  int processID;
  bool isDebugLevelLogging;
  int rotate;
};

using namespace spdlog;


class CLOUD_UTILS_EXPORT TLoggerSpdImpl {
public:

  void init(const TLoggerSetting& setting) {
    if (setting.filePath == "syslog") {
#ifdef __linux__
      size_t q_size = 4096;
      std::string ident = "spdlog";

      spdlog::set_async_mode(q_size, spdlog::async_overflow_policy::block_retry, nullptr, std::chrono::seconds(2));
      spdlog::set_pattern("%n - %D %T | " + std::to_string(setting.processID) + " | %l | %v");

      m_loggerConsole = spdlog::stdout_color_mt(setting.name + "_" + std::to_string(setting.processID));
      m_logger = spdlog::syslog_logger("syslog", setting.name, LOG_PID);

      if (setting.isDebugLevelLogging == true) {
        m_logger->set_level(level::debug);
      }
#else 
      throw TError("Your platform does not support a syslog", TErrorType::INTERNAL_ERROR);
#endif
    }
    else {
      size_t q_size = 4096;
      spdlog::set_async_mode(q_size, spdlog::async_overflow_policy::block_retry, nullptr, std::chrono::seconds(2));
      spdlog::set_pattern("%n - %D %T | " + std::to_string(setting.processID) + " | %l | %v");

      m_loggerConsole = spdlog::stdout_color_mt(setting.name + "_" + std::to_string(setting.processID));
      m_logger        = spdlog::rotating_logger_mt(setting.name, setting.filePath, 10000000, setting.rotate - 1);
     
      if (setting.isDebugLevelLogging == true) {
        m_logger->set_level(level::debug);
      }
    }
  }

  void debug(const std::string& msg) {
    if (m_logger)        m_logger->debug(msg);
    if (m_loggerConsole) m_loggerConsole->debug(msg);
  }

  void info(const std::string& msg) {
    if (m_logger)        m_logger->info(msg);
    if (m_loggerConsole) m_loggerConsole->info(msg);
  }

  void error(const std::string& msg) {
    if (m_logger)        m_logger->error(msg);
    if (m_loggerConsole) m_loggerConsole->error(msg);
  }

private:
  typedef std::shared_ptr<logger> LoggerPtr;

  LoggerPtr m_logger;
  LoggerPtr m_loggerConsole;
};

class CLOUD_UTILS_EXPORT TLogger {
public:
  static void init(const TLoggerSetting &setting);

  static void debug(const char* fName, const char* method, long line, const std::string& msg);

  static void info(const char* fName, const char* method, long line, const std::string& msg);

  static void error(const char* fName, const char* method, long line, const std::string& msg);

  static std::string loggerName;

private:
  static TLoggerSpdImpl impl;
};

class CLOUD_UTILS_EXPORT TLogMessageStream : public std::stringstream {
public:
  TLogMessageStream(const char* fileName, const char* functionName, long number, LogLevel level);

  ~TLogMessageStream();

private:
  std::string fileName;
  std::string functionName;
  long        lineNumber;
  LogLevel    level;
};

#define TLogInfo()  TLogMessageStream(__FILE__, M_FUNCTION_DESCRIPTION_, __LINE__, OdWeb::Info)
#define TLogError() TLogMessageStream(__FILE__, M_FUNCTION_DESCRIPTION_, __LINE__, OdWeb::Error)
#define TLogDebug() TLogMessageStream(__FILE__, M_FUNCTION_DESCRIPTION_, __LINE__, OdWeb::Debug)
}
