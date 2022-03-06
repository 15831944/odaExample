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

#ifndef _NW_SAVEDITEMSELEMENT_H_
#define _NW_SAVEDITEMSELEMENT_H_

#include "NwExport.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "OdArray.h"
#include "NwObject.h"
#include "SmartPtr.h"

class OdNwSavedItem;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwSavedItem object pointers.
*/
typedef OdSmartPtr<OdNwSavedItem> OdNwSavedItemPtr;

/** \details
  This class represents geometry.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSavedItemsElement : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSavedItemsElement);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwSavedItemsElement object.
  */
  OdNwSavedItemsElement();
  
  /** \details
    Constructor for objects of the OdNwSavedItemsElement class. Creates a new
    OdNwSavedItemsElement object for the specified item.

    \param pImpl [in] Item to create an OdNwSavedItemsElement object for.
  */
  explicit OdNwSavedItemsElement(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSavedItemsElement();

public:
  /** \details
    Returns a constant reference to an array of OdNwSavedItemPtr objects.

    \returns Constant reference to an array of OdNwSavedItemPtr objects.

    \remarks
    The method is deprecated. Use OdResult getSavedItems(OdNwObjectIdArray& aSavedItems) const instead.
  */
  const OdArray<OdNwSavedItemPtr>& getSavedItems() const;

  /** \details
    Returns an array of object IDs of OdNwSavedItemPtr objects.

    \param aSavedItems [out] OdArray with object IDs of OdNwSavedItemPtr objects.

    \returns eOk if successful, or an appropriate error code if not.
  */
  OdResult getSavedItems(OdNwObjectIdArray& aSavedItems) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwSavedItemsElement object pointers.
*/
typedef OdSmartPtr<OdNwSavedItemsElement> OdNwSavedItemsElementPtr;

#endif // _NW_SAVEDITEMSELEMENT_H_
