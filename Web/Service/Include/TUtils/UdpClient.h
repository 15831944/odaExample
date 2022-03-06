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
#define ASIO_STANDALONE
#include "asio.hpp"
#include "OdaCommon.h"

#include <string>
#include <mutex>
#include <sstream>
 
#include "CloudLibTools.h"

namespace OdWeb {

  using std::string;
  using asio::ip::udp;
  using std::stringstream;

class CLOUD_UTILS_EXPORT UdpClient {
  public:
    int maxSize;

  private:
    std::mutex       m_mutex;
    bool             m_mock;
    asio::io_service m_ioService;
    udp::socket      m_socket;
    udp::endpoint    m_endpoint;

  public:
    UdpClient();

    void config(const string &host, int port);

    void sendString(const string& str);
  };
}
