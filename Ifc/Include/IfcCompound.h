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

#ifndef _IFC_COMPOUND_H_
#define _IFC_COMPOUND_H_

#include "IfcBuildOptions.h"
#include "IfcEntityTypes.h"
#include "IfcFile.h"
#include "IfcEntity.h"

/** \details 
Contains declarations related to working with IFC files content.
*/
namespace OdIfc {

/** \details 
A class that implements working with an IFC compound object.
*/
class IFCCORE_EXPORT OdIfcCompound : public OdGiDrawable
{
//DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdIfcCompound);

protected:

  OdIfcEntity*  m_pEntInst;
//DOM-IGNORE-END

public:

  /**\details 
  Composes the compound object into a specified model.
  \remarks 
  The pointer to a model is deprecated and can be removed from the method signature in future releases.
  */
  virtual void compose();

  /**\details 
  Retrieves the current type of the compound object.
  \returns Returns an <link OdIfc::OdIfcEntityType, OdIfcEntityType> enumeration value that represents the current compound object type.
  */
  OdIfcEntityType type();
  
  /** \details
  Retrieves the current value of an attribute specified by its definition.
  \param attrDef [in] A value of the <link OdIfc::OdIfcAttribute, OdIfcAttribute> enumeration that represents the attribute definition.
  \returns Returns the current value of the attribute.
  \remarks 
  The method provides late binding access to the attribute value by its definition. 
  Attributes of select and aggregate data types are also supported.
  */
  OdRxValue getAttr(const OdIfcAttribute attrDef) const { return m_pEntInst->getAttr(attrDef); }
  
  /** \details
  Retrieves the current value of an attribute specified by its name.
  \param attrName [in] An ANSI string that contains the attribute name.
  \returns Returns the current value of the attribute.
  \remarks 
  The method provides late binding access to the attribute value by its name. 
  Attributes of select and aggregate data types are also supported.
  */
  virtual OdRxValue getAttr(const OdAnsiString &attrName) const { return m_pEntInst->getAttr(attrName); }

  /** \details
  Retrieves the model that currently owns the compound object.
  \returns Returns a raw pointer to the <link OdIfc::OdIfcModel, OdIfcModel> object representing the model that owns the entity.
  */
  OdIfcModel* owningModel() const;
  
  /**  \details
  Retrieves whether the compound object belongs to a specified entity type.
  \param entityName [in] An entity type name.
  \returns Returns true if the compound object belongs to the specified type; otherwise, the method returns false.
  */
  bool isKindOf(OdIfcEntityType type) const { return m_pEntInst->isKindOf(type); };
  
  /** \details
  Retrieves whether the compound object is an instance of a specified type.
  \param entityType [in] An instance of the <link OdIfc::OdIfcEntityType, OdIfcEntityType> enumeration that represents the entity type.
  \returns Returns true if the compound object is an instance of the specified type; otherwise, the method returns false.
  */
  bool isInstanceOf(OdIfcEntityType entityType) const { return m_pEntInst->isInstanceOf(entityType); };
  
  /** \details
  Retrieves the name of the current compound object's type.
  \returns Returns an ANSI string value that contains the current compound object's type name.
  */
  const OdAnsiString& typeName() { return m_pEntInst->typeName(); };
  
  /** \details 
  Retrieves the compound object's underlying IFC entity instance.
  \param pInst [in] A raw pointer to the compound object.
  \returns Returns a smart pointer to the compound object.
  */
  static OdIfcEntityPtr earlyAccess(OdIfcCompound* pInst) { return pInst->m_pEntInst; };

  OdIfcFile* owningIfcFile() const;

  //
  // OdGiDrawable void implementation
  //

  /** \details
  Retrieves whether the compound object is a persistent one.
  \returns Returns true if the compound object is a persistent one; otherwise, the method returns false.
  \remarks 
  Persistent objects are database-resident objects (i.e., they are stored in a database).
  */
  virtual bool isPersistent() const { return id() != NULL; };

  /** \details
  Retrieves the identifier of the compound object's database.
  \returns Returns a raw pointer to a stub object that provides access to the database.
  \remarks 
  The method returns a NULL pointer if the compound object is not a persistent one.
  */
  virtual OdDbStub* id() const { return m_pEntInst->m_id; };

  /** \details 
  Sets a new Gs node cache for the compound object.
  \param pGsNode [in] A raw pointer to an <exref target="https://docs.opendesign.com/tv/OdGsCache.html">OdGsCache</exref> object.
  */
  virtual void setGsNode(OdGsCache* pGsNode);

  /** \details
  Retrieves the current Gs node object of the compound object.
  \returns Returns a raw pointer to the <exref target="https://docs.opendesign.com/tv/OdGsCache.html">OdGsCache</exref> object associated with the compound object.
  */
  virtual OdGsCache* gsNode() const;

  /** \details 
  Sets the values of the compound object's sub-entity traits. 
  \param traits [out] A raw pointer to the traits to be filled and returned to a calling subroutine.
  \returns Returns the result of setting the values.
  */
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits * traits) const;

  /** \details 
  Draws a graphical compound object representation that is independent of any viewport contexts. 
  \param wd [in] A raw pointer to the object that encapsulates parameters of viewport-independent vectorization.
  \returns Returns true if drawing was successful; otherwise, the method returns false.
  */
  virtual bool subWorldDraw(OdGiWorldDraw * wd) const;

  /** \details 
  Draws a graphical compound object that is dependent on the viewport context.
  \param vd [in] A raw pointer to the object that encapsulates parameters of viewport-dependent vectorization.
  */
  virtual void subViewportDraw(OdGiViewportDraw * vd) const;

//DOM-IGNORE-BEGIN
private:

  void setInst(OdIfcEntity *pEnt) { m_pEntInst = pEnt; }

  friend class ::OdIfcEntResolver;
//DOM-IGNORE-END
};

/** \details 
A data type that represents a smart pointer to an <link OdIfc::OdIfcCompound, OdIfcCompound> object.
*/
typedef OdSmartPtr<OdIfcCompound> OdIfcCompoundPtr;

}

#endif // _IFC_COMPOUND_H_
