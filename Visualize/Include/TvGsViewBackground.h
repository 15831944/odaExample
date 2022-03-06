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

#ifndef _ODTV_GSVIEW_BACKGROUND_H_INCLUDED_
#define _ODTV_GSVIEW_BACKGROUND_H_INCLUDED_

#include "OdaCommon.h"

#include "Tv.h"
#include "TvIObject.h"
#include "TvTraitsDef.h"

class OdTvGsViewBackgroundId;

/** \details
  This class represents a view solid background.
  \sa
  <link tv_working_with_attributes_view_backgrounds, Work with View Backgrounds>
*/
class ODTV_EXPORT OdTvGsViewSolidBackground : public OdTvHandledIObject
{
public:

  /** \details
    Sets a solid color to this background.
    
    \param color [in] A new color represented with an instance of the <link OdTvColorDef, OdTvColorDef> class.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color is successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setColorSolid(const OdTvColorDef& color) = 0;

  /** \details
    Retrieves the solid color of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the color definition represented as an RGB color, inherited color or color index.
    \remarks
    If the rc parameter is not null and the color information is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getColorSolid(OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the name for the background.
    
    \param sName [in]  A new background name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new name is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the name of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the background name.
    \remarks
    If the rc parameter is not null and the name is successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) = 0;

};

/** \details
  A data type that represents a smart pointer to an <link OdTvGsViewSolidBackground, OdTvGsViewSolidBackground> object.
*/
typedef OdTvSmartPtr<OdTvGsViewSolidBackground> OdTvGsViewSolidBackgroundPtr;

/** \details
  This class represents a view gradient background.
  \sa
  <link tv_working_with_attributes_view_backgrounds, Work with View Backgrounds>
*/
class ODTV_EXPORT OdTvGsViewGradientBackground : public OdTvHandledIObject
{
public:

  /** \details
    Sets a top gradient color to this background.
    
    \param color [in] A color represented with an instance of the <link OdTvColorDef, OdTvColorDef> class.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color is successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setColorTop(const OdTvColorDef& color) = 0;

  /** \details
    Retrieves the top gradient color of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the color definition represented as an RGB color, inherited color or color index.
    \remarks
    If the rc parameter is not null and the color information is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getColorTop(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a middle gradient color to this background.
    
    \param color [in] A color represented with an instance of the <link OdTvColorDef, OdTvColorDef> class.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color is successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setColorMiddle(const OdTvColorDef& color) = 0;

  /** \details
    Retrieves the middle gradient color of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the color definition represented as an RGB color, inherited color or color index.
    \remarks
    If the rc parameter is not null and the color information is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getColorMiddle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a bottom gradient color for this background.
    
    \param color [in] A color represented with an instance of the <link OdTvColorDef, OdTvColorDef> class.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color is successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setColorBottom(const OdTvColorDef& color) = 0;

  /** \details
    Retrieves the bottom gradient color of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the color definition represented as an RGB color, inherited color or color index.
    \remarks
    If the rc parameter is not null and the color information is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getColorBottom(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the horizon value for the background.
    
    \param dHorizon [in] A new horizon value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the horizon value is successfully applied, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setHorizon(double dHorizon) = 0;

  /** \details
    Retrieves the horizon value of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the horizon value.
    \remarks
    If the rc parameter is not null and the horizon value is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual double getHorizon(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the height value for the background.
    
    \param dHeight [in] A new height value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the height value is successfully applied, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setHeight(double dHeight) = 0;

  /** \details
    Retrieves the height value of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the height value.
    \remarks
    If the rc parameter is not null and the height value is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual double getHeight(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the rotation value for the background.
    
    \param dRotation [in] A new rotation value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the rotation value is successfully applied, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setRotation(double dRotation) = 0;

  /** \details
    Retrieves the rotation value of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the rotation value.
    \remarks
    If the rc parameter is not null and the rotation value is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual double getRotation(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the name for the background.
    
    \param sName [in]  A new background name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new name is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the name of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the background name.
    \remarks
    If the rc parameter is not null and the name is successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvGsViewGradientBackground, OdTvGsViewGradientBackground> object.
*/
typedef OdTvSmartPtr<OdTvGsViewGradientBackground> OdTvGsViewGradientBackgroundPtr;

/** \details
  This class represents a view image background.
  \sa
  <link tv_working_with_attributes_view_backgrounds, Work with View Backgrounds>
*/
class ODTV_EXPORT OdTvGsViewImageBackground : public OdTvHandledIObject
{
public:

