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

#ifndef __NW_SELECTION_SET_H__
#define __NW_SELECTION_SET_H__

#include "NwSavedItem.h"
#include "NwSelectionSetsTypes.h"

class OdNwFindSpec;
class OdNwFindSelection;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwFindSpec object pointers.
*/
typedef OdSmartPtr<OdNwFindSpec> OdNwFindSpecPtr;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwFindSelection object pointers.
*/
typedef OdSmartPtr<OdNwFindSelection> OdNwFindSelectionPtr;

/** \details
  Class represents selection sets  element
 
  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSelectionSetItem : public OdNwSavedItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSelectionSetItem);
  //DOM-IGNORE-END

public:
  /** \details
      Default constructor.
  */
  OdNwSelectionSetItem();
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSelectionSetItem();

  /** \details
    Returns the list of Model Item object.

    \returns List of OdNwObjectId Model Item object.
  */
  OdNwObjectIdArray getModelItems() const;
  
  /** \details
    Returns the find selection object.

    \returns Pointer to the find selection object.
  */
  OdNwFindSelectionPtr getFindSelection() const;
  
  /** \details
    Returns the type of selection set item.

    \returns Value, specified by the NwSelectionSetItemType::Enum enumeration.

    \remarks
     Selection set item type can be one of the following:

     <table>
     Name                                                                        Value  Description
     NwSelectionSetItemType::Enum::PATHLINK               0     Path link
     NwSelectionSetItemType::Enum::FINDCONDITION    1     Find condition
     NwSelectionSetItemType::Enum::NONE                      2     None
     NwSelectionSetItemType::Enum::ZONESPEC             3    Zone spec
     </table>
  */
  NwSelectionSetItemType::Enum getItemType() const;
  
  /** \details
    Returns pointer to class that contains find condition results.

    \returns OdNwFindSpecPtr as pointer to OdNwFindSpec.
  */
  OdNwFindSpecPtr getFindSpec() const;
  
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwSelectionSetItem object pointers.
*/
typedef OdSmartPtr<OdNwSelectionSetItem> OdNwSelectionSetItemPtr;

#endif
