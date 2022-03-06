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

#ifndef _DAI_STRINGTYPE_H
#define _DAI_STRINGTYPE_H

#include "daiSimpleType.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details
  A class that implements a data type definition for the EXPRESS SCHEMA STRING type.
  */
  class DAI_EXPORT StringType : public SimpleType
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(StringType);
    //DOM-IGNORE-END

    /** \details
    Creates a new string type with a specified name.
    \param fixedWidth [in] A flag that determines whether the domain of the created string type has fixed (equal to true) or variable (equal to false) width.
    \param width      [in] A maximum, or for fixed width the exact, number of characters in a value of the type.
    \returns Returns a smart pointer to the created <link OdDAI::StringType, string type> instance.
    */
    static OdSmartPtr<StringType> createObject(
      bool fixedWidth,
      int width = Consts::OdIntUnset);

    /** \details
    Creates a new string type object with default parameters.
    */
    StringType();

    /** \details
    Creates a new string type object with specified parameters.
    \param fixedWidth [in] A flag that determines whether the domain of the created string type has fixed (equal to true) or variable (equal to false) width.
    \param width      [in] A maximum, or for fixed width the exact, number of characters in a value of the type.
    */
    StringType(bool fixedWidth, int width = Consts::OdIntUnset);

    /** \details
    Retrieves the maximum, or for fixed width the exact, number of characters in a value of the type.
    \returns Returns the number of characters.
    */
    int width() const { return m_width; };

    /** \details
    Determines whether the string type has fixed width.
    \returns Returns true if the string type has fixed width; otherwise the method returns false.
    */
    bool fixedWidth() const { return m_fixedWidth; };

    /** \details
    Retrieves the string type code.
    \returns Returns a const pointer to the type code of the string type.
    */
    virtual const OdTypeCodePtr type() const { return m_type; };

    /** \details
    Retrieves name of String type in lower case.
    \returns Returns a const reference to OdAnsiString that contains String type name in lower case.
    */
    virtual const OdAnsiString& name() const;

    /** \details
    Retrieves name of String type in upper case.
    \returns Returns a const reference to OdAnsiString that contains String type name in upper case.
    */
    virtual const OdAnsiString& nameUpperCase() const;

  protected:
    //DOM-IGNORE-BEGIN
    int m_width;
    bool m_fixedWidth;
    OdTypeCodePtr m_type;

    void setWidth(int width) { m_width = width; };
    void setFixedWidth(bool fixedWidth) { m_fixedWidth = fixedWidth; };
    static OdTypeCodePtr createTypeCode(bool fixedWidth, int width);
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::StringType, string type> object.
  */
  typedef OdSmartPtr<StringType> StringTypePtr;

}

#endif // _DAI_STRINGTYPE_H
