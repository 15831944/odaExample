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

#ifndef _ODTV_ENTITYTYPIFIEDGEOMETRYDATA_H_INCLUDED_
#define _ODTV_ENTITYTYPIFIEDGEOMETRYDATA_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvGeometryDataImpl.h"

/** \details
  Struct for storing the extrusion data
*/
struct OdTvGeometryExtrusionData
{
  /** \details
  Constructor
  */
  OdTvGeometryExtrusionData() : m_normal(OdTvVector::kZAxis), m_thickness(0.) {}
  /** \details
  Destructor
  */
  ~OdTvGeometryExtrusionData();
  /** \details
  Read
  */
  void read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  /** \details
  Write
  */
  void write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  /** \details
  Checks that there is data for extrusion
  */
  bool hasExtrusion() const;
  /** \details
  Special methods for read/write thickness and normal
  */
  static double        rdThickness(OdTvDbDwgFiler* pFiler);
  static OdTvVector&   rdNormal(OdTvDbDwgFiler* pFiler, OdTvVector& p);
  static void          wrThickness(OdTvDbDwgFiler* pFiler, double val);
  static void          wrNormal(OdTvDbDwgFiler* pFiler, const OdTvVector& p);

  /** \details
  Data fields
  */
  OdTvVector      m_normal;          // normal vector which specifies the direction and distance of the extrusion
  double          m_thickness;        // an amount on which the extrusion should be performed
};

/** \details
  This class implements the line defined by two points
*/
class OdTvPolylineDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the polyline flags
  */
  enum polylineFlags
  {
    kFilledExtrusion = 1 << 16 // means that the extrusion will be filled in
  };

  OdTvPolylineDataImpl()
    : OdTvGeometryDataImpl()
    , m_pPoints(NULL)
    , m_pExtrusionData(NULL)
    , m_nPoints (0)
  {
  }
  virtual ~OdTvPolylineDataImpl();

  /* own methods */
  OdTvResult set(const OdTvPoint& start, const OdTvPoint& end);
  OdTvResult set(const OdTvPointArray& pointArray);
  OdTvResult set(OdInt32 nPoints, const OdTvPoint* points);
  void get(OdTvPointArray& pointArray) const;
  OdInt32  getPointsCount() const;

  void setNormal(const OdTvVector* normal);
  bool getNormal(OdTvVector& normal) const; // returns true if and only if the normal was set

  void setThickness(double thickness, bool bFilled = false);
  double getThickness(bool& bFilled) const;

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                   entityGeometryDataType() const { return Polyline; }
  virtual bool                             draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes  getFirstColorGeomType() const { return OdTvGeometryData::kPolylines; }
  virtual bool                             hasThickness() const { return (m_pExtrusionData && m_pExtrusionData->hasExtrusion()); }
  virtual void                             read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                             write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;


  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;
  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
                                   const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints,
                                   const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;
  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:

  void deletePoints();

private:
  OdTvPoint*                  m_pPoints;              // points of the polyline
  OdTvGeometryExtrusionData*  m_pExtrusionData;       //extrusion parameters
  OdUInt32                    m_nPoints;              // number of the polyline points
};

typedef OdTvSmartPtrInternal<OdTvPolylineDataImpl> OdTvPolylineDataImplPtr;


/** \details
  This is an wrapper of the interface class for OdTvGeometryData object.

  \remarks
  The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvPolylineDataWrapper : public OdTvPolylineData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvPolylineData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Replace the points of this Polyline with the specified points
  */
  virtual OdTvResult setPoints(const OdTvPoint& start, const OdTvPoint& end);

  /** \details
  Replace the points of this Polyline with the specified points
  */
  virtual OdTvResult setPoints(const OdTvPointArray& pointArray);

  /** \details
  Replace the points of this Polyline with the specified points
  */
  virtual OdTvResult setPoints(OdInt32 nPoints, const OdTvPoint* points);

  /** \details
  Returns the number of points in this Polyline
  */
  virtual OdInt32 getPointsCount(OdTvResult* rc = NULL) const;

  /** \details
  Returns the points of this Polyline
  */
  virtual OdTvResult getPoints(OdTvPointArray& pointArray) const;

  /** \details
  Set the normal vector for this polyline

  \remarks Normal vector can be used for an extrusion
  or for the correct orientation of the inclusion in the linetypes
  */
  virtual OdTvResult setNormal(const OdTvVector* normal);

  /** \details
  Get the normal vector of this polyline
  */
  virtual bool getNormal(OdTvVector& normal, OdTvResult* rc = NULL) const;

  /** \details
  Set the thickness of the polyline
  */
  virtual OdTvResult setThickness(double thickness, bool bFilled = false);

  /** \details
  Returns the thickness of the polyline
  */
  virtual double getThickness(bool& bFilled, OdTvResult* rc = NULL) const;
};


//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
  This class implements the circle defined by center, radius and normal
*/
class OdTvCircleDataImpl : public OdTvGeometryDataImpl
{

public:

