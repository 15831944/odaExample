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

/************************************************************************/
/* This class is an implementation of the OdDbGripPointsPE class for    */
/* OdDbPolyline entities.                                               */
/************************************************************************/
#include "StdAfx.h"
#include "DbPolylineGripPoints.h"
#include "DbPolyline.h"
#include "Ge/GeMatrix3d.h"
#include "Ge/GeCircArc2d.h"
#include "Ge/GeCircArc3d.h"
#include "Gi/GiViewport.h"

OdResult OdDbPolylineGripPointsPE::getGripPoints( const OdDbEntity* pEnt, OdGePoint3dArray& gripPoints )const
{
  unsigned int size = gripPoints.size();
  OdDbPolylinePtr pPoly = pEnt;
  
  gripPoints.resize( size + (pPoly->numVerts()*2-1) );

  if (pPoly->numVerts() > 1)
  {
    pPoly->getPointAt( 0, gripPoints[size] );
  }
  unsigned int iIndAdd = size + 1;
  for ( unsigned int i = 1; i < pPoly->numVerts(); ++i )
  {
    OdGePoint3d p; pPoly->getPointAtParam( i - 0.5, p );
    gripPoints[iIndAdd++] = p;
    pPoly->getPointAt( i, gripPoints[iIndAdd++] );
  }
  if (pPoly->isClosed() && !gripPoints.last().isEqualTo(gripPoints.first()))
  {
    OdGePoint3d p; pPoly->getPointAtParam(pPoly->numVerts() - 0.5, p);
    gripPoints.append(p);
  }
  return eOk;
}

void applyOffsetToVertices(OdGePoint2dArray &pLoopPointsArr, OdGeDoubleArray& dBulgesArr, const OdUInt32 indexPointInLoop, const OdUInt32 curretGripIndex, const OdGeVector3d &offset);

OdResult OdDbPolylineGripPointsPE::moveGripPointsAt( OdDbEntity* pEnt, const OdIntArray& indices, const OdGeVector3d& offset )
{
  unsigned size = indices.size();
  if ( size == 0 )
    return eOk;

  OdDbPolylinePtr pPoly = pEnt;
  OdGeMatrix3d x = OdGeMatrix3d::worldToPlane(pPoly->normal());
  int nVerts = pPoly->numVerts();
  
  OdGePoint2dArray pointrsArr;
  OdGeDoubleArray bulgesArr;
  pointrsArr.reserve(nVerts);
  bulgesArr.reserve(nVerts);
  for (int i = 0; i < nVerts; ++i)
  {
    pPoly->getPointAt(i, *pointrsArr.append());
    bulgesArr.push_back(pPoly->getBulgeAt(i));
  }
  unsigned int i = 0;
  for (i = 0; i < size; ++i )
  {
    applyOffsetToVertices(pointrsArr, bulgesArr, indices[i] / 2, indices[i], offset);
  }
  for (int i = 0; i < nVerts; ++i)
  {
    pPoly->setPointAt(i, pointrsArr[i]);
    pPoly->setBulgeAt(i, bulgesArr[i]);
  }
  return eOk;
}

OdResult OdDbPolylineGripPointsPE::getStretchPoints( const OdDbEntity* ent, OdGePoint3dArray& stretchPoints ) const
{
  unsigned int size = stretchPoints.size();
  OdDbPolylinePtr pPoly = ent;

  stretchPoints.resize( size + pPoly->numVerts() );
  unsigned int i = 0;
  for ( ; i < pPoly->numVerts(); ++i )
    pPoly->getPointAt( i, stretchPoints[size + i] );

  return eOk;
}


OdResult OdDbPolylineGripPointsPE::moveStretchPointsAt( OdDbEntity* ent, const OdIntArray& indices, const OdGeVector3d& offset)
{
  OdDbPolylinePtr pPoly = ent;
  OdGeVector3d off(offset);
  off.transformBy(OdGeMatrix3d::worldToPlane(pPoly->normal()));
  OdGeVector2d offset2d(offset.convert2d());
  
  for (unsigned int i = 0; i < indices.size(); ++i )
  {
    OdGePoint2d p;
    pPoly->getPointAt(indices[i], p);
    pPoly->setPointAt(indices[i], p + offset2d);
  }
  return eOk;
}

