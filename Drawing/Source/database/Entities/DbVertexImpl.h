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

#ifndef _ODDBVERTEXIMPL_INCLUDED_
#define _ODDBVERTEXIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DbVertex.h"
#include "DbSystemInternals.h"

class OdDbVertexImpl : public OdDbEntityImpl
{
  static OdDbVertexImpl* getImpl(const OdDbVertex *pObj)
  { return (OdDbVertexImpl*)OdDbSystemInternals::getImpl(pObj);}

protected:
//  OdUInt8 m_VertexFlags;

public:
  OdGePoint3d m_Point;

  OdDbVertexImpl() {/*m_VertexFlags = 0;*/}

  virtual OdResult dxfInFields(OdDbDxfFiler* )
  { ODA_ASSERT(0); return eOk; }
  virtual void dxfOutFields(OdDbDxfFiler* ) const
  { ODA_ASSERT(0); }

  enum VertexFlags
  { // Bit mask values
    kCurveFitVertex     =   1,  // Extra vertex created by curve-fitting
    kHasTangent         =   2,  // Curve-fit tangent defined for this vertex.
                                // A curve-fit tangent direction of 0 may be
                                // omitted from DXF output but is significant if this bit is set
    kSplineFitVertex    =   8,  // Spline vertex created by spline-fitting
    kSplineControlPoint =  16,  // Spline frame control point
    k3dPolylineVertex   =  32,  // 3D polyline vertex
    kPolygonMeshVertex  =  64,  // Polygon mesh vertex
    kPolyfaceMeshVertex = 128   // Polyface mesh vertex
  };

  virtual OdUInt8 getVertexFlags() const = 0;
  virtual void setVertexFlags(OdUInt8 val) = 0;

  friend class OdDbVertex;
};

#endif // _ODDBVERTEXIMPL_INCLUDED_
