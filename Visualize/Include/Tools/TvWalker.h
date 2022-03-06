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

#ifndef _ODTV_WALKER_H_INCLUDED_
#define _ODTV_WALKER_H_INCLUDED_

#include "TvToolsExport.h"

// Visualize SDK
#include "TvEntity.h"
#include "TvCamera.h"
#include "TvAnimation.h"
#include <map>


/** \details
  This class implements camera walking methods.
*/
class ODTVTOOLS_EXPORT OdTvCameraWalker
{
public:
  /** \details
    Constructs the OdTvCameraWalker object.
  */
  OdTvCameraWalker();
  
  /** \details
    Destroys the OdTvCameraWalker object.
  */
  ~OdTvCameraWalker();
  
  /** \details
    Specifies a camera that will walk.
    
    \param cameraId [in] OdTvEntityId that refers to the OdTvCamera object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult setCamera( OdTvEntityId cameraId );
  
  /** \details
    Retrieves camera object.
    
    \returns Returns OdTvEntityId that refers to the OdTvCamera object.
  */
  OdTvEntityId camera() const;
  
  /** \details
    Translates the camera in a given direction.
    
    \param moveVector [in] Moving direction and distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks moveVector direction will be a moving direction and moveVector length will be a moving distance.
  */
  OdTvResult move( const OdTvVector& moveVector );
  
  /** \details
    Rotates the camera around the specified axis.
    
    \param axis [in] Rotation axis.
    \param angle [in] Rotation angle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult turn( const OdTvVector& axis, double angle );
  
  /** \details
    Translates the camera object forward in a viewing direction.
    
    \param moveDistance [in] Moving distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult moveForward( double moveDistance );
  
  /** \details
    Translates the camera object backward in a viewing direction.
    
    \param moveDistance [in] Moving distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult moveBackward( double moveDistance );
  
  /** \details
    Translates the camera object backward in a right vector direction.
    
    \param moveDistance [in] Moving distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult moveLeft( double moveDistance );
  
  /** \details
    Translates the camera object forward in a right vector direction.
    
    \param moveDistance [in] Moving distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult moveRight( double moveDistance );
  
  /** \details
    Translates the camera object forward in a up vector direction.
    
    \param moveDistance [in] Moving distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult moveUp( double moveDistance );
  
  /** \details
    Translates the camera object backward in a down vector direction.
    
    \param moveDistance [in] Moving distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult moveDown( double moveDistance );
  
  /** \details
    Turns camera left.
    
    \param angle [in] Rotation angle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult turnLeft( double angle );
  
  /** \details
    Turns camera right.
    
    \param angle [in] Rotation angle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult turnRight( double angle );
  
  /** \details
    Turns camera up.
    
    \param angle [in] Rotation angle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult turnUp( double angle );
  
  /** \details
    Turns camera down.
    
    \param angle [in] Rotation angle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  OdTvResult turnDown( double angle );

  //DOM-IGNORE-BEGIN
protected:
  OdTvEntityId m_camera;
  //DOM-IGNORE-END
};

/** \details
  This structure defines camera walking animation interpolation step.
*/
struct ODTVTOOLS_EXPORT OdTvCameraAnimationStep
{
  /** Camera that presents animation keyframe. */
  OdTvEntityId camera;
  /** Keyframe value. */
  OdUInt32 frame;
  /** Keyframe interpolation type. */
  OdTvAnimationAction::Interpolator interpol;
  /** \details
  Constructs default OdTvCameraAnimationStep object.
  */
  OdTvCameraAnimationStep() : camera( OdTvEntityId() ), frame( 0 ), interpol( OdTvAnimationAction::kLinear )
  {

  }
};

/** \details
  This structure defines camera actions group.
*/
struct ODTVTOOLS_EXPORT OdTvCameraAction
{
  /** Camera position action. */
  OdTvAnimationActionId positionAction;
  /** Camera target action. */
  OdTvAnimationActionId targetAction;
  /** Camera up vector action. */
  OdTvAnimationActionId upAction;
  /** Camera fields width and height action. */
  OdTvAnimationActionId fieldsAction;
  
  /** \details
    Retrieves camera action by index.
    
    \param ind [in] Action index.
    \returns Returns camera action associated with specified index.
  */
  OdTvAnimationActionId action( OdUInt8 ind ) const
  {
    switch( ind )
    {
    case 0: return positionAction;
    case 1: return targetAction;
    case 2: return upAction;
    case 3: return fieldsAction;
    }
    return OdTvAnimationActionId();
  }
};

/** \details
  This function fills OdTvCameraAction so it will pass all OdTvCameraAnimationStep.
  
  \param result       [out] Instance of OdTvCameraAction to store result.
  \param actorCamera  [in] Camera object that will be used as actor.
  \param steps        [in] Vector of OdTvCameraAnimationStep.
  \returns Returns true if actions generation successful; otherwise returns false.
*/
bool ODTVTOOLS_EXPORT generateCameraWalkingAction( OdTvCameraAction& result, OdTvEntityId actorCamera, const OdVector<OdTvCameraAnimationStep>& steps );


#endif //_ODTV_WALKER_H_INCLUDED_
