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

#ifndef _ODTV_LAYERIMPL_H_INCLUDED_
#define _ODTV_LAYERIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdDbStub.h"

#include "TvLayer.h"
#include "TvInterfaceWrappers.h"
#include "TvTraitsDefImpl.h"
#include "TvUserDataImpl.h"

#include "DbLayerTableRecord.h"
#include "DbSymbolTable.h"

/** \details
This class is the internal implementation of the layer. Such implementation is need
because of special storing of the lineweight attribute and color
*/
class OdTvLayerImpl : public OdTvDbLayerTableRecord, public OdTvXDataStorage
{
  OdTvLayerImpl();

  virtual ~OdTvLayerImpl();
public:
  ODRX_DECLARE_MEMBERS(OdTvLayerImpl);

  /** \details
  Sets the values of this object's subentity traits, and returns with the calling
  object's subentity traits.

  \param pTraits [in] Pointer to the OdGiDrawableTraits object to be set.
  */
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;

  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Sets the color for this Insert
  */
  void setTvColor(const OdTvCmEntityColor& color);

  /** \details
  Returns the color of this Insert
  */
  const OdTvCmEntityColor& getTvColor() const;

  /** \details
  Sets the line weight for this Insert
  */
  void setLineweight(OdDb::LineWeight lineWeight);

  /** \details
  Returns the line weight of this Insert
  */
  OdDb::LineWeight getLineweight() const;

  /** \details
  Sets true if the layer should be ByBlock layer.
  */
  void setIsByBlock(bool bIsByBlock);

  /** \details
  Retrieves the ByBlock state of the layer.
  */
  bool getIsByBlock() const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

private:

  // color (where index 0 means NOT byBlock)
  OdTvCmEntityColor  m_tvColor;

  // lineweight (not as index - simply as int)
  OdDb::LineWeight    m_tvLineWeight;

  //means that the laye ris by block (the object with such layer will inherit the layer from the parent)
  //emulate .dwg zero level
  bool m_bIsByBlock;
};

typedef OdSmartPtr<OdTvLayerImpl> OdTvLayerImplPtr;


