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

#include "FMCodeSnippetsStdAfx.h"
#include "Modeler/FMMdlBody.h"
#include "Modeler/FMMdlIterators.h"

using namespace FacetModeler;

/** <snippet name="fm_iteration_tags" lang="cpp"> */
void iterTags()
{
  Body body = Body::box(OdGePoint3d::kOrigin, OdGeVector3d(10., 10., 10.));
  EdgeBodyIterator iter(&body);
  OdUInt64 tag = 0;
  while (!iter.done())
  {
    Edge* pEdge = iter.get();
    pEdge->setTag(tag++);
    odPrintConsoleString(L"The edge's number is: %d\n", pEdge->tag());
    iter.next();
  }
}
/** </snippet> */

void _FMDocIteration_func(OdEdCommandContext* pCmdCtx)
{
  DeviationParams devParams;
  
  Body pBody = Body::box(OdGePoint3d::kOrigin, OdGeVector3d(10., 10., 10.));
  Face* pFace = FaceIterator(&pBody).get();

  /** <snippet name="fm_iteration_face" lang="cpp"> */
  FaceIterator itF(&pBody);
  while (!itF.done())
  {
    pFace = itF.get();
    /* ... working with a face ...*/
    itF.next();
  }
  /** </snippet> */
  /** <snippet name="fm_iteration_edge" lang="cpp"> */
  EdgeFaceIterator iter(pFace);
  while (!iter.done())
  {
    Edge* pEdge = iter.get();

    //access the starting point of the current edge
    OdGePoint3d ptVtx = pEdge->vertex()->point();
    /* ... working with an edge ... */

    bool bNextLoop;
    iter.next(&bNextLoop);
    if (bNextLoop)
    {
      /* ... */
    }
  }
  /** </snippet> */

  /** <snippet name="fm_iteration_vertex" lang="cpp"> */
  VertexIterator itV(&pBody);
  while (!itV.done())
  {
    Vertex* pVertex = itV.get();

    /* ... work with a vertex ... */

    itV.next();
  }
  /** </snippet> */
}

