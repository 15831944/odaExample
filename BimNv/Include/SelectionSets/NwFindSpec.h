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

#ifndef __NW_FINDSPEC_H__
#define __NW_FINDSPEC_H__

#include "NwObject.h"
#include "NwSelectionSetsTypes.h"
class OdNwFindConditionItem;
class OdNwSelSetFindSelection;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwFindConditionItem object pointers.
*/
typedef OdSmartPtr<OdNwFindConditionItem> OdNwFindConditionItemPtr;


/** \details
  This template class is a specialization of the OdArray class for OdNwFindConditionItemPtr objects.
*/
typedef OdArray<OdNwFindConditionItemPtr> OdNwFindConditionList;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwSelSetFindSelection object pointers.
*/
typedef OdSmartPtr<OdNwSelSetFindSelection> OdNwSelSetFindSelectionPtr;

/** \details
 This class represents a list of find condition items.
 
 <group OdNw_Classes>
*/
class NWDBEXPORT OdNwFindSpec : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwFindSpec);
  //DOM-IGNORE-END
public:

  /** \details
    Default constructor.
  */
  OdNwFindSpec();

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwFindSpec();
  
  /** \details
    Gets a list of find conditions.

    \param findCondList [out] OdArray of OdNwFindConditionItemPtr objects.
    \return eOk if the operation is successful or an appropriate error code otherwise.
  */
  OdResult getFindConditionList(OdNwFindConditionList & findCondList);
 
  /** \details
    Returns the search mode.

    \return Value from the NwSelectionFindConditionMode::Enum enumeration that represents the search mode.
  */
  NwSelectionFindConditionMode::Enum getMode() const;
  
  /** \details
    Returns the flag for pruning below the result.
    
    \return True if the flag is set, false otherwise.
  */
  bool isPruneBelow() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwFindSpec object pointers.
*/
typedef OdSmartPtr<OdNwFindSpec> OdNwFindSpecPtr;

#endif /* __NW_FINDSPEC_H__ */
