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

#ifndef _ODDB_REGION_INCLUDED_
#define _ODDB_REGION_INCLUDED_

#include "DbModelerGeometryImpl.h"
#include "DbRegion.h"
#include "DbBody.h"
#include "DbSystemInternals.h"

class OdDbRegionImpl : public OdDbModelerGeometryImpl
{
  friend class OdDbRegion;
  public:
    static OdDbRegionImpl* getImpl(const OdDbRegion *pObj)
    { return static_cast<OdDbRegionImpl*>(OdDbSystemInternals::getImpl(pObj));}
    virtual OdResult booleanOper(OdDb::BoolOperType operation, OdDbModelerGeometryImpl* pOtherBody,
      OdModelerGeometry::geomType typeThis, OdModelerGeometry::geomType typeOther) ODRX_OVERRIDE;

    virtual OdResult getAreaProp( const OdGePoint3d& origin, const OdGeVector3d& xAxis,
      const OdGeVector3d& yAxis, double& perimeter,
      double& area, OdGePoint2d& centroid,
      double momInertia[2], double& prodInertia,
      double prinMoments[2], OdGeVector2d prinAxes[2],
      double radiiGyration[2], OdGePoint2d& extentsLow,
      OdGePoint2d& extentsHigh ) const;

    virtual OdResult intersectWith(const OdDbEntity* pEnt, OdDb::Intersect intType,
      OdGePoint3dArray& points, OdGsMarker thisGsMarker, OdGsMarker otherGsMarker) const;

    virtual OdResult intersectWith( const OdDbEntity* ent, OdDb::Intersect intType,
      const OdGePlane& projPlane, OdGePoint3dArray& points,
      OdGsMarker thisGsMarker, OdGsMarker otherGsMarker ) const;
};

#endif // _ODDB_REGION_INCLUDED_
