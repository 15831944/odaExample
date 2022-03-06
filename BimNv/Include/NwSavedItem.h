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

#ifndef __TNW_SAVEDITEM_H__
#define __TNW_SAVEDITEM_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"

class OdNwComment;

/** \details
  This class is a base class for all saved items.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSavedItem : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSavedItem);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwSavedItem object.
  */
  OdNwSavedItem();

  /** \details
    Constructor for objects of the OdNwSavedItem class. Creates a new
    OdNwSavedItem object for the specified item.

    \param pImpl [in] Item to create a OdNwSavedItem object for.
  */
  explicit OdNwSavedItem(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSavedItem();

public:

  /** \details
    Gets comments about the saved item.

    \returns Comments about the item as an OdArray<OdNwComment>.
  */
  OdArray<OdNwComment> getCommentCollection() const;

  /** \details
    Gets the saved item name as displayed in the GUI.

    \returns Display name of the item as an OdString value.
  */
  OdString getDisplayName() const;

  /** \details
    Gets the globally unique ID for the saved item.

    \returns OdGUID value.
  */
  OdGUID getGuID() const;

  /** \details
    Checks whether this item is a group item.

    \returns True if the item is a group item, or false otherwise.
  */
  bool isGroup() const;

  /** \details
    Gets the parent of this item.

    \returns Object ID of the saved item that is the parent of this item, or
    empty object ID if the item has no parent.
  */
  OdNwObjectId getParentId() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwSavedItem object pointers.
*/
typedef OdSmartPtr<OdNwSavedItem> OdNwSavedItemPtr;

#endif //__TNW_SAVEDITEM_H__
