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

#ifndef _ODTV_STATISTICS_H_INCLUDED_
#define _ODTV_STATISTICS_H_INCLUDED_

#include "Tv.h"
#include "UInt64Array.h"

/** \details
  A base interface class that provides the statistics of operations performed by Visualize SDK.
  \sa
  <link tv_working_with_features_statistics, Work with Statistics>
*/
class ODTV_EXPORT OdTvStatistic
{
public:

  /** \details
    Creates a new statistics object with default parameters.
  */
  OdTvStatistic();

  /** \details
    Retrieves the current size of objects.
    
    \returns Returns the current object's size.
  */
  OdUInt64 getObjectsSize() const;

  //DOM-IGNORE-BEGIN
protected:

  OdUInt64 m_objectsSize;
  //DOM-IGNORE-END

};

/** \details
  A base interface class that provides the statistics for geometry entities.
  \sa
  <link tv_working_with_features_statistics, Work with Statistics>
*/
class ODTV_EXPORT OdTvGeometryStatistic : public OdTvStatistic
{
public:

  /** \details
    Statistics attribute types for geometry entities.
  */
  enum Types
  {
    kEntity,         // Quantity of entities.
    kLight,          // Quantity of lights.
    kInsert,         // Quantity of inserts.

    kPolyline,       // Quantity of polylines.
    kCircle,         // Quantity of circles.
    kCircleWedge,    // Quantity of circle wedges.
    kCircularArc,    // Quantity of circular arcs.
    kEllipse,        // Quantity of ellipses.
    kEllipticArc,    // Quantity of elliptical arcs.
    kPolygon,        // Quantity of polygons.
    kText,           // Quantity of text.
    kShell,          // Quantity of shells.
    kSphere,         // Quantity of spheres.
    kCylinder,       // Quantity of cylinders.
    kBox,            // Quantity of boxes.
    kGeomInsert,     // Quantity of subinserts.
    kSubEntity,      // Quantity of subentities.
    kNurbs,          // Quantity of NURBS.
    kRasterImage,    // Quantity of raster images.
    kInfiniteLine,   // Quantity of infinite lines.
    kMesh,           // Quantity of meshes.
    kPointCloud,     // Quantity of point clouds.
    kRcsPointCloud,  // Quantity of RCS point clouds.
    kGrid,           // Quantity of grids.
    kColoredShape,   // Quantity of colored shapes.
    kBrep,           // Quantity of breps.

    kPoints,         // Quantity of points (for point clouds).
    kFace,           // Quantity of faces (for shells, meshes, colored shapes).
                     //DOM-IGNORE-BEGIN
                     kLast // A special value for internal use.
                     //DOM-IGNORE-END
  };

  /** \details
    Creates a new statistics object for geometry entities with default parameters.
  */
  OdTvGeometryStatistic();

  /** \details
    Retrieves the quantity of objects with a specified type.
    
    \param type [in] A type of object. Only objects of this type are calculated.
    \returns Returns the quantity of objects that have the specified type.
  */
  OdUInt64 getCount(Types type) const;

  //DOM-IGNORE-BEGIN
protected:

  OdUInt64Array m_counts;
  //DOM-IGNORE-END
};

/** \details
  A base interface class that provides the statistics for database objects.
  \sa
  <link tv_working_with_features_statistics, Work with Statistics>
*/
class ODTV_EXPORT OdTvDatabaseStatistic : public OdTvStatistic
{
public:

  /** \details
    Statistics attribute types for database objects.
  */
  enum Types
  {
    kModel,       // Quantity of models.
    kBlock,       // Quantity of blocks.
    kLinetype,    // Quantity of linetypes.
    kLayer,       // Quantity of layers.
    kTextStyle,   // Quantity of text styles.
    kMaterial,    // Quantity of materials.
    kRasterImage, // Quantity of raster images.
    kDevice,      // Quantity of devices.
    kVisualStyle, // Quantity of visual styles.
    kBackground,  // Quantity of backgrounds.
    //DOM-IGNORE-BEGIN
    kLast         // A special value for internal use.
    //DOM-IGNORE-END

  };

  /** \details
    Creates a new statistics object for database objects with default parameters.
  */
  OdTvDatabaseStatistic();

  /** \details
    Retrieves the quantity of objects with a specified type.
    
    \param type [in] A type of object. Only objects of this type are calculated.
    \returns Returns the quantity of objects that have the specified type.
  */
  OdUInt64 getCount(Types type) const;

   /** \details
    Retrieves the database initial size.
    
    \returns Returns the initial size of the database in bytes.
  */
  OdUInt64 getInitialSize() const;

  /** \details
    Retrieves the size of attributes.
    
    \returns Returns the size of attributes.
  */
  OdUInt64 getAttributesSize() const;

  //DOM-IGNORE-BEGIN
protected:

  OdUInt64Array m_counts;
  OdUInt64 m_initialSize;
  OdUInt64 m_attributesSize;

  //DOM-IGNORE-END
};

#endif //_ODTV_STATISTICS_H_INCLUDED_
