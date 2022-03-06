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

#ifndef _ODDBXLATEFILERIMPL_INCLUDED_
#define _ODDBXLATEFILERIMPL_INCLUDED_

#include "OdDwgCopyFiler.h"
#include "SmartPtr.h"

class OdDbXlateFilerImpl;
class OdDbIdMapping;

class OdDbXlateFilerImpl : public OdDbDwgCopyFiler<>
{
protected:
  bool m_bTranslateOnlyInFuxObject;
  OdDbIdMapping* m_pIdMapping;
  OdDbFiler::FilerType filerType() const;
  bool usesReferences() const;
  OdDbObjectId rdSoftOwnershipId();
  OdDbObjectId rdHardOwnershipId();
  OdDbObjectId rdHardPointerId();
  OdDbObjectId rdSoftPointerId();
  inline OdDbObjectId validate(const OdDbObjectId &id)
  {
    return (id.database()==database() ? id : OdDbObjectId::kNull);
  }
public:
  ODRX_DECLARE_MEMBERS(OdDbXlateFilerImpl);

  OdDbXlateFilerImpl() : m_bTranslateOnlyInFuxObject(true), m_pIdMapping(0) {}
  OdDbXlateFilerImpl(OdDbIdMapping* pIdMapping);
  void setIdMapping(OdDbIdMapping* pIdMapping){m_pIdMapping = pIdMapping;}
  void setTranslateOnlyInFluxObjects(bool v){m_bTranslateOnlyInFuxObject = v;}
  void translateObjectIds(OdDbObject* pObj);
  void translateIds(OdDbIdMapping& idMap);
};

typedef OdSmartPtr<OdDbXlateFilerImpl> OdDbXlateFilerImplPtr;


#endif //_ODDBXLATEFILERIMPL_INCLUDED_
