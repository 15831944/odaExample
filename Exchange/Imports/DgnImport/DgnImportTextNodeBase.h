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

#ifndef _DGN_IMPORT_TEXTNODEBASE_INCLUDED_ 
#define _DGN_IMPORT_TEXTNODEBASE_INCLUDED_

#include "DgnImportPE.h"
#include "DgnImportCommon.h"
#include "DgnImportContext.h"
#include <OdaCommon.h>
#include <DbText.h>
#include <DbMText.h>
#include "DgText.h"
#include <DgFontTableRecord.h>
#include <DbTextStyleTable.h>
#include <DbTextStyleTableRecord.h>
#include <DgTextNode.h>
#include <Gi/GiTextStyle.h>
#include <DgTextStyleTableRecord.h>
#include <DgDatabase.h>

namespace TD_DGN_IMPORT 
{

//---------------------------------------------------------------------------------------------------

struct OdDgTextNodeImportData
{
  bool        m_bUnderlineText;
  bool        m_bOverlineText;
  bool        m_bUseRGBColor;
  bool        m_bUseBold;
  bool        m_bUseItalic;
  OdUInt32    m_uColorIndex;
  ODCOLORREF  m_uRGBColor;
  OdString    m_strFontName;
  double      m_dTextSize;
  double      m_dCharSpacing;
  double      m_dWidthFactor;
  double      m_dSlantAngle;
};

//---------------------------------------------------------------------------------------------------

OdString createSpecialSymbolString(const OdArray<OdDgTextExtendedProperties::OdDgSpecialSymbol>& arrSymbols);
OdDbMText::AttachmentPoint convertTextNodeJustification(OdDg::TextJustification uJust);
OdString  addTextNodeSpecialSymbols(const OdDgElement* pText);
OdCmColor convertColor(OdDgGraphicsElement* pElm);

//---------------------------------------------------------------------------------------------------

template <class T>  OdString getDgnTextFontName( T* pText, bool& bTTF )
{
  OdString strRet;

  OdDgDatabase* pDgnDb = pText->database();

  OdDgFontTableRecordPtr pFont = OdDgFontTable::getFont(pDgnDb, pText->getFontEntryId());

  if( !pFont.isNull() )
  {
    if( pFont->getType() == kFontTypeTrueType )
    {
      bTTF = true;
    }
    else
    {
      bTTF = false;
    }

    strRet = pFont.get()->getName();
  }

  return strRet;
}

//---------------------------------------------------------------------------------------------------

template <class T> OdString addTextItem(T* pText, OdDgTextNodeImportData& textData )
{
  OdString strRet = OdString::kEmpty;

  // Prepare data

  double dSlantAngle   = pText->getSlant();
  double dTextSize     = fabs(pText->getHeightMultiplier());
  double dWidthFactor  = 1.0;
  
  if( !OdZero(dTextSize) )
  {
    dWidthFactor = fabs(pText->getLengthMultiplier()) / dTextSize;
  }

  double dCharSpacing = 0;
  OdDgTextExtendedProperties::Spacing uSpacing = OdDgTextExtendedProperties::sInterCharSpacing;

  pText->getSpacing(dCharSpacing,uSpacing);

  double dTrackingPercent = 1.0;
  double dSpaceLength = fabs(pText->getLengthMultiplier()) * 0.7;

  if (uSpacing != OdDgTextExtendedProperties::sAcadInterCharSpacing)
    dTrackingPercent = (dCharSpacing + dSpaceLength) / dSpaceLength;
  else
    dTrackingPercent = dCharSpacing;

  bool bUnderline      = pText->getUnderlineFlag();
  bool bOverline       = pText->getOverlineFlag();
  bool bBold           = pText->getBoldFlag();
  bool bItalic         = pText->getSlantFlag() && OdZero(dSlantAngle);

  bool      bUseRgbColor    = true;
  OdUInt32  uColorIndex     = 0;
  OdUInt32  uRGBColor       = 0;

  OdCmColor textColor = convertColor( pText );

  if( textColor.colorMethod() == OdCmEntityColor::kByACI )
  {
    bUseRgbColor = false;
    uColorIndex  = textColor.colorIndex();
  }
  else if( textColor.colorMethod() == OdCmEntityColor::kByLayer )
  {
    bUseRgbColor = false;
    uColorIndex  = OdCmEntityColor::kACIbyLayer;
  }
  else
  {
    bUseRgbColor = true;
    uRGBColor    = ODRGB( textColor.red(), textColor.green(), textColor.blue() );
  }

  bool     bTTF = false;
  OdString strFontName = getDgnTextFontName( pText, bTTF );

  if( strFontName.isEmpty() )
  {
    strFontName = textData.m_strFontName;
  }

  // Set options

  bool bChangeFont = false;

  if( strFontName != textData.m_strFontName )
  {
    bChangeFont = true;
  }
  else if( bTTF )
  {
    if( (bBold != textData.m_bUseBold) || (bItalic != textData.m_bUseItalic) )
    {
      bChangeFont = true;
    }
  }

  if( bChangeFont )
  {
    if( bTTF )
    {
      strRet += L"\\f" + strFontName;

      if( bBold )
      {
        strRet += L"|b1";
      }
      else
      {
        strRet += L"|b0";
      }

      if( bItalic )
      {
        strRet += L"|i1";
      }
      else
      {
        strRet += L"|i0";
      }

      OdUInt32 uCharset = codePageToCharset(pText->getCodePage());

      OdString strCharset;
      strCharset.format(L"|c%03d", uCharset );

      strRet += strCharset;

      strRet += L"|p0;";
    }
    else if( OdDgnImportContext::getDgnImporter() )
    {
      strRet += L"\\F" + strFontName + L".shx;";

      OdDgnImportContext::getDgnImporter()->createShxFontFromRscFont( strFontName );
    }

    textData.m_strFontName = strFontName;
    textData.m_bUseBold    = bBold;
    textData.m_bUseItalic  = bItalic;
  }

  if( bUnderline != textData.m_bUnderlineText )
  {
    if( bUnderline )
    {
      strRet += L"\\L";
    }
    else
    {
      strRet += L"\\l";
    }

    textData.m_bUnderlineText = bUnderline;
  }

  if( bOverline != textData.m_bOverlineText )
  {
    if( bOverline )
    {
      strRet += L"\\O";
    }
    else
    {
      strRet += L"\\o";
    }

    textData.m_bOverlineText = bOverline;
  }

  bool bChangeColor = false;

  if( bUseRgbColor != textData.m_bUseRGBColor )
  {
    bChangeColor = true;
  }
  else if( bUseRgbColor )
  {
    if( (ODGETRED(uRGBColor) != ODGETRED(textData.m_uRGBColor)) ||
        (ODGETGREEN(uRGBColor) != ODGETGREEN(textData.m_uRGBColor)) ||
        (ODGETBLUE(uRGBColor) != ODGETBLUE(textData.m_uRGBColor))
      )
    {
      bChangeColor = true;
    }
  }
  else
  {
    if( uColorIndex != textData.m_uColorIndex )
    {
      bChangeColor = true;
    }
  }

  if( bChangeColor )
  {
    OdString strColor;

    if( bUseRgbColor )
    {
      strColor.format(L"\\c%d;", uRGBColor );
    }
    else
    {
      strColor.format(L"\\C%d;", uColorIndex );
    }

    strRet += strColor;

    textData.m_uColorIndex  = uColorIndex;
    textData.m_uRGBColor    = uRGBColor;
    textData.m_bUseRGBColor = bUseRgbColor;
  }

  if( !OdZero(textData.m_dTextSize - dTextSize, 1e-4 ) )
  {
    OdString strHeight;
    strHeight.format(L"\\H%fx;", dTextSize / textData.m_dTextSize );
    strHeight.replace(L',',L'.');
    strRet += strHeight;

    textData.m_dTextSize = dTextSize;
  }

  if( !OdZero(textData.m_dSlantAngle - dSlantAngle, 1e-4) )
  {
    OdString strAngle;
    strAngle.format(L"\\Q%f;", dSlantAngle * 180 / OdaPI );
    strAngle.replace(L',',L'.');
    strRet += strAngle;

    textData.m_dSlantAngle = dSlantAngle;
  }

  if( !OdZero( textData.m_dWidthFactor - dWidthFactor, 1e-4 ) )
  {
    OdString strWidthFactor;
    strWidthFactor.format(L"\\W%f;", dWidthFactor );
    strWidthFactor.replace(L',',L'.');
    strRet += strWidthFactor;

    textData.m_dWidthFactor = dWidthFactor;
  }

  if( !OdZero( textData.m_dCharSpacing - dTrackingPercent, 1e-4 ) )
  {
    OdString strSpacing;
    strSpacing.format(L"\\T%f;", dTrackingPercent );
    strSpacing.replace(L',',L'.');
    strRet += strSpacing;

    textData.m_dCharSpacing = dTrackingPercent;
  }

  // Set text

  OdString strCurTextData = pText->getText();

  if( !OdDgnImportContext::getConvertEmptyDataFieldsToSpacesFlag() )
  {
    if( pText->getTextEditFieldCount() > 0 )
    {
      for( OdInt32 i = 0; i < pText->getTextEditFieldCount(); i++ )
      {
        OdDgTextEditField txtField = pText->getTextEditFieldAt(i);
        strCurTextData = convertEmptyDataFieldsTo_( strCurTextData, txtField );
      }
    }
  }

  strCurTextData.replace("\\","\\\\");

  strRet += strCurTextData;

  // Set end of paragraph

  for( OdUInt32 k = 0; k < pText->getCrCount(); k++ )
    strRet += L"\\P";

  return strRet;
}

//---------------------------------------------------------------------------------------------------

template <class T> OdDbObjectId getDbTextStyle(T* pTextNode, double dDefaultTextSize, OdDbDatabase* pDb, OdDgTextNodeImportData& textData, bool bCheckTextSize = true )
{

  OdDgDatabase* pDgnDb = pTextNode->database();

  if( !pDb && !pDgnDb )
  {
    return OdDbObjectId::kNull;
  }

  OdUInt32 uTextStyleEntryId = pTextNode->getTextStyleEntryId();

  OdDgTextStyleTableRecordPtr pRecord;

  if( uTextStyleEntryId > 0 )
  {
    OdDgTextStyleTablePtr pTable = pDgnDb->getTextStyleTable();

    OdDgElementId idTextStyleTableRecord = pTable->getAt( uTextStyleEntryId );

    if( !idTextStyleTableRecord.isNull() )
    {
      pRecord = idTextStyleTableRecord.openObject();
    }
  }
  else
  {
    // set default
    pRecord = pDgnDb->getTextStyleTable()->getDefaultData();
  }

  if( pRecord.isNull() )
  {
    pRecord = pDgnDb->getTextStyleTable()->getDefaultData();
  }

  OdGiTextStyle style;

  if( !pRecord.isNull() )
  {
    pRecord->getGiTextStyle(style);
  }

  bool   bVerticalText = pTextNode->getVerticalFlag();
  bool   bBackwards    = pTextNode->getBackwardsFlag();
  bool   bUpsideDown   = pTextNode->getUpsidedownFlag();
  double dTextSize     = fabs(pTextNode->getHeightMultiplier());
  double dXScale       = 1.0;

  if( !OdZero(dTextSize) )
  {
    dXScale = fabs(pTextNode->getLengthMultiplier()) / dTextSize; 
  }

  if( OdZero(dXScale) )
  {
    dXScale = 1.0;
  }

  if (!OdZero(dDefaultTextSize))
  {
    dTextSize = dDefaultTextSize;
  }

  double dAngle = pTextNode->getSlant();

  OdString strFontName = OdString::kEmpty;

  style.setBackward(bBackwards);
  style.setUpsideDown(bUpsideDown);
  style.setTextSize( dTextSize );
  style.setXScale( dXScale );
  style.setVertical( bVerticalText );

  bool bBold    = pTextNode->getBoldFlag();
  bool bItalic  = pTextNode->getSlantFlag() && OdZero(dAngle);

  OdDgFontTableRecordPtr pFont = OdDgFontTable::getFont(pDgnDb, pTextNode->getFontEntryId());

  if( !pFont.isNull() )
  {
    if( pFont->getType() == kFontTypeTrueType )
    {
      style.setFont(pFont.get()->getName(), bBold, bItalic, 0, 0 );
    }
    else
    {
      style.setFont(pFont.get()->getName(), false, false, 0, 0 );
      style.setFileName( pFont.get()->getName() );
    }

    strFontName = pFont->getName();
  }

  if( pTextNode->getSlantFlag() && !OdZero(dAngle) && !bVerticalText )
  {
    style.setObliquingAngle( dAngle );
  }
  else
  {
    style.setObliquingAngle(0);
  }

  style.loadStyleRec( pDgnDb );

  textData.m_bOverlineText  = false;
  textData.m_bUnderlineText = false;
  textData.m_bUseBold       = bBold;
  textData.m_bUseItalic     = bItalic;
  textData.m_dWidthFactor   = dXScale;
  textData.m_dTextSize      = dTextSize;
  textData.m_strFontName    = strFontName;
  textData.m_dSlantAngle    = dAngle;

  double dCharSpaceing = 0;
  OdDgTextExtendedProperties::Spacing uSpacing = OdDgTextExtendedProperties::sInterCharSpacing;

  pTextNode->getSpacing(dCharSpaceing,uSpacing);

  double dSpaceLength = fabs(pTextNode->getLengthMultiplier()) * 0.7;
  double dTrackingPercent = 1.0;
  
  if( !OdZero(dSpaceLength) )
  {
    dTrackingPercent = (dCharSpaceing+dSpaceLength)/dSpaceLength;
  }

  textData.m_dCharSpacing = dTrackingPercent;

  OdDbTextStyleTablePtr pTable = pDb->getTextStyleTableId().safeOpenObject();

  for (OdDbSymbolTableIteratorPtr pIter = pTable->newIterator(); !pIter->done(); pIter->step())
  {
    OdDbTextStyleTableRecordPtr pRec = pIter->getRecord();
    OdGiTextStyle recStyle;
    giFromDbTextStyle(pRec, recStyle);

    if ( recStyle.getFont() == style.getFont()
      && recStyle.getBigFont() == style.getBigFont()
      && recStyle.isVertical() == style.isVertical()
      && recStyle.isBackward() == style.isBackward()
      && recStyle.isUpsideDown() == style.isUpsideDown()
        )
    {
      OdDgnImportContext::setResourceUsage(pIter->getRecordId());
      return pIter->getRecordId();
    }
  }

  return OdDgnImportContext::createStyleForDbText( pDb, pDgnDb, style, bCheckTextSize );
}

//---------------------------------------------------------------------------------------------------

}
#endif // _DGN_IMPORT_TEXTNODEBASE_INCLUDED_
