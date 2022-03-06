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

#ifndef _DAI_PAGER_H_
#define _DAI_PAGER_H_

#include "daiObjectId.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {
  

  /** \details
  Helper for application instances loading/unloading 
  */
  class DAI_EXPORT Pager 
  {
  public:
    /** \details
    Unload enitity by Id.
    \param id [in] an object id which should be unloaded
    \returns Returns eOk if success, otherwise it should return an error code
    */
    OdResult unload(const OdDAIObjectId& id);

    /** \details
    Unloads enitites.
    \param ids [in] an array of object ids which should be unloaded
    \returns Returns eOk if success, otherwise it should return an error code
    */
    OdResult unload(const OdDAIObjectIds& ids);
  };

}

#endif // _DAI_APPLICATION_INSTANCE_H_
