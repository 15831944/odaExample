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

#ifndef _ODTV_H_INCLUDED_
#define _ODTV_H_INCLUDED_

#include "OdString.h"
#include "OdPlatformSettings.h"
#include "OdVector.h"
#include "DbHostAppProgressMeter.h"

#include "Ge/GePoint3d.h"
#include "Ge/GeVector3d.h"
#include "Ge/GeVector2d.h"
#include "Ge/GeScale3d.h"
#include "Ge/GeMatrix3d.h"
#include "Ge/GeExtents3d.h"
#include "Ge/GePlane.h"

//DOM-IGNORE-BEGIN
//******************************************************************************
//*** TV export symbols ********************************************************
//******************************************************************************

#ifdef TV_VISUALIZE_EXPORTS
  #define ODTV_EXPORT           OD_TOOLKIT_EXPORT
  #define ODTV_EXPORT_STATIC    OD_STATIC_EXPORT
#else
  #define ODTV_EXPORT           OD_TOOLKIT_IMPORT
  #define ODTV_EXPORT_STATIC    OD_STATIC_IMPORT
#endif

//******************************************************************************
//*** TV typedefs *************************************************************
//******************************************************************************
//DOM-IGNORE-END

/** \details
  The data type for a three-dimensional point.
*/
typedef OdGePoint3d                                                    OdTvPoint;

/** \details
  The data type for a three-dimensional point array.
*/
typedef OdVector<OdTvPoint, OdMemoryAllocator<OdTvPoint> >             OdTvPointArray;

/** \details
  The data type for a two-dimensional point.
*/
typedef OdGePoint2d                                                    OdTvPoint2d;

/** \details
  The data type for a two-dimensional point array.
*/
typedef OdVector<OdTvPoint2d, OdMemoryAllocator<OdTvPoint2d> >         OdTvPoint2dArray;

/** \details
  The data type for a three-dimensional vector.
*/
typedef OdGeVector3d                                                   OdTvVector;

/** \details
  The data type for a three-dimensional vector array.
*/
typedef OdVector<OdTvVector, OdMemoryAllocator<OdTvVector> >           OdTvVectorArray;

/** \details
  The data type for a two-dimensional vector.
*/
typedef OdGeVector2d                                                   OdTvVector2d;

/** \details
  The data type for a two-dimensional vector array.
*/
typedef OdVector<OdTvVector2d, OdMemoryAllocator<OdTvVector2d> >       OdTvVector2dArray;

/** \details
  The data type for a three-dimensional scale transformation.
*/
typedef OdGeScale3d                                                    OdTvScale;

/** \details
  The data type for a three-dimensional matrix.
*/
typedef OdGeMatrix3d                                                   OdTvMatrix;

/** \details
  The data type for a three-dimensional extents.
*/
typedef OdGeExtents3d                                                  OdTvExtents3d;

/** \details
  The data type for a plane.
*/
typedef OdGePlane                                                       OdTvPlane;

/** \details
  The data type for a app progress meter
*/
typedef OdDbHostAppProgressMeter                                        OdTvHostAppProgressMeter;

/** \details
  Contains common declarations for Visualize SDK.
*/
namespace OdTv
{
  /** \details
    Types of open modes for a Visualize SDK object.
  */
  enum OpenMode
  {
    kNotOpen = -1,  // Object is not open.
    kForRead = 0,   // Object is open for reading.
    kForWrite = 1,   // Object is open for reading and/or writing.
  };

  /** \details
    Types of attribute inheritances for a Visualize SDK object.

    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  enum InheritedAttribute
  {
    kByLayer = 0,     // An object inherits attributes of the layer on which it resides.
    kByBlock = 1      // An object inherits attributes of the block reference that contains it.
  };

  /** \details
    Visualize SDK major versions.
  */
  enum Version
  {
    kv_TV1 = 1,           // Visualize SDK major version 1 
    kv_TV2 = 2,           // Visualize SDK major version 2 (ODA SDK 19.8)
    kv_TV3 = 3,           // Visualize SDK major version 3 (ODA SDK 19.12)
    kv_TV4 = 4,           // Visualize SDK major version 4 (ODA SDK 20.5)
    kv_TV5 = 5,           // Visualize SDK major version 5 (ODA SDK 20.8)
    kv_TV6 = 6,           // Visualize SDK major version 6 (ODA SDK 20.12)
    kv_TV7 = 7,           // Visualize SDK major version 7.
    kv_TV8 = 8,           // Visualize SDK major version 8.
    kv_TV9 = 9,           // Visualize SDK major version 9.
    kv_CURRENT = kv_TV9,  // Value contains the current major Visualize SDK version.
  };

