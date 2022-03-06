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

#ifndef _ODTV_HIGHLIGHSTYLEIMPL_H_INCLUDED_
#define _ODTV_HIGHLIGHSTYLEIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdDbStub.h"
#include "DbDictionary.h"

#include "TvHighlightStyle.h"
#include "TvInterfaceWrappers.h"
#include "TvUserDataImpl.h"
#include "GiSelectionStyle.h"

class OdGiSelectionStyle;

/** \details
This class represents an implementation of the highlight style
*/
class OdTvHighlightStyleImpl : public OdGiSelectionStyle, public OdTvDbObject, public OdTvXDataStorage
{
protected:
  OdTvHighlightStyleImpl();

public:

  ODRX_DECLARE_MEMBERS(OdTvHighlightStyleImpl);

  virtual ~OdTvHighlightStyleImpl();

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
  Mark that this is highlight style as predefined
  */
  OdTvResult setPredefined(bool bValue);

  /** \details
  Retrieves whether the current highlight style is predefined.
  */
  bool isPredefined(OdTvResult *rc = NULL) const;

  /** \details
  Sets the name of this highlight Style object

  \param name [in]  Name.

  \returns
  Returns tvOk if successful, or an internal error if failed
  */
  OdTvResult setName(const OdString& sName);

  /** \details
  Gets the name of this highlight style object in the case if the highlight style is default
  */
  const OdString getName(OdTvResult* rc = NULL) const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

  /** \details
  Copy options from the given highlight style

  \param pSource [in]  Pointer to the source object
  */
  virtual void copyFrom(const OdRxObject* pSource);

