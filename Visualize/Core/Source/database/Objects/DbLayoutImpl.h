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

#ifndef _OD_DB_LAYOUT_IMPLEMENTATION_
#define _OD_DB_LAYOUT_IMPLEMENTATION_

#include "DbSystemInternals.h"
#include "DbLayout.h"
#include "DbPlotSettingsImpl.h"
#include "UCSInfo.h"
#include "ThumbnailImage.h"

class OdTvDbViewport;
class OdTvDbObjectIterator;
typedef OdSmartPtr<OdTvDbObjectIterator> OdTvDbObjectIteratorPtr;

//#pragma MARKMESSAGE(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! OdTvDbLayoutImpl is exported)
class TOOLKIT_EXPORT OdTvDbLayoutImpl : public OdTvDbPlotSettingsImpl,
                       public OdUCSInfo 
{
  static OdTvDbLayoutImpl* getImpl(const OdTvDbLayout *pObj)
  { return (OdTvDbLayoutImpl*)OdTvDbSystemInternals::getImpl(pObj);}

	OdGePoint2d       m_LimMin;
	OdGePoint2d       m_LimMax;
	OdGePoint3d       m_InsBase;
	OdGePoint3d       m_ExtMin;
	OdGePoint3d       m_ExtMax;

  OdInt16           m_Flags;
  bool getPSLTSCALE() const { return GETBIT(m_Flags, 1); }
  bool getLIMCHECK() const { return GETBIT(m_Flags, 2); }
  void setPSLTSCALE(bool val) { SETBIT(m_Flags, 1, val); }
  void setLIMCHECK(bool val)  { SETBIT(m_Flags, 2, val); }

  OdUInt16          m_status;
  bool tabSelected() const { return GETBIT(m_status, 1); }
  //bool wasActivated() const { return GETBIT(m_status, 2); }
  bool tileModeChanged() const { return GETBIT(m_status, 4); }

  void setTabSelected(bool val) { SETBIT(m_status, 1, val); }
  //void setWasActivated(bool val)  { SETBIT(m_status, 2, val); }
  void setTileModeChanged(bool val)  { SETBIT(m_status, 4, val); }

  double psUnitToMM() const;

  static OdTvDbLayoutImpl* validateLists(const OdTvDbLayout* pLayout);
  static void buildListsFromDXF(OdTvDbLayout* pLayout);
  static void buildListsFromVXTAB(OdTvDbLayout* pLayout, OdTvDbDatabase* pDb);
  bool isModelLayout() const;

public:
  OdTvDbLayoutImpl();
  
  OdInt32             m_TabOrder;
  OdString            m_strName;
	OdTvDbSoftPointerId   m_PaperSpaceId;
	OdTvDbObjectIdArray   m_viewportIds;
	OdTvDbObjectIdArray   m_viewportStack;
  OdThumbnailImage    m_preview;

  static void invalidateLists(const OdTvDbLayout* pLayout);

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);

  void audit (OdTvDbAuditInfo* pAuditInfo);

  static bool setupPaperSettings(OdTvDbLayout *pLayout, OdTvDbDatabase *pDb);
  static void setupOverallViewport(OdTvDbLayout *pLayout, OdTvDbDatabase *pDb, OdTvDbViewport *pVp);
  void activated();
  static void onInitialActivation(OdTvDbLayout *pLayout);

  static OdInt16 vpStatusField(const OdTvDbViewport* pVp);
  static OdInt16 vpNumber(const OdTvDbViewport* pVp, bool bSkipErased = true);
  static OdTvDbObjectIteratorPtr newViewportsIterator(const OdTvDbLayout* pLayout);
  static OdTvDbObjectIteratorPtr newViewportsActivityIterator(const OdTvDbLayout* pLayout);
  static void onViewportAdded(const OdTvDbViewport* pViewport);
  static double psUnitToMM(const OdTvDbLayout* pLayout);

  friend class OdTvDbDatabase;
  friend class OdTvDbDatabaseImpl;
  friend class OdTvDbLayoutUpdater;
  friend class OdTvDbLayout;
  friend class Paper;
  friend class OdTvDbViewportImpl;
  friend TOOLKIT_EXPORT void odAdjustLayouts(OdTvDbDatabase* pDb);
  friend OdTvDbLayoutPtr createModelLayout(OdTvDbDatabase* pDb, const OdTvDbObjectId blockTableRecId);
  friend OdTvDbLayoutPtr createPaperLayout(OdTvDbDatabase* pDb, const OdTvDbObjectId blockTableRecId, int tabOrder);
  friend void odSetCurrentLayout(OdTvDbDatabase* pDb, const OdTvDbObjectId& layoutId, const OdTvDbObjectId& oldLayoutId);

  static bool isValidLayoutName(const OdString& sLayoutName, OdTvDbDatabase* pDb);

  void getBorderMarginRotatedRects(OdGePoint3d *points, OdGePoint3d *MarginsPoints) const;
  static void getLayoutPaperExtents(OdTvDbLayout *pLayout, OdGeExtents2d &ext);
};

inline double OdTvDbLayoutImpl::psUnitToMM(const OdTvDbLayout* pLayout)
{
  pLayout->assertReadEnabled();
  return getImpl(pLayout)->psUnitToMM();
}

#endif // _OD_DB_LAYOUT_IMPLEMENTATION_
