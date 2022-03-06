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

#ifndef __TNW_CATEGORY_H__
#define __TNW_CATEGORY_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#define STL_USING_MAP
#include "OdaSTL.h"

class OdNwProperty;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwProperty object pointers.
*/
typedef OdSmartPtr<OdNwProperty> OdNwPropertyPtr;

/** \details
  This class represents a category of properties.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwCategory : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwCategory);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwCategory
    class.
  */
  OdNwCategory();

  /** \details
    Constructor for objects of the OdNwCategory class. Creates a new
    OdNwCategory object for the specified item.

    \param pImpl [in] Item to create an OdNwModelItem object for.
  */
  explicit OdNwCategory(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwCategory();

public:
  /** \details
    Checks whether the category has a stable ID.

    \returns True if the category has a stable ID, or false otherwise.
  */
  bool hasStableId() const;

  /** \details
    Returns the stable ID of the category as an OdUInt64 object.

    \returns OdUInt64 object with Int64StableId of the category.
  */
  OdUInt64 getInt64StableId() const;

  /** \details
    Returns the stable ID of the category as an OdString object.

    \returns OdString object with the StringStableId of the category.
  */
  OdString getStringStableId() const;

  /** \details
    Returns the display name of the category.

    \returns Display name of the category as a string.

    \remarks Display name is a localized name.
  */
  OdString getDisplayName() const;

  /** \details
    Returns the name of the category.

    \returns Name of the category as a string.
  */
  OdString getName() const;

  /** \details
    Gets the properties of the category as std::map.
    
    \param mProperties [out] std::map with smart pointers to properties as values and string descriptions as keys.

    \returns eOk if the operation is successful, or an appropriate error code otherwise.
  */
  OdResult getProperties(std::map<OdString, OdNwPropertyPtr>& mProperties) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwCategory object pointers.
*/
typedef OdSmartPtr<OdNwCategory> OdNwCategoryPtr;

#endif //__TNW_CATEGORY_H__
