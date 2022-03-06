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

#ifndef _ODTV_ENTITYTYPIFIEDGEOMETRYDATA3D_H_INCLUDED_
#define _ODTV_ENTITYTYPIFIEDGEOMETRYDATA3D_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvGeometryDataImpl.h"
#include "RcsFileServices/RxRcsFileServices.h"
#include "TvExtentsSpaceTree.h"

/** \details
This class implements the sphere data
*/
class OdTvSphereDataImpl : public OdTvGeometryDataImpl
{
public: 

  /** \details
  Enum for the sphere flags
  */
  enum sphereFlags
  {
    k2D                       = 1 << 16,
    kAutoDeviationFlag        = 1 << 17,  // Auto deviation.
    kFixedDeviationFlag       = 1 << 18,  // Fixed deviation.
    kNotMoreThanDeviationFlag = 1 << 19   // Not more than value.
  };

  OdTvSphereDataImpl();
  virtual ~OdTvSphereDataImpl() {};

  OdTvResult set(const OdTvPoint& center, double radius, const OdTvVector& axis, const OdTvVector& primeMeridian);
  void setCenter(const OdTvPoint& center);
  void setRadius(double radius);
  OdTvResult setBasis(const OdTvVector& axis, const OdTvVector& primeMeridian);
  OdTvResult setDeviation(const OdTvSphereData::Deviation& deviationType, OdUInt32 value);

  void get(OdTvPoint& center, double& radius, OdTvVector& axis, OdTvVector& primeMeridian) const;
  OdTvPoint getCenter() const;
  double getRadius() const;
  void getBasis(OdTvVector& axis, OdTvVector& primeMeridian) const;
  OdTvSphereData::Deviation getDeviation(OdUInt32& value, OdTvResult* rc) const;

  virtual TvGeometryType                      entityGeometryDataType() const { return Sphere; }
  virtual bool                                draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                                drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes     getFirstColorGeomType() const { return OdTvGeometryData::kEdges; }
  virtual void                                read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                                write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                                copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  static OdTvResult generateSphereShell(const OdTvPoint& center, double radius, int nDiv, OdTvPointArray& verticesArray, OdInt32Array& faces, OdUInt32* nEdges, OdUInt32* nFaces, OdTvVectorArray& normalsArray, const OdTvVector& axis = OdTvVector(0., 1., 0.));

  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:
  // edge specific routines
  void calculateEdgeVisibilities(OdTvUInt8ArrayStorage& edgesVisibilities, OdUInt32 nEdges, int nDiv, const OdTvEntityImpl* pParentEntity) const;
  void getNearSnapPointFromShell(const OdTvPoint& pickPoint, OdTvGeometryData::SnapMode snapMode, const OdTvVector& eyeDir, const OdTvMatrix& xWorldToEye, const OdTvMatrix* pTransform, OdTvPoint& snapPoint) const;
  //internal methods
  double  mMaxArcStepAngle(double n) const;

private:

  //data
  OdTvPoint       m_center;
  double          m_dRadius;
  OdTvVector      m_axis;
  OdTvVector      m_primeMeridian;
  mutable OdInt32 m_deviationValue;
};

typedef OdTvSmartPtrInternal<OdTvSphereDataImpl> OdTvSphereDataImplPtr;