  OdTvResult setFacesColor(OdUInt32 entries, const OdTvRGBColorDef& color);
  OdTvRGBColorDef getFacesColor(OdTvHighlightStyle::Entry entry, OdTvResult* rc /*= NULL*/) const;
  OdTvResult setFacesTransparency(OdUInt32 entries, OdUInt8 transparency);
  OdUInt8 getFacesTransparency(OdTvHighlightStyle::Entry entry, OdTvResult* rc /*= NULL*/) const;
  OdTvResult setFacesVisibility(OdUInt32 entries, bool bVisible);
  bool getFacesVisibility(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  OdTvResult setFacesStipple(OdUInt32 entries, bool bStipple);
  bool getFacesStipple(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  OdTvResult setFacesParamToDefault(OdUInt32 entries);

  OdTvResult setEdgesColor(OdUInt32 entries, const OdTvRGBColorDef& color);
  OdTvRGBColorDef getEdgesColor(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  OdTvResult setEdgesTransparency(OdUInt32 entries, OdUInt8 transparency);
  OdUInt8 getEdgesTransparency(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  OdTvResult setEdgesVisibility(OdUInt32 entries, bool bVisible);
  bool getEdgesVisibility(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  OdTvResult setEdgesStipple(OdUInt32 entries, bool bStipple);
  bool getEdgesStipple(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  OdTvResult setEdgesLineweight(OdUInt32 entries, OdUInt8 lineweight);
  OdUInt8 getEdgesLineweight(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  OdTvResult setEdgesDrawMode(OdUInt32 entries, OdTvHighlightStyle::EdgesDrawMode mode);
  OdTvHighlightStyle::EdgesDrawMode getEdgeDrawMode(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  OdTvResult setEdgesParamToDefault(OdUInt32 entries);

  OdTvResult setOnTopOfDepth(bool bSet);
  bool getOnTopOfDepth(OdTvResult* rc = NULL) const;

  OdTvResult setByDefault(bool bUseFromPredefined);

private:
  OdGiSelectionStyle::StyleEntry& getStyleEntry(OdTvHighlightStyle::Entry entry) const;

private:

  OdString   m_strName;         // this string represent the real name of the highlight style for the default styles
  bool       m_bIsPredefined;      // true if this highlight style is default

};
typedef OdSmartPtr<OdTvHighlightStyleImpl> OdTvHighlightStyleImplPtr;

/** \details
This is an wrapper of the interface class for OdTvHighlightStyle object.

\remarks
The purpose of this class is to connect the internal highlight style object with an interface object
*/
class OdTvHighlightStyleWrapper : public OdTvHighlightStyle
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvHighlightStyle, OdTvHighlightStyleImpl)

  friend class OdTvDatabaseImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Interface implementation
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Sets the name for the highlight style

  \param sName [in]  Reference to a string that contains the name for this highlight style to set.
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Returns the name for the highlight style as a string.
  */
  virtual const OdString getName(OdTvResult* rc = NULL) const;

  /** \details
  Determines whether the highlight style is default or not. The default highlight styles can not be deleted

  \returns
  true - if the highlight style is default.
  false - otherwise.

  \remarks
  The default highlight styles can not be deleted, renamed or changed the description
  */
  virtual bool isPredefined(OdTvResult* rc = NULL) const;

  /** \details
  Copies options from a specified highlight style object.
  */
  virtual OdTvResult copyFrom(const OdTvHighlightStyleId& highlightStyleId);

  virtual OdTvResult setFacesColor(OdUInt32 entries, const OdTvRGBColorDef& color);
  virtual OdTvRGBColorDef getFacesColor(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  virtual OdTvResult setFacesTransparency(OdUInt32 entries, OdUInt8 transparency);
  virtual OdUInt8 getFacesTransparency(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  virtual OdTvResult setFacesVisibility(OdUInt32 entries, bool bVisible);
  virtual bool getFacesVisibility(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  virtual OdTvResult setFacesStipple(OdUInt32 entries, bool bStipple);
  virtual bool getFacesStipple(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  virtual OdTvResult setFacesParamToDefault(OdUInt32 entries);

  virtual OdTvResult setEdgesColor(OdUInt32 entries, const OdTvRGBColorDef& color);
  virtual OdTvRGBColorDef getEdgesColor(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  virtual OdTvResult setEdgesTransparency(OdUInt32 entries, OdUInt8 transparency);
  virtual OdUInt8 getEdgesTransparency(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  virtual OdTvResult setEdgesVisibility(OdUInt32 entries, bool bVisible);
  virtual bool getEdgesVisibility(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  virtual OdTvResult setEdgesStipple(OdUInt32 entries, bool bStipple);
  virtual bool getEdgesStipple(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  virtual OdTvResult setEdgesLineweight(OdUInt32 entries, OdUInt8 lineweight);
  virtual OdUInt8 getEdgesLineweight(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  virtual OdTvResult setEdgesDrawMode(OdUInt32 entries, OdTvHighlightStyle::EdgesDrawMode mode);
  virtual OdTvHighlightStyle::EdgesDrawMode getEdgeDrawMode(OdTvHighlightStyle::Entry entry, OdTvResult* rc = NULL) const;
  virtual OdTvResult setEdgesParamToDefault(OdUInt32 entries);

  virtual OdTvResult setOnTopOfDepth(bool bSet);
  virtual bool getOnTopOfDepth(OdTvResult* rc = NULL) const;

  /** \details  
  Sets all edges and faces parameters to the default state.
  */
  virtual OdTvResult setByDefault(bool bUseFromPredefined = true);

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
};

/** \details
  This is an implementation of the iterator class for the highlight styles
*/
class ODTV_EXPORT OdTvHighlightStylesIteratorImpl : public OdTvHighlightStylesIterator
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
    Returns the highlight style currently referenced by this Iterator object.
  */
  virtual OdTvHighlightStyleId getHighlightStyle(OdTvResult* rc = NULL) const;

  /** \details
    Positions this Iterator object at the specified highlight style.
    \param objectId [in]  highlight style ID.
  */
  virtual OdTvResult seek(const OdTvHighlightStyleId& objectId);

  /** \details
    Methods for creating the object
  */
  static OdTvHighlightStylesIteratorPtr createObject(OdTvDbDictionaryIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvHighlightStylesIteratorImpl();
  OdTvHighlightStylesIteratorImpl(OdTvDbDictionaryIterator* pDbIterator);

  virtual ~OdTvHighlightStylesIteratorImpl();
  // DB iterator
  OdTvDbDictionaryIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;

};


#include "TD_PackPop.h"

#endif //_ODTV_HIGHLIGHSTYLEIMPL_H_INCLUDED_
