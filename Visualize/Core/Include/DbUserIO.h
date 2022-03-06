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

#ifndef _ODDBUSERIO_H_INCLUDED_
#define _ODDBUSERIO_H_INCLUDED_

#include "DbExport.h"
#include "OdPlatform.h"
#include "Ed/EdUserIO.h"
#include "Ed/EdBaseUserIO.h"
#include "DbSSet.h"

class OdTvCmColor;
class OdSelectionSet;
class OdGsModel;


typedef OdSmartPtr<OdSSetTracker> OdSSetTrackerPtr;

/** \details
    <group OdEd_Classes>
*/
class ODRX_ABSTRACT TOOLKIT_EXPORT OdTvEdSSetTracker : public OdSSetTracker
{
public:
  ODRX_DECLARE_MEMBERS(OdTvEdSSetTracker);

  virtual bool append(OdDbStub* id, const OdDbSelectionMethod* pMethod);
  virtual bool remove(OdDbStub* id, const OdDbSelectionMethod* pMethod);

  virtual bool append(const OdTvDbObjectId& entId, const OdDbSelectionMethod* pMethod) = 0;
  virtual bool remove(const OdTvDbObjectId& entId, const OdDbSelectionMethod* pMethod) = 0;
};

typedef OdSmartPtr<OdTvEdSSetTracker> OdEdSSetTrackerPtr;


/** \details
    This class implements geometric interactive user IO functionality for custom interactive command objects.
    Corresponding C++ library: TD_Db
    <group OdTvDb_Classes>
*/
class ODRX_ABSTRACT TOOLKIT_EXPORT OdTvDbUserIO : public OdEdBaseUserIO
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbUserIO);

  virtual void setPickfirst(OdSelectionSet* pSSet) = 0;

  virtual OdSelectionSetPtr pickfirst() = 0;
    
  /** \details
    Returns user input of a color.

    \param prompt [in]  Message displayed to prompt the user.
    \param options [in]  Combination of OdEd::GetPointOptions enum values. 
    \param pDefaultValue [in]  Pointer to a default value to return if an empty string is received as input.
    \param keywords [in]  Keyword string.
    \param pTracker [in]  Pointer to a User IO tracker.
    
    \remarks
    This function uses the underlying OdEdBaseIO functions putString and getString for low
    level output and input.
    
    If prompt is an empty string, a default prompt string is used.  
  */
  virtual OdTvCmColor getColor(const OdString& prompt,
                             int options = OdEd::kInpDefault,
                             const OdTvCmColor* pDefaultValue = 0,
                             const OdString& keywords = OdString::kEmpty,
                             OdEdColorTracker* pTracker = 0) = 0;

  /** \details
      Launches interactive object selection to fill selection set.

      \param prompt [in]  Message displayed to prompt the user.
      \param options [in]  Combination of OdEd::GetPointOptions enum values. 
      \param pDefaultValue [in]  Pointer to a default value to return if an empty string is received as input.
      \param keywords [in]  Keyword string.
      \param pTracker [in]  Pointer to a User IO tracker.

      \remarks
      Each subsequent call to this function modifies current selection set.
      Returned value is guaranteed to be not null.
  */
  virtual OdSelectionSetPtr select(const OdString& prompt = OdString::kEmpty,
                                   int options = OdEd::kSelDefault,
                                   const OdSelectionSet* pDefaultValue = 0,
                                   const OdString& keywords = OdString::kEmpty,
                                   OdSSetTracker* pTracker = 0,
                                   OdGePoint3dArray* ptsPointer = NULL) = 0;
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbUserIO object pointers.
*/
typedef OdSmartPtr<OdTvDbUserIO> OdTvDbUserIOPtr;

#endif //#ifndef _ODDBUSERIO_H_INCLUDED_
