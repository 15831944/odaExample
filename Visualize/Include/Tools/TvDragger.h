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

//DOM-IGNORE-BEGIN
#ifndef OD_TV_DRAGGER_H
#define OD_TV_DRAGGER_H

//ODA
#include "Ge/GePoint3d.h"
#include "SharedPtr.h"
// #include "OdaCommon.h"

//ODA Visualize SDK
#include "TvFactory.h"
#include "TvGsView.h"

//ODA Visualize SDK extension
#include "TvExtendedView.h"
//DOM-IGNORE-END

/** \details
  Types of dragging operation results.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
enum eDraggerResults
{
  kNothingToDo          = 0x00, // No action is needed.
  kNeedUpdateCursor     = 0x01, // Need to update the cursor.
  kNeedUpdateView       = 0x02, // Need to update the view.
  kNeedFinishDragger    = 0x04, // Need to finish the dragging operation.
};

/** \details
  A data type that represents the dragging operation result.
*/
typedef unsigned int eDraggerResult;

/** \details
  Dragging object states.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
enum eDraggerViewChangeTypes
{
  kViewChangePan        = 0x00,    // Notify that the view was panned
  kViewChangeZoom       = 0x01,    // Notify that the view was zoomed (in/out, window, extents)
  kViewChangeRotate     = 0x02,    // Notify that the view was rotated
  kViewChangeFull       = 0x04,    // Notify that the view parameters was changed
  kViewChangeSize       = 0x08     // Notify that the view size was changed (resize or relative size was changed)
};

/** \details
  A data type that represents the type of the view change about which the dragger is notified.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
typedef unsigned int eDraggerViewChangeType;

/** \details
  A data type that represents the dragging operation result.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
typedef unsigned int eDraggerResult;

class OdTvDragger;

/** \details
  A data type that represents a smart pointer to an <link OdTvDragger, OdTvDragger> object.
*/
typedef OdSharedPtr<OdTvDragger> OdTvDraggerPtr;

//DOM-IGNORE-BEGIN
#define CHECK_DRAGGER                                                                                \
  if ( m_state == kWaiting )                                                                         \
    return kNothingToDo;                                                                             \
                                                                                                     \
  OdTvGsViewPtr pView = getActiveTvViewPtr();                                                        \
  if ( pView.isNull() )                                                                              \
    return kNothingToDo;    
//DOM-IGNORE-END
    

