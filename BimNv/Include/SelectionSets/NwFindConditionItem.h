
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

#ifndef __NW_FIND_CONDITION_ITEM_H__
#define __NW_FIND_CONDITION_ITEM_H__
#include "NwObject.h"
#include "NwSelectionSetsTypes.h"

class OdNwName;
class OdNwVariant;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwName object pointers.
*/
typedef OdSmartPtr<OdNwName> OdNwNamePtr;

/** \details
 This class represents find condition items.
 
 <group OdNw_Classes>
*/
class NWDBEXPORT OdNwFindConditionItem : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwFindConditionItem);
  //DOM-IGNORE-END
public:
  /** \details
    Default constructor.
  */
  OdNwFindConditionItem();

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwFindConditionItem();

  /** \details
    Returns the category column.

    \returns Smart pointer to the OdNwName object.
  */
  OdNwNamePtr getCategory() const;
  
  /** \details
    Returns the property column.

    \returns Smart pointer to the OdNwName object.
  */
  OdNwNamePtr getProperty() const;
  
  /** \details
    Returns the sign of the marked condition item flag.
    
    \returns True if the specified flag is set.
    
    \remarks
    Flag type can be one of the following:
    <table>
     Name                                                              Value   Description
     NwSelectionFindConditionFlags::NONE                                 0     No additional options.
     NwSelectionFindConditionFlags::IGNORE_CATEGORY_USER_NAME            1     Ignore DisplayName when matching category.
     NwSelectionFindConditionFlags::IGNORE_CATEGORY_INTERNAL_NAME        2     Ignore internal name when matching category.
     NwSelectionFindConditionFlags::IGNORE_PROPERTY_USER_NAME            4     Ignore DisplayName when matching property.
     NwSelectionFindConditionFlags::IGNORE_PROPERTY_INTERNAL_NAME        8     Ignore internal name when matching property.
     NwSelectionFindConditionFlags::IGNORE_STRING_VALUE_CASE             16    Ignore DisplayName when matching category or property.
     NwSelectionFindConditionFlags::NEGATE_CONDITIONS                    32    Negate the sense of the condition.
     NwSelectionFindConditionFlags::IGNORE_STRING_VALUE_DIACRITICS       128   Ignore diacritic signs when matching DisplayString values.
     NwSelectionFindConditionFlags::IGNORE_STRING_VALUE_CHARACTER_WIDTH  256   Ignore character width when matching DisplayString values.
    </table>
  */
  bool isFlagSet(NwSelectionFindConditionFlags::Enum flag);
  
  /** \details
    Returns the condition type.
    
   \returns Value specified by the NwSelectionFindConditionType::Enum enumeration.

    \remarks
    Condition type can be one of the following:

    <table>
    Name           Value   Description
    NEVER           0      Never used.
    ATTRIB          1      With attributes.
    NO_ATTRIB       2      No attributes.
    PROP            3      Defined; to match the search criteria, a property must have a value defined.
    NO_PROP         4      Undefined; to match the search criteria, a property must not have a defined value.
    SAME_TYPE       5      The same type
    EQUALS          6      Equals; a property must match the value exactly.
    NOT_EQUALS      7      Not equal; use with any type of property.
    LESS_THAN       8      Less than; use with numerical property types only.
    LESS_EQUAL      9      Less than or equal; use with numerical property types only.
    GREATER_EQUAL   10     Greater than or equal; use with numerical property types only.
    GREATER_THAN    11     Greater than; use with numerical property types only.
    CONTAINS        12     A property must contain the specified value.
    WILDCARD        13     Using wildcards allows matching any one character (?) or an arbitrary sequence of characters (*).
    WITHIN_DAY      14     To match the search criteria, a property must be within the specified day.
    WITHIN_WEEK     15     To match the search criteria, a property must be within the specified week.
    </table>
  */
  NwSelectionFindConditionType::Enum getCondition() const;
  
  /** \details
    Returns the value to compare.
    
    \returns Value of the column as a variant type.
  */
  OdNwVariant getValue() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwFindConditionItem object pointers.
*/
typedef OdSmartPtr<OdNwFindConditionItem> OdNwFindConditionItemPtr;

/** \details
  This template class is a specialization of the OdArray class for OdNwFindConditionItemPtr object pointers.
*/
typedef OdArray<OdNwFindConditionItemPtr> OdNwFindConditionList;

#endif
