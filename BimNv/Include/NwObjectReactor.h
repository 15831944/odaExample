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


#ifndef __NW_OBJECTREACTOR_H__
#define __NW_OBJECTREACTOR_H__

#include "RxObject.h"
#include "NwExport.h"

class OdNwObject;

/** \details
  This class is the base class for custom classes that receive notifications of OdNwDatabase events.

  \remarks Events consist of the addition, modification, or deletion of objects from an OdNwDatabase instance.

  \remarks The default implementations of all methods in this class do nothing.

  Corresponding C++ library: TG_Db

  <group OdNw_Classes>
>
*/
class NWDBEXPORT OdNwObjectReactor : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdNwObjectReactor);

  /** \details
    Notification function called whenever the notifying element has had its clone() member function called. 
    
    \param pElement [in]  Pointer to the notifying element.
    \param pNewElement [in]  Pointer to the element resulting from the copy.

    \remarks
    The default implementation of this function does nothing. This function can be
    overridden in custom classes.
  */
  virtual void copied(const OdNwObject* pElement,
                      const OdNwObject* pNewElement) {}

  /** \details
    Notification function called whenever an element has been erased or unerased.

    \param pElement [in]  Pointer to the element that was erased/unerased.
    \param erasing [in]  True if and only if this element is being erased.
    
    \remarks
    The default implementation of this function does nothing. This function can be
    overridden in custom classes.
  */
  virtual void erased(const OdNwObject* pElement, bool erasing = true) {}

  /** \details
    Notification function called whenever an object is about to be deleted from memory.
    \param pElement [in]  Pointer to the object being deleted.

    \remarks
    This function is called before the operation.
  */
  virtual void goodbye(const OdNwObject* pElement) {}

  /** \details
    Notification function called whenever an element is opened for modifying OdDg::kForWrite.

    \param pElement [in]  Pointer to the element that is being opened.

    \remarks
    The default implementation of this function does nothing. This function can be
    overridden in custom classes.
  */
  virtual void openedForModify(const OdNwObject* pElement) {}

  /** \details
    Notification function called whenever an element is opened for writing, a function
    has been called that could modify the contents of this element, and this element is now being
    closed.

    \param pElement [in]  Pointer to the element that is being closed after being modified.

    \remarks The default implementation of this function does nothing. This function can be
    overridden in custom classes.
  */
  virtual void modified(const OdNwObject* pElement) {}

  /** \details
    Notification function called whenever an element is modified.
    
    \param pElement [in]  Pointer to the modified element.
    
    \remarks
    The default implementation of this function does nothing. This function can be
    overridden in custom classes.
  */
  virtual void modifiedGraphics(const OdNwObject* pElement) {}

  /** \details
    Notification function called whenever the attribute linkages have been written
    to the notifying element.
    
    \param pElement [in]  Pointer to the notifying element.
    
    \remarks
    Notification is made upon pElement->close().
    
    The default implementation of this function does nothing. This function can be
    overridden in custom classes.
  */
  virtual void modifiedLinkages(const OdNwObject* pElement) {}

  /** \details
    Notification function called whenever a method of the
    specified sub-element has called assertWriteEnabled().
    
    \param pElement [in]  Pointer to the notifying element.
    \param pSubElm [in]  A pointer to the subelement owned by pElement.
    
    \remarks
    Notification is made upon pElement->close().
  */
  virtual void subElementModified(const OdNwObject* pElement,
                                  const OdNwObject* pSubElm) {}

  /** \details
    Notification function called whenever the notifying
    element is in the midst of an Undo operation that
    is undoing modifications.
    
    \param pElement [in]  Pointer to the notifying element.
    
    The default implementation of this function does nothing. This function can be
    overridden in custom classes.
  */
  virtual void modifyUndone(const OdNwObject* pElement) {}

  /** \details
    Notification function called whenever the undo process
    processes the appending of the notifying element to the database.
    
    \param pElement [in]  Pointer to the notifying element.
    
    \remarks
    The notifying element is marked as erased. It is not removed from the database, and can be unerased,
    even 'before' it was created. 
    
    The default implementation of this function does nothing. This function can be
    overridden in custom classes.
  */
  virtual void unappended(const OdNwObject* pElement) {}

  /** \details
    Notification function called whenever a redo process
    processes the reappending of the notifying element to the database.
    
    \param pElement [in]  Pointer to the notifying element.
    
    \remarks
    
    The default implementation of this function does nothing. This function can be
    overridden in custom classes.
  */
  virtual void reappended(const OdNwObject* pElement) {}

  /** \details
    Notification function called immediately before an element is closed.

    \param elementId [in]  OdDbStub with an ID of the element that is being closed.

    \remarks
    The default implementation of this function does nothing. This function can be
    overridden in custom classes.
  */
  virtual void closed(class OdDbStub* elementId) {}
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwObjectReactor object pointers.
*/
typedef OdSmartPtr<OdNwObjectReactor> OdNwObjectReactorPtr;

typedef OdNwObjectReactor OdNwDatabaseReactor;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwDatabaseReactor object pointers.
*/
typedef OdSmartPtr<OdNwDatabaseReactor> OdNwDatabaseReactorPtr;

#endif // __NW_OBJECTREACTOR_H__


