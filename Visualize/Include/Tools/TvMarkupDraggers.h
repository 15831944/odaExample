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

#ifndef OD_TV_VIEWERMARKUPDRAGGERS_H
#define OD_TV_VIEWERMARKUPDRAGGERS_H

//ODA Visualize Viewer
#include "OdList.h"

// Visualize SDK extensions
#include "TvDragger.h"

//DOM-IGNORE-BEGIN
// name of temp entity for markups
#define OD_TV_MARKUP_TEMP_ENTITY    OD_T("$MarkupTempEntity")
#define OD_TV_MARKUP_MODEL          OD_T("$ODA_TVVIEWER_MARKUPS")

#define OD_TV_MARKUP_RECTANGLES   OD_T("Rectangles")
#define OD_TV_MARKUP_CIRCLES      OD_T("Circles")
#define OD_TV_MARKUP_TEXT         OD_T("Texts")
#define OD_TV_MARKUP_FREEHANDLES  OD_T("Free handles")
#define OD_TV_MARKUP_CLOUDS       OD_T("Clouds")

#define OD_TV_MARKUP_TEXTSTYLE    OD_T("TextStyle")
#define OD_TV_MARKUP_LINESPACING   0.035
#define OD_TV_MARKUP_TEXTSIZE      0.02
#define OD_TV_MARKUP_ADDCARETTRANSLATION 0.001
//DOM-IGNORE-END

/**\details
  Searches for a geometry sub-entity by its name.
  
  \param pIt      [in] A smart pointer to the iterator object that provides access to the geometry data of sub-entities.
  \param name     [in] A string that contains the sub-entity name to search for.
  \param onlyName [in] A flag that determines whether the only first found sub-entity with the specified name should be returned.
  \returns Returns an identifier of the geometry sub-entity if it was found; otherwise returns an empty identifier.
  \remarks 
  If the onlyName parameter value is equal to true (by default), the function searches through the geometry sub-entities and 
  returns the last found sub-entity with the specified name.
  If the onlyName parameter value is equal to false, the function searches for either the first visible sub-entity 
  that has a name other than specified in the name parameter or the first sub-entity with the specified name.
*/
OdTvGeometryDataId findSubEntityByName(OdTvGeometryDataIteratorPtr pIt, const OdString& name, bool onlyName = true);

/**\details
  Searches for an entity by its name.
  
  \param pIt      [in] A smart pointer to the iterator object that provides access to the entities collection.
  \param name     [in] A string that contains the entity name to search for.
  \param onlyName [in] A flag that determines whether the only first found entity with the specified name should be returned.
  \returns Returns an identifier of the entity if it was found; otherwise returns an empty identifier.
  \remarks 
  If the onlyName parameter value is equal to true (by default), the function searches through the entities and 
  returns the last found entity with the specified name.
  If the onlyName parameter value is equal to false, the function searches for either the first visible entity 
  that has a name other than specified in the name parameter or the first entity with the specified name.
*/
OdTvEntityId       findEntityByName(OdTvEntitiesIteratorPtr pIt, const OdString& name, bool onlyName = true);

/** \details
  The base interface class that stores the parameters of the view that is associated with the markup entity.
*/
class ODTVTOOLS_EXPORT OdTvSaveViewParams
{
public:

  OdTvPoint               m_pos;          // The view's camera position.
  OdTvPoint               m_target;       // The view's camera target.
  OdTvVector              m_up;           // The view's camera up-vector.
  OdTvGsView::Projection  m_proj;         // The view's camera projection type.
  OdTvGsView::RenderMode  m_mode;         // The view's rendering mode.
  double                  m_width;        // The view's camera field width.
  double                  m_height;       // The view's camera field height.
  OdInt64                 m_modelHandle;  // The model handle

  /** \details
    Creates a new set of view parameters with default values.
  */
  OdTvSaveViewParams() : m_width(0.), m_height(0.), m_modelHandle(0)
  {}

  /** \details
    Fills parameters from view object.
    
    \param viewId  [in]  An identifier of a view object that is the base for the created object.
  */
  void fillParams(const OdTvGsViewId& viewId);

  /** \details
    Destroys the set of view parameters.
  */
  virtual ~OdTvSaveViewParams() {}

  /** \details
    Reads data from the platform-dependent stream.
    
    \param strm [in] Pointer to a stream buffer to read from.
  */
  void read(OdStreamBuf* strm);