/** \details
  The interface class that provides a base implementation for the Visualize Viewer dragging tool.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
class ODTVTOOLS_EXPORT OdTvDragger
{
public:

  ODRX_HEAP_OPERATORS();

  /** \details
    Dragging object states.
  */
  enum eDraggerState
  {
    kWaiting = 0, // The dragger object is waiting for a user's action.
    kWorking = 1, // The dragger object is working. 
    kFinishing    // The dragger object is finishing the operation.
  };

  /**\details 
    Creates a new dragging object with specified parameters.
    
    \param tvDeviceId         [out] A placeholder for the identifier of the device object the dragging object is associated with.
    \param tvDraggersModelId  [out] A placeholder for the identifier of the model that contains dragging objects.
    \remarks
    The constructor creates a new dragging object instance and stores device and model identifiers to the passed parameters to return them to a calling subroutine.
  */
  OdTvDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId);

  /** \details 
    Destroys the dragging object.
  */
  virtual ~OdTvDragger();

  /** \details
    Starts the dragging operation.
    
    \param pPrevDragger   [in] A smart pointer to a previous dragging operation.
    \param pExtendedView  [in] A raw pointer to the associated extended view.
    \returns Returns the result of the dragging operation start.
    \remarks 
    The method should be called to prepare the dragging object for the operation.
  */
  virtual eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);

  /** \details
    Activates the dragging object.
    
    \returns Returns the result of the activating.
    \remarks 
    The method should be called to prepare the dragging object for the operation.
  */
  virtual eDraggerResult activate();

  /** \details
    The mouse button click event handler for the dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse button click event.
  */
  virtual eDraggerResult nextpoint(int x, int y);

  /** \details
    The mouse button release event handler for the dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse button click event.
 */
  virtual eDraggerResult nextpointup(int x, int y);

  /** \details
    The mouse move event handler for the dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse move event.
  */
  virtual eDraggerResult drag(int x, int y);

  /** \details
    Finishes the dragging operation.
    
    \param rc [out] A placeholder for the result of the operation.
    \returns Returns a smart pointer to the previous dragging object.
    \remarks 
    The method should be called before exiting from the dragging operation.
  */
  virtual OdTvDraggerPtr finish(eDraggerResult& rc);

  /** \details
    Checks whether the dragging operation can be finished.
    
    \returns Returns true if the dragging operation can be finished; otherwise the method returns false.
  */
  virtual bool canFinish();

  /** \details
    Processes the Enter key press event.
    
    \returns Returns the result of the event processing.
  */
  virtual eDraggerResult processEnter();

  /** \details
    Processes the Backspace key press event.
    
    \returns Returns the result of the event processing.
  */
  virtual eDraggerResult processBackspace();

  /** \details
    Processes the Escape key press event.
    
    \returns Returns the result of the event processing.
  */
  virtual eDraggerResult processEscape();

  /** \details
    Processes the Delete key press event.
    
    \returns Returns the result of the event processing.
  */
  virtual eDraggerResult processDelete();

  /** \details
    Processes the text input event.
    
    \param text [in] A string that contains the input text.
    \returns Returns the result of the event processing.
  */
  virtual eDraggerResult processText(const OdString& text) { return kNothingToDo; };

  /** \details
    Processes the mouse right button press event.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of the event processing.
  */
  virtual eDraggerResult processMouseRightBtn(int x, int y);

  /** \details
    Modifies the geometry at each view update. 
    
    \remarks 
    Formally creating and deleting temporary geometry dragging objects should be performed inside
    the <link OdTvDragger::start@OdTvDraggerPtr@OdTvExtendedView*, start()> 
    and <link OdTvDragger::finish@eDraggerResult&, finish()> methods or in other appropriate methods; 
    modification of such objects should be normally performed inside the 
    <link OdTvDragger::nextpoint@int@int, nextpoint()>, <link OdTvDragger::nextpointup@int@int, nextpointup()> 
    and <link OdTvDragger::drag@int@int, drag()> methods. 
    But there are some situations when the geometry should be modified at each view update. 
    This method allows for these operations.
  */
  virtual void drawInvalidate();

  /** \details
    Notify that the view is changed
    \remarks
  */
  virtual void notifyAboutViewChange(eDraggerViewChangeType notify);

  /** \details
    Checks whether it is needed to receive and process events that are not mouse clicks.
    
    \returns Returns true if it is needed to receive and process other events besides the mouse clicks; otherwise the method returns false.
  */
  bool needFreeDrag() { return m_bNeedFreeDrag; }

  /** \details
    Checks whether the dragging object has a previous one.
    
    \returns Returns true if the current dragging object has a previous one; otherwise the method returns false.
  */
  bool hasPrevious() { return !m_pPrevDragger.isNull(); }

  /** \details
    Checks the current state of the dragging object.
    
    \returns Returns the current state.
  */
  eDraggerState getState() { return m_state; }

  /** \details
    Checks whether the dragging object needs input text to be entered.
    
    \returns Returns true if the dragging object needs input text; otherwise the method returns false.
  */
  bool needText() { return false; }

  /** \details
    Checks the invalidation time of the dragging object in milliseconds.
    
    \returns Returns the true number of milliseconds that determines when the dragging object needs to be invalidated.
  */
  int getInvalidationTime() { return m_iInvalidateTime; }

  /** \details
    Sets a new invalidation time for the dragging object.
    
    \param time [in] A quantity of milliseconds to make the dragging object invalidated. 
  */
  void setInvalidationTime(int time) { m_iInvalidateTime = time; }

//DOM-IGNORE-BEGIN
protected:
  
  /** \details
    Resets the dragger state.
  */
	virtual eDraggerResult reset();

  /** \details
    Converts eye points to WCS in eye planes.
  */
  OdGePoint3d toEyeToWorld(int x, int y) const;

  /** \details
    Converts WCS point in eye plane to WCS point in UCS plane.
    By default the UCS plane is equal to WCS plane.
  */
  bool toUcsToWorld(OdGePoint3d& wcsPt) const;

  /** \details
    Returns the active TvView.
  */
  OdTvGsViewPtr getActiveTvViewPtr() const;

  /** \details
    Adds a dragger model to the active view.
  */
  void addDraggersModelToView();

  /** \details
    Removes the dragger's model from the active view.
  */
  void removeDraggersModelFromView();

  /** \details
    This method updates the cursor (if needed).
  */
  virtual bool updateCursor();

protected:

  //device, associated with this dragger
  OdTvGsDeviceId m_TvDeviceId; 

  //special model for managing dragger's temporary geometry
  OdTvModelId m_tvDraggersModelId;

  //pointer to tv extended window (with which the dragger has started)
  OdTvExtendedView* m_pTvExtendedView;

  // state of the dragger
  eDraggerState m_state;

  //pointer to the previous dragger
  OdTvDraggerPtr m_pPrevDragger;

  //flag that indicates whether the dragger has temporary drawable geometry
  bool m_bHaveDrawableTemporaryGeometry;

  //flag that indicates whether the dragger wants to receive drag without pressed buttons 
  bool m_bNeedFreeDrag;

  //time to invalidate dragger, milliseconds
  int m_iInvalidateTime;

  //UCS parameters
  OdTvPoint  m_ptOrigin;
  OdTvVector m_xAxis;
  OdTvVector m_yAxis;
//DOM-IGNORE-END
};

#endif //OD_TV_DRAGGER_H
