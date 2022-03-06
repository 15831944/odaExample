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

#ifndef _BFC_FILE_ATTRIBUTES_GROUP_H
#define _BFC_FILE_ATTRIBUTES_GROUP_H

#include "BcfCommon.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  /** \details
  A class that stores and operates the group of a BCF file attributes.
  */
  class BCF_EXPORT OdBcfFileAttributesGroup
  {
  public:
    /** \details 
    Creates a new BCF file attributes group object with default parameters.
    */
    OdBcfFileAttributesGroup();

    /** \details
    Checks whether a file attribute group instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const;

    /** \details 
    A string that contains the name of the related IFC project.
    */
    OdString m_ifcProject;
    
    /** \details 
    A string that contains the name of the related IFC spatial structure element.
    */
    OdString m_ifcSpatialStructureElement;
    
    /** \details 
    A flag that determines whether the attribute group is an external one (if equals to true) or not (if equals to false).
    */
    bool     m_isExternal;
  };

  namespace Utils
  {
    inline bool isUnset(const OdBcf::OdBcfFileAttributesGroup & value)
    {
      return OdBcf::Utils::isUnset(value.m_ifcProject) &&
        OdBcf::Utils::isUnset(value.m_ifcSpatialStructureElement) &&
        OdBcf::Utils::isUnset(value.m_isExternal);
    }
  }

} //namespace OdBcf

#endif // _BFC_FILE_ATTRIBUTES_GROUP_H
