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


#ifndef _ODTV_ENTITYTYPIFIEDGEOMETRYDATAMISC_H_INCLUDED_
#define _ODTV_ENTITYTYPIFIEDGEOMETRYDATAMISC_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvGeometryDataImpl.h"
#include "TvGeometryTypifiedDataMisc.h"
#include "TvAttributeResolverImpl.h"

#include "Gi/GiTextStyle.h"
#include "GiCommonDraw.h"

/** \details
    This class implements the line defined by two points   
*/
class OdTvTextDataImpl : public OdTvGeometryDataImpl
{
  friend class OdTvEntityImpl;

public:

  /** \details
  Enum for the text flags
  */
  enum textFlags
  {
    kIsNonRotatable                = 1 << 16,  // true if text is non rotatable
    kNeedAdjustAlignment           = 1 << 17,  // indicate that something was changed and it is need to perform adjust alignment
    kNoMirror                      = 1 << 18,  // No mirror.
    kMirroredInX                   = 1 << 19,  // Mirrored around the X-axis.
    kMirroredInY                   = 1 << 20,  // Mirrored around the Y-axis.
    kMirroredInXAndY               = 1 << 21,  // Mirrored around both the X-axis and Y-axis.
    kNoStroke                      = 1 << 22,  // no stroke
    kUnderlinedOn                  = 1 << 23,  // Underlined on
    kUnderlinedOff                 = 1 << 24,  // Underlined off
    kOverlinedOn                   = 1 << 25,  // Overlined on
    kOverlinedOff                  = 1 << 26,  // Overlined off
    kStrikedOn                     = 1 << 27,  // Striked on
    kStrikedOff                    = 1 << 28   // Striked off
  };

  OdTvTextDataImpl(const OdTvPoint& alignPoint, const OdString& msg, OdDbStub* textStyle);
  virtual ~OdTvTextDataImpl();

  // own
  //WCS
  OdTvPoint position(bool bFromInterface = false, const OdTvEntityImpl* pParentEntity = NULL);
  void       setPosition(const OdTvPoint& position, bool bFromInterface = false);
  
  //WCS
  OdTvPoint alignmentPoint(bool bFromInterface = false, const OdTvEntityImpl* pParentEntity = NULL);
  void setAlignmentPoint(const OdTvPoint& alignment, bool bFromInterface = false);
    
  //WCS normal to the plane of this entity
  OdTvVector normal() const;
  void setNormal(const OdTvVector& normal);
 
  double thickness() const;
  void setThickness(double thickness);

  // radians
  double rotation(bool bFromInterface = false, const OdTvEntityImpl* pParentEntity = NULL);
  void setRotation(double rotation, bool bFromInterface = false);

  OdString textString() const;
  void setTextString(const OdString& textString);

  //text height
  double height() const;
  void setHeight(double height, bool bFromInterface = false);

  //Width factor of this Text entity
  double widthFactor() const;
  void setWidthFactor(double widthFactor, bool bFromInterface = false);

  // set/get the mirrored type
  OdTvTextStyle::MirrorType mirroredType() const;
  void setMirroredType(OdTvTextStyle::MirrorType mirroredType);
   
  // set/get alignment mode
  OdTvTextStyle::AlignmentType alignmentMode() const;
  void setAlignmentMode(OdTvTextStyle::AlignmentType alignMode, bool bFromParent = false);

  // set/get text style
  OdTvTextStyleDef getTextStyle(const OdTvEntityImpl* pParentEntity) const;
  void setTextStyle(const OdTvTextStyleDef& textStyle, const OdTvEntityImpl* pParentEntity);
    
  // set/get non rotatable property
  bool getNonRotatable(OdTvResult* rc = NULL) const;
  void setNonRotatable(bool bNonRotatable);

  // set/get underlined
  void setUnderlined(OdTvTextData::StrokeState underlined);
  OdTvTextData::StrokeState getUnderlined() const;

