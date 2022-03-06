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

#ifndef _ODTV_ENTITYGEOMETRY_H_INCLUDED_
#define _ODTV_ENTITYGEOMETRY_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "Int32Array.h"
#include "DoubleArray.h"

/** \details
  Contains Visualize SDK declarations.
*/
namespace OdTv
{
	/** \details
    Enumeration for entity geometries types.
	*/
  enum OdTvGeometryDataType
  {
    kUndefinied                         = 0,  // Undefined geometry.
    kPolyline                           = 1,  // A polyline.
    kCircle                             = 2,  // A circle.
    kCircleWedge                        = 3,  // A circle wedge.
    kCircularArc                        = 4,  // A circular arc.
    kEllipse                            = 5,  // An ellipse.
    kEllipticArc                        = 6,  // An elliptical arc.
    kPolygon                            = 7,  // A polygon.
    kText                               = 8,  // Text.
    kShell                              = 9,  // A shell.
    kSphere                             = 10, // A sphere.
    kCylinder                           = 11, // A cylinder.
    kSubInsert                          = 12, // An insert sub-entity.
    kSubEntity                          = 13, // A sub-entity.
    kNurbs                              = 14, // A NURBS curve.
    kRasterImage                        = 15, // A raster image.
    kInfiniteLine                       = 16, // An infinite line.
    kMesh                               = 17, // A mesh.
    kPointCloud                         = 18, // A point cloud.
    kGrid                               = 19, // A grid.
    kColoredShape                       = 20, // A colored shape.
    kBox                                = 21, // A box.
    kBrep                               = 22, // A boundary representation object.
    kRcsPointCloud                      = 23, // A specific RCS file based point cloud object.
    kProgressiveMesh                    = 24  // A progressive mesh
  };
}


/** \details
  This is an interface class for an OdTvPolylineData object.
  \sa
  <link tv_geometry_lines, Work with Lines>
*/
class ODTV_EXPORT OdTvPolylineData : public OdTvIObject
{
public:

