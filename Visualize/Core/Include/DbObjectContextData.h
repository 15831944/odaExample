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

#ifndef _DBOBJECTCONTEXTDATA_H_INCLUDED_
#define _DBOBJECTCONTEXTDATA_H_INCLUDED_

#include "DbObject.h"
#include "DbHatch.h"
#include "DbMText.h"

class OdTvDbObjectContext;

/** \details
    This class defines the set of object properties that represent an object in 
	some context.
  
    \remarks
    The context data varies depending on the current context, for example, the current 
	annotation scale. This class is intended for application developers only, 
	not for TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbObjectContextData : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbObjectContextData);
  OdTvDbObjectContextData();

  /*
  virtual OdResult dwgInContext(OdTvDbDwgFiler*,OdTvDbObjectContext* &);
  virtual void dwgOutContext(OdTvDbDwgFiler*) const;
*/
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  virtual const OdTvDbObjectContext* context() const;
  virtual bool matchesContext(const OdTvDbObjectContext&) const;
  virtual void setContext(const OdTvDbObjectContext&);
  virtual void setContextToNull();

  bool fileToExtensionDictionary() const;
  bool isDefaultContextData() const;
  bool isModified() const;
  void setFileToExtensionDictionary(bool);
  void setModified(bool);
  void setIsDefault(bool b);

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbObjectContextData> OdTvDbObjectContextDataPtr;

/** \details
    This class defines the set of object properties that represent an annotation scale.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbAnnotScaleObjectContextData : public OdTvDbObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbAnnotScaleObjectContextData);
  OdTvDbAnnotScaleObjectContextData();

  virtual const OdTvDbObjectContext* context() const;
  virtual void setContext(const OdTvDbObjectContext&);
  /*
  virtual OdResult dwgInContext(OdTvDbDwgFiler*,OdTvDbObjectContext*&);
  virtual OdResult dwgOutContext(OdTvDbDwgFiler*) const;
  virtual bool matchesContext(const OdTvDbObjectContext&) const;
  virtual void setContextToNull();
*/
  virtual OdResult getScale(double&) const;

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbAnnotScaleObjectContextData> OdTvDbAnnotScaleObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for an MText object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class OdTvDbMTextObjectContextData;
typedef OdSmartPtr<OdTvDbMTextObjectContextData> OdTvDbMTextObjectContextDataPtr;

/** <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbMTextObjectContextData : public OdTvDbAnnotScaleObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbMTextObjectContextData);
  OdTvDbMTextObjectContextData();
  /*
  bool zeroWidth(double tol = 1e-10) const;
  double rotation(const OdGeVector3d&) const;
*/
  OdGePoint3d location() const;
  OdGeVector3d direction() const;
  double actualHeight() const;
  double actualWidth() const;
  double definedHeight() const;
  double definedWidth() const;
  OdTvDbMText::AttachmentPoint attachment() const;
  OdDb::TextHorzMode horizontalMode() const;
  OdDb::TextVertMode verticalMode() const;

  OdTvDbMText::ColumnType  columnType() const;
  OdInt32 columnCount() const;
  double columnGutter() const;
  double columnHeight(OdInt32) const;
  double columnWidth() const;
  bool columnAutoHeight() const;
  bool columnFlowReversed() const;
  
  void setLocation(const OdGePoint3d&);
  void setDirection(const OdGeVector3d&);
  void setActualHeight(double);
  void setActualWidth(double);
  void setDefinedHeight(double);
  void setDefinedWidth(double);
  void setAttachment(OdTvDbMText::AttachmentPoint);
  //void setAttachmentMovingLocation(OdTvDbMText::AttachmentPoint, const OdGeVector3d&, double);
  void setHorizontalMode(OdDb::TextHorzMode);
  void setVerticalMode(OdDb::TextVertMode);
  
  void setColumnType(OdTvDbMText::ColumnType);
  void setColumnCount(OdInt32);
  void setColumnAutoHeight(bool);
  void setColumnFlowReversed(bool);
  void setColumnGutter(double);
  void setColumnHeight(OdInt32,double);
  void setColumnWidth(double);
/*  
  void  chgdirXattach();
  void  chgYattach();
  void  getCorners(OdGePoint3dArray&, const OdGeVector3d&, bool, double) const;
  void  setDirFromAngle(double, const OdGeVector3d&);
  void  xlateLocation(const OdGeVector3d&);
*/
  static OdTvDbMTextObjectContextDataPtr getMTextAnnoScaleDefaultContextData(const OdTvDbMText*);
  virtual void copyFrom(const OdRxObject* pSource);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

