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

#ifndef _ODTV_GSVIEW_BACKGROUNDIMPL_H_INCLUDED_
#define _ODTV_GSVIEW_BACKGROUNDIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdDbStub.h"
#include "DbDictionary.h"
#include "DbBackground.h"

#include "TvGsViewBackground.h"
#include "TvInterfaceWrappers.h"
#include "TvUserDataImpl.h"

/** \details
This class represents an implementation of the view solid background
*/
class OdTvGsViewSolidBackgroundImpl : public OdTvDbSolidBackground, public OdTvXDataStorage
{
protected:
  OdTvGsViewSolidBackgroundImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvGsViewSolidBackgroundImpl);

  virtual ~OdTvGsViewSolidBackgroundImpl();

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
  Return the value of memory, which this object takes up.
  */
  virtual OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;
};
typedef OdSmartPtr<OdTvGsViewSolidBackgroundImpl> OdTvGsViewSolidBackgroundImplPtr;

/** \details
This is an wrapper of the interface class for OdTvGsViewSolidBackground object.

\remarks
The purpose of this class is to connect the internal view background object with an interface object
*/
class OdTvGsViewSolidBackgroundWrapper : public OdTvGsViewSolidBackground
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvGsViewSolidBackground, OdTvGsViewSolidBackgroundImpl)

protected:
  ODRX_HEAP_OPERATORS();

public:

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Interface implementation
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Sets a solid color to this background.
  \param color    [in] A new color represented with an instance of the <link OdTvColorDef, OdTvColorDef> class.
  */
  virtual OdTvResult setColorSolid(const OdTvColorDef& color);

  /** \details
  Retrieves the solid color of the background.
  \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvColorDef getColorSolid(OdTvResult* rc = NULL);

  /** \details
  Sets the name for the background.
  \param sName [in]  A new background name.
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Retrieves the name of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdString getName(OdTvResult* rc = NULL);

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};

/** \details
This class represents an implementation of the view gradient background
*/
class OdTvGsViewGradientBackgroundImpl : public OdTvDbGradientBackground, public OdTvXDataStorage
{
protected:
  OdTvGsViewGradientBackgroundImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvGsViewGradientBackgroundImpl);

  virtual ~OdTvGsViewGradientBackgroundImpl();

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
  Return the value of memory, which this object takes up.
  */
  virtual OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;
};
typedef OdSmartPtr<OdTvGsViewGradientBackgroundImpl> OdTvGsViewGradientBackgroundImplPtr;

/** \details
This is an wrapper of the interface class for OdTvGsViewGradientBackground object.

\remarks
The purpose of this class is to connect the internal view background object with an interface object
*/
class OdTvGsViewGradientBackgroundWrapper : public OdTvGsViewGradientBackground
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvGsViewGradientBackground, OdTvGsViewGradientBackgroundImpl)

protected:
  ODRX_HEAP_OPERATORS();

public:

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Interface implementation
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Sets a top gradient color to this background.
  \param color [in] A color represented with an instance of the <link OdTvColorDef, OdTvColorDef> class.
  */
  virtual OdTvResult setColorTop(const OdTvColorDef& color);

  /** \details
  Retrieves the top gradient color of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvColorDef getColorTop(OdTvResult* rc = NULL) const;

  /** \details
  Sets a middle gradient color to this background.
  \param color [in] A color represented with an instance of the <link OdTvColorDef, OdTvColorDef> class.
  */
  virtual OdTvResult setColorMiddle(const OdTvColorDef& color);

  /** \details
  Retrieves the middle gradient color of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvColorDef getColorMiddle(OdTvResult* rc = NULL) const;

  /** \details
  Sets a bottom gradient color to this background.
  \param color [in] A color represented with an instance of the <link OdTvColorDef, OdTvColorDef> class.
  */
  virtual OdTvResult setColorBottom(const OdTvColorDef& color);

  /** \details
  Retrieves the bottom gradient color of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvColorDef getColorBottom(OdTvResult* rc = NULL) const;

  /** \details
  Sets the horizon value for the background.
  \param dHorizon [in] A new horizon value.
  */
  virtual OdTvResult setHorizon(double dHorizon);

  /** \details
  Retrieves the horizon value of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual double getHorizon(OdTvResult* rc = NULL) const;

  /** \details
  Sets the height value for the background.
  \param dHeight [in] A new height value.
  */
  virtual OdTvResult setHeight(double dHeight);

  /** \details
  Retrieves the height value of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual double getHeight(OdTvResult* rc = NULL) const;

  /** \details
  Sets the rotation value for the background.
  \param dRotation [in] A new rotation value.
  */
  virtual OdTvResult setRotation(double dRotation);

  /** \details
  Retrieves the rotation value of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual double getRotation(OdTvResult* rc = NULL) const;

  /** \details
  Sets the name for the background.
  \param sName [in]  A new background name.
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Retrieves the name of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdString getName(OdTvResult* rc = NULL);

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};

/** \details
This class represents an implementation of the view image background
*/
class OdTvGsViewImageBackgroundImpl : public OdTvDbImageBackground, public OdTvXDataStorage
{
protected:
  OdTvGsViewImageBackgroundImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvGsViewImageBackgroundImpl);

  virtual ~OdTvGsViewImageBackgroundImpl();

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
  Return the value of memory, which this object takes up.
  */
  virtual OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;
};
typedef OdSmartPtr<OdTvGsViewImageBackgroundImpl> OdTvGsViewImageBackgroundImplPtr;

