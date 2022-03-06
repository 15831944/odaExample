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

#ifndef _ODTV_VISUALSTYLEIMPL_H_INCLUDED_
#define _ODTV_VISUALSTYLEIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdDbStub.h"
#include "DbVisualStyle.h"
#include "GiVisualStyle.h"
#include "DbDictionary.h"

#include "TvVisualStyle.h"
#include "TvInterfaceWrappers.h"
#include "TvUserDataImpl.h"


/** \details
This class represents an implementation of the visual style
*/
class OdTvVisualStyleImpl : public OdTvDbVisualStyle, public OdTvXDataStorage
{
protected:
  OdTvVisualStyleImpl();

public:

  ODRX_DECLARE_MEMBERS(OdTvVisualStyleImpl);

  virtual ~OdTvVisualStyleImpl();

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
  Copy options from the given visual style

  \param pSource [in]  Pointer to the source object
  */
  virtual void copyFrom(const OdRxObject* pSource);

  /** \details
  Mark that this is am defualt visual style
  */
  OdTvResult setDefault(bool bValue);

  /** \details
  Returns true if and only if this visual style is default
  */
  bool       isDefault(OdTvResult *rc = NULL) const;

  /** \details
  Sets the name of this Visual Style object

  \param name [in]  Name.

  \returns
  Returns tvOk if successful, or an internal error if failed
  */
  OdTvResult setName(const OdString& sName);

  /** \details
  Gets the name of this Visual Style object i nthe case if the visual style is default
  */
  const OdString getName() const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

private:

  OdString   m_strName;         // this string represent the real name of the visual style for the default styles
  bool       m_bIsDefault;      // true if this visual style is default

};
typedef OdSmartPtr<OdTvVisualStyleImpl> OdTvVisualStyleImplPtr;


/** \details
This is an wrapper of the interface class for OdTvVisualStyle object.

\remarks
The purpose of this class is to connect the internal visual style object with an interface object
*/
class OdTvVisualStyleWrapper : public OdTvVisualStyle
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvVisualStyle, OdTvVisualStyleImpl)

protected:
  ODRX_HEAP_OPERATORS();

