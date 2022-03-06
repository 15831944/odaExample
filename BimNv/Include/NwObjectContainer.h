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


#ifndef __NW_OBJECTCONTAINER_H__
#define __NW_OBJECTCONTAINER_H__

#include "OdArray.h"
#include "RxObjectImpl.h"
#include "NwObjectIterator.h"
#define STL_USING_ALGORITHM
#include "OdaSTL.h"

/** \details
  This class represents the internal data structure for storing IDs.

  <group OdNw_Classes>
*/
typedef OdNwObjectIdArray NwIdContainer;
//DOM-IGNORE-BEGIN
class NwIdContainerType
{
public:
  typedef OdNwObjectId item;
  typedef NwIdContainer container;
  typedef NwIdContainer::iterator iterator;
  typedef NwIdContainer::const_iterator const_iterator;
  
  /** \details
    Returns true if the iterator has reached the end.
   */
  static bool isDone(const container* pContainer, const const_iterator& iter)
  { 
    return (iter == pContainer->end() || iter < pContainer->begin());
  }
  
  /** \details
    Finds the ID of a container.
    \param pContainer Constant pointer to the container.
    \param pContainer Constant reference to the ID.
    \returns const_iterator if an ID is found, or end() if an ID was not found.
  */
  static const_iterator find(const container* pContainer, const item& id)
  {
    return std::find(pContainer->begin(), pContainer->end(), id);
  }
  
  /** \details
    Returns whether an item is erased.
    \returns Boolean flag is true if the item is erased, otherwise false.
  */
  static bool itemIsErased(const const_iterator& iter)
  {
    return (*iter).isErased();
  }
};
//DOM-IGNORE-END

#define ITER_IS_DONE() TContainerType::isDone(m_pContainer, m_iter)
#define ITER_FIND(id) TContainerType::find(m_pContainer, id)

//DOM-IGNORE-BEGIN
class NwBaseIteratorDummyInterface
{};
//DOM-IGNORE-END

/** \details
  This class represents the implementation of an iterator's base methods.

  <group OdNw_Classes>
*/
template < class TItem,
           class TContainerType,
           class TInterface = NwBaseIteratorDummyInterface >
class NwBaseIterator : public TInterface
{
public:
  /** \details
    Moves the iterator to the start position.
  */
  void start(bool bForward = true, bool bSkipDeleted = true)
  {
    ODA_ASSERT(m_pContainer);
    if (bForward)
    {
      m_iter = m_pContainer->begin();
    }
    else
    {
      m_iter = m_pContainer->end();
      if (m_pContainer->size())
      {
        --m_iter;
      }
    }
    if (bSkipDeleted)
    {
      skipDeleted(bForward);
    }
  }
  
  /** \details
    Returns whether the iterator has reached the end.
    \returns Boolean flag is true if the iterator has reached the end, otherwise false.
  */
  bool done() const
  {
    return ITER_IS_DONE();
  }
  
  /** \details
    Finds an item.
    \returns True if the item is found.
  */
  bool seek(const TItem& id)
  {
    m_iter = ITER_FIND(id);
    return !ITER_IS_DONE();
  }
  /** \details
    Moves the iterator to the next position.
  */
  void step(bool bForward = true, bool bSkipDeleted = true)
  {
    if (!ITER_IS_DONE())
    {
      if (bForward)
        ++m_iter;
      else
        --m_iter;

      if (bSkipDeleted)
      {
        skipDeleted(bForward);
      }
    }
  }
  /** \details
    Returns the item value from the current iterator.
  */
  TItem item() const
  {
    return ITER_IS_DONE() ? TItem(0) : *m_iter;
  }

protected:
  // Constructors
  NwBaseIterator()
    : m_pContainer((OD_TYPENAME TContainerType::container*)0)
  {}

  NwBaseIterator(const typename TContainerType::container* pContainer)
    : m_pContainer(pContainer)
  {}

  // Support method
  virtual void skipDeleted(bool bForward)
  {
    if (bForward)
    {
      while (!ITER_IS_DONE() && TContainerType::itemIsErased(m_iter))
      {
        ++m_iter;
      }
    }
    else
    {
      while (!ITER_IS_DONE() && TContainerType::itemIsErased(m_iter))
      {
        --m_iter;
      }
    }
  }

  const OD_TYPENAME TContainerType::container* m_pContainer;
  OD_TYPENAME TContainerType::const_iterator m_iter;
};

/** \details
  This class represents the internal inline pared-down interface to an IDs container.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwObjectContainer : public NwIdContainer
{
public:
  //DOM-IRNORE-BEGIN
  class iterator : public NwBaseIterator<OdNwObjectId, NwIdContainerType>
  {
  public:
    /** \details
      Constructor. Creates a new iterator object for the given OdNwObjectContainer object.

      \param pContainer A pointer to the OdNwObjectContainer object to create iterator for.
    */
    iterator(const OdNwObjectContainer* pContainer)
      : NwBaseIterator<OdNwObjectId, NwIdContainerType>(pContainer)
    {}
  };
  //DOM-IGNORE-END
  /** \details
    Default constructor.
  */
  OdNwObjectContainer()
  {}
  /** \details
   Adds an object ID to the end of the container.
   \param id Constant reference to the object ID.
 */
  void append(const OdNwObjectId& id)
  {
    push_back(id);
  }
  /** \details
   Removes the object ID from the container.
   \param id Constant reference to the object ID.
 */
  void remove(const OdNwObjectId& id)
  {
    NwIdContainer::remove(id);
  }
  /** \details
   Size of the container.
   \returns Quantity of items in the container.
 */
  OdUInt32 size() const
  {
    return NwIdContainer::size();
  }
  /** \details
   Returns the item by its position.
   \param i Position of the object ID in the container.
   \returns Object ID by the position.
 */
  OdNwObjectId at(OdUInt32 i) const
  {
    return NwIdContainer::at(i);
  }
  /** \details
    Clears the container.
  */
  void clear()
  {
    NwIdContainer::clear();
  }
  /** \details
    Returns an Iterator object that can be used to traverse through objects in the 
    container.
      
    \param atBeginning [in] true - to start at the beginning, or false - to start at the end.
    \param skipDeleted [in] true - to iterate only unerased records, or false - to iterate through 
    unerased and erased records.   
  */
  OdNwObjectIteratorPtr createIterator(bool atBeginning = true, bool skipDeleted = true) const;
};

#endif //__NW_OBJECTCONTAINER_H__