/** \details
This is an wrapper of the interface class for OdTvLayer object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvLayerWrapper : public OdTvLayer
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvLayer, OdTvLayerImpl)

  friend class OdTvEntityImpl;
  friend class OdTvGeometryDataImpl;
  friend class OdTvLayersIteratorImpl;
  friend class OdTvInsertWrapper;
  friend class OdTvInsertDataImpl;
  friend class OdTvDatabaseImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
    Sets the visible status as a Boolean value. The initial value is true (Visible) by
    default.

    \param bVisible [in]  True - to make the layer visible, or False - to make the layer invisible.
  */
  virtual OdTvResult setVisible(bool bVisible);

  /** \details
    Determines whether the layer is visible (negative is invisible, positive
    is visible) and returns True if the layer is visible or False if the layer is invisible.
  */
  virtual bool getVisible(OdTvResult* rc = NULL) const;

  /** \details
    Sets the name for the layer.

    \param sName [in]  Layer name as a String value up to 255 characters long.

    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
    Returns the name of the layer.
  */
  virtual OdString getName(OdTvResult* rc = NULL) const;

  /** \details
    Sets the color for the layer. This color is used when the
    Color property of an entity belonged to this layer is set to byLayer value.

    \param color    [in] Reference to the color instance to be set.

  */
  virtual OdTvResult setColor(const OdTvColorDef& color);

  /** \details
    Returns the color for the layer object. This color is used when
    the Color property of an entity belonged to the layer is set to byLayer value.

  */
  virtual OdTvColorDef getColor(OdTvResult* rc = NULL) const;

  /** \details
    Sets the lineweight for the layer. This lineweight is used when the
    Lineweight property of an entity belonged to this layer is set to ByLayer value.

    \param OdInt8  [in] Lineweight.
  */
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw);

  /** \details
    Returns the lineweight of the layer. This lineweight is used when
    the Lineweight property of an entity belonged to this layer is set to ByLayer value.

  */
  virtual OdTvLineWeightDef getLineWeight(OdTvResult* rc = NULL) const;

  /** \details
    Sets the ID of the linetype. This method associates layer and linetype. This linetype is used when
    the Linetype property of an entity belonged to this layer is set to ByLayer value.

    \param idLinetype [in]  Object ID of the linetype record object to associate it with the layer,
  */
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& linetypeDef);

  /** \details
    Returns the ID of the linetype associated with the layer. This linetype is
    used when the Linetype property of an entity belonged to this layer is set to ByLayer value.

  */
  virtual OdTvLinetypeDef getLinetype(OdTvResult* rc = NULL) const;

  /** \details
    Sets the description for the layer as a String value up to 255 letters length.
    The initial value is an empty string.

    \param sDescription [in]  Description as a String value.
  */
  virtual OdTvResult setDescription(const OdString& sDescription);

  /** \details
    Returns the description for the layer.
  */
  virtual OdString getDescription(OdTvResult* rc = NULL) const;

  /** \details
  Sets the transparency for the layer. This transparency is used when the
  Transparency property of an entity belonged to this layer is set to ByLayer value.

  \param OdTvTransparencyDef  [in] Transparency.
  */
  virtual OdTvResult setTransparency(const OdTvTransparencyDef& transparency);

  /** \details
  Returns the transparency of the layer. This transparency is used when
  the Transparency property of an entity belonged to this layer is set to ByLayer value.

  */
  virtual OdTvTransparencyDef getTransparency(OdTvResult* rc = NULL) const;

  /** \details
  Set the material of the layer

  \param OdTvMaterialDef  [in] Material.
  */
  virtual OdTvResult setMaterial(const OdTvMaterialDef& material);

  /** \details
  Get the material of the layer
  */
  virtual OdTvMaterialDef getMaterial(OdTvResult* rc = NULL) const;

  /** \details
  Sets true if the layer should be ByBlock layer.
  */
  virtual OdTvResult setIsByBlock(bool bIsByBlock);

  /** \details
  Retrieves the ByBlock state of the layer.
  */
  virtual bool getIsByBlock(OdTvResult* rc = NULL) const;

  /** \details
  Sets the visible status for the layer object.
  */
  virtual OdTvResult setTotallyInvisible(bool bTotallyInvisible);

  /** \details
  Retrieves whether the layer is totally invisible or not.
  */
  virtual bool getTotallyInvisible(OdTvResult* rc = NULL) const;

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Internal methods
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  OdTvDbObjectId getWrappedDbObjectId();

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};

/** \details
  This is an implementation of the iterator class for the layers
*/

class ODTV_EXPORT OdTvLayersIteratorImpl : public OdTvLayersIterator
{
  friend class OdTvDatabaseImpl;
public:

  /** \details
    Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done(OdTvResult* rc = NULL) const;

  /** \details
    Steps this Iterator object.
  */
  virtual OdTvResult step();

  /** \details
    Returns the layer currently referenced by this Iterator object.
  */
  virtual OdTvLayerId getLayer(OdTvResult* rc = NULL) const;

  /** \details
    Positions this Iterator object at the specified layer.
    \param objectId [in]  Layer ID.
  */
  virtual OdTvResult seek(const OdTvLayerId& LayerId);

  /** \details
    Methods for creating the object
  */
  static OdTvLayersIteratorPtr createObject(OdTvDbSymbolTableIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvLayersIteratorImpl();
  OdTvLayersIteratorImpl(OdTvDbSymbolTableIterator* pDbIterator);

  virtual ~OdTvLayersIteratorImpl();
  // Db iterator
  OdTvDbSymbolTableIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;

};

#include "TD_PackPop.h"

#endif //_ODTV_LAYERIMPL_H_INCLUDED_