  /** \details
    Writes data to the platform-dependent stream.
    
    \param strm [in] Pointer to a stream buffer to write to.
  */
  void write(OdStreamBuf* strm);

  //DOM-IGNORE-BEGIN
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END
};

/** \details
  The base interface class for rectangle markup dragging.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
class ODTVTOOLS_EXPORT OdTvRectangleMarkupDragger : public OdTvDragger
{
public:

  ODRX_HEAP_OPERATORS();
  
  /** \details 
    Creates a new rectangle markup dragging object with specified parameters. 
    
    Returns the device identifier and the identifier of the model that contains dragging objects to a calling subroutine.
    \param tvDeviceId         [out] A placeholder for the device identifier that is returned to a calling subroutine. 
    \param tvDraggersModelId  [out] A placeholder for the identifier of the model that contains dragging objects to be returned to a calling subroutine. 
    \param appTvId            [in]  An identifier of the registered application associated with the rectangle markup dragging object.
    \param color              [in]  A color of the rectangle markup.
    \param weight             [in]  A weight of the rectangle markup.
  */
  OdTvRectangleMarkupDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, const OdTvRegAppId& appTvId, OdTvColorDef color, OdUInt8 weight);
  
  /**\details 
    Destroys the rectangle markup dragging object.
  */
  ~OdTvRectangleMarkupDragger();

  /** \details
    Starts the rectangle markup dragging operation.
    
    \param pPrevDragger   [in] A smart pointer to a previous dragging operation.
    \param pExtendedView  [in] A raw pointer to the associated extended view.
    \returns Returns the result of the dragging operation start.
    \remarks 
    The method should be called to prepare the dragging object for the operation.
  */
  eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
  
  /** \details
    The mouse button click event handler for the rectangle markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse button click event.
  */
  eDraggerResult nextpoint(int x, int y);
  
  /** \details
    The mouse move event handler for the rectangle markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse move event.
  */
  eDraggerResult drag(int x, int y);
  
  /** \details
    The mouse button release event handler for the rectangle dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse button click event.
 */
  eDraggerResult nextpointup(int x, int y);
  
  /** \details
    Checks whether the dragging operation can be finished.
    
    \returns Returns true if the dragging operation can be finished; otherwise the method returns false.
  */
  bool canFinish() { return true; };

  /** \details
    Processes the Escape key press event.
    
    \returns Returns the result of the event processing.
  */
  eDraggerResult processEscape();

  //DOM-IGNORE-BEGIN
private:
  void updateFrame(bool bCreate);

private:
  bool m_bSuccess;

  // first clicked point (WCS)
  OdGePoint3d m_firstPt;

  // local state of the dragger
  bool m_bIsPressed;

  // last drag point (WCS)
  OdGePoint3d m_lastDragPt;

  // need to control the ::start called first time or not
  bool m_bJustCreatedObject;

  // temporary geometry
  OdTvEntityId m_entityId;
  OdTvGeometryDataId m_rectFoldEntityId;
  OdTvGeometryDataId m_rectEntityId;
  OdTvGeometryDataId m_frameId;

  // points for creating the polygon frame
  OdTvPointArray m_pts;

  // registered app name for user data
  OdTvRegAppId m_appTvId;

  OdUInt8 m_weight;
  OdTvColorDef m_color;
//DOM-IGNORE-END
};


/** \details
  The base interface class for circle markup dragging.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
class ODTVTOOLS_EXPORT OdTvCircleMarkupDragger : public OdTvDragger
{
public:

  ODRX_HEAP_OPERATORS();

  /** \details 
    Creates a new circle markup dragging object with specified parameters. 
    Returns the device identifier and the identifier of the model that contains dragging objects to a calling subroutine.
    
    \param tvDeviceId         [out] A placeholder for the device identifier that is returned to a calling subroutine. 
    \param tvDraggersModelId  [out] A placeholder for the identifier of the model that contains dragging objects to be returned to a calling subroutine. 
    \param appTvId            [in]  An identifier of the registered application associated with the circle markup dragging object.
    \param color              [in]  A color of the circle markup.
    \param weight             [in]  A weight of the circle markup.
  */
  OdTvCircleMarkupDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, const OdTvRegAppId& appTvId, OdTvColorDef color, OdUInt8 weight);
  
  /**\details 
    Destroys the circle markup dragging object.
  */
  ~OdTvCircleMarkupDragger();

  /** \details
    Starts the circle markup dragging operation.
    
    \param pPrevDragger   [in] A smart pointer to a previous dragging operation.
    \param pExtendedView  [in] A raw pointer to the associated extended view.
    \returns Returns the result of the dragging operation start.
    \remarks 
    The method should be called to prepare the dragging object for the operation.
  */
  eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
  
  /** \details
    The mouse button click event handler for the circle markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse button click event.
  */
  eDraggerResult nextpoint(int x, int y);
  
  /** \details
    The mouse move event handler for the circle markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse move event.
  */
  eDraggerResult drag(int x, int y);
  
  /** \details
    The mouse button release event handler for the circle markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse button click event.
 */
  eDraggerResult nextpointup(int x, int y);
  
  /** \details
    Checks whether the dragging operation can be finished.
    
    \returns Returns true if the dragging operation can be finished; otherwise the method returns false.
  */
  bool canFinish() { return true; };

