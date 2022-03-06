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

#ifndef __NW_VERTICES_DATA_IMPL_H__
#define __NW_VERTICES_DATA_IMPL_H__

#include "NwObjectImpl.h"
#include "NwVerticesData.h"
#include "Ge/GeExtents3d.h"
#include "Ge/GePoint3dArray.h"
#include "Ge/GePoint2dArray.h"
#include "Ge/GeVector3dArray.h"
#include "UInt32Array.h"
#include "UInt16Array.h"

class OdNwVerticesDataImpl;
class OdNwGraphicVertexSet;
class OdNwGraphicTexCoordSet;
class OdNwGraphicNormalSet;
class OdNwGraphicColorSet;

typedef OdSmartPtr<OdNwGraphicVertexSet> OdNwGraphicVertexSetPtr;
typedef OdSmartPtr<OdNwGraphicTexCoordSet> OdNwGraphicTexCoordSetPtr;
typedef OdSmartPtr<OdNwGraphicNormalSet> OdNwGraphicNormalSetPtr;
typedef OdSmartPtr<OdNwGraphicColorSet> OdNwGraphicColorSetPtr;

class OdNwVerticesDataImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwVerticesData)
public:
  OdNwVerticesDataImpl();
  virtual ~OdNwVerticesDataImpl();
  ODRX_DECLARE_MEMBERS(OdNwVerticesDataImpl);

public:
  static OdNwVerticesDataImpl* getImpl(const OdNwVerticesData* pNwGeometry);
  static OdNwVerticesDataImpl* getImpl(const OdRxObject* pRxGeometry);

public:
  OdNwGraphicVertexSetPtr getVertexSet() const;
  OdNwGraphicTexCoordSetPtr getTexCoordSet() const;
  OdNwGraphicNormalSetPtr getNormalSet() const;
  OdNwGraphicColorSetPtr getColorSet() const;

  void setVertexSet(const OdNwGraphicVertexSetPtr&);
  void setTexCoordSet(const OdNwGraphicTexCoordSetPtr&);
  void setNormalSet(const OdNwGraphicNormalSetPtr&);
  void setColorSet(const OdNwGraphicColorSetPtr&);

  OdGeExtents3d calculateBoundingBox() const;
  virtual OdUInt32 getPrimitiveCount() const;

  static bool validateIndices(OdGePoint3dArray& vertices, const OdUInt16Array& vertexPerLine, const OdUInt16Array& indexesPerLine);
  static bool validateTexCoords(const OdGePoint3dArray& vertices, OdGePoint2dArray& texCoords);
  static bool validateNormals(const OdGePoint3dArray& vertices, OdGeVector3dArray& normals);
  static bool validateColors(const OdGePoint3dArray& vertices, OdUInt32Array& colors);

private:
  OdNwGraphicVertexSetPtr m_pVertexSet;
  OdNwGraphicTexCoordSetPtr m_pTexCoordSet;
  OdNwGraphicNormalSetPtr m_pNormalSet;
  OdNwGraphicColorSetPtr m_pColorSet;
};

#endif //__NW_VERTICES_DATA_IMPL_H__
