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

#ifndef _ODDBDETAILVIEWSTYLEIMPL_INCLUDED_
#define _ODDBDETAILVIEWSTYLEIMPL_INCLUDED_

#include "DbDetailViewStyle.h"
#include "DbModelDocViewStyleImpl.h"

class OdDbDetailViewStyleImpl : public OdDbModelDocViewStyleImpl
{
public:
  static OdDbDetailViewStyleImpl* getImpl(const OdDbDetailViewStyle* pObj)
  { 
    return (OdDbDetailViewStyleImpl*) OdDbSystemInternals::getImpl(pObj);
  }
  OdDbDetailViewStyleImpl();
protected:
  friend class OdDbDetailViewStyle;

  virtual void setDefault(OdDbObject* pObj, OdDbDatabase* pDb = NULL);

  enum ShowFlags {
    en_UnknownAlwaysOn = 0x1,
    // View Label / Label : 
    en_ShowViewLabel = 0x2
  };
  OdInt32 m_bitFlags; // 0x3 (en_UnknownAlwaysOn | en_ShowViewLabel)

  OdDbObjectId m_identifierStyleId; // text style // x55 Standard
  OdCmColor m_identifierColor; // text color // 256 kByLayer
  double m_identifierHeight; // text height // 0.24

  OdDbObjectId m_arrowSymbolId; // 0 Closed filled
  OdCmColor m_arrowSymbolColor; // 256 kByLayer
  double m_arrowSymbolSize; // 0.24
  OdString m_Ac27Unk2; // empty
  double m_identifierOffset; // 0.36
  enum PlacementFlags {
    en_WithLeader = 0x1, // == AddLeaderWhenMovingIdentifierAwayFromBoundary
    en_OnBoundary = 0x2  // == PlaceIdentifierInGapOnDetailViewBoundary (!PlaceIdentifierOutsideTheDetailViewBoundary) // == en_ShowArrows
  };
  OdDbDetailViewStyle::IdentifierPlacement m_bitPlacement; // 0x3 (kOnBoundaryWithLeader)
  
  OdDbObjectId m_boundaryLineTypeId; // x5D Continuous
  OdDb::LineWeight m_boundaryLineWeight; // 25 kLnWt025	
  OdCmColor m_boundaryLineColor; // 256 kByLayer
  
  OdDbObjectId m_viewLabelTextStyleId; // text style //x55 Standard
  OdCmColor m_viewLabelTextColor; // 256 kByLayer
  double m_viewLabelTextHeight; // 0.24
  OdDbModelDocViewStyle::AttachmentPoint m_viewLabelAttachment; // 1 kBelowView
  double m_viewLabelOffset; // 0.75
  OdDbModelDocViewStyle::TextAlignment m_viewLabelAlignment; // 1 kTextAlignmentCenter
  OdString m_viewLabelPattern; // L"%<\\AcVar ViewType \\f "%tc1">% %<\\AcVar ViewDetailId>%\\PSCALE %<\\AcVar ViewScale \\f \"%sn\">%"
  
  OdDbObjectId m_connectionLineTypeId; // linetype // x5D Continuous
  OdDb::LineWeight m_connectionLineWeight; // 25 kLnWt025	
  OdCmColor m_connectionLineColor; // 256 kByLayer
  
  OdDbObjectId m_borderLineTypeId; // linetype // x5D Continuous
  OdDb::LineWeight m_borderLineWeight; // 25 kLnWt025
  OdCmColor m_borderLineColor; // 256 kByLayer
  OdDbDetailViewStyle::ModelEdge m_modelEdge; // 0 OdDbDetailViewStyle::kSmooth 
};

#endif // _ODDBDETAILVIEWSTYLEIMPL_INCLUDED_