/** \details
    This class defines a set of annotation-specific properties for a Text object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbTextObjectContextData : public OdTvDbAnnotScaleObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbTextObjectContextData);
  OdTvDbTextObjectContextData();
  virtual OdGePoint2d alignmentPointInEcs() const;
  //virtual void audit(OdTvDbAuditInfo *,OdTvDbText *,OdInt32 &,bool &);
  virtual OdDb::TextHorzMode horizontalMode() const;
  virtual OdGePoint2d positionInEcs() const;
  virtual double rotation() const;
  virtual void setAlignmentPointInEcs(const OdGePoint2d&);
  virtual void setHorizontalMode(OdDb::TextHorzMode);
  virtual void setPositionInEcs(const OdGePoint2d&);
  virtual void setRotation(double);

  //static OdTvDbTextObjectContextData* getTextAnnoScaleDefaultContextData(const OdTvDbText*);

  virtual void copyFrom(const OdRxObject *);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbTextObjectContextData> OdTvDbTextObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for an MText Attribute object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbMTextAttributeObjectContextData : public OdTvDbTextObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbMTextAttributeObjectContextData);
  OdTvDbMTextAttributeObjectContextData();
  virtual void setContext(const OdTvDbObjectContext&) ODRX_OVERRIDE;
  virtual OdTvDbMTextObjectContextDataPtr getMTextObjectContextData() const;
  virtual void setMTextObjectContextData(OdTvDbMTextObjectContextData*);
  virtual void copyFrom(const OdRxObject *);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbMTextAttributeObjectContextData> OdTvDbMTextAttributeObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for a Block Reference object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbBlkRefObjectContextData : public OdTvDbAnnotScaleObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBlkRefObjectContextData);
  OdTvDbBlkRefObjectContextData();

  virtual OdGePoint3d positionInEcs() const;
  virtual double rotation() const;
  virtual OdGeScale3d  scaleFactors() const;
  virtual void setPositionInEcs(const OdGePoint3d&);
  virtual void setRotation(double);
  virtual void setScaleFactors(const OdGeScale3d&);
  //static OdTvDbBlkRefObjectContextData* getBlkAnnoScaleDefaultContextData(const OdTvDbBlockReference *);

  //virtual void audit(OdTvDbAuditInfo *,OdTvDbBlockReference *,OdInt32 &,bool &);
  virtual void copyFrom(const OdRxObject *);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbBlkRefObjectContextData> OdTvDbBlkRefObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for a Dimension object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbDimensionObjectContextData : public OdTvDbAnnotScaleObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbDimensionObjectContextData);
  OdTvDbDimensionObjectContextData();

  virtual OdTvDbObjectId blockIndex() const;
  virtual void setBlockIndex(OdTvDbObjectId);
  void setNDBRDimBlock(OdTvDbBlockTableRecord*);
  OdTvDbBlockTableRecordPtr getNDBRDimBlock()const;

  enum OverrideCode
  {
    eDimtofl  = 1,
    eDimsoxd   = 2,
    eDimatfit = 4,
    eDimtix   = 8,
    eDimtmove = 16
  };
  virtual bool  hasOverride(OverrideCode) const;
  virtual void setOverride(OverrideCode,bool);

  // dimvar overrides
  virtual OdInt16  dimatfit() const;
  virtual bool  dimsoxd() const;
  virtual bool  dimtix() const;
  virtual OdInt16  dimtmove() const;
  virtual bool  dimtofl() const;

  virtual void setDimatfit(OdInt16);
  virtual void setDimsoxd(bool);
  virtual void setDimtix(bool);
  virtual void setDimtmove(OdInt16);
  virtual void setDimtofl(bool);

  virtual bool  defTextLocation() const;
  virtual OdGePoint2d  textLocation() const;
  virtual double  textRotation() const;
  virtual bool  getArrowFirstIsFlipped() const;
  virtual bool  getArrowSecondIsFlipped() const;

  virtual void setDefTextLocation(bool);
  virtual void setTextLocation(const OdGePoint2d& /*,bool */);
  virtual void setTextRotation(double);
  virtual void  setArrowFirstIsFlipped(bool);
  virtual void  setArrowSecondIsFlipped(bool);
   
   //  virtual double calcZeroDimScale(OdTvDbDatabase *);
   //  OdResult createOrClearBlock(OdTvDbDatabase *);
   //  virtual void addEntity(OdTvDbEntity *);
   //   OdResult getEntityList(OdRxObjectPtrArray&, bool&) const;
   //   virtual OdGePoint3d  getFlipArrowPickPoint() const;
   //   bool  isBlockSpace(OdTvDbObjectId,OdTvDbDatabase *) const;
   //   virtual bool  isFlipArrow() const;
   //   virtual bool  isOwnDimBlock() const;
   //   virtual bool  recomputeDimBlock() const;
   //   void  releaseLayoutGeometry();
   //   virtual void  setFlipArrow(bool);
   //   virtual void  setFlipArrowPickPoint(OdGePoint3d &);
   //   virtual OdResult setOwnDimBlock(bool);
   //   virtual OdResult setRecomputeDimBlock(bool);
   //   void  setToBeRemoved(bool);
   //   OdResult stuffNewEntitiesInDatabase(bool,const OdGeMatrix3d&,wchar_t *);
   //  OdResult geomExtents(OdGeExtents3d&, const BlockRefData&) const;
   //  virtual OdRxObjectPtrArray const *  geometry() const;
