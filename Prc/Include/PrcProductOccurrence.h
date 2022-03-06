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

#ifndef _PRCPRODUCTOCCURRENCE_INCLUDED_
#define _PRCPRODUCTOCCURRENCE_INCLUDED_ 

#include "PrcUserData.h"
#include "PrcSceneDisplayParameters.h"
#include "PrcFilter.h"
#include "PrcView.h"
#include "PrcMarkups.h"
#include "PrcReference.h"
#include "PrcTransformation3d.h"
#include "PrcProductInformation.h"
#include "PrcReferencesOfProductOccurrence.h"
#include "PrcBaseWithGraphics.h"
#include "OdStack.h"
#include "PrcPartDefinition.h"

SMARTPTR(OdPrcProductOccurrence);

/** \details 
<group PRC_Files_Structures_Assemblies> 

Class representing an assembly tree. 
  */
class PRC_TOOLKIT OdPrcProductOccurrence : public OdPrcBaseWithGraphics
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcProductOccurrence);
  //DOM-IGNORE-END

  /** \details 
  Destroys the assembly tree object.
  */
  virtual ~OdPrcProductOccurrence();

  /** \details
  Sets a new location which moves entities in the product occurrence to its parent space.

  \param location [in] A pointer to a new transformation object between the product occurrence and its parent.
  
  \returns Returns eOk if a new location was successfully applied or an appropriate error code in the other case.
  */
  OdResult setLocation(const OdPrcTransformation3d * location);

  /** \details
  Returns the current location of the product occurrence.
  */
  const OdPrcTransformation3d *location() const;

   /** \details
  Returns current references of the product occurrence.
  References are returned as a reference to an OdPrcReferencesOfProductOccurrence object, therefore it can be used to set new references.
  */
  OdPrcReferencesOfProductOccurrence &referencesOfProductOccurrence();

  /** \details
  Returns current references of the product occurrence.
  */
  const OdPrcReferencesOfProductOccurrence &referencesOfProductOccurrence() const;

  /** \details
  Returns the current product information of the product occurrence.
  The product information is returned as a reference to an OdPrcProductInformation object, therefore it can be used to change the product information.
  */
  OdPrcProductInformation &productInformation();

  /** \details
  Returns the current product information of the product occurrence.
  */
  const OdPrcProductInformation &productInformation() const;

  /** \details
  Returns the current array of referenced entity identifiers. These entities may have modifiers towards their nominal definition.
  The array of referenced entity identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to modify the list of referenced entity identifiers.
  */
  OdPrcObjectIdArray &entityReference();

  /** \details
  Returns the current array of referenced entity identifiers. These entities may have modifiers towards their nominal definition.
  */
  const OdPrcObjectIdArray &entityReference() const;

  /** \details
  Returns current product occurrence markups.
  Product occurrence markups are returned as a reference to an OdPrcMarkups object, therefore it can be used to set new markups and modify existing ones.
  */
  OdPrcMarkups &markups();

  /** \details
  Returns current product occurrence markups.
  */
  const OdPrcMarkups &markups() const;

  /** \details
  Returns the current array of annotation view identifiers.
  The array of annotation view identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new identifiers or modify existing ones.
  */
  OdPrcObjectIdArray &annotationViews();

  /** \details
  Returns the current array of annotation view identifiers.
  */
  const OdPrcObjectIdArray &annotationViews() const;

  /** \details
  Returns the current array of display filter identifiers.
  The array of display filter identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new identifiers or modify existing ones.
  */
  OdPrcObjectIdArray &displayFilter();

  /** \details
  Returns the current array of display filter identifiers.
  */
  const OdPrcObjectIdArray &displayFilter() const;
  
  /** \details
  Returns the current array of specific filter identifiers. 
  Specific filters are applied when data is being loaded from a product prototype.
  The array of specific filter identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new identifiers or modify existing ones.
  */
  OdPrcObjectIdArray &entityFilter();

  /** \details
  Returns the current array of specific filter identifiers. 
  */
  const OdPrcObjectIdArray &entityFilter() const;

  /** \details
  Returns the current array of scene display parameter identifiers. 
  The array of scene display parameter identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new parameters or modify existing ones.
  */
  OdPrcObjectIdArray &sceneDisplayParameters();

  /** \details
  Returns the current array of scene display parameter identifiers. 
  */
  const OdPrcObjectIdArray &sceneDisplayParameters() const;

  /** \details
  Returns current user defined data.
  Current user defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData &userData();

  /** \details
  Returns current user defined data.
  */
  const OdPrcUserData &userData() const;

  /** \details
  Sets a new product behavior value. 
  The behavior value contains different flags for the product occurrence.

  \param product_behaviour [in] A new behavior value to be set.
  */
  void setProductBehaviour(OdInt8 product_behaviour);

  /** \details
  Returns the current product occurrence behavior value.
  */
  OdInt8 productBehaviour() const;

  /** \details 
  Returns the current external data of the product assembly tree.
  */
  const OdPrcProductOccurrence* getExternalData() const;

  /** \details 
  Returns the current part definition for the product assembly tree.
  */
  const OdPrcPartDefinition* getPartDefinition() const;

  /** \details 
  Returns the current location of the product assembly tree represented by a 3D transformation object.
  */
  const OdPrcTransformation3d* getLocation() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool     subWorldDraw (OdGiWorldDraw * pWd) const;
};

#endif // _PRCPRODUCTOCCURRENCE_INCLUDED_

