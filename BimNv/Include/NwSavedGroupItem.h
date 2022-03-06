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

#ifndef __TNW_SAVEDGROUP_H__
#define __TNW_SAVEDGROUP_H__

#include "NwSavedItem.h"

/** \details
  This class is a base class for arrays of saved items.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSavedGroupItem : public OdNwSavedItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSavedGroupItem);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwSavedGroupItem object.
  */
  OdNwSavedGroupItem();
  
  /** \details
    Constructor for objects of the OdNwSavedGroupItem class. Creates a new
    OdNwSavedGroupItem object for the specified item.

    \param pImpl [in] Item to create an OdNwSavedGroupItem object for.
  */
  explicit OdNwSavedGroupItem(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSavedGroupItem();

public:

  /** \details
    Gets the child saved items of the group.

    \param objIds [out] OdArray of object IDs of the saved items.

    \returns eOk if the array of child saved items is retrieved successfully, or
    an appropriate error code otherwise.
  */
  OdResult getChildren(OdNwObjectIdArray& objIds) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwSavedGroupItem object pointers.
*/
typedef OdSmartPtr<OdNwSavedGroupItem> OdNwSavedGroupItemPtr;

#endif //__TNW_SAVEDVIEWPOINT_H__
