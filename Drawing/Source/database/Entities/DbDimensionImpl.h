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

class OdDbDimensionImpl : public DimStyleRef<OdDbEntityImpl>
{
  static OdDbDimensionImpl* getImpl(const OdDbDimension *pObj)
  { return (OdDbDimensionImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdDbHardPointerId m_BlockRecordId;
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
  OdDbBlockTableRecordPtr m_pNDBRBlock;

  OdUInt8           m_version;

  virtual void copyFromContextData(OdDbObject *pObj,OdDbObjectContextData*,OdDbObjectContextData*);
  virtual OdGePoint3d getDimLineDefPt(OdDbObjectContextData* ctx) { return OdGePoint3d::kOrigin; }
  virtual void setDimLineDefPt(OdDbObjectContextData* ctx, OdGePoint3d point) {};

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

  OdDbDimensionImpl();

  friend class OdDbDimension;
  friend class OdDwgR12FileLoader;

  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void getRtBgrndTxtColor(OdDbObject *pObj);
  void setRtBgrndTxtColor(OdDbObject *pObj);

  void getRtExtLineFixLenEnable(OdDbObject *pObj);
  void setRtExtLineFixLenEnable(OdDbObject *pObj);

  void getRtExtLineFixLen(OdDbObject *pObj);
  void setRtExtLineFixLen(OdDbObject *pObj);

  void getRtDimLinetype(OdDbObject *pObj);
  void setRtDimLinetype(OdDbObject *pObj);

  void getRtDimExt1Linetype(OdDbObject *pObj);
  void setRtDimExt1Linetype(OdDbObject *pObj);

  void getRtDimExt2Linetype(OdDbObject *pObj);
  void setRtDimExt2Linetype(OdDbObject *pObj);

  void getRtFlipArrow(OdDbObject *pObj);
  void setRtFlipArrow(OdDbObject *pObj);

  void getRtArcSymbolType(OdDbObject *pObj);
  void setRtArcSymbolType(OdDbObject *pObj);

  void getRtJogAngle(OdDbObject *pObj);
  void setRtJogAngle(OdDbObject *pObj);

  void audit (OdDbAuditInfo* pAuditInfo);

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

  static bool jogSymbolOn(const OdDbDimension* pDim);
  // the point is used if there were no jog on dimension
  static void setJogSymbolOn(OdDbDimension* pDim, bool value, const OdGePoint3d& p);
  static OdGePoint3d jogSymbolPosition(const OdDbDimension* pDim);
  static void setJogSymbolPosition(OdDbDimension* pDim, const OdGePoint3d& pt);
  static bool extArcOn(const OdDbDimension* pDim);
  static void setExtArcOn(OdDbDimension* pDim, bool val);
  static double extArcStartAngle(const OdDbDimension* pDim);
  static void setExtArcStartAngle(OdDbDimension* pDim, double newAngle);
  static double extArcEndAngle(const OdDbDimension* pDim);
  static void setExtArcEndAngle(OdDbDimension* pDim, double newAngle);
  static bool extArcOnRadial(const OdDbDimension* pDim);
  static bool jogSymbolUserDefPos(const OdDbDimension* pDim);
  static void setJogSymbolUserDefPos(OdDbDimension* pDim, bool value);
  static double jogSymbolHeight(const OdDbObject* pObj);
  static void setJogSymbolHeight(OdDbObject* pObj, double value);

  static void setDimTALN(OdDbDimension *pDim, bool val);
  static bool getDimTALN(const OdDbDimension *pDim);

  void recomputeDimBlock(OdDbDimension* dim, bool forceUpdate);

  static void checkRecomputeDimBlock(OdDbHostAppServices* appServices);

  virtual void copyXDataDuringExplode(OdDbEntity* pEnt, OdResBuf* xd) {}
};

inline void OdDbDimensionImpl::checkRecomputeDimBlock(OdDbHostAppServices* appServices) {
  if (OdDbDimStyleTableRecord::desc() && appServices->getRecomputeDimBlocksRequired()) {
    // Try to load RecomputeDimBlock application
    // and throw exception if it is missed.
      ::odrxDynamicLinker()->loadApp(OdRecomputeDimBlockModuleName, false);
  }
}


#endif // _ODDBDIMENSIONIMPL_INCLUDED_
