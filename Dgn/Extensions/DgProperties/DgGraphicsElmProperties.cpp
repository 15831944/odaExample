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

#include "DgGraphicsElmProperties.h"
#include "DgCmColor.h"
#include "DgLevelTableRecord.h"
#include "DgTable.h"
#include "DgDatabase.h"
#include "DgDisplayStyle.h"

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ColorIndex
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementColorIndexProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getColorIndex();

  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementColorIndexProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setColorIndex(*rxvalue_cast<OdUInt32>(&value));

  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Color
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementColorProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{

  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdCmEntityColor cmColor;

  OdUInt32 uIndex = pObj->getColorIndex();

  if( uIndex == OdDg::kColorByLevel )
    cmColor.setColorMethod( OdCmEntityColor::kByLayer );
  else if( uIndex == OdDg::kColorByCell )
    cmColor.setColorMethod( OdCmEntityColor::kByBlock );
  else if( uIndex < 256 )
  {
    OdCmEntityColor::setDgnColorIndex(&uIndex, uIndex);
    cmColor.setColor( uIndex );
  }
  else
  {
    ODCOLORREF rgbColor = pObj->getColor();
    cmColor.setColorMethod( OdCmEntityColor::kByColor );
    cmColor.setRed( ODGETRED(rgbColor) );
    cmColor.setGreen( ODGETGREEN(rgbColor) );
    cmColor.setBlue( ODGETBLUE(rgbColor) );
  }

  value = cmColor;

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementColorProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  const OdCmEntityColor* pColor = rxvalue_cast<OdCmEntityColor>(&value);

  switch( pColor->colorMethod() )
  {
    case OdCmEntityColor::kByLayer:
      pObj->setColorIndex( OdDg::kColorByLevel ); break;
    case OdCmEntityColor::kByBlock:
      pObj->setColorIndex( OdDg::kColorByCell ); break;
    case OdCmEntityColor::kByACI:
      pObj->setColorIndex( pColor->colorIndex() ); break; //???
    case OdCmEntityColor::kByDgnIndex:
      pObj->setColorIndex( pColor->colorIndex() ); break;
    case OdCmEntityColor::kByPen:
      pObj->setColorIndex( pColor->colorIndex() ); break; //???
    case OdCmEntityColor::kByColor:
    {
      ODCOLORREF curColor = ODRGB( pColor->red(), pColor->green(), pColor->blue());
      pObj->setColor(curColor);
    }
  }

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: GraphicsGroupIndex
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementGraphicsGroupIndexProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getGraphicsGroupEntryId();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementGraphicsGroupIndexProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setGraphicsGroupEntryId(*rxvalue_cast<OdUInt32>(&value));

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Class
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementClassProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getClass();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementClassProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setClass(*rxvalue_cast<OdDgGraphicsElement::Class>(&value));

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LevelIndex
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementLevelIndexProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getLevelEntryId();

  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementLevelIndexProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setLevelEntryId(*rxvalue_cast<OdUInt32>(&value));
 
  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Level
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementLevelProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getLevelId();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementLevelProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setLevelId(*rxvalue_cast<OdDgElementId>(&value));
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LevelName
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementLevelNameProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdString      strRet  = OdString::kEmpty;
  OdDgElementId idLevel = pObj->getLevelId();

  if( !idLevel.isNull() )
  {
    OdDgLevelTableRecordPtr pLevel = idLevel.openObject(OdDg::kForRead);
    strRet = pLevel->getName();
  }

  value = strRet;

  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementLevelNameProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdString strLevelName = *rxvalue_cast<OdString>(&value);

  OdDgDatabase* pDb = pObj->database();

  if( !pDb )
    return eNotApplicable;

  OdDgLevelTablePtr pLevelTable = pDb->getLevelTable(OdDg::kForRead);

  OdDgElementId idLevel = pLevelTable->getAt(strLevelName);

  if( !idLevel.isNull() )
    pObj->setLevelId(idLevel);
  else
    return eNotApplicable;
 
  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LineStyleIndex
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementLineStyleIndexProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getLineStyleEntryId();

  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementLineStyleIndexProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setLineStyleEntryId(*rxvalue_cast<OdUInt32>(&value));
 
  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LineStyle
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementLineStyleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getLineStyleId();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementLineStyleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setLineStyleId(*rxvalue_cast<OdDgElementId>(&value));
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LineStyleName
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementLineStyleNameProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdString      strRet  = OdString::kEmpty;
  OdDgElementId idLineStyle = pObj->getLineStyleId();

  if( !idLineStyle.isNull() )
  {
    OdDgLineStyleTableRecordPtr pLineStyle = idLineStyle.openObject(OdDg::kForRead);
    strRet = pLineStyle->getName();
  }

  value = strRet;

  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementLineStyleNameProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdString strLineStyleName = *rxvalue_cast<OdString>(&value);

  OdDgDatabase* pDb = pObj->database();

  if( !pDb )
    return eNotApplicable;

  OdDgLineStyleTablePtr pLineStyleTable = pDb->getLineStyleTable(OdDg::kForRead);

  OdDgElementId idLineStyle = pLineStyleTable->getAt(strLineStyleName);

  if( !idLineStyle.isNull() )
    pObj->setLineStyleId(idLineStyle);
  else
    return eNotApplicable;
 
  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
//                                          property: LineWeight
//-----------------------------------------------------------------------------------------------------------------------

OdDb::LineWeight mapLineWeightToDb(OdUInt32 uLW)
{
  switch( uLW )
  {
    case OdDg::kLineWeightByLevel: return OdDb::kLnWtByLayer;
    case OdDg::kLineWeightByCell: return OdDb::kLnWtByBlock;
    case 0: return OdDb::kLnWt000;
    case 1: return OdDb::kLnWt013;
    case 2: return OdDb::kLnWt030;
    case 3: return OdDb::kLnWt040;
    case 4: return OdDb::kLnWt053;
    case 5: return OdDb::kLnWt070;
    case 6: return OdDb::kLnWt080;
    case 7: return OdDb::kLnWt100;
    case 8: return OdDb::kLnWt106;
    case 9: return OdDb::kLnWt120;
    case 10: return OdDb::kLnWt140;
    case 11: return OdDb::kLnWt158;
    case 12: return OdDb::kLnWt158;
    case 13: return OdDb::kLnWt158;
    case 14: return OdDb::kLnWt200;
    default: return OdDb::kLnWt211;
  }
}

//-----------------------------------------------------------------------------------------------------------------------

OdUInt32 mapLineWeightToDg(OdDb::LineWeight uLW)
{
  switch (uLW)
  {
    case OdDb::kLnWtByLayer: return OdDg::kLineWeightByLevel;
    case OdDb::kLnWtByBlock: return OdDg::kLineWeightByCell;
    case OdDb::kLnWt000: return 0;
    default:
    {
      if (uLW <= OdDb::kLnWt013) return 1;
      else if (uLW <= OdDb::kLnWt030) return 2;
      else if (uLW <= OdDb::kLnWt040) return 3;
      else if (uLW <= OdDb::kLnWt053) return 4;
      else if (uLW <= OdDb::kLnWt070) return 5;
      else if (uLW <= OdDb::kLnWt080) return 6;
      else if (uLW <= OdDb::kLnWt100) return 7;
      else if (uLW <= OdDb::kLnWt106) return 8;
      else if (uLW <= OdDb::kLnWt120) return 9;
      else if (uLW <= OdDb::kLnWt140) return 10;
      else if (uLW <= OdDb::kLnWt158) return 12;
      else if (uLW <= OdDb::kLnWt200) return 14;
      else return OdDb::kLnWt211;
    }
  }
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementLineWeightProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = (OdDb::LineWeight)(mapLineWeightToDb(pObj->getLineWeight()));

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementLineWeightProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setLineWeight(mapLineWeightToDg((*rxvalue_cast<OdDb::LineWeight>(&value))));
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Thickness
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementThicknessProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getThickness();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementThicknessProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setThickness(*rxvalue_cast<double>(&value));
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Priority
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementPriorityProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getPriority();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementPriorityProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setPriority(*rxvalue_cast<OdInt32>(&value));
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Invisible
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementInvisibleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getInvisibleFlag();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementInvisibleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setInvisibleFlag(*rxvalue_cast<bool>(&value));
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: 3D
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElement3DProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->get3dFormatFlag();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ViewIndependent
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementViewIndependentProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getViewIndependentFlag();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementViewIndependentProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setViewIndependentFlag(*rxvalue_cast<bool>(&value));
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: NonPlanar
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementNonPlanarProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getNonPlanarFlag();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: NotSnappable
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementNotSnappableProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getNotSnappableFlag();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementNotSnappableProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setNotSnappableFlag(*rxvalue_cast<bool>(&value));
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: HBit
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementHBitProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getHbitFlag();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementHBitProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setHbitFlag(*rxvalue_cast<bool>(&value));
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Transparency
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementTransparencyProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  value = pObj->getTransparency();

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementTransparencyProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  pObj->setTransparency(*rxvalue_cast<OdCmTransparency>(&value));
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Extents
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementExtentsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdGeExtents3d extData;
  pObj->getGeomExtents(extData);
  value = extData;

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: DisplayStyle
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementDisplayStyleProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdDgDisplayStyleGraphicsElementPEPtr pElementPE = OdDgDisplayStyleGraphicsElementPEPtr(OdRxObjectPtr(pObj));
  OdDgElementId idDisplayStyle;

  if( !pElementPE.isNull() )
  {
    OdDgDisplayStyleTableRecordPtr pDisplayStyle = pElementPE->getDispalyStyle(pObj);

    if( !pDisplayStyle.isNull() )
      idDisplayStyle = pDisplayStyle->elementId();
  }

  value = idDisplayStyle;

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgGraphicsElementDisplayStyleProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdDgElementId idDisplayStyle = *rxvalue_cast<OdDgElementId>(&value);
  OdDgDisplayStyleGraphicsElementPEPtr pElementPE = OdDgDisplayStyleGraphicsElementPEPtr(OdRxObjectPtr(pObj));

  if( idDisplayStyle.isNull() )
  {
    pElementPE->setDispalyStyle(pObj, OdDgDisplayStyleTableRecordPtr() );
  }
  else
  {
    OdDgElementPtr pElm = idDisplayStyle.openObject(OdDg::kForRead);

    if( !pElm.isNull() && pElm->isKindOf(OdDgDisplayStyleTableRecord::desc()) )
    {
      OdDgDisplayStyleTableRecordPtr pDisplayStyle = pElm;
      pElementPE->setDispalyStyle(pObj, pDisplayStyle);
    }
  }
 
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: DisplayStyleName
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementDisplayStyleNameProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdString      strRet  = OdString::kEmpty;

  OdDgDisplayStyleGraphicsElementPEPtr pElementPE = OdDgDisplayStyleGraphicsElementPEPtr(OdRxObjectPtr(pObj));
  OdDgElementId idDisplayStyle;

  if( !pElementPE.isNull() )
  {
    OdDgDisplayStyleTableRecordPtr pDisplayStyle = pElementPE->getDispalyStyle(pObj);

    if( !pDisplayStyle.isNull() )
      strRet = pDisplayStyle->getName();
  }

  value = strRet;

  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------
/*
OdResult OdDgGraphicsElementDisplayStyleNameProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdString strDisplayStyleName = *rxvalue_cast<OdString>(&value);

  OdDgDatabase* pDb = pObj->database();

  if( !pDb )
    return eNotApplicable;

  OdDgDisplayStyleGraphicsElementPEPtr pElementPE = OdDgDisplayStyleGraphicsElementPEPtr(OdRxObjectPtr(pObj));
  OdDgDisplayStyleTablePtr pDisplayStyleTable = pDb->getDisplayStyleTable(OdDg::kForRead);

  if( strDisplayStyleName.isEmpty() )
  {
    pElementPE->setDispalyStyle(pObj, OdDgDisplayStyleTableRecordPtr() );
    return eOk;
  }

  OdDgElementId idDisplayStyle = pDisplayStyleTable->getAt(strDisplayStyleName);

  if( idDisplayStyle.isNull() )
    return eNotApplicable;

  OdDgElementPtr pElm = idDisplayStyle.openObject(OdDg::kForRead);

  if( !pElm.isNull() && pElm->isKindOf(OdDgDisplayStyleTableRecord::desc()) )
  {
    OdDgDisplayStyleTableRecordPtr pDisplayStyle = pElm;
    pElementPE->setDispalyStyle(pObj, pDisplayStyle);
  }
 
  return eOk;
}
*/
//-----------------------------------------------------------------------------------------------------------------------



