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

#ifndef _DbPolyLineTemplates_h_Included_
#define _DbPolyLineTemplates_h_Included_

#include "Db2dVertex.h"

template<class VertexPtrType, class PolyLineType>
class PolylineTemplates
{
public:
  static OdResult getStartSegmentPoint(const PolyLineType* pThis, OdGePoint3d& pt, OdTvDbObjectIteratorPtr& pIter, unsigned i )
  {
    // pIter must points to start of polyline
    VertexPtrType pVert;
    ODA_ASSERT(pIter.get() && !pIter->done());

    while (!pIter->done())
    {
      pVert = pIter->entity();
      if (pVert->vertexType() != 1/*OdDb::k2dSplineCtlVertex or OdDb::k3dControlVertex*/) 
        break;
      pIter->step();
    }
  
    while (i && !pIter->done())
    {
      --i;
      pIter->step();
      while (!pIter->done())
      {
        pVert = pIter->entity();
        if (pVert->vertexType() != 1/*OdDb::k2dSplineCtlVertex or OdDb::k3dControlVertex*/) 
          break;
        pIter->step();
      }
    }

    if (pIter->done())
    {
      if (pThis->isClosed() && i == 0)
        pIter->start();
      else
        return eInvalidInput;
    }

    while (!pIter->done())
    {
      pVert = pIter->entity();
      if (pVert->vertexType() != 1/*OdDb::k2dSplineCtlVertex or OdDb::k3dControlVertex*/) 
        break;
      pIter->step();
    }

    if (pIter->done()) 
      return eInvalidInput;

    pt = pVert->position();

    return eOk;
  }

  static OdResult getEndSegmentPoint(const PolyLineType* pThis, OdGePoint3d& pt, OdTvDbObjectIteratorPtr& pIter)
  {
    // pIter must points to start segment point
    ODA_ASSERT(pIter.get() && !pIter->done());
    pIter->step();

    VertexPtrType pVert;
    for(; !pIter->done(); pIter->step())
    {
      pVert = pIter->entity();
      if(pVert->vertexType() != 1/*OdDb::k2dSplineCtlVertex or OdDb::k3dControlVertex*/)
        break;
    }

    if (pIter->done())
    {
      if (!pThis->isClosed()) 
        return eInvalidInput;

      pIter->start();
    }

    while (!pIter->done())
    {
      pVert = pIter->entity();
      if (pVert->vertexType() != 1/*OdDb::k2dSplineCtlVertex or OdDb::k3dControlVertex*/)
        break;
      pIter->step();
    }

    if (pIter->done())
      return eInvalidInput;

    pt = pVert->position();

    return eOk;
  }

  static OdResult getLastSegment( const PolyLineType* pThis, OdGePoint3d& pt1, OdGePoint3d& pt2, OdTvDbObjectIteratorPtr& pIter )
  {
    VertexPtrType pVert;
    pIter->start( false );

    while (!pIter->done())
    {
      pVert = pIter->entity();
      if (pVert->vertexType() != 1/*OdDb::k2dSplineCtlVertex or OdDb::k3dControlVertex*/) 
        break;
      pIter->step(false);
    }
    if (pIter->done()) 
      return eInvalidInput;

    pt2 = pVert->position();

    pIter->step(false);
    while (!pIter->done())
    {
      pVert = pIter->entity();
      if (pVert->vertexType() != 1/*OdDb::k2dSplineCtlVertex or OdDb::k3dControlVertex*/) 
        break;
      pIter->step(false);
    }
    if (pIter->done()) 
      return eInvalidInput;

    pt1 = pVert->position();

    return eOk;
  }

  static OdUInt32 getNumSegments(const PolyLineType* pThis, OdTvDbObjectIteratorPtr& pIter)
  {
    // pIter must points to start of polyline
    ODA_ASSERT(pIter.get() && !pIter->done());

    OdUInt32 nRet = 0;

    while (!pIter->done())
    {
      VertexPtrType pVert = pIter->entity();
      if (pVert->vertexType() != 1/*OdDb::k2dSplineCtlVertex or OdDb::k3dControlVertex*/)
      {
        ++nRet;
      }
      pIter->step();
    }

    if (nRet && !pThis->isClosed())
    {
      --nRet;
    }

    return nRet;
  }
};

#endif
