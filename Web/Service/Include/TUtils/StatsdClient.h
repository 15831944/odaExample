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

#include "UdpClient.h"
#include "OdaCommon.h"


#include <string>
#include <memory>
#include <sstream>

#include "CloudLibTools.h"

namespace OdWeb {
  using std::string;
  using std::vector;

  class CLOUD_UTILS_EXPORT StatsdClient {
  public:
    static StatsdClient& getInstance();

    string prefix();

    string suffix();

    void setPrefix(const string& prefix);

    void setSuffix(const string& suffix);

    void config(const string &ip, int port);

    void send(const string &str);

    void sendStat(const string &stat, float value, const string &type);

    void sendStat(const string &stat, const string &value, const string &type);

    void timing(const string &stat, int time = 1);

    void increment(const string &stat, int value = 1);

    void decrement(const string &stat, int value = -1);

    void histogram(const string &stat, float value);

    void gauge(const string &stat, float value);

    void set(const string &stat, const string &value);

    void unique(const string &stat, const string &value);

  private:
      UdpClient m_client;
      string    m_prefix;
      string    m_suffix;
      /*
        Singleton class
        using getInstance()
      */
      StatsdClient();
  };
}