/** \details
This is an wrapper of the interface class for OdTvSphereData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvSphereDataWrapper : public OdTvSphereData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvSphereData)

protected:
  ODRX_HEAP_OPERATORS();

public:
  /** \details
  Set the center and radius of the sphere
  */
  virtual OdTvResult setParam(const OdTvPoint& center, double radius, const OdTvVector& axis = OdTvVector(0., 1., 0), const OdTvVector& primeMeridian = OdTvVector(1., 0., 0));

  /** \details
  Set the radius of the sphere
  */
  virtual OdTvResult setRadius(double radius);

  /** \details
  Set the center of the sphere
  */
  virtual OdTvResult setCenter(const OdTvPoint& center);

  /** \details
  Set the basis of the sphere
  */
  virtual OdTvResult setBasis(const OdTvVector& axis, const OdTvVector& primeMeridian);

  /** \details
  Set the deviation for this sphere.
  */
  virtual OdTvResult setDeviation(const Deviation& deviationType, OdUInt32 value);

  /** \details
  Returns the array of the vertices
  */
  virtual OdTvResult getParam(OdTvPoint& center, double& radius, OdTvVector& axis, OdTvVector& primeMeridian) const;

  /** \details
  Get the radius of the sphere
  */
  virtual double getRadius(OdTvResult* rc = NULL) const;

  /** \details
  Get the center of the sphere
  */
  virtual OdTvPoint getCenter(OdTvResult* rc = NULL) const;

  /** \details
  Get the basis of the sphere
  */
  virtual OdTvResult getBasis(OdTvVector& axis, OdTvVector& primeMeridian) const;

  /** \details
  Retrieves deviation data of this sphere.
  */
  virtual Deviation getDeviation(OdUInt32& value, OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the Cylinder data
*/
class OdTvCylinderDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the cylinder flags
  */
  enum cylinderFlags
  {
    k2D                       = 1 << 16,
    kAutoDeviationFlag        = 1 << 17,  // Auto deviation.
    kFixedDeviationFlag       = 1 << 18,  // Fixed deviation.
    kNotMoreThanDeviationFlag = 1 << 19,  // Not more than value.
    kNoneCapFlag              = 1 << 20,  // No capping.
    kFirstCapFlag             = 1 << 21,  // First capping.
    kSecondCapFlag            = 1 << 22,  // Second capping.
    kBothCapFlag              = 1 << 23   // Both capping.
  };

  OdTvCylinderDataImpl();
  OdTvCylinderDataImpl(const OdTvPointArray& points, const OdDoubleArray& radii, const OdTvCylinderData::Capping& caps = OdTvCylinderData::kBoth);
  virtual ~OdTvCylinderDataImpl()
  {
    if (m_points)
    {
      delete[] m_points;
      m_points = NULL;
    }

    if (m_radii)
    {
      delete[] m_radii;
      m_radii = NULL;
    }
  }

  //set/get
  OdTvResult set(const OdTvPointArray& points, const OdDoubleArray& radii, const OdTvCylinderData::Capping& caps = OdTvCylinderData::kBoth);
  OdTvResult set(const OdTvPoint& point1, const OdTvPoint& point2, double radius, const OdTvCylinderData::Capping& caps = OdTvCylinderData::kBoth);
  void get(OdTvPointArray& points, OdDoubleArray& radii, OdTvCylinderData::Capping& caps);

  OdTvPointArray getPoints() const;
  OdDoubleArray getRadii() const;
  OdTvCylinderData::Capping getCaps() const;
  OdTvCylinderData::Deviation getDeviation(OdUInt32& value, OdTvResult* rc) const;

  OdTvResult setPoints(const OdTvPointArray& points);
  OdTvResult setRadii(const OdDoubleArray& radii);
  void setCaps(const  OdTvCylinderData::Capping& caps = OdTvCylinderData::kBoth);
  OdTvResult setDeviation(const OdTvCylinderData::Deviation& deviationType, OdUInt32 value);

  virtual TvGeometryType                    entityGeometryDataType() const { return Cylinder; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes   getFirstColorGeomType() const { return OdTvGeometryData::kEdges; }
  virtual OdTvGeometryData::GeometryTypes   getSecondColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  static OdTvResult generateCylinderShell(OdTvPointArray& verticesArray, OdInt32Array& faces, const OdTvPointArray& points, const OdDoubleArray& radii, OdUInt32* nEdges, OdUInt32* nFaces, OdTvVectorArray& faceNormalsArray, OdUInt32 flags = kBothCapFlag, int nDiv = 10);

  static OdTvResult generateCylinderShell(OdTvPointArray& verticesArray, OdInt32Array& faces, const OdTvPoint* points, const double* radii, OdUInt32 nPoints, OdUInt32 nRadii, OdUInt32* nEdges, OdUInt32* nFaces, OdTvVectorArray& faceNormalsArray, OdUInt32 flags = kBothCapFlag, int nDiv = 10);

  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:

    static OdTvResult checkPoints(const OdTvPointArray& points);
    double maxArcStepAngle(double n) const;
    double maxRadius() const;
    OdTvResult drawIsolines(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
    void getNearSnapPointFromShell(const OdTvPoint& pickPoint, OdTvGeometryData::SnapMode snapMode, const OdTvVector& eyeDir, const OdTvMatrix& xWorldToEye, const OdTvMatrix* pTransform, OdTvPoint& snapPoint) const;

private:

  //data
  OdTvPoint*        m_points;
  OdDouble*         m_radii;
  OdUInt32          m_nPoints;
  OdUInt32          m_nRadii;
  mutable OdInt32   m_deviationValue;
};

typedef OdTvSmartPtrInternal<OdTvCylinderDataImpl> OdTvCylinderDataImplPtr;


/** \details
This is an wrapper of the interface class for OdTvGeometryData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvCylinderDataWrapper : public OdTvCylinderData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvCylinderData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Set params of the Cylinder
  */
  virtual OdTvResult setParam(const OdTvPoint& point1, const OdTvPoint& point2, double& radius, const Capping& caps = OdTvCylinderData::kBoth);

  /** \details
  Set params of the Cylinder
  */
  virtual OdTvResult setParam(const OdTvPointArray& points, const OdDoubleArray& radii, const Capping& caps = OdTvCylinderData::kBoth);

  /** \details
  Get params of the Cylinder
  */
  virtual OdTvResult getParam(OdTvPointArray& points, OdDoubleArray& radii, Capping& cap);

  /** \details
  Set the points for this Cylinder
  */
  virtual OdTvResult setPoints(const OdTvPointArray& points);

  /** \details
  Set the radius for this Cylinder
  */
  virtual OdTvResult setRadii(const OdDoubleArray& radius);

  /** \details
  Set the capping for this Cylinder
  */
  virtual OdTvResult setCaps(const Capping& caps = OdTvCylinderData::kBoth);

  /** \details
  Set the deviation for this cylinder.
  */
  virtual OdTvResult setDeviation(const Deviation& deviationType, OdUInt32 value);

  /** \details
  Get the point1 of this Cylinder
  */
  virtual OdTvPointArray getPoints(OdTvResult* rc = NULL) const;

  /** \details
  Get the radius of this Cylinder
  */
  virtual OdDoubleArray getRadii(OdTvResult* rc = NULL) const;


  /** \details
  Get the cappig of this Cylinder
  */
  virtual Capping getCaps(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves deviation data of this cylinder.
  */
  virtual Deviation getDeviation(OdUInt32& value, OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the Box data
*/
class OdTvBoxDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the box flags
  */
  enum boxFlags
  {
    k2D = 1 << 16
  };

public:
  OdTvBoxDataImpl();
  virtual ~OdTvBoxDataImpl() {}

  OdTvResult set(const OdTvPoint& centerPoint, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDirection = OdTvVector::kXAxis);
  void get(OdTvPoint& centerPoint, double& dLength, double& dWidth, double& dHeight, OdTvVector& baseNormal, OdTvVector& lengthDirection) const;

  void setCenterPoint(const OdTvPoint& point);
  OdTvPoint getCenterPoint() const;

  void setLength(double dLength);
  double getLength() const;

  void setWidth(double dWidth);
  double getWidth() const;

  void setHeight(double dHeight);
  double getHeight() const;

  OdTvResult setBaseNormal(const OdTvVector& baseNormal);
  OdTvVector getBaseNormal() const;

  OdTvResult setLengthDirection(const OdTvVector& lengthDirection);
  OdTvVector getLengthDirection() const;

  virtual TvGeometryType                    entityGeometryDataType() const { return Box; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes   getFirstColorGeomType() const { return OdTvGeometryData::kEdges; }
  virtual OdTvGeometryData::GeometryTypes   getSecondColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  static OdTvResult generateBoxShell(OdTvPointArray& verticesArray, OdInt32Array& facesArray, OdTvVectorArray& normalsArray, const OdTvPoint& centerPoint, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDirection = OdTvVector::kXAxis);

  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:

  static void generateBoxVertices(OdTvPointArray& verticesArray, const OdTvPoint& centerPoint, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDirection = OdTvVector::kXAxis);

private:

  //data
  OdTvPoint     m_centerPoint;
  OdTvVector    m_baseNormal;
  OdTvVector    m_lengthDirection;
  double        m_dLength;
  double        m_dWidth;
  double        m_dHeight;
};

typedef OdTvSmartPtrInternal<OdTvBoxDataImpl> OdTvBoxDataImplPtr;

/** \details
This is an wrapper of the interface class for OdTvGeometryData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvBoxDataWrapper : public OdTvBoxData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvBoxData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Set params of the Box

  \param centerPoint [in]  Center point of box base.
  \param dLength [in]  Length of box.
  \param dWidth [in]  Width of box.
  \param dHeight [in]  Height of box.
  \param baseNormal [in] Normal of base, defines base plane.
  \param lengthDirection [in] Define length direction
  */
  virtual OdTvResult setParam(const OdTvPoint& centerPoint, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDirection = OdTvVector::kXAxis);

  /** \details
  Get params of the Box

  \param centerPoint [out]  Center point of box base.
  \param dLength [out]  Length of box.
  \param dWidth [out]  Width of box.
  \param dHeight [out]  Height of box.
  \param baseNormal [out] Normal of base, defines base plane.
  \param lengthDirection [out] Define length direction
  */
  virtual OdTvResult getParam(OdTvPoint& centerPoint, double& dLength, double& dWidth, double& dHeight, OdTvVector& baseNormal, OdTvVector& lengthDirection) const;

  /** \details
  Set the center point of this Box
  */
  virtual OdTvResult setCenterPoint(const OdTvPoint& point);

  /** \details
  Get the center point of this Box
  */
  virtual OdTvPoint getCenterPoint(OdTvResult* rc = NULL) const;

  /** \details
  Set length of this Box.
  */
  virtual OdTvResult setLength(double dLength);

  /** \details
  Get length of this Box.
  */
  virtual double getLength(OdTvResult* rc = NULL) const;

  /** \details
  Set width of this Box.
  */
  virtual OdTvResult setWidth(double dWidth);

  /** \details
  Get width of this Box.
  */
  virtual double getWidth(OdTvResult* rc = NULL) const;

  /** \details
  Set height of this Box.
  */
  virtual OdTvResult setHeight(double dHeight);

  /** \details
  Get height of this Box.
  */
  virtual double getHeight(OdTvResult* rc = NULL) const;

  /** \details
  Set normal to base plane of this Box.
  */
  virtual OdTvResult setBaseNormal(const OdTvVector& baseNormal);

  /** \details
  Get normal to base plane of this Box.
  */
  virtual OdTvVector getBaseNormal(OdTvResult* rc = NULL) const;

  /** \details
  Set length direction of this Box.
  */
  virtual OdTvResult setLengthDirection(const OdTvVector& lengthDirection);

  /** \details
  Get length direction of this Box.
  */
  virtual OdTvVector getLengthDirection(OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This is an interface class for OdTvPointCloudData object
*/
class OdTvPointCloudDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the point cloud flags
  */
  enum pointCloudFlags
  {
    kVerticesSelectable         = 1 << 16,
    kUseSpatialTreeForSelection = 1 << 17
  };

  /** \details
  Structure for the storing the internal spatila tree
  */
  struct spaceTreeParameters
  {
    OdTvExtentsSpaceTreeVertex*       m_pPointsTree;
    OdTvExtents3d                     m_extents;
    spaceTreeParameters() : m_pPointsTree(NULL) {}

    OdUInt64 getObjectSize() const
    {
      OdUInt64 res = 0;

      //size itself
      res += sizeof(*this);

      if (m_pPointsTree != NULL)
        res += m_pPointsTree->getObjectSize();

      return res;
    }
  };

  // constructors / destructor
  OdTvPointCloudDataImpl();
  OdTvPointCloudDataImpl(OdInt32 numPoints, const OdTvPoint* points);
  OdTvPointCloudDataImpl(const OdTvPointArray& points);
  virtual ~OdTvPointCloudDataImpl();

  // set methods
  OdTvResult set(OdInt32 numPoints, const OdTvPoint* points);
  OdTvResult set(const OdTvPointArray& points);
  OdTvResult set(OdPointCloudDataSourcePtr pDataSource, const OdTvColorDef& defaultColor);
  OdTvResult setPointSize(OdInt32 pointSize);

  // get methods
  OdTvPointArray get(OdTvResult* rc = NULL) const;
  void           get(OdTvPointArray& pointArray) const;
  OdInt32        getPointSize(OdTvResult* rc = NULL) const;
  OdInt32        getPointsCount(OdTvResult* rc = NULL) const;
  OdTvPoint      getPointCoo(OdInt32 ind, OdTvResult* rc = NULL) const;

  OdTvResult editPointsViaRange(OdUInt32 startPos, OdUInt32 nPointss, const OdTvPoint* points);
  OdTvResult editPointsViaList(OdUInt32 nPoints, const OdUInt32* indPoints, const OdTvPoint* points);

  OdTvResult appendPoints(OdInt32 nPoints, const OdTvPoint* points);

  /** \details
  Get sub geometry by marker
  */
  bool getSubGeomIdByGsMarker(const OdGsMarker& marker, OdTv::SubGeometryType& type, OdInt64& subGeomId) const;

  /** \details
  Get markers by sub geometry ids
  */
  bool getGsMarkersBySubGeomIds(OdArray< OdGsMarker >& markers, const OdUInt32Array& subGeomIds) const;

  /** \details
  Return the last marker of this shell object
  */
  OdGsMarker getEndMarker() const;

  /** \details
  Return the first - 1 marker of this shell object
  */
  OdGsMarker getStartMarker() const;

  /** \details
  Get all markers of this geometry data (including subgeometry)
  */
  virtual void getMarkers(std::set< OdGsMarker >& markers, std::set< OdGsMarker >* pCompareMarkers = NULL) const;

  /**
  Point colors management
  */
  OdTvResult setPointColorsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvRGBColorDef* colors);
  OdTvResult setPointColorsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvRGBColorDef& color);

  OdTvResult setPointColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color);
  OdTvResult setPointColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors);

  OdTvResult getPointColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvRGBColorDefArray& colors) const;
  OdTvResult getPointColorsViaList(const OdInt32Array& indPoints, OdTvRGBColorDefArray& colors) const;
  OdTvRGBColorDef getPointColor(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Point normals management
  */
  OdTvResult setPointNormalsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvVector* vectors);
  OdTvResult setPointNormalsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvVector& vector);

  OdTvResult setPointNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector);
  OdTvResult setPointNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors);

  OdTvResult getPointNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const;
  OdTvResult getPointNormalsViaList(const OdInt32Array& indPoints, OdTvVectorArray& vectors) const;
  OdTvVector getPointNormal(OdInt32 ind, OdTvResult* rc = NULL) const;

  /** \details
  Use spatial tree for selection.
  */
  OdTvResult setUseSpatialTreeForSelection(bool bUseSpatialTreeForSelection);
  bool getUseSpatialTreeForSelection(OdTvResult* rc = NULL) const;

  virtual TvGeometryType                   entityGeometryDataType() const { return PointCloud; }
  virtual bool                             draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                             drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes  getFirstColorGeomType() const { return OdTvGeometryData::kVertices; }
  virtual void                             read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                             write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;
  virtual void                             setSelectability(const OdTvSelectabilityDef& selectability);
  virtual void                             actionAfterTransformModifying();

  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

  /** \details
  Get points tree.
  */
  OdTvExtentsSpaceTreeBase* getPointsTree() const;

  /** \details
  Check if geometry data can be selected
  */
  virtual bool isSelectable() const;

  /** \details
  Get vertices selectable
  */
  bool getVerticesSelectable() const {return GETBIT(m_flags, kVerticesSelectable);}