  /** \details
    Visualize SDK minor versions.
  */
  enum MinorVersion
  {
    kv_MINOR_TV0 = 0,           // Visualize SDK minor version 0.
    kv_MINOR_TV1 = 1,           // Visualize SDK minor version 1.
    kv_MINOR_TV2 = 2,           // Visualize SDK minor version 2.
    kv_MINOR_TV3 = 3,           // Visualize SDK minor version 3.
    kv_MINOR_TV4 = 4,           // Visualize SDK minor version 4. 
    kv_MINOR_TV5 = 5,           // Visualize SDK minor version 5.
    kv_MINOR_TV6 = 6,           // Visualize SDK minor version 6.
    kv_MINOR_TV7 = 7,           // Visualize SDK minor version 7.
    kv_MINOR_TV8 = 8,           // Visualize SDK minor version 8.
    kv_MINOR_TV9 = 9,           // Visualize SDK minor version 9.
    kv_MINOR_TV10 = 10,         // Visualize SDK minor version 10.
    kv_MINOR_TV11 = 11,         // Visualize SDK minor version 11.
    kv_MINOR_TV12 = 12,         // Visualize SDK minor version 12.
    kv_MINOR_CURRENT = kv_MINOR_TV1,  // Value contains the current minor Visualize SDK version.
  };

  /** \details
    Types of orientation.
  */
  enum OrientationType
  {
    kNoOrientation = 0,     // No orientation is defined.
    kCounterClockwise = 1,  // Counter-clockwise orientation.
    kClockwise = 2          // Clockwise orientation.
  };

  /** \details
    Types of handled object.
  */
  enum HandledObjectType
  {
    kNone = 0,            // No handled object.
    kModel = 1,           // Model object.
    kBlock = 2,           // Block object.
    kEntity = 3,          // Entity object.
    kInsert = 4,          // Insert object.
    kLight = 5,           // Light object.
    kGsDevice = 6,        // GS device object.
    kGsView = 7,          // GS view object.
    kLayer = 8,           // Layer object.
    kLinetype = 9,        // Linetype object.
    kMaterial = 10,       // Material object.
    kRasterImageDef = 11, // Raster image object.
    kTextStyle = 12,      // Text style object.
    kCamera = 13          // Camera object
  };

  /** \details
    Types of sub-geometry.
  */
  enum SubGeometryType
  {
    kNullSubGeometryType = 0, // No sub-geometry.
    kFaceSubGeometryType,     // Face sub-geometry.
    kEdgeSubGeometryType,     // Edge sub-geometry.
    kVertexSubGeometryType,   // Vertex sub-geometry.
  };

  /** \details
    Types of filling mode.
  */
  enum FillingMode
  {
    kAs2D = 1,          // If this flag is set, plane objects are filled in k2DOptimized rendering mode only if the normal is co-directed with the eye vector.
    kAsSolid = 2,       // If this flag is set, plane objects are filled in kWireframe rendering mode; in 'kHiddenLine' rendering mode plane objects are not filled.
    kEveryWhere = 4,    // If this flag is set, plane objects are filled in all modes, and all other flags are ignored.
  };

  /** \details
    Types of extents.
    \remarks
    There are rules that determine the priority of different types of extents.
    External extents have the first priority (this extents object can be set with the setExtents() method).
    Cached view extents (which are calculated during full vectorization) have second priority.
    If there are no cached extents, the geometric extents are calculated.
    Please remember that geometric extents are not as exact as view extents.
    Also, geometric extents are not cached automatically. If you want to cache them, call the setExtents() method explicitly.
    Different types of extents can be in different coordinate systems: for the 'kExternal' type the CS is generally undefined. You should control it 
    by yourself when using setExtents() method. For the 'kView' type in many cases it will be the WCS since such type is valid only for the model, the block 
    or the top level entities or inserts. There is only one exception - when the model has Units transformation or it's own modeling matrix in 'fastMode'. In this case
    the 'kView' extents should be multiplied by the combinations of units transformation and 'fastMode' own transformation.
    For the 'kGeom' type situation is the same as for the 'kView' type for the model, the block or the top level entities or inserts. 
    For the subentites it will be ECS (entity CS) which means that only subentities own transformation will be taken into account while all parent's transformation should be applied separately to receive the WCS extents.
  */
  enum ExtentsType
  {
    kPreferred = 0, // Preferred extents.
    kExternal = 1,  // External extents.
    kView = 2,      // View extents.
    kGeom = 3       // Geometric extents.
  };

