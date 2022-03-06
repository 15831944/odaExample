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


#ifndef OD_DxfLoadResolverForDimension_H
#define OD_DxfLoadResolverForDimension_H

#include "DbDxfLoader.h"

class DxfLoadResolverForDimension : public OdRxObjectImpl<DxfLoadResolver>
{
  DxfLoadResolverForDimension & operator = (const DxfLoadResolverForDimension&);

protected:
  OdTvDbObjectId    m_id;
  OdString        m_blockName;

  DxfLoadResolverForDimension(OdTvDbObjectId id, OdString name)
    : OdRxObjectImpl<DxfLoadResolver>()
    , m_id(id)
    , m_blockName(name)
  {}

public:
  static DxfLoadResolverPtr createObject(OdTvDbObjectId id, OdString name)
  {
    return DxfLoadResolverPtr(
      (DxfLoadResolver*)new DxfLoadResolverForDimension(id, name), kOdRxObjAttach);
  }

  virtual void resolve()
  {
    if (!m_id.isErased())
    {
      OdTvDbDimensionPtr pEnt = m_id.safeOpenObject(OdDb::kForWrite);
      OdTvDbObjectId id = OdTvDbSymUtil::getBlockId(m_blockName, pEnt->database());
      pEnt->setDimBlockId(id);
    }
  }
};

#endif