private:
  // if m_colors is empty need get color from entity
  void calculatePointColor(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdTvGeometryDataTraits* pLocalTraits);
  void calculatePointNormals();
  void affectPointColors(OdTvCmEntityColor& color, OdTvCmEntityColor& blockRefColor, OdDbStub* layerdbId, OdGiWorldDraw* pWorldDraw);

  void updateExtents(const OdTvPointArray& points);

  //  Reset spatial tree
  virtual void resetSpatialTree();

  // Process spatial tree edit
  virtual void processSpatialTreeEdit(OdUInt32 startPos, OdUInt32 nPoints, bool bNeedRemove = true);
  virtual void processSpatialTreeEdit(OdUInt32 nPoints, const OdUInt32* indPoints);

private:

  //here we can use arrays despite the fact that it uses additional data (for logical, length, grow length etc) since usually we have 
  //a significant number of points
  OdTvPointArray                    m_points;
  OdTvColorArrayStorage             m_colors;
  OdTvVector3dArrayStorage          m_normals;
  spaceTreeParameters*              m_pExtentsSpaceTreeParameters;
  OdGsMarker                        m_startMarker;
  OdInt16                           m_nPointSize;
};

typedef OdTvSmartPtrInternal<OdTvPointCloudDataImpl> OdTvPointCloudDataImplPtr;

