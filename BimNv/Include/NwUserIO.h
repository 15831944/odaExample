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

#ifndef _ODNWUSERIO_H_INCLUDED_
#define _ODNWUSERIO_H_INCLUDED_

#include "NwObject.h"
#include "NwExport.h"
#include "NwCmColor.h"
#include "NwSSet.h"
#include "OdPlatform.h"
#include "Ed/EdUserIO.h"
#include "Ed/EdBaseUserIO.h"

class OdCmColor;
class OdSelectionSet;


/** \details
  This class represents selection set trakers.

  <group OdEd_Classes>
*/
class ODRX_ABSTRACT NWDBEXPORT OdNwSSetTracker : public OdEdInputTracker
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSSetTracker);
  //DOM-IGNORE-END

  /** \details
    Appends a new object to the selection set traker.

    \param id      [in]  Object ID.
    \param pMethod [in]  Selection method.

    \returns True if the operation is successful; false otherwise.
  */
  virtual bool append(const OdNwObjectId&  id, const OdDbSelectionMethod* pMethod) = 0;

  /** \details
    Removes an object from the selection set traker.

    \param id      [in]  Object ID.
    \param pMethod [in]  Selection method.

    \returns True if the operation is successful; false otherwise.
  */
  virtual bool remove(const OdNwObjectId&  id, const OdDbSelectionMethod* pMethod) = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwSSetTracker object pointers.
*/
typedef OdSmartPtr<OdNwSSetTracker> OdNwSSetTrackerPtr;


/** \details
  This class implements geometric interactive user IO functionality for custom
  interactive command objects.

  Corresponding C++ library: TB_DB
*/
class ODRX_ABSTRACT NWDBEXPORT OdNwUserIO : public OdEdBaseUserIO
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwUserIO);
  //DOM-IGNORE-END

//  virtual void setPickfirst(OdBmSelectionSet* pSSet) = 0;

  /** \details
    Returns the user input of a color.

    \param prompt        [in]  Message displayed to prompt the user.
    \param options       [in]  Combination of OdEd::GetPointOptions enum values.
    \param pDefaultValue [in]  Pointer to a default value to return if an empty string is received as input.
    \param keywords      [in]  Keyword string.
    \param pTracker      [in]  Pointer to a User IO tracker.

    \returns User input of a color.

    \remarks
    This function uses the underlying OdEdBaseIO functions putString() and
    getString() for low level output and input.
    If prompt is an empty string, the default prompt string is used.
  */
  virtual OdNwCmColor getColor( const OdString& prompt,
                                int options = OdEd::kInpDefault,
                                const OdCmColorBase* pDefaultValue = 0,
                                const OdString& keywords = OdString::kEmpty,
                                OdEdColorTracker* pTracker = 0) = 0;

  /** \details
    Launches interactive object selection to fill a selection set.

    \param prompt        [in]  Message displayed to prompt the user.
    \param options       [in]  Combination of OdEd::GetPointOptions enum values.
    \param pDefaultValue [in]  Pointer to a default value to return if an empty string is received as input.
    \param keywords      [in]  Keyword string.
    \param pTracker      [in]  Pointer to a User IO tracker.

    \returns Smart pointer to the filled selection set.

    \remarks
    Each subsequent call to this function modifies the current selection set.
    Returned value is guaranteed to be not NULL.
  */
  virtual OdNwSelectionSetPtr select(const OdString& prompt = OdString::kEmpty,
    int options = OdEd::kSelDefault,
    const OdNwSelectionSet* pDefaultValue = 0,
    const OdString& keywords = OdString::kEmpty,
    OdNwSSetTracker* pTracker = 0) = 0;

  /** \details
    Returns the user input of a color as a wrapped value.

    \param prompt        [in]  Message displayed to prompt the user.
    \param options       [in]  Combination of OdEd::GetPointOptions enum values.
    \param pDefaultValue [in]  Pointer to the default value to return if an empty string is received as input.
    \param keywords      [in]  Keyword string.
    \param pTracker      [in]  Pointer to a User IO tracker.

    \returns User input of a color as a wrapped value.

    \remarks
    This function uses the underlying OdEdBaseIO functions putString() and
    getString() for low level output and input.
    If the prompt is an empty string, the default prompt string is used.
  */
  virtual OdSharedPtr<OdCmColorBase> getCmColor(
    const OdString& prompt,
    int options = OdEd::kInpDefault,
    const OdCmColorBase* pDefaultValue = 0,
    const OdString& keywords = OdString::kEmpty,
    OdEdColorTracker* pTracker = 0) = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbUserIO
  object pointers.
*/
typedef OdSmartPtr<OdNwUserIO> OdNwUserIOPtr;

#endif //#ifndef _ODNWUSERIO_H_INCLUDED_
