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
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#ifndef _ODDbModelDocViewStyleIMPL_INCLUDED_
#define _ODDbModelDocViewStyleIMPL_INCLUDED_

#include "DbModelDocViewStyle.h"

#include "DbSystemInternals.h"
//#include "DbColor.h"
#include "DbObjectImpl.h"
//#include "OdValue.h"

class OdTvDbModelDocViewStyleImpl : public OdTvDbObjectImpl
{
  static OdTvDbModelDocViewStyleImpl* getImpl(const OdTvDbModelDocViewStyle* pObj)
  { 
    return (OdTvDbModelDocViewStyleImpl*) OdTvDbSystemInternals::getImpl(pObj);
  }
protected:
  OdTvDbModelDocViewStyleImpl();
  virtual void setDefault(OdTvDbObject* pObj, OdTvDbDatabase* pDb = NULL);

  // OdTvDbObjectImpl overridden
  virtual void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  OdResult setViewLabelPattern(OdTvDbModelDocViewStyle* pOwner, OdString& oldPattern, const OdString& newPattern, const OdTvDbField* pField); //to avoid using of duplicate code in Section and DetailViewStyle

  friend  class OdTvDbModelDocViewStyle;

  void clear();

  OdString m_description;
  bool m_isCurrent;
  OdString m_DisplayName;
  OdUInt32 m_flags;
};

#endif // _ODDbModelDocViewStyleIMPL_INCLUDED_