  /** \details
    Sets the points for this polyline.
    
    \param start	[in] A start point for the polyline.
    \param end	[in] An end point for the polyline.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the start and end points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPoints (const OdTvPoint& start, const OdTvPoint& end) = 0;

  /** \details
    Sets the points for this polyline.
    
    \param pointArray	[in] An array of points for the polyline.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the polyline points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPoints (const OdTvPointArray& pointArray) = 0;

  /** \details
    Sets the points for this polyline.
    
    \param nPoints	[in] A quantity of points to be set.
    \param points		[in] An array of points for the polyline represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the polyline points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPoints (OdInt32 nPoints, const OdTvPoint* points) = 0;

  /** \details
    Retrieves the quantity of points of this polyline.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the quantity of points as an OdInt32 value.
    \remarks
    If the quantity of points is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdInt32 getPointsCount (OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the points of this polyline.
    
    \param pointArray	[out] An array of points to be filled.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the polyline points are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getPoints (OdTvPointArray& pointArray) const = 0;

  /** \details
    Sets the normal vector for this polyline.
    
    \param normal [in] A pointer to a normal vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    The normal vector can be used for an extrusion or for the correct orientation of inclusion in linetypes.
    If the polyline normal vector is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setNormal(const OdTvVector* normal) = 0;

  /** \details
    Retrieves the normal vector of this polyline if it is set.
    
    \param normal [out] A normal vector.
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a bool value that shows whether the normal was previously set.
    \remarks 
    The normal vector can be used for an extrusion or for the correct orientation of inclusion in linetypes.
    If the polyline normal vector was previously set, the method returns true and the param normal is set to a corresponding value, 
    otherwise the method returns false and the param normal is unchanged.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual bool getNormal(OdTvVector& normal, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the thickness for this polyline.
    
    \param thickness 	[in] A double value representing a new thickness for the polyline.
    \param bFilled 	[in] A bool value that indicates whether a polyline is filled or not.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the polyline thickness is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setThickness(double thickness, bool bFilled = false) = 0;

  /** \details
    Retrieves the thickness value of the polyline.
    
    \param bFilled 	[out] A bool value that indicates whether a polyline is filled or not.
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the thickness of the polyline as a double value.
    \remarks
    If the polyline does not have a thickness, the method returns 0.0; otherwise it returns a non-zero positive value.
  */
  virtual double getThickness(bool& bFilled, OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the polyline geometry type and is used for storing and passing references to the polyline object.
*/
typedef OdTvSmartPtr<OdTvPolylineData> OdTvPolylineDataPtr;



/** \details
  This is an interface class for an OdTvCircleData object
  (defined by three points on the circumference of the circle).
  \sa
  <link tv_geometry_circles, Work with Circles>
*/
class ODTV_EXPORT OdTvCircleData : public OdTvIObject
{
public:

  /** \details
    Sets the center, radius and perpendicular to the plane of the circle.
    
    \param center	[in] A center point of the circle.
    \param radius	[in] A radius of the circle.
    \param normal	[in] A normal vector to an arbitrary plane in which the circle can be placed.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of the circle are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set (const OdTvPoint& center, double radius, const OdTvVector& normal) = 0;

  /** \details
    Sets the three points on the circumference of the circle.
    
    \param firstPoint		[in] The first point defining the circle.
    \param secondPoint	[in] The second point defining the circle.
    \param thirdPoint		[in] The third point defining the circle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points of the circle are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set (const OdTvPoint& firstPoint, const OdTvPoint& secondPoint, const OdTvPoint& thirdPoint) = 0;

  /** \details
    Sets the center point for this circle.
    
    \param center	[in] A center point of the circle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the center point of the circle is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setCenter (const OdTvPoint& center) = 0;
  
  /** \details
    Sets the normal vector for this circle.
    
    \param normal	[in] A normal vector to an arbitrary plane in which the circle can be placed.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vector of the circle is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setNormal (const OdTvVector& normal) = 0; 
  
  /** \details
    Set the radius for this circle.
    
    \param radius	[in] A radius of the circle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the radius of the circle is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setRadius (double radius) = 0; 

  /** \details
    Retrieves the center, radius and perpendicular to the plane of the circle.
    
    \param center	[out] A center point of the circle.
    \param radius	[out] A radius of the circle.
    \param normal	[out] A normal vector to an arbitrary plane in which the circle can be placed.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of the circle are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult get (OdTvPoint& center, double& radius, OdTvVector& normal) const = 0;

  /** \details
    Retrieves the center point of this circle.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the center point of the circle is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getCenter (OdTvResult* rc = NULL) const = 0;
  
  /** \details
    Retrieves the normal vector of this circle.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvVector class that represents a vector in 3D space.
    \remarks
    If the normal vector of the circle is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvVector getNormal (OdTvResult* rc = NULL) const = 0; 
  
  /** \details
    Retrieves the radius of this circle.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a radius of the circle as a double value.
    \remarks
    If the normal vector of the circle is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual double getRadius (OdTvResult* rc = NULL) const = 0; 

  /** \details
    Sets whether the circle should be filled in (or not).
    
    \param bFilled	[in] A bool value that indicates whether a circle should be filled in (or not).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter of the circle is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFilled(bool bFilled) = 0;

  /** \details
    Shows whether the circle is filled or not.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a bool value that shows if the circle is filled.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the thickness for this circle.
    
    \param thickness 	[in] A double value representing a new thickness for the circle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the circle thickness is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setThickness (double thickness) = 0;

  /** \details
    Retrieves the thickness value of the circle.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the thickness of the circle as a double value.
    \remarks
    If the circle does not have a thickness, the method returns 0.0; otherwise it returns a non-zero positive value.
  */
  virtual double getThickness (OdTvResult* rc = NULL) const = 0;

};

/** \details
  A data type that represents a smart pointer to an instance of the circle geometry type and is used for storing and passing references to the circle object.
*/
typedef OdTvSmartPtr<OdTvCircleData> OdTvCircleDataPtr;


/** \details
  This is an interface class for an OdTvCircleArcData object.
  \sa
  <link tv_geometry_arcs, Work with Arcs>
*/
class ODTV_EXPORT OdTvCircleArcData : public OdTvIObject
{
public:

  /** \details
    Sets three points on the circumference of the circle arc.
    
    \param startPoint		[in] A start point of the circle arc.
    \param middlePoint	[in] A middle point of the circle arc.
    \param endPoint		[in] An end point of the circle arc.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of the circle arc are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set(const OdGePoint3d &startPoint, const OdGePoint3d &middlePoint,
    const OdGePoint3d &endPoint) = 0;

  /** \details
    Sets the start point on the circumference of the circle arc.
    
    \param startPoint	[in] A start point of the circle arc.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the start point of the circle arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setStart(const OdGePoint3d &startPoint) = 0;

  /** \details
    Sets the middle point on the circumference of the circle arc.
    
    \param middlePoint	[in] A middle point of the circle arc.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the middle point of the circle arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMiddle(const OdGePoint3d &middlePoint) = 0;

  /** \details
    Sets the end point on the circumference of the circle arc.
    
    \param middlePoint	[in] An end point of the circle arc.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the end point of the circle arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEnd(const OdGePoint3d &middlePoint) = 0;

  /** \details
    Retrieves three points of the circle arc.
    
    \param startPoint		[out] A start point of the circle arc.
    \param middlePoint	[out] A middle point of the circle arc.
    \param endPoint		[out] An end point of the circle arc.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points of the circle arc are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult get(OdGePoint3d &startPoint, OdGePoint3d &middlePoint, OdGePoint3d &endPoint) const = 0;
  
  /** \details
    Retrieves the start point of the circle arc.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the start point of the circle arc is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getStart(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the middle point of the circle arc.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the middle point of the circle arc is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getMiddle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the end point of the circle arc.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the middle point of the circle arc is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getEnd(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets whether the circle arc should be filled in (or not).
    
    \param bFilled	[in] A bool value that indicates whether a circle arc should be filled in (or not).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter of the circle arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFilled(bool bFilled) = 0;

  /** \details
    Shows whether the circle arc is filled or not.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a bool value that shows if the circle arc is filled.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the thickness for this circle arc.
    
    \param thickness 	[in] A double value representing a new thickness for the circle arc.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the circle thickness is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setThickness(double thickness) = 0;

  /** \details
    Retrieves the thickness value of the circle arc.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the thickness of the circle arc as a double value.
    \remarks
    If the circle arc does not have a thickness, the method returns 0.0; otherwise it returns a non-zero positive value.
  */
  virtual double getThickness(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the circle arc geometry type and is used for storing and passing references to the circle arc object.
*/
typedef OdTvSmartPtr<OdTvCircleArcData> OdTvCircleArcDataPtr;


/** \details
  This is an interface class for an OdTvCircleWedgeData object
  (defined by three points: start, middle and end points on the circumference of the circle).
  \sa
  <link tv_geometry_arcs, Work with Arcs>
*/
class ODTV_EXPORT OdTvCircleWedgeData : public OdTvIObject
{
public:

  /** \details
    Sets the three points on the circumference of the circle wedge.
    
    \param startPoint		[in] A start point of the circle wedge.
    \param middlePoint	[in] A middle point of the circle wedge.
    \param endPoint		[in] An end point of the circle wedge.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of the circle wedge are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set(const OdTvPoint& startPoint, const OdTvPoint& middlePoint, const OdTvPoint& endPoint) = 0;

  /** \details
    Sets the start point on the circumference of the circle wedge.
    
    \param start	[in] A start point of the circle wedge.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the start point of the circle wedge is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setStart(const OdTvPoint& start) = 0;

  /** \details
    Sets the middle point on the circumference of the circle wedge.
    
    \param middle	[in] A middle point of the circle wedge.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the middle point of the circle wedge is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMiddle(const OdTvPoint& middle) = 0;

  /** \details
    Sets the end point on the circumference of the circle wedge.
    
    \param end	[in] An end point of the circle wedge.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the end point of the circle wedge is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEnd(const OdTvPoint& end) = 0;

  /** \details
    Retrieves three points of the circle wedge: start, middle and end points.
    
    \param startPoint		[out] A start point of the circle wedge.
    \param middlePoint	[out] A middle point of the circle wedge.
    \param endPoint		[out] An end point of the circle wedge.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points of the circle wedge are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult get(OdTvPoint& startPoint, OdTvPoint& middlePoint, OdTvPoint& endPoint) const = 0;

  /** \details
    Retrieves the start point of the circle wedge.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the start point of the circle wedge is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getStart(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the middle point of the circle wedge.
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the middle point of the circle wedge is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getMiddle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the end point of the circle wedge.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the middle point of the circle wedge is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getEnd(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets whether the circle wedge should be filled in (or not)
    
    \param bFilled	[in] A bool value that indicates whether a circle wedge should be filled in (or not).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter of the circle wedge is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFilled(bool bFilled) = 0;

  /** \details
    Shows whether the circle wedge is filled or not.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a bool value that shows if the circle wedge is filled.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the thickness for this circle wedge.
    
    \param thickness 	[in] A double value representing a new thickness for the circle wedge.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the circle thickness is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setThickness(double thickness) = 0;

  /** \details
    Retrieves the thickness value of the circle wedge.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the thickness of the circle wedge as a double value.
    \remarks
    If the circle wedge does not have a thickness, the method returns 0.0; otherwise it returns a non-zero positive value.
  */
  virtual double getThickness(OdTvResult* rc = NULL) const = 0;

};

/** \details
  A data type that represents a smart pointer to an instance of the circle wedge geometry type and is used for storing and passing references to the circle wedge object.
*/
typedef OdTvSmartPtr<OdTvCircleWedgeData> OdTvCircleWedgeDataPtr;


/** \details
  This is an interface class for an OdTvEllipseData object.
  \sa
  <link tv_geometry_ellipses, Work with Ellipses>
*/
class ODTV_EXPORT OdTvEllipseData : public OdTvIObject
{
public:
  /** \details
    Sets the three points on the circumference of the ellipse.
    
    \param centerPoint	[in] A center point of the ellipse.
    \param majorPoint		[in] A point of the ellipse that defines the major axis.
    \param minorPoint		[in] A point of the ellipse that defines the minor axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points of the ellipse are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set(const OdGePoint3d &centerPoint, const OdGePoint3d &majorPoint,
    const OdGePoint3d &minorPoint) = 0;

  /** \details
    Sets the center point on the circumference of this ellipse.
    
    \param centerPoint	[in] A center point of the ellipse.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the center point of the ellipse is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setCenter(const OdGePoint3d &centerPoint) = 0;

  /** \details
    Sets the major point on the circumference of this ellipse.
    
    \param majorPoint		[in] A point of the ellipse that defines the major axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the major point of the ellipse is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMajor(const OdGePoint3d &majorPoint) = 0;

  /** \details
    Sets the minor point on the circumference of this ellipse.
    
    \param minorPoint		[in] A point of the ellipse that defines the minor axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the minor point of the ellipse is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMinor(const OdGePoint3d &minorPoint) = 0;

  /** \details
    Retrieves the center, major and minor points of the ellipse.
    
    \param centerPoint	[out] A center point of the ellipse.
    \param majorPoint		[out] A point of the ellipse that defines the major axis.
    \param minorPoint		[out] A point of the ellipse that defines the minor axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points of the ellipse are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult get(OdGePoint3d &centerPoint, OdGePoint3d &majorPoint, OdGePoint3d &minorPoint) const = 0;

  /** \details
    Retrieves the center point of this ellipse.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the center point of the ellipse is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getCenter(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the major point of this ellipse.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the major point of the ellipse is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getMajor(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the minor point of this ellipse.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the minor point of the ellipse is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getMinor(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets whether the ellipse should be filled in (or not)
    
    \param bFilled	[in] A bool value that indicates whether the ellipse should be filled in (or not).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter of the ellipse is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFilled(bool bFilled) = 0;

  /** \details
    Shows whether the ellipse is filled or not.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a bool value that shows if the ellipse is filled.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the thickness for this ellipse.
    
    \param thickness 	[in] A double value representing a new thickness for the ellipse.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the ellipse thickness is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setThickness(double thickness) = 0;

  /** \details
    Retrieves the thickness value of the ellipse.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the thickness of the ellipse as a double value.
    \remarks
    If the ellipse does not have a thickness, the method returns 0.0; otherwise it returns a non-zero positive value.
  */
  virtual double getThickness(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the ellipse geometry type and is used for storing and passing references to the ellipse object.
*/
typedef OdTvSmartPtr<OdTvEllipseData> OdTvEllipseDataPtr;


/** \details
  This is an interface class for an OdTvEllipticArcData object
  (defined by a center point, axis points of intersection with ellipse, and
  start and end angles of the elliptical arc).
  \sa
  <link tv_geometry_arcs, Work with Arcs>
*/
class ODTV_EXPORT OdTvEllipticArcData : public OdTvIObject
{
public:
  /** \details
    Sets the center point, axis points of intersection with the ellipse, and
    
    start and end angles of the elliptical arc.
    \param centerPoint	[in] A center point of the elliptical arc.
    \param majorPoint		[in] A point of the ellipse that defines the major axis.
    \param minorPoint		[in] A point of the ellipse that defines the minor axis.
    \param start			[in] A double value representing a start angle from which the elliptical arc is drawn. Measured in radians.
    \param end			[in] A double value representing an end angle to which the elliptical arc is drawn. Measured in radians.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of the elliptical arc are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set(const OdTvPoint& centerPoint, const OdTvPoint& majorPoint, const OdTvPoint& minorPoint, double start, double end) = 0;

  /** \details
    Sets the center point of this elliptical arc.
    
    \param center		[in] A center point of the elliptical arc.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the center point of the elliptical arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setCenter(const OdTvPoint& center) = 0;

  /** \details
    Sets the major point on the circumference of this elliptical arc.
    
    \param major		[in] A point of the elliptical arc that defines the major axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the major point of the elliptical arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMajor(const OdTvPoint& major) = 0;

  /** \details
    Sets the minor point on the circumference of this elliptical arc.
    
    \param minor		[in] A point of the elliptical arc that defines the minor axis.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the minor point of the elliptical arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMinor(const OdTvPoint& minor) = 0;

  /** \details
    Sets the start angle for this elliptical arc.
    
    \param start		[in] A double value representing a start angle from which the elliptical arc is drawn. Measured in radians.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the start angle of the elliptical arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setStart(double start) = 0;

  /** \details
    Sets the end angle for this elliptical arc.
    
    \param end		[in] A double value representing an end angle to which the elliptical arc is drawn. Measured in radians.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the end angle of the elliptical arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEnd(double end) = 0;

  /** \details
    Retrieves the center point, axis points of intersection with ellipse,
    starting and ending angles of the elliptical arc of the elliptical arc.
    
    \param center [out] A center point of the elliptical arc.
    \param major  [out] A point of the ellipse that defines the major axis.
    \param minor  [out] A point of the ellipse that defines the minor axis.
    \param start  [out] A double value representing a start angle from which the elliptical arc is drawn. Measured in radians.
    \param end	  [out] A double value representing an end angle to which the elliptical arc is drawn. Measured in radians.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of the elliptical arc are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult get(OdTvPoint& center, OdTvPoint& major, OdTvPoint& minor, double& start, double& end) const = 0;

  /** \details
    Retrieves the center point of the elliptical arc.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the center point of the elliptical arc is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getCenter(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the major point of the elliptical arc.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the major point of the elliptical arc is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getMajor(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the minor point of the elliptical arc.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the minor point of the elliptical arc is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getMinor(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the start angle of the elliptical arc.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the start angle of the elliptical arc is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual double getStart(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the end angle of the elliptical arc.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the end angle of the elliptical arc is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual double getEnd(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets whether the elliptical arc should be filled-in (or not).
    
    \param bFilled	[in] A bool value that indicates whether the elliptical arc should be filled-in (or not).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter of the elliptical arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFilled(bool bFilled) = 0;

  /** \details
    Shows whether the elliptical arc is filled or not.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a bool value that shows if the elliptical arc is filled.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the thickness for this elliptical arc.
    
    \param thickness 	[in] A double value representing a new thickness for the elliptical arc.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the thickness of the elliptical arc is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setThickness(double thickness) = 0;

  /** \details
    Retrieves the thickness value of the elliptical arc.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the thickness of the elliptical arc as a double value.
    \remarks
    If the elliptical arc does not have a thickness, the method returns 0.0; otherwise it returns a non-zero positive value.
  */
  virtual double getThickness(OdTvResult* rc = NULL) const = 0;

};

/** \details
  A data type that represents a smart pointer to an instance of the elliptical arc geometry type and is used for storing and passing references to the elliptical arc object.
*/
typedef OdTvSmartPtr<OdTvEllipticArcData> OdTvEllipticArcDataPtr;


/** \details
  This is an interface class for an OdTvPolygonData object.
  \sa
  <link tv_geometry_polygons, Work with Polygons>
*/
class ODTV_EXPORT OdTvPolygonData : public OdTvIObject
{
public:

  /** \details
    Replaces the points of this polygon with the specified points.
    
    \param pointArray	[in] An array of points for the polygon.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the polyline points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPoints (const OdTvPointArray& pointArray) = 0;

  /** \details
    Replaces the points of this polygon with the specified points.
    
    \param nPoints	[in] A quantity of points to be set.
    \param points		[in] An array of points for the polygon represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the polyline points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPoints (OdInt32 nPoints, const OdTvPoint* points) = 0;

  /** \details
    Retrieves the quantity of points of this polygon.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the quantity of points as an OdInt32 value.
    \remarks
    If the quantity of points is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual int getPointsCount (OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the points of this polygon.
    
    \param pointArray	[out] An array of points to be filled.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the polygon points are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getPoints (OdTvPointArray& pointArray) const = 0;

  /** \details
    Sets whether the polygon should be filled in (or not).
    
    \param bFilled	[in] A bool value that indicates whether the polygon should be filled in (or not).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter of the polygon is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFilled(bool bFilled) = 0;

  /** \details
    Shows whether the polygon is filled or not.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a bool value that shows if the polygon is filled.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getFilled(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the filling mode, which is a combination of flags 'kFilled2D', 'kFilledSolid' and 'kFilledEveryWhere'. Takes effect only if 
    
    the polygon is filled in. The default value is 'kFilledSolid'.
    \param flags 	[in] An OdUInt8 value that represents the combination of flags that influence the filling mode.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the flag for the filling mode is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSpecificFillingMode(OdUInt8 flags) = 0;

  /** \details
    Retrieves the specific filling mode.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an OdUInt8 value that represents the combination of flags that influence the filling mode.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdUInt8 getSpecificFillingMode(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets whether the polygon should use an inverse normal.
    
    \param bUse 	[in] A bool value that specifies if the polygon uses an inverse normal vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    The method can be useful for linetypes with inclusions at the contour.
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setUseInverseNormal(bool bUse) = 0;

  /** \details
    Checks whether the polygon uses an inverse normal.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a bool value that shows if the polygon uses an inverse normal.
    \remarks 
    The method can be useful for linetypes with inclusions at the contour.
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual bool getUseInverseNormal(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the polygon geometry type and is used for storing and passing references to the polygon object.
*/
typedef OdTvSmartPtr<OdTvPolygonData> OdTvPolygonDataPtr;


/** \details
  This is an interface class for an OdTvNurbsData object.
  \sa
  <link tv_geometry_nurbs, Work with NURBS>
*/
class ODTV_EXPORT OdTvNurbsData : public OdTvIObject
{
public:

  /** \details
    Sets the degree, control points, weights, knots, and start and end parameters of the NURBS.
    
    \param degree         [in] A positive integer value that controls the number of points per interval that are available for modeling.
    \param controlPoints  [in] An array of control points that define the track along which the NURBS is drawn.
    \param weights        [in] An array of double values that control the curve shape near corresponding control points.
    \param knots          [in] An array of knots for the NURBS.
    \param start          [in] Start parameter. Defines the start of the visible NURBS segment. Range is from 0.0 to 1.0. Must be less than the value of the end parameter.
    \param end            [in] End parameter. Defines the end of the visible NURBS segment. Range is from 0.0 to 1.0. Must be greater than the value of the start parameter.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of the NURBS are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set(unsigned int degree, const OdTvPointArray& controlPoints, const OdDoubleArray& weights, const OdDoubleArray& knots, double start = 0., double end = 1.) = 0;

  /** \details
    Sets the degree, control points, weights, knots, and start and end parameters of the NURBS.
    
    \param degree         [in] A positive integer value that controls the number of points per interval that are available for modeling.
    \param nControlPoints [in] A positive integer value that defines the quantity of control points.
    \param controlPoints  [in] A pointer to an array of control points that define the track along which the NURBS is drawn.
    \param weights        [in] A pointer to an array of double values that control the curve shape near corresponding control points.
    \param nKnots         [in] A positive integer value that defines the quantity of knots.
    \param knots          [in] A pointer to an array of knots for the NURBS.
    \param start          [in] Defines the start of the visible NURBS segment. Range is from 0.0 to 1.0. Must be less than the value of the end parameter.
    \param end            [in] Defines the end of the visible NURBS segment. Range is from 0.0 to 1.0. Must be greater than the value of the start parameter.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of the NURBS are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set(unsigned int degree, unsigned int nControlPoints, const OdTvPoint* controlPoints, const double* weights, unsigned int nKnots, const double* knots, double start = 0., double end = 1.) = 0;

  /** \details
    Replaces control points of the NURBS starting with startPos.
    
    \param startPos       [in] A positive integer value that defines the starting position for replacement of control points.
    \param controlPoints  [in] An array of control points that define the track along which the NURBS is drawn.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new control points of the NURBS are successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editControlPoints(unsigned int startPos, const OdTvPointArray& controlPoints) = 0;

  /** \details
    Replaces control points of the NURBS starting with startPos.
    
    \param startPos       [in] A positive integer value that defines the starting position for replacement of control points.
    \param nControlPoints [in] A positive integer value that defines the quantity of control points.
    \param controlPoints  [in] A pointer to an array of control points that define the track along which the NURBS is drawn.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new control points of the NURBS are successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editControlPoints(unsigned int startPos, unsigned int nControlPoints, const OdTvPoint* controlPoints) = 0;

  /** \details
    Replaces weights of the NURBS starting with startPos.
    
    \param startPos       [in] A positive integer value that defines the starting position for replacement of weights.
    \param weights        [in] An array of double values that control the curve shape near corresponding control points.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the weight values of the NURBS are successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editWeights(unsigned int startPos, const OdDoubleArray& weights) = 0;

  /** \details
    Replaces weights of the NURBS starting with startPos.
    
    \param startPos       [in] A positive integer value that defines the starting position for replacement of weights.
    \param nWeights       [in] A quantity of array elements of weight values.
    \param weights        [in] An array of double values that control the curve shape near corresponding control points.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the weight values of the NURBS are successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editWeights(unsigned int startPos, unsigned int nWeights, const double* weights) = 0;

  /** \details
    Replaces knots of the NURBS starting with startPos.
    
    \param startPos       [in] A positive integer value that defines the starting position for replacement of knots.
    \param knots          [in] An array of knots for NURBS.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the knots of the NURBS are successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editKnots(unsigned int startPos, const OdDoubleArray& knots) = 0;

  /** \details
    Replaces knots of the NURBS starting with startPos.
    
    \param startPos       [in] A positive integer value that defines the starting position for replacement of knots.
    \param nKnots         [in] A positive integer value that defines the quantity of knots.
    \param knots          [in] A pointer to an array of knots for the NURBS.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the knots of the NURBS are successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editKnots(unsigned int startPos, unsigned int nKnots, const double* knots) = 0;

  /** \details
    Sets the start and end parameters of the NURBS.
    
    \param start          [in] Defines the start of the visible NURBS segment. Range is from 0.0 to 1.0. Must be less than the value of the end parameter.
    \param end            [in] Defines the end of the visible NURBS segment. Range is from 0.0 to 1.0. Must be greater than the value of the start parameter.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of the NURBS are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setStartEnd(double start, double end) = 0;

  /** \details
    Retrieves the degree, control points, weights, knots, and start and end parameters of the NURBS.
    
    \param degree         [out] A positive integer value that controls the number of points per interval that are available for modeling.
    \param controlPoints  [out] An array of control points that define the track along which the NURBS is drawn.
    \param weights        [out] An array of double values that control the curve shape near corresponding control points.
    \param knots          [out] An array of knots for the NURBS.
    \param start          [out] Start parameter. Defines the start of the visible NURBS segment. Range is from 0.0 to 1.0. Must be less than the value of the end parameter.
    \param end            [out] End parameter. Defines the end of the visible NURBS segment. Range is from 0.0 to 1.0. Must be greater than the value of the start parameter.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of the NURBS are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult get(unsigned int& degree, OdTvPointArray& controlPoints, OdDoubleArray& weights, OdDoubleArray& knots, double& start, double& end) const = 0;

  /** \details
    Retrieves the degree of the NURBS.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an unsigned integer value that represents the number of points per interval that are available for modeling.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual unsigned int getDegree(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the control points of the NURBS.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an OdTvPointArray that represents an array of 3D points.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPointArray getControlPoints(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the weights of the NURBS.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an OdDoubleArray that stores double values for weights of points.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdDoubleArray getWeights(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the knots of the NURBS.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an OdDoubleArray that stores double values for knots.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdDoubleArray getKnots(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the start and end parameters of the NURBS.
    
    \param start  [out] Represents the start of the visible NURBS segment. Range is from 0.0 to 1.0.
    \param end    [out] Represents the end of the visible NURBS segment. Range is from 0.0 to 1.0.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvResult getStartEnd(double& start, double& end) const = 0;

  /** \details
    Sets the thickness of the NURBS.
    
    \param thickness 	[in] A double value representing a new thickness for the NURBS.
    \param bFilled 	[in] A bool value that indicates whether the NURBS is filled or not.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvResult setThickness(double thickness, bool bFilled = false) = 0;

  /** \details
    Retrieves the thickness of the NURBS.
    
    \param bFilled 	[out] A bool value that indicates whether the NURBS is filled or not.
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the thickness of the NURBS as a double value.
    \remarks
    If the method finishes successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual double getThickness(bool& bFilled, OdTvResult* rc = NULL) const = 0;

};

/** \details
  A data type that represents a smart pointer to an instance of the NURBS geometry type and is used for storing and passing references to the NURBS object.
*/
typedef OdTvSmartPtr<OdTvNurbsData> OdTvNurbsDataPtr;


/** \details
  This is an interface class for an OdTvInfiniteLineData object.
  \sa
  <link tv_geometry_lines, Work with Lines>
*/
class ODTV_EXPORT OdTvInfiniteLineData : public OdTvIObject
{
public:
  /** \details
    Enumeration for entity geometry types.
  */
  enum Type
  {
    kRay = 0,  // A ray entity type.
    kLine = 1  // A line entity type.
  };

  /** \details
    Sets the start and end points for the infinite line.
    
    \param startPoint		[in] A starting point of the infinite line.
    \param endPoint		[in] An ending point of the infinite line.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points of the infinite line are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set(const OdTvPoint& startPoint, const OdTvPoint& endPoint) = 0;

  /** \details
    Sets the first point for the infinite line.
    
    \param firstPoint		[in] The first point of the infinite line.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the first point of the infinite line is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFirst(const OdTvPoint& firstPoint) = 0;

  /** \details
    Sets the second point for the infinite line.
    
    \param secondPoint	[in] The second point of the infinite line.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the second point of the infinite line is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSecond(const OdTvPoint& secondPoint) = 0;

  /** \details
    Sets the type of infinite line (ray or line).
    
    \param ilt			[in] The type of infinite line. Possible values: kRay, kLine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the type of infinite line is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setType(Type ilt) = 0;

  /** \details
    Retrieves the start and end points of the infinite line.
    
    \param firstPoint		[out] The start point of the infinite line.
    \param secondPoint	[out] The end point of the infinite line.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points of the infinite line are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult get(OdTvPoint& firstPoint, OdTvPoint& secondPoint) const = 0;

  /** \details
    Retrieves the start point of the infinite line.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the first point of the infinite line is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvPoint getFirst(OdTvResult* rc = NULL) const = 0;

 /** \details
    Retrieves the end point of the infinite line.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the second point of the infinite line is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvPoint getSecond(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the type of the infinite line (ray or xline).
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a Type value that shows the type of the line.
    \remarks
    If the type of infinite line is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual Type getType(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the infinite line geometry type and is used for storing and passing references to the infinite line object.
*/
typedef OdTvSmartPtr<OdTvInfiniteLineData> OdTvInfiniteLineDataPtr;


#endif // _ODTV_ENTITYGEOMETRY_H_INCLUDED_

