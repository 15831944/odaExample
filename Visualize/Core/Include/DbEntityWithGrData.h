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




#ifndef _OD_DB_ENTITYWITHGRDATA_
#define _OD_DB_ENTITYWITHGRDATA_

#include "TD_PackPush.h"

#include "DbEntity.h"


/** \details
    This class is the Protocol Extension for OdTvDbEntity objects with stored graphics data.
    
    Corresponding C++ library: TD_Db
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbEntityWithGrDataPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbEntityWithGrDataPE);
  virtual bool worldDraw( const OdTvDbEntity* entity, OdGiWorldDraw* pWd ) const = 0;

  static void addX_to(OdRxClass* cls);
  static void delX_from(OdRxClass* cls);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbEntityWithGrData object pointers.
*/
typedef OdSmartPtr<OdTvDbEntityWithGrDataPE> OdTvDbEntityWithGrDataPEPtr;


inline void OdTvDbEntityWithGrDataPE::addX_to(OdRxClass* cls) {
  if (desc()) {
    OdTvDbEntityWithGrDataPEPtr grDataPeImpl = desc()->create();
    if (grDataPeImpl.get()) // dna: impl constructor initialized in OdTvDbIOModule::initApp()
      cls->addX(desc(), grDataPeImpl);
  }
}

inline void OdTvDbEntityWithGrDataPE::delX_from(OdRxClass* cls) {
  if (desc())
    cls->delX(desc());
}

#include "TD_PackPop.h"

#endif
