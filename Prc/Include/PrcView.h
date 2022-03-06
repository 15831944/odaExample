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

#ifndef _PRCVIEW_INCLUDED_
#define _PRCVIEW_INCLUDED_ 


#include "PrcObjectId.h"
#include "PrcUserData.h"
#include "PrcSceneDisplayParameters.h"
#include "PrcPlane.h"
#include "PrcBaseWithGraphics.h"

SMARTPTR(OdPrcView);

/** \details
<group PRC_Graphic_Classes>

Class representing a view that is associated with planes. It also can define an entity's visibilities and an entity's positions.
*/
class PRC_TOOLKIT OdPrcView : public OdPrcBaseWithGraphics
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcView)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of display filters.
  The array of display filters is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new display filters.
  */
  OdPrcObjectIdArray &displayFilters();

  /** \details
  Returns the current array of display filters.
  */
  const OdPrcObjectIdArray &displayFilters() const;

  /** \details
  Returns the current canonical definition of the planar surface.
  The plane definition is returned as a reference to an OdPrcPlanePtr object, therefore it can be used to change the planar surface definition.
  */
  OdPrcPlanePtr &plane();

  /** \details
  Returns the current canonical definition of the planar surface.
  */
  const OdPrcPlanePtr &plane() const;

  /** \details
  Returns current scene display parameters.
  Scene display parameters are returned as a reference to OdPrcObjectId object, therefore it can be used to set new parameters.
  */
  OdPrcObjectId &sceneDisplayParameters();

  /** \details
  Returns current scene display parameters.
  */
  const OdPrcObjectId &sceneDisplayParameters() const;

  /** \details
  Returns the current array of linked item identifiers.
  The array of linked item identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new linked items array.
  */
  OdPrcObjectIdArray &linkedItems();

  /** \details
  Returns the current array of linked item identifiers.
  */
  const OdPrcObjectIdArray &linkedItems() const;

  /** \details
  Returns the current array of annotation entity identifiers.
  The array of annotation entity identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new annotation entities array.
  */
  OdPrcObjectIdArray &annotations();

  /** \details
  Returns the current array of annotation entity identifiers.
  */
  const OdPrcObjectIdArray &annotations() const;

  /** \details
  Returns current user defined data.
  User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData &userData();

  /** \details
  Returns current user defined data.
  */
  const OdPrcUserData &userData() const;

  /** \details
  Sets a new value of the annotation view flag.
  The annotation view flag indicates whether the view is an annotation view (if true) or not (if false).

  \param isAnnotationView [in] A new value of the flag to be set.
  */
  void setIsAnnotationView(bool isAnnotationView);

  /** \details
  Returns the current value of the annotation view flag.
  The annotation view flag indicates whether the view is an annotation view (if true) or not (if false).
  */
  bool isAnnotationView() const;

  /** \details
  Sets a new value of the default view flag.
  The default view flag indicates whether the view is the default view (if true) or not (if false).

  \param isDefaultView [in] A new value of the flag.
  */
  void setIsDefaultView(bool isDefaultView);

  /** \details
  Returns the current value of the default view flag.
  The default view flag indicates whether the view is the default view (if true) or not (if false).
  */
  bool isDefaultView() const;

  /** \details
  Sets a new value of the dummy plane flag.
  The dummy plane flag indicates whether the plane specifies only direction (if true).

  \param isDummyPlane [in] A new value of the flag.
  */
  void setIsDummyPlane(bool isDummyPlane);

  /** \details
  Returns the current value of the dummy plane flag.
  The dummy plane flag indicates whether the plane specifies only direction (if true).
  */
  bool isDummyPlane() const;

protected:
  virtual bool subWorldDraw(OdGiWorldDraw * pWd) const;
};

#endif // _PRCVIEW_INCLUDED_

