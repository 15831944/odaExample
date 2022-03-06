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
/* OdDbMPolygon entities.                                               */
/************************************************************************/
#include "StdAfx.h"
#include "DbMPolygonGripPoints.h"
#include "DbPolyline.h"
#include "Ge/GeMatrix3d.h"
#include "Ge/GeCircArc2d.h"
#include "Ge/GeCircArc3d.h"
#include "Gi/GiViewport.h"
#include "DbMPolygon.h"
#include "Ge/GePolyline2d.h"
#include "UInt32Array.h"
#include "Ge/GeLineSeg2d.h"
#include "Ge/GeRay2d.h"
#include "Ge/GeLine2d.h"

inline static bool isArc(const OdGeDoubleArray& dBulgesArr, const OdUInt32 index)
{
  return index < dBulgesArr.size() && dBulgesArr.at(index) != 0;
}

inline static OdUInt32 countGripPointsInLoop(const OdGePoint2dArray& pLoopPointsArr)
{
  if (pLoopPointsArr.isEmpty())
    return 0;
  return (pLoopPointsArr.size()) * 2;
}

OdResult OdDbMPolygonGripPointsPE::getGripPoints(const OdDbEntity* pEntity, OdGePoint3dArray& gripPoints) const
{
  OdDbMPolygonPtr pMPolygon = pEntity;
  OdUInt32 nNumLoop = pMPolygon->numMPolygonLoops();
  OdUInt32 nGripPointsSize = 0;
  OdGePoint3d point3d;
  
  OdGeExtents3d ext3d;
  for (OdUInt32 iCurLoop = 0; iCurLoop < nNumLoop; ++iCurLoop)
  {
    OdGePoint2dArray pLoopPointsArr;
    OdGeDoubleArray dBulgesArr;
    OdGePolyline2d pol;
    
    pMPolygon->getMPolygonLoopAt(iCurLoop, pLoopPointsArr, dBulgesArr);
    if (!pLoopPointsArr.isEmpty())
    {
      if (pLoopPointsArr.length() == dBulgesArr.length())
        dBulgesArr.removeLast();
      pLoopPointsArr.removeLast();
    }
    OdUInt32 prevGripSize = gripPoints.size();
    gripPoints.reserve(gripPoints.size() + countGripPointsInLoop(pLoopPointsArr) + 1);

    if (pLoopPointsArr.size() > 1)
    {
      point3d = OdGePoint3d(pLoopPointsArr.at(0).x, pLoopPointsArr.at(0).y, 0.);
      gripPoints.push_back(point3d);
    }
    
    for (unsigned int i = 0; i < pLoopPointsArr.size(); ++i)
    { 
      OdUInt32 iNext = i + 1;
      if (iNext == pLoopPointsArr.size())
        iNext = 0;
      if(isArc(dBulgesArr, i))//if (i < dBulgesArr.size() && dBulgesArr.at(i) != 0)
      {
        OdGeCircArc2d arc(pLoopPointsArr[i], pLoopPointsArr[iNext], dBulgesArr[i], false);
        point3d.set(arc.midPoint().x, arc.midPoint().y, 0.);
        gripPoints.push_back(point3d);
      }
      else
      {
        OdGePoint2d midPoint = (pLoopPointsArr[i] + pLoopPointsArr[iNext].asVector()) / 2.;
        point3d.set(midPoint.x, midPoint.y, 0.);
        gripPoints.push_back(point3d);
      }
      ext3d.addPoint(point3d);
      point3d.set(pLoopPointsArr[iNext].x, pLoopPointsArr[iNext].y, 0.);
      ext3d.addPoint(point3d);
      gripPoints.push_back(point3d);
    }
    if (gripPoints.size() > 1 && gripPoints.last().isEqualTo(gripPoints.at(prevGripSize)))
      gripPoints.removeLast();
  }
  if (nNumLoop > 0)
    gripPoints.push_back((ext3d.maxPoint() + ext3d.minPoint().asVector()) / 2.0);
  return eOk;
}


OdUInt32 getIndexPointInLoop(const OdUInt32 numberOfGripPoints, const OdUInt32 gripIndex, const OdGePoint2dArray & pLoopPointsArr)
{
  OdUInt32 indexGripPointInLoop = 0;
  indexGripPointInLoop = numberOfGripPoints - 1 - gripIndex;//-1 to lead size to index
  //indexGripPointInLoop = (pLoopPointsArr.size()) * 2 - 1 - indexGripPointInLoop;//-1 to lead size to index
  indexGripPointInLoop = countGripPointsInLoop(pLoopPointsArr) - 1 - indexGripPointInLoop;//-1 to lead size to index
  if (gripIndex % 2 == 1)
    --indexGripPointInLoop;    
  return indexGripPointInLoop / 2;
}

