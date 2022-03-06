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
#include "OdaCommon.h"
#include <fstream>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "CloudLibTools.h"

using namespace std;

namespace OdWeb {

typedef unique_ptr<ifstream, function<void(ifstream*)>> UpIFStream;

class CLOUD_UTILS_EXPORT TConfigReader {
public:
  TConfigReader() {};
  TConfigReader(const string& fileName);
  void readConfig();
  virtual void setIp(const string& ip) = 0;
  virtual void setWorkerCount(const int count) = 0;
  virtual string ip() = 0;
  virtual int workersCount() = 0;
  virtual int workersTimeout() = 0;
  virtual string workersPath() = 0;
  virtual string fileDirectory() = 0;
  virtual int backendPort() = 0;
  virtual int frontendPort() = 0;
  virtual void setBackendPort(const int port) = 0;
  virtual void setFrontendPort(const int port) = 0;
  virtual int getStartDelay() = 0;
  virtual vector<string> getModules() = 0;

  virtual void setClientInterface(const string& ip) = 0;
  virtual string getClientInterface() = 0;
  virtual string getLogPath() = 0;
  virtual void setRotate(const int count) = 0;
  virtual int getRotate() = 0;
  virtual bool isLogDebug() = 0;
  virtual string getSslCertPath() = 0;
  virtual string getSslKeyPath() = 0;
  virtual string getSslPassword() = 0;

  virtual string getStatsdIp() = 0;
  virtual int getStatsdPort() = 0;

  virtual void setDefault() = 0;
  virtual void saveToFile(const string& path) = 0;

  string getFileName() { return m_fileName; };

 protected:
  virtual void parse(const UpIFStream& ifs) {};

 protected:
  string m_fileName;
};

}  // namespace OdWeb
