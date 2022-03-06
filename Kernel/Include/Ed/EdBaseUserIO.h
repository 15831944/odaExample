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

#ifndef _EDBASEUSERIO_H_INCLUDED_
#define _EDBASEUSERIO_H_INCLUDED_

#include "OdPlatform.h"
#include "Ed/EdUserIO.h"
#include "SSet.h"
#include "TD_PackPush.h"

class OdSelectionSet;
class OdGsModel;

/** \details
    <group OdEd_Classes>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdSSetTracker : public OdEdInputTracker
{
public:
  ODRX_DECLARE_MEMBERS(OdSSetTracker);

  /** \details
    Called by select framework when an entity is going to be appended to working selection set.

    \param id [in]  Object id of the entity is going to be appended.
    \param pMethod [in]  Selection Method object, describing a method the entity was selected. 

    \returns
    flag indicating if the entity can be added to working selection set or not.
  */
  virtual bool append(OdDbStub* id, const OdDbSelectionMethod* pMethod);

  /** \details
    Called by select framework when an entity is going to be removed to working selection set.

    \param id [in]  Object id of the entity is going to be removed.
    \param pMethod [in]  Selection Method object, describing a method the entity was selected. 

    \returns
    flag indicating if the entity can be removed from working selection set or not.
  */
  virtual bool remove(OdDbStub* id, const OdDbSelectionMethod* pMethod);

  /** \details
    Called by selection framework. If returned true then append()/remove() would be called for every subentity.
  */
  virtual bool trackSubentities() const;

  /** \details
    Called by select framework when a subentity is going to be appended to working selection set.

    \param subEntPath [in]  Descriptor of the subentity is going to be appended.
    \param pMethod [in]  Selection Method object, describing a method a subentity was selected. 

    \returns
    flag indicating if the subentity can be added to working selection set or not.

    \remarks
    To enable calling this calback method OdSSetTracker::trackSubentities() should be overridden to return true.
  */
  virtual bool append(const OdDbBaseFullSubentPath& subEntPath, const OdDbSelectionMethod* pMethod);

  /** \details
    Called by select framework when a subentity is going to be removed from working selection set.

    \param subEntPath [in]  Descriptor of the subentity is going to be removed.
    \param pMethod [in]  Selection Method object, describing a method a subentity was selected. 

    \returns
    flag indicating if subentity can be removed to working selection set or not.

    \remarks
    To enable calling this calback method OdSSetTracker::trackSubentities() should be overridden to return true.
  */
  virtual bool remove(const OdDbBaseFullSubentPath& subEntPath, const OdDbSelectionMethod* pMethod);
};

typedef OdSmartPtr<OdSSetTracker> OdSSetTrackerPtr;

/** \details
    This class implements geometric interactive user IO functionality for custom interactive command objects.
    Corresponding C++ library: TD_Root
    <group OdEd_Classes>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdEdBaseUserIO : public OdEdUserIO
{
public:
  ODRX_DECLARE_MEMBERS(OdEdBaseUserIO);

  virtual OdGePoint3d getLASTPOINT() const = 0;

  virtual void setLASTPOINT(const OdGePoint3d& pt) = 0;

  virtual OdEdPointDefTrackerPtr createRubberBand(const OdGePoint3d& base,
                                                  OdGsModel* pModel = NULL) const = 0;

  virtual OdEdPointDefTrackerPtr createRectFrame(const OdGePoint3d& base,
                                                 OdGsModel* pModel = NULL) const = 0;

  /** \details
    Returns user input of a point.

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
  virtual OdGePoint3d getPoint(const OdString& prompt,
                               int options = OdEd::kGptDefault,
                               const OdGePoint3d* pDefaultValue  = 0,
                               const OdString& keywords = OdString::kEmpty,
                               OdEdPointTracker* pTracker = 0) = 0;

  /** \details
    Returns user input of an angle.

    \param prompt [in]  Message displayed to prompt the user.
    \param options [in]  Combination of OdEd::GetPointOptions enum values. 
    \param defaultValue [in]  Default value to return if an empty string is received as input.
    \param keywords [in]  Keyword string.
    \param pTracker [in]  Pointer to a User IO tracker.
    
    \remarks
    This function uses the underlying OdEdBaseIO functions putString and getString for low
    level output and input.
    
    If prompt is an empty string, a default prompt string is used.  
    
    \remarks
    All angles are expressed in radians.
  */
  virtual double getAngle(const OdString& prompt,
                          int options = OdEd::kInpDefault,
                          double defaultValue = 0.0,
                          const OdString& keywords = OdString::kEmpty,
                          OdEdRealTracker* pTracker = 0) = 0;

  /** \details
    Returns user input of a distance.

    \param prompt [in]  Message displayed to prompt the user.
    \param options [in]  Combination of OdEd::GetPointOptions enum values. 
    \param defaultValue [in]  Default value to return if an empty string is received as input.
    \param keywords [in]  Keyword string.
    \param pTracker [in]  Pointer to a User IO tracker.
   
    \remarks
    This function uses the underlying OdEdBaseIO functions putString and getString for low
    level output and input.
    
    If prompt is an empty string, a default prompt string is used.  
  */
  virtual double getDist(const OdString& prompt,
                         int options = OdEd::kInpDefault,
                         double defaultValue = 0.0,
                         const OdString& keywords = OdString::kEmpty,
                         OdEdRealTracker* pTracker = 0) = 0;
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbUserIO object pointers.
*/
typedef OdSmartPtr<OdEdBaseUserIO> OdEdBaseUserIOPtr;

#include "TD_PackPop.h"
#endif //#ifndef _EDBASEUSERIO_H_INCLUDED_
