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


#ifndef _ODDB_GEODATA_INCLUDED_
#define _ODDB_GEODATA_INCLUDED_

#include "TD_PackPush.h"

#include "DbObject.h"
#include "OdDbGeoCoordinateSystem.h"

/** \details
  This class represents GeoData objects in an OdTvDbDatabase instance.

  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbGeoData: public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbGeoData);
  /** \details
    Default constructor.
  */
  OdTvDbGeoData();

  /** \details
    This enumeration represents the type of design coordinates.
  */
  enum TypeOfCoordinates
  {
    kCoordTypUnknown = 0,   // Unknown
    kCoordTypLocal,         // Local grid
    kCoordTypGrid,          // Projected grid
    kCoordTypGeographic     // Geographic (latitude/longitude)
  };

  /** \details
    This enumeration represents the scale estimation method.
  */
  enum ScaleEstimationMethod
  {
    kScaleEstMethodUnity = 1,       // Unity
    kScaleEstMethodUserDefined,     // User defined scale factor
    kScaleEstMethodReferencePoint,  // Grid scale at reference point
    kScaleEstMethodPrismoidal       // Prismoidal
  };

  /** \details
    Returns the Object ID of the block table record.
  */
  OdTvDbObjectId blockTableRecordId() const;
  
  /** \details
    Sets the Object ID of the block table record.
    
    \param blockId [in] Object ID of the block table record.
  */
  OdResult setBlockTableRecordId(const OdTvDbObjectId& blockId);
  
  /** \details
    Posts this OdTvDbGeoData object to the database.
    
    \param objId [out] Object ID of the posted OdTvDbGeoData object.
    
    \returns Returns eOK if successful, or an appropriate error code if not.
    
    \remarks
    Call the setBlockTableRecordId() method to set the block table record 
    before calling the postToDb() method.
  */
  OdResult postToDb(OdTvDbObjectId& objId);

  /** \details
    Erases this OdTvDbGeoData object from the database.
    
    \returns Returns eOK if the object was successfully erased, or an appropriate error code if not.
  */
  OdResult eraseFromDb();

  /** \details
    Returns the type of design coordinates.
    
    \remarks
    The type of design coordinates can be one of the following:
* kCoordTypUnknown
* kCoordTypLocal
* kCoordTypGrid
* kCoordTypGeographic 
  */
  TypeOfCoordinates coordinateType() const;
  
  /** \details
    Sets the type of design coordinates.
    
    \param designCoordinateType [in] Type of coordinates for setting.
    
    \remarks
    The designCoordinateType can be one of the following:
* kCoordTypUnknown
* kCoordTypLocal
* kCoordTypGrid
* kCoordTypGeographic 
    The current implementation supports only kCoordTypGrid and kCoordTypGeographic 
    types and recalculates coordinates correctly only if the Unit of the drawing is set to meter. 
  */
  OdResult setCoordinateType(TypeOfCoordinates designCoordinateType);

  /** \details
    Returns the design coordinates of the point associated with the point position
    specified by the setReferencePoint() method.

    \remarks
    There is no a default value for the point's design coordinates. They must be specified 
    clearly by the application that creates an OdTvDbGeoData object.
  */
  OdGePoint3d designPoint() const;
  
  /** \details
    Sets the design coordinates of the point associated with the point position
    specified by the setReferencePoint() method.

    \param point [in] Point design coordinates.
    
    \remarks
    There is no default value for the point's design coordinates. They must be specified 
    clearly by the application that creates an OdTvDbGeoData object.
  */
  OdResult setDesignPoint(const OdGePoint3d& point);

  /** \details
    Returns the reference point associated with the design coordinates that is set 
    by the setDesignPoint() method.
  */
  OdGePoint3d referencePoint() const;
  
  /** \details
    Sets the reference point associated with the design coordinates that is set 
    by the setDesignPoint() method.
    
    \param point [in] Reference point.
    
    \remarks
    If the type of coordinate is kCoordTypLocal, the point argument is defined by the 
    setCoordinateSystem() method of this object. 
  */
  OdResult setReferencePoint(const OdGePoint3d& point);

  /** \details
    Returns the current value of the horizontal unit scale.
    
    \returns Returns the factor that is used to multiply the X or Y coordinate 
    in the design database to produce the equivalent value in meters.
    
    \remarks
    Default value is 1.0. 
  */ 
  double horizontalUnitScale() const;
  /** \details
    Returns the horizontal unit type.
    
    \returns If the current value of the horizontal unit scale was set by the setHorizontalUnit() method, 
    this method returns the OdDb::UnitsValue used at that time.   
  */
  OdDb::UnitsValue horizontalUnits() const;
  
  /** \details
    Sets the current value of the horizontal unit scale.
    
    \param horzUnitScale [in] Double value that is used to multiply the X or Y coordinate 
    to produce the equivalent value in meters.
  */ 
  OdResult setHorizontalUnitScale(double horzUnitScale);
  
  /** \details
    Sets the linear unit in which X and Y cooordinates are expressed.
    
    \param horizUnits [in] Unit system in which horizontal X and Y coordinates are expressed.
  */
  OdResult setHorizontalUnits(OdDb::UnitsValue horizUnits);

  /** \details
    Returns the current value of the vertical unit scale.
    
    \returns Returns the factor that is used to multiply the X or Y coordinate 
    in the design database to produce the equivalent value in meters.
  */ 
  double verticalUnitScale() const;
  /** \details
    Returns the vertical unit type.
    
    \returns If the current value of the vertical unit scale was set by setVerticalUnits() method, 
    this method returns the OdDb::UnitsValue used at that time.   
  */
  OdDb::UnitsValue verticalUnits() const;
  /** \details
    Sets the current value of the vertical unit scale.
    
    \param horzUnitScale [in] Double value that is used to multiply the X or Y coordinate 
    to produce the equivalent value in meters.
  */ 
  OdResult setVerticalUnitScale(double vertUnitScale);
  /** \details
    Sets the vertical unit.
    
    \param vertUnits [in] Vertical unit.
  */
  OdResult setVerticalUnits(OdDb::UnitsValue vertUnits);
  
  /** \details
    Returns the copy of the vector that defines the direction of the vertical axis 
    of a local coordinate system.
    
    \remarks
    The default value of the vector is (0, 0, 1).
  */
  OdGeVector3d upDirection() const;
  /** \details
    Sets the current value of the vector that defines the direction of the vertical axis 
    of a local coordinate system.
    
    \param vec [in] Reference to the OdGeVector3d object.
    
    \remarks
    The vector default value is (0, 0, 1).
  */
  OdResult setUpDirection(const OdGeVector3d& vec);

  /** \details
    Returns the azimuth of the Y axis relative to true north in radians east of north.
  */
  double northDirection() const;
  /** \details
    Returns the copy of the 2D vector that defines the direction of true north in terms of design coordinates.
  */
  OdGeVector2d northDirectionVector() const;
  /** \details
    Sets the current value of the 2D vector that defines the direction of true north in terms of design coordinates.
    
    \param north [in] 2D vector.
    
    \remarks
    The default value is (0,1).
  */
  OdResult setNorthDirectionVector(const OdGeVector2d& north);

  /** \details
    Returns the current value of the scale estimation method of this object.
  */
  ScaleEstimationMethod scaleEstimationMethod() const;
  /** \details
    Sets the current value of the scale estimation method of this object.
    
    \param value [in] ScaleEstimationMethod enum value.
  */
  OdResult setScaleEstimationMethod(ScaleEstimationMethod value);

  /** \details
    Returns the current value of the scale factor of this object.
    
    \remarks
    The default value is 1.0. 
  */
  double scaleFactor() const;
  /** \details
    Sets the user-defined scale factor of this object.
    
    \param value [in] Scale value.
    
    \remarks
    The default value is 1.0. 
  */
  OdResult setScaleFactor(double value);

  /** \details
    Returns the boolean value that controls the application of the sea-level 
    correction to horizontal coordinates during a local-to-grid transformation process.
    
    \remarks
    The default value is false. 
  */
  bool doSeaLevelCorrection() const;
  /** \details
    Sets the boolean value that controls the application of the sea-level 
    correction to horizontal coordinates during a local-to-grid transformation process.
    
    \param seaLevelCorrectionOn [in] Boolean value to enable (true) or 
    disable (false) sea-level correction.
    
    \remarks
    The default value is false. 
  */
  OdResult setDoSeaLevelCorrection(bool seaLevelCorrectionOn);

  /** \details
    Returns the current value of the object's sea level elevation.
  */
  double seaLevelElevation() const;
  /** \details
    Sets the object's sea level elevation.
    
    \param value [in] Sea level evaluation value.
  */
  OdResult setSeaLevelElevation(double value);

  /** \details
    Returns the radius of curvature of the ellipsoid model 
    that is used in the sea-level correction algorithm.
    
    \remarks
    The radius is measured in meters.
  */
  double coordinateProjectionRadius() const;
  /** \details
    Sets the radius of curvature of the ellipsoid model 
    that is used in the sea-level correction algorithm.
    
    \param value [in] Radius value, in meters.
  */
  OdResult setCoordinateProjectionRadius(double value);

  /** \details
    Returns the current coordinate system definition.
  */
  OdString coordinateSystem() const;
  /** \details
    Sets the current coordinate system definition.
    
    \param coordSystem [in] String that represents a coordinate system.
    
    \remarks
    When the coordinate system is changed, mesh point arrays are not changed. 
    To get access to these arrays, use set/getMeshPointMaps(), getMeshPointMap() and 
    addMeshPointMap() methods.    
  */
  OdResult setCoordinateSystem(const OdString& coordSystem);

  /** \details
    Returns the geoRSS tag.
  */
  OdString geoRSSTag() const;
  /** \details
    Sets the user generated geoRSS tag.
    
    \param rssTag [in] GeoRSS tag value.
  */
  OdResult setGeoRSSTag(const OdString& rssTag);

  /** \details
    Returns the current value of the ObservationFrom property.
  */
  OdString observationFrom() const;
  /** \details
    Sets the current value of the ObservationFrom property.
    
    \param from [in] New value of the ObservationFrom property.
  */
  OdResult setObservationFrom(const OdString& from);

  /** \details
    Returns the current value of the ObservationTo property.
  */
  OdString observationTo() const;
  /** \details
    Sets the current value of the ObservationTo property.
    
    \param to [in] New value of the ObservationTo property.
  */
  OdResult setObservationTo(const OdString& to);

  /** \details
    Returns the current value of the ObservationCoverage property.
  */
  OdString observationCoverage() const;
  /** \details
    Sets the current value of the ObservationCoverage property.
    
    \param coverage [in] New value of the ObservationCoverage property.
  */
  OdResult setObservationCoverage(const OdString& coverage);

  /** \details
    Returns the number of points in the transformation mesh.
  */
  OdInt32 numMeshPoints() const;
  /** \details
    Returns the design points and the associated reference points in the object's transformation mesh.
    
    \param index [in] Number of the points to be fetched.
    \param srcPt [out] Source point.
    \param dstPt [out] Destination point.
  */
  OdResult getMeshPointMap(OdInt32 index, OdGePoint2d& srcPt, OdGePoint2d& dstPt) const;
  /** \details
    Returns the object's transformation mesh points.
    
    \param srcPts [out] Array of all design points.
    \param dstPts [out] Array of all reference points.
    
    \remarks
    The returned arrays are valid if they contain the same number of points and are not empty.
  */
  OdResult getMeshPointMaps(OdGePoint2dArray& srcPts, OdGePoint2dArray& dstPts) const;
  /** \details
    Inserts a new design/reference point association into the mesh.
    
    \param index [in] Array index.
    \param srcPt [in] Source point.
    \param dstPt [in] Destination point.
    
    \remarks
    The new point association is inserted before the array index parameter. 
    If the index specification is invalid, the new point association is appended to the end 
    of the mesh array.
  */
  OdResult addMeshPointMap(OdInt32 index, const OdGePoint2d& srcPt, const OdGePoint2d& dstPt);
  /** \details
    Replaces the object's transformation mesh point arrays.

    \param srcPts [in] Array of design points.
    \param dstPts [in] Array of associated reference points.
  */
  OdResult setMeshPointMaps(const OdGePoint2dArray& srcPts, const OdGePoint2dArray& dstPts);
  /** \details
    Resets both object's transformation mesh point arrays.
  */
  OdResult resetMeshPointMaps();

  /** \details
    Returns the number of faces in the mesh triangulation.
  */
  OdInt32 numMeshFaces() const;
  /** \details
    Returns the three vertex indexes for the specified face.

    \param faceIndex [in] Face index.
    \param p0 [out] The first vertex index.
    \param p1 [out] The second vertex index.
    \param p2 [out] The third vertex index.
  */
  OdResult getMeshFace(OdInt32 faceIndex, OdInt32 & p0, OdInt32 & p1, OdInt32 & p2) const;
  /** \details
    Sets the three vertex indexes for the specified triangle face.

    \param faceIndex [in] Face index.
    \param p0 [in] The first vertex index.
    \param p1 [in] The second vertex index.
    \param p2 [in] The third vertex index.
  */
  OdResult addMeshFace(OdInt32 faceIndex, OdInt32 p0, OdInt32 p1, OdInt32 p2);

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  /** \details
    Transforms the design point into an equivalent geographic point.

    \param dwgPt [in] Point, in design coordinates, to be transformed.
    \param geoPt [out] Geographic equivalent of the dwgPt.
    
    \returns Returns eOK if successful, or an appropriate error code if not.
        
    \remarks
    Longitude ordinate is transformed in the X member of the OdGePoint3d object, 
    latitude ordinate is transformed in the Y member of the OdGePoint3d object and 
    the elevation (altitude) is transformed in the Z member of the OdGePoint3d object.
  */
  OdResult transformToLonLatAlt(const OdGePoint3d& dwgPt, OdGePoint3d& geoPt) const;
  /** \details
    Transforms the design point into an equivalent geographic point.

    \param x [in] X ordinate of the design point.
    \param y [in] Y ordinate of the design point.
    \param z [in] Z ordinate of the design point.
    \param lon [out] Longitude ordinate of the transformed point. 
    \param lat [out] Latitude ordinate of the transformed point. 
    \param alt [out] Altitude (elevation) ordinate of the transformed point. 
    
    \returns Returns eOK if successful, or an appropriate error code if not.
  */
  OdResult transformToLonLatAlt(double x, double y, double z, double& lon, double& lat, double& alt) const;
  
  /** \details
    Transforms the geographic point into an equivalent design point.

    \param geoPt [in] Geographic point to be transformed.
    \param dwgPt [out] Transformed equivalent in design coordinates.
    
    \returns Returns eOK if successful, or an appropriate error code if not.
        
    \remarks
    Longitude ordinate is transformed in the X member of the OdGePoint3d object, 
    latitude ordinate is transformed in the Y member of the OdGePoint3d object and 
    the elevation (altitude) is transformed in the Z member of the OdGePoint3d object.
  */
  OdResult transformFromLonLatAlt(const OdGePoint3d& geoPt, OdGePoint3d& dwgPt) const;
  /** \details
     Transforms the geographic point into an equivalent design point.

    \param lon [in] Longitude ordinate of the point to be transformed. 
    \param lat [in] Latitude ordinate of the point to be transformed. 
    \param alt [in] Altitude ordinate of the point to be transformed. 
    \param x [out] X ordinate of the transformed point.
    \param y [out] Y ordinate of the transformed point.
    \param z [out] Z ordinate of the transformed point.
    
    \returns Returns eOK if successful, or an appropriate error code if not.
  */
  OdResult transformFromLonLatAlt(double lon, double lat, double alt, double& x, double& y, double& z) const;

  /** \details
   Updates transformation data. This function must be called after geodata fields were modified.

  \returns Returns eOK if successful, or an appropriate error code if not.
*/
  OdResult updateTransformationMatrix();

  //DOM-IGNORE-BEGIN
  //For internal use only:
  const OdGeMatrix3d & getMatrixToLLA() const;
  const OdGeMatrix3d & getMatrixFromLLA() const;
  const OdGeMatrix3d & getMatrixLocalToLLA() const;
  const OdGeMatrix3d & getMatrixLocalFromLLA() const;
  OdResult meshTransformToLLA(const OdGePoint2d & ptIn, OdGePoint2d & ptOut) const;
  OdResult meshTransformFromLLA(const OdGePoint2d & ptIn, OdGePoint2d & ptOut) const;
  OdResult getSimpleTransformerToLLA(OdTvDbGeoCoordinateSystemTransformerPtr & pTransformer) const;
  OdResult getSimpleTransformerFromLLA(OdTvDbGeoCoordinateSystemTransformerPtr & pTransformer) const;
  //DOM-IGNORE-END
};

//GLOBAL API FUNCTIONS
  /** \details
    Global method which is used for getting the OdTvDbGeoData object ID.
    
    \param pDb [in/out] Pointer to a database. 
    \param objId [out] OdTvDbGeoData object ID. 
    
    \returns Returns eOK if successful, or an appropriate error code if not.
  */
TOOLKIT_EXPORT OdResult odtvdbGetGeoDataObjId(OdTvDbDatabase *pDb, OdTvDbObjectId& objId);

TOOLKIT_EXPORT OdResult odtvdbGetGeoDataTransform(OdTvDbDatabase* pDbSource, OdTvDbDatabase* pDbTarget, OdGePoint3d& pt, double& dRotation, double& dScale);

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbGeoData object pointers.
*/
typedef OdSmartPtr<OdTvDbGeoData> OdTvDbGeoDataPtr;

#include "TD_PackPop.h"

#endif //_ODDB_GEODATA_INCLUDED_