  // set/get overlined
  void setOverlined(OdTvTextData::StrokeState underlined);
  OdTvTextData::StrokeState getOverlined() const;

  // set/get striked
  void setStriked(OdTvTextData::StrokeState underlined);
  OdTvTextData::StrokeState getStriked() const;

  // get bounding points
  virtual OdTvResult getBoundingPoints(OdTvPointArray& array, OdTvDbDatabase* pDb) const;

  /** \details
  Returns true if and only if text is drawn overlined with this TextStyle.
  */


  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                    entityGeometryDataType() const{return Text; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawView(OdGiViewportDraw* pViewportDraw, const OdTvEntityImpl* pParentEntity) const;
  virtual OdTvGeometryData::GeometryTypes   getFirstColorGeomType() const { return OdTvGeometryData::kText; }
  virtual void                              beforeDraw(const OdTvEntityImpl* pParentEntity);
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion() );
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                              copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;
  virtual bool                              copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity, OdTvAttributeResolverImpl* pResolver) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:
  // empty constructor (can use only inside dwgInFields of 'OdTvEntityImpl'
  OdTvTextDataImpl();
  
  // implementation for the drawView (non const)
  void drawViewInternal(OdGiViewportDraw* pViewportDraw, const OdTvEntityImpl* pParentEntity);

  // Draw common text
  void commonDraw(OdGiCommonDraw* pCommonDraw, const OdTvEntityImpl* pParentEntity, OdGiGeometry* pGeometry) const;

  // Adjusts the position of this Text entity for the current alignment   
  bool adjustAlignment(const OdTvEntityImpl* pParentEntity);

  void getRawExts(OdGePoint3d& min, OdGePoint3d& max, double& actHeight, double& actWidth, OdTvDbDatabase* pDb) const;

  void copyToInternal(OdTvTextDataImpl* pTargetTextData) const;

private:
  OdString                         m_strText;                   // string
  OdTvVector                       m_vNormal;                   // normal vector of the text
  OdGePoint2d                      m_position;                  // position (in the text plane)
  OdGePoint2d                      m_alignmentPoint;            // alignment point (in the text plane)
  double                           m_d_Elevation;               // elevation of the text over the text plane
  double                           m_dAngle;                    // rotation angle of the direction vector over the normal
  double                           m_dHeight;                   // text height factor
  double                           m_dWidth;                    // text width factor
  double                           m_dAlignedHeight;            // text height factor after aligning
  double                           m_dAlignedWidth;             // text width factor after aligning
  double                           m_dThickness;                // thickness
  OdTvDbSoftPointerId              m_textStyleId;               // text style
  OdUInt32                         m_cntStyleChanges;           // counter for the text style changes
  OdTvTextStyle::AlignmentType     m_alignmentMode;             // alignment mode
};

typedef OdTvSmartPtrInternal<OdTvTextDataImpl> OdTvTextDataImplPtr;



