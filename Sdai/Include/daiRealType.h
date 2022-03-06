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

#ifndef _DAI_REALTYPE_H
#define _DAI_REALTYPE_H

#include "daiSimpleType.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details
  A class that implements a data type definition for the EXPRESS SCHEMA REAL type.
  */
  class DAI_EXPORT RealType : public SimpleType
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(RealType);
    //DOM-IGNORE-END

    /** \details
    Default constructor.
    */
    RealType();

   /** \details
   Constructor with specified parameter.
   \param precision [in] The minumum number of significant digits in a value of the type.
   */
    RealType(int precision);

    /** \details
    Retrieves the minumum number of significant digits in a value of the type.
    \returns Returns the minumum number of significant digits.
    */
    int precision() const { return m_precision; };

    /** \details
    Retrieves the real type code.
    \returns Returns a const pointer to the type code of the real type.
    */
    const OdTypeCodePtr type() const;

    /** \details
    Retrieves name of Real type in lower case.
    \returns Returns a const reference to OdAnsiString that contains Real type name in lower case.
    */
    virtual const OdAnsiString& name() const;

    /** \details
    Retrieves name of Real type in upper case.
    \returns Returns a const reference to OdAnsiString that contains Real type name in upper case.
    */
    virtual const OdAnsiString& nameUpperCase() const;

  private:
    //DOM-IGNORE-BEGIN
    int m_precision;
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::RealType, real type> object.
  */
  typedef OdSmartPtr<RealType> RealTypePtr;

}

#endif // _DAI_REALTYPE_H
