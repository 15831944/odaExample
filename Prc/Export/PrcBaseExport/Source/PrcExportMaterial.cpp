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
#include "PrcExport.h"
#include "PrcExportColor.h"
#include "PrcMaterial.h"
#include "PrcMaterialGeneric.h"
#include "PrcTextureApplication.h"
#include "PrcTextureDefinition.h"
#include "PrcPolyBrepModel.h"
#include "PrcBrepModel.h"
#include "RxDictionary.h"
#include "RxSystemServices.h"
#include "RxRasterServices.h"
#include "RxVariantValue.h"
#include "DynamicLinker.h"
#include "MemoryStream.h"
#include "PrcCreateMeshHelper.h"
#include "DbBaseHostAppServices.h"
#include "PrcBrepData.h"
#include "PrcFace.h"

#include "Gs/GsBaseMaterialView.h"
#include "Gi/GiGeometrySimplifier.h"
#include "Gi/GiSubEntityTraitsDataSaver.h"
#include "Gi/GiDummyGeometry.h"
#include "PdfExportGiDrawablePE.h"

OdCmEntityColor getCurrentEntityColor(const PDF2PRCExportParams &params, const OdGiDrawable * pDrawable)
{
  OdCmEntityColor color = params.m_pTraitsData ? params.m_pTraitsData->trueColor() : OdCmEntityColor::kNone;
  if (color.isNone())
  {
    PdfExportGiDrawablePEPtr ex = PdfExportGiDrawablePE::cast(pDrawable);
    if (ex.get())
    {
      color = ex->getColor(pDrawable);
    }
  }

  if (color.isNone())
  {
    return OdCmEntityColor::kNone;
  }

  if (color.isByACI())
  {
    OdRxVariantValue rxPallet = OdRxVariantValue(params.m_extraOptions->getAt("Pallet"));
    OdRxVariantValue rxNumColors = OdRxVariantValue(params.m_extraOptions->getAt("NumColors"));
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
  return color;
}

OdCmTransparency getCurrentEntityTransparency(const PDF2PRCExportParams &params, const OdGiDrawable * pDrawable)
{
  OdCmTransparency transparency = params.m_pTraitsData ? params.m_pTraitsData->transparency() : OdCmTransparency::kErrorValue;
  if (transparency.isInvalid())
  {
    PdfExportGiDrawablePEPtr ex = PdfExportGiDrawablePE::cast(pDrawable);
    if (ex.get())
    {
      transparency = ex->getTransparency(pDrawable);
    }
  }
  return transparency;
}

OdDbStub * getCurrentEntityMaterial(const PDF2PRCExportParams &params, const OdGiDrawable * pDrawable)
{
  OdDbStub * material = params.m_pTraitsData ? params.m_pTraitsData->material() : NULL;
  if (!material)
  {
    PdfExportGiDrawablePEPtr ex = PdfExportGiDrawablePE::cast(pDrawable);
    if (ex.get())
    {
      material = ex->getMaterial(pDrawable);
    }
  }
  return material;
}

void saveCurrentTrueColor(OdPrcExportContext &context, const PDF2PRCExportParams &params, const OdGiDrawable * pDrawable)
{
  DrawingColorNode colorNode;
  colorNode.drawingColor = getCurrentEntityColor(params, pDrawable);
  colorNode.transparency = getCurrentEntityTransparency(params, pDrawable);
  OdPrcFileStructure &newStructure = *context.getFile()->fileStructures().last();

  if (colorNode.drawingColor.isNone())
  {
    return;
  }
  OdPrcObjectId lineStyleID = context.getLineStyleID(colorNode, newStructure, true);
  OdPrcPartDefinitionPtr pPD = newStructure.fileStructureTree().partDefinition().last().safeOpenObject(kForWrite);
  OdPrcRepresentationItemPtr pRI = pPD->representationItem().last().safeOpenObject(kForWrite);
  pRI->styleId() = lineStyleID;
}

void saveCurrentEntityMaterial(OdPrcExportContext &context, const PDF2PRCExportParams &params, const OdGiDrawable * pDrawable)
{
  OdDbStub * material = getCurrentEntityMaterial(params, pDrawable);
  if (material)
  {
    OdPrcFileStructure &newStructure = *context.getFile()->fileStructures().last();
    DrawingMaterialNode matNode;
    matNode.pMaterial = material;
    matNode.drawingColor = getCurrentEntityColor(params, pDrawable);
    matNode.transparency = getCurrentEntityTransparency(params, pDrawable);

    //create material
    OdPrcObjectId lineStyleID = context.getLineStyleID(matNode, newStructure);
    OdPrcPartDefinitionPtr pPD = newStructure.fileStructureTree().partDefinition().last().safeOpenObject(kForWrite);
    OdPrcRepresentationItemPtr pRI = pPD->representationItem().last().safeOpenObject(kForWrite);
    pRI->styleId() = lineStyleID;
  }
  else
  {
    saveCurrentTrueColor(context, params, pDrawable);
  }
}
