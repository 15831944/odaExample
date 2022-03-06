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

#ifndef _ODDBVIEWREPIMAGEIMPL_INCLUDED_
#define _ODDBVIEWREPIMAGEIMPL_INCLUDED_

#include "DbViewRepImage.h"
#include "DbEntityImpl.h"

class OdDbViewRepImageImpl : public OdDbEntityImpl
{
private:
  friend class OdDbViewRepImage;

  static OdDbViewRepImageImpl* getImpl(const OdDbViewRepImage* pObj)
  { 
    return (OdDbViewRepImageImpl*) OdDbSystemInternals::getImpl(pObj);
  }

  OdDbViewRepImageImpl();

  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdInt32 m_unknown;
  OdDbObjectId m_viewportId;
  OdGePoint3d m_centerPoint;
  double m_width;
  double m_height;
  OdInt32 m_iWidth;
  OdInt32 m_iHeight;

  OdBinaryData m_binaryData;
};

typedef OdSmartPtr<OdDbViewRepImageImpl> OdDbViewRepImageImplPtr;

#endif // _ODDBVIEWREPIMAGEIMPL_INCLUDED_
