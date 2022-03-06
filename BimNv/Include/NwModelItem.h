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

#ifndef __TNW_MODELITEM_H__
#define __TNW_MODELITEM_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#define STL_USING_MAP
#include "OdaSTL.h"
#include "NwModelItemIcon.h"

class OdGePoint3d;
class OdGeExtent3d;
class OdNwCategory;
class OdNwFullSubentPath;
class OdNwAttribute;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwCategory object pointers.
*/
typedef OdSmartPtr<OdNwCategory> OdNwCategoryPtr;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwAttribute object pointers.
*/
typedef OdSmartPtr<OdNwAttribute> OdNwAttributePtr;

/** \details
  This class represents an instance node within the model hierarchy.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwModelItem : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwModelItem);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwModelItem
    class.
  */
  OdNwModelItem();

  /** \details
    Constructor for objects of the OdNwModelItem class. Creates a new
    OdNwModelItem object for the specified item.

    \param pImpl [in] Item to create an OdNwModelItem object for.
  */
  explicit OdNwModelItem(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwModelItem();

public:

  /** \details
    Calculates and returns the bounding box of an item and its children.

    \returns OdGeExtents3d object with the bounding box of this model item.
  */
  OdGeExtents3d getBoundingBox() const;

  /** \details
    Returns all ancestors within the model hierarchy of this item.

    \param aAncestors [out] OdArray with object IDs of ancestors of the model item.

    \returns eOk if successful, or an appropriate error code if not.
  */
  OdResult getAncestors(OdNwObjectIdArray& aAncestors) const;

  /** \details
    Returns all ancestors within the model hierarchy of this item and the item
    itself.

    \param aAncestors [out] OdArray with the object IDs of ancestors of the model item and the item itself.

    \returns eOk if successful, or an appropriate error code if not.
  */
  OdResult getAncestorsAndSelf(OdNwObjectIdArray& aAncestors) const;

  /** \details
    Returns the children within the model hierarchy of this item.

    \param aChildren [out] OdArray with the object IDs of the children of this item.

    \returns eOk if successful, or an appropriate error code if not.
  */
  OdResult getChildren(OdNwObjectIdArray& aChildren) const;

  /** \details
    Returns the display name for the type of the item.

    \returns Display name for the type of the item.

    \remarks
    Display name is derived from the type in the original design application.
  */
  OdString getClassDisplayName() const;

  /** \details
    Returns the name of the type of the item.

    \returns Name of the type of the item.

    \remarks
    Name is derived from the type in the original design application.
  */
  OdString getClassName() const;

  /** \details
    Returns all descendants within the model hierarchy of this item.

    \param aDescendants [out] OdArray with the object IDs to descendants of this model item.

    \returns eOk if successful, or an appropriate error code if not.
  */
  OdResult getDescendants(OdNwObjectIdArray& aDescendants) const;

  /** \details
    Returns all descendants within the model hierarchy of this item and the item
    itself.

    \param aDescendants [out] OdArray with the object IDs of descendants of this model item and the item itself.

    \returns eOk if successful, or an appropriate error code if not.
  */
  OdResult getDescendantsAndSelf(OdNwObjectIdArray& aDescendants) const;

  /** \details
    Returns the end-user supplied name for the item.

    \returns End-user supplied name for the item.

    \remarks
    DisplayName can be empty.
  */
  OdString getDisplayName() const;

  /** \details
    Indicates whether there is geometry in the model item.

    \returns True if the model item has geometry, or false otherwise.
  */
  bool hasGeometry() const;

  /** \details
    Returns the object ID of the geometry component for this item.

    \returns Object ID of the OdNwComponent object with the geometry component
    for this item. If the item does not have geometry, the returned object ID is
    empty.
  */
  OdNwObjectId getGeometryComponentId() const;

  /** \details
    Returns the GUID for the instance data referred to by this item.

    \returns OdGUID object with the GUID for the instance data referred to by
    this item.
  */
  OdGUID getInstanceGuid() const;

  /** \details
    Returns the object ID of the parent model item within the model hierarchy.

    \returns Object ID of the OdNwModelItem object with the parent model item.
    If the item is the root of the hierarchy, the returned object ID is empty.
  */
  OdNwObjectId getParentId() const;

  /** \details
    Returns the properties of this item divided into multiple categories as
    std::map.

    \param mCategories [out] std::map with smart pointers to categories as values and string descriptions as keys.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    The method is deprecated. Use getAttributes(OdArray<OdNwAttributePtr>& aAttributes, OdUInt32 categoryTypes) const
    instead.
  */
  OdResult getPropertyCategories(std::map<OdString, OdNwCategoryPtr>& mCategories) const;

  /** \details
    Returns the properties of this item divided into multiple categories as
    std::map for selected types of categories.

    \param mCategories  [out] std::map with smart pointers to categories as values and string descriptions as keys.
    \param categoryTypes [in] OdUInt32 value with bitfields such as the attribute's type for selective conversion to a category.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    Bitfield values with the attribute's type for selective conversion to a category
    can be returned from the NwCategoryConversionType::Enum enumeration.
    If categoryTypes is NULL, all attributes are converted.

    The method is deprecated. Use getAttributes(OdArray<OdNwAttributePtr>& aAttributes, OdUInt32 categoryTypes) const
    instead.
  */
  OdResult getSelectivePropertyCategories(std::map<OdString, OdNwCategoryPtr>& mCategories, OdUInt32 categoryTypes = 0) const;

  /** \details
    Returns the properties of this item divided into multiple categories as objects of classes which are derived from OdNwAttribute.

    \param aAttributes  [out] OdArray with smart pointers to attributes.
    \param categoryTypes [in] OdUInt32 value with bitfields such as an attribute's type for selective getting.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    Bitfield values with an attribute's type for selective getting
    can be returned from the NwCategoryConversionType::Enum enumeration.
    If categoryTypes is NULL, the method gets all attributes.
  */
  OdResult getAttributes(OdArray<OdNwAttributePtr>& aAttributes, OdUInt32 categoryTypes = 0) const;

  /** \details
    Returns the icon type of the model item.

    \remarks
    The returned type can be one of the following:

    <table>
    Name                                Value   Description
    NwModelItemIcon::NONE               0x0     Model item doesn't have a type
    NwModelItemIcon::FILE               0x1     Model item type is file
    NwModelItemIcon::LAYER              0x2     Model item type is layer
    NwModelItemIcon::COLLECTION         0x3     Model item type is collection
    NwModelItemIcon::GROUP              0x4     Model item type is group
    NwModelItemIcon::INSERT_GROUP       0x5     Model item type is insert group
    NwModelItemIcon::COMPOSITE_OBJECT   0x6     Model item type is composite object
    NwModelItemIcon::INSERT_GEOMETRY    0x7     Model item type is insert geometry
    NwModelItemIcon::GEOMETRY           0x8     Model item type is geometry
    </table>
  */
  NwModelItemIcon::Enum getIcon() const;

  /** \details
    Indicates whether the model item node is hidden.

    \returns True if the model item is hidden, or false if not.

    \remarks
      The method returns a value corresponding to the current viewpoint.
  */
  bool isHidden() const;
  
  /** \details
    Indicates whether the model item node is required.

    \returns The true value if the model item is required, or false if not.

    \remarks
      The method returns a value corresponding to the current viewpoint.
  */
  bool isRequired() const;

  /** \details
    Adds a new model item node to the model item.

    \param sClassName        [in] Class name of the source tree node.
    \param sClassDisplayName [in] Class user name of the source tree node.
    \param icon             [in] Type of the new child model item.
    \param sDisplayName      [in] Name of the source tree node.
    \param pResCode          [out] Pointer to the OdResult object with an error code if the operation is not successful, or eOk if successful.

    \returns Object ID of the new OdNwModelItem object.

    \remarks
    The icon can be one of the following:

    <table>
    Name                                Value   Description
    NwModelItemIcon::NONE               0x0     Model item doesn't have a type
    NwModelItemIcon::FILE               0x1     Model item type is file
    NwModelItemIcon::LAYER              0x2     Model item type is layer
    NwModelItemIcon::COLLECTION         0x3     Model item type is collection
    NwModelItemIcon::GROUP              0x4     Model item type is group
    NwModelItemIcon::INSERT_GROUP       0x5     Model item type is insert group
    NwModelItemIcon::COMPOSITE_OBJECT   0x6     Model item type is composite object
    NwModelItemIcon::INSERT_GEOMETRY    0x7     Model item type is insert geometry
    NwModelItemIcon::GEOMETRY           0x8     Model item type is geometry
    </table>

    Adding is succesfull only for types:
      NwModelItemIcon::FILE, if addition is in the root node only with FILE nodes as child.
      NwModelItemIcon::LAYER, if addition is in the FILE node without FILE nodes as child.
      NwModelItemIcon::GROUP, NwModelItemIcon::COMPOSITE_OBJECT, NwModelItemIcon::GEOMETRY, if addition is not in the insert node.
      in other cases this method returns an empty OdNwObjectId with eNotApplicable as the resulting code.
  */
  OdNwObjectId addModelItem(const OdString& sClassName, const OdString& sClassDisplayName, NwModelItemIcon::Enum icon, const OdString& sDisplayName = OD_T(""), OdResult* pResCode = NULL);

  /** \details
    Sets the node's hidden value.

    \param value [in] Hidden value for the node.
    \returns eOk if the far hidden status is set to the node, or an appropriate
    error code otherwise.

    \remarks
      The method sets a value corresponding to the current viewpoint.
  */
  OdResult setIsHidden(bool value);

  /** \details
    Highlights the specified entity in underlying model objects.

    \param bDoIt        [in]  Flag that indicates whether highlighting is enabled (true value) or disabled (false value).
    \param pSubId       [in]  Path to the entity for highlighting.
    \param highlightAll [in]  Flag to highlight all.
  */
  void highlight(const bool bDoIt = true, const OdNwFullSubentPath* pSubId = 0,
    const bool highlightAll = false) const;
  
  /** \details
    Highlights an element.

    \param bDoIt        [in]  Flag that indicates whether highlighting is enabled (true value) or disabled (false value).
    \param pSubId       [in]  Path to the entity for highlighting.
    \param highlightAll [in]  Flag to highlight all.
  */
  void subHighlight(const bool bDoIt, const OdNwFullSubentPath* pPath,
    const bool highlightAll = false) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwModelItem object pointers.
*/
typedef OdSmartPtr<OdNwModelItem> OdNwModelItemPtr;

#endif //__TNW_MODELITEM_H__
