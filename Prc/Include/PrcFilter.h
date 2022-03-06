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

#ifndef _PRCFILTER_INCLUDED_
#define _PRCFILTER_INCLUDED_ 
 

#include "PrcContentLayerFilterItems.h"
#include "PrcContentEntityFilterItems.h"
#include "PrcUserData.h"

SMARTPTR(OdPrcFilter);

/** \details 
<group PRC_Files_Structures_Assemblies> 

Class stores information about the filtering of sub-parts inside a complex part.
*/
class PRC_TOOLKIT OdPrcFilter : public OdPrcReferencedBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcFilter)
  //DOM-IGNORE-END

  /** \details
  Returns current user defined data of the filter.
  User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData &userData();
  
  /** \details
  Returns current user defined data of the filter.  
  */
  const OdPrcUserData &userData() const;
  
  /** \details
  Returns current entity filter data.
  Entity filter data is returned as a reference to an OdPrcContentEntityFilterItems object, therefore it can be used to set new entity filter data.
  */
  OdPrcContentEntityFilterItems &contentEntityFilterItems();
  
  /** \details
  Returns current entity filter data.
  */
  const OdPrcContentEntityFilterItems &contentEntityFilterItems() const;
  
  /** \details
  Returns current layer filter data.
  Layer filter data is returned as a reference to an OdPrcContentLayerFilterItems object, therefore it can be used to set new layer filter data.
  */
  OdPrcContentLayerFilterItems &contentLayerFilterItems();
  
  /** \details
  Returns current layer filter data.
  */
  const OdPrcContentLayerFilterItems &contentLayerFilterItems() const;
  
  /** \details
  Sets a new value of the active flag. 
  The active flag indicates whether the filter is active (if true) or inactive (if false).

  \param is_active [in] A new value of the flag to be set.
  */
  void setIsActive(bool is_active);
  
  /** \details
  Returns the current value of the active flag.
  The active flag indicates whether the filter is active (if true) or inactive (if false).
  */
  bool isActive() const;
};

typedef OdArray<OdPrcFilter> OdPrcFilterArray;

#endif // _PRCFILTER_INCLUDED_