OdResult OdDbPolylineGripPointsPE::getOsnapPoints(const OdDbEntity* ent, 
                                                  OdDb::OsnapMode osnapMode, 
                                                  OdGsMarker gsSelectionMark, 
                                                  const OdGePoint3d& pickPoint,
                                                  const OdGePoint3d& lastPoint, 
                                                  const OdGeMatrix3d& xWorldToEye, 
                                                  OdGePoint3dArray& snapPoints) const
{
  OdDbPolylinePtr pPoly = ent;

  if (gsSelectionMark)
  {
    OdDbFullSubentPath subEntPath(OdDb::kEdgeSubentType, gsSelectionMark);
    OdDbEntityPtr pSubEnt = pPoly->subentPtr(subEntPath);
    if (!pSubEnt.isNull())
      return pSubEnt->getOsnapPoints( 
                                    osnapMode, 
                                    0,  // gsSelectionMark, 
                                    pickPoint,
                                    lastPoint, 
                                    xWorldToEye, 
                                    snapPoints);
  }

  int size = snapPoints.size();
  switch ( osnapMode )
  {
  case OdDb::kOsModeEnd:
    getStretchPoints( ent, snapPoints );
    break;
  case OdDb::kOsModeMid:
      {
        snapPoints.resize( size + pPoly->numVerts() - 1 );
        for ( unsigned i = 1; i < pPoly->numVerts(); ++i )
          pPoly->getPointAtParam( i - 0.5, snapPoints[ size + i - 1 ] );
        break;
      }
  
  case OdDb::kOsModeCen:

    for ( unsigned i = 0; i < pPoly->numVerts(); i++ )
    {
      if ( pPoly->segType(i) == OdDbPolyline::kArc )
      {  
        OdGeCircArc3d arc;
        pPoly->getArcSegAt(i, arc);

        snapPoints.append( arc.center() );
      }
    }

    break;

  case OdDb::kOsModeQuad: 
    {
  
    for ( unsigned i = 0; i < pPoly->numVerts(); i++ )
    {
      if ( pPoly->segType(i) == OdDbPolyline::kArc )
      {  
        OdGeCircArc3d arc;
        pPoly->getArcSegAt(i, arc);

       
        const OdDbDatabase* pDb = ent->database(); 
        OdGeVector3d xAxis = pDb->getUCSXDIR(); 
        OdGeVector3d yAxis = pDb->getUCSYDIR(); 
        OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
        if ( !arc.normal().isParallelTo(zAxis) )
          return eInvalidAxis;

        OdGeVector3d vStart, vEnd, vQuad;

        vStart = arc.startPoint() - arc.center();
        vEnd = arc.endPoint() - arc.center();
 
        int k[5] = {0, 1, 0, -1, 0};

        for (int quad = 0; quad < 4; quad ++)
        {
          vQuad = xAxis * arc.radius() * k[quad + 1] 
                + yAxis * arc.radius() * k[quad] ;

          if ( (vQuad - vStart).crossProduct( (vEnd - vQuad ) ).isCodirectionalTo( arc.normal() ) )
          {
            snapPoints.append( arc.center() 
                + xAxis * arc.radius() * k[quad + 1] 
                + yAxis * arc.radius() * k[quad] );
          }
        }        
      }
    }

    }   
    break;
  case OdDb::kOsModeNear:
    {
      OdGePoint3d p; 
      if ( pPoly->getClosestPointTo( pickPoint, xWorldToEye.inverse() * OdGeVector3d::kZAxis, p ) == eOk )
        snapPoints.append( p );
    }
    break;
  default:
    break;
  }
  return eOk;
}
