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

#ifndef __NWCLIPPLANESET_H__
#define __NWCLIPPLANESET_H__

#include "NwExport.h"
#include "NwClipPlaneSetMode.h"
#include "NwClipPlane.h"

class OdGeMatrix3d;

/** \details
  This class represents a set of clipping plane objects of a view.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwClipPlaneSet : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwClipPlaneSet);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwClipPlaneSet class.
  */
  OdNwClipPlaneSet();

public:

  /** \details
    Destructor. Frees allocated resources.
  */
  virtual ~OdNwClipPlaneSet();

public:
  /** \details
    Returns the clipping planes type mode.

    \returns Clipping planes type mode as an NwClipPlaneSetMode::Enum value.

    \remarks
    The type must be one of the following:

    <table>
    Name                             Value     Description
    NwClipPlaneSetMode::CL_PLANES    0x00      Plane mode.
    NwClipPlaneSetMode::CL_BOX       0x01      Box mode.
    </table>
  */
  NwClipPlaneSetMode::Enum getMode() const;

  /** \details
    Returns the transformation matrix of the clipping planes.

    \returns Transformation matrix of the clipping planes as an OdGeMatrix3d
    object.

    \remarks
    The transformation matrix is required for the CL_BOX mode.
    Matrix values are expressed in model units.
  */
  OdGeMatrix3d getTransform() const;

  /** \details
    Gets the planes of the view for the current clipping plane mode.

    \param planes [out] OdArray of OdGePlane objects with planes of the view.

    \returns eOk if the planes are retrieved successfully, or an appropriate
    error code otherwise.

    \remarks
    The planes contain resulting geometry data for rendering. For the CL_PLANE
    mode the clipping plane with the default mode corresponds to default
    OdGePlane objects.
  */
  OdResult getPlanesForActiveMode(OdArray<OdGePlane>& planes);

  /** \details
    Gets the clipping plane of the view by index.

    \param clipPlane [out] OdNwClipPlane object with the selected clipping plane.
    \param idx        [in] Clipping plane index.

    \returns eOk if the clipping plane is retrieved successfully, or an
    appropriate error code otherwise.

    \remarks
     The planes are required for the CL_PLANE mode. For the CL_BOX mode clipping
     plane objects have the default mode.
  */
  OdResult getClipPlaneByIndex(OdNwClipPlane& clipPlane, OdUInt32 idx);

  /** \details
    Returns a boolean value of the linked status of clipping planes.

    \returns True if clipping planes are linked, or false if not.

    \remarks
    Linked clipping planes means that clipping planes move together.
  */
  bool isLinked() const;

  /** \details
    Returns an index of the current clipping plane.

    \returns Index of the current clipping plane.
  */
  OdUInt32 getCurrentPlaneIndex() const;

  /** \details
    Returns a boolean value of the enabled section status of the view.

    \return True if clipping planes are enabled, or false if not.
  */
  bool isEnabled() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwClipPlaneSet object pointers.
*/
typedef OdSmartPtr<OdNwClipPlaneSet> OdNwClipPlaneSetPtr;

#endif //__NWCLIPPLANESET_H__
