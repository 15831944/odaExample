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

#ifndef _ODTV_HIGHLIGHTSTYLE_H_INCLUDED_
#define _ODTV_HIGHLIGHTSTYLE_H_INCLUDED_

#include "OdaCommon.h"

#include "Tv.h"
#include "TvIObject.h"
#include "TvTraitsDef.h"

class OdTvHighlightStyleId;

/** \details
  The abstract interface class for managing highlight styles in Visualize SDK.
*/
class ODTV_EXPORT OdTvHighlightStyle : public OdTvHandledIObject
{
public:

  /** \details
    Entries of the highlight style
  */
  enum Entry
  {
    /** En entry for 2D render mode.*/
    k2D     = 1 << 0,
    /** En entry for 2D render mode, renders on top of usual 2D mode (k2D).*/
    k2DTop  = 1 << 1,
    /** En entry for 3D render mode.*/
    k3D     = 1 << 2,
    /** En entry for 3D render mode, renders on top of usual 3D mode (k3D).*/
    k3DTop  = 1 << 3
  };

  /** \details
    Edge's draw mode in the highlight style
  */
  enum EdgesDrawMode
  {
    /** Draw existing edges.*/
    kExist    = 0,
    /** Draw isolines.*/
    kIsolines = 1,
    /** Draw contour.*/
    kCountour = 2
  };