//   bool  toBeRemoved() const;
//   OdResult updateContentsFromField(bool);
//   static OdTvDbDimensionObjectContextData * getDimensionAnnoScaleDefaultContextData(const OdTvDbDimension*);
//   static OdTvDbDimensionObjectContextData * getDimensionCurrentContextData(const OdTvDbDimension*);
//  
  virtual void copyFrom(const OdRxObject *);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  void transformBy(const OdGeMatrix3d &mx);
};

typedef OdSmartPtr<OdTvDbDimensionObjectContextData> OdTvDbDimensionObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for an Aligned Dimension object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbAlignedDimensionObjectContextData : public OdTvDbDimensionObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbAlignedDimensionObjectContextData);
  OdTvDbAlignedDimensionObjectContextData();

  OdGePoint3d dimLinePoint() const;
  void setDimLinePoint(const OdGePoint3d&);

  //static OdTvDbAlignedDimensionObjectContextData * getAlignedDimensionAnnoScaleDefaultContextData(const OdTvDbDimension*);

  virtual void copyFrom(const OdRxObject* pSource);

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbAlignedDimensionObjectContextData> OdTvDbAlignedDimensionObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for an Angular Dimension object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbAngularDimensionObjectContextData : public OdTvDbDimensionObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbAngularDimensionObjectContextData);
  OdTvDbAngularDimensionObjectContextData();

  OdGePoint3d arcPoint() const;
  void setArcPoint(const OdGePoint3d &);
  //OdResult update2Line(const OdGePoint3d *,const OdGePoint3d*,double,const OdGeVector3d&);
  //OdResult update3Point(const OdGePoint3d *,const OdGePoint3d*,double,const OdGeVector3d&);
  //OdResult updateArc(const OdGePoint3d *,const OdGePoint3d *,double,const OdGeVector3d&);

  //static OdTvDbAngularDimensionObjectContextData * getAngularDimensionAnnoScaleDefaultContextData(const OdTvDbDimension*);

  virtual void copyFrom(const OdRxObject* pSource);

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbAngularDimensionObjectContextData> OdTvDbAngularDimensionObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for a Diametric Dimension object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbDiametricDimensionObjectContextData : public OdTvDbDimensionObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbDiametricDimensionObjectContextData);
  OdTvDbDiametricDimensionObjectContextData();

  OdGePoint3d chordPoint() const;
  OdGePoint3d farChordPoint() const;
  void setChordPoint(const OdGePoint3d&);
  void setFarChordPoint(const OdGePoint3d&);

  //static OdTvDbDiametricDimensionObjectContextData* getDiametricDimensionAnnoScaleDefaultContextData(const OdTvDbDimension*);

  virtual void copyFrom(const OdRxObject* pSource);

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbDiametricDimensionObjectContextData> OdTvDbDiametricDimensionObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for an Ordinate Dimension object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbOrdinateDimensionObjectContextData : public OdTvDbDimensionObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbOrdinateDimensionObjectContextData);
  OdTvDbOrdinateDimensionObjectContextData();

  OdGePoint3d leaderEndPoint() const;
  OdGePoint3d origin() const;
  void setLeaderEndPoint(const OdGePoint3d&);
  void setOrigin(const OdGePoint3d&);

