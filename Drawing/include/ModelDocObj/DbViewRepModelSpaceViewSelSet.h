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

#ifndef OD_DBVIEWREPMODELSPACEVIEWSELSET_INCLUDED_
#define OD_DBVIEWREPMODELSPACEVIEWSELSET_INCLUDED_

#include "DbObject.h"
#include "ModelDocObjExports.h"

#include "TD_PackPush.h"

/** \details
    
    Corresponding C++ library:  AcModelDocObj

    <group OdModelDocObj_Classes> 
*/
class MODELDOCOBJ_EXPORT OdDbViewRepModelSpaceViewSelSet : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbViewRepModelSpaceViewSelSet);

  OdDbViewRepModelSpaceViewSelSet();
  //OdDbViewRepModelSpaceViewSelSet(const OdArray<OdDbObjectId>&);
  virtual ~OdDbViewRepModelSpaceViewSelSet();

  static bool getSelectedObjIdsForView(const OdDbObjectId&, OdArray<OdDbObjectId>&);

  void setSelectedObjIds(const OdArray<OdDbObjectId>&);
  OdArray<OdDbObjectId>& selectedObjIds();
  const OdArray<OdDbObjectId>& selectedObjIds() const;

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdDbViewRepModelSpaceViewSelSet> OdDbViewRepModelSpaceViewSelSetPtr;

#include "TD_PackPop.h"

#endif //OD_DBVIEWREPMODELSPACEVIEWSELSET_INCLUDED_