//DOM-IGNORE-BEGIN
private:
  void updateFrame(bool bCreate);

private:
  bool m_bSuccess;
  // first clicked point (WCS)
  OdGePoint3d m_firstPt;

  // local state of the dragger
  bool m_bIsPressed;

  // last drag point (WCS)
  OdGePoint3d m_lastDragPt;

  // need to control the ::start called first time or not
  bool m_bJustCreatedObject;

  // temporary geometry
  OdTvEntityId m_entityId;
  OdTvGeometryDataId m_circFoldEntityId;
  OdTvGeometryDataId m_circEntityId;
  OdTvGeometryDataId m_frameId;

  // registered app name for user data
  OdTvRegAppId m_appTvId;

  OdUInt8 m_weight;
  OdTvColorDef m_color;
//DOM-IGNORE-END
};

/** \details
  The base interface class for handle markup dragging.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
class ODTVTOOLS_EXPORT OdTvHandleMarkupDragger : public OdTvDragger
{
public:

  ODRX_HEAP_OPERATORS();

  /** \details 
    Creates a new handle markup dragging object with specified parameters. 
    Returns the device identifier and the identifier of the model that contains dragging objects to a calling subroutine.
    
    \param tvDeviceId         [out] A placeholder for the device identifier that is returned to a calling subroutine. 
    \param tvDraggersModelId  [out] A placeholder for the identifier of the model that contains dragging objects to be returned to a calling subroutine. 
    \param appTvId            [in]  An identifier of the registered application associated with the handle markup dragging object.
    \param color              [in]  A color of the handle markup.
    \param weight             [in]  A weight of the handle markup.
  */
  OdTvHandleMarkupDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, const OdTvRegAppId& appTvId, OdTvColorDef color, OdUInt8 weight);
  
  /**\details 
    Destroys the handle markup dragging object.
  */
  ~OdTvHandleMarkupDragger();

  /** \details
    Starts the handle markup dragging operation.
    
    \param pPrevDragger   [in] A smart pointer to a previous dragging operation.
    \param pExtendedView  [in] A raw pointer to the associated extended view.
    \returns Returns the result of the dragging operation start.
    \remarks 
    The method should be called to prepare the dragging object for the operation.
  */
  eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
  
  /** \details
    The mouse button click event handler for the handle markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse button click event.
  */
  eDraggerResult nextpoint(int x, int y);
  
  /** \details
    The mouse move event handler for the handle markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse move event.
  */
  eDraggerResult drag(int x, int y);
  
  /** \details
    The mouse button release event handler for the handle markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse button click event.
 */
  eDraggerResult nextpointup(int x, int y);
  
  /** \details
    Checks whether the dragging operation can be finished.
    
    \returns Returns true if the dragging operation can be finished; otherwise the method returns false.
  */
  bool canFinish() { return true; };

//DOM-IGNORE-BEGIN
private:
  void updateFrame();

private:
  bool m_bSuccess;
  // first clicked point (WCS)
  OdGePoint3d m_firstPt;

  // local state of the dragger
  bool m_bIsPressed;

  // need to control the ::start called first time or not
  bool m_bJustCreatedObject;

  // temporary geometry
  OdTvEntityId m_entityId;
  OdTvGeometryDataId m_handFoldEntityId;
  OdTvGeometryDataId m_handEntityId;
  OdTvGeometryDataId m_frameId;

  OdTvPointArray m_points;

  // registered app name for user data
  OdTvRegAppId m_appTvId;

  OdUInt8 m_weight;
  OdTvColorDef m_color;
//DOM-IGNORE-END
};