  /** \details
    Sets the image file name for the background.
    
    \param filename [in]  An image file name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new image filename is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setImageFilename(const OdString& filename) = 0;

  /** \details
    Retrieves the image file name for the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the background image filename.
    \remarks
    If the rc parameter is not null and the image file name is successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdString getImageFilename(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the fit-to-screen flag value.
    
    \param bFitToScreen [in] A new flag value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new flag value is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFitToScreen(bool bFitToScreen) = 0;

  /** \details
    Retrieves the value of the fit-to-screen flag.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the value of the fit-to-screen flag.
    \remarks
    If the rc parameter is not null and the flag value is successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual bool getFitToScreen(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the maintain-aspect-ratio flag value.
    
    \param bMaintainAspectRatio [in] A new flag value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new flag value is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMaintainAspectRatio(bool bMaintainAspectRatio) = 0;

  /** \details
    Retrieves the value of the maintain-aspect-ratio flag.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the value of the maintain-aspect-ratio flag.
    \remarks
    If the rc parameter is not null and the flag value is successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual bool getMaintainAspectRatio(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the use-tiling flag value.
    
    \param bUseTiling [in] A new flag value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new flag value is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setUseTiling(bool bUseTiling) = 0;

  /** \details
    Retrieves the value of the use-tiling flag.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the value of the use-tiling flag.
    \remarks
    If the rc parameter is not null and the flag value is successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual bool getUseTiling(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the x-offset value for the background.
    
    \param dXOffset [in] An x-offset value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the x-offset is successfully applied, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setXOffset(double dXOffset) = 0;

  /** \details
    Retrieves the x-offset value of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the x-offset value.
    \remarks
    If the rc parameter is not null and the x-offset value is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual double getXOffset(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the y-offset value for the background.
    
    \param dYOffset [in] A y-offset value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the y offset is successfully applied, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setYOffset(double dYOffset) = 0;

  /** \details
  Retrieves the y-offset value of the background.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the y-offset value.
  \remarks
  If the rc parameter is not null and the y-offset value is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
  appropriate error code.
  */
  virtual double getYOffset(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the x-scale value for the background.
    
    \param dXScale [in] An x-scale value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the x-scale is successfully applied, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setXScale(double dXScale) = 0;

  /** \details
    Retrieves the x-scale value of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the x-scale value.
    \remarks
    If the rc parameter is not null and the x-scale value is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual double getXScale(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the y-scale value for the background.
    
    \param dYScale [in] A y-scale value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the y-scale is successfully applied, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setYScale(double dYScale) = 0;

  /** \details
    Retrieves the y-scale value of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the y-scale value.
    \remarks
    If the rc parameter is not null and the y-scale value is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual double getYScale(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the name for the background.
    
    \param sName [in]  A new background name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new name is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the name of the background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the background name.
    \remarks
    If the rc parameter is not null and the name is successfully returned, the rc parameter accepts tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) = 0;

};

/** \details
  A data type that represents a smart pointer to an <link OdTvGsViewImageBackground, OdTvGsViewGradientBackground> object.
*/
typedef OdTvSmartPtr<OdTvGsViewImageBackground> OdTvGsViewImageBackgroundPtr;

/** \details
  This is an interface class for access to any OdTvGsViewBackground.
  \sa
  <link tv_working_with_attributes_view_backgrounds, Work with View Backgrounds>
*/
class ODTV_EXPORT OdTvGsViewBackgroundId : public OdTvId
{
public:
  /** \details
    Enumerates view background types.
  */
  enum BackgroundTypes
  {
    kSolid = 0,       // A solid background.
    kGradient = 1,    // A gradient background.
    kImage = 2        // An image background.
  };

  /** \details
    Returns the type of view background.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current type of the view background represented as a value of the <link OdTvGsViewBackgroundId::BackgroundTypes, BackgroundTypes> enumeration.
    \remarks
    If the rc parameter is not null and the view background type is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  BackgroundTypes getType(OdTvResult* rc = NULL) const;

  /** \details
    Opens the view background determined with its identifier as an <link OdTvGsViewSolidBackground, OdTvGsViewSolidBackground> object for a read or write operation.
    
    \param mode [in] An open mode value (read or write).
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the view solid background object.
    \remarks
    If the rc parameter is not null and the view background is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvGsViewSolidBackgroundPtr openAsSolidBackground(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

  /** \details
    Opens the view background determined with its identifier as an <link OdTvGsViewGradientBackground, OdTvGsViewGradientBackground> object for a read or write operation.
    
    \param mode [in] An open mode value (read or write).
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the view gradient background object.
    \remarks
    If the rc parameter is not null and the view background is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvGsViewGradientBackgroundPtr openAsGradientBackground(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

  /** \details
    Opens the view background determined with its identifier as an <link OdTvGsViewImageBackground, OdTvGsViewImageBackground> object for a read or write operation.
    
    \param mode [in] An open mode value (read or write).
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the view image background object.
    \remarks
    If the rc parameter is not null and the view background is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvGsViewImageBackgroundPtr openAsImageBackground(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;
};

/** \details
  The base interface class for the iterator of Visualize SDK view background objects.
  An iterator object provides sequential access to a collection of view backgrounds.
*/
class ODTV_EXPORT OdTvGsViewBackgroundsIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Retrieves the view background that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the view background identifier if the iterator refers to a layer; otherwise it returns an identifier with a null value.
    \remarks 
    If the rc parameter is not null and the view background identifier is successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    If the iterator refers to a view background, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvGsViewBackgroundId getGsViewBackground(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches the view background defined through its identifier and moves the iterator to this view background if found.
    
    \param viewBackgroundId [in] A view background identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the view background specified through its identifier is found, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvGsViewBackgroundId& viewBackgroundId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvGsViewBackgroundsIterator, OdTvGsViewBackgroundsIterator> object.
*/
typedef OdTvSmartPtr<OdTvGsViewBackgroundsIterator> OdTvGsViewBackgroundsIteratorPtr;

#endif //_ODTV_GSVIEW_H_INCLUDED_
