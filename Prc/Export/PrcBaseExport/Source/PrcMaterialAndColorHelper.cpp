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

// PrcMaterialAndColorHelper.cpp: implementation of the PrcMaterialAndColorHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "PrcCommon.h"
#include "PrcMaterialAndColorHelper.h"
#include "PrcExportColor.h"
#include "RxVariantValue.h"
#include "Pdf2PrcExportParams.h"
#include "PdfExportGiDrawablePE.h"

PrcMaterialAndColorHelper::PrcMaterialAndColorHelper(
  const PDF2PRCExportParams *params,
  OdPrcExportContextPtr pContext,
  OdDbStub* pDefaultMaterial /*= NULL*/
)
  : OdBaseMaterialAndColorHelper(pDefaultMaterial)
  , m_pParams(params)
  , m_pContext(pContext)
{
  if (m_pParams && m_pParams->m_pTraitsData)
  {
    setSourceFaceColor(m_pParams->m_pTraitsData->trueColor());
  }
}

OdResult PrcMaterialAndColorHelper::convertColor(const OdCmEntityColor& sourceDbColor, OdCmEntityColor& destinationDbColor)
{
  if (!m_pParams || m_pSourceDb.isNull())
  {
    return eNullPtr;
  }
  // color should be handled for different coloring methods
  OdCmEntityColor color;
  if (sourceDbColor.isByLayer())
  {
    if (m_pParams->m_pTraitsData)
    {
      OdRxObjectPtr pLayer = OdDbBaseDatabasePEPtr(m_pSourceDb)->openObject(m_pParams->m_pTraitsData->layer());
      PdfExportLayerPEPtr ex = PdfExportLayerPE::cast(pLayer);
      if (ex.get())
      {
        color = ex->getColor(pLayer);
      }
    }
  }
  else if (sourceDbColor.isByBlock())
  {
    if (m_pParams->m_pByBlockTraitsData)
    {
      color = m_pParams->m_pByBlockTraitsData->trueColor();
    }
  }
  else
  {
    color = sourceDbColor;
  }

  switch (color.colorMethod())
  {
  case OdCmEntityColor::kACIbyBlock:
  case OdCmEntityColor::kByLayer:
    return eNotImplementedYet;
  case OdCmEntityColor::kByACI:
    {
      OdRxVariantValue rxPallet = OdRxVariantValue(m_pParams->m_extraOptions->getAt("Pallet"));
      OdRxVariantValue rxNumColors = OdRxVariantValue(m_pParams->m_extraOptions->getAt("NumColors"));
      if (rxPallet.get() && rxNumColors.get())
      {
        //take color from current pallet
        OdUInt64 pPallet = rxPallet->getUInt64();
        OdUInt32 numColors = rxNumColors->getUInt32();
        OdUInt32* arrPallet = (OdUInt32*)pPallet;
        if (numColors > (OdUInt32)color.colorIndex())
        {
          OdUInt32 rgb = arrPallet[color.colorIndex()];
          color.setRGB(ODGETRED(rgb), ODGETGREEN(rgb), ODGETBLUE(rgb));
        }
      }
    }
    break;
  case OdCmEntityColor::kByColor:
    break;
  default:
    color.setRGB(255, 0, 0); //red color as default
    //throw eNotImplementedYet;
  }

  destinationDbColor = color;
  return eOk;
}

OdDbStub * PrcMaterialAndColorHelper::findMaterialInUserCache(const MaterialDataStore & matData)
{
  DrawingMaterialNode matNode;
  matNode.drawingColor = matData.sourceColor;
  matNode.pMaterial = matData.sourceMaterial;
  matNode.transparency.setAlpha(255);
  std::map<DrawingMaterialNode, OdPrcObjectId>::const_iterator pIt = m_pContext->materialCache().find(matNode);
  if (pIt != m_pContext->materialCache().end())
  {
    return pIt->second;
  }
  return NULL;
}

void PrcMaterialAndColorHelper::addMaterialToUserCache(const MaterialDataStore & matData)
{
  DrawingMaterialNode matNode;
  matNode.drawingColor = matData.sourceColor;
  matNode.pMaterial = matData.sourceMaterial;
  matNode.transparency.setAlpha(255);
  m_pContext->materialCache()[matNode] = matData.materialId;
}
