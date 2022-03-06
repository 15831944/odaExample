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

#ifndef _DAI_VALIDATION_TASK_LIST_H
#define _DAI_VALIDATION_TASK_LIST_H

#include "OdaCommon.h"
#include "daiValidationTask.h"
#include "RxObject.h"

#define STL_USING_LIST
#include "OdaSTL.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  Retrieves the list of the raw pointers to Rx-Objects of the all model validation tasks classes in library.
  \returns A list of raw pointers to Rx-Objects classes.
  */
  std::list<OdRxClass*> DAI_EXPORT daiModelValidationTasks();
  /** \details
  Retrieves the list of the raw pointers to Rx-Objects of the all instances validation tasks classes in library.
  \returns A list of raw pointers to Rx-Objects classes.
  */
  std::list<OdRxClass*> DAI_EXPORT daiInstanceValidationTasks();
  /** \details
  Retrieves the list of the raw pointers to Rx-Objects of the all extent validation tasks classes in library.
  \returns A list of raw pointers to Rx-Objects classes.
  */
  std::list<OdRxClass*> DAI_EXPORT daiExtentValidationTasks();
}
#endif // _DAI_VALIDATION_TASK_LIST_H
