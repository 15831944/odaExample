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

class OdDbViewport;
class OdDbObjectIterator;
typedef OdSmartPtr<OdDbObjectIterator> OdDbObjectIteratorPtr;

//#pragma MARKMESSAGE(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! OdDbLayoutImpl is exported)
class TOOLKIT_EXPORT OdDbLayoutImpl : public OdDbPlotSettingsImpl,
                       public OdUCSInfo 
{
  static OdDbLayoutImpl* getImpl(const OdDbLayout *pObj)
  { return (OdDbLayoutImpl*)OdDbSystemInternals::getImpl(pObj);}

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

  static OdDbLayoutImpl* validateLists(const OdDbLayout* pLayout);
  static void buildListsFromDXF(OdDbLayout* pLayout);
  static void buildListsFromVXTAB(OdDbLayout* pLayout, OdDbDatabase* pDb);
  bool isModelLayout() const;

public:
  OdDbLayoutImpl();
  
  OdInt32             m_TabOrder;
  OdString            m_strName;
	OdDbSoftPointerId   m_PaperSpaceId;
	OdDbObjectIdArray   m_viewportIds;
	OdDbObjectIdArray   m_viewportStack;
  OdThumbnailImage    m_preview;

  static void invalidateLists(const OdDbLayout* pLayout);

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdDbAuditInfo* pAuditInfo);

  void audit (OdDbAuditInfo* pAuditInfo);

  static bool setupPaperSettings(OdDbLayout *pLayout, OdDbDatabase *pDb);
  static void setupOverallViewport(OdDbLayout *pLayout, OdDbDatabase *pDb, OdDbViewport *pVp);
  void activated();
  static void onInitialActivation(OdDbLayout *pLayout);

  static OdInt16 vpStatusField(const OdDbViewport* pVp);
  static OdInt16 vpNumber(const OdDbViewport* pVp, bool bSkipErased = true);
  static OdDbObjectIteratorPtr newViewportsIterator(const OdDbLayout* pLayout);
  static OdDbObjectIteratorPtr newViewportsActivityIterator(const OdDbLayout* pLayout);
  static void onViewportAdded(const OdDbViewport* pViewport);
  static double psUnitToMM(const OdDbLayout* pLayout);

  friend class OdDbDatabase;
  friend class OdDbDatabaseImpl;
  friend class OdDbLayoutUpdater;
  friend class OdDbLayout;
  friend class Paper;
  friend class OdDbViewportImpl;
  friend TOOLKIT_EXPORT void odAdjustLayouts(OdDbDatabase* pDb);
  friend OdDbLayoutPtr createModelLayout(OdDbDatabase* pDb, const OdDbObjectId blockTableRecId);
  friend OdDbLayoutPtr createPaperLayout(OdDbDatabase* pDb, const OdDbObjectId blockTableRecId, int tabOrder);
  friend void odSetCurrentLayout(OdDbDatabase* pDb, const OdDbObjectId& layoutId, const OdDbObjectId& oldLayoutId);

  static bool isValidLayoutName(const OdString& sLayoutName, OdDbDatabase* pDb);

  void getBorderMarginRotatedRects(OdGePoint3d *points, OdGePoint3d *MarginsPoints) const;
  static void getLayoutPaperExtents(OdDbLayout *pLayout, OdGeExtents2d &ext);
};

inline double OdDbLayoutImpl::psUnitToMM(const OdDbLayout* pLayout)
{
  pLayout->assertReadEnabled();
  return getImpl(pLayout)->psUnitToMM();
}

#endif // _OD_DB_LAYOUT_IMPLEMENTATION_
