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

#ifndef _DBSCALE_INCLUDED_
#define _DBSCALE_INCLUDED_

#include "DbObject.h"

/** \details
  <group OdTvDb_Classes>

  This class implements the scale object that stores information about an annotation scale as an 
  element of the database container. The database stores the scale instances in the dictionary 
  and associates the object ID with an each scale instance. The scale dictionary is accessed from 
  the database object using the getScaleListDictionaryId() method. The root drawing dictionary, 
  associates the "TV_ACAD_SCALELIST" name with the scale dictionary.

  \remarks
  This class is intended for stand-alone applications only. TXSDK developers cannot use it.

  \sa
  TD_Db

  \sa
  <link db_scale_sample_object.html, Example of Working with the Scale Object>

  <link db_scale_sample_dictionary.html, Example of Working with the Scale Dictionary Object>

  \sa
  <link db_scale.html, Working with Scales>

  OdTvDbAnnotationScale class
*/
class TOOLKIT_EXPORT OdTvDbScale : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbScale);

  /** \details
    Builds an instance of the scale object.

    \remarks
    Use the static pseudo-constructor instead it.
    See: <link db_scale_manipulate.html, Manipulating Objects of the Scale Dictionary>
  */
  OdTvDbScale();


  /** \details
    Returns the internal scale name as a String value. This name is used as a comment for the ratio 
    of paper units to drawing units when the scale object is displayed in a list.
  
    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::setScaleName() method
  */
  class OdString scaleName() const;


  /** \details
    Sets the internal scale name as a String value. This name is used as a comment for the ratio 
    of paper units to drawing units when the scale object is displayed in a list. The initial value 
    is an empty string by default.
  
    \param sName [in]   Scale name as non-empty string.

    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::scaleName() method
  */
  void setScaleName( const OdString& sName );


  /** \details
    Returns the scale factor as a positive Double value. This factor defines the ratio in which 
    units of model space correlate to the units of paper space and indicates how many paper units 
    fit to one drawing unit.
  
    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::paperUnits(), OdTvDbScale::drawingUnits() methods
  */
  double scale() const;


  /** \details
    Returns the number of drawing units as a positive Double value.
  
    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::setDrawingUnits(), OdTvDbScale::paperUnits(), OdTvDbScale::scale() methods
  */
  double drawingUnits() const;


  /** \details
    Sets the number of drawing units as a positive Double value. The initial value is 1.0 by default.
  
    \param vUnits [in]   value of drawing units.

    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::drawingUnits(), OdTvDbScale::setPaperUnits(), OdTvDbScale::scale() methods
  */
  void setDrawingUnits( double vUnits );


  /** \details
    Returns the number of paper units as a positive Double value.
  
    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::setPaperUnits(), OdTvDbScale::drawingUnits(), OdTvDbScale::scale() methods
  */
  double paperUnits() const;


  /** \details
    Sets the number of paper units as a positive Double value. The initial value is 1.0 by default.
  
    \param vUnits [in]   value of paper units.

    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::paperUnits(), OdTvDbScale::setDrawingUnits(), OdTvDbScale::scale() methods
  */
  void setPaperUnits( double vUnits );


  /** \details
    Determines whether the scale object is temporary stored in the database and returns True if the  
    scale is temporary or False if the scale is fixed. 
    
    \remarks
    The temporary scale typically exists because attached XREF objects in the drawing have dependencies 
    on scales that are not directly referenced by other objects in the drawing. 

    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::setIsTemporaryScale() method
  */
  bool isTemporaryScale() const;


  /** \details
    Sets the scale temporary status as a Boolean value. The initial value is False by default.

    \remarks
    The temporary scale typically exists because attached XREF objects in the drawing have  
    dependencies on scales that are not directly referenced by other objects in the drawing. 

    \param bStatus [in]   True if the scale is temporary or False if the scale is fixed.

    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::isTemporaryScale() method
  */
  void setIsTemporaryScale( bool bStatus );


  /** \details
    Determines whether the scale object is selected as one-to-one (1:1) by default and returns True if 
    the scale is selected (1:1) by default or False if the scale is not the default.

    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::setIsUnitScale() method
  */
  bool isUnitScale() const;


  /** \details
    Sets the scale default status as a Boolean value. The initial value is False by default.

    \param bStatus [in]   True if the scale is selected (1:1) by default or False if the scale is not the default.

    \sa
    <link db_scale_sample_object.html, Example of Working with the Scale Object>

    \sa
    <link db_scale.html, Working with Scales>

    OdTvDbScale::isUnitScale() method
  */
  void setIsUnitScale( bool bStatus );

  /*!DOM*/
  /** \details
    For internal use only.
  */
  void getXRefMangledName(OdString, OdString&, OdTvDbDatabase *);
  /*!DOM*/  
  /** \details
    For internal use only.
  */
  static bool nameExists(const OdString&, bool xref, OdString*, OdTvDbDatabase *);

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler) ODRX_OVERRIDE;
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const ODRX_OVERRIDE;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler) ODRX_OVERRIDE;
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const ODRX_OVERRIDE;

  virtual void appendToOwner(OdTvDbIdPair& idPair, OdTvDbObject* pOwnerObject, OdTvDbIdMapping& ownerIdMap) ODRX_OVERRIDE;
  virtual OdResult subErase(bool erasing) ODRX_OVERRIDE;
  virtual void applyPartialUndo(OdTvDbDwgFiler* pFiler, OdRxClass* pClass) ODRX_OVERRIDE;
};

/** \details
  The typified smart pointer for the scale object. This template class is a specialization of 
  the OdSmartPtr class for OdTvDbScale object.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbScale> OdTvDbScalePtr;


#endif //_DBSCALE_INCLUDED_
