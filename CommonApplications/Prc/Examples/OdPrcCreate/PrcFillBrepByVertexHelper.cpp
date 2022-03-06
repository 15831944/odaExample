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

#include "PrcCommon.h"
#include "PrcFillBrepByVertexHelper.h"
#include "PrcPlane.h"
#include "PrcLine3d.h"
#include "PrcUniqueVertex.h"
#include "Ge/GePlane.h"
#include "Ge/GeLineSeg3d.h"


struct edgeStruct
{
  OdPrcEdgePtr pEdge;
  OdUInt32 startIndx;
  OdUInt32 endIndx;
};

OdPrcCoEdgePtr getCoEdge(OdArray<edgeStruct> &arrEdges, const OdUInt32 &startIndx, const OdUInt32 &endIndx, const OdGePoint3dArray &vertexList)
{
  OdPrcCoEdgePtr curCoEdge = OdPrcCoEdge::createObject();

  for (OdUInt32 i = 0; i < arrEdges.size(); i++)
  {
    if (arrEdges[i].startIndx == startIndx && arrEdges[i].endIndx == endIndx)
    {
      curCoEdge->setEdge(arrEdges[i].pEdge);
      curCoEdge->setOrientationWithLoop(kSame);
      return curCoEdge;
    }
    else if (arrEdges[i].startIndx == endIndx && arrEdges[i].endIndx == startIndx)
    {
      curCoEdge->setEdge(arrEdges[i].pEdge);
      curCoEdge->setOrientationWithLoop(kOpposite);
      return curCoEdge;
    }
  }

  OdGeLineSeg3d geLine(vertexList[startIndx],vertexList[endIndx]);
  OdPrcLine3dPtr line = OdPrcLine3d::createObject();
  line->setFromOdGeCurve(geLine);

  OdPrcEdgePtr curEdge = OdPrcEdge::createObject();
  curEdge->contentWireEdge().curve() = line;
  OdPrcUniqueVertexPtr startP = OdPrcUniqueVertex::createObject();
  OdPrcUniqueVertexPtr endP = OdPrcUniqueVertex::createObject();
  startP->point() = vertexList[startIndx];
  endP->point() = vertexList[endIndx];
  curEdge->setStartVertex(startP);
  curEdge->setEndVertex(endP);

  curCoEdge->setEdge(curEdge);
  curCoEdge->setOrientationWithLoop(kSame);

  edgeStruct newEdgeInArr;
  newEdgeInArr.pEdge = curEdge;
  newEdgeInArr.startIndx = startIndx;
  newEdgeInArr.endIndx = endIndx;
  arrEdges.push_back(newEdgeInArr);

  return curCoEdge;
}

OdResult fillBrepDataByVertex(OdPrcBrepDataPtr pBrepData, const OdGePoint3dArray &vertexList, const OdArray<OdUInt32Array> &vertexOrder)
{
  OdArray<edgeStruct> arrEdges;

  OdUInt32 cntFaces = vertexOrder.size();

  OdPrcConnexPtr pCurConnex = OdPrcConnex::createObject();
  pBrepData->addConnex(pCurConnex);

  {
    OdPrcShellPtr pCurShell = OdPrcShell::createObject();
    pCurConnex->addShell(pCurShell);

    for (OdUInt32 i = 0; i < cntFaces; i++)
    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");
      }

      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);

      //add loop
      OdPrcLoopPtr curLoop = OdPrcLoop::createObject();
      pCurFace->addLoop(curLoop);
      OdUInt32 cntEdges = vertexOrder[i].size();
      if (cntEdges < 3)
      {
        ODA_ASSERT(!"Wrong edge count");
        return eInvalidInput;
      }
      for (OdUInt32 j = 0; j < cntEdges; j++)
      {
        OdUInt32 startIndx = vertexOrder[i][j] - 1;
        OdUInt32 endIndx = j+1 < cntEdges ? vertexOrder[i][j+1] - 1 : vertexOrder[i][0] - 1;
        curLoop->addCoEdge(getCoEdge(arrEdges,startIndx,endIndx,vertexList));
        curLoop->setOrientationWithSurface(kSame);
      }

      // calculate plane
      OdGePoint3d pnt1 = vertexList[vertexOrder[i][0] - 1];
      OdGePoint3d pnt2 = vertexList[vertexOrder[i][1] - 1];
      OdGePoint3d pnt3 = vertexList[vertexOrder[i][2] - 1];
      OdGeVector3d vec1 = pnt2 - pnt1;
      OdGeVector3d vec2 = pnt3 - pnt2;
      OdGeVector3d vrNormal = vec1.crossProduct(vec2);
      vrNormal.normalize();
      OdGePlane gePlane(pnt1,vrNormal);

      OdGeInterval intU( -12345.0, 12345.0 );
      OdGeInterval intV( -12345.0, 12345.0 );
      gePlane.setEnvelope(intU, intV);

      pPrcPlane->setFromOdGeSurface(gePlane);
      pCurFace->baseSurface() = pPrcPlane;
    }

    //pCurShell->setShellIsClosed(true); // flag shellIsClosed is entered automatically in the method updateIsClosedFlag in OdPrcBrepModel
  }

  return eOk;
}