/** \details
  The base interface class for cloud markup dragging.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
class ODTVTOOLS_EXPORT OdTvCloudMarkupDragger : public OdTvDragger
{
public:

  ODRX_HEAP_OPERATORS();

  /** \details 
    Creates a new cloud markup dragging object with specified parameters. 
    Returns the device identifier and the identifier of the model that contains dragging objects to a calling subroutine.
    
    \param tvDeviceId         [out] A placeholder for the device identifier that is returned to a calling subroutine. 
    \param tvDraggersModelId  [out] A placeholder for the identifier of the model that contains dragging objects to be returned to a calling subroutine. 
    \param appTvId            [in]  An identifier of the registered application associated with the cloud markup dragging object.
    \param color              [in]  A color of the cloud markup.
    \param weight             [in]  A weight of the cloud markup.
  */
  OdTvCloudMarkupDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, const OdTvRegAppId& appTvId, OdTvColorDef color, OdUInt8 weight);
  
  /**\details 
    Destroys the cloud markup dragging object.
  */
  ~OdTvCloudMarkupDragger();

  /** \details
    Starts the cloud markup dragging operation.
    
    \param pPrevDragger   [in] A smart pointer to a previous dragging operation.
    \param pExtendedView  [in] A raw pointer to the associated extended view.
    \returns Returns the result of the dragging operation start.
    \remarks 
    The method should be called to prepare the dragging object for the operation.
  */
  eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
  
  /** \details
    The mouse button click event handler for the cloud markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse button click event.
  */
  eDraggerResult nextpoint(int x, int y);
  
  /** \details
    The mouse move event handler for the cloud markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse move event.
  */
  eDraggerResult drag(int x, int y);
  
  /** \details
    Processes the Enter key press event.
    
    \returns Returns true if the dragging operation should be finished; otherwise the method returns false.
  */
  eDraggerResult processEnter();
  
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

//DOM-IGNORE-BEGIN
private:
  void updateFrame(bool bCreate);

  void calculateArcs(OdTvPoint& startPoint, OdTvPoint& firstMidPoint, OdTvPoint& midPoint, OdTvPoint& secondMidPoint, OdTvPoint& endPoint);
  void drawArcs(OdTvEntityPtr& pEntity);
  void updateArcs(OdTvGeometryDataId& firstArcId, OdTvGeometryDataId& secondArcId);
  void createFrame();

private:
  bool m_bSuccess;
  // first clicked point (WCS)
  OdGePoint3d m_penultPt;

  // last drag point (WCS)
  OdGePoint3d m_lastDragPt;

  // local state of the dragger
  bool m_bDraggerStarted;

  // need to control the ::start called first time or not
  bool m_bJustCreatedObject;

  // temporary geometry
  OdTvEntityId m_entityId;

  OdTvGeometryDataId m_cloudFoldEntityId;
  OdTvGeometryDataId m_tempEntityId; // Temp subentity for current arc
  OdTvGeometryDataId m_frameId;     // Subentity for arcs

  OdList<OdTvGeometryDataId> m_arcsIdList;

  // registered app name for user data
  OdTvRegAppId m_appTvId;

  OdUInt8 m_weight;
  OdTvColorDef m_color;
//DOM-IGNORE-END
};

/** \details
  The base interface class for flashing a text input caret for dragging objects.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
class OdTvTextCaret
{
public:

  ODRX_HEAP_OPERATORS();

  /** \details
    Creates a new text caret dragging object with specified text data.
    
    \param caretTextData [out] A placeholder for the identifier of the geometry data that represents the caret text. The identifier is returned to a calling subroutine.
  */
  OdTvTextCaret(OdTvGeometryDataId& caretTextData);

  /** \details
    Updates the text caret.
  */
  void updateCaret();

//DOM-IGNORE-BEGIN
private:
  // OdTvTextData for caret
  OdTvGeometryDataId m_caretTextData;

  // True if "|" is shown
  bool m_bCaretIsShown;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of smart pointers to an <link OdTvTextCaret, OdTvTextCaret> object.
*/
typedef OdSharedPtr<OdTvTextCaret> OdTvTextCaretPtr;

/** \details
  The base interface class for text markup dragging.
  \sa
  <link tv_tools_draggers, Work with Draggers>
*/
class ODTVTOOLS_EXPORT OdTvTextMarkupDragger : public OdTvDragger
{
public:

  ODRX_HEAP_OPERATORS();

