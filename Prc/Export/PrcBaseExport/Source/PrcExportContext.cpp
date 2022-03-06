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
#include "PrcExportContext.h"
#include "PrcCreateTopologyHelper.h"
#include "Gs/GsBaseMaterialView.h"
#include "PrcMaterialGeneric.h"

#define STL_USING_MAP
#include "OdaSTL.h"

ODRX_CONS_DEFINE_MEMBERS(OdPrcExportContext, OdRxObject, RXIMPL_CONSTR);

OdPrcExportContext::OdPrcExportContext()
  : m_colormap()
  , m_materialmap()
  , m_pDb(NULL)
{
  m_pFile = createTopologyCommon();
}

DrawingColorNode::DrawingColorNode()
  : drawingColor(OdCmEntityColor::kNone)
  , transparency(OdCmTransparency::kErrorValue)
{
}

bool DrawingColorNode::operator<(const DrawingColorNode& colNode) const
{
  if (drawingColor.color() < colNode.drawingColor.color())
  {
    return true;
  }
  if (drawingColor.color() > colNode.drawingColor.color())
  {
    return false;
  }

  if (transparency.serializeOut() < colNode.transparency.serializeOut())
  {
    return true;
  }
  return false;
}

DrawingMaterialNode::DrawingMaterialNode()
  : pMaterial(NULL)
{
}

bool DrawingMaterialNode::operator<(const DrawingMaterialNode& matNode) const
{
  if (DrawingColorNode::operator<(matNode))
  {
    return true;
  }
  if (matNode.DrawingColorNode::operator<(*this))
  {
    return false;
  }
  if (pMaterial < matNode.pMaterial)
  {
    return true;
  }
  return false;
}

OdPrcObjectId OdPrcExportContext::getLineStyleID(const DrawingColorNode & colorNode, OdPrcFileStructure &newStructure, bool createIfNotFound /*= true*/)
{
  // try find color id in cache (with tolerance)
  std::map<DrawingColorNode, OdPrcObjectId>::const_iterator pIt = colorCache().find(colorNode);
  if (pIt != colorCache().end())
  {
    // found => return line style id
    return pIt->second;
  }

  OdCmEntityColor::ColorMethod colormethod = colorNode.drawingColor.colorMethod();
  if (OdCmEntityColor::kNone == colormethod)
  {
    if (createIfNotFound && 255 != colorNode.transparency.alpha())
    {
      //create empty lineStyle
      OdPrcCategory1LineStylePtr pLs = OdPrcCategory1LineStyle::createObject();
      newStructure.addObject(pLs);
      pLs->setLineWidth(1.0f);
      newStructure.fileStructureGlobals().category1LineStyles().push_back(pLs->objectId());
      pLs->setTransparency(colorNode.transparency.alpha());
      OdPrcObjectId colorID = pLs->objectId();
      colorCache()[colorNode] = colorID;
      return colorID;
    }
    else
    {
      //nothing to create
      return NULL;
    }
  }

  OdUInt32 colorRGB = 0;

  // get rgb from color
  // color should be handled for different coloring methods
  switch (colormethod)
  {
  case OdCmEntityColor::kByACI:
  {
    //TODO: It takes color from default pallete
    OdUInt32 color32 = OdCmEntityColor::lookUpRGB(colorNode.drawingColor.colorIndex());
    colorRGB = ODRGB(ODGETBLUE(color32), ODGETGREEN(color32), ODGETRED(color32));
    break;
  }
  case OdCmEntityColor::kByColor:
  {
    colorRGB = ODRGB(colorNode.drawingColor.red(), colorNode.drawingColor.green(), colorNode.drawingColor.blue());
    break;
  }
  default:
  {
    // currently red color is set as default
    colorRGB = 0x000000ff;
  }
  }

  if (createIfNotFound)
  {
    OdPrcObjectId colorID = OdPrcCategory1LineStyle::createByColor(ODGETRED(colorRGB) / 255., ODGETGREEN(colorRGB) / 255., ODGETBLUE(colorRGB) / 255., newStructure);
    if (255 != colorNode.transparency.alpha())
    {
      OdPrcCategory1LineStylePtr pLs = colorID.openObject();
      pLs->setTransparency(colorNode.transparency.alpha());
    }
    colorCache()[colorNode] = colorID;
    return colorID;
  }

  return NULL;
}

OdPrcObjectId OdPrcExportContext::getLineStyleID(const DrawingMaterialNode & matNode, OdPrcFileStructure &fileStructure, bool createIfNotFound /*= true*/)
{
  ODA_ASSERT(matNode.pMaterial);
  ODA_ASSERT(matNode.drawingColor.isByColor() || matNode.drawingColor.isByACI());
  OdDbBaseDatabase *pDb = getDatabase();
  ODA_ASSERT(pDb);

  std::map<DrawingMaterialNode, OdPrcObjectId>::const_iterator pResult = materialCache().find(matNode);
  if (pResult != materialCache().end())
  {
    return pResult->second;
  }

  if (!createIfNotFound)
  {
    return NULL;
  }

  OdGiDrawablePtr pGiMaterial = OdDbBaseDatabasePEPtr(pDb)->openObject(matNode.pMaterial);

  OdGiMaterialTraitsTaker myTraits;
  pGiMaterial->setAttributes(&myTraits);
  OdPrcObjectId lineStylelId = OdPrcCategory1LineStyle::createByMaterial(&myTraits, &matNode.drawingColor, &matNode.transparency, pDb, fileStructure);
  materialCache()[matNode] = lineStylelId;
  return lineStylelId;
}