  /** \details
    Units of linear dimension.
  */
  enum Units
  {
    kUserDefined = 0,       //User-defined conversion coefficient to meters
    kMeters = 1,            //Meters (SI system)
    kCentimeters = 2,       //Centimeters (1/100 meter)
    kMillimeters = 3,       //Millimeters (1/1000 meter)
    kFeet = 4,              //Feet (12 inches, 1/3 yard)
    kInches = 5,            //Inches (2.54 centimeters)
    kYards = 6,             //Yards (0.9144 meter)
    kKilometers = 7,        //Kilometers (1000 meters)
    kMiles = 8,             //Miles (1760 yards)
    kMicrometers = 9,       //Micrometers (microns, 1/1 000 000 meter)
    kMils = 10,             //Mils (1/1000 inch)
    kMicroInches = 11       //Microinches (1/1 000 000 inch)
  };
}

/** \details
  Calculates coefficient for converting 'From' units to 'To' units.

  \param unitsFrom                  [in]  Linear units from which to convert the value.
  \param unitsTo                    [in]  Linear units to which to convert the value.
  \param userDefCoefToMeters_uFrom  [in]  User-defined coefficient to meters transform. Actual only for unitsFrom = 'kUserDefined'.
  \param userDefCoefToMeters_uTo    [in]  User defined coefficient to meters transform. Actual only for unitsTo = 'kUserDefined'.
  \returns Coefficient for converting 'From' units to 'To' units.
*/
ODTV_EXPORT double odTvGetUnitsConversionCoef(OdTv::Units unitsFrom, OdTv::Units unitsTo, double userDefCoefToMeters_uFrom = 1., double userDefCoefToMeters_uTo = 1.);

/** \details
  Version of the VSF (Visualize Stream Format) object, which contains major and minor versions.
*/
class OdTvVSFVersion
{
  OdTv::Version       m_majorVersion;     //Visualize SDK major version
  OdTv::MinorVersion  m_minorVersion;     //Visualize SDK minor version

public:
  /** \details
    Creates a VSF version object as current version.
  */
  OdTvVSFVersion() : m_majorVersion(OdTv::kv_CURRENT), m_minorVersion(OdTv::kv_MINOR_CURRENT) {}

  /** \details
    Creates a VSF version object with major version as a parameter.
    \param ver [in] Major version.
  */
  OdTvVSFVersion(OdTv::Version ver) : m_majorVersion(ver)
  {
    if (ver <= OdTv::kv_TV6)
      m_minorVersion = OdTv::kv_MINOR_TV0;
    else
      m_minorVersion = OdTv::kv_MINOR_CURRENT;
  }

  /** \details
    Creates a VSF version object with the specified parameters.
    \param majorVer [in] Major version.
    \param minorVer [in] Minor version.
  */
  OdTvVSFVersion(OdTv::Version majorVer, OdTv::MinorVersion minorVer) : m_majorVersion(majorVer)
  {
    if (majorVer <= OdTv::kv_TV6)
      m_minorVersion = OdTv::kv_MINOR_TV0;
    else
      m_minorVersion = minorVer;
  }

  /** \details
    Creates a VSF version object as a copy of an existing one (copy constructor).
    \param ver [in] A version to be used as an original for creating a new version.
  */
  OdTvVSFVersion(const OdTvVSFVersion& ver)
  {
    m_majorVersion = ver.m_majorVersion;
    m_minorVersion = ver.m_minorVersion;
  }

  /** \details
    Returns the major Visualize SDK version.
    
    \returns
    A value from the OdTv::Version enumeration representing current major version.
  */
  OdTv::Version majorVersion() const { return m_majorVersion; }

  /** \details
    Returns the minor Visualize SDK version.
  
    \returns
    A value from the OdTv::MinorVersion enumeration representing current minor version.
  */
  OdTv::MinorVersion minorVersion() const { return m_minorVersion; }

  /** \details
    The less than operator for a version. This operator compares two versions and determines whether the left version is less than the right one.
    \param ver [in] Another version object for comparing.
    \returns Returns true if the left version is less than the right version, otherwise returns false.
  */  
  bool operator < (const OdTvVSFVersion& ver) const
  {
    if (m_majorVersion < ver.m_majorVersion)
      return true;
    else if (m_majorVersion == ver.m_majorVersion)
    {
      if (m_minorVersion < ver.m_minorVersion)
        return true;
    }

    return false;
  }

