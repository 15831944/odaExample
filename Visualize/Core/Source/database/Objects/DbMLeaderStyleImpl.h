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

#ifndef _ODDBMLEADERSTYLE_INCLUDED_
#define _ODDBMLEADERSTYLE_INCLUDED_

#include "DbSystemInternals.h"
#include "DbMLeaderStyle.h"

#include "CmColor.h"
#include "DbObjectImpl.h"
#include "DbEntities.h"

class OdTvDbMLeaderStyleImpl : public OdTvDbObjectImpl
{
public:
  static OdTvDbMLeaderStyleImpl* getImpl(const OdTvDbMLeaderStyle *pObj)
  { return (OdTvDbMLeaderStyleImpl*)OdTvDbSystemInternals::getImpl(pObj); }

public:
  OdString          m_strStyleDescription;
  OdUInt16          m_DrawMLeaderOrder;     // OdTvDbMLeaderStyle::DrawMLeaderOrderType
  OdUInt16          m_DrawLeaderOrder;      // OdTvDbMLeaderStyle::DrawLeaderOrderType
  OdUInt16          m_ContentType;          // OdTvDbMLeaderStyle::ContentType
  OdUInt16          m_LeftAttachment;       // OdTvDbMLeaderStyle::TextAttachmentType
  OdUInt16          m_RightAttachment;      // OdTvDbMLeaderStyle::TextAttachmentType
  OdUInt16          m_TextAngleType;        // OdTvDbMLeaderStyle::TextAngleType
  OdInt16           m_TextAlignmentType;    // OdTvDbMLeaderStyle::TextAlignmentType
  OdUInt16          m_BlockConnectionType;  // OdTvDbMLeaderStyle::BlockConnectionType

  double            m_dSegmentFirstAngle;
  double            m_dSegmentSecondAngle;

  int               m_iLeaderMaxPoints;
  OdUInt32          m_Flags;

  OdInt16           m_LeaderLineType;
  OdTvDbObjectId      m_LeaderLineTypeId;
  OdTvCmColor         m_LeaderLineColor;
  OdInt32           m_LeaderLineWeight;

  bool              m_bDoglegEnabled;
  double            m_dLandingGap;
  bool              m_bLandingEnabled;
  double            m_dLandingDistance;

  OdTvDbObjectId      m_ArrowHeadId;
  double            m_dArrowHeadSize;

  OdString          m_TextDefault;
  OdTvDbObjectId      m_TextStyleId;
  bool              m_bTextAlignLeftAlways;
  OdTvCmColor         m_TextColor;
  double            m_TextHeight;
  bool              m_TextFrameEnabled;

  double            m_AlignSpace;
  bool              m_bAlignEnabled;

  OdTvDbObjectId      m_BlockId;
  OdTvCmColor         m_BlockColor;
  OdGeScale3d       m_BlockScale;
  bool              m_BlockScaleEnabled;
  double            m_BlockRotation;
  bool              m_BlockRotationEnabled;

  double            m_Scale;

  bool              m_bPropChanged;
  bool              m_bIsAnotative;
  bool              m_bModifiedForRecompute;

  double            m_dBreakSize;

  OdInt16           m_AttachmentDirection;  // OdTvDbMLeaderStyle::TextAttachmentDirection
  OdInt16           m_TopAttachment;        // OdTvDbMLeaderStyle::TextAttachmentType
  OdInt16           m_BottomAttachment;     // OdTvDbMLeaderStyle::TextAttachmentType

  bool              m_bExtendLeaderToText;
public:
  OdTvDbMLeaderStyleImpl();

  void audit(OdTvDbAuditInfo* pAuditInfo);
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion ver);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdResult dxfInFields  (OdTvDbDxfFiler* pFiler);
  void  dxfOutFields(OdTvDbDxfFiler* pFiler);

  static void setColorFromDxf(OdUInt32 rgbm, OdTvCmColor& color);
  DBENT_EXPORT static bool isModifiedForRecompute(const OdTvDbObject* pObj);
  virtual void setModified(bool val) ODRX_OVERRIDE;
  void setModifiedForRecompute()
  {
    m_bModifiedForRecompute = true;
  }

private:
  static OdInt16 m_Version;

  bool isValidName(const OdString&);

  inline static void clearVersionXData( OdTvDbObject *pObj )
  {
    pObj->setXData(OdTvResBuf::newRb(OdTvResBuf::kDxfRegAppName, L"ACAD_MLEADERVER"));
  }

  inline static void fixVersionXData( OdTvDbObject *pObj )
  {
    OdString strAppName(L"ACAD_MLEADERVER");
    OdTvResBufPtr pRbuf = pObj->xData( strAppName );
    if( pRbuf.isNull() )
    {
      (pRbuf = OdTvResBuf::newRb( 1001 ))->setString( strAppName );
      pRbuf->insert( OdTvResBuf::newRb( 1070 ) )->setInt16( (OdInt16)2 );
      pObj->database()->newRegApp( strAppName );
      pObj->setXData( pRbuf );
    }
    else
    {
      OdTvResBufPtr pRbVersion = pRbuf->next();
      if( !pRbVersion.isNull() && pRbVersion->restype() == 1070 && pRbVersion->getInt16() == 1 )
      {
        pRbVersion->setInt16( 2 );
        pObj->setXData( pRbuf );
      }
    }

  }

  void init(OdDb::MeasurementValue measurement, bool NDBRO = false);

  friend class OdTvDbMLeaderStyle;
  friend class OdTvDbMLeader;
  friend class OdTvDbMLeaderImpl;
};

inline void odtvdbVerifyDefMLeaderStyle(OdTvDbDatabase* pDb, OdTvDbAuditInfo* pAuditInfo = 0) {
  if (!pDb->usingCoreOnly())
    OdTvDbEntitiesModulePtr(odrxSafeLoadApp(OdDbEntitiesAppName))->VerifyDefMLeaderStyle(pDb, pAuditInfo);
}

#endif // _ODDBMLINESTYLE_INCLUDED_
