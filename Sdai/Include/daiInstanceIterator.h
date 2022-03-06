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

#ifndef _DAI_INSTANCEITERATOR_H_
#define _DAI_INSTANCEITERATOR_H_

#include "daiObjectId.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details
  An abstract class that provides the interface of an iterator through entities of the model.
  An iterator allows you to get sequential access to entities that are contained in any collection.
  */
  class DAI_EXPORT InstanceIterator
  {
  public:

    /** \details
    Destroys the iterator object.
    */
    virtual ~InstanceIterator() {};

    /** \details
    Retrieves whether the end of the instance list is reached.
    \returns Returns true if the end of the instance list is reached; otherwise the method returns false.
    */
    virtual bool done() const = 0;

    /** \details
    Moves to the next instance in the list.
    */
    virtual void step() = 0;

    /** \details
    Retrieves the identifier of the iterator object.
    \returns Returns the iterator's identifier.
    */
    virtual OdDAIObjectId id() const = 0;
  };
  
  /** \details 
  A data type that represents a smart pointer to an <link OdDAI::InstanceIterator, InstanceIterator> object.
  */
  typedef OdSharedPtr<InstanceIterator> InstanceIteratorPtr;

}

#endif // _DAI_INSTANCEITERATOR_H_