  /** \details
    The greater than operator for a version. This operator compares two versions and determines whether the left version is greater than the right one.
    \param ver [in] Another version object for comparing.
    \returns Returns true if the left version is greater than the right version, otherwise returns false.
  */
  bool operator > (const OdTvVSFVersion& ver) const
  {
    if (m_majorVersion > ver.m_majorVersion)
      return true;
    else if (m_majorVersion == ver.m_majorVersion)
    {
      if (m_minorVersion > ver.m_minorVersion)
        return true;
    }

    return false;
  }

  /** \details
    The less or equal operator for a version. This operator compares two versions and determines whether the left version is less than or equal to the right one.
    \param ver [in] Another version object for comparing.
    \returns Returns true if the left version is less than or equal to the right version, otherwise returns false.
  */
  bool operator <= (const OdTvVSFVersion& ver) const
  {
    if (m_majorVersion < ver.m_majorVersion)
      return true;
    else if (m_majorVersion == ver.m_majorVersion)
    {
      if (m_minorVersion <= ver.m_minorVersion)
        return true;
    }

    return false;
  }

  /** \details
    The greater than or equal operator for a version. This operator compares two versions and determines whether the left version is greater than or equal to the right one.
    \param ver [in] Another version object for comparing.
    \returns Returns true if the left version is greater than or equal to the right version, otherwise returns false.
  */
  bool operator >= (const OdTvVSFVersion& ver) const
  {
    if (m_majorVersion > ver.m_majorVersion)
      return true;
    else if (m_majorVersion == ver.m_majorVersion)
    {
      if (m_minorVersion >= ver.m_minorVersion)
        return true;
    }

    return false;
  }

  /** \details
    The equal operator for a version. This operator compares two versions and determines whether they are equal.
    \param ver [in] Another version object for comparing.
    \returns Returns true if the versions are equal, otherwise returns false.
  */
  bool operator==(const OdTvVSFVersion& ver) const { return m_majorVersion == ver.m_majorVersion && m_minorVersion == ver.m_minorVersion; }

  /** \details
    The non-equal operator for a version. This operator compares two versions and determines whether they are not equal.
    \param ver [in] Another version object for comparing.
    \returns Returns true if the versions are not equal, otherwise returns false.
  */
  bool operator!=(const OdTvVSFVersion& ver) const { return m_majorVersion != ver.m_majorVersion && m_minorVersion != ver.m_minorVersion; }

};

/** \details
  Defines the disabled back or front clipping plane distance.
*/
#define ODTV_INFINITE_XCLIP_DEPTH (1.0e+300)

#define TV_SCALAR_MIN    (-2147483647 - 1)  // Minimum signed 32-bit integer value.
#define TV_SCALAR_MAX      2147483647       // Maximum signed 32-bit integer value.

/** \details
  Two-dimensional device coordinate point.
  \remarks
  Device coordinates are measured in pixels from the lower-left corner.
*/
struct OdTvDCPoint
{
  long x;  // X-coordinate.
  long y;  // Y-coordinate.

  /** \details
    Creates a two-dimensional device coordinate point.
  */
  OdTvDCPoint() { }

  /** \details
    Creates a two-dimensional device coordinate point with specified coordinates.
    \param xx [in] An X-coordinate value.
    \param yy [in] A Y-coordinate value.
  */
  OdTvDCPoint(long xx, long yy) : x(xx), y(yy) { }

  /** \details
    Creates a two-dimensional <link tv_working_with_base_classes_device, device> coordinate point as a copy of an existing one (copy constructor).
    \param dcPoint [in] A point to be used as an original for creating a new point.
  */
  OdTvDCPoint(const OdTvDCPoint& dcPoint)
  {
    x = dcPoint.x;
    y = dcPoint.y;
  }

  /** \details
    The assignment operator for a two-dimensional <link tv_working_with_base_classes_device, device> coordinate point.
    \param dcPoint [in] The left operand of the assignment operation.
    \returns Returns the reference to the point modified after the assignment operation.
  */
  OdTvDCPoint& operator=(const OdTvDCPoint& dcPoint) { x = dcPoint.x; y = dcPoint.y; return *this; }
};

