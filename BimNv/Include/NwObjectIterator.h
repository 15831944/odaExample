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


#ifndef _NWOBJECTITERATOR_H_
#define _NWOBJECTITERATOR_H_

#include "NwObject.h"

/** \details
  This class represents an iterator of an OdNwObject object.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwObjectIterator : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdNwObjectIterator);

  /** \details
    Default constructor.
  */
  OdNwObjectIterator() {}

  /** Description:
    Sets this iterator object to reference the *entity* that it would normally return first.
     
    Remarks:
    Allows multiple traversals of the iterator list.

    Arguments:
    atBeginning (I) True to start at the beginning, false to start at the end. 
    skipErased (I) If and only if true, *erased* records are skipped.
  */  
  virtual void start(
    bool atBeginning = true, 
    bool skipErased = true) = 0;

  /** Description:
    Returns true if and only if the traversal by this iterator object is complete.
  */  
  virtual bool done() const = 0;

  /** Description:
    Returns the object ID of the *entity* currently referenced by this iterator object.
  */
  virtual OdNwObjectId item() const = 0;

  /** Description:
    Opens and returns the *entity* currently referenced by this iterator object.

    Arguments:
    openMode (I) Mode in which to open the *entity*.
    openErasedEntity (I) If and only if true, *erased* records are opened or retrieved.

    Remarks:
    Returns a smartb pointer to the opened *entity* if successful, otherwise returns a null smart pointer.
  */
  //virtual OdDbElementPtr element(
  //OdDb::OpenMode openMode = OdDb::kForRead, 
  //bool openErasedEntity = false) = 0;

  /** Description:
    Steps this iterator object.

    Arguments:
    forward (I) True to step *forward*, false to step backward.
    skipErased (I) If and only if true, *erased* records are skipped.
  */
  virtual void step(
    bool forward = true, 
    bool skipErased = true) = 0;

  /** Description:
    Positions this iterator object at the specified record.
    Arguments:
    objectId (I) Object ID of the *entity*.
    pEntity(I) Pointer to the *entity*.
  */  
  virtual bool seek(const OdNwObjectId& objectId) = 0;
};

/** Description:
  This template class is a specialization of the OdSmartPtr class for OdDbObjectIterator object pointers.
*/
typedef OdSmartPtr<OdNwObjectIterator> OdNwObjectIteratorPtr;

#endif //_NWOBJECTITERATOR_H_