  /** \details
    Sets a new name for the highlight style object.
    
    \param sName [in] A string that contains the new name for the highlight style.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new name of the highlight style object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the current highlight style name.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the current name of the highlight style object.
    \remarks
    If the rc parameter is not null and the current name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual const OdString getName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves whether the current highlight style is predefined.
    
    If the predefined flag value is equal to true, the highlight style is used as a predefined one; if the highlight style is not used as a predefined, the method returns false.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the highlight style is the predefined; otherwise the method returns false.
    The predefined highlight style can not be deleted or renamed.
    If the rc parameter is not null and the current value of the predefined flag was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool isPredefined(OdTvResult* rc = NULL) const = 0;

  /** \details
    Copies options from a specified highlight style object.
    
    \param highlightStyleId [in] An identifier of a highlight style object to copy options from.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the copy operation.
    \remarks
    If the highlight style options were successfully copied, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult copyFrom(const OdTvHighlightStyleId& highlightStyleId) = 0;

  /** \details
    Sets a new faces color value for the specified highlight entries.
    
    \param entries     [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The color will be assigned to all input entries.
    \param color       [in] A new color value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the set color operation.
    \remarks
    If the specified color was successfully assigned to the entry of highlight style, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFacesColor(OdUInt32 entries, const OdTvRGBColorDef& color) = 0;

  /** \details
    Retrieves the current color of the faces for the specified highlight entry.
    
    \param entry     [in] An entry of highlight style.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvRGBColorDef, OdTvRGBColorDef> class that represents the current faces color.
    \remarks
    If the rc parameter is not null and the color object was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvRGBColorDef getFacesColor(Entry entry, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new faces transparency value for the specified highlight entries.
    
    \param entries        [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The transparency will be assigned to all input entries.
    \param transparency   [in] A new transparency value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the set transparency operation.
    \remarks
    If the transparency was successfully assigned to the entry of highlight style, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFacesTransparency(OdUInt32 entries, OdUInt8 transparency) = 0;

  /** \details
    Retrieves the current transparency of the faces for the specified highlight entry.
    
    \param entry     [in] An entry of highlight style.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the faces transparency value for the current entry of highlight type.
    \remarks
    If the rc parameter is not null and the transparency object was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt8 getFacesTransparency(Entry entry, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new faces visibility value for the specified highlight entries.
    
    \param entries  [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The visibility will be assigned to all input entries.
    \param bVisible [in] A new visibility value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the visibility setting operation.
    \remarks
    If the specified visibility value was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFacesVisibility(OdUInt32 entries, bool bVisible) = 0;

  /** \details
    Retrieves the current visibility of the faces for the specified highlight entry.
    
    \param entry [in] An entry of highlight style.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current visibility of the faces for the specified highlight entry.
    \remarks
    If the rc parameter is not null and the visibility property was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getFacesVisibility(Entry entry, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new faces stipple flag for the specified highlight entries.
    
    \param entries  [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The stipple mode will be assigned to all input entries.
    \param bStipple [in] A new stipple flag.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the stipple flag setting operation.
    \remarks
    If the stipple flag was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFacesStipple(OdUInt32 entries, bool bStipple) = 0;

  /** \details
    Retrieves the current stipple flag of the faces for the specified highlight entry.
    
    \param entry [in] An entry of highlight style.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current stipple flag of the faces for the specified highlight entry.
    \remarks
    If the rc parameter is not null and the stipple flag was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getFacesStipple(Entry entry, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets all faces parameters to the default state for the specified highlight entries.
    
    \param entries    [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The stipple mode will be assigned to all input entries.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the setting values by default operation.
    \remarks
    If the setting values by default was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFacesParamToDefault(OdUInt32 entries) = 0;

  /** \details
    Sets a new edges color value for the specified highlight entries.
    
    \param entries     [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The color will be assigned to all input entries.
    \param color       [in] A new color value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the set color operation.
    \remarks
    If the specified color was successfully assigned to the entry of highlight style, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesColor(OdUInt32 entries, const OdTvRGBColorDef& color) = 0;

  /** \details
    Retrieves the current color of the edges for the specified highlight entry.
    
    \param entry    [in] An entry of highlight style.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvRGBColorDef, OdTvRGBColorDef> class that represents the current edges color.
    \remarks
    If the rc parameter is not null and the color object was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvRGBColorDef getEdgesColor(Entry entry, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new edges transparency value for the specified highlight entries.
    
    \param entries        [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The transparency will be assigned to all input entries.
    \param transparency   [in] A new transparency value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the set transparency operation.
    \remarks
    If the transparency was successfully assigned to the entry of highlight style, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesTransparency(OdUInt32 entries, OdUInt8 transparency) = 0;

  /** \details
    Retrieves the current transparency of the edges for the specified highlight entry.
    
    \param entry     [in] An entry of highlight style.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the edges transparency value for the current entry of highlight type.
    \remarks
    If the rc parameter is not null and the transparency object was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt8 getEdgesTransparency(Entry entry, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new edges visibility value for the specified highlight entries.
    
    \param entries  [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The visibility will be assigned to all input entries.
    \param bVisible [in] A new visibility value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the visibility setting operation.
    \remarks
    If the specified visibility value was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesVisibility(OdUInt32 entries, bool bVisible) = 0;

  /** \details
    Retrieves the current visibility of the edges for the specified highlight entry.
    
    \param entry [in] An entry of highlight style.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current visibility of the edges for the specified highlight entry.
    \remarks
    If the rc parameter is not null and the visibility property was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getEdgesVisibility(Entry entry, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new edges stipple flag for the specified highlight entries.
    
    \param entries  [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The stipple mode will be assigned to all input entries.
    \param bStipple [in] A new stipple flag.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the stipple flag setting operation.
    \remarks
    If the stipple flag was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesStipple(OdUInt32 entries, bool bStipple) = 0;

  /** \details
    Retrieves the current stipple flag of the edges for the specified highlight entry.
    
    \param entry [in] An entry of highlight style.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current stipple flag of the edges for the specified highlight entry.
    \remarks
    If the rc parameter is not null and the stipple flag was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getEdgesStipple(Entry entry, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new edges lineweight value for the specified highlight entry.
    
    \param entries  [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The stipple mode will be assigned to all input entries.
    \param lineweight [in] A new lineweight value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the set lineweight operation.
    \remarks
    If the lineweight was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesLineweight(OdUInt32 entries, OdUInt8 lineweight) = 0;

  /** \details
    Retrieves the current lineweight of the edges for the specified highlight entry.
    
    \param entry     [in] An entry of highlight style.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the edges lineweight value for the current entry of highlight.
    \remarks
    If the rc parameter is not null and the lineweight value was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt8 getEdgesLineweight(Entry entry, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new edge draw mode value for the specified highlight entry.
    
    \param entries  [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The stipple mode will be assigned to all input entries.
    \param mode  [in] A new edge draw mode value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the set edge draw mode operation.
    \remarks
    If the an edge draw mode was successfully assigned to the entries of highlight style, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesDrawMode(OdUInt32 entries, EdgesDrawMode mode) = 0;

  /** \details
    Retrieves the current edges draw mode for the specified highlight entry.
    
    \param entry     [in] An entry of highlight style.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the edges draw mode value for the current entry of highlight style.
    \remarks
    If the rc parameter is not null and the edge draw mode value was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual EdgesDrawMode getEdgeDrawMode(Entry entry, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets all edges parameters to the default state for the specified highlight entries.
    
    \param entries    [in] A highlight style entries combination (one of a few elements from enum 'Entry'). The stipple mode will be assigned to all input entries.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the setting values by default operation.
    \remarks
    If the setting values by default was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesParamToDefault(OdUInt32 entries) = 0;

  /** \details
    Sets the flag which indicates whether the selected object should be rendered on top of depth in 3d mode.
    
    \param bSet [in]  New value for "draw on top of depth" flag.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the setting on top of depth operation.
    \remarks
    By default "draw on top" style is rendered on top of order, but with this flag it can be rendered on top of depth in 3d rendering modes, works only for k3DTop highlight style entry.
  */
  virtual OdTvResult setOnTopOfDepth(bool bSet) = 0;