  /** \details
  Enum for the circle flags
  */
  enum circleFlags
  {
    kFilled = 1 << 16 // means that circle will be filled in
  };


  OdTvCircleDataImpl()
    : OdTvGeometryDataImpl()
    , m_vNormal(OdTvVector::kZAxis)
    , m_dRadius(0.)
    , m_thickness(0.)
    , m_center(OdTvPoint::kOrigin)
  {}
  virtual ~OdTvCircleDataImpl() {}

  /* own methods */
  OdTvResult set(const OdTvPoint& center, double radius, const OdTvVector& normal);
  OdTvResult set(const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, const OdTvPoint& thirdPoint);
  void get(OdTvPoint& center, double& radius, OdTvVector& normal) const;

  void setCenter(const OdTvPoint& center);
  OdTvResult setNormal(const OdTvVector& normal);
  void setRadius(double radius);

  OdTvPoint getCenter() const;
  OdTvVector getNormal() const;
  double getRadius() const;

  void setFilled(bool bFilled);
  bool getFilled() const;

  void   setThickness(double thickness);
  double getThickness() const;

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                    entityGeometryDataType() const { return Circle; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes   getFirstColorGeomType() const { return OdTvGeometryData::kEdges; }
  virtual OdTvGeometryData::GeometryTypes   getSecondColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual bool                              hasThickness() const { return fabs(m_thickness) > 1.0e-6; }
  virtual bool                              hasFilling() const { return GETBIT(m_flags, kFilled); }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                              copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:

  //data
  OdTvPoint   m_center;
  OdTvVector  m_vNormal;
  double      m_dRadius;

  // attributes
  double        m_thickness;
};

typedef OdTvSmartPtrInternal<OdTvCircleDataImpl> OdTvCircleDataImplPtr;


/** \details
  This is an wrapper of the interface class for OdTvGeometryData object.

  \remarks
  The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvCircleDataWrapper : public OdTvCircleData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvCircleData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Set the center, radius and perpendicular to the plane of the circle
  */
  virtual OdTvResult set(const OdTvPoint& center, double radius, const OdTvVector& normal);

  /** \details
  Set the three points on the circumference of the circle
  */
  virtual OdTvResult set(const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, const OdTvPoint& thirdPoint);

  /** \details
  Set the center point for this circle
  */
  virtual OdTvResult setCenter(const OdTvPoint& center);

  /** \details
  Set the normal vector for this circle
  */
  virtual OdTvResult setNormal(const OdTvVector& normal);

  /** \details
  Set the radius for this circle
  */
  virtual OdTvResult setRadius(double radius);

  /** \details
  Returns the center, radius and perpendicular to the plane of the circle
  */
  virtual OdTvResult get(OdTvPoint& center, double& radius, OdTvVector& normal) const;

  /** \details
  Get the center point of this circle
  */
  virtual OdTvPoint getCenter(OdTvResult* rc = NULL) const;

  /** \details
  Get the normal vector of this circle
  */
  virtual OdTvVector getNormal(OdTvResult* rc = NULL) const;

  /** \details
  Get the radius of this circle
  */
  virtual double getRadius(OdTvResult* rc = NULL) const;

  /** \details
  Set that circle should be filled-in (or not)
  */
  virtual OdTvResult setFilled(bool bFilled);

  /** \details
  Returns the filled state of the circle
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const;

  /** \details
  Set the thickness of the circle
  */
  virtual OdTvResult setThickness(double thickness);

  /** \details
  Returns the thickness of the circle
  */
  virtual double getThickness(OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the circle arc defined by three points
*/
class OdTvCircleArcDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the circle arc flags
  */
  enum circleArcFlags
  {
    kFilled = 1 << 16 // means that circle arc will be filled in
  };

  OdTvCircleArcDataImpl()
    : OdTvGeometryDataImpl()
    , m_thickness(0.)
    , m_startPoint(-1., 0., 0.)
    , m_middlePoint(0., 1., 0.)
    , m_endPoint(1., 0., 0.)
  {}
  virtual ~OdTvCircleArcDataImpl() {};

  //own methods
  OdTvResult set(const OdGePoint3d &startPoint, const OdGePoint3d &middlePoint,
    const OdGePoint3d &endPoint);
  OdTvResult setStart(const OdGePoint3d &startPoint);
  OdTvResult setMiddle(const OdGePoint3d &middlePoint);
  OdTvResult setEnd(const OdGePoint3d &middlePoint);

  void get(OdGePoint3d &startPoint, OdGePoint3d &middlePoint, OdGePoint3d &endPoint) const;
  OdGePoint3d getStart(OdTvResult* rc  = NULL) const;
  OdGePoint3d getMiddle(OdTvResult* rc = NULL) const;
  OdGePoint3d getEnd(OdTvResult* rc = NULL) const;

  void setFilled(bool bFilled);
  bool getFilled() const;

  void setThickness(double thickness);
  double getThickness() const;

  //OdTvGeometryDataImpl
  virtual TvGeometryType                  entityGeometryDataType() const { return CircleArc; }
  virtual bool                            draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                            drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes getFirstColorGeomType() const { return OdTvGeometryData::kEdges; }
  virtual OdTvGeometryData::GeometryTypes getSecondColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual bool                            hasThickness() const { return fabs(m_thickness) > 1.0e-6; }
  virtual bool                            hasFilling() const { return GETBIT(m_flags, kFilled); }
  virtual void                            read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                            write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:

  //data
  OdGePoint3d m_startPoint;
  OdGePoint3d m_middlePoint;
  OdGePoint3d m_endPoint;

  //attributes
  double m_thickness;
};

typedef OdTvSmartPtrInternal<OdTvCircleArcDataImpl> OdTvCircleArcDataImplPtr;


/** \details
This is an wrapper of the interface class for OdTvGeometryData object.
\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvCircleArcDataWrapper : public OdTvCircleArcData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvCircleArcData)

protected:
  ODRX_HEAP_OPERATORS();

public:
  /** \details
  Set the three points on the circumference of the circle arc
  */
  virtual OdTvResult set(const OdGePoint3d &startPoint, const OdGePoint3d &middlePoint,
    const OdGePoint3d &endPoint);

