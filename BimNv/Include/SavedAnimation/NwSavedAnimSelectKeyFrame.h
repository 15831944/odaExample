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

#ifndef __NW_SAVEDANIMSELECTKEYFRAME_H__
#define __NW_SAVEDANIMSELECTKEYFRAME_H__

#include "NwObject.h"
#include "NwSavedItem.h"
/**
 This class represents selected key frame.
 
 <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSavedAnimSelectKeyFrame : public OdNwSavedItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSavedAnimSelectKeyFrame);
  //DOM-IGNORE-END
public:
  /** \details
    Default constructor.
  */
  OdNwSavedAnimSelectKeyFrame();

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSavedAnimSelectKeyFrame();
  /**  \details
    Returns current position in the playback.
    
    \returns The value of the playback positions in double.
  */
  double getTime() const;
  
  /** \details
   Determines whether values are automatically interpolated between the current and the last keyframes.
  
   \returns True if values are automatically interpolated between the current and the last keyframes, or false otherwise.
  */
  bool isInterpolation() const;

  /** \details
   Returns the coordinate values to move the selected objects into this position.

   \returns Reference to the OdGeVector3d object with move vector.
  */
  const OdGeVector3d& getTranslation() const;

  /** \details
   Returns the rotation of the object from center.

   \returns Rotation of the object from center as an OdGeQuaternion value.
  */
  const OdGeQuaternion & getRotation() const;
  
  /** \details
   Return orientation of the rotation.

   \returns Orientation of the rotation from center as an OdGeQuaternion value.
  */
  const OdGeQuaternion & getRotationToolOrientation() const;
  
  /** \details
   Returns origin (or center point) of the rotation or scale.

   \returns Origin (or center point) as an OdGePoint3d instance.
  */
  const OdGePoint3d & getCenter() const;

  /** \details
   Returns color of the object.

   \returns Color of the object as an OdNwColor value.
  */
  const OdNwColor & getColor() const;
  
  /** \details
   Returns transparency level.

   \returns Transparency level as a double value.
  */
  double getOpacity() const;
  
  /** \details
   Returns adjusted rotation of the object for the scale procedure.

   \returns Adjusted rotation of the object for the scale procedure as an OdGeQuaternion.
  */
  const OdGeQuaternion & getScaleQuaternion() const;

  /** \details
   Returns scaling factor.

   \returns Scaling factor as an OdGeVector3d reference.
  */
  const OdGeVector3d & getScaleVector() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwSavedAnimSelectKeyFrame object pointers.
*/
typedef OdSmartPtr<OdNwSavedAnimSelectKeyFrame> OdNwSavedAnimSelectKeyFramePtr;

#endif /* __NW_SAVEDANIMSELECTKEYFRAME_H__ */
