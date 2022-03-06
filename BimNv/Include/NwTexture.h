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

#ifndef __TNW_TEXTURE_H__
#define __TNW_TEXTURE_H__

#include "NwMaterial.h"
#include "NwTextureValueType.h"
#include "NwModelUnits.h"

class OdGiRasterImage;
class OdGeMatrix3d;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiRasterImage object pointers.
*/
typedef OdSmartPtr<OdGiRasterImage> OdGiRasterImagePtr;

/** \details
  This class represents a geometry texture within the model hierarchy.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwTexture : public OdNwMaterial
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwTexture);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwTexture
    class.
  */
  OdNwTexture();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwTexture();

public:

  /** \details
    Returns a string parameter value depending on the value of the mask.

    \param type [in] Parameter type specified by the NwTextureValueType::Enum.
    \param pResult [out] Pointer to the OdResult object with the error code.

    \returns
    Returns an OdString value depending on the type.

    \remarks
    The type must match NwTextureValueType::Enum value for OdString values, in this case pResult will be eOk, in other cases - eNotApplicable.

  */
  OdString getStringValue(NwTextureValueType::Enum type, OdResult* pResult = NULL) const;


  /** \details
    Returns a double parameter value depending on the value of the mask.

    \param type [in] Parameter type specified by the NwTextureValueType::Enum.
    \param pResult [out] Pointer to the OdResult object with the error code.

    \returns
    Returns a double value depending on the type.

    \remarks
    The type must match NwTextureValueType::Enum value for double values, in this case pResult will be eOk, in other cases - eNotApplicable.

  */
  double getDoubleValue(NwTextureValueType::Enum type, OdResult* pResult = NULL) const;

  /** \details
    Returns a units parameter value depending on the value of the mask.

    \param type [in] Parameter type specified by the NwTextureValueType::Enum.
    \param pResult [out] Pointer to the OdResult object with the error code.

    \returns
    Returns an NwModelUnits::Enum value depending on the type.

    \remarks
    getUnitValue() returns one of the following:

    <table>
    Name                                 Value   Description
    NwModelUnits::UNITS_METERS           0x00    SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second
    NwModelUnits::UNITS_CENTIMETERS      0x01    1 100th of an SI meter
    NwModelUnits::UNITS_MILLIMETERS      0x02    1 1000th of an SI meter
    NwModelUnits::UNITS_FEET             0x03    1 3rd of a yard
    NwModelUnits::UNITS_INCHES           0x04    1 12th of a foot, 2.54 SI centimeters
    NwModelUnits::UNITS_YARDS            0x05    Imperial yard, 0.9144 SI meters
    NwModelUnits::UNITS_KILOMETERS       0x06    1000 SI meters
    NwModelUnits::UNITS_MILES            0x07    1760 yards
    NwModelUnits::UNITS_MICROMETERS      0x08    1 1,000,000th of an SI meter, micron
    NwModelUnits::UNITS_MILS             0x09    1 1,000th of an inch
    NwModelUnits::UNITS_MICROINCHES      0x0A    1 1,000,000th of an inch
    </table>

    The type must match NwTextureValueType::Enum value for unit values, in this case pResult will be eOk, in other cases - eNotApplicable.

  */
  NwModelUnits::Enum getUnitValue(NwTextureValueType::Enum type, OdResult* pResult = NULL) const;

  /** \details
    Returns a raster image parameter value depending on the value of the mask.

    \param type [in] Parameter type specified by the NwTextureValueType::Enum.
    \param pResult [out] Pointer to the OdResult object with the error code.

    \returns
    Returns an OdGiRasterImagePtr value depending on the type.

    \remarks
    The type must match NwTextureValueType::Enum value for raster image values, in this case pResult will be eOk, in other cases - eNotApplicable.

  */
  OdGiRasterImagePtr getRasterImageValue(NwTextureValueType::Enum type, OdResult* pResult = NULL) const;

  /** \details
    Returns a OdGeMatrix3d parameter value depending on the value of the mask.

    \param type [in] Parameter type specified by the NwTextureValueType::Enum.
    \param desiredUnits [in] Parameter type specified by the NwModelUnits::Enum with model units in which mapping transformation need to calculate.
    \param pResult [out] Pointer to the OdResult object with the error code.

    \returns
    Returns an OdGeMatrix3d value depending on the type.

    \remarks
    The type must match NwTextureValueType::Enum value for matrix values, in this case pResult will be eOk, in other cases - eNotApplicable.

    The desiredUnits must be one of the following:
    <table>
    Name                                 Value   Description
    NwModelUnits::UNITS_METERS           0x00    SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second
    NwModelUnits::UNITS_CENTIMETERS      0x01    1 100th of an SI meter
    NwModelUnits::UNITS_MILLIMETERS      0x02    1 1000th of an SI meter
    NwModelUnits::UNITS_FEET             0x03    1 3rd of a yard
    NwModelUnits::UNITS_INCHES           0x04    1 12th of a foot, 2.54 SI centimeters
    NwModelUnits::UNITS_YARDS            0x05    Imperial yard, 0.9144 SI meters
    NwModelUnits::UNITS_KILOMETERS       0x06    1000 SI meters
    NwModelUnits::UNITS_MILES            0x07    1760 yards
    NwModelUnits::UNITS_MICROMETERS      0x08    1 1,000,000th of an SI meter, micron
    NwModelUnits::UNITS_MILS             0x09    1 1,000th of an inch
    NwModelUnits::UNITS_MICROINCHES      0x0A    1 1,000,000th of an inch
    </table>
  */
  OdGeMatrix3d getMatrixValue(NwTextureValueType::Enum type, NwModelUnits::Enum desiredUnits, OdResult* pResult = NULL) const;

  /** \details
    Returns the diffuse intensity of this texture.

    \returns Returns a double value of the diffuse intensity of this texture.
  */
  double getDiffuseIntensity() const;

  /** \details
    Returns the specular intensity of this texture.

    \returns Returns a double value of the specular intensity of this texture.
  */
  double getSpecularIntensity() const;

  /** \details
    Returns the reflect intensity of this texture.

    \returns Returns a double value of the reflect intensity of this texture.
  */
  double getReflectIntensity() const;

  /** \details
    Returns the bump amount value of this texture.

    \returns Returns a double value of the bump amount of this texture.
  */
  double getBumpAmount() const;

  /** \details
    Returns the tint color of this texture.

    \param color [out] OdNwColor object for the tint color of this texture.

    \returns Returns eOk if successful, or an appropriate error code if not.
  */
  OdResult getTint(OdNwColor& color) const;

  /** \details
    Indicates whether a tint color is used for this texture.

    \returns Returns true if a tint color is used for this texture, or returns false if not.
  */
  bool IsUseTintColor() const;

  /** \details
    Returns the transmit color of this texture.

    \param color [out] OdNwColor object for the transmit color of this texture.

    \returns Returns eOk if successful, or an appropriate error code if not.
  */
  OdResult getTransmitColor(OdNwColor& color) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwTexture object pointers.
*/
typedef OdSmartPtr<OdNwTexture> OdNwTexturePtr;

#endif //__TNW_TEXTURE_H__
