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

#ifndef _DBDYNAMICBLOCKPURGEPREVENTER__INCLUDED_
#define _DBDYNAMICBLOCKPURGEPREVENTER__INCLUDED_

#include "DbBlockRepresentationData.h"
#include "DbEvalGraph.h"
#include "RxDictionary.h"

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbDynamicBlockPurgePreventer : public OdTvDbBlockRepresentationData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbDynamicBlockPurgePreventer);
  static OdSmartPtr<OdTvDbDynamicBlockPurgePreventer> safeCreateByClassName();
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  OdTvDbDynamicBlockPurgePreventer();
};

typedef OdSmartPtr<OdTvDbDynamicBlockPurgePreventer> OdTvDbDynamicBlockPurgePreventerPtr;

inline OdTvDbDynamicBlockPurgePreventerPtr OdTvDbDynamicBlockPurgePreventer::safeCreateByClassName() {
  return ::odrxSafeCreateObject<OdTvDbDynamicBlockPurgePreventer>("AcTvDbDynamicBlockPurgePreventer", "TD_DynBlock");
}



#endif // _DBDYNAMICBLOCKPURGEPREVENTER__INCLUDED_
