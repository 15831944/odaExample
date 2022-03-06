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

#ifndef _DGN_IMPORT_TEXTNODE_INCLUDED_ 
#define _DGN_IMPORT_TEXTNODE_INCLUDED_

#include "DgnImportTextNodeBase.h"

namespace TD_DGN_IMPORT 
{

//---------------------------------------------------------------------------------------------------

template <class T> OdGePoint3d getMTextPosition(T*){return OdGePoint3d::kOrigin;}

//---------------------------------------------------------------------------------------------------

template <> OdGePoint3d getMTextPosition<OdDgTextNode2d>(OdDgTextNode2d* textNode2d)
{
  OdGePoint2d ptPos = textNode2d->getOrigin();

  return OdGePoint3d( ptPos.x, ptPos.y, 0 );
}

//---------------------------------------------------------------------------------------------------

template <> OdGePoint3d getMTextPosition<OdDgTextNode3d>(OdDgTextNode3d* textNode3d)
{
  return textNode3d->getOrigin();
}

//===================================================================================================

template <class T> OdGeVector3d getMTextNormal(T*){return OdGeVector3d::kZAxis;}

//---------------------------------------------------------------------------------------------------

template <> OdGeVector3d getMTextNormal<OdDgTextNode2d>(OdDgTextNode2d* textNode2d)
{
  return OdGeVector3d::kZAxis;
}

//---------------------------------------------------------------------------------------------------

template <> OdGeVector3d getMTextNormal<OdDgTextNode3d>(OdDgTextNode3d* textNode3d)
{
  OdGeMatrix3d matTransform = textNode3d->getRotation().getMatrix();
  matTransform.transposeIt();

  OdGeVector3d vrZAxis = OdGeVector3d::kZAxis;

  vrZAxis = vrZAxis.transformBy(matTransform);

  if( !OdZero(vrZAxis.length()) )
  {
    vrZAxis.normalize();
  }
  else
  {
    vrZAxis = OdGeVector3d::kZAxis;
  }

  return vrZAxis;
}

//===================================================================================================

template <class T> double getMTextRotAngle(T*){return 0;}

//---------------------------------------------------------------------------------------------------

template <> double getMTextRotAngle<OdDgTextNode2d>(OdDgTextNode2d* textNode2d)
{
  return textNode2d->getRotation();
}

//---------------------------------------------------------------------------------------------------

template <> double getMTextRotAngle<OdDgTextNode3d>(OdDgTextNode3d* textNode3d)
{
  OdGeMatrix3d matTransform = textNode3d->getRotation().getMatrix();
  matTransform.transposeIt();

  OdGeVector3d vrZAxis = OdGeVector3d::kZAxis;
  OdGeVector3d vrXAxis = OdGeVector3d::kXAxis;

  vrZAxis = vrZAxis.transformBy(matTransform);
  vrXAxis = vrXAxis.transformBy(matTransform);

  if( !OdZero(vrZAxis.length()) )
  {
    vrZAxis.normalize();
  }
  else
  {
    vrZAxis = OdGeVector3d::kZAxis;
  }

  if( !OdZero(vrXAxis.length()) )
  {
    vrXAxis.normalize();
  }
  else
  {
    vrXAxis = OdGeVector3d::kXAxis;
  }

  return OdGeMatrix3d::planeToWorld(vrZAxis).getCsXAxis().angleTo(vrXAxis, vrZAxis);
}

//============================================================================================

template <class T> OdString addTabSpaces( T* pTextNode )
{
  OdString strRet = OdString::kEmpty;

  OdDoubleArray arrTabStop = pTextNode->getTabStopArray();

  if( arrTabStop.isEmpty() )
  {
    OdDgElementIteratorPtr pTextIter = pTextNode->createIterator();

    for(; !pTextIter->done(); pTextIter->step() )
    {
      OdDgElementPtr pElm = pTextIter->item().openObject(OdDg::kForRead);

      if( pElm->isKindOf(OdDgText3d::desc()) )
      {
        OdDgText3dPtr pText3d = pElm;

        if( pText3d->getTextIndentationOverrideFlag() )
          arrTabStop = pText3d->getTabStopArrayOverride();
      }
      else if( pElm->isKindOf(OdDgText2d::desc()) )
      {
        OdDgText2dPtr pText2d = pElm;

        if( pText2d->getTextIndentationOverrideFlag() )
          arrTabStop = pText2d->getTabStopArrayOverride();
      }

      if( !arrTabStop.isEmpty() )
        break;
    }
  }

  if( !arrTabStop.isEmpty() )
  {
    for( OdUInt32 i = 0; i < arrTabStop.size(); i++ )
    {
      double dCurTabStop = arrTabStop[i];

      for( OdUInt32 j = i+1; j < arrTabStop.size(); j++ )
      {
        if( arrTabStop[j] < dCurTabStop )
        {
          dCurTabStop = arrTabStop[j];
          arrTabStop[j] = arrTabStop[i];
          arrTabStop[i] = dCurTabStop;
        }
      }
    }

    strRet += L"\\pt ";

    for(unsigned int i = 0; i < arrTabStop.size(); i++ )
    {
      OdString strValue;
      strValue.format(L"%f", arrTabStop[i]);
      strValue.replace(L',', L'.');

      if( strValue.find(L'.') != -1 )
      {
        while( strValue[strValue.getLength() - 1] == L'0')
          strValue = strValue.left(strValue.getLength() - 1);

        if( strValue[strValue.getLength() - 1] == L'.' )
          strValue = strValue.left(strValue.getLength() - 1);

        if( strValue.isEmpty() )
          strValue = L"0";

        strRet += strValue + L",";
      }
    }

    if( !arrTabStop.isEmpty() )
    {
      strRet = strRet.left(strRet.getLength() - 1);
      strRet += L";";
    }
  }

  return strRet;
}

//===================================================================================================

template <class T> OdString getMTextContents(T*, OdDgTextNodeImportData& textData ){return OdString::kEmpty;}

//---------------------------------------------------------------------------------------------------

template <> OdString getMTextContents<OdDgTextNode2d>(OdDgTextNode2d* textNode2d, OdDgTextNodeImportData& textData)
{
  OdString strRet;

  strRet += addTabSpaces( textNode2d );
  strRet += addTextNodeSpecialSymbols( textNode2d );

  OdDgElementIteratorPtr pIter = textNode2d->createIterator();

  for(; !pIter->done(); pIter->step() )
  {
    OdDgText2dPtr pText2d = pIter->item().openObject(OdDg::kForWrite);

    strRet += addTextItem( pText2d.get(), textData );
    strRet += addTextNodeSpecialSymbols( pText2d );
  }

  return strRet;
}

//---------------------------------------------------------------------------------------------------

template <> OdString getMTextContents<OdDgTextNode3d>(OdDgTextNode3d* textNode3d, OdDgTextNodeImportData& textData)
{
  OdString strRet;

  strRet += addTabSpaces( textNode3d );
  strRet += addTextNodeSpecialSymbols( textNode3d );

  OdDgElementIteratorPtr pIter = textNode3d->createIterator();

  for(; !pIter->done(); pIter->step() )
  {
    OdDgText3dPtr pText3d = pIter->item().openObject(OdDg::kForWrite);

    strRet += addTextItem( pText3d.get(), textData );
    strRet += addTextNodeSpecialSymbols( pText3d );
  }

  return strRet;
}

//---------------------------------------------------------------------------------------------------

double getMTextOffsetForExactlyLineSpacing(const OdString& strContents, double dTextHeight)
{
  double dRet = 0.0;

  OdString strData = strContents;

  if (strData.find(L"\\P") != -1)
  {
    if (strData.find(L"\\P") != 0)
      strData = strData.left(strData.find(L"\\P"));
    else
      strData = OdString::kEmpty;
  }

  double dScale = 1.0;

  while( strData.find(L"\\H") != -1 )
  {
    strData = strData.right(strData.getLength() - strData.find(L"\\H") - 2);
    OdString strFactor = strData;

    if( strFactor.find(L';') != -1 )
    {
      strFactor = strFactor.left(strFactor.find(L';') - 1);
      OdAnsiString strToDAnsi(strFactor);
      double dCurScale = odStrToD(strToDAnsi);
      strData = strData.right(strData.getLength() - strFactor.getLength() - 1);

      if (dCurScale > dScale)
        dScale = dCurScale;
    }
    else
      strData = OdString::kEmpty;
  }

  dRet = (dScale - 1.0)*dTextHeight;

  return dRet;
}

//---------------------------------------------------------------------------------------------------

template <class T > struct OdDgnTextNodeImportPE : OdDgnComplexElementImportPE<T>
{

//---------------------------------------------------------------------------------------------------

  void subImportElement(OdDgElement* e, OdDbBlockTableRecord* owner) ODRX_OVERRIDE
  {
    OdDbDatabase* pDb = owner->database();

    T* textNode = static_cast<T*>(e);

    //   Sometimes text nodes can contain non-text elements, may be it's not correct, but we decided to 
    // check text node items before of convert to MText.

    bool bHasWrongElements = false;

    OdDgElementIteratorPtr pTextIter = textNode->createIterator();

    for(; !pTextIter->done(); pTextIter->step() )
    {
      OdDgElementPtr pCheckElm = pTextIter->item().openObject(OdDg::kForRead);

      if( pCheckElm.isNull() || pCheckElm->getElementType() != OdDgElement::kTypeText )
      {
        bHasWrongElements = true;
        break;
      }
    }

    if( bHasWrongElements )
    {
      OdDgnComplexElementImportPE<T>::subImportElement(e, owner);
      return;
    }

    //

    double       dTextSize         = fabs(textNode->getHeightMultiplier());
    double       dSymbolWidth      = fabs(textNode->getLengthMultiplier());
    OdUInt32     uFirstFontEntryId = textNode->getFontEntryId();
    double       dLineSpacing = textNode->getLineSpacing();

    OdDgElementIteratorPtr pIter = textNode->createIterator();

    for(; !pIter->done(); pIter->step() )
    {
      OdDgElementPtr pElm = pIter->item().openObject(OdDg::kForRead);

      if( pElm->isKindOf(OdDgText3d::desc()) )
      {
        OdDgText3dPtr pText3d = pElm;

        if( !OdZero(pText3d->getHeightMultiplier()) )
        {
          dTextSize = fabs(pText3d->getHeightMultiplier());
          dSymbolWidth = fabs(pText3d->getLengthMultiplier());
        }

        uFirstFontEntryId = pText3d->getFontEntryId();

        break;
      }
      else if( pElm->isKindOf(OdDgText2d::desc()) )
      {
        OdDgText2dPtr pText2d = pElm;

        if( !OdZero(pText2d->getHeightMultiplier()) )
        {
          dTextSize = fabs(pText2d->getHeightMultiplier());
          dSymbolWidth = fabs(pText2d->getLengthMultiplier());
        }

        uFirstFontEntryId = pText2d->getFontEntryId();

        break;
      }
    }

    if( OdZero(dTextSize) )
    {
      OdDgnComplexElementImportPE<T>::subImportElement(e, owner);
      return;
    }

    OdDgTextNodeImportData curData;

    OdGePoint3d  ptPosition       = getMTextPosition(textNode);
    OdGeVector3d vrNormal         = getMTextNormal(textNode);
    double       dRotAngle        = getMTextRotAngle(textNode);
    OdDbObjectId idTextStyle      = getDbTextStyle(textNode, dTextSize, pDb, curData, false);

    OdDbMTextPtr pMText = OdDbMText::createObject();
    pMText->setDatabaseDefaults(pDb);

    pMText->setNormal(vrNormal);
    pMText->setAttachment(convertTextNodeJustification(textNode->getJustification()));
    pMText->setLocation(ptPosition);
    pMText->setRotation(dRotAngle);
    pMText->setTextHeight(dTextSize);
    pMText->setTextStyle( idTextStyle );

    OdUInt32 uMaxLength = textNode->getMaxLength();

    if( uMaxLength == 0 )
    {
      uMaxLength = 255;
    }

    if( !OdZero(dSymbolWidth) )
    {
      pMText->setWidth( uMaxLength * dSymbolWidth );
    }
    else
    {
      pMText->setWidth( uMaxLength * dTextSize );
    }

    if( textNode->getLineSpacingType() == 0 || OdZero(dLineSpacing) )
    {
      if( OdZero(dLineSpacing) )
      {
        OdDgFontTableRecordPtr pDgFont = OdDgFontTable::getFont(textNode->database(), uFirstFontEntryId);

        if (!pDgFont.isNull())
        {
          OdGiTextStyle fontTextStyle;

          if (pDgFont->getType() == kFontTypeTrueType)
            fontTextStyle.setFont(pDgFont.get()->getName(), false, false, 0, 0);
          else
            fontTextStyle.setFileName(pDgFont.get()->getName());

          fontTextStyle.setTextSize(1.0);
          fontTextStyle.loadStyleRec(textNode->database());

          OdFont* pFont = fontTextStyle.getFont();

          if (pFont)
            dLineSpacing = dTextSize * (fabs(pFont->getBelow()) / fabs(pFont->getAbove()));
        }
      }

      pMText->setLineSpacingStyle( OdDb::kExactly );

      double dLineSpacingFactor = (dTextSize + dLineSpacing) / dTextSize * 3 / 5;

      if( dLineSpacingFactor < 0.25 )
      {
        dLineSpacingFactor = 0.25;
      }

      if( dLineSpacingFactor > 4.0 )
      {
        dLineSpacingFactor = 4.0;
      }

      pMText->setLineSpacingFactor( dLineSpacingFactor );
    }
    else
    {
      pMText->setLineSpacingStyle( OdDb::kAtLeast );

      double dLineSpacingFactor = textNode->getLineSpacing();

      if( dLineSpacingFactor < 0.25 )
      {
        dLineSpacingFactor = 0.25;
      }

      if( dLineSpacingFactor > 4.0 )
      {
        dLineSpacingFactor = 4.0;
      }

      pMText->setLineSpacingFactor( dLineSpacingFactor );
    }

    copyEntityProperties( textNode, pMText );

    OdCmColor curColor = pMText->color();

    if( curColor.colorMethod() == OdCmEntityColor::kByColor )
    {
      curData.m_bUseRGBColor = true;
      curData.m_uRGBColor    = curColor.color();
    }
    else if( (curColor.colorMethod() == OdCmEntityColor::kByACI) || (curColor.colorMethod() == OdCmEntityColor::kByDgnIndex) )
    {
      curData.m_bUseRGBColor = false;
      curData.m_uColorIndex  = curColor.colorIndex();
    }
    else if( curColor.colorMethod() == OdCmEntityColor::kByLayer )
    {
      curData.m_bUseRGBColor = false;
      curData.m_uColorIndex  = OdCmEntityColor::kACIbyLayer;
    }
    else
    {
      curData.m_bUseRGBColor = false;
      curData.m_uColorIndex  = OdCmEntityColor::kACIbyBlock;
    }

    OdString     strMTextContents = getMTextContents(textNode, curData);
    pMText->setContents(strMTextContents);

    if( pMText->lineSpacingStyle() == OdDb::kExactly )
    {
      double dFactor = 0;

      switch( pMText->attachment() )
      {
        case OdDbMText::kTopLeft:
        case OdDbMText::kTopCenter:
        case OdDbMText::kTopRight:
        case OdDbMText::kTopAlign:
        case OdDbMText::kTopFit:
        case OdDbMText::kTopMid:
          dFactor = 1.0; break;
        case OdDbMText::kMiddleLeft:
        case OdDbMText::kMiddleCenter:
        case OdDbMText::kMiddleRight:
        case OdDbMText::kMiddleAlign:
        case OdDbMText::kMiddleFit:
        case OdDbMText::kMiddleMid:
          dFactor = 2.0; break;
      }

      if( !OdZero(dFactor) )
      {
        double dTopOffset = getMTextOffsetForExactlyLineSpacing(strMTextContents, pMText->textHeight()) / dFactor;

        if (!OdZero(dTopOffset))
        {
          OdGeVector3d vrOffset = pMText->direction();
          vrOffset.normalize();
          vrOffset.rotateBy(OdaPI2, vrNormal);
          pMText->setLocation(ptPosition - vrOffset * dTopOffset);
        }
      }
    }

    owner->appendOdDbEntity(pMText);

    if( pMText->actualWidth() < pMText->width() * 0.9 )
    {
      pMText->setWidth(pMText->actualWidth()*1.1);
    }
  }
};

//---------------------------------------------------------------------------------------------------

}
#endif // _DGN_IMPORT_TEXTNODE_INCLUDED_
