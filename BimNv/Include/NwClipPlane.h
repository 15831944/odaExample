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

#ifndef __NWCLIPPLANE_H__
#define __NWCLIPPLANE_H__

#include "NwExport.h"
#include "NwObject.h"
#include "NwClipPlaneAlignment.h"
#include "NwClipPlaneState.h"

class OdNwClipPlaneImpl;
class OdGePlane;

/** \details
  This class represents a clipping plane object of a view.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwClipPlane
{
public:
  /** \details
    Default constructor. Creates a new object of the OdNwClipPlane class.
  */
  OdNwClipPlane();

  /** \details
    Copy constructor. Creates a copy of a given OdNwClipPlane object.

    \param OdNwClipPlane [in] Clipping plane object to be copied.
  */
  OdNwClipPlane(const OdNwClipPlane&);

  /** \details
    Copy assignment operator.

    \param OdNwClipPlane [in] Clipping plane object to be copied.
  */
  OdNwClipPlane& operator=(const OdNwClipPlane&);

  /** \details
    Destructor. Frees allocated resources.
  */
  ~OdNwClipPlane();

public:
  /** \details
    Returns the object ID of the clipping plane.

    \return OdNwObjectId object with the database ID of the clipping plane.
  */
  virtual OdNwObjectId objectId() const;

  /** \details
    Returns the object ID of the clipping plane's owner.

    \returns Pointer to OdDbStub with the database ID of the clipping plane's
    owner.
  */
  virtual OdDbStub* ownerId() const;

  /** \details
    Returns the database ID of the clipping plane.

    \returns Pointer to OdDbStub with the database ID of the clipping plane.

    \remarks
    Returns a null pointer if the clipping plane is not persistent.
  */
  OdDbStub* id() const;

  /** \details
    Returns the alignment type of this clipping plane.

    \returns Alignment type as an NwClipPlaneAlignment::Enum value.

    \remarks
    The type must be one of the following:

    <table>
    Name                               Value   Description
    NwClipPlaneAlignment::AL_NONE      0x00    Type is unset.
    NwClipPlaneAlignment::TO_VIEW      0x01    View clip plane.
    NwClipPlaneAlignment::BACK         0x02    Back clip plane.
    NwClipPlaneAlignment::FRONT        0x03    Front clip plane.
    NwClipPlaneAlignment::LEFT         0x04    Left clip plane.
    NwClipPlaneAlignment::RIGHT        0x05    Right clip plane.
    NwClipPlaneAlignment::TOP          0x06    Top clip plane.
    NwClipPlaneAlignment::BOTTOM       0x07    Bottom clip plane.
    NwClipPlaneAlignment::TO_SURFACE   0x08    Surface clip plane.
    NwClipPlaneAlignment::TO_LINE      0x09    Line clip plane.
    NwClipPlaneAlignment::CUSTOM       0x0A    Custom clip plane.
    </table>
  */
  NwClipPlaneAlignment::Enum getAlignment() const;

  /** \details
    Returns the state type of this clipping plane.

    \returns State type as an NwClipPlaneState::Enum value.

    \remarks
    The type must be one of the following:

    <table>
    Name                             Value     Description
    NwClipPlaneState::DEFAULT        0x00      Clipping plane is default.
    NwClipPlaneState::ENABLED        0x01      Clipping plane is enabled.
    </table>
  */
  NwClipPlaneState::Enum getState() const;

  /** \details
    Returns the plane object of the clipping plane.

    \returns OdGePlane object with the plane of the clipping plane.
  */
  OdGePlane getPlane() const;

private:
  //DOM-IGNORE-BEGIN
  friend class OdNwClipPlaneImpl;
  OdSmartPtr<OdNwClipPlaneImpl> m_pImpl;
  //DOM-IGNORE-END
};

#endif //__NWCLIPPLANE_H__
