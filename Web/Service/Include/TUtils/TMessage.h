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
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include "TWorkerState.h"
#include "TError.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>

#include "CloudLibTools.h"

namespace OdWeb {
using namespace rapidjson;
using namespace std;

typedef PrettyWriter<StringBuffer> TWriter;

enum TSenderType {
  WORKER,
  CONTROLLER,
  CLIENT,
  SERVER
};

enum TMessageType {
  KEEPALIVE,
  STATE,
  RESPONSE,
  CONFIG,
  COMMAND,
  EXCEPTION,
  WORKERS_INFO,
  KILL,
  GET_FREE_WORKER
};

class CLOUD_UTILS_EXPORT TBody {
public:
  TBody() {}
  virtual ~TBody() {}
  virtual void serialize(TWriter& writer) const {}
  virtual void parse(Value &body) {}
};
typedef shared_ptr<TBody> TBodyPtr;

class CLOUD_UTILS_EXPORT TWorkersInfo : public TBody {
  public:
    TWorkersInfo() {}

    ~TWorkersInfo() {}

    TWorkersInfo(const vector<TWorkerInfo>& workerInfo)
    : m_workersInfo(workerInfo) {}

    TWorkersInfo(const TWorkersInfo& obj)
    : TWorkersInfo(obj.m_workersInfo) {}

    void serialize (TWriter& writer) const override;

    void parse(Value& body) override;

    vector<TWorkerInfo> getWorkersInfo();
  private:
    vector<TWorkerInfo> m_workersInfo;
};

class CLOUD_UTILS_EXPORT TEmptyBody : public TBody {
  public:
    TEmptyBody() {}

    ~TEmptyBody() {}

    void serialize(TWriter& writer) const override;
};

class CLOUD_UTILS_EXPORT TStateBody : public TBody {
public:
  TStateBody();
  
  TStateBody(StateId state);
  
  ~TStateBody() override;

  TStateBody(const TStateBody& msg);

  void serialize(TWriter& writer) const override;

  void parse(Value &body) override;

  StateId getState();
private:
  StateId m_state;
};

class CLOUD_UTILS_EXPORT TKeepAliveBody : public TBody {
public:
  TKeepAliveBody() {}

  ~TKeepAliveBody() override {};

  TKeepAliveBody(const TKeepAliveBody& msg) {}
  
  TKeepAliveBody& operator=(const TKeepAliveBody& msg) { return *this; }

  void serialize(TWriter& writer) const override;

  void parse(Value &body) override {}
};

class CLOUD_UTILS_EXPORT TConfigBody : public TBody {
public:
  TConfigBody() {}
  
  TConfigBody(const string &host, int port)
    : m_host(host), m_port(port) {}
    
  ~TConfigBody() override {};

  TConfigBody(const TConfigBody& obj) {
    m_host = obj.m_host;
    m_port = obj.m_port;
  }

  TConfigBody& operator=(const TConfigBody& obj) { return *this; }

  void serialize(TWriter& writer) const override;

  void parse(Value &body) override {
    m_host = body["host"].GetString();
    m_port = body["port"].GetInt();
  }

  string getHost() const { return m_host; }
  int    getPort() const { return m_port; }

  void setHost(string &str) { m_host = str; }
  void setPort(int port)    { m_port = port; }

private:
  string m_host;
  int    m_port;
};

class CLOUD_UTILS_EXPORT TCommandBody : public TBody {
public:
  TCommandBody() {}
  
  TCommandBody(const string &name, vector<string> &args) 
    : m_name(name),
    m_args(args) {}

  ~TCommandBody() override {};

  TCommandBody(const TCommandBody& obj) {
    m_name = obj.m_name;
    m_args = obj.m_args;
  }

  TCommandBody& operator=(const TCommandBody& obj) { return *this; }

  void serialize(TWriter& writer) const override;

  void parse(Value &body) override;

  vector<string> getArgs() { return m_args; }

  string getName() { return m_name; }
private:
  string m_name;
  vector<string> m_args;
};

class CLOUD_UTILS_EXPORT TResponseBody : public TBody {
public:
  TResponseBody() {}
  
  TResponseBody(vector<string> &args)
    : m_args(args) {}

  ~TResponseBody() override {};

  TResponseBody(const TResponseBody& obj) {
    m_args = obj.m_args;
  }

  TResponseBody& operator=(const TResponseBody& obj) { return *this; }

  void serialize(TWriter& writer) const override;

  void parse(Value &body) override;

  vector<string> getAnswer() { return m_args; }
private:
  vector<string> m_args;
};

class CLOUD_UTILS_EXPORT TExceptionBody : public TBody {
public:
  TExceptionBody() {}
  TExceptionBody(string name, string decs, TErrorType error_code)
    : m_name(name), m_description(decs), m_error_code(error_code) {}

  ~TExceptionBody() override {};

  TExceptionBody(const TExceptionBody& obj) {
    m_name = obj.m_name;
    m_description = obj.m_description;
  }

