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
#include "docopt.h"
#include <string>
#include <map>

#include "CloudLibTools.h"

using namespace std;
namespace OdWeb {
typedef map<std::string, docopt::value> ParamsMap;

class CLOUD_UTILS_EXPORT TInputParserImpl {
public:
  TInputParserImpl(const std::string &usageTemplate);

  void parse(int argc, const char** argv);

  string getOption(const std::string& param);

  bool hasOption(const std::string& param);

  bool isNotEmpty(const std::string& param);

  ParamsMap getOptions();
private:
  ParamsMap m_args;
  string    m_usage;
};
};
