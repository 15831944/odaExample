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

#ifndef __NW_SELECTION_SETS_TYPES_H__
#define __NW_SELECTION_SETS_TYPES_H__

/** \details
  Contains selection set item type.

  <group TNW_Namespaces>
*/
namespace NwSelectionSetItemType
{
  /** \details
    Defines the selection set item types.
  */
  enum Enum
  {
    /** Path link */
    PATHLINK = 0,
    /** Link condition */
    FINDCONDITION = 1,
    /** None */
    NONE = 2,
    /** Zone spec */
    ZONESPEC =3
  };
}

/** \details
  Contains the compare operation types.

  <group TNW_Namespaces>
*/
namespace NwSelectionFindConditionType
{
  /** \details
  Defines the compare operation types.
  */
  enum Enum
  {
    /** Never used */
    NEVER = 0,
    /** With attributes */
    ATTRIB,
    /** No attributes */
    NO_ATTRIB,
    /** Defined; to match the search criteria, a property must have a value defined. */
    PROP,
    /** Undefined; to match the search criteria, a property must not have a defined value. */
    NO_PROP,
    /** The same type */
    SAME_TYPE,
    /** Equals; a property must match the value exactly. */
    EQUALS,
    /** Not equal; use with any type of property. */
    NOT_EQUALS,
    /** Less than; use with numerical property types only. */
    LESS_THAN,
    /** Less than or equal; use with numerical property types only. */
    LESS_EQUAL,
    /** Greater than or equal; use with numerical property types only. */
    GREATER_EQUAL,
    /** Greater than; use with numerical property types only. */
    GREATER_THAN,
    /** A property must contain the specified value. */
    CONTAINS,
    /** Using wildcards allows matching any one character (?) or an arbitrary sequence of characters (*). */
    WILDCARD,
    /** To match the search criteria, a property must be within the specified day. */
    WITHIN_DAY,
    /** To match the search criteria, a property must be within the specified week. */
    WITHIN_WEEK
  };
}
/** \details
    Contains the type of searches.

    <group TNW_Namespaces>
 */
namespace NwSelectionFindConditionMode
{
  /** \details
    Defines the type of searches.
  */
  enum Enum
  {
    /**  Searches all items selected in the Find Selection Tree. */
    ALL = 0,
    /** Selected paths only. Only searches within the items selected in the Find Selection Tree for qualifying items. */
    SELETED,
    /** Only searches below the items selected in the Find Selection Tree. */
    BELOW
  };
}

/** \details
   Contains condition options.

   <group TNW_Namespaces>
*/
namespace NwSelectionFindConditionFlags
{
  /** \details
   Defines condition options.
  */
  enum Enum
  {
    /** No additional options. */
    NONE = 0,
    /** Ignore DisplayName when matching a category. */
    IGNORE_CATEGORY_USER_NAME = 1,
    /** Ignore internal name when matching a category. */
    IGNORE_CATEGORY_INTERNAL_NAME = 2,
    /** Ignore DisplayName when matching a property. */
    IGNORE_PROPERTY_USER_NAME = 4,
    /** Ignore internal name when matching a property. */
    IGNORE_PROPERTY_INTERNAL_NAME = 8,
    /** Ignore DisplayName when matching a category or property. */
    IGNORE_STRING_VALUE_CASE = 16,
    /** Negate the sense of the condition. */
    NEGATE_CONDITIONS = 32,
    /** Ignore diacritic signs when matching DisplayString values. */
    IGNORE_STRING_VALUE_DIACRITICS = 128,
    /** Ignore character width when matching DisplayString values. */
    IGNORE_STRING_VALUE_CHARACTER_WIDTH = 256
  };
}

#endif 