  TExceptionBody& operator=(const TExceptionBody& obj) { return *this; }

  void serialize(TWriter& writer) const override;

  void parse(Value &body) override;

  string getName() { return m_name; }

  string getDescription() { return m_description; }
private:
  string m_name;
  string m_description;
  unsigned m_error_code;
};

class CLOUD_UTILS_EXPORT TKillBody : public TBody {
public:
  TKillBody() {}
  TKillBody(int id) : m_id(id) {}
  TKillBody(const TKillBody& obj) { m_id = obj.m_id; }

  ~TKillBody() override {};

  TKillBody& operator=(const TKillBody& obj) { return *this; }

  void serialize(TWriter& writer) const override;

  void parse(Value &body) override;

  int getId() { return m_id; }

private:
  int m_id;
};

class CLOUD_UTILS_EXPORT TFreeWorkerBody : public TBody {
public:
  TFreeWorkerBody() = default;
 
  TFreeWorkerBody(const TWorkerInfo& wInfo) : m_info(wInfo) {}

  TFreeWorkerBody(const TFreeWorkerBody& obj) {}

  ~TFreeWorkerBody() override {};

  TFreeWorkerBody& operator=(const TFreeWorkerBody& obj) { return *this; }

  void serialize(TWriter& writer) const override;

  void parse(Value &body) override;

  const std::map<std::string, std::string>& getOverrideArguments();
private:
  TWorkerInfo m_info;
  std::map<std::string, std::string> m_arguments;

};

class CLOUD_UTILS_EXPORT TBodyFactory {
private:
  typedef TBody* (*functionCreator)();
  typedef map <unsigned, functionCreator> FactoryMap;

  template<class BindType>
  static TBody* creator() { return new BindType(); }

  FactoryMap m_items;
public:
  TBodyFactory() {
    // Package for web controller - worker 
    add<TKeepAliveBody>(KEEPALIVE);
    add<TStateBody>(STATE);
    add<TConfigBody>(CONFIG); 
    // Package for web client - worker 
    add<TCommandBody>(COMMAND);
    add<TResponseBody>(RESPONSE);
    add<TExceptionBody>(EXCEPTION);
    // Packet for web server - controller
    add<TWorkersInfo>(WORKERS_INFO);
    add<TKillBody>(KILL);
    add<TFreeWorkerBody>(GET_FREE_WORKER);
  }

  template <class Derived>
  void add(unsigned key) { m_items[key] = &creator<Derived>; }

  TBody* create(unsigned key) {
    auto itr = m_items.find(key);
    if (itr != m_items.end())
      return itr->second();
    return nullptr;
  }
};

class CLOUD_UTILS_EXPORT TMessage {
public:
  TMessage() :
    m_version("0.1"),
    m_senderType(CLIENT),
    m_senderId(0),
    m_packetNum(0),
    m_packetType(0),
    m_body(NULL) {}

  TMessage(const string& data) { parse(data); }

  TMessage(const string& version, unsigned sender_type, unsigned sender_id, 
           unsigned packet_num, unsigned packet_type, TBody *body) 
    : m_version(version),
    m_senderType(sender_type),
    m_senderId(sender_id),
    m_packetNum(packet_num),
    m_packetType(packet_type),
    m_body(body) {}

  TMessage(const TMessage& msg) 
    : m_version(msg.m_version),
    m_senderType(msg.m_senderType),
    m_senderId(msg.m_senderId),
    m_packetNum(msg.m_packetNum),
    m_packetType(msg.m_packetType),
    m_body(msg.m_body) {}

  TMessage& operator=(const TMessage& msg) {
    m_version     = msg.m_version;
    m_senderType = msg.m_senderType;
    m_senderId   = msg.m_senderId;
    m_packetNum  = msg.m_packetNum;
    m_packetType = msg.m_packetType;
    m_body        = msg.getBody();
    return *this;
  }

  void serialize(TWriter& writer) const;

  template<typename TBodyClass>
  std::shared_ptr<TBodyClass> getBody() { 
    return static_pointer_cast<TBodyClass>(m_body);
  }

  TBodyPtr getBody() const { return m_body; }
  void setBody(TBody *body) { m_body.reset(body); }

  void parse(const string& str);

  string toString() const {
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    serialize(writer);
    return sb.GetString();
  }

  string   getVersion()    const { return m_version; }
  unsigned getSenderType() const { return m_senderType; }
  unsigned getSenderId()   const { return m_senderId; }
  unsigned getPacketNum()  const { return m_packetNum; }
  unsigned getPacketType() const { return m_packetType; }

private:
  string   m_version;
  unsigned m_senderType;
  unsigned m_senderId;
  unsigned m_packetNum;
  unsigned m_packetType;
  TBodyPtr m_body;
  
  TBodyFactory& getFactory() {
    static TBodyFactory factor;
    return factor;
  }
};

}