/** \details
  Two-dimensional <link tv_working_with_base_classes_device, device> rectangle. A rectangle is determined with two coordinates: 
  * Lower left corner (xmin and ymin).
  * Upper right corner (xmax and ymax).
  \remarks
  Device coordinates are measured in pixels from the lower-left to upper-right corner.
*/
struct OdTvDCRect
{
  long xmin; // The X-axis coordinate of the left lower corner of the rectangle.
  long xmax; // The X-axis coordinate of the right upper corner of the rectangle.
  long ymin; // The Y-axis coordinate of the left lower corner of the rectangle.
  long ymax; // The Y-axis coordinate of the right upper corner of the rectangle.

  /** \details
    Creates a new two-dimensional rectangle object with default corner coordinates.    
  */
  OdTvDCRect()
  {
    xmin = ymin = TV_SCALAR_MAX;
    xmax = ymax = TV_SCALAR_MIN;
  }

  /** \details
    Creates a new two-dimensional rectangle object with specified corner coordinates.
    \param xMin [in] The X-coordinate of the lower left corner of the rectangle.
    \param xMax [in] The X-coordinate of the upper right corner of the rectangle. 
    \param yMin [in] The Y-coordinate of the lower left corner of the rectangle.
    \param yMax [in] The Y-coordinate of the upper right corner of the rectangle.
  */
  OdTvDCRect(long xMin, long xMax, long yMin, long yMax) : xmin(xMin), xmax(xMax), ymin(yMin),ymax(yMax) { }

  /** \details
    Creates a two-dimensional <link tv_working_with_base_classes_device, device> coordinate rectangle object as a copy of an existing one (copy constructor).
    \param dcRect [in] A rectangle to be used as an original for creating a new rectangle.
  */
  OdTvDCRect(const OdTvDCRect& dcRect)
  {
    xmax = dcRect.xmax;
    ymax = dcRect.ymax;
    xmin = dcRect.xmin;
    ymin = dcRect.ymin;
  }

  /** \details
    The assignment operator for a two-dimensional <link tv_working_with_base_classes_device, device> coordinate rectangle.
    \param dcRect [in] The left operand of the assignment operation.
    \returns Returns the reference to the rectangle modified after the assignment operation.
  */
  OdTvDCRect & operator=(const OdTvDCRect& dcRect)
  {
    xmax = dcRect.xmax;
    ymax = dcRect.ymax;
    xmin = dcRect.xmin;
    ymin = dcRect.ymin;

    return*this;
  }
};

/** \details
  Enumerates different results of Visualize SDK operations.
  \remarks
  The text description for a particular resulting code can be retrieved with the 
  <link odTvGetResultCodeDescription@OdTvResult,  odTvGetResultCodeDescription() function>.
  
  \sa
  <link tv_working_with_base_classes_results_errors, Get Operation Results and Error Handling>
 */