public:

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Interface implementation
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Sets the description for the visual style.

  \param description [in]  Reference to a string that contains the description for this visual style to set.
  */
  virtual OdTvResult setDescription(const OdString& description);

  /** \details
  Returns the description for the visual style as a string.
  */
  virtual const OdString getDescription(OdTvResult* rc = NULL) const;

  /** \details
  Sets the name for the visual style

  \param sName [in]  Reference to a string that contains the name for this visual style to set.
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Returns the name for the visual style as a string.
  */
  virtual const OdString getName(OdTvResult* rc = NULL) const;

  /** \details
  Copy options from the given visual style

  \param vsId         [in]  Visual style to copy from.
  */
  virtual OdTvResult copyFrom(const OdTvVisualStyleId& vsId);

  /** \details
  Determines whether the visual style is default or not. The default visual styles can not be deleted

  \returns
  true - if the visual style is default.
  false - otherwise.

  \remarks
  The default visual styles can not be deleted, renamed or changed the description
  */
  virtual bool getDefault(OdTvResult* rc = NULL) const;

  /** \details
  Sets an integer option of the visual style.

  \param opt  [in]      OdTvVisualStyleOptions::Options to set.
  \param nVal [in]      Integer option value to set.
  \param op   [in]      OdTvVisualStyleOperations::Operation to use for setting the option.
  */
  virtual OdTvResult setOption(OdTvVisualStyleOptions::Options opt, OdInt32 nVal,
    OdTvVisualStyleOperations::Operation op = OdTvVisualStyleOperations::kSet);

  /** \details
  Sets a boolean option of the visual style.

  \param opt  [in]  OdTvVisualStyleOptions::Options to set.
  \param bVal [in]  Boolean option value to set.
  \param op   [in]  OdTvVisualStyleOperations::Operation to use for setting the option.
  */
  virtual OdTvResult setOption(OdTvVisualStyleOptions::Options opt, bool bVal,
    OdTvVisualStyleOperations::Operation op = OdTvVisualStyleOperations::kSet);

  /** \details
  Sets a double option of the visual style.

  \param opt  [in]    OdTvVisualStyleOptions::Options to set.
  \param dVal [in]    Double option value to set.
  \param op   [in]    OdTvVisualStyleOperations::Operation to use for setting the option.
  */
  virtual OdTvResult setOption(OdTvVisualStyleOptions::Options opt, double dVal,
    OdTvVisualStyleOperations::Operation op = OdTvVisualStyleOperations::kSet);

  /** \details
  Sets a color option of the visual style.

  \param opt    [in]  OdTvVisualStyleOptions::Options to set.
  \param color  [in]  Color option value to set.
  \param op     [in]  OdTvVisualStyleOperations::Operation to use for setting the option.
  */
  virtual OdTvResult setOption(OdTvVisualStyleOptions::Options opt, const OdTvColorDef& color,
    OdTvVisualStyleOperations::Operation op = OdTvVisualStyleOperations::kSet);

  /** \details
  Gets an integer option of the visual style.

  \param opt  [in]    OdTvVisualStyleOptions::Options option.
  \param nVal [out]   Reference to an Integer value for return.
  \param pOp    [out]   Pointer to the OdTvVisualStyleOperations::Operation for setting the value that is currently in effect for this option.

  \remarks
  If the requested option has another type or is absent the error returned while the reference to the value doesn't change
  */
  virtual OdTvResult getOption(OdTvVisualStyleOptions::Options opt, OdInt32& nVal, OdTvVisualStyleOperations::Operation *pOp = NULL);

  /** \details
  Gets a boolean option of the visual style.

  \param prop [in]   OdTvVisualStyleOptions::Options option.
  \param bVal [out]  Reference to an Boolean value for return.
  \param pOp    [out]   Pointer to the OdTvVisualStyleOperations::Operation for setting the value that is currently in effect for this option.

  \remarks
  If the requested option has another type or is absent the error returned while the reference to the value doesn't change
  */
  virtual OdTvResult getOption(OdTvVisualStyleOptions::Options opt, bool& bVal, OdTvVisualStyleOperations::Operation *pOp = NULL);

  /** \details
  Gets a double option of the visual style.

  \param prop [in]   OdTvVisualStyleOptions::Options option.
  \param dVal [out]  Reference to an Double value for return.
  \param pOp    [out]   Pointer to the OdTvVisualStyleOperations::Operation for setting the value that is currently in effect for this option.

  \remarks
  If the requested option has another type or is absent the error returned while the reference to the value doesn't change
  */
  virtual OdTvResult getOption(OdTvVisualStyleOptions::Options opt, double& dVal, OdTvVisualStyleOperations::Operation *pOp = NULL);

  /** \details
  Gets a color option of the visual style.

  \param prop   [in]   OdTvVisualStyleOptions::Options option.
  \param color [out]   Reference to an Color value for return.
  \param pOp    [out]   Pointer to the OdTvVisualStyleOperations::Operation for setting the value that is currently in effect for this option.

  \remarks
  If the requested option has another type or is absent the error returned while the reference to the value doesn't change
  */
  virtual OdTvResult getOption(OdTvVisualStyleOptions::Options opt, OdTvColorDef& color, OdTvVisualStyleOperations::Operation *pOp = NULL);

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};

/** \details
  This is an implementation of the iterator class for the visual styles
*/
class ODTV_EXPORT OdTvVisualStylesIteratorImpl : public OdTvVisualStylesIterator
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
    Returns the visual style currently referenced by this Iterator object.
  */
  virtual OdTvVisualStyleId getVisualStyle(OdTvResult* rc = NULL) const;

  /** \details
    Positions this Iterator object at the specified visual style.
    \param objectId [in]  Visual style ID.
  */
  virtual OdTvResult seek(const OdTvVisualStyleId& VisualStyleId);

  /** \details
    Methods for creating the object
  */
  static OdTvVisualStylesIteratorPtr createObject(OdTvDbDictionaryIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvVisualStylesIteratorImpl();
  OdTvVisualStylesIteratorImpl(OdTvDbDictionaryIterator* pDbIterator);

  virtual ~OdTvVisualStylesIteratorImpl();
  // DB iterator
  OdTvDbDictionaryIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;

};

/** \details
Gets the GI visual style property by option
*/
OdGiVisualStyleProperties::Property GetGiVisualStylePropertyByOption(OdTvVisualStyleOptions::Options opt);

#include "TD_PackPop.h"

#endif //_ODTV_VISUALSTYLEIMPL_H_INCLUDED_
