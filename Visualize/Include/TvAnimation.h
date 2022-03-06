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

#ifndef _ODTV_ANIMATION_H_INCLUDED_
#define _ODTV_ANIMATION_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvEntity.h"
#include "TvSelection.h"

/** \details
  This is an abstract class that represents the interface for an animation action object.
  
  \remarks
  Each action should contain keypoints in some frames. Values in frames without keypoint data are results of interpolation between nearest keypoints.
  Each keypoint contains data as pairs < OdTvAnimationAction::Keydata, double value >.
  Interpolation in interval [KeypointA, KeypointB] uses KeypointA interpolation type.
  Open intervals ( [0, Keypoint_1] and [Keypoint_Last, numFrames()] ) use nearest keypoint values.
*/
class ODTV_EXPORT OdTvAnimationAction : public OdTvHandledIObject
{
public:
  /** \details
    Enumerates animation action keypoint data types.
  */
  enum Keydata
  {
    kTranslationX,  //Translation by X axis.
    kTranslationY,  //Translation by Y axis.
    kTranslationZ,  //Translation by Z axis.
    kRotationX,     //Rotation by X axis.
    kRotationY,     //Rotation by Y axis.
    kRotationZ,     //Rotation by Z axis.
    kScaleX,        //Scaling by X axis.
    kScaleY,        //Scaling by Y axis.
    kScaleZ,        //Scaling by Z axis.

    kNumKeydata     //Service type: number of actual data types.
  };
  
  /** \details
    Enumerates animation action keypoint data interpolation.
  */
  enum Interpolator
  {
    kThreshold,     //No interpolation: value is equal to the previous keypoint value.
    kLinear,        //Linear interpolation.
    kCubic          //Cubic spline interpolation.
  };
  
  /** \details
    The interface class for the iterator of <link OdTvAnimationKeypointIterator, OdTvAnimationKeypointIterator> objects.
    An iterator object provides sequential access to a collection of animation action keypoints.
  */
  class ODTV_EXPORT OdTvAnimationKeypointIterator : public OdTvIterator, public OdTvIObject
  {
  public:
    /** \details
      Retrieves keypoint frame.
      
      \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
      \returns Returns keypoint frame number.
    */
    virtual OdUInt32 frame( OdTvResult* rc = NULL ) const = 0;
    
    /** \details
      Checks that keypoint has data of specified type.
      
      \param kd     [in]   Keypoint data type.
      \param pValue [out]  Pointer to the value to store keypoint data value.
      \param rc     [out]  A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
      \returns Returns true if keypoint contain specified data type; otherwise returns false.
      \remarks If keypoint contains specified data type and pValue is not a NULL, keypoint data value will be stored in pValue.
    */
    virtual bool hasData( OdTvAnimationAction::Keydata kd, double* pValue = NULL, OdTvResult* rc = NULL ) const = 0;
  };
  
  /** \details
    A data type that represents a smart pointer to an <link OdTvAnimationActionsIterator, OdTvAnimationActionsIterator> object.
  */
  typedef OdTvSmartPtr<OdTvAnimationKeypointIterator> OdTvAnimationKeypointIteratorPtr;
  
  /** \details
    Specifies keypoint data in the action frame.
    
    \param nFrame [in] Action frame where keypoint should be specified.
    \param kd     [in] Keypoint data type.
    \param keyval [in] Keypoint data value.
    \param ipl    [in] Keypoint data interpolation type.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If there is no keypoint in specified frame, new keypoint will be created. 
    If keypoint already exists in specified frame, specified data will be added or overwritten.
  */
  virtual OdTvResult setKeypoint( OdUInt32 nFrame, Keydata kd, double keyval, Interpolator ipl = kCubic ) = 0;
  