/** \details
    This is an wrapper of the interface class for OdTvTextData object.

    \remarks
    The purpose of this class is to connect the internal entity object with an interface object
*/ 
class OdTvTextDataWrapper : public OdTvTextData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvTextData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
    Returns the position of this text (WCS). The result can be not equal to last setPosition due to alignment
  */
  virtual OdTvPoint getPosition(OdTvResult* rc = NULL) const;
  
  /** \details
    Sets the position of this text (WCS).
  */
  virtual OdTvResult setPosition(const OdTvPoint& position);

  /** \details
    Returns the alignment point of this text (WCS);
  */
  virtual OdTvPoint getAlignmentPoint(OdTvResult* rc = NULL) const;
  
  /** \details
    Sets the alignment point of this text (WCS).
  */
  virtual OdTvResult setAlignmentPoint(const OdTvPoint& alignment);

  /** \details
  Returns the normal vector of this text
  */
  virtual OdTvVector getNormal(OdTvResult* rc = NULL) const;

  /** \details
  Set the normal vector for this text
  */
  virtual OdTvResult setNormal(const OdTvVector& normal);

  /** \details
  Returns the rotation angle of this text
  */
  virtual double getRotation(OdTvResult* rc = NULL) const;

  /** \details
  Set the rotation angle for this text
  */
  virtual OdTvResult setRotation(double rotation);

  /** \details
  Returns the string of this text
  */
  virtual OdString getString (OdTvResult* rc = NULL) const;

  /** \details
  Set the string for this text
  */
  virtual OdTvResult setString (const OdString& msg);

  /** \details
  Returns the alignment mode
  */
  virtual OdTvTextStyle::AlignmentType getAlignmentMode(OdTvResult* rc = NULL) const;

  /** \details
  Set the alignment mode
  */
  virtual OdTvResult setAlignmentMode(OdTvTextStyle::AlignmentType alignMode);

  /** \details
  Set the text style for all text inside entity
  */
  virtual OdTvResult setTextStyle(const OdTvTextStyleDef& textStyle);

  /** \details
  Returns the text style of all text inside entity
  */
  virtual OdTvTextStyleDef getTextStyle(OdTvResult* rc = NULL) const;

  /** \details
  Returns the height scale factor of the text boundary. This factor influences on the width
  and height together and is used for proportional scaling of letters, spaces, and the text boundary.
  */
  virtual double getTextSize(OdTvResult* rc = NULL) const;

  /** \details
  Sets the text size which is the height scale factor of the text boundary. This factor
  influences on the text width and text height together and is used for proportional scaling of
  letters, spaces, and the text boundary. A value less than 1.0 decreases the text. A value
  greater than 1.0 increases the text. The initial value is 0.0 by default, which means that will be used the
  text size from the text style

  \param vSize [in]  Text size as a positive Double value.
  */
  virtual OdTvResult setTextSize(double dSize);

  /** \details
  Returns the width scale factor of the text boundary. This factor influences only on the
  width and is used for scaling of letters and spaces when the height is constant.
  */
  virtual double getWidthFactor(OdTvResult* rc = NULL) const;

  /** \details
  Sets the width scale factor of the text boundary. This factor influences only on the
  text width and is used for scaling of letters and spaces when the height is constant. A value
  less than 1.0 condenses the text. A value greater than 1.0 expands the text. The initial value
  is 0.0 by default, which means that will be used the
  width factor from the text style

  \param widthFactor [in]  width factor as a positive Double value.
  */
  virtual OdTvResult setWidthFactor(double widthFactor);

  /** \details
  Returns true if non rotatable
  */
  virtual bool getNonRotatable(OdTvResult* rc = NULL) const;

  /** \details
  Set non rotatable property for all text inside entity
  */
  virtual OdTvResult setNonRotatable(bool bNonRotatable);

  /** \details
  Controls the underlined drawing of text.

  \param underlined [in]  Controls underlined drawing.
  */
  virtual OdTvResult setUnderlined(StrokeState underlined);

  /** \details
  Returns the state of the underlined drawing of the text.
  */
  virtual StrokeState getUnderlined(OdTvResult* rc = NULL) const;

  /** \details
  Controls the overlined drawing of text.

  \param overlined [in]  Controls overlined drawing.
  */
  virtual OdTvResult setOverlined(StrokeState overlined);

  /** \details
  Returns the state of the overlined drawing of the text.
  */
  virtual StrokeState getOverlined(OdTvResult* rc = NULL) const;

  /** \details
  Controls the striked drawing of text.

  \param striked [in]  Controls striked drawing.
  */
  virtual OdTvResult setStriked(StrokeState striked);

  /** \details
  Returns the state of the striked drawing of the text.
  */
  virtual StrokeState getStriked(OdTvResult* rc = NULL) const;

  /** \details
  Return array with bounding points.

  \param array [in]
  Top left is array[0]
  Top right is array[1]
  Bottom left is array[2]
  Bottom right is array[3]
  */
  virtual OdTvResult getBoundingPoints(OdTvPointArray& array) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the line defined by two points