  /** \details
  Set the start point on the circumference of the circle arc
  */
  virtual OdTvResult setStart(const OdGePoint3d &startPoint);

  /** \details
  Set the middle point on the circumference of the circle arc
  */
  virtual OdTvResult setMiddle(const OdGePoint3d &middlePoint);

  /** \details
  Set the end point on the circumference of the circle arc
  */
  virtual OdTvResult setEnd(const OdGePoint3d &middlePoint);

  /** \details
Returns the three points to the plane of the circle arc
*/
  virtual OdTvResult get(OdGePoint3d &startPoint, OdGePoint3d &middlePoint, OdGePoint3d &endPoint) const;

  /** \details
  Returns the start point to the plane of the circle arc
  */
  virtual OdTvPoint getStart(OdTvResult* rc = NULL) const;

  /** \details
  Returns the middle point to the plane of the circle arc
  */
  virtual OdTvPoint getMiddle(OdTvResult* rc = NULL) const;

  /** \details
  Returns the end point to the plane of the circle arc
  */
  virtual OdTvPoint getEnd(OdTvResult* rc = NULL) const;

  /** \details
  Set that circle arc should be filled-in (or not)
  */
  virtual OdTvResult setFilled(bool bFilled);

  /** \details
  Returns the filled state of the circle arc
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const;

  /** \details
  Set the thickness of the circle arc
  */
  virtual OdTvResult setThickness(double thickness);

