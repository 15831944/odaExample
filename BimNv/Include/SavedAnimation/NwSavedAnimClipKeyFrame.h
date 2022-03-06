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

#ifndef __NW_SAVEDANIMCLIPKEYFRAME_H__
#define __NW_SAVEDANIMCLIPKEYFRAME_H__

#include "NwObject.h"
#include "NwSavedItem.h"

/**
 This class represents animation section plane key frame.
 
 <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSavedAnimClipKeyFrame : public OdNwSavedItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSavedAnimClipKeyFrame);
  //DOM-IGNORE-END
public:
  /** \details
    Default constructor.
  */
  OdNwSavedAnimClipKeyFrame();

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSavedAnimClipKeyFrame();
  
  /** \details
    Returns current position in the playback.
    
    \returns The value of the playback position.
  */
  double getTime() const;
  
  /** \details
   Determines whether values are automatically interpolated between the current and the last keyframes.

   \returns True if values are automatically interpolated between the current and the last keyframes, or false otherwise.
  */
  bool isInterpolation() const;
  
  /** \details
    Returns an object ID of the clipping planes.

    \returns Object ID of the OdNwClipPlaneSet object with the clipping planes.
  */
  OdNwObjectId getClipPlaneSetId() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwSavedAnimClipKeyFrame object pointers.
*/
typedef OdSmartPtr<OdNwSavedAnimClipKeyFrame> OdNwSavedAnimClipKeyFramePtr;

#endif /* __NW_SAVEDANIMCLIPKEYFRAME_H__ */