*/
class OdTvInsertDataImpl : public OdTvGeometryDataImpl
{
public:

  OdTvInsertDataImpl()
    : OdTvGeometryDataImpl()
  {}
  virtual ~OdTvInsertDataImpl();

  /* own methods */
  OdTvBlockId getBlock(OdTvResult* rc = NULL) const;
  OdTvResult setBlock(const OdTvBlockId& blockId, const OdTvDbObjectId& wnerId);

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                   entityGeometryDataType() const { return Insert; }
  virtual bool                             draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                             drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes  getFirstColorGeomType() const { return OdTvGeometryData::kAll; }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity, OdTvAttributeResolverImpl* pResolver) const;

  virtual OdTvResult setColor(const OdTvColorDef& color, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll);
  virtual OdTvColorDef getColor(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll);
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw);
  virtual OdTvLineWeightDef getLineWeight();
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& lt, OdTvDbDatabase* pDb = NULL);
  virtual OdTvLinetypeDef getLinetype(OdTvDbDatabase* pDb);
  virtual OdTvResult setLinetypeScale(double linetypeScale);
  virtual double getLinetypeScale();
  virtual OdTvResult setLayer(const OdTvLayerDef& l, OdTvDbDatabase* pDb = NULL);
  virtual OdTvLayerDef getLayer(OdTvDbDatabase* pDb);
  virtual OdTvResult setVisibility(const OdTvVisibilityDef& visible);
  virtual OdTvVisibilityDef getVisibility() const;

  virtual void setSelectability(const OdTvSelectabilityDef& selectability);

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

private:
  OdTvDbObjectId m_InsertId;
};

typedef OdTvSmartPtrInternal<OdTvInsertDataImpl> OdTvInsertDataImplPtr;

/** \details
This is an wrapper of the interface class for OdTvInsertData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvInsertDataWrapper : public OdTvInsertData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvInsertData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Returns the ID of the block associated with this Insert.
  */
  virtual OdTvBlockId getBlock(OdTvResult* rc = NULL) const;

  /** \details
  Sets the ID of the block associated with this Insert.

  \param blockId [in]  Object ID of the block.
  */
  virtual OdTvResult setBlock(const OdTvBlockId& blockId);

};


//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the subentity data implementation

\remarks For this class it is not need to write the wrapper since it is supposed 
 that we will return the OdTvEntityPtr for OdTvGeometryId in this case
*/
class OdTvSubEntityDataImpl : public OdTvGeometryDataImpl
{
public:

  OdTvSubEntityDataImpl()
    : OdTvGeometryDataImpl(),
    m_pLastMarker(NULL)
  {}
  virtual ~OdTvSubEntityDataImpl();

