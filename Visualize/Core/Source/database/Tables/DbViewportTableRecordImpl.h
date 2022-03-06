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

#ifndef _ODDBVIEWPORTTABLERECORDIMPL_INCLUDED_
#define _ODDBVIEWPORTTABLERECORDIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbViewportTableRecord.h"
#include "DbAbstractViewTableRecordImpl.h"

class OdGsView;

class OdTvDbViewportTableRecordImpl : public OdTvDbAbstractViewTableRecordImpl
{
  static OdTvDbViewportTableRecordImpl* getImpl(const OdTvDbViewportTableRecord *pObj)
  { return (OdTvDbViewportTableRecordImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdGePoint2d m_LowerLeft;
  OdGePoint2d m_UpperRight;
  OdGePoint2d m_SnapBase;
  OdGePoint2d m_SnapSpacing;
  OdGePoint2d m_GridSpacing;
  double      m_dSnapRotation;
  OdInt16     m_AppStatusField;
  OdInt16     m_AppID;
  OdInt16     m_CircleZoomPercent;
  OdInt16     m_SnapIsoPair;
  OdGsView*   m_pGsView;

  struct
  {
    bool FastZoom;
    bool UcsIconOn;
    bool UcsIconAtUcsOrigin;
    bool GridOn;
    bool SnapOn;
    bool SnapStyle;
    bool UnknownFlag;
  } m_VpFlags;

  // Grid flags
  enum
  {
    kDisplayGridBeyondLimits = 1, // display the grid beyond limits (negative of "is grid bound to limits" API function)
    kIsGridAdaptive          = 2, // 
    kAllowSubdivision        = 4, // allow subdivision below grid spacing (negative of "is grid subdivision restricted" API function)
    kIsGridFollow            = 8  // is grid follow dynamic UCS
  };
  OdUInt16 m_gridFlags; // groupcode 60

public:
  OdTvDbViewportTableRecordImpl();

  inline bool isFastZoom() const { return m_VpFlags.FastZoom; }
  inline void setFastZoom(bool value) { m_VpFlags.FastZoom = value; }

  inline bool isUcsIconOn() const { return m_VpFlags.UcsIconOn; }
  inline void setUcsIconOn(bool value) { m_VpFlags.UcsIconOn = value; }

  inline bool isUcsIconAtUcsOrigin() const { return m_VpFlags.UcsIconAtUcsOrigin; }
  inline void setUcsIconAtUcsOrigin(bool value) { m_VpFlags.UcsIconAtUcsOrigin = value; }

  inline bool isSnapOn() const { return m_VpFlags.SnapOn; }
  inline void setSnapOn(bool value) { m_VpFlags.SnapOn = value; }

  inline bool isGridOn() const { return m_VpFlags.GridOn; }
  inline void setGridOn(bool value) { m_VpFlags.GridOn = value; }

  inline bool getSnapStyle() const { return m_VpFlags.SnapStyle; }
  inline void setSnapStyle(bool value) { m_VpFlags.SnapStyle = value; }

  inline bool getUnknownFlag() const { return m_VpFlags.UnknownFlag; }
  inline void setUnknownFlag(bool value) { m_VpFlags.UnknownFlag = value; }

  static void setDefaultVar(OdTvDbViewportTableRecord * pVp, OdDb::MeasurementValue measurement = OdDb::kEnglish);
  static void sync(OdTvDbViewportTableRecord* pVp, bool bLayoutActivated = false);

  TOOLKIT_EXPORT void checkTileModeCorners(OdTvDbObject * pObj, OdTvDbFiler * pFiler);

protected:
  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format,
    OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format,
    OdDb::DwgVersion version);

  void audit (OdTvDbAuditInfo* pAuditInfo);
  void setName(const OdString& name);
  int verifyName(const OdString& strName, bool bLeadAsteriskAllowed = false) const;

private:

  friend class OdTvDbViewportTableRecord;
  friend class OdTvDbViewportTableImpl;
  friend class OdTvDwgR12FileLoader;
  friend class OdTvDwgR12FileWriter;
};

#endif //_ODDBVIEWPORTTABLERECORDIMPL_INCLUDED_
