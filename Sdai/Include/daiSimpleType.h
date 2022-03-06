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

#ifndef _DAI_SIMPLETYPE_H
#define _DAI_SIMPLETYPE_H

#include "daiDictionaryInstance.h"
#include "daiTypeCode.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details
  A class that implements a data type definition for the EXPRESS SCHEMA SIMPLE type.
  */
  class DAI_EXPORT SimpleType : public DictionaryInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(SimpleType);
    //DOM-IGNORE-END

    /** \details
    Retrieves the code of the simple data type.
    \returns A smart pointer to the <link OdTypeCode, type code> object of the simple data type.
    */
    virtual const OdTypeCodePtr type() const = 0;

    /** \details
    Retrieves name of simple type in lower case.
    \returns Returns a const reference to OdAnsiString that contains simple type name in lower case.
    */
    virtual const OdAnsiString& name() const = 0;

    /** \details
    Retrieves name of simple type in upper case.
    \returns Returns a const reference to OdAnsiString that contains simple type name in upper case.
    */
    virtual const OdAnsiString& nameUpperCase() const = 0;
  };

  /** \details
  A data type that represents a smart pointer to a <link OdDAI::SimpleType, simple type> object.
  */
  typedef OdSmartPtr<SimpleType> SimpleTypePtr;

  /** \details
  A data type that represents an STD map of pairs consisting of an STD string and a smart pointer to a <link OdDAI::SimpleType, simple type> object.
  */
  typedef std::map<std::string, SimpleTypePtr> SimpleTypeDictionary;
}

#endif // _DAI_SIMPLETYPE_H