  /** \details 
    Creates a new text markup dragging object with specified parameters. 
    Returns the device identifier and the identifier of the model that contains dragging objects to a calling subroutine.
    
    \param tvDeviceId         [out] A placeholder for the device identifier that is returned to a calling subroutine. 
    \param tvDraggersModelId  [out] A placeholder for the identifier of the model that contains dragging objects to be returned to a calling subroutine. 
    \param appTvId            [in]  An identifier of the registered application associated with the text markup dragging object.
    \param color              [in]  A color of the text markup.
    \param weight             [in]  A weight of the text markup.
  */
  OdTvTextMarkupDragger(OdTvGsDeviceId& tvDeviceId, OdTvModelId& tvDraggersModelId, const OdTvRegAppId& appTvId, OdTvColorDef color, OdUInt8 weight);
  
  /**\details 
    Destroys the text markup dragging object.
  */
  ~OdTvTextMarkupDragger();

  /** \details
    Starts the text markup dragging operation.
    
    \param pPrevDragger   [in] A smart pointer to a previous dragging operation.
    \param pExtendedView  [in] A raw pointer to the associated extended view.
    \returns Returns the result of the dragging operation start.
    \remarks 
    The method should be called to prepare the dragging object for the operation.
  */
  eDraggerResult start(OdTvDraggerPtr pPrevDragger, OdTvExtendedView* pExtendedView);
  
  /** \details
    The mouse button click event handler for the text markup dragging object.
    
    \param x [in] The X-axis device coordinate of the mouse position.
    \param y [in] The Y-axis device coordinate of the mouse position.
    \returns Returns the result of handling the mouse button click event.
  */
  eDraggerResult nextpoint(int x, int y);
  
  /** \details
    Finishes the dragging operation.
    
    \param rc [out] A placeholder for the result of the operation.
    \returns Returns a smart pointer to the previous dragging object.
    \remarks 
    The method should be called before exiting from the dragging operation.
  */
  OdTvDraggerPtr finish(eDraggerResult& rc);
  
  /** \details
    Processes the Enter key press event.
    
    \returns Returns true if the dragging operation should be finished; otherwise the method returns false.
  */
  eDraggerResult processEnter();
  
  /** \details
    Processes the Backspace key press event.
    
    \returns Returns the result of the event processing.
  */
  eDraggerResult processBackspace();
  
  /** \details
    Processes the text input event.
    
    \param text [in] A string that contains the input text.
    \returns Returns the result of the event processing.
  */
  eDraggerResult processText(const OdString& text);
  
  /** \details
    Checks whether the dragging operation can be finished.
    
    \returns Returns true if the dragging operation can be finished; otherwise the method returns false.
  */
  virtual bool canFinish();
  
  /** \details
    Retrieves the active row of the text markup dragging object. 
    
    \returns Returns the identifier of the geometry data that represents the active row.
  */
  virtual OdTvGeometryDataId getActiveRow();
  
  /** \details
    Modifies the geometry at each view update. 
    
    \sa
    For details, see the description of the <link OdTvDragger::drawInvalidate, drawInvalidate()> method of the 
    <link OdTvDragger, OdTvDragger> class.
  */
  virtual void drawInvalidate();

//DOM-IGNORE-BEGIN
private:
  void updateFrame(bool bCreate, const OdString& text = OD_T(""));
  void createFrame();
  OdTvGeometryDataId addText(OdTvGeometryDataId& geomId, const OdTvPoint& pos, const OdString& text);
  OdTvGeometryDataId getPrevRow();
  void moveFirstPoint(OdTvVector& dir);
  void updateCaretPos();

private:

  bool m_bSuccess;

  // first clicked point (WCS)
  OdGePoint3d m_firstPt;

  // local state of the dragger
  bool m_bIsPressed;

  // last drag point (WCS)
  OdGePoint3d m_lastDragPt;

  // need to control the ::start called first time or not
  bool m_bJustCreatedObject;

  // temporary geometry
  OdTvEntityId m_entityId;
  OdTvGeometryDataId m_textFoldEntityId;
  OdTvGeometryDataId m_frameId;

  OdTvGeometryDataId m_caretId; // Subentity for caret

  // pointer to flashing caret
  OdTvTextCaretPtr   m_pCaret;

  // text state
  bool m_bNeedStartTextInput;

  // registered app name for user data
  OdTvRegAppId m_appTvId;

  OdUInt8 m_weight;
  OdTvColorDef m_color;
//DOM-IGNORE-END
};

#endif //OD_TV_VIEWERMARKUPDRAGGERS_H