enum OdTvResult
{  
  tvOk                                   ,      // An operation successfully finished.
  tvInternal                             ,      // A requested operation is for Visualize SDK internal use only.
  tvNotImplementedYet                    ,      // Not implemented yet.
  tvNotSupported                         ,      // Not supported.
  tvInvalidInput                         ,      // Incorrect input data was provided.
  tvFactoryDoesntExist                   ,      // A visualize object factory does not exist.
  tvMissingObject                        ,      // A needed object is missing.
  tvObjectLeftOnDisk                     ,      // A needed object is left on disk.        
  tvErasedObject                         ,      // A retrieved object was erased.
  tvIdHasNoData                          ,      // An object with the specified identifier has no internal data.
  tvIdWrongData                          ,      // An object with the specified identifier has incorrect data.
  tvIdWrongDataType                      ,      // An object with the specified identifier has an incorrect data type.
  tvNullObjectPtr                        ,      // A pointer to an object is NULL.
  tvAlreadyExistSameName                 ,      // An object with the specified name already exists in the database.
  tvGeometryDataDoesntExistOrBeenDeleted ,      // Retrieved geometry data does not exist or was deleted.
  tvGeometryDataHasAnotherType           ,      // Retrieved geometry data has a different type than was expected.
  tvWrongDevicePathData                  ,      // Incorrect device path information was provided.
  tvDeviceLoadingFailed                  ,      // Device information loading failed.
  tvDeviceCreatingFailed                 ,      // Device creation failed.
  tvDeviceWrongType                      ,      // A device has an incorrect type.
  tvDeviceWrongBitmapState               ,      // An invalid device bitmap state occurred.
  tvInvalidDeviceOption                  ,      // An invalid device option was provided.
  tvDeviceOptionHasErrorType             ,      // Device option information contains an error type.
  tvDeviceOptionDoesntSupport            ,      // The device option is not supported.
  tvDevicesIsEmpty                       ,      // Device is empty.
  tvViewHasDifferentDevice               ,      // The view has a different device than was provided.
  tvViewIndexTooBig                      ,      // The view index is out of range: the index value is greater than or equal to the view's array elements count.
  tvViewIndexTooSmall                    ,      // The view index is out of range: the index value is too small.
  tvModelHasErrorDatabase                ,      // A model has an incorrect database.
  tvMethodNotImplemented                 ,      // A method is not implemented yet.
  tvGeoDataHasNoParent                   ,      // Geometry data does not have a parent object.
  tvCannotCreateInternalDatabase         ,      // An internal database can not be created.
  tvInternalDeviceDoesntCreated          ,      // An internal device has not been created.
  tvMissedTextTraits                     ,      // Text traits are missing.
  tvInternalDatabaseDoesntCreated        ,      // An internal database has not been created.
  tvPolygonNotPlanar                     ,      // A polygon is not planar.
  tvPolygonHasLessThanThreePoints        ,      // A polygon has less than three points.
  tvInternalDatabaseHasNoModelsContainer ,      // Internal database has no model container.
  tvInternalDatabaseHasNoImagesContainer ,      // Internal database has no image container.
  tvInternalDatabaseHasNoVisualStylesContainer, // Internal database has no visual style container.
  tvInternalIteratorMissing              ,      // An internal iterator for objects is missing.
  tvLinearlyDependentCircleArg           ,      // A linearly dependent circle argument.
  tvEmptyName                            ,      // An object has an empty name.
  tvInvalidName                          ,      // An object's name is invalid.
  tvForbiddenName                        ,      // An object has a forbidden name.
  tvSelfReferencedBlock                  ,      // A block object references itself.
  tvInvalidColorType                     ,      // An object has an invalid color type.
  tvInvalidLinetypeType                  ,      // An object has an invalid linetype value.
  tvNonPositiveNurbsDegree               ,      // A non-positive NURBS degree value was detected.
  tvInvalidNurbsControlPoints            ,      // A NURBS curve has invalid control points.
  tvInvalidNurbsWeights                  ,      // A NURBS curve has invalid weights.
  tvInvalidNurbsKnots                    ,      // A NURBS curve has invalid knots.
  tvInvalidNurbsStartEndParams           ,      // A NURBS curve has invalid start and/or end parameter values.
  tvNotOpenForWrite                      ,      // An object has not been opened for writing before trying to write data to it.
  tvInvalidLineWeightType                ,      // An object has an invalid lineweight type.
  tvImageFileAccessErr                   ,      // An error occurred while accessing an image file.
  tvImageNotLoaded                       ,      // An image was not loaded.
  tvInvalidLayerType                     ,      // An object has an invalid layer type.
  tvRasterImageObjectDoesntExistOrBeenDeleted,  // A raster image object does not exist or has been deleted from the database.
  tvInvalidVerticesInput                 ,      // Invalid input vertex data was provided.
  tvInvalidFacesInput                    ,      // Invalid input face data was provided.
  tvInvalidShellVerticesInput            ,      // Invalid input shell vertex data was provided.
  tvInvalidShellFacesInput               ,      // Invalid input shell face data was provided.
  tvInvalidMeshVerticesInput             ,      // Invalid input mesh vertex data was provided.
  tvInvalidTransparencyType              ,      // Invalid input transparency type value.
  tvNonSetupDevice                       ,      // The specified device was not set up.
  tvEmptyFilePath                        ,      // A file path is empty.
  tvMissingFilerModule                   ,      // A filer module is missing.
  tvMissingFiler                         ,      // A filer is missing.
  tvInvalidFilePath                      ,      // An invalid file path was provided.
  tvCannotOpenFile                       ,      // The specified file can not be opened.
  tvErrorDuringOpenFile                  ,      // An error occurred while opening the specified file.
  tvFilerEmptyInternalDatabase           ,      // An empty internal database for a filer was found.
  tvMissingVisualizeDeviceModule         ,      // The Visualize SDK device module is missing.
  tvWrongRasterImageType                 ,      // An incorrect raster image type was provided.
  tvInvalidFileType                      ,      // An invalid file type was provided.
  tvViewportObjectCanHaveOnlyOneParent   ,      // A viewport object has more than one parent.
  tvThereIsNoActiveView                  ,      // No active view was found.
  tvInvalidClippingPointInput            ,      // An invalid input clipping point was provided.
  tvWrongHandledObjectClass              ,      // An incorrect class for a handled object was provided.
  tvWrongHandledObjectParent             ,      // An incorrect parent for a handled object was provided.
  tvWrongHandledObjectType               ,      // An incorrect type of a handled object was provided.
  tvDuplicateHandle                      ,      // A duplicate handle was detected.
  tvWrongSubItemPath                     ,      // An incorrect sub-item path was provided.
  tvInvalidExtents                       ,      // An invalid extents was provided.
  tvNoRequestedExtents                   ,      // No requested extents were found.
  tvOperationIsNotAllowedBy2dView        ,      // The operation is not allowed by the 2D view.
  tvInvalidVisualStyleOption             ,      // Invalid visual style operation.
  tvVisualStyleOptionHasErrorType        ,      // The visual style operation returned an error.
  tvForbiddenOperationDefVisualStyle     ,      // A forbidden visual style operation was requested.
  tvInvalidBoxVectors                    ,      // Invalid input vectors for the box creation.
  tvErrorDuringExport                    ,      // An error occurred while exporting the database to the specified file.
  tvMissingExportModule                  ,      // An export module is missing.
  tvMissingExporter                      ,      // An exporter is missing.
  tvNonRevisionControlInternalDatabase   ,      // Internal database has no storage.
  tvOkOldFormatRead                      ,      // Old file format read successfully.
  tvMissingModelerGeometryCreatorService ,      // The modeler geometry creator service is missing
  tvBrepBuilderInitializationFailed      ,      // The Brep builder initialization was failed
  tvMissingBrepFilerModule               ,      // The Brep builder module is missing
  tvBrepBuilderConversionFailed          ,      // The Brep builder conversion was failed
  tvBrepBuilderFinishFailed              ,      // The Brep builder finish process was failed
  tvBrepHasNoCache                       ,      // The Brep data has no cache
  tvCollideWarnInputHasInvalidData       ,      // Collide warning: input contains invalid data
  tvCollideErrorInputHasNoValidData      ,      // Collide error: input has no valid data
  tvCollideWarnInputWithHasInvalidData   ,      // Collide warning: collide with contains invalid data
  tvCollideWarnInputWithHasNoValidData   ,      // Collide warning: collide with has no valid data
  tvCollideSelectionLevelWasChanged      ,      // Collide warning: selection level was changed (from nested to entity) 
  tvPolylineHasNoPoints                  ,      // A polyline has no points. 
  tvZeroNormal                           ,      // A normal vector has invalid value.
  tvEllipseInvalidPoints                 ,      // An ellipse has invalid points.
  tvSphereZeroBasis                      ,      // A sphere vectors (axis/prime meridian) is/are zero length.
  tvCylinderMatchingPoints               ,      // A cylinder has matching points.
  tvCylinderPointsNumber                 ,      // A cylinder points number is invalid.
  tvCylinderRadiiNumber                  ,      // A cylinder radii number is invalid.
  tvInfiniteLineMatchingPoints           ,      // An infinite line/ray  has matching points.
  tvRasterImageZeroVector                ,      // A raster image has zero vectors.
  tvCollisionResultsHaveNotEqualLenth    ,      // A lists with result of collision have different length.
  tvCuttingPlaneZeroNormal               ,      // A cutting plane function has zero length normal.
  tvRcsModuleIsMissed                    ,      // The RCS module is missing.
  tvNativePropMissedDatabase             ,      // The database for the manipulation with native properties is missing.
  tvNativePropMissedObject               ,      // An object for the manipulation with native properties is missing.
  tvWarning                              ,      // No error occurred, but some functionality may not work (e.g. partial viewing request on database without partial indexes).
  tvCommonDataAccessTreeMissed           ,      // Common data access tree is missing.
  tvProgressiveMeshWasNotObtained        ,      // Failed to retrieve progressive mesh traits.
  tvEntityIdNotFoundForOriginal          ,      // Failed to find entity by original id.
  tvPointCloudDoesNotHaveRequestedData   ,      // Point cloud does not have requested data.
  tvFilerEmptyContext                    ,      // Data context could not be obtained.
  tvUserAbort                            ,      // Operation aborted by user.
  tvAlreadyInUse                         ,      // Trying to modify data that is already in use.
  tvIsolateHideNoGsNode                  ,      // Trying to isolate/hide data in the 'per session' mode without Gs cache.
  tvOkPartially                          ,      // An operation successfully finished partially.
  tvForbiddenOperationDefHighlightStyle  ,      // A forbidden highlight style operation was requested.

