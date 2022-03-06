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

#ifndef _ODDBSECTIONVIEWSTYLEIMPL_INCLUDED_
#define _ODDBSECTIONVIEWSTYLEIMPL_INCLUDED_

#include "DbSectionViewStyle.h"
#include "DbModelDocViewStyleImpl.h"

class OdDbSectionViewStyleImpl : public OdDbModelDocViewStyleImpl
{
public:
  static OdDbSectionViewStyleImpl* getImpl(const OdDbSectionViewStyle* pObj)
  { 
    return (OdDbSectionViewStyleImpl*) OdDbSystemInternals::getImpl(pObj);
  }
  OdDbSectionViewStyleImpl();
protected:
  friend  class OdDbSectionViewStyle;

  virtual void setDefault(OdDbObject* pObj, OdDbDatabase* pDb = NULL);

  enum IdentifierPosition {
    // Identifier and Arrows / Identifier :
    kShowAllBendIndentifiers = 0x10, // show identifier at all bends
    kUseContinuousLabeling = 0x1, // use continuous labeling
    // Identifier and Arrows / Direction arrows :
    kShowDirectionArrows = 0x2,
    // Cutting Plane / End and bend lines :
    kShowEndAndBendLines = 0x20, // Show end and bend lines
    // Cutting Plane / Cutting plane lines :
    kShowCuttingPlaneLines = 0x8, // Show Cutting plane lines 
    // View Label / Label :
    kShowViewLabel = 0x4, 
    // Hatch / Hatch :
    kShowHatching = 0x40 // Show hatching
  };
  OdInt32 m_bitFlags; // 90 // 78=0x4e kShowHatching | kShowCuttingPlaneLines | kShowViewLabel

  OdDbObjectId m_identifierStyleId;
  OdCmColor m_identifierColor;
  double m_identifierHeight;
  OdString m_identifierExcludeCharacters;
  OdDbObjectId m_arrowStartSymbolId;
  OdDbObjectId m_arrowEndSymbolId;
  OdCmColor m_arrowSymbolColor;
  double m_arrowSymbolSize;
  double m_arrowSymbolExtensionLength;
  OdDb::LineWeight m_planeLineWeight;
  OdCmColor m_planeLineColor;
  OdDbObjectId m_planeLineTypeId;
  OdCmColor m_bendLineColor;
  OdDb::LineWeight m_bendLineWeight;
  OdDbObjectId m_bendLineTypeId;
  double m_bendLineLength;
  double m_endLineLength;
  OdDbObjectId m_viewLabelTextStyleId;
  OdCmColor m_viewLabelTextColor;
  double m_viewLabelTextHeight;
  double m_viewLabelOffset;
  OdDbModelDocViewStyle::AttachmentPoint m_viewLabelAttachment;
  OdDbModelDocViewStyle::TextAlignment m_viewLabelAlignment;
  OdString m_viewLabelPattern;
  OdString m_hatchPattern;
  OdCmColor m_hatchColor;
  OdCmColor m_hatchBackgroundColor;
  double m_hatchScale;
  OdGeDoubleArray m_hatchAngles; // rad
  OdCmTransparency m_hatchTransparency; // 0
  bool m_bUnk1, // false
       m_bUnk2; // false
  OdDbSectionViewStyle::IdentifierPosition m_viewIdentifierPosition;
  double m_viewIdentifierOffset;
  OdDbSectionViewStyle::ArrowDirection m_arrowPosition;
  double m_endLineOvershoot;
};

#endif // _ODDBSECTIONVIEWSTYLEIMPL_INCLUDED_
