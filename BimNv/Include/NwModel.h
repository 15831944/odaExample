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

#ifndef __TNW_MODEL_H__
#define __TNW_MODEL_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#include "NwModelType.h"
#define STL_USING_LIST
#include "OdaSTL.h"
#include "NwModelUnits.h"

class OdGeMatrix3d;
class OdNwDataProperty;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwDataProperty object pointers.
*/
typedef OdSmartPtr<OdNwDataProperty> OdNwDataPropertyPtr;

/** \details
  This class represents a model in the database.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwModel : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwModel);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwModel
    class.
  */
  OdNwModel();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwModel();

public:

  /** \details
    Returns the filename of the model.

    \returns Returns the filename of the model.
  */
  OdString getFileName() const;

  /** \details
    Returns the path of the model.

    \returns Returns the path of the model.
  */
  OdString getPath() const;

  /** \details
    Returns the name of the original source file from which this model was first converted.

    \returns Name of the original source file, or an empty string if the filename is unknown.
  */
  OdString getSourceFileName() const;

  /** \details
    Checks whether the model is changed after loading from the original file.

    \returns true if the model is changed, or false otherwise.
  */
  bool isChange() const;

  /** \details
    Returns a transformation matrix applied to the model.

    \returns Transformation matrix as an OdGeMatrix3d object.
  */
  OdGeMatrix3d getTransform() const;

  /** \details
    Returns the type of the loaded model. 
    
    \remarks
      The returned type can be one of the following:
    
    <table>
    Name                        Value   Description
    NwModelType::undefined      0       Original model is undefined.
    NwModelType::dwg_model      1       Original model is from a .dwg file.
    NwModelType::dgn_model      2       Original model is a DGN model.
    NwModelType::revit_model    3       Original model is an Autodesk(R) Revit(R) model.
    NwModelType::nw_model       4       Original model is an Autodesk Navisworks(R) model.
    NwModelType::nw_13_model    5       Original model is an Autodesk Navisworks model.
    </table>
  */
  NwModelType::Enum getType() const;

  /** \details
    Returns the measuring units set for this model.

    \remarks
    Returned value can be one of the following:

    <table>
    Name                                 Value   Description
    NwModelUnits::UNITS_METERS           0x00    SI meter.
    NwModelUnits::UNITS_CENTIMETERS      0x01    1 100th of an SI meter.
    NwModelUnits::UNITS_MILLIMETERS      0x02    1 1000th of an SI meter.
    NwModelUnits::UNITS_FEET             0x03    1 3rd of a yard.
    NwModelUnits::UNITS_INCHES           0x04    1 12th of a foot, 2.54 SI centimeters.
    NwModelUnits::UNITS_YARDS            0x05    Imperial yard, 0.9144 SI meters.
    NwModelUnits::UNITS_KILOMETERS       0x06    1000 SI meters
    NwModelUnits::UNITS_MILES            0x07    1760 yards
    NwModelUnits::UNITS_MICROMETERS      0x08    1 1,000,000th of an SI meter, micron
    NwModelUnits::UNITS_MILS             0x09    1 1,000th of an inch
    NwModelUnits::UNITS_MICROINCHES      0x0A    1 1,000,000th of an inch
    </table>
  */
  NwModelUnits::Enum getUnits() const;

  /** \details
    Gets the property list of the model as std::list.

    \param lProperties [out] std::list with smart pointers to properties as values.
    \returns eOk if the properties are retrieved successfully, or an appropriate error code otherwise.
  */
  OdResult getProperties(std::list<OdNwDataPropertyPtr>& lProperties) const;

  /** \details
    Returns the globally unique identifier assigned to this model.

    \returns Model's globally unique identifier as an OdGUID object.
  */
  OdGUID getGuId() const;

  /** \details
    Returns the original GUID that the model was created with.

    \returns The original GUID that the model was created with as an OdGUID object.

    \remarks
      If the model is appended to a sheet several times, each model instance has the same source GUID but different GUIDs.
  */
  OdGUID getSourceGuId() const;

public:
  /** \details
    Sets the path to the model.

    \param path [in] String with the model path to set.
    \returns eOk if the path is set successfully, or an appropriate error code otherwise.
  */
  OdResult setSourcePath(const OdString& path);

  /** \details
    Sets the transformation matrix for the model.

    \param trMtrx [in] Transformation matrix to set.
  */
  void setTransform(const OdGeMatrix3d& trMtrx);

  /** \details
    Sets the measuring units for this model.

    \param units [in] Measuring units to set.
    \remarks Units must be one of the following:

    <table>
    Name                                 Value   Description
    NwModelUnits::UNITS_METERS           0x00    SI meter.
    NwModelUnits::UNITS_CENTIMETERS      0x01    1 100th of an SI meter.
    NwModelUnits::UNITS_MILLIMETERS      0x02    1 1000th of an SI meter.
    NwModelUnits::UNITS_FEET             0x03    1 3rd of a yard.
    NwModelUnits::UNITS_INCHES           0x04    1 12th of a foot, 2.54 SI centimeters.
    NwModelUnits::UNITS_YARDS            0x05    Imperial yard, 0.9144 SI meters.
    NwModelUnits::UNITS_KILOMETERS       0x06    1000 SI meters
    NwModelUnits::UNITS_MILES            0x07    1760 yards
    NwModelUnits::UNITS_MICROMETERS      0x08    1 1,000,000th of an SI meter, micron
    NwModelUnits::UNITS_MILS             0x09    1 1,000th of an inch
    NwModelUnits::UNITS_MICROINCHES      0x0A    1 1,000,000th of an inch
    </table>
  */
  void setUnits(NwModelUnits::Enum units);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwModel object pointers.
*/
typedef OdSmartPtr<OdNwModel> OdNwModelPtr;

#endif //__TNW_MODEL_H__
