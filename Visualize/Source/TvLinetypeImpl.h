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

#ifndef _ODTV_LINETYPEIMPL_H_INCLUDED_
#define _ODTV_LINETYPEIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdDbStub.h"

#include "TvLinetype.h"
#include "TvInterfaceWrappers.h"
#include "TvUserDataImpl.h"

#include "DbLinetypeTableRecord.h"
#include "DbSymbolTable.h"

/** \details
This class is the internal implementation of the linetype. Such implementation is need
because of need to calculate the number of created objects
*/
class OdTvLinetypeImpl : public OdTvDbLinetypeTableRecord, public OdTvXDataStorage
{
  OdTvLinetypeImpl();

  virtual ~OdTvLinetypeImpl();
public:

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;

  virtual OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

  void setScale(double scale);

  double getScale() const;

  ODRX_DECLARE_MEMBERS(OdTvLinetypeImpl);

private:
  double m_scale;
};

typedef OdSmartPtr<OdTvLinetypeImpl> OdTvLinetypeImplPtr;

/** \details
This is an wrapper of the interface class for OdTvLinetype object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvLinetypeWrapper : public OdTvLinetype
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvLinetype, OdTvLinetypeImpl)

  friend class OdTvEntityImpl;
  friend class OdTvGeometryDataImpl;
  friend class OdTvLinetypesIteratorImpl;
  friend class OdTvInsertWrapper;
  friend class OdTvInsertDataImpl;
  friend class OdTvDatabaseImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Sets the line type elements for this line type
  */
  virtual OdTvResult setElements(const OdTvLinetypeElementArray& elements);

  /** \details
  Sets the line type elements for this line type

  \param nElements[in]  Number of the elements of the following array.
  \param elements [in]  Array of the pointers to the line type elements.
  */
  virtual OdTvResult setElements(OdInt32 nElements, const OdTvLinetypeElementPtr* elements);

  /** \details
  Returns the line type elements array for this line type
  */
  virtual OdTvResult getElements(OdTvLinetypeElementArray& elements) const;

  /** \details
  Sets the name for the linetype object.

  \param sName [in]  Linetype name as a String value up to 255 characters long.

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Returns the name of the line type object.
  */
  virtual OdString getName(OdTvResult* rc = NULL) const;

  /** \details
  Sets the description for the linetype record object. It can be a comment or series of underscores,
  dots, dashes, and spaces to show a representation
  of the linetype. The initial value is an empty string by default.

  \param sComment [in]  Comment as an arbitrary string.
  */
  virtual OdTvResult setDescription(const OdString& sDescr);

  /** \details
  Returns the description of the linetype. It is a comment or series
  of underscores, dots, dashes, and spaces to show a representation of the linetype.
  */
  virtual OdString getDescription(OdTvResult* rc = NULL) const;

  /** \details
  Sets the alignment scaling to fit for the linetype.
  */
  virtual OdTvResult setScaledToFit(bool bScaleToFit);

  /** \details
  Determines whether or not the alignment is scaled to fit and returns True if the
  alignment is scaled to fit or False if the alignment is not scaled to fit.
  */
  virtual bool getScaledToFit(OdTvResult* rc = NULL) const;

  /** \details
  Sets a scale for the linetype object. This scale will be applied to all elements in this linetype.
  */
  virtual OdTvResult setScale(double scale);

  /** \details
  Retrieves the scale of this linetype.
  */
  virtual double getScale(OdTvResult* rc = NULL) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Internal methods
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  OdTvDbObjectId getWrappedDbObjectId();

  static OdTvResult fillLineType(OdTvDbLinetypeTableRecordPtr pLinetype, OdInt32 nElements, const OdTvLinetypeElementPtr* elements);

  static void fillPredefinedLineType(OdTvDbLinetypeTableRecordPtr pLinetype, OdTvLinetype::Predefined lt);

  static OdTvResult getLineTypeElements(OdTvDbLinetypeTableRecordPtr pLinetype, OdTvLinetypeElementArray& elements);

  static OdTvDbObjectId getPredefinedLinetypeDb(OdTvDbDatabase* pDbDatabase, OdTvLinetype::Predefined lt);

  static OdString getPredefinedLinetypeName(OdTvLinetype::Predefined lt);
};



/** \details
    This is an implementation of the iterator class for the linetypes
*/
class ODTV_EXPORT OdTvLinetypesIteratorImpl : public OdTvLinetypesIterator
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
  Returns the linetype currently referenced by this Iterator object.
  */
  virtual OdTvLinetypeId getLinetype(OdTvResult* rc = NULL) const;

  /** \details
    Positions this Iterator object at the specified linetype.
    \param objectId [in]  Lietype ID.
  */
  virtual OdTvResult seek(const OdTvLinetypeId& LinetypeId);

  /** \details
    Methods for creating the object
  */
  static OdTvLinetypesIteratorPtr createObject(OdTvDbSymbolTableIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvLinetypesIteratorImpl();
  OdTvLinetypesIteratorImpl(OdTvDbSymbolTableIterator* pDbIterator);

  virtual ~OdTvLinetypesIteratorImpl();
  // Db iterator
  OdTvDbSymbolTableIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;
};

#include "TD_PackPop.h"

#endif //_ODTV_LINETYPEIMPL_H_INCLUDED_