  /* own methods */
  OdTvDbObjectId getEntity();
  void setEntity(OdTvDbObjectId entityId);

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                   entityGeometryDataType() const { return SubEntity; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                             drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes  getFirstColorGeomType() const { return OdTvGeometryData::kAll; }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  virtual OdTvResult setColor(const OdTvColorDef& color, OdUInt16 geomType = (OdUInt16)OdTvGeometryData::kAll);
  virtual OdTvColorDef getColor(OdTvGeometryData::GeometryTypes geomType = OdTvGeometryData::kAll);
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw);
  virtual OdTvLineWeightDef getLineWeight();
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& lt, OdTvDbDatabase* pDb = NULL);
  virtual OdTvLinetypeDef getLinetype(OdTvDbDatabase* pDb);
  virtual OdTvResult setLinetypeScale(double linetypeScale);
  virtual double getLinetypeScale();
  virtual OdTvResult setLayer(const OdTvLayerDef& l, OdTvDbDatabase* pDb = NULL);
  virtual OdTvLayerDef getLayer(OdTvDbDatabase* pDb);
  virtual OdTvResult setVisibility(const OdTvVisibilityDef& visible);
  virtual OdTvVisibilityDef getVisibility() const;

  virtual OdTvResult rotate(double x, double y, double z);
  virtual OdTvResult rotateAxis(const OdTvVector& aVector, double ang, const OdTvPoint& center = OdTvPoint::kOrigin);
  virtual OdTvResult translate(double x, double y, double z);
  virtual OdTvResult translate(const OdTvVector& aVector);
  virtual OdTvResult scale(double x, double y, double z);
  virtual OdTvResult setModelingMatrix(const OdTvMatrix& matrix);
  virtual OdTvMatrix getModelingMatrix() const;
  virtual OdTvResult appendModelingMatrix(const OdTvMatrix& matrix);

  virtual void setSelectability(const OdTvSelectabilityDef& selectability);

  virtual OdGsMarker* getLastMarker() const { return m_pLastMarker; };

  virtual void getMarkers(std::set< OdGsMarker >& markers, std::set< OdGsMarker >* pCompareMarkers = NULL) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual void            setParentEntityId(OdTvDbObjectId dbId);

private:
  OdTvDbObjectId m_EntityId;

  // Pointer to last marker
  OdGsMarker* m_pLastMarker;
};

typedef OdTvSmartPtrInternal<OdTvSubEntityDataImpl> OdTvSubEntityDataImplPtr;

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the raster image geometry data
*/
class OdTvRasterImageDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the raster image flags
  */
  enum rasterImageFlags
  {
    kIsClipInverted      = 1 << 16,
    kClipping            = 1 << 17,
    kWasAddedAsReference = 1 << 18
  };

  /** \details
  Structure for store the clipping parameters
  */
  struct ClippingData
  {
    OdTvPoint2dArray    m_ClipPoints;
    OdTvPoint2dArray    m_ClipPointsCache;
  };

  OdTvRasterImageDataImpl();
  OdTvRasterImageDataImpl(OdTvRasterImageId imageId, const OdTvPoint& origin, const OdTvVector& u, const OdTvVector& v);
  virtual ~OdTvRasterImageDataImpl();

  OdTvResult setImageId(OdTvRasterImageId imageId);
  OdTvRasterImageId getImageId() const;

  OdTvResult setOrientation(const OdTvPoint& origin, const OdTvVector& u, const OdTvVector& v);
  OdTvResult getOrientation(OdTvPoint& origin, OdTvVector& u, OdTvVector& v) const;

  OdTvResult setClipBoundary(const OdTvPoint2dArray& clipPoints);
  OdTvResult getClipBoundary(OdTvPoint2dArray& clipPoints) const;

  bool getClipped() const;

  OdTvResult setClipInverted(bool val);
  bool getClipInverted() const;

  OdTvResult setBrightness(OdInt8 brightness);
  OdInt8 getBrightness() const;

  OdTvResult setContrast(OdInt8 contrast);
  OdInt8 getContrast() const;

  OdTvResult setFade(OdInt8 fade);
  OdInt8 getFade() const;

  OdTvVector2d getImageSize(OdTvResult* rc = NULL) const;

  OdTvResult setMonochromeBackgroundColor(const OdTvColorDef& backgroundColor);
  OdTvColorDef getMonochromeBackgroundColor(OdTvResult* rc = NULL) const;

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                    entityGeometryDataType() const { return RasterImage; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawView(OdGiViewportDraw* pViewportDraw, const OdTvEntityImpl* pParentEntity) const;
  virtual OdTvGeometryData::GeometryTypes   getFirstColorGeomType() const { return OdTvGeometryData::kNone; }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                              copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;
  virtual bool                              copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity, OdTvAttributeResolverImpl* pResolver) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:
  void convertInvertedClip();
  void removeFromImageReferenceList();

  void copyToInternal(OdTvRasterImageDataImpl* pTargetRasterImage) const;

  OdTvPointArray getWcsBoundaryPoints() const;

