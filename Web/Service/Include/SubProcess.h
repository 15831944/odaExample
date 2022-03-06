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
#include <cstdlib>
#include <vector>
#include <thread>
#include <sstream>
#include "Logger.h"

using namespace std;

namespace OdWeb {
  class SubProcess {
  private:
    string m_command;
    vector<string> m_argument;
    bool m_isRunning;
    int m_Code;

    void setIsRun(bool isRun) {
      m_isRunning = isRun;
    }

    void setResult(int code) {
      m_Code = code;
    }

    static void execute(SubProcess* subProcess) {
      LogInfo() << "start execute job";
      subProcess->setIsRun(true);
      std::stringstream stream;

#if defined(_WIN32)
      stream << "\"";
#endif
      stream << "\"" << subProcess->getCommand() << "\" ";
      for (auto& arg : subProcess->getArguments()) stream << "\"" << arg << "\" ";

#if defined(_WIN32)
      stream << "\"";
#endif

      const string str = stream.str();

      LogInfo() << "run file converter with arguments " << str;

      int code = system(str.c_str());

      subProcess->setResult(code);
      subProcess->setIsRun(false);
      LogInfo() << "converter finished with code " << code;
    }
  public:
    SubProcess() {
      m_isRunning = false;
      m_Code = -1;
    }

    void setCommand(const string& command) {
      m_command = command;
    }

    string getCommand() {
      return m_command;
    }

    vector<string> getArguments() {
      return m_argument;
    }

    void setArguments(const vector<string>& arguments) {
      m_argument = arguments;
    }

    bool getIsRunning() {
      return m_isRunning;
    }

    int getResult() {
      return m_Code;
    }

    void cancel() {
      //TODO
    }

    void start() {
      m_isRunning = true;
      std::thread(SubProcess::execute, this).detach();
    }
  };
}