/** \details
This is an wrapper of the interface class for OdTvGsViewImageBackground object.

\remarks
The purpose of this class is to connect the internal view background object with an interface object
*/
class OdTvGsViewImageBackgroundWrapper : public OdTvGsViewImageBackground
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvGsViewImageBackground, OdTvGsViewImageBackgroundImpl)

protected:
  ODRX_HEAP_OPERATORS();

public:

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Interface implementation
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Sets the image file name to background.
  \param filename [in]  A image file name.
  */
  virtual OdTvResult setImageFilename(const OdString& filename);

  /** \details
  Retrieves the image file name to background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdString getImageFilename(OdTvResult* rc = NULL) const;

  /** \details
  Sets the fit to screen flag value.
  \param bFitToScreen [in] A new flag value.
  */
  virtual OdTvResult setFitToScreen(bool bFitToScreen);

  /** \details
  Retrieves the value of the fit to screen flag.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual bool getFitToScreen(OdTvResult* rc = NULL) const;

  /** \details
  Sets the maintain aspect ratio flag value.
  \param bMaintainAspectRatio [in] A new flag value.
  */
  virtual OdTvResult setMaintainAspectRatio(bool bMaintainAspectRatio);

  /** \details
  Retrieves the value of the maintain aspect ratio flag.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual bool getMaintainAspectRatio(OdTvResult* rc = NULL) const;

  /** \details
  Sets the use tiling flag value.
  \param bUseTiling [in] A new flag value.
  */
  virtual OdTvResult setUseTiling(bool bUseTiling);

  /** \details
  Retrieves the value of the use tiling flag.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual bool getUseTiling(OdTvResult* rc = NULL) const;

  /** \details
  Sets the x offset value for the background.
  \param dXOffset [in] A x offset value.
  */
  virtual OdTvResult setXOffset(double dXOffset);

  /** \details
  Retrieves the x offset value of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual double getXOffset(OdTvResult* rc = NULL) const;

  /** \details
  Sets the y offset value for the background.
  \param dYOffset [in] A y offset value.
  */
  virtual OdTvResult setYOffset(double dYOffset);

  /** \details
  Retrieves the y offset value of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual double getYOffset(OdTvResult* rc = NULL) const;

  /** \details
  Sets the x scale value for the background.
  \param dXScale [in] A x scale value.
  */
  virtual OdTvResult setXScale(double dXScale);

  /** \details
  Retrieves the x scale value of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual double getXScale(OdTvResult* rc = NULL) const;

  /** \details
  Sets the y scale value for the background.
  \param dYScale [in] A y scale value.
  */
  virtual OdTvResult setYScale(double dYScale);

  /** \details
  Retrieves the y scale value of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual double getYScale(OdTvResult* rc = NULL) const;

  /** \details
  Sets the name for the background.
  \param sName [in]  A new background name.
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Retrieves the name of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdString getName(OdTvResult* rc = NULL);

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};

/** \details
This is an implementation of the iterator class for the view background
*/
class ODTV_EXPORT OdTvGsViewBackgroundsIteratorImpl : public OdTvGsViewBackgroundsIterator
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
  Returns the view background currently referenced by this Iterator object.
  */
  virtual OdTvGsViewBackgroundId getGsViewBackground(OdTvResult* rc = NULL) const;

  /** \details
  Positions this Iterator object at the specified view background.
  \param viewBackgroundId [in]  View background ID.
  */
  virtual OdTvResult seek(const OdTvGsViewBackgroundId& viewBackgroundId);

  /** \details
  Methods for creating the object
  */
  static OdTvGsViewBackgroundsIteratorPtr createObject(OdTvDbDictionaryIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvGsViewBackgroundsIteratorImpl();
  OdTvGsViewBackgroundsIteratorImpl(OdTvDbDictionaryIterator* pDbIterator);

  virtual ~OdTvGsViewBackgroundsIteratorImpl();
  // DB iterator
  OdTvDbDictionaryIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;

};

#include "TD_PackPop.h"

#endif //_ODTV_GSVIEW_BACKGROUNDIMPL_H_INCLUDED_
