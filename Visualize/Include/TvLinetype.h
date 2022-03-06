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

#ifndef _ODTV_LINETYPE_H_INCLUDED_
#define _ODTV_LINETYPE_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvLinetypeElement.h"
#include "TvUserData.h"

typedef OdVector<OdTvLinetypeElementPtr>  OdTvLinetypeElementArray;

/** \details
  The abstract interface class for linetype management of Visualize SDK entities.
  \sa
  <link tv_working_with_attributes_linetypes, Work with Linetypes>
*/
class ODTV_EXPORT OdTvLinetype : public OdTvHandledIObject
{
public:

  /** \details
    Predefined linetypes.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  enum Predefined
  {
    kSolid = 0,               // Solid pattern.
    kDashDot = 1,             // Pattern of 0.5 Dash - 0.125 Space - Dot - 0.125 Space.
    kDashed = 2,              // Pattern of 0.5 Dash - 0.125 Space.
    kDotted = 3,              // Pattern of Dot - 0.125 Space.
    kDash2Dot = 4,            // Pattern of 0.5 Dash - 0.125 Space - Dot - 0.125 Space - Dot - 0.125 Space.
    kDash3Dot = 5,            // Pattern of 0.5 Dash - 0.125 Space - Dot - 0.125 Space - Dot - 0.125 Space - Dot - 0.125 Space.
    kLongDash = 6,            // Pattern of 1.0 Dash - 0.125 Space.
    kLongDashShortDash = 7,   // Pattern of 1.0 Dash - 0.125 Space - 0.25 Dash - 0.125 Space.
    kLongDash2ShortDash = 8   // Pattern of 1.0 Dash - 0.125 Space - 0.25 Dash - 0.125 Space - 0.25 Dash - 0.125 Space.
  };
  
  /** \details
    Sets new linetype elements for the linetype object.
    
    \param elements [in] An array of linetype elements.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If new linetype elements were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual OdTvResult setElements(const OdTvLinetypeElementArray& elements) = 0;

  /** \details
    Sets new linetype elements for the linetype object.
    
    \param nElements [in] An array of linetype elements.
    \param elements  [in] A pointer to an array of smart pointers to linetype elements.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If new linetype elements were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual OdTvResult setElements(OdInt32 nElements, const OdTvLinetypeElementPtr* elements) = 0;

  /** \details
    Retrieves the current linetype elements of the linetype object.
    
    \param elements [out] A placeholder for an array of linetype elements. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The method fills the passed array and returns it to a calling subroutine.
    If linetype elements were successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual OdTvResult getElements(OdTvLinetypeElementArray& elements) const = 0;

  /** \details
    Sets a new name for the linetype object.
    
    \param sName [in] A string that contains the new linetype object's name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The name string length should be from 0 to 255 characters.
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the new linetype object name was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the current linetype object's name.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the name of the linetype object.
    \remarks 
    If the rc parameter is not null and the name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual OdString getName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new description for the linetype object. 
    
    It can be a comment or series of underscores, dots, dashes, and spaces to reflect the representation of the linetype. 
    The initial value is an empty string.
    \param sDescr [in] A string that contains the description.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new linetype object description was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual OdTvResult setDescription(const OdString& sDescr) = 0;

  /** \details
    Retrieves the current linetype object's description.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the description of the linetype object.
    \remarks 
    If the rc parameter is not null and the description was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual OdString getDescription(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new alignment scale-to-fit flag value for the linetype object.
    
    \param bScaleToFit [in] A flag value that determines whether the scaling is applied (if true) of not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual OdTvResult setScaledToFit(bool bScaleToFit) = 0;

  /** \details
    Retrieves whether the alignment is scaled to fit. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the alignment is scaled to fit; otherwise the method returns false.
    \remarks 
    If the rc parameter is not null and the alignment scaling flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual bool getScaledToFit(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a scale for the linetype object. This scale will be applied to all elements in this linetype.
    
    \param scale [in] A new scale value
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the scale value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual OdTvResult setScale(double scale) = 0;

  /** \details
    Retrieves the scale of this linetype.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Scale of this linetype object.
    \remarks
    If the rc parameter is not null and the scale value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes_properties, Work with Linetype Properties>
  */
  virtual double getScale(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvLinetype, OdTvLinetype> object.
*/
typedef OdTvSmartPtr<OdTvLinetype> OdTvLinetypePtr;


/** \details
  The interface class for a linetype object identifier that allows access to the <link OdTvLinetype, OdTvLinetype> object.
*/
class ODTV_EXPORT OdTvLinetypeId : public OdTvId
{
public:

  /** \details
    Opens the linetype determined with its identifier for a read or write operation. 
    
    \param mode [in] An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the linetype object.
    \remarks
    If the rc parameter is not null and the linetype is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvLinetypePtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;
};

/** \details
  The base interface class for the iterator of Visualize SDK linetype objects.
  An iterator object provides sequential access to a collection of linetypes.
*/
class ODTV_EXPORT OdTvLinetypesIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Retrieves the linetype that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the linetype object identifier if the iterator refers to a linetype; otherwise it returns an identifier with a null value.
    \remarks 
    If the rc parameter is not null and the linetype identifier is successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    If the iterator refers to a linetype, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvLinetypeId getLinetype(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches the linetype defined by its identifier and moves the iterator to this linetype object if found.
    
    \param linetypeId [in] A linetype identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the linetype specified by its identifier is found, the method returns the tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvLinetypeId& linetypeId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvLinetypesIterator, linetypes iterator> object.
*/
typedef OdTvSmartPtr<OdTvLinetypesIterator> OdTvLinetypesIteratorPtr;


#endif // _ODTV_LINETYPE_H_INCLUDED_