  //DOM-IGNORE-BEGIN
  tvDummyLastError  // A special value for internal use.
  //DOM-IGNORE-END
};

/** \details
  Gets explanatory text for a given OdTvResult result code.
  
  \param iCode [in]  An <link OdTvResult, OdTvResult result code>.
  \returns Returns explanatory text represented with an OdString object.
  \remarks
  The method returns a string message filled with explanatory text
  based on the value of iCode. The text is written in English.
*/
ODTV_EXPORT OdString odTvGetResultCodeDescription( OdTvResult iCode );

/** \details
    The base class for a Visualize SDK object identifier. 
    
    \sa
    <link tv_working_with_base_classes_id, Work with Identifiers and Smart Pointers>
*/
class OdTvId
{
public:

  /** \details 
    Creates an instance of an object identifier with a zero value.
  */
  OdTvId() : m_pImplId(0){}

  /** \details
    Determines whether the identifier object is null.
    
    \returns Returns true if the identifier is null, otherwise returns false.
  */
  bool isNull() const{return m_pImplId==0; }

  /** \details
    Resets the identifier object to a null value.
  */
  void setNull() { m_pImplId=0; }

  /** \details
    The less than operator for an identifier. This operator compares two identifiers and determines whether the left identifier is less than the right one.
    
    \param id [in] Another identifier object for comparing.
    \returns Returns true if the left identifier is less than the right identifier, otherwise returns false.
  */
  bool operator < (const OdTvId& id) const { return m_pImplId < id.m_pImplId; }

