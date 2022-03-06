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

#include "TConfigReader.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include <utility>

#include "CloudLibTools.h"

using namespace rapidjson;

namespace OdWeb {

class CLOUD_UTILS_EXPORT TConfigReaderJSON : public TConfigReader {
public:
  TConfigReaderJSON() {};

  TConfigReaderJSON(const string &fileName)
  : TConfigReader(fileName){}

  virtual void parse(const UpIFStream& ifs) override;
  
  string ip() override;
  void setIp(const string& ip) override;

  int backendPort() override;
  void setBackendPort(const int port) override;

  int frontendPort() override;
  void setFrontendPort(const int port) override;
  
  int workersCount() override;
  void setWorkerCount(const int count) override;

  void setWorkersTimeout(int timeout);
  int workersTimeout() override;

  string workersPath() override;
  std::pair<unsigned, unsigned> portsRange();
  string fileDirectory() override;
  int getStartDelay() override;

  void setModules(const vector<string>& vec);
  vector<string> getModules() override;

  void setClientInterface(const string& ip) override;
  string getClientInterface() override;
  string getLogPath() override;

  void setRotate(const int count) override;
  int getRotate() override;

  bool isLogDebug() override;
  // SSL ---
  string getSslCertPath() override;
  string getSslKeyPath() override;
  string getSslPassword() override;

  // statsD ---
  string getStatsdIp() override;
  int getStatsdPort() override;

  void setDefault() override;
  void saveToFile(const string& path) override;

  std::string toString();

  //     ---
private:
  string                   m_tcIp;
  int                      m_tcBackendPort;
  int                      m_tcFrontendPort;
  int                      m_tcCount;
  string                   m_twPath;
  string                   m_twFileDirectory;
  string                   m_tcLogPath;
  int                      m_rotate;
  bool                     m_tcLogDebug;

  pair<unsigned, unsigned> m_twPortRange;
  int                      m_twTimeout;
  int                      m_twStartDelay;
  string                   m_twClientInterface;
  vector<string>           m_twModules;
  string                   m_twSslCertPath;
  string                   m_twSslKeyPath;
  string                   m_twSslPassword;

  string                   m_tcStatsdIp;
  unsigned int             m_tcStatsdPort;

  std::shared_ptr<Document> m_doc;
private:
  void assertHasMember(const string &name, const Value &doc);

  void extractIp(const Document &doc);
  void extractBackendPort(const Document &doc);
  void extractFrontendPort(const Document &doc);
  void extractWorkerCount(const Document &doc);
  void extractWorkerPath(const Document &doc);
  void extractFileDirectory(const Document &doc);
  void extractLogPath(const Document &doc);
  void extractRotate(const Document& doc);
  void extractLogDebug(const Document &doc);

  void extractPortRange(const Document &doc);
  void extractTimeout(const Document &doc);
  void extractStartDelay(const Document &doc);
  void extractClientInterface(const Document &doc);
  void extractModules(const Document &doc);
  void extractSslCertPath(const Document &doc);
  void extractSslPassword(const Document &doc);
  void extractSslKeyPath(const Document &doc);
  void extractStatsdIp(const Document &doc);
  void extractStatsdPort(const Document &doc);
  
  void printAllSetting();
};

}  // namespace OdWeb
