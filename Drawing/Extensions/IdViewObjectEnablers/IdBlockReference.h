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

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of the "Object enabler" for AcIdBlockReference ("Id" - short for "Inventor Drawing")

#ifndef IDBLOCKREFERENCE_INCLUDED
#define IDBLOCKREFERENCE_INCLUDED

#include "TD_PackPush.h"

#include "DbBlockReference.h"
#include "DbFiler.h"
#include "DbBlockTableRecord.h"
#include "Gi/GiViewportDraw.h"
#include "IdViewExport.h"

/** \details
    This class implements the object enabler for block references exported from 
	drawings created with Autodesk� Inventor�.

    Library: Id
    <group OdId_Classes> 
*/
class IDVIEW_EXPORT OdIdBlockReference : public OdDbBlockReference
{
  OdDbObjectId m_pVportId; 
public:
  ODDB_DECLARE_MEMBERS(OdIdBlockReference);
  OdIdBlockReference(){};

  OdDbObjectId vportId()  const     { return m_pVportId; }
  void setVportId(OdDbObjectId id)  { m_pVportId = id; }

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;

  bool subWorldDraw(OdGiWorldDraw* pWd) const;

  void subViewportDraw(OdGiViewportDraw* pViewportDraw) const;

  OdResult subExplode(OdRxObjectPtrArray& entitySet) const;

  // Converts OdIdBlockReference in Model Space to OdDbBlockReference.
  // Viewport transformation is added to new OdDbBlockReference
  // If pBlockRecord is Null than owner of Viewport (Paper Space block) is used.
  // So instead of OdIdBlockReference in MS OdDbBlockReference in PS is created
  // preserving visual representation
  OdResult explodeGeometryToBlock(OdDbBlockTableRecord *pBlockRecord, OdDbObjectIdArray *ids);

  virtual OdDbObjectPtr decomposeForSave(
    OdDb::SaveType format, 
    OdDb::DwgVersion ver, 
    OdDbObjectId& replaceId, 
    bool& exchangeXData);
};

#include "TD_PackPop.h"

#endif  // IDBLOCKREFERENCE_INCLUDED

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

