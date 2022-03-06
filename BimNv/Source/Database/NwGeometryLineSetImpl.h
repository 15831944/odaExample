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

#ifndef __NWGEOMETRYLINESETIMPL_INCLUDED__
#define __NWGEOMETRYLINESETIMPL_INCLUDED__

#include "NwGeometryLineSet.h"
#include "NwGeometryImpl.h"
#include "UInt16Array.h"

class OdNwGeometryLineSetImpl;
class OdNwVerticesData;

typedef OdSmartPtr<OdNwVerticesData> OdNwVerticesDataPtr;


class OdNwGeometryLineSetImpl : public OdNwGeometryImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGeometryLineSet)
public:
  OdNwGeometryLineSetImpl();
  virtual ~OdNwGeometryLineSetImpl();
  ODRX_DECLARE_MEMBERS(OdNwGeometryLineSetImpl);

public:
  bool draw(OdGiWorldDraw* pWd) const override;

public:
  static OdNwGeometryLineSetImpl* getImpl(const OdNwGeometryLineSet* pNwGeometry);
  static OdNwGeometryLineSetImpl* getImpl(const OdRxObject* pRxGeometry);

public:
  // deprected
  OdArray<OdGePoint3d> getVertexes() const override;
  // deprected
  OdArray<OdUInt32> getColors() const override;

public:
  OdUInt16Array getVertexCountPerLine() const;
  void setVertexCountPerLine(const OdUInt16Array& val);
  OdUInt32 getPrimitiveCount() const override;

  OdNwVerticesDataPtr getVerticesData() const;
  void setVerticesData(const OdNwVerticesDataPtr&);

  virtual OdGeExtents3d calculateBoundingBox() const;
  static OdNwGeometryLineSetPtr createPolyline(const OdGePoint3dArray& points);

protected:
  OdUInt16Array m_aVertexCountPerLine;
  OdNwVerticesDataPtr m_pVerticesData;
};

#endif //__NWGEOMETRYLINESETIMPL_INCLUDED__