void createCache(OdDbMPolygonPtr pMPolygon, OdArray<OdUInt32> &cacheSearchPointIndex)
{
  const OdUInt32 nNumLoop = pMPolygon->numMPolygonLoops();
  OdInt32 lookUpIndexLoop = 0;
  OdUInt32 indexCurLoop = cacheSearchPointIndex.size();
  OdUInt32 countPoints = 0;
  OdGePoint2dArray pLoopPointsArr;
  OdGeDoubleArray dBulgesArr;
  for (; indexCurLoop < nNumLoop; ++indexCurLoop)
  {
    pLoopPointsArr.clear();
    dBulgesArr.clear();
    pMPolygon->getMPolygonLoopAt(indexCurLoop, pLoopPointsArr, dBulgesArr);
    if (pLoopPointsArr.size() < 2)
    {
      cacheSearchPointIndex.push_back(countPoints);//skip loops with one point
      continue;
    }
    pLoopPointsArr.removeLast();
    countPoints += countGripPointsInLoop(pLoopPointsArr);
    cacheSearchPointIndex.push_back(countPoints);
  }
}

inline OdUInt32 findIndexCurrentLoop(OdDbMPolygonPtr pMPolygon, const OdArray<OdUInt32>& cacheSearchPointIndex, const OdUInt32 gripIndex)
{
  ODA_ASSERT(!cacheSearchPointIndex.isEmpty() && cacheSearchPointIndex.last() >= gripIndex);
  OdUInt32 indexCurLoop = 0;
  for (; indexCurLoop < cacheSearchPointIndex.size(); ++indexCurLoop)
  {
    if (cacheSearchPointIndex[indexCurLoop] > gripIndex)
      break;
  }
  return indexCurLoop;
}



enum ShiftPosition
{
  eStartPoint = 0,
  eMidPoint,
  eEndPoint
};

OdGePoint2d extendArc(OdGeDoubleArray &dBulgesArr, const OdGePoint2dArray &pLoopPointsArr, const OdGeVector3d &offset, const OdUInt32 indexPointInLoop, const ShiftPosition shift)
{
  const double dBulge = dBulgesArr[indexPointInLoop];
  const OdGePoint2d startPoint(pLoopPointsArr[indexPointInLoop]);
  const OdGePoint2d endPoint(indexPointInLoop >= pLoopPointsArr.size() - 1 ? pLoopPointsArr.first() : pLoopPointsArr[indexPointInLoop + 1]);
  OdGeCircArc2d arc(startPoint, endPoint, dBulge, false);

  OdGeCircArc2d arcNew;
  switch (shift)
  {
  case eStartPoint:arcNew.set(startPoint + offset.convert2d(), arc.midPoint(), endPoint); break;
  case eMidPoint:  arcNew.set(startPoint, arc.midPoint() + offset.convert2d(), endPoint); break;
  case eEndPoint:  arcNew.set(startPoint, arc.midPoint(), endPoint + offset.convert2d()); break;
  }
  double dBulgeNew = tan((arcNew.endAng() - arcNew.startAng()) / 4);
  if (arcNew.isClockWise())
    dBulgeNew = -dBulgeNew;
    
  dBulgesArr[indexPointInLoop] = dBulgeNew;
  return startPoint + offset.convert2d();//need only for start point
}


void changePrevSegment(OdGeDoubleArray& dBulgesArr, const OdGePoint2dArray &pLoopPointsArr, const OdGeVector3d& offset, const OdUInt32 indexPointInLoop)
{
  const OdUInt32 prevIndexPointInLoop = indexPointInLoop == 0 ? pLoopPointsArr.size() - 1 : indexPointInLoop - 1;
  if (isArc(dBulgesArr, prevIndexPointInLoop))
    extendArc(dBulgesArr, pLoopPointsArr, offset, prevIndexPointInLoop, eEndPoint);
}

void changeNextSegment(OdGeDoubleArray& dBulgesArr, const OdGePoint2dArray &pLoopPointsArr, const OdGeVector3d& offset, const OdUInt32 indexPointInLoop)
{
  const OdUInt32 nextIndexPointInLoop = indexPointInLoop + 1 >= pLoopPointsArr.size() ? 0 : indexPointInLoop + 1;
  if (isArc(dBulgesArr, nextIndexPointInLoop))
    extendArc(dBulgesArr, pLoopPointsArr, offset, nextIndexPointInLoop, eStartPoint);
}