  /** \details
    Checks whether a keypoint exists in the specified frame.
    
    \param nFrame [in] Action frame number.
    \param rc     [out]  A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if specified frame already contains keypoint; otherwise returns false.
  */
  virtual bool hasKeypoint( OdUInt32 nFrame, OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Checks whether the keypoint has data of specified type.
    
    \param nFrame [in]   Action frame number.
    \param kd     [in]   Keypoint data type.
    \param pValue [out]  Pointer to the value to store keypoint data value.
    \param rc     [out]  A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if keypoint contain specified data type; otherwise returns false.
    \remarks 
    If keypoint contains specified data type and pValue is not a NULL, keypoint data value will be stored in pValue.
    If no keypoint exist in specified frame, tvInvalidInput will be used as rc value.
  */
  virtual bool keypointHasData( OdUInt32 nFrame, Keydata kd, double* pValue, OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Removes keypoint from specified frame.
    
    \param nFrame [in]   Action frame number.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult removeKeypoint( OdUInt32 nFrame ) = 0;
  
  /** \details
    Removes all keypoints.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult removeKeypoints() = 0;
  
  /** \details
    Retrieves action keypoints iterator.
    
    \param rc [out]  A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns smart pointer to the keypoint iterator.
  */
  virtual OdTvAnimationKeypointIteratorPtr getKeypointsIterator( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves frame data of specified type.
    
    \param nFrame [in]   Action frame number.
    \param kd     [in]   Data type.
    \param pValue [out]  Pointer to the value to store data value.
    \param rc     [out]  A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if frame contains specified data type; otherwise returns false.
    \remarks 
    Unlike keypointHasData method, frameData method can be called for any action frame whether it has a keypoint or not.
  */
  virtual bool frameData( OdUInt32 nFrame, Keydata kd, double* pValue, OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves action frames number.
    
    \param rc     [out]  A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns number of action frames.
  */
  virtual OdUInt32 numFrames( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies number of action frames.
    
    \param nFrames       [in] A number of action frames.
    \param bRescaleRange [in] A flag that indicates, should exist keypoints be rescaled or not.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If nFrames is less than numFrames() and bRescaleRange is false, all keypoint from frames more than nFrame will be removed.
  */
  virtual OdTvResult setNumFrames( OdUInt32 nFrames, bool bRescaleRange = false ) = 0;
  
  /** \details
    Retrieves action speed.
    
    \param rc     [out]  A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns action speed as number of frames per second.
  */
  virtual OdUInt32 FPS( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies action speed.
    
    \param fps    [in] Action speed as number of frames per second.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult setFPS( OdUInt32 fps ) = 0;
  
  /** \details
    Retrieves action active frame.
    
    \param rc     [out]  A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns action active frame.
  */
  virtual OdUInt32 activeFrame( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies action active frame.
    
    \param fps    [in] Action active frame.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult setActiveFrame( OdUInt32 nFrame ) const = 0;
  
  /** \details
    Sets a new name for the animation action.
    
    \param sName [in] A string that contains the new name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the renaming.
    \remarks
    If the new name was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName( const OdString& sName ) = 0;
  
  /** \details
    Retrieves the current name of the animation action.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current name of the device.
    \remarks
    If the rc parameter is not null and the action name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getName( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Checks whether the action should be saved in file or not.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns flag that indicate should action be saved in file or not.
    \remarks
    Animation containers, that contain actions that should not be saved in file, will skip such pairs <Action, Actor> during the saving.
  */
  virtual bool getNeedSaveInFile( OdTvResult* rc = NULL ) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvAnimationAction, OdTvAnimationAction> object.
*/
typedef OdTvSmartPtr<OdTvAnimationAction> OdTvAnimationActionPtr;

/** \details
  The interface class for a database object identifier that allows access to the <link OdTvAnimationAction, OdTvAnimationAction> object.
*/
class ODTV_EXPORT OdTvAnimationActionId : public OdTvId
{
public:
  /** \details
    Opens the Animation action determined with its identifier for a read or write operation.
    
    \param mode [in] An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the animation action object.
    \remarks
    If the rc parameter is not null and the animation action is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvAnimationActionPtr openObject( OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL ) const;
};

/** \details
  The interface class for the iterator of <link OdTvAnimationAction, OdTvAnimationAction> objects.
  An iterator object provides sequential access to a collection of animation actions.
*/
class ODTV_EXPORT OdTvAnimationActionsIterator : public OdTvIterator, public OdTvIObject
{
public:
  /** \details
    Retrieves the animation action that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the animation action identifier if the iterator refers to a animation action; otherwise it returns a null value identifier.
    \remarks
    If the rc parameter is not null and the animation action identifier is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    If the iterator refers to an animation action, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvAnimationActionId getAnimationAction( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Searches the animation action defined through its identifier and moves the iterator to this animation action if found.
    
    \param actionId [in] An animation action identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the animation action specified through its identifier is found, the method returns the tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek( const OdTvAnimationActionId& actionId ) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvAnimationActionsIterator, OdTvAnimationActionsIterator> object.
*/
typedef OdTvSmartPtr<OdTvAnimationActionsIterator> OdTvAnimationActionsIteratorPtr;

class OdTvAnimationIterator;


/** \details
  This is an abstract class that represents the interface for an Animation container.
  Animation container contains animations: pairs of <Actor, Action> with additional properties
  where Actor defines the object to be animated and Action defines modification rules.
  
  \sa
  <link tv_working_with_features_animation, Work with Animation>
*/
class ODTV_EXPORT OdTvAnimationContainer : public OdTvHandledIObject
{
public:
  /**\ details
    This class represents actor basis.
  */
  class ODTV_EXPORT OdTvActorBasis
  {
  public:
    /** \details
      Constructs actor basis with default origin (0.0.0) and default axis { (1,0.0), (0,1,0), (0,0,1) }.
    */
    OdTvActorBasis();
    /** \details
      Constructs actor basis with specified origin and default axis { (1,0.0), (0,1,0), (0,0,1) }.
      
      \param origin [in] Basis origin.
    */
    OdTvActorBasis( const OdTvPoint& origin );
    
    /** \details
      Constructs actor basis with specified origin and axis.
      
      \param origin [in] Basis origin.
      \param xAxis  [in] Basis X axis.
      \param yAxis  [in] Basis Y axis.
      \param zAxis  [in] Basis Z axis.
    */
    OdTvActorBasis( const OdTvPoint& origin, const OdTvVector& xAxis, const OdTvVector& yAxis, const OdTvVector& zAxis );
    
    /** \details
      Retrieves basis origin.
      
      \returns Returns the reference to the basis origin.
    */
    OdTvPoint& origin();
    
    /** \details
      Retrieves basis origin.
      
      \returns Returns the basis origin.
    */
    const OdTvPoint& origin() const;
    
    /** \details
      Retrieves basis X axis.
      
      \returns Returns the reference to the basis X axis.
    */
    OdTvVector& xAxis();
    
    /** \details
      Retrieves basis X axis.
      
      \returns Returns the basis X axis.
    */
    const OdTvVector& xAxis() const;
    
    /** \details
      Retrieves basis Y axis.
      
      \returns Returns the reference to the basis Y axis.
    */
    OdTvVector& yAxis();
    
    /** \details
      Retrieves basis Y axis.
      
      \returns Returns the basis Y axis.
    */
    const OdTvVector& yAxis() const;
    
    /** \details
      Retrieves basis Z axis.
      
      \returns Returns the reference to the basis Z axis.
    */
    OdTvVector& zAxis();
    
    /** \details
      Retrieves basis Z axis.
      
      \returns Returns the basis Z axis.
    */
    const OdTvVector& zAxis() const;
//DOM-IGNORE-BEGIN
  protected:
    OdTvPoint m_origin;
    OdTvVector m_axis[ 3 ];
//DOM-IGNORE-END
  };
  
  /** \details
    Adds the action of the specified actor to the container.
    
    \param actor        [in] Actor (path to the object) that should execute action.
    \param actionId     [in] ID of the action object.
    \param nRepeats     [in] Number of action repeats (0 - no repeats, -1 - endless)
    \param timeStart    [in] Time of animation start (msecs since play()).
    \param pCustomBasis [in] Custom actor basis (NULL for defaults).
    \returns Returns the result of the remove operation as an <link OdTvResult, OdTvResult> value.
  */
  virtual OdTvResult addAnimation( const OdTvSubItemPath& actor, const OdTvAnimationActionId& actionId, OdInt32 nRepeats = 0, OdUInt32 timeStart = 0, OdTvActorBasis* pCustomBasis = NULL ) = 0;
  
  /** \details
    Removes specified animation from container.
    
    \param pIterator [in] Smart pointer to the iterator object, that defines animation to be removed from container.
    \returns Returns the result of the remove operation as an <link OdTvResult, OdTvResult> value.
  */
  virtual OdTvResult removeAnimation( const OdTvSmartPtr<OdTvAnimationIterator>& pIterator ) = 0;
  
  /** \details
    Removes all animations with specified actor.
    
    \param actor [in] Actor (path to the object) that should be removed will all it actions.
    \returns Returns the result of the remove operation as an <link OdTvResult, OdTvResult> value.
  */
  virtual OdTvResult removeAnimations( const OdTvSubItemPath& actor ) = 0;
  
  /** \details
    Removes all animations from container.
    
    \returns Returns the result of the remove operation as an <link OdTvResult, OdTvResult> value.
  */
  virtual OdTvResult removeAnimations() = 0;
  
  /** \details
    Validate all animations in the animation container.
    
    \returns Returns the result of the remove operation as an <link OdTvResult, OdTvResult> value.
    \remarks After adding to the animation container, actor can be modified. So, animation container have to update actor cache.
    However, currently container can not catch actors modifications, so this method have to be called manually.
  */
  virtual OdTvResult validateAnimations() = 0;
  
  /** \details
    Retrieves animations iterator.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns smart pointer to the animation iterator object.
  */
  virtual OdTvSmartPtr<OdTvAnimationIterator> getAnimationIterator( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies actual time for the animation container.
    
    \param msec [in] Actual time in milliseconds.
    \returns Returns the result of the remove operation as an <link OdTvResult, OdTvResult> value.
    \remarks
    This method will execute all appropriate actions of all actors.
  */
  virtual OdTvResult setCurrentTime( OdUInt32 msec ) = 0;
  
  /** \details
    Retrieves actual animation container time.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns actual animation container time.
  */
  virtual OdUInt32 currentTime( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves animation container summary time.
    
    \param msec [out] A reference to the variable to store the summary time in milliseconds.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if animation container has finite summary time; otherwise returns false.
  */
  virtual bool totalTime( OdUInt32& msec, OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Resets all animations of all actors in the animation container.
    
    \returns Returns the result of the remove operation as an <link OdTvResult, OdTvResult> value.
    \remarks 
    Since even first (0) action frame may modify original object, this method resets all action changes and restore actor into original state.
  */
  virtual OdTvResult reset() = 0;
  
  /** \details
    Sets a new name for the animation container.
    
    \param sName [in] A string that contains the new name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the renaming.
    \remarks
    If the new name was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName( const OdString& sName ) = 0;
  
  /** \details
    Retrieves the current name of the animation container.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current name of the device.
    \remarks
    If the rc parameter is not null and the action name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getName( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Checks whether the container should be saved in file or not.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns flag that indicate should container be saved in file or not.
  */
  virtual bool getNeedSaveInFile( OdTvResult* rc = NULL ) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvAnimationContainer, OdTvAnimationContainer> object.
*/
typedef OdTvSmartPtr<OdTvAnimationContainer> OdTvAnimationContainerPtr;

/** \details
  This is an abstract class that represents the interface for an Animation iterator.
*/
class ODTV_EXPORT OdTvAnimationIterator : public OdTvIterator, public OdTvIObject
{
public:
  /** \details
    Retrieves animation start time.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns animation start time (in millisecond).
  */
  virtual OdUInt32 timeStart( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves animation action.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns animation action.
  */
  virtual OdTvAnimationActionId action( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves animation actor.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns animation actor.
    \remarks
    Actor is a path to the object that should execute action.
  */
  virtual const OdTvSubItemPath& actor( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves animation repeats count.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns animation repeats count.
    \remarks
    Zero repeats count means action executes only once; -1 means infinite actions loop.
  */
  virtual OdInt32 repeats( OdTvResult* rc = NULL ) const = 0;
  
/** \details
    Retrieves animation actor basis.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns animation actor basis.
  */
  virtual const OdTvAnimationContainer::OdTvActorBasis& basis( OdTvResult* rc = NULL ) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvAnimationIterator, OdTvAnimationIterator> object.
*/
typedef OdTvSmartPtr<OdTvAnimationIterator> OdTvAnimationIteratorPtr;


/** \details
  The interface class for a database object identifier that allows access to the <link OdTvAnimationContainer, OdTvAnimationContainer> object.
*/
class ODTV_EXPORT OdTvAnimationContainerId : public OdTvId
{
public:
  /** \details
    Opens the Animation container determined with its identifier for a read or write operation.
    
    \param mode [in] An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the animation container object.
    \remarks
    If the rc parameter is not null and the animation container is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvAnimationContainerPtr openObject( OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL ) const;
};

/** \details
  The interface class for the iterator of <link OdTvAnimationContainer, OdTvAnimationContainer> objects.
  An iterator object provides sequential access to a collection of animation containers.
*/
class ODTV_EXPORT OdTvAnimationContainersIterator : public OdTvIterator, public OdTvIObject
{
public:
  /** \details
    Retrieves the animation container that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the animation container identifier if the iterator refers to a animation container; otherwise it returns a null value identifier.
    \remarks
    If the rc parameter is not null and the animation container identifier is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    If the iterator refers to an animation container, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvAnimationContainerId getAnimationContainer( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Searches the animation container defined through its identifier and moves the iterator to this animation container if found.
    
    \param containerId [in] An animation container identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the animation container specified through its identifier is found, the method returns the tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek( const OdTvAnimationContainerId& containerId ) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvAnimationContainersIterator, OdTvAnimationContainersIterator> object.
*/
typedef OdTvSmartPtr<OdTvAnimationContainersIterator> OdTvAnimationContainersIteratorPtr;


#endif // _ODTV_ANIMATION_H_INCLUDED_
