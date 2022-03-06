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

#include <OdaCommon.h>
#include "DgnImportText.h"
#include "DgnImportCommon.h"
#include <DgDatabase.h>
#include <DgText.h>
#include <DgTagElement.h>
#include <DgTextStyleTableRecord.h>
#include <DbText.h>
#include <DgFontTableRecord.h>
#include <DbTextStyleTable.h>
#include <DbTextStyleTableRecord.h>
#include <DgTagElement.h>
#include <DbBlockReference.h>
#include <DbAttribute.h>
#include <DbAttributeDefinition.h>
#include <DgSharedCellDefinition.h>
#include <DgSharedCellReference.h>
#include "DgnImportContext.h"
#include "DgnImportImpl.h"
#include "DgnImportTextNodeBase.h"

namespace TD_DGN_IMPORT {

//---------------------------------------------------------------------------------------------------

static void setTextJustification(OdDbText* dbTxt, OdDg::TextJustification tj)
{
  switch (tj)
  {
  case OdDg::kLeftTop:
  case OdDg::kLeftMarginTop:
    dbTxt->setHorizontalMode(OdDb::kTextLeft);
    dbTxt->setVerticalMode(OdDb::kTextTop);
    break;
  case OdDg::kLeftCenter:
  case OdDg::kLeftMarginCenter:
    dbTxt->setHorizontalMode(OdDb::kTextLeft);
    dbTxt->setVerticalMode(OdDb::kTextVertMid);
    break;
  case OdDg::kLeftBottom:
  case OdDg::kLeftMarginBottom:
  case OdDg::kLeftDescender:
    dbTxt->setHorizontalMode(OdDb::kTextLeft);
    dbTxt->setVerticalMode(OdDb::kTextBase);
    break;
  case OdDg::kCenterTop:
    dbTxt->setHorizontalMode(OdDb::kTextCenter);
    dbTxt->setVerticalMode(OdDb::kTextTop);
    break;
  case OdDg::kCenterCenter:
    dbTxt->setHorizontalMode(OdDb::kTextCenter);
    dbTxt->setVerticalMode(OdDb::kTextVertMid);
    break;
  case OdDg::kCenterBottom:
  case OdDg::kCenterDescender:
    dbTxt->setHorizontalMode(OdDb::kTextCenter);
    dbTxt->setVerticalMode(OdDb::kTextBase);
    break;
  case OdDg::kRightTop:
  case OdDg::kRightMarginTop:
    dbTxt->setHorizontalMode(OdDb::kTextRight);
    dbTxt->setVerticalMode(OdDb::kTextTop);
    break;
  case OdDg::kRightCenter:
  case OdDg::kRightMarginCenter:
    dbTxt->setHorizontalMode(OdDb::kTextRight);
    dbTxt->setVerticalMode(OdDb::kTextVertMid);
    break;
  case OdDg::kRightBottom:
  case OdDg::kRightMarginBottom:
  case OdDg::kRightDescender:
    dbTxt->setHorizontalMode(OdDb::kTextRight);
    dbTxt->setVerticalMode(OdDb::kTextBase);
    break;
  }
}

//---------------------------------------------------------------------------------------------------

template<class T> bool getBold(T* txt, bool& retVal ) { return false; }

//---------------------------------------------------------------------------------------------------

template<> bool getBold<OdDgText2d>(OdDgText2d* txt, bool& retVal)
{
  bool bRet = true;
  retVal = txt->getBoldFlag();
  return bRet;
}

//---------------------------------------------------------------------------------------------------

template<> bool getBold<OdDgText3d>(OdDgText3d* txt, bool& retVal)
{
  bool bRet = true;
  retVal = txt->getBoldFlag();
  return bRet;
}

//---------------------------------------------------------------------------------------------------

template<> bool getBold<OdDgTagElement>(OdDgTagElement* txt, bool& retVal)
{
  bool bRet = true;
  retVal = txt->getBoldFlag();
  return bRet;
}

//---------------------------------------------------------------------------------------------------

template<class T> bool getItalic(T* txt, bool& retVal) { return false; }

//---------------------------------------------------------------------------------------------------

template<> bool getItalic<OdDgText2d>(OdDgText2d* txt, bool& retVal)
{
  bool bRet = true;
  retVal = txt->getSlantFlag() && OdZero(txt->getSlant());
  return bRet;
}

//---------------------------------------------------------------------------------------------------

template<> bool getItalic<OdDgText3d>(OdDgText3d* txt, bool& retVal)
{
  bool bRet = true;
  retVal = txt->getSlantFlag() && OdZero(txt->getSlant());
  return bRet;
}

//---------------------------------------------------------------------------------------------------

template<> bool getItalic<OdDgTagElement>( OdDgTagElement* txt, bool& retVal)
{
  bool bRet = true;
  retVal = txt->getUseSlantFlag() && OdZero(txt->getSlant());
  return bRet;
}

//---------------------------------------------------------------------------------------------------

template<class T> void setTextStyle(T* txt, OdDbText* dbTxt)
{
  OdDgElementId dgStyleId = txt->database()->getTextStyleTable()->getAt(txt->getTextStyleEntryId());

  OdDgTextStyleTableRecordPtr pDgTextStyle;

  bool bBold   = false;
  bool bItalic = false;

  bool bBoldOverride   = getBold(txt, bBold);
  bool bItalicOverride = getItalic(txt, bItalic);

  bool bEqualBold      = true;
  bool bEqualItalics   = true;
  bool bEqualVertical  = true;

  OdDgFontTableRecordPtr pFontRec = OdDgFontTable::getFont(txt->database(), txt->getFontEntryId());

  if( dgStyleId.isValid() )
    pDgTextStyle = dgStyleId.openObject(OdDg::kForRead);

  bool bEqualFonts = true;

  if( !pDgTextStyle.isNull() )
  {
    OdUInt32 uFontData = txt->getFontEntryId();
    OdUInt32 uFontStyleData = pDgTextStyle->getFontEntryId();

    bEqualFonts = uFontStyleData == uFontData;

    bool bStyleVertical = pDgTextStyle->getTextDirection() & OdDg::kVertical;
    bool bVertical = txt->getVerticalFlag();

    bEqualVertical = bStyleVertical == bVertical;
  }

  if( !pFontRec.isNull() && pFontRec->getType() == kFontTypeTrueType )
  {
    if( bBoldOverride && !pDgTextStyle.isNull() )
      bEqualBold = (bBold == pDgTextStyle->getBoldFlag());
    else if( !pDgTextStyle.isNull() )
      bBold = pDgTextStyle->getBoldFlag();

    if( bItalicOverride && !pDgTextStyle.isNull() )
      bEqualItalics = (bItalic == (pDgTextStyle->getItalicsFlag() && OdZero(pDgTextStyle->getSlant())));
    else if( !pDgTextStyle.isNull() )
      bItalic = pDgTextStyle->getItalicsFlag() && OdZero(pDgTextStyle->getSlant()) ;
  }

  if (dgStyleId.isValid() && bEqualFonts && bEqualBold && bEqualItalics && bEqualVertical)
  {
    OdDbObjectId idDbTextStyle = OdDgnImportContext::getObjectId(dgStyleId);
    dbTxt->setTextStyle(idDbTextStyle);
  }
  else
  {
    if( pFontRec.isNull() )
      return;

    OdString styleName = L"Style-" + pFontRec->getName();

    if( txt->getVerticalFlag() )
    {
       styleName = L"Style-V-" + pFontRec->getName();
    }

    if( (pFontRec->getType() == kFontTypeTrueType) && (bBold || bItalic ) )
    {
      styleName += L"-";

      if( bBold )
        styleName += L"B";

      if( bItalic )
        styleName += L"I";
    }

    OdDbTextStyleTablePtr tst = dbTxt->database()->getTextStyleTableId().safeOpenObject(OdDb::kForWrite);
    OdDbObjectId styleId = tst->getAt(styleName);
    if (styleId.isValid())
    {
      OdDgnImportContext::setResourceUsage(styleId);
      dbTxt->setTextStyle(styleId);
    }
    else
    {
      OdDbTextStyleTableRecordPtr ts = OdDbTextStyleTableRecord::createObject();
      ts->setName(styleName);
      OdDbObjectId idStyle = tst->add(ts);

      if (pFontRec->getType() == kFontTypeShx)
      {
        ts->setFileName(pFontRec->getName());
      }
      else if( pFontRec->getType() == kFontTypeRsc && OdDgnImportContext::getDgnImporter() )
      {
        OdDgnImportContext::getDgnImporter()->createShxFontFromRscFont( pFontRec->getName() );
        ts->setFileName(pFontRec->getName() + L".shx");
      }
      else if (pFontRec->getType() == kFontTypeTrueType)
      {
        ts->setFont(pFontRec->getName(), bBold, bItalic, 0, 0);
      }
      else
        return;

      ts->setIsVertical( txt->getVerticalFlag() );

      dbTxt->setTextStyle(idStyle);
    }
  }
}

//---------------------------------------------------------------------------------------------------

template<class T> static bool isUnderlineText(T* txt )
{
  bool bRet = txt->getUnderlineFlag();
  return bRet;
}

//---------------------------------------------------------------------------------------------------

template<class T> static bool isOverlineText(T* txt )
{
  bool bRet = txt->getOverlineFlag();
  return bRet;
}

//---------------------------------------------------------------------------------------------------

void convertText2dToMText( OdDgText2d* txt, OdDbBlockTableRecord* owner )
{
  double       dTextSize = fabs(txt->getHeightMultiplier());
  double       dSymbolWidth = fabs(txt->getLengthMultiplier());

  if( OdZero(dTextSize) )
    return;

  OdDbDatabase* pDb = owner->database();

  OdDgTextNodeImportData curData;

  OdGePoint2d  ptOrigin = txt->getPosition();
  OdGePoint3d  ptPosition( ptOrigin.x, ptOrigin.y, 0.0);
  OdGeVector3d vrNormal     = OdGeVector3d::kZAxis;
  double       dRotAngle    = txt->getRotation();
  OdDbObjectId idTextStyle  = getDbTextStyle(txt, dTextSize, pDb, curData, false);

  OdDbMTextPtr pMText = OdDbMText::createObject();
  pMText->setDatabaseDefaults(pDb);

  pMText->setNormal(vrNormal);
  pMText->setAttachment( convertTextNodeJustification(txt->getJustification()));
  pMText->setLocation(ptPosition);
  pMText->setRotation(dRotAngle);
  pMText->setTextHeight(dTextSize);
  pMText->setTextStyle(idTextStyle);

  OdUInt32 uMaxLength = txt->getText().getLength();

  if( !OdZero(dSymbolWidth) )
    pMText->setWidth(uMaxLength * dSymbolWidth);
  else
    pMText->setWidth(uMaxLength * dTextSize);

  pMText->setLineSpacingStyle(OdDb::kAtLeast);
  pMText->setLineSpacingFactor(1.0);

  copyEntityProperties(txt, pMText);

  OdCmColor curColor = pMText->color();

  if (curColor.colorMethod() == OdCmEntityColor::kByColor)
  {
    curData.m_bUseRGBColor = true;
    curData.m_uRGBColor = curColor.color();
  }
  else if ((curColor.colorMethod() == OdCmEntityColor::kByACI) || (curColor.colorMethod() == OdCmEntityColor::kByDgnIndex))
  {
    curData.m_bUseRGBColor = false;
    curData.m_uColorIndex = curColor.colorIndex();
  }
  else if (curColor.colorMethod() == OdCmEntityColor::kByLayer)
  {
    curData.m_bUseRGBColor = false;
    curData.m_uColorIndex = OdCmEntityColor::kACIbyLayer;
  }
  else
  {
    curData.m_bUseRGBColor = false;
    curData.m_uColorIndex = OdCmEntityColor::kACIbyBlock;
  }

  OdString     strMTextContents = addTextItem(txt, curData);
  pMText->setContents(strMTextContents);

  owner->appendOdDbEntity(pMText);

  if (pMText->actualWidth() < pMText->width() * 0.9)
  {
    pMText->setWidth(pMText->actualWidth()*1.1);
  }
}

//---------------------------------------------------------------------------------------------------

void OdDgText2dImportPE::subImportElement(OdDgElement* e, OdDbBlockTableRecord* owner)
{
  OdDgText2d* txt = (OdDgText2d*)e;

  if( OdZero(txt->getHeightMultiplier()) )
    return;

  if( OdDgnImportContext::isImportDgTextAsDbMText() )
  {
    convertText2dToMText(txt, owner);
    return;
  }

  OdDbTextPtr dbTxt = OdDbText::createObject();
  dbTxt->setDatabaseDefaults(owner->database());
  owner->database()->addOdDbObject(dbTxt, owner->objectId());
  copyEntityProperties(txt, dbTxt);
  owner->appendOdDbEntity(dbTxt);
  setTextStyle(txt, dbTxt);

  OdString strText = txt->getText();

  if( !OdDgnImportContext::getConvertEmptyDataFieldsToSpacesFlag() )
  {
    if( txt->getTextEditFieldCount() > 0 )
    {
      for( OdInt32 i = 0; i < txt->getTextEditFieldCount(); i++ )
      {
        OdDgTextEditField txtField = txt->getTextEditFieldAt(i);
        strText = convertEmptyDataFieldsTo_( strText, txtField );
      }
    }
  }

  if( isUnderlineText(txt) )
  {
    strText = L"%%u" + strText;
  }

  if( isOverlineText(txt) )
  {
    strText = L"%%o" + strText;
  }

  OdDgFontTableRecordPtr pFontRec = txt->database()->getFontTable(OdDg::kForRead)->getFont(txt->getFontEntryId());

  if (pFontRec.isNull() || pFontRec->getType() == kFontTypeRsc) // default Char_Fast_Font font if rsc too
  {
    strText.replace(OdChar(0x5E), OdChar(0xB0));
    strText.replace(OdChar(0xC8), OdChar(0xB4));
    strText.replace(OdChar(0xC9), OdChar(0x2205));
  }

  dbTxt->setTextString(strText);

  dbTxt->setHeight(fabs(txt->getHeightMultiplier()));

  if( txt->getHeightMultiplier() < 0 )
    dbTxt->mirrorInY(true);

  if( txt->getLengthMultiplier() < 0 )
    dbTxt->mirrorInX(true);

  setTextJustification(dbTxt, txt->getJustification());
  dbTxt->setRotation(txt->getRotation());
  OdGePoint2d p2(txt->getPosition());
  OdGePoint3d p(p2.x, p2.y, 0);
  dbTxt->setOblique(txt->getSlant());
  if (!OdZero(txt->getHeightMultiplier()) && !OdZero(txt->getLengthMultiplier()))
    dbTxt->setWidthFactor(fabs(txt->getLengthMultiplier())/fabs(txt->getHeightMultiplier()));
  if (dbTxt->verticalMode() == OdDb::kTextBase &&  dbTxt->horizontalMode() == OdDb::kTextLeft)
    dbTxt->setPosition(p);
  else
    dbTxt->setAlignmentPoint(p);
  dbTxt->adjustAlignment(owner->database());

  if( txt->getOffsetFlag() )
  {
    OdGeVector3d vrOffset( txt->getLineOffset().x, txt->getLineOffset().y, 0 );
    vrOffset.rotateBy( txt->getRotation(), OdGeVector3d::kZAxis );
    OdGeMatrix3d matTransform = OdGeMatrix3d::translation( vrOffset );
    dbTxt->transformBy(matTransform);
  }

  OdDgnImportPathToDwgObject dwgPath;
  dwgPath.m_idPath.objectIds().push_back( dbTxt->objectId() );
  dwgPath.m_bExists = true;
  OdDgnImportContext::addObjectPath( e->elementId(), dwgPath );
}

//---------------------------------------------------------------------------------------------------

void convertText3dToMText(OdDgText3d* txt, OdDbBlockTableRecord* owner)
{
  double       dTextSize = fabs(txt->getHeightMultiplier());
  double       dSymbolWidth = fabs(txt->getLengthMultiplier());

  if (OdZero(dTextSize))
    return;

  OdDbDatabase* pDb = owner->database();

  OdDgTextNodeImportData curData;

  OdGePoint3d  ptPosition = txt->getPosition();

  OdGeMatrix3d matTransform = txt->getRotation().getMatrix();
  matTransform.transposeIt();

  OdGeVector3d vrNormal = OdGeVector3d::kZAxis;

  vrNormal = vrNormal.transformBy(matTransform);

  if (!OdZero(vrNormal.length()))
    vrNormal.normalize();
  else
    vrNormal = OdGeVector3d::kZAxis;

  OdGeVector3d vrZAxis = OdGeVector3d::kZAxis;
  OdGeVector3d vrXAxis = OdGeVector3d::kXAxis;

  vrZAxis = vrZAxis.transformBy(matTransform);
  vrXAxis = vrXAxis.transformBy(matTransform);

  if( !OdZero(vrZAxis.length()) )
    vrZAxis.normalize();
  else
    vrZAxis = OdGeVector3d::kZAxis;

  if (!OdZero(vrXAxis.length()))
    vrXAxis.normalize();
  else
    vrXAxis = OdGeVector3d::kXAxis;

  double dRotAngle = OdGeMatrix3d::planeToWorld(vrZAxis).getCsXAxis().angleTo(vrXAxis, vrZAxis);

  OdDbObjectId idTextStyle = getDbTextStyle(txt, dTextSize, pDb, curData, false);

  OdDbMTextPtr pMText = OdDbMText::createObject();
  pMText->setDatabaseDefaults(pDb);

  pMText->setNormal(vrNormal);
  pMText->setAttachment(convertTextNodeJustification(txt->getJustification()));
  pMText->setLocation(ptPosition);
  pMText->setRotation(dRotAngle);
  pMText->setTextHeight(dTextSize);
  pMText->setTextStyle(idTextStyle);

  OdUInt32 uMaxLength = txt->getText().getLength();

  if (!OdZero(dSymbolWidth))
    pMText->setWidth(uMaxLength * dSymbolWidth);
  else
    pMText->setWidth(uMaxLength * dTextSize);

  pMText->setLineSpacingStyle(OdDb::kAtLeast);
  pMText->setLineSpacingFactor(1.0);

  copyEntityProperties(txt, pMText);

  OdCmColor curColor = pMText->color();

  if (curColor.colorMethod() == OdCmEntityColor::kByColor)
  {
    curData.m_bUseRGBColor = true;
    curData.m_uRGBColor = curColor.color();
  }
  else if ((curColor.colorMethod() == OdCmEntityColor::kByACI) || (curColor.colorMethod() == OdCmEntityColor::kByDgnIndex))
  {
    curData.m_bUseRGBColor = false;
    curData.m_uColorIndex = curColor.colorIndex();
  }
  else if (curColor.colorMethod() == OdCmEntityColor::kByLayer)
  {
    curData.m_bUseRGBColor = false;
    curData.m_uColorIndex = OdCmEntityColor::kACIbyLayer;
  }
  else
  {
    curData.m_bUseRGBColor = false;
    curData.m_uColorIndex = OdCmEntityColor::kACIbyBlock;
  }

  OdString     strMTextContents = addTextItem(txt, curData);
  pMText->setContents(strMTextContents);

  owner->appendOdDbEntity(pMText);

  if (pMText->actualWidth() < pMText->width() * 0.9)
  {
    pMText->setWidth(pMText->actualWidth()*1.1);
  }
}

//---------------------------------------------------------------------------------------------------

void OdDgText3dImportPE::subImportElement(OdDgElement* e, OdDbBlockTableRecord* owner)
{
  OdDgText3d* txt = (OdDgText3d*)e;

  if( OdZero(txt->getHeightMultiplier()) )
    return;

  if (OdDgnImportContext::isImportDgTextAsDbMText())
  {
    convertText3dToMText(txt, owner);
    return;
  }

  OdDbTextPtr dbTxt = OdDbText::createObject();
  dbTxt->setDatabaseDefaults(owner->database());
  owner->database()->addOdDbObject(dbTxt, owner->objectId());
  copyEntityProperties(txt, dbTxt);
  owner->appendOdDbEntity(dbTxt);
  setTextStyle(txt, dbTxt);

  OdString strText = txt->getText();

  if( !OdDgnImportContext::getConvertEmptyDataFieldsToSpacesFlag() )
  {
    if( txt->getTextEditFieldCount() > 0 )
    {
      for( OdInt32 i = 0; i < txt->getTextEditFieldCount(); i++ )
      {
        OdDgTextEditField txtField = txt->getTextEditFieldAt(i);
        strText = convertEmptyDataFieldsTo_( strText, txtField );
      }
    }
  }

  if( isUnderlineText(txt) )
  {
    strText = L"%%u" + strText;
  }

  if( isOverlineText(txt) )
  {
    strText = L"%%o" + strText;
  }

  OdDgFontTableRecordPtr pFontRec = txt->database()->getFontTable(OdDg::kForRead)->getFont(txt->getFontEntryId());

  if( pFontRec.isNull() || pFontRec->getType() == kFontTypeRsc ) // default Char_Fast_Font font if rsc too
  {
    strText.replace(OdChar(0x5E), OdChar(0xB0));
    strText.replace(OdChar(0xC8), OdChar(0xB4));
    strText.replace(OdChar(0xC9), OdChar(0x2205));
  }

  dbTxt->setTextString(strText);

  dbTxt->setHeight(fabs(txt->getHeightMultiplier()));

  if( txt->getHeightMultiplier() < 0 )
    dbTxt->mirrorInY(true);

  if( txt->getLengthMultiplier() < 0 )
    dbTxt->mirrorInX(true);

  dbTxt->transformBy(txt->getRotation().getMatrix().transpose());
  setTextJustification(dbTxt, txt->getJustification());
  { //There are dgn files with invalid oblique angle
    double oblique = txt->getSlant();
    oblique -= floor(oblique/Oda2PI)*Oda2PI;
    if (oblique >= OdaPI)
      oblique -= Oda2PI;
    if (fabs(oblique) <= OdaToRadian(85.))
      dbTxt->setOblique(oblique);
  }
  if (!OdZero(txt->getHeightMultiplier()) && !OdZero(txt->getLengthMultiplier()))
    dbTxt->setWidthFactor(fabs(txt->getLengthMultiplier())/fabs(txt->getHeightMultiplier()));
  if (dbTxt->verticalMode() == OdDb::kTextBase &&  dbTxt->horizontalMode() == OdDb::kTextLeft)
    dbTxt->setPosition(txt->getPosition());
  else
    dbTxt->setAlignmentPoint(txt->getPosition());
  dbTxt->adjustAlignment(owner->database());

  if( txt->getOffsetFlag() )
  {
    OdGeVector3d vrOffset( txt->getLineOffset().x, txt->getLineOffset().y, 0 );
    vrOffset.transformBy( txt->getRotation().getMatrix().transpose() );
    OdGeMatrix3d matTransform = OdGeMatrix3d::translation( vrOffset );
    dbTxt->transformBy(matTransform);
  }

  OdDgnImportPathToDwgObject dwgPath;
  dwgPath.m_idPath.objectIds().push_back( dbTxt->objectId() );
  dwgPath.m_bExists = true;
  OdDgnImportContext::addObjectPath( e->elementId(), dwgPath );
}

//---------------------------------------------------------------------------------------------------

OdString getTagValue(OdDgTagElement* tag)
{
  OdString strRet;

  switch( tag->getDataType() )
  {
    case OdDgTagDefinition::kChar: strRet = tag->getString(); break;
    case OdDgTagDefinition::kInt16: strRet.format(L"%d", tag->getInt16()); break;
    case OdDgTagDefinition::kInt32: strRet.format(L"%d", tag->getInt32()); break;
    case OdDgTagDefinition::kDouble: strRet.format(L"%f", tag->getDouble()); break;
  }

  return strRet;
}

//---------------------------------------------------------------------------------------------------

bool isTagAssociatedWithCellHeader(OdDgElementId& idDgTagAssociatedId,
                                     OdDgTagElement* tag,
                                       OdDbBlockTableRecordPtr& pCellBlock,
                                         OdDbObjectId& idTagOwner)
{
  if( idTagOwner.isNull() || idDgTagAssociatedId.isNull() )
    return false;

  OdDgElementPtr pElement = idDgTagAssociatedId.openObject(OdDg::kForRead);

  if( pElement.isNull() || (pElement->getElementType() != OdDgElement::kTypeCellHeader) )
    return false;

  OdDbObjectPtr pBlockRefObj = idTagOwner.openObject(OdDb::kForRead);

  if (pBlockRefObj.isNull() || !pBlockRefObj->isKindOf(OdDbBlockReference::desc()))
    return false;

  OdDbBlockReferencePtr pBlockRef = pBlockRefObj;

  OdDbObjectId idBlockDef = pBlockRef->blockTableRecord();

  if (idBlockDef.isNull())
    return false;

  pCellBlock = idBlockDef.openObject(OdDb::kForWrite);

  return true;
}

//---------------------------------------------------------------------------------------------------

bool isTagIntoSharedCell( OdDgElementId& idSharedCellRef, OdDgTagElement* tag )
{
  bool bRet = false;

  if(idSharedCellRef.isNull() )
    return bRet;

  OdDgElementPtr pElm = idSharedCellRef.openObject(OdDg::kForRead);

  if (pElm.isNull() || !pElm->isKindOf(OdDgSharedCellReference::desc()))
    return bRet;

  OdDgSharedCellReferencePtr pSharedCellRef = pElm;
  OdDgSharedCellDefinitionPtr pSharedCellDef = pSharedCellRef->findDefinition();

  if( pSharedCellDef.isNull() )
    return bRet;

  OdDgElementId idBaseTagSet;
  OdUInt16 uBaseTagDef;
  tag->getTagDefinitionId(idBaseTagSet, uBaseTagDef);

  OdDgElementIteratorPtr pIter = pSharedCellDef->createIterator();

  for(; !pIter->done(); pIter->step())
  {
    OdDgElementPtr pItem = pIter->item().openObject(OdDg::kForRead);

    if( pItem->isKindOf(OdDgTagElement::desc()) )
    {
      OdDgTagElementPtr pTag = pItem;

      OdDgElementId idCurTagSet;
      OdUInt16 uCurTagDef;
      pTag->getTagDefinitionId(idCurTagSet, uCurTagDef);

      if ((idCurTagSet == idBaseTagSet) && (uCurTagDef == uBaseTagDef))
      {
        bRet = true;
        break;
      }
    }
  }

  return bRet;
}

//---------------------------------------------------------------------------------------------------

bool createAttributeDefinition(OdDgTagElement* tag, const OdDgTagDefinitionPtr& pDgTagDef, OdDbBlockTableRecord* owner)
{
  if (pDgTagDef.isNull())
    return false;

  OdDbAttributeDefinitionPtr pDbAttrDef = OdDbAttributeDefinition::createObject();
  pDbAttrDef->setDatabaseDefaults(owner->database());
  owner->database()->addOdDbObject(pDbAttrDef, owner->objectId());
  copyEntityProperties(tag, pDbAttrDef);
  owner->appendOdDbEntity(pDbAttrDef);
  setTextStyle(tag, pDbAttrDef);

  pDbAttrDef->setTag(pDgTagDef->getName());
  pDbAttrDef->setPrompt(pDgTagDef->getPrompt());
  pDbAttrDef->setInvisible(!pDgTagDef->getDisplayTagFlag());
  pDbAttrDef->setConstant(false);
  pDbAttrDef->setVerifiable(pDgTagDef->getConfirmFlag());

  OdString strTagValue = getTagValue(tag);

  OdDgFontTableRecordPtr pFontRec = tag->database()->getFontTable(OdDg::kForRead)->getFont(tag->getFontEntryId());

  if (pFontRec.isNull() || pFontRec->getType() == kFontTypeRsc) // default Char_Fast_Font font if rsc too
  {
    strTagValue.replace(OdChar(0x5E), OdChar(0xB0));
    strTagValue.replace(OdChar(0xC8), OdChar(0xB4));
    strTagValue.replace(OdChar(0xC9), OdChar(0x2205));
  }

  pDbAttrDef->setTextString(strTagValue);

  pDbAttrDef->setHeight(fabs(tag->getHeightMultiplier()));

  if (tag->getHeightMultiplier() < 0)
    pDbAttrDef->mirrorInY(true);

  if (tag->getLengthMultiplier() < 0)
    pDbAttrDef->mirrorInX(true);

  OdGeMatrix3d matTransform;

  if (tag->get3dFormatFlag())
  {
    matTransform = tag->getRotation3d().getMatrix();
    matTransform.transposeIt();
  }
  else
  {
    matTransform = OdGeMatrix3d::rotation(tag->getRotation2d(), OdGeVector3d::kZAxis);
  }

  pDbAttrDef->transformBy(matTransform);
  setTextJustification(pDbAttrDef, tag->getJustification());
  { //There are dgn files with invalid oblique angle
    double oblique = tag->getSlant();
    oblique -= floor(oblique / Oda2PI)*Oda2PI;
    if (oblique >= OdaPI)
      oblique -= Oda2PI;
    if (fabs(oblique) <= OdaToRadian(85.))
      pDbAttrDef->setOblique(oblique);
  }
  if (!OdZero(tag->getHeightMultiplier()) && !OdZero(tag->getLengthMultiplier()))
    pDbAttrDef->setWidthFactor(fabs(tag->getLengthMultiplier()) / fabs(tag->getHeightMultiplier()));
  if (pDbAttrDef->verticalMode() == OdDb::kTextBase &&  pDbAttrDef->horizontalMode() == OdDb::kTextLeft)
    pDbAttrDef->setPosition(tag->getOrigin());
  else
    pDbAttrDef->setAlignmentPoint(tag->getOrigin());

  if (tag->getOffsetUsedFlag())
  {
    matTransform = OdGeMatrix3d::translation(tag->getOffset());
    pDbAttrDef->transformBy(matTransform);
  }

  pDbAttrDef->adjustAlignment(owner->database());

  return true;
}

//---------------------------------------------------------------------------------------------------

void createAttribute(OdDgTagElement* tag, 
                       const OdDgTagDefinitionPtr& pDgTagDef, 
                         OdDbBlockReferencePtr& ownerBlockRef, 
                           OdDbBlockTableRecord* owner)
{
  if( pDgTagDef.isNull() )
    return;

  OdDbAttributePtr dbAttr = OdDbAttribute::createObject();
  dbAttr->setDatabaseDefaults(owner->database());
  owner->database()->addOdDbObject(dbAttr, ownerBlockRef->objectId());
  copyEntityProperties(tag, dbAttr);
  ownerBlockRef->appendAttribute(dbAttr);
  setTextStyle(tag, dbAttr);

  if (!pDgTagDef.isNull())
    dbAttr->setTag(pDgTagDef->getName());

  dbAttr->setTextString(getTagValue(tag));
  dbAttr->setHeight(fabs(tag->getHeightMultiplier()));
  dbAttr->setInvisible(tag->getInvisibleFlag());

  if( tag->getFreezeGroup() != 0 )
    dbAttr->setInvisible(true);

  if (tag->getHeightMultiplier() < 0)
    dbAttr->mirrorInY(true);

  if (tag->getLengthMultiplier() < 0)
    dbAttr->mirrorInX(true);

  OdGeMatrix3d matTransform;

  if (tag->get3dFormatFlag())
  {
    matTransform = tag->getRotation3d().getMatrix();
    matTransform.transposeIt();
  }
  else
  {
    matTransform = OdGeMatrix3d::rotation(tag->getRotation2d(), OdGeVector3d::kZAxis);
  }

  dbAttr->transformBy(matTransform);

  setTextJustification(dbAttr, tag->getJustification());

  try
  { //There are dgn files with invalid oblique angle
    double oblique = tag->getSlant();
    oblique -= floor(oblique / Oda2PI)*Oda2PI;
    if (oblique >= OdaPI)
      oblique -= Oda2PI;
    if (fabs(oblique) <= OdaToRadian(85.))
      dbAttr->setOblique(oblique);
  }
  catch (...)
  {
  }

  if (!OdZero(tag->getHeightMultiplier()) && !OdZero(tag->getLengthMultiplier()))
    dbAttr->setWidthFactor(fabs(tag->getLengthMultiplier()) / fabs(tag->getHeightMultiplier()));
  if (dbAttr->verticalMode() == OdDb::kTextBase &&  dbAttr->horizontalMode() == OdDb::kTextLeft)
    dbAttr->setPosition(tag->getOrigin());
  else
    dbAttr->setAlignmentPoint(tag->getOrigin());

  if (tag->getOffsetUsedFlag())
  {
    matTransform = OdGeMatrix3d::translation(tag->getOffset());
    dbAttr->transformBy(matTransform);
  }

  dbAttr->adjustAlignment(owner->database());
}

//---------------------------------------------------------------------------------------------------

void createTextFromTag(OdDgTagElement* tag, OdDbBlockTableRecord* owner)
{
  OdString strText = getTagValue(tag);

  if( strText.isEmpty() )
    return;

  if (tag->getFreezeGroup() != 0)
    return;

  // Try to export tag as text.
  OdDbTextPtr dbTxt = OdDbText::createObject();
  dbTxt->setDatabaseDefaults(owner->database());
  owner->database()->addOdDbObject(dbTxt, owner->objectId());
  copyEntityProperties(tag, dbTxt);
  owner->appendOdDbEntity(dbTxt);
  setTextStyle(tag, dbTxt);

  OdDgFontTableRecordPtr pFontRec = tag->database()->getFontTable(OdDg::kForRead)->getFont(tag->getFontEntryId());

  if (pFontRec.isNull() || pFontRec->getType() == kFontTypeRsc) // default Char_Fast_Font font if rsc too
  {
    strText.replace(OdChar(0x5E), OdChar(0xB0));
    strText.replace(OdChar(0xC8), OdChar(0xB4));
    strText.replace(OdChar(0xC9), OdChar(0x2205));
  }

  dbTxt->setTextString(strText);

  dbTxt->setHeight(fabs(tag->getHeightMultiplier()));

  if (tag->getHeightMultiplier() < 0)
    dbTxt->mirrorInY(true);

  if (tag->getLengthMultiplier() < 0)
    dbTxt->mirrorInX(true);

  OdGeMatrix3d matTransform;

  if (tag->get3dFormatFlag())
  {
    matTransform = tag->getRotation3d().getMatrix();
    matTransform.transposeIt();
  }
  else
  {
    matTransform = OdGeMatrix3d::rotation(tag->getRotation2d(), OdGeVector3d::kZAxis);
  }

  dbTxt->transformBy(matTransform);
  setTextJustification(dbTxt, tag->getJustification());
  { //There are dgn files with invalid oblique angle
    double oblique = tag->getSlant();
    oblique -= floor(oblique / Oda2PI)*Oda2PI;
    if (oblique >= OdaPI)
      oblique -= Oda2PI;
    if (fabs(oblique) <= OdaToRadian(85.))
      dbTxt->setOblique(oblique);
  }
  if (!OdZero(tag->getHeightMultiplier()) && !OdZero(tag->getLengthMultiplier()))
    dbTxt->setWidthFactor(fabs(tag->getLengthMultiplier()) / fabs(tag->getHeightMultiplier()));
  if (dbTxt->verticalMode() == OdDb::kTextBase &&  dbTxt->horizontalMode() == OdDb::kTextLeft)
    dbTxt->setPosition(tag->getOrigin());
  else
    dbTxt->setAlignmentPoint(tag->getOrigin());

  if (tag->getOffsetUsedFlag())
  {
    matTransform = OdGeMatrix3d::translation(tag->getOffset());
    dbTxt->transformBy(matTransform);
  }

  dbTxt->adjustAlignment(owner->database());
}

//---------------------------------------------------------------------------------------------------

void OdDgTagImportPE::subImportElement(OdDgElement* e, OdDbBlockTableRecord* owner)
{
  OdDgTagElement* tag = (OdDgTagElement*)e;

  // Skip binary tags.

  if (tag->getDataType() == OdDgTagDefinition::kBinary)
    return;

  // Get tag definition

  OdDgElementId idTagSet;
  OdUInt16 uTagDef;
  tag->getTagDefinitionId(idTagSet, uTagDef);

  OdDgTagDefinitionPtr pDgTagDef;

  if (!idTagSet.isNull())
  {
    OdDgTagDefinitionSetPtr pDgTagSet = idTagSet.openObject(OdDg::kForRead);

    if (!pDgTagSet.isNull())
      pDgTagDef = pDgTagSet->getByEntryId(uTagDef);
  }

  // Check tag owner element to create attribute definition, attribute or text.

  OdDbBlockTableRecord* pOwnerForAttributeDefinition = owner;

  bool bCreateDefinition = false;
  bool bCreateAttribute = true;
  bool bAllowToCreateDefinition = true;

  OdDgElementId idDgTagOwner        = tag->ownerId();
  OdDgElementId idDgTagAssociatedId = tag->getAssociationId();

  while (!idDgTagOwner.isNull())
  {
    OdDgElementPtr pDgTagOwner = idDgTagOwner.openObject(OdDg::kForRead);

    if( pDgTagOwner->isKindOf(OdDgModel::desc()) )
      break;
    else if (pDgTagOwner->isKindOf(OdDgSharedCellDefinition::desc()))
    {
      bCreateDefinition = true;
      bCreateAttribute  = false;
      break;
    }
    else
      bAllowToCreateDefinition = false;

    idDgTagOwner = pDgTagOwner->ownerId();
  }

  if (idDgTagOwner.isNull() || (bCreateDefinition && !bAllowToCreateDefinition))
    return;

  // Check association of tag

  OdDbObjectId idTagOwner;
  OdDbBlockTableRecordPtr pCellBlock;

  if( !idDgTagAssociatedId.isNull() && !bCreateDefinition )
  {
    idTagOwner = OdDgnImportContext::getObjectId(idDgTagAssociatedId);

    if (!idTagOwner.isNull())
    {
      if (!isTagIntoSharedCell(idDgTagAssociatedId, tag))
      {
        if( isTagAssociatedWithCellHeader(idDgTagAssociatedId, tag, pCellBlock, idTagOwner) )
        {
          pOwnerForAttributeDefinition = pCellBlock.get();
          bCreateDefinition = true;
          bCreateAttribute  = true;
        }
        else
          idTagOwner = 0;
      }
    }
  }

  // Create definition

  if( bCreateDefinition )
  {
    if (!createAttributeDefinition(tag, pDgTagDef, pOwnerForAttributeDefinition))
      return;
  }

  // Create attribute.
  
  if( bCreateAttribute )
  {
    if (idTagOwner.isErased() || idTagOwner.isNull())
    {
      createTextFromTag(tag, owner);
      return;
    }

    OdDbBlockReferencePtr ownerBlockRef = OdDbBlockReference::cast(idTagOwner.openObject(OdDb::kForWrite));

    if (ownerBlockRef.isNull())
      return;

    createAttribute(tag, pDgTagDef, ownerBlockRef, owner);
  }
}

}
