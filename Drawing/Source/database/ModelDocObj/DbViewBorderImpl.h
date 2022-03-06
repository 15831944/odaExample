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

#ifndef _ODDBVIEWBORDERIMPL_INCLUDED_
#define _ODDBVIEWBORDERIMPL_INCLUDED_

#include "OdDbStub.h"
#include "DbViewBorder.h"
#include "DbEntityImpl.h"
#include "Ge/GeExtents2d.h"

class OdDbViewBorderImpl : public OdDbEntityImpl
{
private:
  friend class OdDbViewBorder;

  static OdDbViewBorderImpl* getImpl(const OdDbViewBorder* pObj)
  { 
    return (OdDbViewBorderImpl*) OdDbSystemInternals::getImpl(pObj);
  }
  OdDbViewBorderImpl();

  bool isHighlighted() const;
  void setHighlighted(bool bVal);
  void setScale( double newScale, bool standart = true );

  // OdDbObjectImpl methods
  ////virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  //virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdGeExtents2d m_extents; // (194.3512, 155.6786) (216.4659, 177.6058)
  OdDbObjectId m_viewportId; // DbViewport x2A1
  OdGeVector2d m_offset;
  OdGePoint2d m_point; // (205.4086, 166.6422)
  OdDbObjectId m_scaleId;  // DbScale x1c8

  bool m_isHighlighted;
  //double m_RotationAngle;
};

#endif // _ODDBVIEWBORDERIMPL_INCLUDED_