void applyOffsetToVertices(OdGePoint2dArray &pLoopPointsArr, OdGeDoubleArray& dBulgesArr, const OdUInt32 indexPointInLoop, const OdUInt32 curretGripIndex, const OdGeVector3d &offset)
{
  ODA_ASSERT(!pLoopPointsArr.isEmpty());
  if (isArc(dBulgesArr, indexPointInLoop) && curretGripIndex % 2 == 0)
  {//changed startPoint of arc
    OdGePoint2d newPoint = extendArc(dBulgesArr, pLoopPointsArr, offset, indexPointInLoop, eStartPoint);
    changePrevSegment(dBulgesArr, pLoopPointsArr, offset, indexPointInLoop);
    pLoopPointsArr[indexPointInLoop] = newPoint;
  }
  else if (isArc(dBulgesArr, indexPointInLoop) && curretGripIndex % 2 == 1)
  {//changed midPoint of arc
    extendArc(dBulgesArr, pLoopPointsArr, offset, indexPointInLoop, eMidPoint);
  }
  else if (curretGripIndex % 2 == 0)
  {//changed startPoint of line
    changePrevSegment(dBulgesArr, pLoopPointsArr, offset, indexPointInLoop);
    pLoopPointsArr[indexPointInLoop] = pLoopPointsArr[indexPointInLoop] + offset.convert2d();
  }
  else if (curretGripIndex % 2 == 1)
  {//changed midPoint of line
    changePrevSegment(dBulgesArr, pLoopPointsArr, offset, indexPointInLoop);
    changeNextSegment(dBulgesArr, pLoopPointsArr, offset, indexPointInLoop);
    pLoopPointsArr[indexPointInLoop] = pLoopPointsArr[indexPointInLoop] + offset.convert2d();
    if (indexPointInLoop + 1 >= pLoopPointsArr.size())
      pLoopPointsArr[0] = pLoopPointsArr[0] + offset.convert2d();
    else
    {
      pLoopPointsArr[indexPointInLoop + 1] = pLoopPointsArr[indexPointInLoop + 1] + offset.convert2d();
    }
  }
}

OdResult OdDbMPolygonGripPointsPE::moveGripPointsAt(OdDbEntity* pEntity, const OdIntArray& indicesInput, const OdGeVector3d& offset)
{
  if (indicesInput.isEmpty())
    return eOk;//eInvalidInput ?
  OdDbMPolygonPtr pMPolygon = pEntity;
  OdArray<OdUInt32> cacheSearchPointIndex;//index is number of loop. Value is sum of previous grip points loops.
  OdGePoint2dArray pLoopPointsArr;
  OdGeDoubleArray dBulgesArr;
  createCache(pMPolygon, cacheSearchPointIndex);
  OdIntArray indices = indicesInput;
  std::sort(indices.begin(), indices.end());
  OdIntArray replaceIndices;
  OdGePoint2dArrayArray pLoopPointsArrArr;
  OdArray<OdGeDoubleArray> dBulgesArrArr;
  if (indices.last() == cacheSearchPointIndex.last())
  {//like acad. If in the indicesInput a few points, and one of it is a point to translate a entity - just translate entity.
    OdGeMatrix3d mat;
    mat.setTranslation(offset);
    return pEntity->transformBy(mat);
  }
  OdUInt32 indexPrevLoop = 0xffffffff, indexCurLoop = 0;
  for (OdUInt32 iIndex = 0; iIndex < indices.size(); ++iIndex)
  {
    const OdUInt32 curretGripIndex = indices[iIndex];
    indexCurLoop = findIndexCurrentLoop(pMPolygon, cacheSearchPointIndex, curretGripIndex);
    if (indexCurLoop != indexPrevLoop)
    {
      OdResult res;
      if (indexPrevLoop != 0xffffffff)
      {
        pLoopPointsArr.push_back(pLoopPointsArr.first());
        dBulgesArr.push_back(dBulgesArr.first());

        replaceIndices.push_back(indexPrevLoop);
        pLoopPointsArrArr.push_back(pLoopPointsArr);
        dBulgesArrArr.push_back(dBulgesArr);
        pLoopPointsArr.clear();
        dBulgesArr.clear();
      }

      pLoopPointsArr.clear();
      dBulgesArr.clear();
      res = pMPolygon->getMPolygonLoopAt(indexCurLoop, pLoopPointsArr, dBulgesArr);
      if (res != eOk)
        return res;
      if (!pLoopPointsArr.isEmpty())
      {
        if(dBulgesArr.size() >= pLoopPointsArr.size())
          dBulgesArr.removeLast();
        pLoopPointsArr.removeLast();
      }
      
    }
    indexPrevLoop = indexCurLoop;
    const OdUInt32 indexPointInLoop = getIndexPointInLoop(cacheSearchPointIndex[indexCurLoop], curretGripIndex, pLoopPointsArr);
    if (curretGripIndex == cacheSearchPointIndex.last())
    {
      OdGeMatrix3d matrix;
      matrix.setTranslation(offset);
      pEntity->transformBy(matrix);
      continue;
    }
    applyOffsetToVertices(pLoopPointsArr, dBulgesArr, indexPointInLoop, curretGripIndex, offset);

    //if (indexPointInLoop == 0)//last and start point must be equal
      //pLoopPointsArr.last() = pLoopPointsArr.first();
  }
  if (!pLoopPointsArr.isEmpty())
  {
    if(dBulgesArr.size() == pLoopPointsArr.size())
      dBulgesArr.push_back(dBulgesArr.first());
    pLoopPointsArr.push_back(pLoopPointsArr.first());
  }
  replaceIndices.push_back(indexCurLoop);
  pLoopPointsArrArr.push_back(pLoopPointsArr);
  dBulgesArrArr.push_back(dBulgesArr);
  OdIntArray reject;
  OdResult res = pMPolygon->replaceMPolygonLoopAt(replaceIndices, pLoopPointsArrArr, dBulgesArrArr, reject);
  if (res != eOk)
    return res;
  return eOk;
}

