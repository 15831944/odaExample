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

#ifndef __TNW_GRIDSYSTEM_H__
#define __TNW_GRIDSYSTEM_H__

#include "NwObject.h"

class OdNwGridLine;
class OdNwGridLevel;
class OdGeMatrix3d;
class OdGePoint3d;
class OdGeVector3d;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGridLine object pointers.
*/
typedef OdSmartPtr<OdNwGridLine> OdNwGridLinePtr;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGridLevel object pointers.
*/
typedef OdSmartPtr<OdNwGridLevel> OdNwGridLevelPtr;

/** \details
  This class represents a system of grid lines and levels.
 
 <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGridSystem : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGridSystem);
  //DOM-IGNORE-END
public:
  /** \details
    Default constructor.
  */
  OdNwGridSystem();

public:
  
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGridSystem();
  
  /** \details
    Returns the origin of the geometry data.

    \returns OdGePoint3d object with the origin of the geometry data.
  */
  OdGePoint3d getOrigin() const;
  
  /** \details
    Returns the direction to the top orthogonal view of a model.

    \returns Instance of OdGeVector3d as the direction to the top orthogonal view of a model.
  */
  OdGeVector3d getUpVector() const;
  
  /** \details
    Returns the display name of the grid system element item.
   
    \returns Display name of the grid system.
  */
  OdString getName() const;
  
  /** \details
    Gets an array of the grid lines contained in the grid system element item.

    \param gridLineList [out] OdArray with OdNwGridLine smart pointers as values.
    \returns eOk if the sceneRefs are retrieved successfully, or an appropriate error code otherwise.
   */
  OdResult getGridLineList(OdArray<OdNwGridLinePtr> & gridLineList) const;
  
  /** \details
    Returns an array of the grid levels contained in the grid system element item.

    \param gridLevelList [out] OdArray with OdNwGridLevel smart pointers as values.
    \returns eOk if the sceneRefs are retrieved successfully, or an appropriate error code otherwise.
  */
  OdResult getGridLevelList(OdArray<OdNwGridLevelPtr> & gridLevelList) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwGridSystem object pointers.
*/
typedef OdSmartPtr<OdNwGridSystem> OdNwGridSystemPtr;

#endif /* NwGridSystem_h */
