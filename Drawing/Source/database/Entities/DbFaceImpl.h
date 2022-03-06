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

#ifndef _ODDBFACEIMPL_INCLUDED_
#define _ODDBFACEIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "Gi/Gi.h"
#include "DbSystemInternals.h"
#include "DbFace.h"

class OdDbFaceImpl : public OdDbEntityImpl
{
  static OdDbFaceImpl* getImpl(const OdDbFace *pObj)
  { return (OdDbFaceImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdGePoint3d m_Points[4];
  OdUInt8     m_FaceFlags;

public:
  OdDbFaceImpl() : m_FaceFlags(0) {}
  OdGiVisibility edgeVisiblity(OdUInt16 number) const
  {
    if(number > 3)
    {
      throw OdError_InvalidIndex();
    }
    return ((m_FaceFlags & (1 << number)) == 0 ? kOdGiVisible : kOdGiInvisible);
  }

private:
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  friend class OdDbFace;
};

#endif // _ODDBFACEIMPL_INCLUDED_