  /** \details
    The greater than operator for an identifier. This operator compares two identifiers and determines whether the left identifier is greater than the right one.
    
    \param id [in] Another identifier object for comparing.
    \returns Returns true if the left identifier is greater than the right identifier, otherwise returns false.
  */
  bool operator > (const OdTvId& id) const { return m_pImplId > id.m_pImplId; }

  /** \details
    The greater than or equal operator for an identifier. This operator compares two identifiers and determines whether the left identifier is greater than or equal to the right one.
    
    \param id [in] Another identifier object for comparing.
    \returns Returns true if the left identifier is greater than or equal to the right identifier, otherwise returns false.
  */
  bool operator >= (const OdTvId& id) const { return m_pImplId >= id.m_pImplId; }

  /** \details
    The less or equal operator for an identifier. This operator compares two identifiers and determines whether the left identifier is less than or equal to the right one.
    
    \param id [in] Another identifier object for comparing.
    \returns Returns true if the left identifier is less than or equal to the right identifier, otherwise returns false.
  */
  bool operator <= (const OdTvId& id) const { return m_pImplId <= id.m_pImplId; }

  /** \details
    The equal operator for an identifier. This operator compares two identifiers and determines whether they are equal.
    
    \param id [in] Another identifier object for comparing.
    \returns Returns true if the identifiers are equal, otherwise returns false.
    \sa 
    <link OdTvId::!=@OdTvId&@const, Non-equal operator for identifiers>.
  */
  bool operator==(const OdTvId& id) const { return m_pImplId == id.m_pImplId; }

  /** \details
    The non-equal operator for an identifier. This operator compares two identifiers and determines whether they are not equal.
    
    \param id [in] Another identifier object for comparing.
    \returns Returns true if the identifiers are not equal (have different values), otherwise returns false.
    \sa 
    <link OdTvId::==@OdTvId&@const, Identifier equal operator>.
  */
  bool operator!=(const OdTvId& id) const { return m_pImplId != id.m_pImplId; }

//DOM-IGNORE-BEGIN
protected:
  void* m_pImplId;
//DOM-IGNORE-END
};

/** \details 
The base class for a Visualize SDK object iterator.
*/
class OdTvIterator
{
public:

  /** \details
    Determines whether the traversal through the iterator was completed.
    
    \param rc [out] A pointer to a value of the <link OdTvResult, OdTvResult> type that contains the method execution result.
    \returns Returns true if the traversal using the iterator object was completed, otherwise returns false.
  */
  virtual bool done(OdTvResult* rc = NULL) const{ return true;};

  /** \details
    Steps to the next value in the iterator object. 
    
    \returns Returns a value of the <link OdTvResult, OdTvResult> type that contains the result of stepping to the next value. 
    If the step was successful, the method returns the tvOk value.
  */
  virtual OdTvResult step() {return tvOk; };
};


#endif // _ODTV_H_INCLUDED_