OdResult OdDbMPolygonGripPointsPE::getStretchPoints(const OdDbEntity* pEntity, OdGePoint3dArray& stretchPoints) const
{
  return getGripPoints(pEntity, stretchPoints);
}

OdResult OdDbMPolygonGripPointsPE::moveStretchPointsAt(OdDbEntity* pEntity, const OdIntArray& indices, const OdGeVector3d& offset)
{
  return moveGripPointsAt(pEntity, indices, offset);
}

OdResult OdDbMPolygonGripPointsPE::getOsnapPoints(const OdDbEntity* pEntity, OdDb::OsnapMode osnapMode, OdGsMarker gsSelectionMark, 
  const OdGePoint3d& pickPoint, const OdGePoint3d& lastPoint, const OdGeMatrix3d& xWorldToEye, OdGePoint3dArray& snapPoints) const
{
  OdDbMPolygonPtr pMPolygon = pEntity;
  if (gsSelectionMark)
  {
    OdDbFullSubentPath subEntPath(OdDb::kEdgeSubentType, gsSelectionMark);
    OdDbEntityPtr pSubEnt = pMPolygon->subentPtr(subEntPath);
    if (!pSubEnt.isNull())
      return pSubEnt->getOsnapPoints(
        osnapMode,
        0,  // gsSelectionMark, 
        pickPoint,
        lastPoint,
        xWorldToEye,
        snapPoints);
  }
  OdGePoint3dArray gripPoints;
  OdResult res = getGripPoints(pEntity, gripPoints);
  if (res != eOk)
    return res;
  switch (osnapMode)
  {
  case OdDb::kOsModeEnd:
  {
    for (OdUInt32 i = 0; i < gripPoints.size(); i += 2)
    {
      snapPoints.push_back(gripPoints[i]);
    }
    break;
  }
  case OdDb::kOsModeMid:
  {
    for (OdUInt32 i = 1; i < gripPoints.size(); i += 2)
    {
      snapPoints.push_back(gripPoints[i]);
    }
    break;
  }
  case OdDb::kOsModeCen:
  case OdDb::kOsModeNear:
  {
    OdGePoint2dArray loopPointsArr;
    OdGeDoubleArray dBulgesArr;
    OdUInt32 nextPoint = 0;
    OdGePoint2d pClosestPoint;
    for (OdInt32 iCurLoop = 0; iCurLoop < pMPolygon->numMPolygonLoops(); ++iCurLoop)
    {
      loopPointsArr.clear();
      dBulgesArr.clear();
      pMPolygon->getMPolygonLoopAt(iCurLoop, loopPointsArr, dBulgesArr);
      if (!loopPointsArr.isEmpty())
      {
        if (dBulgesArr.size() >= loopPointsArr.size())
          dBulgesArr.removeLast();
        loopPointsArr.removeLast();
      }
      for (OdUInt32 j = 0; j < dBulgesArr.size(); ++j)
      {
        nextPoint = 0;
        if (j + 1 < loopPointsArr.size())
          nextPoint = j + 1;
        if (isArc(dBulgesArr, j))
        {
          OdGeCircArc2d arc2d(loopPointsArr[j], loopPointsArr[nextPoint], dBulgesArr[j], false);
          if(osnapMode == OdDb::kOsModeCen)
            snapPoints.push_back(OdGePoint3d().set(arc2d.center(), 0.));
          else //kOsModeNear
            snapPoints.push_back(OdGePoint3d().set(arc2d.closestPointTo(pickPoint.convert2d()), 0.));
        }
        else if (osnapMode == OdDb::kOsModeNear)
        {
          OdGeLineSeg2d seg2d(loopPointsArr[j], loopPointsArr[nextPoint]);
          snapPoints.push_back(OdGePoint3d().set(seg2d.closestPointTo(pickPoint.convert2d()), 0.));
        }
      }
    }
    break;
  }
  default:
    break;
  }

  return eOk;
}
