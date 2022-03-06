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

#ifndef _ODDBVIEWPORTIMPL_INCLUDED_
#define _ODDBVIEWPORTIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "IdArrays.h"
#include "ViInfo.h"
#include "DbSystemInternals.h"
#include "BasePerThreadStorage.h"
#include "DbViewport.h"

class OdDbViewportImpl : public OdDbEntityImpl, public OdViInfo
{
  typedef enum
  {
    STATUS_PERSPECTIVE      = 0x1,
    STATUS_FRONTCLIP        = 0x2,
    STATUS_BACKCLIP         = 0x4,
    STATUS_UCSFOLLOW        = 0x8,
    STATUS_FRONTCLIPATEYE   = 0x10,
    STATUS_UCSICON          = 0x20,
    STATUS_UCSATORIGIN      = 0x40,
    STATUS_FASTZOOM         = 0x80,
    STATUS_SNAPON           = 0x100,
    STATUS_GRIDON           = 0x200,
    STATUS_SNAPSTYLEISO     = 0x400,
    STATUS_HIDDENINPLOT     = 0x800,
    STATUS_SNAPISOPAIRTOP   = 0x1000,
    STATUS_SNAPISOPAIRRIGHT = 0x2000,
    STATUS_ZOOMLOCKING      = 0x4000,
    STATUS_ALWAYS           = 0x8000,
    STATUS_NONRECTCLIP      = 0x10000,
    STATUS_OFF              = 0x20000,
    GRID_BEYOND_LIMITS      = 0x40000,  // display grid beyond limits
    GRID_ADAPTIVE           = 0x80000,  // is grid adaptive
    GRID_ALLOW_SUBDIVS      = 0x100000, // are subdivisions allowed
    GRID_FOLLOW_UCS         = 0x200000  // is grid follow dynamic UCS
  } ViewportFlags;
  
  OdDbHardPointerId m_VXTableRecordId;

public:
  static OdDbViewportImpl* getImpl(const OdDbViewport *pObj)
  { return (OdDbViewportImpl*)OdDbSystemInternals::getImpl(pObj);}

  static OdInt16 number(const OdDbViewport* pVp, bool bSkipErased = true);
  static OdInt16 statusField(const OdDbViewport* pVp);

  static bool viewportIdLessFn(const OdDbViewport* pVp1, const OdDbViewport* pVp2);
  static bool stackValLessFn(const OdDbViewport* pVp1, const OdDbViewport* pVp2);

  static OdDbObjectId vxTableRecordId(const OdDbViewport* pVp);
  static void setVxTableRecordId(OdDbViewport* pVp, OdDbObjectId id);
  static OdDbObjectId layoutId(const OdDbViewport* pVp);
  static bool isOverallVport(const OdDbViewport* pVp);

  static void syncPs(OdDbViewport* pVp, bool bLayoutActivated = false);
  static void syncMs(OdDbViewport* pVp, bool bLayoutActivated = false);

  static OdUInt32 isOverallInvalid(const OdDbViewport* pVp);
  static void fixOverallParams(OdDbViewport* pVp, OdUInt32 bits);
  static void fixOverallParams(OdRxObject *pView, const OdDbViewport* pVp);

  bool hasXData(OdDb::DwgVersion ver, OdDbFiler::FilerType filerType) const;
  void dxfOutXData(OdDbDxfFiler* pFiler) const;
  OdResBufPtr xData(const OdChar* regappName, bool treatLayerNameAsHandle = false) const ODRX_OVERRIDE;
  void setXData(const OdResBuf* pXData, bool treatLayerNameAsHandle = false, OdUInt16 maxSize = XDATA_MAX_SIZE, bool bTreatRegappAsId = false);
  void freezeLayersInViewport(const OdDbObjectIdArray &layerIds);

  OdGePoint3d       m_Center;
  double            m_dWidth;
  double            m_dHeight;
  OdGePoint2d       m_SnapBase;
  OdGeVector2d      m_SnapDist;
  OdGeVector2d      m_GridDist;
  double            m_dSnapAngle;
  OdInt16           m_CircleZoom;
  OdHardPtrIdArray  m_FrozenLayers;
  OdDbHardPointerId m_ClipId;
  OdInt32           m_StatusFlags;
  OdString          m_strStyleSheet;
  OdString          m_strEffStyleSheet;
  bool              m_bUcsSavedWithViewport;
  bool              m_bVpUcsIconDisplayed;
  OdInt16           m_SnapIsoPair;
  OdInt16           m_dxf68;
  OdInt16           m_dxf69;
  OdInt16           m_shadePlot;
  bool              m_bAddToLayout;

  OdGsView* m_pGsView;
  OdGsView *getGsView() const { return m_pGsView; }
  void setGsView(OdGsView *pView) { m_pGsView = pView; }

