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

#ifndef _ODDBDIMENSIONIMPL_INCLUDED_
#define _ODDBDIMENSIONIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DimStyleRef.h"
#include "DbDimension.h"
#include "DbSystemInternals.h"
#include "Ge/GePoint2dArray.h"
#include "Ge/GeScale3d.h"
#include "DbObjectContextData.h"
#include "DbObjectContextDataManager.h"
#include "DbDimStyleTableRecord.h"

class OdTvDbDimensionImpl : public DimStyleRef<OdTvDbEntityImpl>
{
  static OdTvDbDimensionImpl* getImpl(const OdTvDbDimension *pObj)
  { return (OdTvDbDimensionImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdTvDbHardPointerId m_BlockRecordId;
  OdGePoint3d       m_DimLineDefPt;
  // OdGePoint3d       m_DimTextMidPt;
  OdGePoint2d       m_DimCloneInsPt;    // OCS as in DWG file
  OdString          m_strDimText;
  double            m_dUcsXAngle;
  double            m_dTextRot;
  OdGeVector3d      m_vNormal;
  const OdGeVector3d& normal() const {return m_vNormal;}
  OdGeScale3d       m_overallScale;
  double            m_dOverallRotation;
  double            m_dMeasurement;
  OdInt32           m_LinespacingStyle;
  double            m_dLinespacingFactor;
  OdInt32           m_AttachPt;
  double            m_dOblique;  // GC 52 expected in dimension section by R15 and R18

  bool              m_bUserDefinedTextPosition; //UserTextPos
  bool              m_bSingleReferencedBlock;   //SingleReference
  bool              m_bDynamicDimension;
  bool              m_bXOrd;

  bool              m_bFlipArrow1;
  bool              m_bFlipArrow2;
  bool              m_bShouldParticipateInOPM;  // run-time value

  double            m_dTextWidth;
  double            m_dTextHeight;
  OdGePoint3d       m_ocsDimTextMidPt; // OCS - z coord is elevation
  OdTvDbBlockTableRecordPtr m_pNDBRBlock;

  OdUInt8           m_version;

  virtual void copyFromContextData(OdTvDbObject *pObj,OdTvDbObjectContextData*,OdTvDbObjectContextData*);
  virtual OdGePoint3d getDimLineDefPt(OdTvDbObjectContextData* ctx) { return OdGePoint3d::kOrigin; }
  virtual void setDimLineDefPt(OdTvDbObjectContextData* ctx, OdGePoint3d point) {};

  double elevation() const  {return m_ocsDimTextMidPt.z;}

  enum DimType
  {
    DimRotated = 0,    //0
    DimAligned,        //1
    Dim2LineAngular,   //2
    DimDiametric,      //3
    DimRadial,         //4
    Dim3PointAngular,  //5
    DimOrdinate,       //6
    DimUnknown,        //7
    DimArcLen,         //8
    DimRadialLarge     //9
  };

  virtual OdUInt8 getDimTypeFlag() { ODA_ASSERT(0); return 0; }

  OdTvDbDimensionImpl();

  friend class OdTvDbDimension;
  friend class OdTvDwgR12FileLoader;

  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void getRtBgrndTxtColor(OdTvDbObject *pObj);
  void setRtBgrndTxtColor(OdTvDbObject *pObj);

  void getRtExtLineFixLenEnable(OdTvDbObject *pObj);
  void setRtExtLineFixLenEnable(OdTvDbObject *pObj);

  void getRtExtLineFixLen(OdTvDbObject *pObj);
  void setRtExtLineFixLen(OdTvDbObject *pObj);

  void getRtDimLinetype(OdTvDbObject *pObj);
  void setRtDimLinetype(OdTvDbObject *pObj);

  void getRtDimExt1Linetype(OdTvDbObject *pObj);
  void setRtDimExt1Linetype(OdTvDbObject *pObj);

  void getRtDimExt2Linetype(OdTvDbObject *pObj);
  void setRtDimExt2Linetype(OdTvDbObject *pObj);

  void getRtFlipArrow(OdTvDbObject *pObj);
  void setRtFlipArrow(OdTvDbObject *pObj);

  void getRtArcSymbolType(OdTvDbObject *pObj);
  void setRtArcSymbolType(OdTvDbObject *pObj);

  void getRtJogAngle(OdTvDbObject *pObj);
  void setRtJogAngle(OdTvDbObject *pObj);

  void audit (OdTvDbAuditInfo* pAuditInfo);

  /** Transforms common dimension data by the specified matrix.
  */
  virtual OdResult transformBy(const OdGeMatrix3d& xform, bool b2Copy);

  virtual void setElevation(double elevation, const OdGeMatrix3d& world2Plane, const OdGeMatrix3d& plane2World);
  void recomputeElevation(OdGePoint3d& pt, double elevation, const OdGeMatrix3d& world2Plane, const OdGeMatrix3d& plane2World);

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }

  OdAnsiString getAnsiText() const;
  void correctTextCoding();

  static bool jogSymbolOn(const OdTvDbDimension* pDim);
  // the point is used if there were no jog on dimension
  static void setJogSymbolOn(OdTvDbDimension* pDim, bool value, const OdGePoint3d& p);
  static OdGePoint3d jogSymbolPosition(const OdTvDbDimension* pDim);
  static void setJogSymbolPosition(OdTvDbDimension* pDim, const OdGePoint3d& pt);
  static bool extArcOn(const OdTvDbDimension* pDim);
  static void setExtArcOn(OdTvDbDimension* pDim, bool val);
  static double extArcStartAngle(const OdTvDbDimension* pDim);
  static void setExtArcStartAngle(OdTvDbDimension* pDim, double newAngle);
  static double extArcEndAngle(const OdTvDbDimension* pDim);
  static void setExtArcEndAngle(OdTvDbDimension* pDim, double newAngle);
  static bool extArcOnRadial(const OdTvDbDimension* pDim);
  static bool jogSymbolUserDefPos(const OdTvDbDimension* pDim);
  static void setJogSymbolUserDefPos(OdTvDbDimension* pDim, bool value);
  static double jogSymbolHeight(const OdTvDbObject* pObj);
  static void setJogSymbolHeight(OdTvDbObject* pObj, double value);

  static void setDimTALN(OdTvDbDimension *pDim, bool val);
  static bool getDimTALN(const OdTvDbDimension *pDim);

  void recomputeDimBlock(OdTvDbDimension* dim, bool forceUpdate);

  static void checkRecomputeDimBlock(OdTvDbHostAppServices* appServices);

  virtual void copyXDataDuringExplode(OdTvDbEntity* pEnt, OdTvResBuf* xd) {}
};

inline void OdTvDbDimensionImpl::checkRecomputeDimBlock(OdTvDbHostAppServices* appServices) {
  if (OdTvDbDimStyleTableRecord::desc() && appServices->getRecomputeDimBlocksRequired()) {
    // Try to load RecomputeDimBlock application
    // and throw exception if it is missed.
      ::odrxDynamicLinker()->loadApp(OdRecomputeDimBlockModuleName, false);
  }
}


#endif // _ODDBDIMENSIONIMPL_INCLUDED_
