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

#pragma once;

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "TStringConverter.h"

#include "OdaCommon.h"
#include "OdString.h"
#include "RxDictionary.h"
#include "RxVariantValue.h"

namespace OdWeb {
  class Settings {
  public:
    Settings() {
      m_settins = ::odrxSysRegistry()->getAt(L"WEB_COMMAND_SETTINGS_SET");
      if (m_settins.isNull()) {
        ::odrxSysRegistry()->putAt(L"WEB_COMMAND_SETTINGS_SET", OdRxDictionary::createObject());
      }
      m_settins = ::odrxSysRegistry()->getAt(L"WEB_COMMAND_SETTINGS_SET");
    }

    OdRxVariantValue get(const OdString& name) {
      return OdRxVariantValue(m_settins->getAt(name));
    }

    void set(const OdString& name, const OdString& value) {
      OdString fixedName = name;
      m_settins->putAt(fixedName.makeLower(), OdRxVariantValue(value));
    }

  private:
    OdRxDictionaryPtr m_settins;
  };
}