  /** \details
    Retrieves the flag which indicates whether the selected object should be rendered on top of depth in 3d mode.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the render on top of depth flag value for the k3DTop highlight style entry.
    \remarks
    If the rc parameter is not null and the value was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getOnTopOfDepth(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets all edges and faces parameters to the default state.
    
    \param bUseFromPredefined [in] If style is predefined and flag is true, parameters will reset to the appropriate predefined style.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the setting values by default operation.
    \remarks
    If the setting values by default was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setByDefault(bool bUseFromPredefined = true) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvHighlightStyle, OdTvHighlightStyle> object.
*/
typedef OdTvSmartPtr<OdTvHighlightStyle> OdTvHighlightStylePtr;


/** \details
  The interface class for a highlight style object identifier that allows access to the <link OdTvHighlightStyle, OdTvHighlightStyleId> object.
*/
class ODTV_EXPORT OdTvHighlightStyleId : public OdTvId
{
public:

  /** \details
    Opens the highlight style determined by its identifier for a read or write operation.
    
    \param mode [in] An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the highlight style object.
    \remarks
    If the rc parameter is not null and the highlight style was successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvHighlightStylePtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

};


/** \details
  The base interface class for the iterator of Visualize SDK highlight style objects.
  An iterator object provides sequential access to a collection of highlight styles.
*/
class ODTV_EXPORT OdTvHighlightStylesIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Retrieves the highlight style that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the highlight style identifier if the iterator refers to a highlight style; otherwise it returns an identifier with a null value.
    \remarks
    If the rc parameter is not null and the highlight style identifier was successfully returned, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the iterator refers to a highlight style, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvHighlightStyleId getHighlightStyle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches for the highlight style defined by its identifier and moves the iterator to this highlight style if found.
    
    \param highlightStyleId [in] A highlight style identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the highlight style specified by its identifier was found, the method returns the tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvHighlightStyleId& highlightStyleId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvHighlightStylesIterator, OdTvHighlightStylesIterator> object.
*/
typedef OdTvSmartPtr<OdTvHighlightStylesIterator> OdTvHighlightStylesIteratorPtr;


#endif //_ODTV_HIGHLIGHTSTYLE_H_INCLUDED_
