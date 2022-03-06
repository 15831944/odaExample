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

#ifndef _DAI_BOUND_H
#define _DAI_BOUND_H

#include "daiDictionaryInstance.h"
#include "daiTypeCode.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class SchemaFiller;

  /** \details
  A class that defines limit on an EXPRESS type.
  */
  class DAI_EXPORT Bound : public DictionaryInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(Bound);
    //DOM-IGNORE-END

    /** \details
    Retreives a type code of bound.
    \returns Returns a smart pointer to type code of bound.
    */
    virtual const OdTypeCodePtr type() const = 0;

    //DOM-IGNORE-BEGIN
    friend class SchemaFiller;
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::Bound, bound> object.
  */
  typedef OdSmartPtr<Bound> BoundPtr;
}

#endif // _DAI_BOUND_H
