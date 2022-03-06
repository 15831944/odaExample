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

#ifndef __TNW_SAVEDVIEWPOINT_H__
#define __TNW_SAVEDVIEWPOINT_H__

#include "NwSavedItem.h"

/** \details
  This class represents named viewpoints that are saved.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSavedViewpoint : public OdNwSavedItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSavedViewpoint);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor.
  */
  OdNwSavedViewpoint();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSavedViewpoint();

public:

  /** \details
    Gets the viewpoint associated with this object.

    \returns Object ID of the OdNwViewpoint object.
  */
  OdNwObjectId getViewpointId() const;

  /** \details
    Gets the clipping planes associated with this object.

    \returns Object ID of the OdNwClipPlaneSet object.
  */
  OdNwObjectId getClippingPlanesId() const;

  /** \details
    Gets the list with red lines.

    \param list [out] OdArray of object IDs of OdNwRedLine objects.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getRedLineList(OdNwObjectIdArray& objIds) const;

  /** \details
    Gets the array of model item's object IDs with the override hidden flag for
    this saved viewpoint.

    \param aHidenNodes [out] OdArray of object IDs of OdNwModelItem's objects with the override hidden flag.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getHiddens(OdNwObjectIdArray& aHidenNodes) const;

  /** \details
    Gets the array of model item's object IDs with the override required flag
    for this saved viewpoint.

    \param aReqNodes [out] OdArray of object IDs of OdNwModelItem's objects with the override required flag.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getRequireds(OdNwObjectIdArray& aReqNodes) const;

  /** \details
    Gets the count of apearance overrides for this saved viewpoint.

    \returns OdUInt32 value with the appearance overrides count.
  */
  OdUInt32 getAppearanceOverrideCount() const;

  /** \details
    Gets the array of model item's object IDs with an appearance override for
    this saved viewpoint by index.

    \param idx         [in] Index of the appearance override.
    \param modelItems [out] OdArray of object IDs of OdNwModelItem's objects with the appearance override.
    \param materialId [out] Object ID of the OdNwMaterial object with appearance override data.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getAppearanceOverride(OdUInt32 idx, OdNwObjectIdArray& modelItems, OdNwObjectId& materialId) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwSavedViewpoint object pointers.
*/
typedef OdSmartPtr<OdNwSavedViewpoint> OdNwSavedViewpointPtr;

#endif //__TNW_SAVEDVIEWPOINT_H__