  /** \details
  Returns the thickness of the circle arc
  */
  virtual double getThickness(OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the wedge defined by start, middle and end points on the circumference of the circle
*/
class OdTvCircleWedgeDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the circle wedge flags
  */
  enum circleWedgeFlags
  {
    kFilled = 1 << 16 // means that circle wedge will be filled in
  };

  OdTvCircleWedgeDataImpl()
    : OdTvGeometryDataImpl()
    , m_start(0., 0., 0.)
    , m_middle(0., 1., 0.)
    , m_end(0., 1., 1.)
    , m_thickness(0.)
  {}
  virtual ~OdTvCircleWedgeDataImpl() {}

  /* own methods */
  OdTvResult set(const OdTvPoint& startPoint, const OdTvPoint& middlePoint, const OdTvPoint& endPoint);
  void get(OdTvPoint& startPoint, OdTvPoint& middlePoint, OdTvPoint& endPoint) const;

  OdTvResult setStart(const OdTvPoint& start);
  OdTvResult setMiddle(const OdTvPoint& middle);
  OdTvResult setEnd(const OdTvPoint& end);

  OdTvPoint getStart() const;
  OdTvPoint getMiddle() const;
  OdTvPoint getEnd() const;

  void setFilled(bool bFilled);
  bool getFilled() const;

  void   setThickness(double thickness);
  double getThickness() const;

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                   entityGeometryDataType() const { return CircleWedge; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes  getFirstColorGeomType() const { return OdTvGeometryData::kEdges; }
  virtual OdTvGeometryData::GeometryTypes  getSecondColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual bool                              hasThickness() const { return fabs(m_thickness) > 1.0e-6; }
  virtual bool                              hasFilling() const { return GETBIT(m_flags, kFilled); }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:

  //data
  OdTvPoint   m_start;
  OdTvPoint   m_middle;
  OdTvPoint   m_end;

  // attributes
  double        m_thickness;
};

typedef OdTvSmartPtrInternal<OdTvCircleWedgeDataImpl> OdTvCircleWedgeDataImplPtr;

/** \details
This is an wrapper of the interface class for OdTvGeometryData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvCircleWedgeDataWrapper : public OdTvCircleWedgeData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvCircleWedgeData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Set the three points: start, middle and end points on the circumference of the circle
  */
  virtual OdTvResult set(const OdTvPoint& startPoint, const OdTvPoint& middlePoint, const OdTvPoint& endPoint);

  /** \details
  Set the start point for this circle wedge
  */
  virtual OdTvResult setStart(const OdTvPoint& start);

  /** \details
  Set the middle point for this circle wedge
  */
  virtual OdTvResult setMiddle(const OdTvPoint& middle);

  /** \details
  Set the end point for this circle wedge
  */
  virtual OdTvResult setEnd(const OdTvPoint& end);

  /** \details
  Returns the start, middle and end points on the circumference of the circle
  */
  virtual OdTvResult get(OdTvPoint& start, OdTvPoint& middle, OdTvPoint& end) const;

  /** \details
  Get the start point of this circle wedge
  */
  virtual OdTvPoint getStart(OdTvResult* rc = NULL) const;

  /** \details
  Get the middle point of this circle wedge
  */
  virtual OdTvPoint getMiddle(OdTvResult* rc = NULL) const;

  /** \details
  Get the end point of this circle wedge
  */
  virtual OdTvPoint getEnd(OdTvResult* rc = NULL) const;

  /** \details
  Set that circle wedge should be filled-in (or not)
  */
  virtual OdTvResult setFilled(bool bFilled);

  /** \details
  Returns the filled state of the circle wedge
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const;

  /** \details
  Set the thickness of the circle wedge
  */
  virtual OdTvResult setThickness(double thickness);

  /** \details
  Returns the thickness of the circle wedge
  */
  virtual double getThickness(OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the ellipse defined by three points
*/
class OdTvEllipseDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the ellipse flags
  */
  enum ellipseFlags
  {
    kFilled = 1 << 16 // means that ellipse will be filled in
  };

  OdTvEllipseDataImpl()
    : OdTvGeometryDataImpl()
    , m_thickness(0.)
    , m_centerPoint(0., 0., 0.)
    , m_minorPoint(0., 1., 0.)
    , m_majorPoint(1., 0., 0.)
  {}
  virtual ~OdTvEllipseDataImpl() {};

  //own methods
  OdTvResult set(const OdGePoint3d &centerPoint, const OdGePoint3d &majorPoint,
    const OdGePoint3d &minorPoint);
  OdTvResult setCenter(const OdGePoint3d &centerPoint);
  OdTvResult setMajor(const OdGePoint3d &majorPoint);
  OdTvResult setMinor(const OdGePoint3d &minorPoint);

  void get(OdGePoint3d &centerPoint, OdGePoint3d &majorPoint, OdGePoint3d &minorPoint) const;
  OdGePoint3d getCenter(OdTvResult* rc = NULL) const;
  OdGePoint3d getMajor(OdTvResult* rc = NULL) const;
  OdGePoint3d getMinor(OdTvResult* rc = NULL) const;

  void setFilled(bool bFilled);
  bool getFilled() const;

  void setThickness(double thickness);
  double getThickness() const;

  //OdTvGeometryDataImpl
  virtual TvGeometryType                  entityGeometryDataType() const { return Ellipse; }
  virtual bool                            draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes getFirstColorGeomType() const { return OdTvGeometryData::kEdges; }
  virtual OdTvGeometryData::GeometryTypes getSecondColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual bool                            hasThickness() const { return fabs(m_thickness) > 1.0e-6; }
  virtual bool                            hasFilling() const { return GETBIT(m_flags, kFilled); }
  virtual void                            read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                            write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:

  //data
  OdGePoint3d m_centerPoint;
  OdGePoint3d m_minorPoint;
  OdGePoint3d m_majorPoint;

  //attributes
  double m_thickness;
};

typedef OdTvSmartPtrInternal<OdTvEllipseDataImpl> OdTvEllipseDataImplPtr;


class OdTvEllipseDataWrapper : public OdTvEllipseData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvEllipseData)

protected:
  ODRX_HEAP_OPERATORS();

public:
  /** \details
  Set the three points on the circumference of the ellipse
  */
  virtual OdTvResult set(const OdGePoint3d &centerPoint, const OdGePoint3d &majorPoint,
    const OdGePoint3d &minorPoint);

  /** \details
  Set the center point on the circumference of the ellipse
  */
  virtual OdTvResult setCenter(const OdGePoint3d &centerPoint);

  /** \details
  Set the major point on the circumference of the ellipse
  */
  virtual OdTvResult setMajor(const OdGePoint3d &majorPoint);

  /** \details
  Set the minor point on the circumference of the ellipse
  */
  virtual OdTvResult setMinor(const OdGePoint3d &minorPoint);

  /** \details
  Returns the three points to the plane of the ellipse
  */
  virtual OdTvResult get(OdGePoint3d &centerPoint, OdGePoint3d &majorPoint,
    OdGePoint3d &minorPoint) const;

  /** \details
  Returns the center point to the plane of the ellipse
  */
  virtual OdTvPoint getCenter(OdTvResult* rc = NULL) const;

  /** \details
  Returns the major point to the plane of the ellipse
  */
  virtual OdTvPoint getMajor(OdTvResult* rc = NULL) const;

  /** \details
  Returns the minor point to the plane of the ellipse
  */
  virtual OdTvPoint getMinor(OdTvResult* rc = NULL) const;

