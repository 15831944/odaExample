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
#include "BimCommon.h"
#include "Bim2PrcContextForPdfExportImpl.h"
#include "BmElement.h"

ODRX_CONS_DEFINE_MEMBERS(OdPrcContextForPdfExport_AllInSingleView_BIM, OdPrcContextForPdfExport, RXIMPL_CONSTR);

OdPrcContextForPdfExport_AllInSingleView_BIM::OdPrcContextForPdfExport_AllInSingleView_BIM()
  : m_nextAvailableVp(0)
{
}

bool OdPrcContextForPdfExport_AllInSingleView_BIM::shouldExportAsPRC(
  const OdGiDrawable *pDrawable,
  const OdGiPathNode *pGiPath,
  const OdGsClientViewInfo *pView,
  OdUInt32 &viewportidx) const
{
  // index of viewport (prc file in pdf) where current entity will be exported
  viewportidx = 0;

  // can entity be exported to prc or not
  OdBmElementPtr ptrEntity = OdBmElement::cast(pDrawable);

  if (ptrEntity.isNull())
  {
    return false;
  }

  OdDbStub *pVpId = pView->viewportObjectId;
  std::map< OdDbStub *, OdUInt32> ::iterator it = m_mapViewport.find(pVpId);
  if (it != m_mapViewport.end())
  {
    viewportidx = m_mapViewport[pVpId];
  }
  else
  {
    viewportidx = m_nextAvailableVp;
    m_mapViewport.insert(std::pair<OdDbStub *, OdUInt32>(pVpId, m_nextAvailableVp));
    m_nextAvailableVp++;
  }
  return true;
}

void OdPrcContextForPdfExport_AllInSingleView_BIM::getExtents(
  const OdGiDrawable * pDrawable,
  OdDbStub * viewportObjectId,
  OdGiContext * pGiContext,
  const OdGeMatrix3d & cameraView,
  const OdGeMatrix3d & modelToWorld,
  OdGeExtents3d & extents) const
{
  getExtentsWithParams(pDrawable, viewportObjectId, pGiContext, cameraView, modelToWorld, extents, kOdGiStandardDisplay);
}
