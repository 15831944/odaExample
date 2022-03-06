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

#ifndef _PRCCONTENTPRCBASE_INCLUDED_
#define _PRCCONTENTPRCBASE_INCLUDED_ 
 

#include "OdaCommon.h"
#include "PrcAttributeData.h"
#include "PrcName.h"
#include "PrcObjectId.h"
#include "Gi/GiDrawable.h"

SMARTPTR(OdPrcBase)
class OdPrcBaseImpl;
class OdPrcProductOccurrence;

/** \details 
<group PRC_Base_Classes>

Base class for representing PRC entities.
*/
class PRC_TOOLKIT OdPrcBase : public OdGiDrawable
{
protected:
  OdPrcBase(OdPrcBaseImpl *pImpl);

protected:
  void writeInternal(OdPrcCompressedFiler *pStream);
  void readInternal(OdPrcCompressedFiler *pStream);

public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_BASE_NOTYPE(OdPrcBase)
  //DOM-IGNORE-END

  /** \details
  Returns the type of the PRC entity. */
  virtual OdUInt32 prcType() const;

  /** \details
  Returns the current name of the PRC entity.
  The name is represented as a reference to an OdPrcName object, therefore it can be used to set a new entity name.
  */
  OdPrcName &name();

  /** \details
  Returns the current name of the PRC entity.*/  
  const OdPrcName &name() const;

  /** \details
  Returns the current attribute information of the PRC entity.
  The attribute information is represented as a reference to an OdPrcAttributeData object, therefore it can be used to set new attribute information.
  */
  OdPrcAttributeData &attributeData();
  
  /** \details
  Returns the current attribute information of the PRC entity.*/
  const OdPrcAttributeData &attributeData() const;

  /** \details
  Destroys an instance of a PRC entity.*/
  virtual ~OdPrcBase();

public:
  /** \details
  Returns whether the PRC entity is persistent (true) or not (false).*/
  virtual bool isPersistent() const;

  /** \details
  Returns the PRC entity ID.*/
  virtual OdDbStub* id() const;

  /** \details
    Assigns the specified OdGsCache to the PRC entity.
    
    \param pGsNode [in]  A pointer to an OdGsCache object to be assigned.
  */
  virtual void setGsNode(OdGsCache* pGsNode);

  /** \details
  Returns the OdGsCache object currently assigned to the PRC entity.*/
  virtual OdGsCache* gsNode() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * wd) const;
  virtual void subViewportDraw (OdGiViewportDraw * vd) const;
};

SMARTPTR(OdPrcReferencedBase)
/** \details 
  <group PRC_Base_Classes>
  Base class for a referenced PRC entity.
*/
class PRC_TOOLKIT OdPrcReferencedBase : public OdPrcBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_NOTYPE_PRCBASE(OdPrcReferencedBase)
  //DOM-IGNORE-END

  /** \details
  Sets a new persistent CAD identifier value for the PRC object.
  \param CAD_persistent_identifier [in] A new value of persistent ID to be set.*/
  void setCADPersistentIdentifier(OdUInt32 CAD_persistent_identifier);
  
  /** \details
  Returns the current persistent CAD identifier for the PRC object.*/
  OdUInt32 cadPersistentIdentifier() const;
  
  /** \details
  Sets a new CAD identifier value for the PRC object.
  \param CAD_identifier [in] A new value of CAD identifier to be set.*/
  void setCADIdentifier(OdUInt32 CAD_identifier);
  
    /** \details
  Returns the current CAD identifier for the PRC object.*/
  OdUInt32 cadIdentifier() const;
  
  /** \details
  Returns the PRC object identifier. 
  */
  const OdPrcObjectId& objectId() const;
  
  /** \details 
  Sets a new PRC object identifier. 
  \param stub [in] A pointer to a stub used to create a new PRC object ID.
  */
  void setObjectId (OdDbStub* stub);

  /** \details 
  Returns the current object identifier for the object.
  */
  OdDbStub* id() const;

  /** \details 
  Returns true if the object is persistent or false in the other case.
  */
  bool isPersistent() const;

  /** \details 
  Returns an explicit unique name for "this" entity that can be referenced through PDF or JavaScript. In the case of error, it returns an empty string.

  \param pPrcPO [in] Represents product occurrence assembling the entity. It must be NULL if "this" entity is product occurrence (PRC_TYPE_ASM_ProductOccurence type).
  It should not be NULL if "this" entity is not a product occurrence.
  */
  OdString calculateUniqueName(const OdPrcProductOccurrence *pPrcPO) const;
};

#endif // _PRCCONTENTPRCBASE_INCLUDED_