  OdDbViewportImpl();

protected:
  inline bool getPerspective() const { return GETBIT(m_StatusFlags, STATUS_PERSPECTIVE); }
  inline void setPerspective(bool value) { SETBIT(m_StatusFlags, STATUS_PERSPECTIVE, value); }
  inline bool getFrontClipAtEye() const { return !GETBIT(m_StatusFlags, STATUS_FRONTCLIPATEYE); }
  inline void setFrontClipAtEye(bool value) { SETBIT(m_StatusFlags, STATUS_FRONTCLIPATEYE, !value); }  
  inline bool getBackClip() const { return GETBIT(m_StatusFlags, STATUS_BACKCLIP); }
  inline void setBackClip(bool value) { SETBIT(m_StatusFlags, STATUS_BACKCLIP, value); }
  inline bool getFrontClip() const { return GETBIT(m_StatusFlags, STATUS_FRONTCLIP); }
  inline void setFrontClip(bool value) { SETBIT(m_StatusFlags, STATUS_FRONTCLIP, value); }
  inline bool getUcsFollow() const { return GETBIT(m_StatusFlags, STATUS_UCSFOLLOW); }
  inline void setUcsFollow(bool value) { SETBIT(m_StatusFlags, STATUS_UCSFOLLOW, value); }
  inline bool getUcsIcon() const { return GETBIT(m_StatusFlags, STATUS_UCSICON); }
  inline void setUcsIcon(bool value) { SETBIT(m_StatusFlags, STATUS_UCSICON, value); }
  inline bool isUcsAtOrigin() const { return GETBIT(m_StatusFlags, STATUS_UCSATORIGIN); }
  inline void setUcsAtOrigin(bool value) { SETBIT(m_StatusFlags, STATUS_UCSATORIGIN, value); }
  inline bool isFastZoom() const { return GETBIT(m_StatusFlags, STATUS_FASTZOOM); }
  inline void setFastZoom(bool value) { SETBIT(m_StatusFlags, STATUS_FASTZOOM, value); }
  inline bool isSnapOn() const { return GETBIT(m_StatusFlags, STATUS_SNAPON); }
  inline void setSnapOn(bool value) { SETBIT(m_StatusFlags, STATUS_SNAPON, value); }
  inline bool isGridOn() const { return GETBIT(m_StatusFlags, STATUS_GRIDON); }
  inline void setGridOn(bool value) { SETBIT(m_StatusFlags, STATUS_GRIDON, value); }
  inline bool isSnapStyleIso() const { return GETBIT(m_StatusFlags, STATUS_SNAPSTYLEISO); }
  inline void setSnapStyleIso(bool value) { SETBIT(m_StatusFlags, STATUS_SNAPSTYLEISO, value); }
  inline bool isHiddenInPlot() const { return GETBIT(m_StatusFlags, STATUS_HIDDENINPLOT); }
  inline void setHiddenInPlot(bool value) { SETBIT(m_StatusFlags, STATUS_HIDDENINPLOT, value); }
  inline bool isSnapIsoPairTop() const { return GETBIT(m_StatusFlags, STATUS_SNAPISOPAIRTOP); }
  inline void setSnapIsoPairTop(bool value) { SETBIT(m_StatusFlags, STATUS_SNAPISOPAIRTOP, value); }
  inline bool isSnapIsoPairRight() const { return GETBIT(m_StatusFlags, STATUS_SNAPISOPAIRRIGHT); }
  inline void setSnapIsoPairRight(bool value) { SETBIT(m_StatusFlags, STATUS_SNAPISOPAIRRIGHT, value);}
  inline bool getZoomLocking() const { return GETBIT(m_StatusFlags, STATUS_ZOOMLOCKING);}
  inline void setZoomLocking(bool value) { SETBIT(m_StatusFlags, STATUS_ZOOMLOCKING, value); }
  inline bool getAlways() const { return GETBIT(m_StatusFlags, STATUS_ALWAYS); }
  inline void setAlways(bool value) { SETBIT(m_StatusFlags, STATUS_ALWAYS, value); }
  inline bool isNonRectClip() const { return GETBIT(m_StatusFlags, STATUS_NONRECTCLIP); }
  inline void setNonRectClip(bool value) { SETBIT(m_StatusFlags, STATUS_NONRECTCLIP, value); }
  inline bool isOff() const { return GETBIT(m_StatusFlags, STATUS_OFF); }
  inline void setOff(bool value) { SETBIT(m_StatusFlags, STATUS_OFF, value); }

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion ver);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion ver);

  void audit(OdDbAuditInfo* pAuditInfo);

  friend class OdDbViewport;
  friend class OdDbLayoutImpl;
  friend void RemoveSection_NEWVIEWCONTROL(OdResBufPtr &pRb, OdDbViewport *pObj);

private:
  OdResBufPtr getAcadMviewXdata(bool treatLayerNameAsHandle) const;
  OdResBufPtr prepareXDataResBuf(bool bAcadMviewXdata, OdString regappName = OdString(),
                                 bool treatLayerNameAsHandle = false) const;
};

inline void OdDbViewportImpl::setVxTableRecordId(OdDbViewport* pVp, OdDbObjectId id)
{
  pVp->assertWriteEnabled();
  getImpl(pVp)->m_VXTableRecordId = id;
}

inline OdDbObjectId OdDbViewportImpl::vxTableRecordId(const OdDbViewport* pVp)
{
  pVp->assertReadEnabled();
  return getImpl(pVp)->m_VXTableRecordId;
}

inline bool OdDbViewportImpl::viewportIdLessFn(const OdDbViewport* pVp1, const OdDbViewport* pVp2)
{
  // #7674: 0 is interpreted as negative value in sorting, so -1 and 0 viewports will be after
  //        numerated. For example for this bug we have 1-0-0 flags and order should not be changed.
  //        Change: '- 1' added for negate 0 fields.
  return (OdUInt16(getImpl(pVp1)->m_dxf69 - 1) < OdUInt16(getImpl(pVp2)->m_dxf69 - 1));
}

inline bool OdDbViewportImpl::stackValLessFn(const OdDbViewport* pVp1, const OdDbViewport* pVp2)
{
  return (OdUInt16(getImpl(pVp1)->m_dxf68) < OdUInt16(getImpl(pVp2)->m_dxf68));
}

#endif // _ODDBVIEWPORTIMPL_INCLUDED_
