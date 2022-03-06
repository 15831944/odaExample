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
#ifndef _DBLAYERSTATEMANAGERIMPL_H_INCLUDED_
#define _DBLAYERSTATEMANAGERIMPL_H_INCLUDED_

#include "DbLayerState.h"
#define STL_USING_SET
#include "OdaSTL.h"

class OdDbLayerStateManagerImpl
{
public:
  OdArray<OdDbLayerStateManagerReactorPtr> m_Reactors;
  OdDbDatabase* m_pDatabase;
  OdString m_sLastState;
  std::set<OdDbObjectId> m_xrefStateIds;
private:
  static OdDbLayerStateManagerImpl* getImpl(const OdDbLayerStateManager* pLsMgr)
  { return (OdDbLayerStateManagerImpl*)pLsMgr->m_pImpl;}
  friend class OdDbDatabase;
  friend void xrefLayerStates(OdDbIdMapping* pIdMap, const OdString& xrefName);
  friend void odDbCleanXrefLayerStates(OdDbDatabase* pHostDb, OdDbDatabase* pXrefDb, bool bRemoveFromIdMap, bool bRemoveFromMgrSet);
};

#endif //_DBLAYERSTATEMANAGERIMPL_H_INCLUDED_
