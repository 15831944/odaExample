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

#ifndef _ODTV_ENTITYGEOMETRY3D_H_INCLUDED_
#define _ODTV_ENTITYGEOMETRY3D_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "DoubleArray.h"
#include "TvStatistics.h"

/** \details
  This is an interface class for an OdTvCylinderData object.
  \sa
  <link tv_geometry_cylinders, Work with Cylinders>
*/
class ODTV_EXPORT OdTvCylinderData : public OdTvIObject
{
public:

  /** \details
    Cylinder capping types.
  */
  enum Capping
  {
    kNone = 0,    // No capping.
    kFirst = 1,   // First capping.
    kSecond = 2,  // Second capping.
    kBoth = 3     // Both capping.
  };
  
  /** \details
    Cylinder deviation types.
  */
  enum Deviation
  {
    kAuto         = 0,  // Auto deviation.
    kFixed        = 1,  // Fixed deviation.
    kNotMoreThan  = 2,  // Not more than.
  };

  /** \details
    Sets params of the cylinder.
    
    \param point1 [in] First point of the cylinder.
    \param point2 [in] Second point of the cylinder.
    \param radius [in] Radius of the cylinder.
    \param caps  	[in] Caps for the cylinder.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified cylinder parameters are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setParam(const OdTvPoint& point1, const OdTvPoint& point2, double& radius, const Capping& caps) = 0;

  /** \details
    Sets params of the cylinder.
    
    \param points	[in] An array of points for the cylinder.
    \param radii 	[in] An array of radii (start and end radii).
    \param caps  	[in] Caps for the cylinder.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified cylinder parameters are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setParam(const OdTvPointArray& points, const OdDoubleArray& radii, const Capping& caps) = 0;

  /** \details
    Retrieves params of the cylinder.
    
    \param points	[out] An array of points for the cylinder.
    \param radii 	[out] An array of radii (start and end radii).
    \param cap  	[out] Caps for the cylinder.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified cylinder parameters are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getParam(OdTvPointArray& points, OdDoubleArray& radii, Capping& cap) = 0;

  /** \details
    Set the points for this cylinder.
    
    \param points	[in] An array of points for the cylinder.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the cylinder points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPoints(const OdTvPointArray& points) = 0;

  /** \details
    Set the radius for this cylinder.
    
    \param radius	[in] An array of radii for the cylinder.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the cylinder radii are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setRadii(const OdDoubleArray& radius) = 0;

  /** \details
    Set the capping for this cylinder.
    
    \param caps	[in] A type of capping for the cylinder.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the cylinder capping is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setCaps(const Capping& caps) = 0;

  /** \details
    Set the deviation for this cylinder.
    
    \param deviationType [in] A type of deviation for the cylinder.
    \param value         [in] A value of deviation for the cylinder (used for kFixed and kNotMoreThan types)
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the cylinder deviation is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setDeviation(const Deviation& deviationType, OdUInt32 value) = 0;

  /** \details
    Retrieves the points of this cylinder.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of OdTvPointArray type that contains the points of this cylinder.
    \remarks
    If the cylinder points are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvPointArray getPoints(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the radii of this Cylinder.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of OdDoubleArray type that contains the radii of this cylinder.
    \remarks
    If the cylinder radii are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdDoubleArray getRadii(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves capping data of this cylinder.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of Capping type that contains information about the capping of this cylinder.
    \remarks
    If the cylinder capping data is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual Capping getCaps(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves deviation data of this cylinder.
    
    \param value  [out] Deviation value for the cylinder.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of Deviation type that contains information about the deviation type of this cylinder.
    \remarks
    If the cylinder deviation data is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual Deviation getDeviation(OdUInt32& value, OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the cylinder geometry type and used for storing and passing references to the cylinder object.
*/
typedef OdTvSmartPtr<OdTvCylinderData> OdTvCylinderDataPtr;


/** \details
  This is an interface class for an OdTvSphereData object.
  \sa
  <link tv_geometry_spheres, Work with Spheres>
*/
class ODTV_EXPORT OdTvSphereData : public OdTvIObject
{
public:

  /** \details
    Sphere deviation types.
  */
  enum Deviation
  {
    kAuto         = 0,  // Auto deviation.
    kFixed        = 1,  // Fixed deviation.
    kNotMoreThan  = 2,  // Not more than value.
  };

  /** \details
    Sets params of the sphere.
    
    \param center 		[in] The center point for the sphere.
    \param radius 		[in] The radius of the sphere.
    \param axis 			[in] The axis of the sphere.
    \param primeMeridian	[in] The prime meridian of the sphere.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified sphere parameters are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setParam(const OdTvPoint& center, double radius, const OdTvVector& axis = OdTvVector(0., 1., 0), const OdTvVector& primeMeridian = OdTvVector(1., 0., 0)) = 0;

  /** \details
    Sets the radius of the sphere.
    
    \param radius	[in] The radius for the sphere.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the sphere radius is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setRadius(double radius) = 0;

  /** \details
    Sets the center point of the sphere.
    
    \param center	[in] The center point for the sphere.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the sphere center point is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setCenter(const OdTvPoint& center) = 0;

  /** \details
    Sets the basis of the sphere.
    
    \param axis			[in] The axis of the sphere.
    \param primeMeridian	[in] The prime meridian of the sphere.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the sphere basis is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBasis(const OdTvVector& axis, const OdTvVector& primeMeridian) = 0;

  /** \details
    Set the deviation for this sphere.
    
    \param deviationType [in] A type of deviation for the sphere.
    \param value         [in] A value of deviation for the cylinder (used for kFixed and kNotMoreThan types)
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the sphere deviation is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setDeviation(const Deviation& deviationType, OdUInt32 value) = 0;

  /** \details
    Retrieves params of the sphere.
    
    \param center 		[out] The center point for the sphere.
    \param radius 		[out] The radius of the sphere.
    \param axis 			[out] The axis of the sphere.
    \param primeMeridian	[out] The prime meridian of the sphere.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified sphere parameters are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getParam(OdTvPoint& center, double& radius, OdTvVector& axis, OdTvVector& primeMeridian) const = 0;

  /** \details
    Retrieves the radius of this sphere.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a double value representing the radius this sphere.
    \remarks
    If the sphere radius is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual double getRadius(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the center point of this sphere.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the center point of the sphere is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvPoint getCenter(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the sphere basis data.
    
    \param axis           [out] A placeholder for a vector that represents the basic axis.
    \param primeMeridian  [out] A placeholder for a vector that represents the prime meridian.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the basis data of the sphere is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getBasis(OdTvVector& axis, OdTvVector& primeMeridian) const = 0;

  /** \details
    Retrieves deviation data of this sphere.
    
    \param value  [out] Deviation value for the sphere.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of Deviation type that contains information about the deviation type of this sphere.
    \remarks
    If the sphere deviation data is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual Deviation getDeviation(OdUInt32& value, OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the sphere geometry type and used for storing and passing references to the sphere object.
*/
typedef OdTvSmartPtr<OdTvSphereData> OdTvSphereDataPtr;


/** \details
  This is an interface class for an OdTvBoxData object.
  \sa
  <link tv_geometry_boxes, Work with Boxes>
*/
class ODTV_EXPORT OdTvBoxData : public OdTvIObject
{
public:

  /** \details
    Sets parameters of the box.
    
    \param centerPt   [in]    Center point of the box.
    \param dLength    [in]    Length of the box.
    \param dWidth     [in]    Width of the box.
    \param dHeight    [in]    Height of the box.
    \param baseNormal [in]    Height direction (defines base plane).
    \param lengthDir  [in]    Length direction.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified box parameters are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setParam(const OdTvPoint& centerPt, double dLength, double dWidth, double dHeight, const OdTvVector& baseNormal = OdTvVector::kZAxis, const OdTvVector& lengthDir = OdTvVector::kXAxis) = 0;

  /** \details
    Retrieves parameters of the box.
    
    \param centerPt        [out]  Center point of the box.
    \param dLength         [out]  Length of the box.
    \param dWidth          [out]  Width of the box.
    \param dHeight         [out]  Height of the box.
    \param baseNormal      [out]  Height direction (defines base plane).
    \param lengthDir       [out]  Length direction.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified sphere parameters are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getParam(OdTvPoint& centerPt, double& dLength, double& dWidth, double& dHeight, OdTvVector& baseNormal, OdTvVector& lengthDir) const = 0;

  /** \details
    Sets the center point for this box.
    
    \param point		[in] A center point for the box.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the center point of the box is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setCenterPoint(const OdTvPoint& point) = 0;

  /** \details
    Retrieves the center point of this box.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the center point of the box is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvPoint getCenterPoint(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the length for this box.
    
    \param dLength	[in] The length for the box.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the length of the box is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setLength(double dLength) = 0;

  /** \details
    Retrieves the length of this box.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the length of the box as a double value.
    \remarks
    If the length of the box is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual double getLength(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the width for this box.
    
    \param dWidth		[in] The width for the box.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the width of the box is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setWidth(double dWidth) = 0;

  /** \details
    Retrieves the width of this box.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the width of the box as a double value.
    \remarks
    If the width of the box is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual double getWidth(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the height for this box.
    
    \param dHeight	[in] The height for the box.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the height of the box is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setHeight(double dHeight) = 0;

  /** \details
    Retrieves the height of this box.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the height of the box as a double value.
    \remarks
    If the height of the box is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual double getHeight(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the normal to base plane of this box.
    
    \param baseNormal	[in] Normal vector for base plane of the box.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal to base plane of the box is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBaseNormal(const OdTvVector& baseNormal) = 0;

  /** \details
    Retrieves a normal vector to base plane of this box.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvVector class that represents a vector in 3D space.
    \remarks
    If the normal vector of the box base is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvVector getBaseNormal(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the length direction for this box.
    
    \param lengthDir	[in] A vector that specifies a length direction of the box.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the length direction of the box is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setLengthDirection(const OdTvVector& lengthDir) = 0;

  /** \details
    Retrieves the length direction data of this box.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvVector class that represents a vector in 3D space.
    \remarks
    If the length direction vector of the box base is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvVector getLengthDirection(OdTvResult* rc = NULL) const = 0;

};

/** \details
  A data type that represents a smart pointer to an instance of the box geometry type and used for storing and passing references to the box object.
*/
typedef OdTvSmartPtr<OdTvBoxData> OdTvBoxDataPtr;


/** \details
  This is an interface class for an OdTvPointCloudData object.
*/
class ODTV_EXPORT OdTvPointCloudData : public OdTvIObject
{
public:
  /** \details
    Sets an array of points for the point cloud.
    
    \param points		[in] An array of points for the point cloud.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setParam(const OdTvPointArray& points) = 0;

  /** \details
    Sets an array of points for the point cloud.
    
    \param nPoints	[in] A quantity of points.
    \param points		[in] An array of points represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setParam(OdInt32 nPoints, const OdTvPoint* points) = 0;

  /** \details
    Retrieves the array of points of the point cloud.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPointArray class that contains the points of the point cloud.
    \remarks
    If the points of the point cloud are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvPointArray getParam(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the points of the point cloud.
    
    \param pointArray	[out] An array of points to be filled.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the point cloud points are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getParam(OdTvPointArray& points) const = 0;

  /** \details
    Retrieves the quantity of points of the point cloud.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPointArray class that contains points of the point cloud.
    \remarks
    If the quantity of points is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdInt32 getPointsCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the coordinates for a specified point of the point cloud.
    
    \param ind 	[in] A point index.
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents the coordinates information.
    \remarks
    If the rc parameter is not null and the coordinates data is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
*/
  virtual OdTvPoint getPointCoo(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Replaces points of the point cloud starting with startPos.
    
    \param startPos	[in] A starting position from which the point replacement is applied.
    \param points		[in] An array of points.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points are successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editPointsViaRange(OdUInt32 startPos, const OdTvPointArray& points) = 0;

  /** \details
    Replaces points of the point cloud starting with startPos.
    
    \param startPos	[in] A starting position from which the point replacement is applied.
    \param nPoints	[in] A quantity of points for replacement.
    \param points		[in] An array of points represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points are successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editPointsViaRange(OdUInt32 startPos, OdUInt32 nPoints, const OdTvPoint* points) = 0;

  /** \details
    Replaces points of the point cloud according to a points list.
    
    \param indPoints  [in] An array of point indexes for replacement.
    \param points  	[in] An array of points to be replaced with.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points are successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editPointsViaList(const OdInt32Array& indPoints, const OdTvPointArray& points) = 0;

  /** \details
    Replaces points of the point cloud according to a points list.
    
    \param nPoints    [in] A quantity of points for replacement.
    \param indPoints  [in] An array of point indexes represented with a pointer to the first array element.
    \param points     [in] An array of points to be replaced represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points are successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editPointsViaList(OdUInt32 nPoints, const OdUInt32* indPoints, const OdTvPoint* points) = 0;

  /** \details
    Append an array of points to point cloud points.
    
    \param points   [in] An array of points for the point cloud.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points are successfully appended, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult appendPoints(const OdTvPointArray& points) = 0;

  /** \details
    Append an array of points to point cloud points.
    
    \param nPoints	[in] A quantity of points.
    \param points		[in] An array of points represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified points are successfully appended, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult appendPoints(OdInt32 nPoints, const OdTvPoint* points) = 0;

  /** \details
    Sets the point size.
    
    \param pointSize  [in] A size of a point.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the size of points is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointSize(OdInt32 pointSize) = 0;
  
  /** \details
    Retrieves the point size.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a point size as an OdInt32 value.
    \remarks
    If the size of points is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdInt32 getPointSize(OdTvResult* rc = NULL) const = 0;

  /**
  Point colors management
  */
  
  /** \details
    Sets colors for a list of points of the point cloud.
    
    \param nCount     [in] A quantity of points for which to set color.
    \param indPoints  [in] A pointer to an array of point indexes.
    \param colors     [in] A pointer to an array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointColorsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvRGBColorDef* colors) = 0;
  
  /** \details
    Sets colors for a list of points of the point cloud.
    
    \param indPoints  [in] An array of point indexes.
    \param colors     [in] An array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointColorsViaList(const OdInt32Array& indPoints, const OdTvRGBColorDefArray& colors) = 0;
  
  /** \details
    Sets the color for a list of points of the point cloud.
    
    \param nCount     [in] A quantity of points for which to set color.
    \param indPoints  [in] A pointer to an array of point indexes.
    \param color      [in] A color definition object to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified points is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointColorsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvRGBColorDef& color) = 0;
  
  /** \details
    Sets the color for a list of points of the point cloud.
    
    \param indPoints  [in] An array of point indexes.
    \param color     	[in] A color definition object to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified points is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointColorsViaList(const OdInt32Array& indPoints, const OdTvRGBColorDef& color) = 0;

  /** \details
    Sets a color for a range of points of the point cloud.
    
    \param indStart [in] A starting index for replacement.
    \param nCount   [in] A quantity of points for replacement.
    \param color    [in] A color definition object to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified points is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color) = 0;
  
  /** \details
    Sets colors for a range of points of the point cloud.
    
    \param indStart [in] A starting index for replacement.
    \param colors   [in] An array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointColorsViaRange(OdInt32 indStart, const OdTvRGBColorDefArray& colors) = 0;
  
  /** \details
    Sets colors for a range of points of the point cloud.
    
    \param indStart [in] A starting index for replacement.
    \param nCount   [in] A quantity of points for replacement.
    \param colors   [in] An array of color definitions represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors) = 0;

  
  /** \details
    Retrieves the colors for a range of points of the point cloud.
    
    \param indStart [in] A starting index of the range.
    \param nCount   [in] A quantity of points in the range.
    \param colors   [out] An array of color definition objects to be filled.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified points are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getPointColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvRGBColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves the colors for a range of vertexes of the point cloud.
    
    \param indPoints [in] An array of point indexes.
    \param colors    [out] An array of color definition objects to be filled.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified points are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getPointColorsViaList(const OdInt32Array& indPoints, OdTvRGBColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves the color for a specified point of the point cloud.
    
    \param ind 	[in] A point index.
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvRGBColorDef class that represents the color information.
    \remarks
    If the rc parameter is not null and the color data is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvRGBColorDef getPointColor(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /**
  Point normals management.
  */
  
  /** \details
    Sets normal vectors for a list of points of the point cloud.
    
    \param nCount     [in] A quantity of points.
    \param indPoints  [in] A pointer to an array of point indexes.
    \param vectors    [in] An array of normal vectors represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vectors for specified points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointNormalsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvVector* vectors) = 0;
  
  /** \details
    Sets normal vectors for a list of points of the point cloud.
    
    \param indPoints  [in] A pointer to an array of point indexes.
    \param vectors    [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vectors for specified points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointNormalsViaList(const OdInt32Array& indPoints, const OdTvVectorArray& vectors) = 0;
  
  /** \details
    Sets a normal vector for a list of points of the point cloud.
    
    \param nCount     [in] A quantity of points.
    \param indPoints  [in] A pointer to an array of point indexes.
    \param vector    	[in] A normal vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vector for specified points is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointNormalsViaList(OdInt32 nCount, const OdInt32* indPoints, const OdTvVector& vector) = 0;
  
  /** \details
    Sets a normal vector for a list of points of the point cloud.
    
    \param indPoints  [in] An array of point indexes.
    \param vector    	[in] A normal vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vector for specified points is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointNormalsViaList(const OdInt32Array& indPoints, const OdTvVector& vector) = 0;

  /** \details
    Sets a normal vector for a range of points of the point cloud.
    
    \param indStart [in] A starting index for replacement.
    \param nCount   [in] A quantity of points for replacement.
    \param vector   [in] A normal vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vector for specified points is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector) = 0;
  
  /** \details
    Sets normal vectors for a range of points of the point cloud.
    
    \param indStart [in] A starting index for replacement.
    \param vectors  [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vectors for specified points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointNormalsViaRange(OdInt32 indStart, const OdTvVectorArray& vectors) = 0;
  
  /** \details
    Sets normal vectors for a range of points of the point cloud.
    
    \param indStart [in] A starting index for replacement.
    \param nCount   [in] A quantity of points for replacement.
    \param vectors  [in] An array of normal vectors represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vectors for specified points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors) = 0;

  /** \details
    Retrieves normals for a range of points of the point cloud.
    
    \param indStart [in] A starting index of the range.
    \param nCount   [in] A quantity of points in the range.
    \param vectors  [out] An array of normal vectors to be filled.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If normals for specified points are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getPointNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const = 0;
  
 /** \details
    Retrieves normals for a range of points of the point cloud.
    
    \param indPoints [in] An array of point indexes.
    \param vectors   [out] An array of normal vectors to be filled.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If normals for specified points are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getPointNormalsViaList(const OdInt32Array& indPoints, OdTvVectorArray& vectors) const = 0;
  
  /** \details
    Retrieves the normal vector for a specified point of the point cloud.
    
    \param ind 	[in] A point index.
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvVector class that represents a vector in 3D space.
    \remarks
    If the rc parameter is not null and the normal vector is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVector getPointNormal(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Set if spatial tree for selection should be used.
    
    \param bUseSpatialTreeForSelection [in] A flag that determines whether it is needed to use spatial tree for selection.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If flag was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setUseSpatialTreeForSelection(bool bUseSpatialTreeForSelection) = 0;

  /** \details
    Retrieves if need use spatial tree for selection.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a flag, which determine, if need use spatial tree for selection.
    \remarks
    If the rc parameter is not null and the flag was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getUseSpatialTreeForSelection(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the OdTvPointCloudData class and used for storing and passing references to the point cloud object.
*/
typedef OdTvSmartPtr<OdTvPointCloudData> OdTvPointCloudDataPtr;


/** \details
  This is an abstract interface class for working with boundary representation data in Visualize SDK.
*/
class ODTV_EXPORT OdTvBrepData : public OdTvIObject
{
public:
  /** \details
    Sets a new value of the facet resolution parameter (used in triangulation).
    
    \param dFacetRes [in] A new facet resolution value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new faces resolution parameter value was successfully set, the method returns tvOk;
    otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFacetRes(double dFacetRes) = 0;

  /** \details
    Retrieves the current value of the facet resolution parameter. This value is used for triangulation.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current value of the facet resolution parameter.
    \remarks
    If the rc parameter is not null and the facet resolution was returned successfully, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual double getFacetRes(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets geometry caching enabled or not
    
    \param bEnable [in] A flag indicating should the geometry caching be enabled or not.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new flag for geometry caching was successfully set, the method returns tvOk;
    otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEnableCaching(bool bEnable) = 0;

  /** \details
    Retrieves the current value of the flag indicating should the geometry caching be enabled or not.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current value of the flag indicating should the geometry caching be enabled or not.
    \remarks
    If the rc parameter is not null and the enable caching flag was returned successfully, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual bool getCachingEnabled(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the geometry statistics of the cache if the cache exists
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the geometry statistics of the cache if the cache exists.
    \remarks
    If the rc parameter is not null and the geometry statistics was returned successfully, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdTvGeometryStatistic getCacheStatistic(OdTvResult* rc) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the <link OdTvBrepData, OdTvBrepData> class and used for storing and passing references to the B-Rep data object.
*/
typedef OdTvSmartPtr<OdTvBrepData> OdTvBrepDataPtr;


/** \details
  This is an interface class for an OdTvRcsPointCloudData object.
*/
class ODTV_EXPORT OdTvRcsPointCloudData : public OdTvIObject
{
public:
  /** \details
    Retrieves the quantity of points which are currently drawn.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of OdUInt32 type that contains the number of points which was drawn
    \remarks
    If the quantity of points which was drawn is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdInt32 getDrawnPointsCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the quantity of voxels contents of which are currently visible.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of OdUInt32 type that contains the number of points which was drawn
    \remarks
    If the quantity of points which was drawn is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdInt32 getVisibleVoxelsCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the point size.
    
    \param pointSize  [in] A size of a point.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the size of points is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPointSize(OdInt32 pointSize) = 0;

  /** \details
    Retrieves the point size.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a point size as an OdInt32 value.
    \remarks
    If the size of points is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdInt32 getPointSize(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves an extents of this RCS point cloud object. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an extents of RCS point cloud object.
    \remarks
    If the rc parameter is not null and the extents was returned successfully, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdGeExtents3d getExtents(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves an extents of this RCS point cloud object and transforms it by the transformation.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an extents of RCS point cloud object and transforms it by the transformation.
    \remarks
    If the rc parameter is not null and the extents was returned successfully, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdGeExtents3d getTransformedExtents(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the RCS point cloud geometry type and is used for storing and passing references to the point cloud object.
*/
typedef OdTvSmartPtr<OdTvRcsPointCloudData> OdTvRcsPointCloudDataPtr;

#endif // _ODTV_ENTITYGEOMETRY3D_H_INCLUDED_

