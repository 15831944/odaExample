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

#ifndef _PRCBREPDATA_INCLUDED_
#define _PRCBREPDATA_INCLUDED_ 
 

#include "PrcBody.h"
#include "PrcContentBody.h"
#include "PrcConnex.h"
#include "PrcBoundingBox.h"
#include "Br/BrBrep.h"

/** \details
    <group PRC_Representation_Item_Classes>
    
    Class stores boundary representation data.
*/
class PRC_TOOLKIT OdPrcBrepData : public OdPrcBody
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_BODY(OdPrcBrepData)
  //DOM-IGNORE-END
    
  /** \details
  Returns current bounding box data. 
  Bounding box data is returned as a reference to an OdPrcBoundingBox object, therefore it can be used to set new data.
  */
  OdPrcBoundingBox &boundingBox();

  /** \details
  Returns current bounding box data.
  */
  const OdPrcBoundingBox &boundingBox() const;
  
  /** \details
  Adds a specified connex to the connex array. 
  \param pConnex [in] A new connex object to add.
  */  
  void addConnex(const OdPrcConnexPtr &pConnex);

  /** \details
  Sets a new connex array. 
  \param arrConnexs [in] A new connex array to be set.
  */
  void setConnexs(const OdPrcConnexPtrArray &arrConnexs);
  
  /** \details
  Returns the current array of connex entities. 
  */
  const OdPrcConnexPtrArray &connex() const;
  
  /** \details
  Returns current data of the base topological entity.
  Base topological data is returned as a reference to an OdPrcContentBody object, therefore it can be used to set new data.
  */
  OdPrcContentBody &contentBody();
  
  /** \details
  Returns data of the base topological entity.
  */
  const OdPrcContentBody &contentBody() const;

  /** \details
  Returns the current serial type of the body.
  */
  virtual OdUInt32 getSerialType() const;

  /** \details
  Recalculates the neighboring coEdges for all coEdges in the body.
  */
  void updateCoedgeNeighbours (void);

  /** \details 
  Returns B-Rep data as an OdBrBrep object. 
  \param brep [in] A placeholder for the OdBrBrep object to be returned to a calling subroutine.
  \remarks 
  The method accepts an instance of the OdBrBrep object, fills it with data and returns to a calling subroutine.
  */
  void brep(OdBrBrep& brep);

//DOM-IGNORE-BEGIN
protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
};
//DOM-IGNORE-END
SMARTPTR(OdPrcBrepData);

#endif // _PRCBREPDATA_INCLUDED_

