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

#ifndef __TNW_SAVEDVIEWPOINTANIMATION_H__
#define __TNW_SAVEDVIEWPOINTANIMATION_H__

#include "NwSavedGroupItem.h"
#include "NwAnimationSmoothing.h"

/** \details
  This class represents saved viewpoint animations.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSavedViewpointAnimation : public OdNwSavedGroupItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSavedViewpointAnimation);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor.
  */
  OdNwSavedViewpointAnimation();

public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSavedViewpointAnimation();
public:
  /** \details
    Gets the loop playback value.

    \returns Returns an OdInt32 value for the loop playback.
  */
  OdInt32 getLoopPlayback() const;
  /** \details
    Gets the smoothing type.

    \returns Returns a value specified by the NwAnimationSmoothing::Enum enumeration.

    \remarks
    Smoothing type can be one of the following:

    <table>
    Name                                                      Value     Description
    NwAnimationSmoothing::NONE                                0x00      No smoothing
    NwAnimationSmoothing::SYNCHRONIZE_ANGULAR_LINEAR_SPEEDS   0x01      Synchronize angular linear speed
    </table>
  */
  NwAnimationSmoothing::Enum getSmoothing() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwSavedViewpointAnimation object pointers.
*/
typedef OdSmartPtr<OdNwSavedViewpointAnimation> OdNwSavedViewpointAnimationPtr;

#endif //__TNW_SAVEDVIEWPOINTANIMATION_H__