/** \details
This is an wrapper of the interface class for OdTvGeometryData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvPointCloudDataWrapper : public OdTvPointCloudData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvPointCloudData)

protected:
  ODRX_HEAP_OPERATORS();

public:
  /** \details
  Set the array of points
  */
  virtual OdTvResult setParam(const OdTvPointArray& points);

  /** \details
  Set the array of points
  */
  virtual OdTvResult setParam(OdInt32 nPoints, const OdTvPoint* points);

  /** \details
  Get the array of points
  */
  virtual OdTvPointArray getParam(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves the points of the point cloud.
  */
  virtual OdTvResult getParam(OdTvPointArray& points) const ;

  /** \details
  Get the point size
  */
  virtual OdInt32 getPointsCount(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves the coordinates for a specified point of the point cloud.
  */
  virtual OdTvPoint getPointCoo(OdInt32 ind, OdTvResult* rc = NULL) const;

  /** \details
  Replace points of the point cloud starting with startPos
  */
  virtual OdTvResult editPointsViaRange(OdUInt32 startPos, const OdTvPointArray& points);

  /** \details
  Replace points of the point cloud starting with startPos
  */
  virtual OdTvResult editPointsViaRange(OdUInt32 startPos, OdUInt32 nPoints, const OdTvPoint* points);

  /** \details
  Replace points defined by 'indPoints' of the point cloud
  */
  virtual OdTvResult editPointsViaList(const OdInt32Array& indPoints, const OdTvPointArray& points);

  /** \details
  Replace points defined by 'indPoints' of the point cloud
  */
  virtual OdTvResult editPointsViaList(OdUInt32 nPoints, const OdUInt32* indPoints, const OdTvPoint* points);

  /** \details
  Append an array of points to point cloud points.
  */
  virtual OdTvResult appendPoints(const OdTvPointArray& points);

  /** \details
  Append an array of points to point cloud points.
  */
  virtual OdTvResult appendPoints(OdInt32 nPoints, const OdTvPoint* points);

  /** \details
  Set the point size
  */
  virtual OdTvResult setPointSize(OdInt32 pointSize);

  /** \details
  Get the point size
  */
  virtual OdInt32 getPointSize(OdTvResult* rc = NULL) const;

  /** \details
  Set use spatial tree for selection enabled.
  */
  virtual OdTvResult setUseSpatialTreeForSelection(bool bUseSpatialTreeForSelection);

  /** \details
  Retrieves if need use spatial tree for selection.
  */
  virtual bool getUseSpatialTreeForSelection(OdTvResult* rc = NULL) const;

  /**
  Point colors management
  */
  virtual OdTvResult setPointColorsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvRGBColorDef* colors);
  virtual OdTvResult setPointColorsViaList(const OdInt32Array& indPoints, const OdTvRGBColorDefArray& colors);
  virtual OdTvResult setPointColorsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvRGBColorDef& color);
  virtual OdTvResult setPointColorsViaList(const OdInt32Array& indPoints, const OdTvRGBColorDef& color);

  virtual OdTvResult setPointColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color);
  virtual OdTvResult setPointColorsViaRange(OdInt32 indStart, const OdTvRGBColorDefArray& colors);
  virtual OdTvResult setPointColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors);

  virtual OdTvResult getPointColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvRGBColorDefArray& colors) const;
  virtual OdTvResult getPointColorsViaList(const OdInt32Array& indPoints, OdTvRGBColorDefArray& colors) const;
  virtual OdTvRGBColorDef getPointColor(OdInt32 ind, OdTvResult* rc = NULL) const;

  /**
  Point normals management
  */
  virtual OdTvResult setPointNormalsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvVector* vectors);
  virtual OdTvResult setPointNormalsViaList(const OdInt32Array& indPoints, const OdTvVectorArray& vectors);
  virtual OdTvResult setPointNormalsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvVector& vector);
  virtual OdTvResult setPointNormalsViaList(const OdInt32Array& indPoints, const OdTvVector& vector);

  virtual OdTvResult setPointNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector);
  virtual OdTvResult setPointNormalsViaRange(OdInt32 indStart, const OdTvVectorArray& vectors);
  virtual OdTvResult setPointNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors);

  virtual OdTvResult getPointNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const;
  virtual OdTvResult getPointNormalsViaList(const OdInt32Array& indPoints, OdTvVectorArray& vectors) const;
  virtual OdTvVector getPointNormal(OdInt32 ind, OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This is an interface class for OdTvRcsPointCloudData object
*/
class OdTvRcsPointCloudDataImpl : public OdTvGeometryDataImpl
{
public:
  // constructors / destructor 
  OdTvRcsPointCloudDataImpl()
    : OdTvGeometryDataImpl(), m_nDrawnPointsCount(0), m_nVisibleVoxelsCount(0), m_nPointSize(2) {}
  virtual ~OdTvRcsPointCloudDataImpl() {};

  /* own methods */
  OdTvResult set(OdPointCloudScanDatabasePtr pScanDb, OdPointCloudProjectDatabasePtr pProjDb);
  OdTvResult set(OdPointCloudDataSourcePtr pDataSource, const OdString& outputFilePath);

  OdInt32 getDrawnPointsCount(OdTvResult* rc = NULL) const;
  OdInt32 getVisibleVoxelsCount(OdTvResult* rc = NULL) const;
  OdTvResult setPointSize(OdInt32 pointSize);
  OdInt32 getPointSize(OdTvResult* rc = NULL) const;
  OdGeExtents3d getExtents(OdTvResult* rc = NULL) const;
  OdGeExtents3d getTransformedExtents(OdTvResult* rc = NULL) const;


  virtual TvGeometryType entityGeometryDataType() const { return RcsPointCloud; }
  virtual OdTvGeometryData::GeometryTypes getFirstColorGeomType() const { return OdTvGeometryData::kVertices; }

  virtual bool                             draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                             drawView(OdGiViewportDraw* pViewportDraw, const OdTvEntityImpl* pParentEntity) const;
  virtual void                             drawForMarkers(const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                             read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                             write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual void                             setReadSharedData(void *pSharedData);
  virtual void*                            getReadSharedData() const;

  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

private:
  void drawPoints(OdGiGeometry& geom, OdInt16 pointSize, OdUInt32& nDrawnPoints, OdUInt32& nVisibleVoxels) const;

private:
  
  //data
  OdString m_strRcpFileName;
  OdString m_strRcsFileName;

  mutable OdRxRcsFileServicesPtr m_pRcsFileServices;
  mutable OdPointCloudProjectDatabasePtr m_pProjDb;
  mutable OdPointCloudScanDatabasePtr m_pScanDb;
  mutable OdRcsDataManagerPtr m_pRcsDataMgr;

  OdUInt32 m_nDrawnPointsCount;
  OdUInt32 m_nVisibleVoxelsCount;
  OdInt16  m_nPointSize;
};

typedef OdTvSmartPtrInternal<OdTvRcsPointCloudDataImpl> OdTvRcsPointCloudDataImplPtr;

/** \details
This is an wrapper of the interface class for OdTvRcsPointCloudData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvRcsPointCloudDataWrapper : public OdTvRcsPointCloudData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvRcsPointCloudData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Retrieves the quantity of points which are currently drawn.
  */
  virtual OdInt32 getDrawnPointsCount(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves the quantity of voxels which contents are currently visible.
  */
  virtual OdInt32 getVisibleVoxelsCount(OdTvResult* rc = NULL) const;

  /** \details
  Sets the point size.
  */
  virtual OdTvResult setPointSize(OdInt32 pointSize);

  /** \details
  Retrieves the point size.
  */
  virtual OdInt32 getPointSize(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves an own extents of this rcs point cloud object.
  */
  virtual OdGeExtents3d getExtents(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves a transfromed extents of this rcs point cloud object (in context of RCP project).
  */
  virtual OdGeExtents3d getTransformedExtents(OdTvResult* rc = NULL) const;
};

#include "TD_PackPop.h"

#endif //_ODTV_ENTITYTYPIFIEDGEOMETRYDATA3D_H_INCLUDED_

