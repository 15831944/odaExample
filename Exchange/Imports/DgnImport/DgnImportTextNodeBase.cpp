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

#include "DgnImportTextNodeBase.h"
#include <DgView.h>
#include "DgnImportContext.h"

namespace TD_DGN_IMPORT {

//---------------------------------------------------------------------------------------------------

OdCmColor convertColor(OdDgGraphicsElement* pElm)
{
  OdCmColor retVal;

  OdUInt32 uColorIndex = pElm->getColorIndex();

  OdDgViewPtr pActiveView = OdDgnImportContext::getActiveView();

  if( OdDgnImportContext::getActualViewFlags().getUseLevelSymbologyFlag() )
  {
    OdUInt32 uTmp1;
    OdInt32  uTmp2;
    bool     bLineStyleIsFromLevelDatabase = false;
    applyLevelSymbologyOverrides(OdDgnImportContext::getLevelOverride(pElm->getLevelId()), uColorIndex, uTmp1, uTmp2, bLineStyleIsFromLevelDatabase);
  }

  setDwgColorByDgnIndex(pElm->database(), retVal, uColorIndex);

  return retVal;
}

//---------------------------------------------------------------------------------------------------

OdString createSpecialSymbolString(const OdArray<OdDgTextExtendedProperties::OdDgSpecialSymbol>& arrSymbols)
{
  OdString strRet;

  for (OdUInt32 i = 0; i < arrSymbols.size(); i++)
  {
    if (arrSymbols[i] == OdDgTextExtendedProperties::kTab)
      strRet += L"\t";
    else if (arrSymbols[i] == OdDgTextExtendedProperties::kNewLine)
      strRet += L"\\P";
    else if (arrSymbols[i] == OdDgTextExtendedProperties::kParagraph)
      strRet += L"\\P";
  }

  return strRet;
}

//---------------------------------------------------------------------------------------------------

OdDbMText::AttachmentPoint convertTextNodeJustification(OdDg::TextJustification uJust)
{
  OdDbMText::AttachmentPoint uRet = OdDbMText::kBottomLeft;

  switch (uJust)
  {
    case OdDg::kLeftTop:
    case OdDg::kLeftMarginTop:
    {
      uRet = OdDbMText::kTopLeft;
    } break;

    case OdDg::kLeftCenter:
    case OdDg::kLeftMarginCenter:
    {
      uRet = OdDbMText::kMiddleLeft;
    } break;

    case OdDg::kLeftBottom:
    case OdDg::kLeftMarginBottom:
    case OdDg::kLeftDescender:
    {
      uRet = OdDbMText::kBottomLeft;
    } break;

    case OdDg::kCenterTop:
    {
      uRet = OdDbMText::kTopCenter;
    } break;

    case OdDg::kCenterCenter:
    {
      uRet = OdDbMText::kMiddleCenter;
    } break;

    case OdDg::kCenterBottom:
    case OdDg::kCenterDescender:
    {
      uRet = OdDbMText::kBottomCenter;
    } break;

    case OdDg::kRightTop:
    case OdDg::kRightMarginTop:
    {
      uRet = OdDbMText::kTopRight;
    } break;

    case OdDg::kRightCenter:
    case OdDg::kRightMarginCenter:
    {
      uRet = OdDbMText::kMiddleRight;
    } break;

    case OdDg::kRightBottom:
    case OdDg::kRightMarginBottom:
    case OdDg::kRightDescender:
    {
      uRet = OdDbMText::kBottomRight;
    } break;
  }

  return uRet;
}

//---------------------------------------------------------------------------------------------------

OdString addTextNodeSpecialSymbols(const OdDgElement* pText)
{
  OdString strRet = OdString::kEmpty;

  if (!pText)
  {
    return strRet;
  }

  OdArray<OdDgTextExtendedProperties::OdDgSpecialSymbol> arrSymbols;

  if (pText->isKindOf(OdDgTextNode3d::desc()))
  {
    OdDgTextNode3d* pTextNode3d = (OdDgTextNode3d*)(pText);
    arrSymbols = pTextNode3d->getTextNodeStartSpecialSymbols();
  }
  else if (pText->isKindOf(OdDgTextNode2d::desc()))
  {
    OdDgTextNode2d* pTextNode2d = (OdDgTextNode2d*)(pText);
    arrSymbols = pTextNode2d->getTextNodeStartSpecialSymbols();
  }
  else if (pText->isKindOf(OdDgText3d::desc()))
  {
    OdDgText3d* pText3d = (OdDgText3d*)(pText);
    arrSymbols = pText3d->getSpecialSymbolsAfterText();
  }
  else if (pText->isKindOf(OdDgText2d::desc()))
  {
    OdDgText2d* pText2d = (OdDgText2d*)(pText);
    arrSymbols = pText2d->getSpecialSymbolsAfterText();
  }

  if (!arrSymbols.isEmpty())
    strRet += createSpecialSymbolString(arrSymbols);

  return strRet;
}

//---------------------------------------------------------------------------------------------------

}