/*  static OdTvDbOrdinateDimensionObjectContextData * getOrdinateDimensionAnnoScaleDefaultContextData(const OdTvDbDimension*);
*/
  virtual void copyFrom(const OdRxObject* pSource);

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbOrdinateDimensionObjectContextData> OdTvDbOrdinateDimensionObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for a Radial Dimension object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbRadialDimensionObjectContextData : public OdTvDbDimensionObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbRadialDimensionObjectContextData);
  OdTvDbRadialDimensionObjectContextData();

  OdGePoint3d  chordPoint() const;
  void setChordPoint(const OdGePoint3d&);

  //static OdTvDbRadialDimensionObjectContextData * getRadialDimensionAnnoScaleDefaultContextData(const OdTvDbDimension*);

  virtual void copyFrom(const OdRxObject* pSource);

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbRadialDimensionObjectContextData> OdTvDbRadialDimensionObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for a Large Radial Dimension object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbRadialDimensionLargeObjectContextData : public OdTvDbRadialDimensionObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbRadialDimensionLargeObjectContextData);
  OdTvDbRadialDimensionLargeObjectContextData();

  OdGePoint3d jogPoint() const;
  OdGePoint3d overrideCenter() const;
  void setJogPoint(const OdGePoint3d&);
  void setOverrideCenter(const OdGePoint3d&);

  //static OdTvDbRadialDimensionLargeObjectContextData * getRadialDimensionLargeAnnoScaleDefaultContextData(const OdTvDbDimension*);

  virtual void copyFrom(const OdRxObject* pSource);

  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbRadialDimensionLargeObjectContextData> OdTvDbRadialDimensionLargeObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for a Feature Control Frame object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbFcfObjectContextData : public OdTvDbAnnotScaleObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbFcfObjectContextData);
  OdTvDbFcfObjectContextData();

  virtual OdGeVector3d horizontal() const;
  virtual OdGePoint3d location() const;
  virtual void setHorizontal(const OdGeVector3d&);
  virtual void setLocation(const OdGePoint3d&);

  //static OdTvDbFcfObjectContextData * getFcfAnnoScaleDefaultContextData(const OdTvDbFcf*);

  void transformBy(const OdGeMatrix3d&);
  virtual void copyFrom(OdRxObject const *);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbFcfObjectContextData> OdTvDbFcfObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for a Hatch Scale object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbHatchScaleContextData : public OdTvDbAnnotScaleObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbHatchScaleContextData);
  OdTvDbHatchScaleContextData();

//   virtual OdTvDbObjectContext *  context() const;
//   virtual OdResult  setContext(const OdTvDbObjectContext&);

  void appendLoop(OdInt32 loopType, const EdgeArray& edgePtrs);
  void getLoopAt(const OdTvDbHatch*, OdInt32 i, OdInt32 &loopType, EdgeArray& edgePtrs) const;
  void insertLoopAt(OdInt32 i, OdInt32 loopType, const EdgeArray& edgePtrs);
  OdInt32 loopTypeAt(OdInt32 i) const;
  OdInt32 numLoops() const;
  void removeLoopAt(OdInt32 i);
  void setLoopAt(OdInt32 i, OdInt32 loopType, const EdgeArray& edgePtrs);
  void setLoopTypeAt(OdInt32 i, OdInt32 loopType);
  void setNumLoops(OdInt32 i);

  const OdHatchPattern& hatchPattern() const;
  void  setHatchPattern(const OdHatchPattern&);
  OdGeVector3d patternBaseAngle( ) const;
  double  patternScale() const;
  void  setPatternBaseAngle(const OdGeVector3d&);
  void  setPatternScale(double);
//   void  setSupportsContext(OdTvDbHatch *);

//   void  transformBy(const OdGeMatrix3d&);
//   void  transformBy(OdInt32,const OdGeMatrix2d&,OdInt32);
//   void  transformBy(OdInt32,const OdGeMatrix3d&,const OdGeMatrix3d&,const OdGeMatrix3d&,OdGeVector3d,double);