private:

  //data
  OdGeVector2d              m_Size;           // valid of the image is loaded (already loaded with file or binary)
  OdGePoint3d               m_origin;
  OdGeVector3d              m_uVector;
  OdGeVector3d              m_vVector;
  OdTvDbHardPointerId       m_ImageDefId;
  ClippingData*             m_pClipping;      //clipping parameters

  //at least windows 64 bit will aligh next variables to one 8 byte
  OdTvCmEntityColor         m_backgroundColor; // used as background color only for monochrome images
  OdUInt8                   m_Brightness;
  OdUInt8                   m_Contrast;
  OdUInt8                   m_Fade;
};

typedef OdTvSmartPtrInternal<OdTvRasterImageDataImpl> OdTvRasterImageDataImplPtr;



/** \details
This is an wrapper of the interface class for OdTvRasterImageData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvRasterImageDataWrapper : public OdTvRasterImageData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvRasterImageData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Sets the Object ID of the OdTvDbRasterImageDef object associated with this raster image entity (DXF 340).
  \param imageDefId [in]  Object ID of image to be displayed.
  */
  virtual OdTvResult setImageId(OdTvRasterImageId imageId);

  /** \details
  Returns the Object ID of the OdTvDbRasterImageDef object associated with this raster image entity (DXF 340).
  */
  virtual OdTvRasterImageId getImageId(OdTvResult* rc = NULL) const;

  /** \details
  Sets the orientation and origin of this raster image data.

  \param origin [in]  Lower-left corner.
  \param u [in]  Image width vector.
  \param v [in]  Image height vector.

  \remarks
  The actual height of the image is determined by the width and aspect ratio fo the original image.
  */
  virtual OdTvResult setOrientation(const OdTvPoint& origin, const OdTvVector& u, const OdTvVector& v);

  /** \details
  Returns the orientation and origin of this raster image data.

  \param origin [out]  Receives the lower-left corner.
  \param u [out]  Receives the vector defining the image direction and width.
  \param v [out]  Receives the vector defining the direction of the height of the image.
  */
  virtual OdTvResult getOrientation(OdTvPoint& origin, OdTvVector& u, OdTvVector& v) const;

  /** \details
  Sets the clip boundary for this raster image data.

  \remarks  Array of 2D points should be in pixel coordinates
  if size == 2 - it is a rectangular boundary, polygonal - otherwise
  */
  virtual OdTvResult setClipBoundary(const OdTvPoint2dArray& clipPoints);

  /** \details
  Returns the clip boundary for this raster image data.

  \remarks
  The clip boundary is specified in pixel coordinates.
  */
  virtual OdTvResult getClipBoundary(OdTvPoint2dArray& clipPoints) const;

  /** \details
  Returns the clipping state for this raster image data.
  */
  virtual bool getClipped(OdTvResult* rc = NULL) const;

  /** \details
  Sets the ClipInverted flag value for this raster image data.

  \param val [in]  The ClipInverted flag value.
  */
  virtual OdTvResult setClipInverted(bool val);

  /** \details
  Returns the ClipInverted flag value for this raster image data.
  */
  virtual bool getClipInverted(OdTvResult* rc = NULL) const;

  /** \details
  Sets the brightness value for this raster image data.
  \param brightness [in]  Image brightness [0.0 .. 100.0].
  */
  virtual OdTvResult setBrightness(OdInt8 brightness);

  /** \details
  Returns the brightness value for this raster image data.
  \returns
  Returns a value in the range [0.0 .. 100.0].
  */
  virtual OdInt8 getBrightness(OdTvResult* rc = NULL) const;

  /** \details
  Sets the contrast value for this raster image data.
  \param contrast [in]  Image contrast. [0.0 .. 100.0]
  */
  virtual OdTvResult setContrast(OdInt8 contrast);

  /** \details
  Returns the contrast value for this raster image data.
  \returns
  Returns a value in the range [0.0 .. 100.0].
  */
  virtual OdInt8 getContrast(OdTvResult* rc = NULL) const ;

  /** \details
  Sets the fade value for this raster image data.

  \param fade [in]  Image fade. [0.0 .. 100.0].
  */
  virtual OdTvResult setFade(OdInt8 fade);

  /** \details
  Returns the fade value for this raster image data.
  \returns
  Returns a value in the range [0.0 .. 100.0].
  */
  virtual OdInt8 getFade(OdTvResult* rc = NULL) const;

  /** \details
  Returns the size in pixels of this raster image data.
  */
  virtual OdTvVector2d getImageSize(OdTvResult* rc = NULL) const;

  /** \details
  Sets the background color for this raster image data if it is monochrome.

  \param backgroundColor [in]  Background color.
  */
  virtual OdTvResult setMonochromeBackgroundColor(const OdTvColorDef& backgroundColor);

  /** \details
  Returns the background color for this raster image data.
  */
  virtual OdTvColorDef getMonochromeBackgroundColor(OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the colored shape geometry data
*/
class OdTvColoredShapeDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the colored shape flags
  */
  enum coloredShapeFlags
  {
    kDrawContour = 1 << 16
  };

  OdTvColoredShapeDataImpl()
    : OdTvGeometryDataImpl(),
      m_vertices(NULL),
      m_faces(NULL),
      m_vertexColors(NULL),
      m_edgesVisibilities(NULL),
      m_triangFaces(NULL),
      m_nVertices(0),
      m_nEdges(0),
      m_nFacesList(0),
      m_triangFacesLength(0)
      {}

  OdTvColoredShapeDataImpl(const OdTvPointArray& verticesArray, const OdInt32Array& faces);
  OdTvColoredShapeDataImpl(OdInt32 nPoints, const OdTvPoint* points, OdInt32 faceListSize, const OdInt32* faces);
  virtual ~OdTvColoredShapeDataImpl();

  void set(const OdTvPointArray& verticesArray, const OdInt32Array& faces);
  void set(OdInt32 nVertices, const OdTvPoint* vertices, OdInt32 faceListSize, const OdInt32* faces);

  OdTvResult setVertexColors(const OdTvRGBColorDef* colors);
  OdTvResult setVertexColors(const OdTvRGBColorDefArray& colors);
  OdTvResult setEdgesVisibilities(const OdTvVisibilityDef* visibilities);
  OdTvResult setEdgesVisibilities(const OdTvVisibilityDefArray& visibilities);
  OdTvResult setDrawContour(bool bDraw);
  OdTvResult setHatchPattern(const OdTvHatchPatternDef& def);
  OdTvHatchPatternDef getHatchPattern(OdTvResult* rc = NULL) const;

  void        get(OdTvPointArray& verticesArray, OdInt32Array& faces) const;
  void        getVertexColors(OdTvRGBColorDefArray& colors) const;
  void        getEdgesVisibilities(OdTvVisibilityDefArray& visibilities) const;
  OdUInt32    getVerticesCount(OdTvResult* rc = NULL) const;
  OdUInt32    getFacesCount(OdTvResult* rc = NULL) const;
  OdUInt32    getEdgesCount(OdTvResult* rc = NULL) const;
  bool        getDrawContour() const;

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                    entityGeometryDataType() const { return ColoredShape; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes   getFirstColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual OdTvGeometryData::GeometryTypes   getSecondColorGeomType() const { return OdTvGeometryData::kEdges; }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:
  OdUInt32 countFaces(OdUInt32* nEdges = NULL) const;

  void deleteVerticesData();
  void deleteFaces();
  void deleteEdgesVisibilities();
  void deleteTrianFaces();

private:

  //data
  OdTvPoint*                      m_vertices;             //vertices
  OdInt32*                        m_faces;                //faces storage
  OdCmEntityColor*                m_vertexColors;         //vertices colors
  OdUInt8*                        m_edgesVisibilities;    //edges visibilities
  mutable OdInt32*                m_triangFaces;          //triangle faces storage (after triangulation for snap)
  OdGiHatchPatternPtr             m_pHatchPattern;        //hatch pattern fill data
  OdUInt32                        m_nVertices;            //number of vertices
  OdUInt32                        m_nEdges;               //number of edges
  OdUInt32                        m_nFacesList;           //number of elements in the face's storage
  mutable OdUInt32                m_triangFacesLength;    //number of elements in the triangles storage (after triangulation for snap)
};

typedef OdTvSmartPtrInternal<OdTvColoredShapeDataImpl> OdTvColoredShapeDataImplPtr;



/** \details
This is an wrapper of the interface class for OdTvColoredShapeData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvColoredShapeDataWrapper : public OdTvColoredShapeData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvColoredShapeData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Set the geometry data of the plane colored area
  */
  virtual OdTvResult set(const OdTvPointArray& verticesArray, const OdInt32Array& faces);

  /** \details
  Set the geometry data of the plane colored area
  */
  virtual OdTvResult set(OdInt32 nVertices, const OdTvPoint* vertices, OdInt32 faceListSize, const OdInt32* faces);

  /**
  Set the vertices colors of the plane colored area
  */
  virtual OdTvResult setVertexColors(const OdTvRGBColorDef* colors);

  /**
  Set the vertices colors of the plane colored area
  */
  virtual OdTvResult setVertexColors(const OdTvRGBColorDefArray& colors);

  /**
  Set the edges visibilities of the plane colored area
  */
  virtual OdTvResult setEdgesVisibilities(const OdTvVisibilityDef* visibilities);

  /**
  Set the edges visibilities of the plane colored area
  */
  virtual OdTvResult setEdgesVisibilities(const OdTvVisibilityDefArray& visibilities);

  /** \details
  Sets true if and only if the countour should be drawn
  */
  virtual OdTvResult setDrawContour(bool bDraw);

  /** \details
  Get the geometry data of the plane colored area
  */
  virtual OdTvResult get(OdTvPointArray& verticesArray, OdInt32Array& faces) const;

  /** \details
  Get the vertices color of the plane colored area
  */
  virtual OdTvResult getVertexColors(OdTvRGBColorDefArray& colors) const;

  /** \details
  Get the vertices color of the plane colored area
  */
  virtual OdTvResult getEdgesVisibilities(OdTvVisibilityDefArray& visibilities) const;

  /** \details
  Returns true if and only if the countour should be drawn
  */
  virtual bool getDrawContour(OdTvResult* rc = NULL) const;

  /** \details
  Returns the number of vertices in the plane colored area
  */
  virtual OdUInt32 getVerticesCount(OdTvResult* rc = NULL) const;

  /** \details
  Returns the number of faces in the plane colored area
  */
  virtual OdUInt32 getFacesCount(OdTvResult* rc = NULL) const;

  /** \details
  Returns the number of edges in the plane colored area
  */
  virtual OdUInt32 getEdgesCount(OdTvResult* rc = NULL) const;

  /** \details
  Sets a hatch pattern for the colored shape object.
  */
  virtual OdTvResult setHatchPattern(const OdTvHatchPatternDef& def);

  /** \details
  Retrieves a hatch pattern object for the colored shape object.
  */
  virtual OdTvHatchPatternDef getHatchPattern(OdTvResult* rc = NULL) const;

};

#include "TD_PackPop.h"

#endif //_ODTV_ENTITYTYPIFIEDGEOMETRYDATAMISC_H_INCLUDED_

