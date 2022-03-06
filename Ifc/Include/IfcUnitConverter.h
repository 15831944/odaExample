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

// IfcUnitConverter.h: interface for the OdIfcUnitConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ODA_ODIFCUNITCONVERTER_H_INCLUDED_)
#define ODA_ODIFCUNITCONVERTER_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcBuildOptions.h"

class OdIfcFile;

 /** \details
A class that implements conversion of different units to the SI units.
*/
  class IFCCORE_EXPORT OdIfcUnitConverter
  {
  public:

    /** \details
    Performs an attempt to convert a specified unit to the SI unit.
    \param unitType [in] A string that contains the type of the unit to be converted.
    \param val      [in] A unit value.
    \returns A double value that contains the converted value of the specified unit type.
    \remarks
    The unit type value must belong to the IfcUnitEnum of the current schema.
    */
    double convertToSIUnit(const OdAnsiString& unitType, double val) const;

    /** \details
    Appends a new convertible unit.
    \param unitType [in] A string that contains the type of the convertible unit.
    \param unitId   [in] An identifier of the corresponding IfcConversionBasedUnit object.
    \remarks
    The unit type value must belong to the IfcUnitEnum of the current schema.
    */
    void appendUnit(const OdAnsiString& unitType, const OdDAIObjectId& unitId);

    /** \details
    Appends a new convertible unit.
    \param unitId [in] An identifier of the corresponding IfcConversionBasedUnit object.
    */
    void appendUnit(const OdDAIObjectId& unitId);
    
    /** \details
    Removes all convertible units.
    */
    void clearUnits();
//DOM-IGNORE-BEGIN
  private:
    std::map<OdAnsiString, OdDAIObjectId> m_units;

    double convertIfcConversionBasedUnit          (const OdDAIObjectId& unitId, double val) const;
    double convertIfcConversionBasedUnitWithOffset(const OdDAIObjectId& unitId, double val) const;

    friend class OdIfcFile;
//DOM-IGNORE-END
  };
  
  /** \details 
  A data type that represents a smart pointer to an <link OdIfcUnitConverter, OdIfcUnitConverter> object.
  */
  typedef OdSharedPtr<OdIfcUnitConverter> OdIfcUnitConverterPtr;


#endif // !defined(ODA_ODIFCUNITCONVERTER_H_INCLUDED_)