//   OdResult  updateHatchBoundary(const OdTvDbHatch*,const OdArray<OdHatchBoundaryLoop>&);
//   void  verify(const OdArray<OdHatchBoundaryLoop>&) const;
  void getHatchLineDataAt( const OdTvDbHatch*, OdInt32 n, OdGePoint2d& startPt, OdGePoint2d& endPt) const;
  void getHatchLinesData( const OdTvDbHatch*, OdGePoint2dArray& startPts, OdGePoint2dArray& endPts) const;
  void setHatchLineDataAt( OdInt32 n, const OdGePoint2d& startPt, const OdGePoint2d& endPt);
  void setHatchLinesData( const OdGePoint2dArray& startPts, const OdGePoint2dArray& endPts);
  bool isValidHatchLines(const OdTvDbHatch*) const;
  void setEvaluateHatch(bool/*,bool*/);
  OdInt32 numHatchLines(const OdTvDbHatch*) const;
  void  transformBy(const OdGeMatrix2d&);

  virtual void copyFrom(OdRxObject const *);
  
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbHatchScaleContextData> OdTvDbHatchScaleContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for a Hatch View object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbHatchViewContextData : public OdTvDbHatchScaleContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbHatchViewContextData);
  OdTvDbHatchViewContextData();
/*
  OdResult appendHatchLine(const OdGePoint2d&,const OdGePoint2d&);
  OdResult compressHatch();
  virtual OdTvDbObjectContext * context() const;
  virtual OdResult dwgInContext(OdTvDbDwgFiler *,OdTvDbObjectContext * &);
  virtual OdResult dwgOutContext(OdTvDbDwgFiler *) const;
  OdResult freeUncompressedHatch();
  OdResult initCompression();
  virtual bool matchesContext(const OdTvDbObjectContext&) const;
  OdResult rotateHatchPattern(const OdTvDbHatch*,double);
  virtual OdResult setContext(const OdTvDbObjectContext&);
  OdResult setGrowLength(OdInt32);
  OdResult setLogicalLength(OdInt32);
  OdResult setPhysicalLength(OdInt32);
  OdResult traceHatchBoundary(const OdTvDbHatch*) const;
  bool viewChanged(const OdTvDbHatch*);
*/
  virtual void copyFrom(OdRxObject const *);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  OdTvDbObjectId viewportId() const;
  void setViewportId(OdTvDbObjectId id);
  OdGeVector3d viewTarget() const;
  void setViewTarget(const OdGeVector3d& v);
  double viewRotation() const;
  void setViewRotation(double a);
};

typedef OdSmartPtr<OdTvDbHatchViewContextData> OdTvDbHatchViewContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for a Leader object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbLeaderObjectContextData : public OdTvDbAnnotScaleObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbLeaderObjectContextData);
  OdTvDbLeaderObjectContextData();

  virtual bool addLast(const OdGePoint3d&);
  virtual OdGeVector3d annotationOffset() const;
  virtual OdGeVector3d blockInsertOffset() const;
  virtual void clearFurtherVertices();
  virtual OdResult endPoint(OdGePoint3d &) const;
  virtual const OdGePoint3dArray& furtherVertices() const;
  virtual OdGePoint3d getVertex(OdInt32) const;
  //virtual bool hasHookLine(const OdGePoint3d&) const;
  virtual bool hookLineDirSameAsHorizon() const;
  virtual OdGeVector3d horizontal() const;
  virtual OdInt32 numFurtherVertices() const;
  virtual void removeLastVertex();
  virtual OdResult setAnnotationOffset(const OdGeVector3d&);
  virtual OdResult setBlockInsertOffset(const OdGeVector3d&);
  virtual OdResult setFurtherVertices(const OdGePoint3dArray&);
  virtual OdResult setHookLineDirSameAsHorizon(bool);
  virtual OdResult setHorizontal(const OdGeVector3d&);
  virtual void setVertex(OdInt32,const OdGePoint3d&);
  //virtual OdResult transformBy(const OdGeMatrix3d&);

  //static OdTvDbLeaderObjectContextData * getLeaderAnnoScaleDefaultContextData(OdTvDbLeader const *);

  virtual void copyFrom(OdRxObject const *);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbLeaderObjectContextData> OdTvDbLeaderObjectContextDataPtr;

/** \details
    This class defines a set of annotation-specific properties for an MLeader object.
  
    \remarks
    This class is intended for application developers only, not TX developers.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbMLeaderObjectContextData : public OdTvDbAnnotScaleObjectContextData
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbMLeaderObjectContextData);
  OdTvDbMLeaderObjectContextData();

  //static OdTvDbMLeaderObjectContextData * getMLeaderAnnoScaleDefaultContextData(OdTvDbMLeader const *);
  //virtual OdResult updateContentScale(OdTvDbMLeaderObjectContextData* pData);

  virtual void copyFrom(OdRxObject const *);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdTvDbMLeaderObjectContextData> OdTvDbMLeaderObjectContextDataPtr;

#endif //_DBOBJECTCONTEXTDATA_H_INCLUDED_
