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

#ifndef _DAI_INTEGER_BOUND_H
#define _DAI_INTEGER_BOUND_H

#include "daiBound.h"
#include "daiTypeCode.h"
#include "daiConsts.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class SchemaFiller;

  /** \details
  A class that implements bound whose value is based solely on the schema within which it it declared.
  */
  class DAI_EXPORT IntegerBound : public Bound
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(IntegerBound);
    //DOM-IGNORE-END

    /** \details
    Creates a new integer bound object with specified parameters.
    \param boundValue [in] The integer value for the bound.
    */
    static OdSmartPtr<IntegerBound> createObject(int boundValue);

    /** \details
    Creates a new integer bound defenition with default parameters.
    */
    IntegerBound()
      : m_boundValue(OdDAI::Consts::OdIntUnset)
    {}

    /** \details
    Creates a new integer bound defenition with specified parameters.
    \param boundValue [in] The integer value for the bound.
    */
    IntegerBound(int boundValue)
      : m_boundValue(boundValue)
    {}

    /** \details
    Retreives an integer value for the bound.
    \returns Returns an integer value for the bound.
    */
    int boundValue() const{ return m_boundValue; };

    /** \details
    Retreives a type code of bound.
    \returns Returns a smart pointer to type code of bound.
    */
    virtual const OdTypeCodePtr type() const;

//DOM-IGNORE-BEGIN
  protected:
    int m_boundValue;

    void setBoundValue(int boundValue) { m_boundValue = boundValue; };

    friend class SchemaFiller;
//DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::IntegerBound, integer bound> object.
  */
  typedef OdSmartPtr<IntegerBound> IntegerBoundPtr;
}

#endif // _DAI_INTEGER_BOUND_H
