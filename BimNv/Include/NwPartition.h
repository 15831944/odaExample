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

#ifndef __TNW_PARTITION_H__
#define __TNW_PARTITION_H__

#include "NwModelItem.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#include "NwModelUnits.h"

class OdGeVector3d;
/** \details
  This class represents an instance node within the model hierarchy.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwPartition : public OdNwModelItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwPartition);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwPartition object.
  */
  OdNwPartition();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwPartition();

public:
  /** \details
    Returns the name of the original source file from which this model was first
    converted.

    \returns Name of the original source file, or an empty string if the
    filename is unknown.
  */
  OdString getSourceFileName() const;

  /** \details
    Returns the name of the application in which this model was first created.

    \returns Name of the application in which this model was first created.
  */
  OdString getCreator() const;
  
  /** \details
    Returns the model units of the original source file in which this model was first created.

    \returns Units of the original source file in which this model was first created.

    \remarks
    getUnits() Returns one of the following:

    <table>
    Name                              Value   Description
    NwModelUnits::UNITS_METERS        0x00    SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second.
    NwModelUnits::UNITS_CENTIMETERS   0x01    1/100th of an SI meter.
    NwModelUnits::UNITS_MILLIMETERS   0x02    1/1000th of an SI meter.
    NwModelUnits::UNITS_FEET          0x03    1/3rd of a yard.
    NwModelUnits::UNITS_INCHES        0x04    1/12th of a foot, 2.54 SI centimeters.
    NwModelUnits::UNITS_YARDS         0x05    Imperial yard, 0.9144 SI meters.
    NwModelUnits::UNITS_KILOMETERS    0x06    1000 SI meters.
    NwModelUnits::UNITS_MILES         0x07    1760 yards.
    NwModelUnits::UNITS_MICROMETERS   0x08    1/1,000,000th of an SI meter, micron.
    NwModelUnits::UNITS_MILS          0x09    1/1,000th of an inch.
    NwModelUnits::UNITS_MICROINCHES   0x0A    1/1,000,000th of an inch.
    </table>
  */
  NwModelUnits::Enum getUnits() const;

  /** \details
    Set the model units in which data from this partition are measured.

    \param units  [in] model units of this partition.

    \returns eOk if units setting is successfully, or eNotApplicable is units is not linear.

    \remarks
    Model units from database's root model item are influence for all database data(for example - current viewpoint).
    units must be one of the following:

    <table>
    Name                              Value   Description
    NwModelUnits::UNITS_METERS        0x00    SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second.
    NwModelUnits::UNITS_CENTIMETERS   0x01    1/100th of an SI meter.
    NwModelUnits::UNITS_MILLIMETERS   0x02    1/1000th of an SI meter.
    NwModelUnits::UNITS_FEET          0x03    1/3rd of a yard.
    NwModelUnits::UNITS_INCHES        0x04    1/12th of a foot, 2.54 SI centimeters.
    NwModelUnits::UNITS_YARDS         0x05    Imperial yard, 0.9144 SI meters.
    NwModelUnits::UNITS_KILOMETERS    0x06    1000 SI meters.
    NwModelUnits::UNITS_MILES         0x07    1760 yards.
    NwModelUnits::UNITS_MICROMETERS   0x08    1/1,000,000th of an SI meter, micron.
    NwModelUnits::UNITS_MILS          0x09    1/1,000th of an inch.
    NwModelUnits::UNITS_MICROINCHES   0x0A    1/1,000,000th of an inch.
    </table>
  */
  OdResult setUnits(NwModelUnits::Enum units);

  /** \details
    Returns the direction to the Top orthogonal view of a model.

    \returns Instance of the OdGeVector3d as direction to the Top orthogonal view of a model. If vector isn't defined returns Zero.
  */
  OdGeVector3d getUpVector() const;
  
  /** \details
    Sets the direction of the Up orthogonal view of a model.
  
    \param val [in] Direction to the Up orthogonal view of a model.
  */
  void setUpVector(const OdGeVector3d &val);
  
  /** \details
    Returns the direction to the North (Back) orthogonal view of a model.
  
  \returns Instance of the OdGeVector3d as direction to the North (Back) orthogonal view of a model. If vector isn't defined returns Zero. 
  */
  OdGeVector3d getNorthVector() const;

  /** \details
    Sets the direction of the North orthogonal view of a model.
  
    \param val [in] Direction to the North orthogonal view of a model.
  */
  void setNorthVector(const OdGeVector3d &val);
  
  /** \details
  Returns the direction to the Front orthogonal view of a model.
  
  \returns Instance of the OdGeVector3d as direction to the Front orthogonal view of a model. If vector isn't defined returns Zero. 
  */
  OdGeVector3d getFrontVector() const;
  
  /** \details
    Sets the direction of the Front orthogonal view of a model.
  
    \param val [in] Direction to the Front orthogonal view of a model.
  */
  void setFrontVector(const OdGeVector3d &val);
  

  /** \details
    Adds a new model item node to the partition.

    \param name        [in] Name of the model item.
    \param displayName [in] Display name of the model item.
    \param icon        [in] type of new child model item.

    \returns Object ID of the new OdNwModelItem object.

    \remarks
    The method works only for the root partition.

    The icon can be one of the following:

    <table>
    Name                                Value   Description
    NwModelItemIcon::NONE               0x0     model item doesn't have type
    NwModelItemIcon::FILE               0x1     model item type is file
    NwModelItemIcon::LAYER              0x2     model item type is layer
    NwModelItemIcon::COLLECTION         0x3     model item type is collection
    NwModelItemIcon::GROUP              0x4     model item type is group
    NwModelItemIcon::INSERT_GROUP       0x5     model item type is insert group
    NwModelItemIcon::COMPOSITE_OBJECT   0x6     model item type is composite object
    NwModelItemIcon::INSERT_GEOMETRY    0x7     model item type is insert geometry
    NwModelItemIcon::GEOMETRY           0x8     model item type is geometry
    </table>

    The method is deprecated. Use OdNwModelItem::addModelItem instead.
  */
  OdNwObjectId addModelItem(OdString name, OdString displayName, NwModelItemIcon::Enum icon = NwModelItemIcon::GEOMETRY);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwPartition object pointers.
*/
typedef OdSmartPtr<OdNwPartition> OdNwPartitionPtr;

#endif //__TNW_PARTITION_H__
