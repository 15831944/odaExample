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
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#ifndef _ODDBHYPERLINKEX_INCLUDED_
#define _ODDBHYPERLINKEX_INCLUDED_

#include "DbStdAfx.h"
#include "DbHyperlinkImpl.h"

class OdDbEntityHyperlinkPEImplEx : public OdDbEntityHyperlinkPEImpl
{
public:
  OdDbEntityHyperlinkPEImplEx() {};

  void getFieldHyperlinks(OdDbField* field, OdDbHyperlinkCollection* coll, bool bOneOnly)
  {
    if(!field)
      return;
    if(bOneOnly && coll->count())
      return;
    getHyperlinks(field, coll, bOneOnly);
    for(OdUInt32 i = 0; i < field->childCount(); ++i)
      getFieldHyperlinks(OdDbField::cast(field->getChild(i, OdDb::kForRead)), coll, bOneOnly);
  }

  OdDbHyperlinkCollectionPtr getHyperlinkCollectionEx(const OdRxObject* obj,
    bool bOneOnly, bool bIgnoreBlockDefinition) ODRX_OVERRIDE
  {
    OdDbHyperlinkCollectionPtr pColl = getHyperlinkCollection(obj, bOneOnly, bIgnoreBlockDefinition);
    OdDbObjectPtr pObj = obj;
    getFieldHyperlinks(OdDbField::cast(pObj->getField(OD_T("TEXT"), OdDb::kForRead)), pColl, bOneOnly);
    return pColl;
  };

};

#endif //_ODDBHYPERLINKEX_INCLUDED_
