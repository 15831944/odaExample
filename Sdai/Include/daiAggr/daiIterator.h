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

#ifndef _DAI_ITERATOR_H
#define _DAI_ITERATOR_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"
#include "RxValue.h"

#include "daiBuildOptions.h"
#include "daiAggr/daiAggr.h"

/** \details 
Implements the Data Access Interface (DAI) which provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details
  An abstract class that provides the interface of an iterator for traversing through an aggregate. 
  An iterator provides sequential access to data objects in an aggregate.
  Sequential access assumes that before getting access to an element you have to read elements 
  that are placed before the desired element in the aggregate.
  */
  class DAI_EXPORT Iterator
  {
  public:
    /** \details 
    Destroys the iterator object.
    */
    virtual ~Iterator() {};
    
    /** \details 
    Moves the iterator to the beginning of an aggregate instance. 
    When the iterator is at the beginning of an aggregate, it doesn't refer to an element (there is no current element).
    \remarks
    Call the <link OdDAI::Iterator::next, next()> method after this method to make the last element of an aggregate the current one.
    Applicable for ordered aggregates (arrays, lists).
    */
    virtual void beginning() = 0;
    
    /** \details 
    Moves the iterator to the next element of an aggregate relative to the current one.
    The next element becomes the current one unless the end of an aggregate is reached.
    \returns 
    true if the move to the next element was performed successfully; otherwise the method returns false. 
    The false value returned by the method means that the end of the aggregation container is reached and the iterator can not be moved anymore.
    For example: 
    \code
    <pre>
      for (it->beginning(); it->next(); )
      {
        it->getCurrentMember()...
      }
    </pre>
    \remarks
    Applicable for ordered aggregates (arrays, lists).
    */
    virtual bool next() = 0;
    
    /** \details 
    Moves the iterator to the previous element of an aggregate relative to the current one.
    The previous element becomes the current one unless the beginning of an aggregate is reached.
    \returns 
    true if the move to the previous element was performed successfully; otherwise the method returns false. 
    The false value returned by the method means that the beginning of the aggregation container is reached and the iterator can not be moved anymore.
    For example: 
    \code
    <pre>
      for (it->end(); it->previous(); )
      {
        it->getCurrentMember()...
      }
    </pre>
    \remarks
    Applicable for ordered aggregates (arrays, lists).
    */
    virtual bool previous() = 0;

    /** \details 
    Moves the iterator to the end of an aggregate instance. 
    When the iterator is at the end of an aggregate, it doesn't refer to an element (there is no current element). 
    \remarks
    Call the <link OdDAI::Iterator::previous, previous()> method after this method to make the last element of an aggregate the current one.
    Applicable for ordered aggregates (arrays, lists).
    */
    virtual void end() = 0;

    /** \details 
    Creates an aggregate and makes it the current element of the iterator. 
    The created aggregate replaces the current item referred to by the iterator.
    \returns A raw pointer to the created aggregate instance.
    \remarks 
    This method can be used to create nested aggregates.
    */
    virtual Aggr* createAggrInstanceAsCurrentMember() = 0;
    
    /** \details 
    Creates an aggregate and places it before the current element referred to by the iterator. 
    \returns A raw pointer to the created aggregate instance.
    \remarks 
    This method can be used to create nested aggregates.
    */
    virtual Aggr* createAggrInstanceBeforeCurrentMember() = 0;
    
    /** \details 
    Creates an aggregate and places it after the current element referred to by the iterator. 
    \returns A raw pointer to the created aggregate instance.
    \remarks 
    This method can be used to create nested aggregates.
    */
    virtual Aggr* createAggrInstanceAfterCurrentMember() = 0;

    /** \details 
    Retrieves the current element of an aggregate referred to by the iterator. 
    \returns 
    An instance of the <exref target="https://docs.opendesign.com/tkernel/OdRxValue.html">OdRxValue</exref> class 
    that represents the current element referred to by the iterator.
    */
    virtual OdRxValue getCurrentMember() const = 0;
    
    /** \details 
    Retrieves the value of the current element of an aggregate referred to by the iterator. 
    \returns An instance of the <exref target="https://docs.opendesign.com/tkernel/OdRxValue.html">OdRxValue</exref> class 
    that represents the value of the current element referred to by the iterator.
    */
    virtual OdRxValue getCurrentMemberValue() const = 0;

    /** \details 
    Sets a new current element of an aggregate for the iterator. 
    The new element replaces the previously current element.
    \param anItem [in] An instance of the <exref target="https://docs.opendesign.com/tkernel/OdRxValue.html">OdRxValue</exref> class that represents the new element to be set as current.
    */
    virtual void putCurrentMember(const OdRxValue& anItem) = 0;
    
    /** \details 
    Adds a new specified element to the list aggregate before the element referred to by the iterator. 
    The new element is added before the current element; the current element that the iterator refers to is not changed.
    \param anItem [in] An instance of the <exref target="https://docs.opendesign.com/tkernel/OdRxValue.html">OdRxValue</exref> class that represents the new element to be added.
    \remarks 
    The method throws an exception with the AI_NVLD code value if the aggregate instance is not a list.
    */
    virtual void addBeforeCurrentMember(const OdRxValue& anItem) = 0; 
    
    /** \details 
    Adds a new specified element to the list aggregate after the element referred to by the iterator. 
    The new element is added after the current element; the current element that the iterator refers to is not changed.
    \param anItem [in] An instance of the <exref target="https://docs.opendesign.com/tkernel/OdRxValue.html">OdRxValue</exref> class that represents the new element to be added.
    \remarks 
    The method throws an exception with the AI_NVLD code value if the aggregate instance is not a list.
    */
    virtual void addAfterCurrentMember(const OdRxValue& anItem) = 0;
    
    /** \details 
    Removes the current element from an aggregate.
    \returns true if the element is successfully removed; otherwise, the method returns false.
    */
    virtual bool removeCurrentMember() = 0;

    /** \details 
    Retrieves the value bound of the current element referred to by the iterator.
    \returns An unsigned integer value that represents the value bound.
    */
    virtual int getValueBound() const = 0;
    
    /** \details 
    Determines whether the value of the current array element referred to by the iterator is set.
    \returns true if the value of the current element is set; otherwise, the method returns false.
    \remarks
    Applicable only for arrays.
    */
    virtual bool testCurrentMember() const = 0;

    /** \details 
    Retrieves the type of the current element referred to by the iterator.
    \returns 
    An instance of the <exref target="https://docs.opendesign.com/tkernel/OdRxValueType.html">OdRxValueType</exref> class 
    that contains information about the type of the current element.
    */
    virtual const OdRxValueType& type() const = 0;
  };
  
  /** \details 
  A data type that represents a smart pointer to an <link OdDAI::Iterator Iterator> object.
  */
  typedef OdSharedPtr<Iterator> IteratorPtr;

}


#endif // _DAI_ITERATOR_H
