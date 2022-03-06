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

#ifndef _PRCPARTDEFINITION_INCLUDED_
#define _PRCPARTDEFINITION_INCLUDED_ 
 

#include "PrcUserData.h"
#include "PrcView.h"
#include "PrcMarkups.h"
#include "PrcRepresentationItem.h"
#include "PrcBoundingBox.h"
#include "PrcBaseWithGraphics.h"
SMARTPTR(OdPrcPartDefinition);

  /** \details 
  <group PRC_Files_Structures_Assemblies> 

  Class representing a part definition. It consists of a bounding box and views with annotations or specific display parameters.
  */
class PRC_TOOLKIT OdPrcPartDefinition : public OdPrcBaseWithGraphics
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcPartDefinition);
  //DOM-IGNORE-END

  /** \details
  Returns current bounding box data.
  Bounding box data is returned as a reference to an OdPrcBoundingBox object, therefore it can be used to set new bounding box data.
  */
  OdPrcBoundingBox &boundingBox();

  /** \details
  Returns current bounding box data.
  */
  const OdPrcBoundingBox &boundingBox() const;

  /** \details
  Returns the current array of identifiers of visible representation items.
  The array of identifiers of visible representation items is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new items.
  */
  OdPrcObjectIdArray &representationItem();

  /** \details
  Returns the current array of identifiers of visible representation items.
  */
  const OdPrcObjectIdArray &representationItem() const;
  
  /** \details
  Returns current part definition markups.
  Markups are returned as a reference to an OdPrcMarkups object, therefore it can be used to set new markups.
  */
  OdPrcMarkups &markups();
   
  /** \details
  Returns current part definition markups.
  */
  const OdPrcMarkups &markups() const;
  
  /** \details
  Returns the current array of annotation view identifiers.
  The array of annotation view identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new identifiers.
  */
  OdPrcObjectIdArray &annotationView();
  
  /** \details
  Returns the current array of annotation view identifiers.
  */
  const OdPrcObjectIdArray &annotationView() const;
  
  /** \details
  Returns current user defined data. 
  User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData &userData();

  /** \details
  Returns current user defined data. 
  */
  const OdPrcUserData &userData() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
};

#endif // _PRCPARTDEFINITION_INCLUDED_

