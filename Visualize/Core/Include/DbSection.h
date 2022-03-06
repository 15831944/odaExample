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


#ifndef _OdTvDbSection_h_Included_
#define _OdTvDbSection_h_Included_

#include "DbEntity.h"
#include "SmartPtr.h"
#include "DbHatch.h"
#include "TD_PackPush.h"
#include "ModelerGeometry.h"

class OdTvDbSectionSettings;
typedef OdSmartPtr<OdTvDbSectionSettings> OdTvDbSectionSettingsPtr;

class OdTvDbSection;
typedef OdSmartPtr<OdTvDbSection> OdTvDbSectionPtr;

/** \details

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbSection : public OdTvDbEntity
{
public:
  enum State
  {
    kPlane              = 0x01,
    kBoundary           = 0x02,
    kVolume             = 0x04
  };

  enum SubItem
  {
    kNone               = 0x00,
    kSectionLine        = 0x01,
    kSectionLineTop     = 0x02,
    kSectionLineBottom  = 0x04,
    kBackLine           = 0x08,
    kBackLineTop        = 0x10,
    kBackLineBottom     = 0x20,
    kVerticalLineTop    = 0x40,
    kVerticalLineBottom = 0x80
  };

  enum Height
  {
    kHeightAboveSectionLine = 0x1,
    kHeightBelowSectionLine = 0x2
  };

public:
  ODDB_DECLARE_MEMBERS(OdTvDbSection);

  OdTvDbSection();
  static OdTvDbSectionPtr createObject(const OdGePoint3dArray& pts,
    const OdGeVector3d& verticalDir);
  static OdTvDbSectionPtr createObject(const OdGePoint3dArray& pts,
    const OdGeVector3d& verticalDir, const OdGeVector3d& vecViewingDir);

  OdTvDbSection::State state() const;
  void setState(OdTvDbSection::State nState);

  const OdString getName() const;
  void getName(OdString& sName) const;
  void setName(const OdString& pszName);

  OdGeVector3d viewingDirection () const;
  OdResult setViewingDirection(const OdGeVector3d& dir);

  OdGeVector3d verticalDirection() const;
  OdResult setVerticalDirection(const OdGeVector3d& dir);

  OdGeVector3d normal() const;
  OdResult plane(OdGeVector3d& uAxis, OdGeVector3d& vAxis) const;

  int indicatorTransparency() const;
  void setIndicatorTransparency(int nTransparency);

  OdTvCmColor indicatorFillColor  () const;
  void setIndicatorFillColor(const OdTvCmColor& color);

  int numVertices() const;
  OdResult getVertex(int nIndex, 
    OdGePoint3d& pt) const;
  OdResult setVertex(int nIndex, 
    const OdGePoint3d& pt);
  OdResult addVertex(int nInsertAt, 
    const OdGePoint3d& pt);
  OdResult removeVertex(int nIndex);
  void  getVertices(OdGePoint3dArray& pts) const;
  OdResult setVertices(const OdGePoint3dArray& pts);

  double height(OdTvDbSection::Height nHeightType) const;
  OdResult setHeight(OdTvDbSection::Height nHeightType, double fHeight);

  //bool  hitTest(const OdGePoint3d& ptHit, int* pSegmentIndex, OdGePoint3d* ptOnSegment, OdTvDbSection::SubItem* pSubItem) const;
  OdResult createJog   (const OdGePoint3d& ptOnSection);
  bool hasJogs() const;

  OdTvDbObjectId getSettings() const;
  OdTvDbSectionSettingsPtr getSettings(OdDb::OpenMode mode) const;

  bool isLiveSectionEnabled() const;
  void enableLiveSection(bool bEnable);

  bool isSlice() const;
  OdResult setIsSlice( bool bIsSlice );

  double thicknesDepth() const;
  OdResult setThicknesDepth( double depth );

  double sectionPlaneOffset() const;
  OdResult setSectionPlaneOffset( double offset );

public:
  // Base class overrides
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;

  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

  //virtual OdResult subGetClassID(void* pClsid) const;
  
  virtual void subClose();
  
  virtual OdResult subTransformBy(const OdGeMatrix3d& xform);

  virtual OdResult subGetTransformedCopy(const OdGeMatrix3d& mat, OdTvDbEntityPtr& pCopy) const;

  //virtual OdResult subGetGeomExtents(OdGeExtents3d& extents) const;

  OdResult generateSectionGeometry (OdTvDbEntity*             pEnt,
                                    OdArray<OdTvDbEntityPtr>& intBoundaryEnts,
                                    OdArray<OdTvDbEntityPtr>& intFillEnts,
                                    OdArray<OdTvDbEntityPtr>& backgroundEnts,
                                    OdArray<OdTvDbEntityPtr>& foregroundEnts,
                                    OdArray<OdTvDbEntityPtr>& curveTangencyEnts) const;

  // INTERNAL USE ONLY
  OdResult generateSectionGeometry (OdTvDbEntity*             pEnt,
                                    OdArray<OdTvDbEntityPtr>& intBoundaryEnts,
                                    OdArray<OdTvDbEntityPtr>& intFillEnts,
                                    OdArray<OdTvDbEntityPtr>& backgroundEnts,
                                    OdArray<OdTvDbEntityPtr>& foregroundEnts,
                                    OdArray<OdTvDbEntityPtr>& curveTangencyEnts,
                                    bool                    bIsSetProperties) const;


  double topPlane() const;
  OdResult  setTopPlane(double);

  double bottomPlane() const;
  OdResult setBottomPlane(double);
  
  double elevation() const;
  OdResult setElevation( double);
};


//*************************************************************************
// OdTvDbSectionSettings
//*************************************************************************

/** \details

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbSectionSettings : public OdTvDbObject
{
public:
  enum SectionType
  {
    kLiveSection                = 0x1,
    k2dSection                  = 0x2,
    k3dSection                  = 0x4 
  };

  enum Geometry
  {
    kIntersectionBoundary       = 0x1,
    kIntersectionFill           = 0x2,
    kBackgroundGeometry         = 0x4,
    kForegroundGeometry         = 0x8,
    kCurveTangencyLines         = 0x10 
  };

  enum Generation
  {
    kSourceAllObjects           = 0x1,
    kSourceSelectedObjects      = 0x2,

    kDestinationNewBlock        = 0x10,
    kDestinationReplaceBlock    = 0x20,
    kDestinationFile            = 0x40
  };

public:
  ODDB_DECLARE_MEMBERS(OdTvDbSectionSettings);

  OdTvDbSectionSettings();

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  /*virtual OdResult subGetClassID(
    void* pClsid) const;*/

  void reset();
  void reset(OdTvDbSectionSettings::SectionType nSecType);

  OdTvDbSectionSettings::SectionType currentSectionType() const;
  void setCurrentSectionType(OdTvDbSectionSettings::SectionType nSecType);

  OdTvDbSectionSettings::Generation generationOptions(OdTvDbSectionSettings::SectionType nSecType) const;
  void setGenerationOptions(OdTvDbSectionSettings::SectionType nSecType,
    OdTvDbSectionSettings::Generation nOptions);

  void getSourceObjects(OdTvDbSectionSettings::SectionType nSecType,
    OdTvDbObjectIdArray& ids) const;
  void setSourceObjects(OdTvDbSectionSettings::SectionType nSecType,
    const OdTvDbObjectIdArray& ids);

  OdTvDbObjectId destinationBlock(OdTvDbSectionSettings::SectionType nSecType) const;
  void setDestinationBlock(OdTvDbSectionSettings::SectionType nSecType,
    const OdTvDbObjectId& id);

  const OdString destinationFile(OdTvDbSectionSettings::SectionType nSecType) const;
  void setDestinationFile(OdTvDbSectionSettings::SectionType nSecType,
    const OdString& pszFileName);

  bool  visibility(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setVisibility(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    bool bVisible);
  OdTvCmColor color(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setColor(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, const OdTvCmColor& color);
  OdString layer(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setLayer(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    const OdString& pszLayer);
  OdString linetype(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setLinetype (OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    const OdString& pszLinetype);
  double linetypeScale(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setLinetypeScale(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    double fScale);
  OdString plotStyleName(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setPlotStyleName(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    const OdString& pszPlotStyleName);
  OdDb::LineWeight lineWeight(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setLineWeight(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    OdDb::LineWeight nLineWeight);
  int   faceTransparency(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setFaceTransparency(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    int nTransparency);
  int   edgeTransparency(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setEdgeTransparency(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    int nTransparency);
  bool  hatchVisibility(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setHatchVisibility(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    bool bVisible);
  void getHatchPattern(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    OdTvDbHatch::HatchPatternType& nPatternType, 
    OdString& pszPatternName) const;
  void setHatchPattern(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    OdTvDbHatch::HatchPatternType nPatternType, 
    const OdString& pszPatternName);
  double hatchAngle(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setHatchAngle(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    double fAngle);
  double hatchSpacing(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setHatchSpacing(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    double fSpacing);
  double hatchScale(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setHatchScale(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    double fScale);
  bool  hiddenLine(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setHiddenLine(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    bool bHiddenLine);
  bool  divisionLines(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry) const;
  void setDivisionLines(OdTvDbSectionSettings::SectionType nSecType, 
    OdTvDbSectionSettings::Geometry nGeometry, 
    bool bShow);
};


#include "TD_PackPop.h"

#endif //_OdTvDbSection_h_Included_
