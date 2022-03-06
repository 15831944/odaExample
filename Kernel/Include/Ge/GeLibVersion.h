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

#pragma once

#include "GeExport.h"
#include "TD_PackPush.h"

#define IMAGE_MAJOR_VER 2           
#define IMAGE_MINOR_VER 0           
#define IMAGE_CORRECTIVE_VER 0      
#define IMAGE_INTERNAL_VER 0        

/** \details
    This class provides management of GeLib versions.

    Corresponding C++ library: TD_Ge

    <group OdGe_Classes> 
*/
class GE_TOOLKIT_EXPORT OdGeLibVersion
{
public:
  /** \details
    Default constructor for the OdGeLibVersion class.
  */
  OdGeLibVersion ();
  
  /** \details
    Copy constructor for the OdGeLibVersion class.
    
    \param source [in]  A OdGeLibVersion object to be copied.
  */
  OdGeLibVersion (
    const OdGeLibVersion& source);
  
  /** \details
    Constructor for the OdGeLibVersion class.
    
    \param major [in]  Major version.
    \param minor [in]  Minor version.
    \param corrective [in]  Corrective version.
    \param schema [in]  Schema version.
  */
  OdGeLibVersion (
    OdUInt8 major, 
    OdUInt8 minor,
    OdUInt8 corrective,
    OdUInt8 schema);

  /** \details
    Returns the major version of GeLib.
  */
  OdUInt8 majorVersion () const; 

  /** \details
    Returns the minor version of GeLib.
  */
  OdUInt8 minorVersion () const; 

  /** \details
    Returns the corrective version of GeLib.
  */
  OdUInt8 correctiveVersion () const;
   
  /** \details
    Returns the schema version of GeLib.
  */
  OdUInt8 schemaVersion () const;

  /** \details
    Sets the major version of GeLib.

    \param major [in]  Major version.
  */
  OdGeLibVersion& setMajorVersion (
    OdUInt8 major); 

  /** \details
    Sets the minor version of GeLib.

    \param minor [in]  Minor version.
  */
  OdGeLibVersion& setMinorVersion (
    OdUInt8 minor); 

  /** \details
    Sets the corrective version of GeLib.

    \param corrective [in]  Corrective version.
  */
  OdGeLibVersion& setCorrectiveVersion (
    OdUInt8 corrective); 

  /** \details
    Sets the schema version of GeLib.

    \param schema [in]  Schema version.
  */
  OdGeLibVersion& setSchemaVersion (
    OdUInt8 schema);

  /** \details
    Comparison operator for the OdGeLibVersion object.
    
    \param libVersion     [in]  OdGeLibVersion object to compare.
    
    \returns
    A boolean value that indicates whether the input library version is identical to this library version.
  */
  bool operator == (
    const OdGeLibVersion& libVersion) const; 
  
  /** \details
    Comparison operator for the OdGeLibVersion object.
    
    \param libVersion     [in]  OdGeLibVersion object to compare.
    
    \returns
    A boolean value that indicates whether the input interval is not identical to this interval.
  */
  bool operator != (
    const OdGeLibVersion& libVersion) const; 
  
  /** \details
    Comparison operator for the OdGeLibVersion object.
    
    \param libVersion     [in]  OdGeLibVersion object to compare.
    
    \returns
    A boolean value that indicates whether the input library version is less than this library version.
  */
  bool operator < (
    const OdGeLibVersion& libVersion) const;
  
  /** \details
    Comparison operator for the OdGeLibVersion object.
    
    \param libVersion     [in]  OdGeLibVersion object to compare.
    
    \returns
    A boolean value that indicates whether the input library version is less than or equal to this library version.
  */
  bool operator <= (
    const OdGeLibVersion& libVersion) const; 
  
  /** \details
    Comparison operator for the OdGeLibVersion object.
    
    \param libVersion     [in]  OdGeLibVersion object to compare.
    
    \returns
    A boolean value that indicates whether the input library version is greater than this library version.
  */
  bool operator > (
    const OdGeLibVersion& libVersion) const; 
  
  /** \details
    Comparison operator for the OdGeLibVersion object.
    
    \param libVersion     [in]  OdGeLibVersion object to compare.
    
    \returns
    A boolean value that indicates whether the input library version is greater than or equal to this library version.
  */
  bool operator >= (
    const OdGeLibVersion& libVersion) const;
//DOM-IGNORE-BEGIN
  GE_STATIC_EXPORT static const OdGeLibVersion kRelease0_95; // GeLib release 0.

  GE_STATIC_EXPORT static const OdGeLibVersion kReleaseSed; // GeLib 14.0 release. 

  GE_STATIC_EXPORT static const OdGeLibVersion kReleaseTah; // GeLib 15.0 release.

private:
  OdUInt8 mVersion[10];
//DOM-IGNORE-END
};

#include "TD_PackPop.h"