  /** \details
  Set that ellipse should be filled-in (or not)
  */
  virtual OdTvResult setFilled(bool bFilled);

  /** \details
  Returns the filled state of the ellipse
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const;

  /** \details
  Set the thickness of the ellipse
  */
  virtual OdTvResult setThickness(double thickness);

  /** \details
  Returns the thickness of the ellipse
  */
  virtual double getThickness(OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the elliptic arc defined by center point, points of Intersection of axis with ellipse,
starting and ending angles of the elliptical arc
*/

class OdTvEllipticArcDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the elliptic arc flags
  */
  enum ellipticArcFlags
  {
    kFilled = 1 << 16 // means that elliptic arc will be filled in
  };

  OdTvEllipticArcDataImpl()
    : OdTvGeometryDataImpl()
    , m_center(0., 0., 0.)
    , m_major(2., 0., 0.)
    , m_minor(0., 1., 0.)
    , m_start(0.)
    , m_end(1.)
    , m_thickness(0.)
  {}
  virtual ~OdTvEllipticArcDataImpl() {}

  /* own methods */
  OdTvResult set(const OdTvPoint& centerPoint
    , const OdTvPoint& majorPoint
    , const OdTvPoint& minorPoint
    , const double start
    , const double end);
  void get(OdTvPoint& centerPoint
    , OdTvPoint& majorPoint
    , OdTvPoint& minorPoint
    , double& start
    , double& end) const;

  OdTvPoint getCenter() const;
  OdTvPoint	getMajor() const;
  OdTvPoint getMinor() const;
  double getStart() const;
  double getEnd() const;

  void setFilled(bool bFilled);
  bool getFilled() const;

  void   setThickness(double thickness);
  double getThickness() const;

  OdTvResult setCenter(const OdTvPoint& center);
  OdTvResult setMajor(const OdTvPoint& major);
  OdTvResult setMinor(const OdTvPoint& minor);
  void setStart(double start);
  void setEnd(double end);

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                   entityGeometryDataType() const { return EllipticArc; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes  getFirstColorGeomType() const { return OdTvGeometryData::kEdges; }
  virtual OdTvGeometryData::GeometryTypes  getSecondColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual bool                              hasThickness() const { return fabs(m_thickness) > 1.0e-6; }
  virtual bool                              hasFilling() const { return GETBIT(m_flags, kFilled); }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:

  //data
  OdTvPoint   m_center;
  OdTvPoint   m_major;
  OdTvPoint   m_minor;
  double      m_start;
  double      m_end;

  // attributes
  double        m_thickness;
};

typedef OdTvSmartPtrInternal<OdTvEllipticArcDataImpl> OdTvEllipticArcDataImplPtr;


/** \details
This is an wrapper of the interface class for OdTvGeometryData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvEllipticArcDataWrapper : public OdTvEllipticArcData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvEllipticArcData)

protected:
  ODRX_HEAP_OPERATORS();

public:
  /** \details
  Set center point, points of Intersection of axis with ellipse,
  starting and ending angles of the elliptical arc of the elliptic arc
  */
  virtual OdTvResult set(const OdTvPoint& centerPoint, const OdTvPoint& majorPoint, const OdTvPoint& minorPoint, double start, double end);

  /** \details
  Set the center point for this elliptic arc
  */
  virtual OdTvResult setCenter(const OdTvPoint& center);

  /** \details
  Set the major point for this elliptic arc
  */
  virtual OdTvResult setMajor(const OdTvPoint& major);

  /** \details
  Set the minor point for this elliptic arc
  */
  virtual OdTvResult setMinor(const OdTvPoint& minor);

  /** \details
  Set the start ang for this elliptic arc
  */
  virtual OdTvResult setStart(double start);

  /** \details
  Set the end ang for this elliptic arc
  */
  virtual OdTvResult setEnd(double end);

  /** \details
  Returns center point, points of Intersection of axis with ellipse,
  starting and ending angles of the elliptical arc of the elliptic arc
  */
  virtual OdTvResult get(OdTvPoint& center, OdTvPoint& major, OdTvPoint& minor, double& start, double& end) const;

  /** \details
  Get the center point of this elliptic arc
  */
  virtual OdTvPoint getCenter(OdTvResult* rc = NULL) const;

  /** \details
  Get the major point of this elliptic arc
  */
  virtual OdTvPoint getMajor(OdTvResult* rc = NULL) const;

  /** \details
  Get the minor point of this elliptic arc
  */
  virtual OdTvPoint getMinor(OdTvResult* rc = NULL) const;

  /** \details
  Get the start ang of this elliptic arc
  */
  virtual double getStart(OdTvResult* rc = NULL) const;

  /** \details
  Get the end ang of this elliptic arc
  */
  virtual double getEnd(OdTvResult* rc = NULL) const;

  /** \details
  Set that elliptic arc should be filled-in (or not)
  */
  virtual OdTvResult setFilled(bool bFilled);

  /** \details
  Returns the filled state of the elliptic arc
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const;

  /** \details
  Set the thickness of the elliptic arc
  */
  virtual OdTvResult setThickness(double thickness);

  /** \details
  Returns the thickness of the elliptic arc
  */
  virtual double getThickness(OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
  This class implements the polygon data
*/
class OdTvPolygonDataImpl : public OdTvGeometryDataImpl
{

public:

  /** \details
  Enum for the polygon flags
  */
  enum polygonFlags
  {
    kFilled           = 1 << 16,
    kFilled2D         = 1 << 17,
    kFilledSolid      = 1 << 18,
    kFilledEveryWhere = 1 << 19,
    kUseInverseNormal = 1 << 20
  };

  OdTvPolygonDataImpl() :OdTvGeometryDataImpl()
    , m_pPoints2D(0)
    , m_normal(OdTvVector::kZAxis)
    , m_thickness(0.)
    , m_elevation(0.)
    , m_nPoints(0)
  {
    SETBIT_1(m_flags, kFilledSolid);
  }

  virtual ~OdTvPolygonDataImpl() 
  {
    deletePoints();
  }

  //set/get
  OdTvResult set(const OdTvPointArray& pointArray);
  OdTvResult set(OdInt32 nPoints, const OdTvPoint* points);
  void get(OdTvPointArray& pointArray) const;
  int  getPointsCount() const;

  void setFilled(bool bFilled);
  bool getFilled() const;

  void   setThickness(double thickness);
  double getThickness() const;

  void setSpecificFillingMode(OdUInt8 flags);
  OdUInt8 getSpecificFillingMode() const;

  void setUseInverseNormal(bool bUse);
  bool getUseInverseNormal() const;

  virtual TvGeometryType                    entityGeometryDataType() const { return Polygon; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                              drawForMarkers(const OdTvEntityImpl* pParentEntitym, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes   getFirstColorGeomType() const { return OdTvGeometryData::kEdges; }
  virtual OdTvGeometryData::GeometryTypes   getSecondColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual bool                              hasThickness() const { return fabs(m_thickness) > 1.0e-6; }
  virtual bool                              hasFilling() const { return GETBIT(m_flags, kFilled);}
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                              copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:

  void deletePoints();

private:

  //data
  OdTvPoint2d*      m_pPoints2D;    // 2D points
  OdTvVector        m_normal;       // normal
  double            m_elevation;    // elevation
  double            m_thickness;    // thickness
  OdUInt32          m_nPoints;      // number of the polyline points
};

typedef OdTvSmartPtrInternal<OdTvPolygonDataImpl> OdTvPolygonDataImplPtr;


/** \details
  This is an wrapper of the interface class for OdTvGeometryData object.

  \remarks
  The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvPolygonDataWrapper : public OdTvPolygonData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvPolygonData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Replace the points of this Polygon with the specified points
  */
  virtual OdTvResult setPoints(const OdTvPointArray& pointArray);

  /** \details
  Replace the points of this Polygon with the specified points
  */
  virtual OdTvResult setPoints(OdInt32 nPoints, const OdTvPoint* points);

  /** \details
  Returns the number of points in this polygon
  */
  virtual int getPointsCount(OdTvResult* rc = NULL) const;

  /** \details
  Returns the points of this Polygon
  */
  virtual OdTvResult getPoints(OdTvPointArray& pointArray) const;

  /** \details
  Set that polygon should be filled-in (or not)
  */
  virtual OdTvResult setFilled(bool bFilled);

  /** \details
  Returns the filled state of the polygon
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const;

  /** \details
  Set filling mode. Set combimation of the flags 'kAs2D' and 'kAs3D'. Influences on something only if
  the polygon is filled-in
  */
  virtual OdTvResult setSpecificFillingMode(OdUInt8 flags);

  /** \details
  Returns the specific filling mode
  */
  virtual OdUInt8 getSpecificFillingMode(OdTvResult* rc = NULL) const;

  /** \details
  Set the thickness of the circle
  */
  virtual OdTvResult setThickness(double thickness);

  /** \details
  Returns the thickness of the circle
  */
  virtual double getThickness(OdTvResult* rc = NULL) const;

  /** \details
  Set that the polygon should use an inverse normal

  \remarks this flag can be usefull in the case of linetype with inclusions at the contour
  */
  virtual OdTvResult setUseInverseNormal(bool bUse);

  /** \details
  Returns the fag about using of the inverse normal
  */
  virtual bool getUseInverseNormal(OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the NURBS defined by degree, control points, weights, knots, start and end parameters
*/
class OdTvNurbsDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the nurbs flags
  */
  enum nurbsFlags
  {
    kFilledExtrusion = 1 << 16 // means that the extrusion will be filled in
  };

  OdTvNurbsDataImpl() : OdTvGeometryDataImpl(),
    m_thickness(0.),
    m_pControlPoints(0),
    m_pWeights(0),
    m_pKnots(0),
    m_degree(0),
    m_nPoints(0),
    m_nWeights(0),
    m_nKnots(0)
  {}

  virtual ~OdTvNurbsDataImpl()
  {
    deletePoints();
    deleteWeights();
    deleteKnots();
  }

  //set/get
  OdTvResult set(unsigned int degree, const OdTvPointArray& controlPoints, const OdDoubleArray& weights, const OdDoubleArray& knots, double start = 0., double end = 1.);
  OdTvResult set(unsigned int degree, unsigned int controlPointsNum, const OdTvPoint* controlPoints, const double* weights, unsigned int knotsNum, const double* knots, double start = 0., double end = 1.);
  void get(unsigned int& degree, OdTvPointArray& controlPoints, OdDoubleArray& weights, OdDoubleArray& knots, double& start, double& end) const;

  unsigned int getDegree() const;
  OdTvPointArray getControlPoints() const;
  OdDoubleArray getWeights() const;
  OdDoubleArray getKnots() const;
  void getStartEnd(double& start, double& end) const;

  OdTvResult editControlPoints(unsigned int startPos, const OdTvPointArray& controlPoints);
  OdTvResult editControlPoints(unsigned int startPos, unsigned int controlPointsNum, const OdTvPoint* controlPoints);
  OdTvResult editWeights(unsigned int startPos, const OdDoubleArray& weights);
  OdTvResult editWeights(unsigned int startPos, unsigned int weightsNum, const double* weights);
  OdTvResult editKnots(unsigned int startPos, const OdDoubleArray& knots);
  OdTvResult editKnots(unsigned int startPos, unsigned int knotsNum, const double* knots);

  OdTvResult setStartEnd(double start, double end);

  void       setThickness(double thickness, bool bFilled = false);
  double     getThickness(bool& bFilled) const;

  virtual TvGeometryType                    entityGeometryDataType() const { return Nurbs; }
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes   getFirstColorGeomType() const { return OdTvGeometryData::kPolylines; }
  virtual bool                              hasThickness() const { return fabs(m_thickness) > 1.0e-6; }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                              copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;


  virtual OdUInt64    getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;
  virtual OdTvResult  getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
                                   const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints,
                                   const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool        getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:
  OdTvResult checkParameters(unsigned int degree, const OdTvPointArray& controlPoints, const OdDoubleArray& weights, const OdDoubleArray& knots, double start, double end) const;
  OdTvResult checkParameters(unsigned int degree, unsigned int controlPointsNum, const OdTvPoint* controlPoints, unsigned int knotsNum, const double* knots, double start, double end) const;
  OdTvResult checkKnots(unsigned int degree, unsigned int knotsNum, const double* knots) const;
  double*    fillUniformKnots() const;

private:

  void deletePoints();
  void deleteWeights();
  void deleteKnots();

private:

  //data
  OdTvPoint* m_pControlPoints;
  double* m_pWeights;
  double* m_pKnots;
  double m_start;
  double m_end;

  //attributes
  double          m_thickness;

  //data 2
  OdUInt32 m_degree;
  OdUInt32 m_nPoints;
  OdUInt32 m_nWeights;
  OdUInt32 m_nKnots;
};

typedef OdTvSmartPtrInternal<OdTvNurbsDataImpl> OdTvNurbsDataImplPtr;

/** \details
This is an wrapper of the interface class for OdTvNurbsData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvNurbsDataWrapper : public OdTvNurbsData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvNurbsData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Set degree, control points, weights, knots, start and end parameters of the nurbs
  */
  virtual OdTvResult set(unsigned int degree, const OdTvPointArray& controlPoints, const OdDoubleArray& weights, const OdDoubleArray& knots, double start = 0., double end = 1.);

  /** \details
  Set degree, control points, weights, knots, start and end parameters of the nurbs
  */
  virtual OdTvResult set(unsigned int degree, unsigned int nControlPoints, const OdTvPoint* controlPoints, const double* weights, unsigned int nKnots, const double* knots, double start = 0., double end = 1.);

  /** \details
  Replace control points of the nurbs starting with startPos
  */
  virtual OdTvResult editControlPoints(unsigned int startPos, const OdTvPointArray& controlPoints);

  /** \details
  Replace control points of the nurbs starting with startPos
  */
  virtual OdTvResult editControlPoints(unsigned int startPos, unsigned int nControlPoints, const OdTvPoint* controlPoints);

  /** \details
  Replace weights of the nurbs starting with startPos
  */
  virtual OdTvResult editWeights(unsigned int startPos, const OdDoubleArray& weights);

  /** \details
  Replace weights of the nurbs starting with startPos
  */
  virtual OdTvResult editWeights(unsigned int startPos, unsigned int nWeights, const double* weights);

  /** \details
  Replace knots of the nurbs starting with startPos
  */
  virtual OdTvResult editKnots(unsigned int startPos, const OdDoubleArray& knots);

  /** \details
  Replace knots of the nurbs starting with startPos
  */
  virtual OdTvResult editKnots(unsigned int startPos, unsigned int nKnots, const double* knots);

  /** \details
  Set the start and end parameters of the nurbs
  */
  virtual OdTvResult setStartEnd(double start, double end);

  /** \details
  Get degree, control points, weights, knots, start and end parameters of the nurbs
  */
  virtual OdTvResult get(unsigned int& degree, OdTvPointArray& controlPoints, OdDoubleArray& weights, OdDoubleArray& knots, double& start, double& end) const;

  /** \details
  Get the degree of the nurbs
  */
  virtual unsigned int getDegree(OdTvResult* rc = NULL) const;

  /** \details
  Get the control points of the nurbs
  */
  virtual OdTvPointArray getControlPoints(OdTvResult* rc = NULL) const;

  /** \details
  Get the weights of the nurbs
  */
  virtual OdDoubleArray getWeights(OdTvResult* rc = NULL) const;

  /** \details
  Get the knots of the nurbs
  */
  virtual OdDoubleArray getKnots(OdTvResult* rc = NULL) const;

  /** \details
  Get the start and end parameters of the nurbs
  */
  virtual OdTvResult getStartEnd(double& start, double& end) const;

  /** \details
  Set the thickness of the polyline
  */
  virtual OdTvResult setThickness(double thickness, bool bFilled = false);

  /** \details
  Returns the thickness of the polyline
  */
  virtual double getThickness(bool& bFilled, OdTvResult* rc = NULL) const;
};

//***********************************************************************************************************************
//***********************************************************************************************************************
//***********************************************************************************************************************

/** \details
This class implements the infinite line defined by first and second points and type of line (ray or line)
*/
class OdTvInfiniteLineDataImpl : public OdTvGeometryDataImpl
{
public:

  /** \details
  Enum for the nurbs flags
  */
  enum infiniteLineFlags
  {
    kLine = 1 << 16 // means that the infinite line is the line (not ray). Ray otherwise
  };

  OdTvInfiniteLineDataImpl() : OdTvGeometryDataImpl()
    , m_first(0., 0., 0.)
    , m_second(1., 0., 0.)
  {}
  virtual ~OdTvInfiniteLineDataImpl() {};

  // set and get start and end points
  OdTvResult set(const OdTvPoint& firstPoint, const OdTvPoint& secondPoint);
  OdTvResult set(const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, OdTvInfiniteLineData::Type ilt);
  OdTvResult setFirst(const OdTvPoint& firstPoint);
  OdTvResult setSecond(const OdTvPoint& secondPoint);

  void get(OdTvPoint& firstPoint, OdTvPoint& secondPoint) const;
  OdTvPoint getFirst() const;
  OdTvPoint getSecond() const;

  // get/set type of infinite line
  void setType(OdTvInfiniteLineData::Type ilt);
  OdTvInfiniteLineData::Type getType() const;

  /* OdTvGeometryDataImpl */
  virtual TvGeometryType                   entityGeometryDataType() const { return InfiniteLine; };
  virtual bool                              draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual OdTvGeometryData::GeometryTypes  getFirstColorGeomType() const { return OdTvGeometryData::kPolylines; }
  virtual void                              read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                              write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                             copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  /* OdTvIObject methods implementation */
  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  virtual OdTvResult getSnapPoints(OdTvGeometryData::SnapMode snapMode, const OdTvPoint& pickPoint,
    const OdTvMatrix& xWorldToEye, OdTvPointArray& snapPoints, const OdTvMatrix* pTransform = NULL, double focalLength = -1.) const;

  virtual bool getSupportSnapMode(OdTvGeometryData::SnapMode snapMode, OdTvResult* rc = NULL) const;

private:
  OdTvPoint                               m_first;  // start point
  OdTvPoint                               m_second; // end point, through this point will pass line
};

typedef OdTvSmartPtrInternal<OdTvInfiniteLineDataImpl> OdTvInfiniteLineDataImplPtr;


/** \details
This is an wrapper of the interface class for OdTvGeometryData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvInfiniteLineDataWrapper : public OdTvInfiniteLineData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvInfiniteLineData)

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Set the start and end points
  */
  virtual OdTvResult set(const OdTvPoint& firstPoint, const OdTvPoint& secondPoint);

  /** \details
  Set the start point
  */
  virtual OdTvResult setFirst(const OdTvPoint& firstPoint);

  /** \details
  Set the second point
  */
  virtual OdTvResult setSecond(const OdTvPoint& secondPoint);

  /** \details
  Set type of line (ray or line)
  */
  virtual OdTvResult setType(Type ilt);

  /** \details
  Get the start and end points
  */
  virtual OdTvResult get(OdTvPoint& firstPoint, OdTvPoint& secondPoint) const;

  /** \details
  Get the start point
  */
  virtual OdTvPoint getFirst(OdTvResult* rc = NULL) const;

  /** \details
  Get the second point
  */
  virtual OdTvPoint getSecond(OdTvResult* rc = NULL) const;

  /** \details
  Get type of line (ray or line)
  */
  virtual Type getType(OdTvResult* rc = NULL) const;
};


#include "TD_PackPop.h"

#endif //_ODTV_ENTITYTYPIFIEDGEOMETRYDATA_H_INCLUDED_

