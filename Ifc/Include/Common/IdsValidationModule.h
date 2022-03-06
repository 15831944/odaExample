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

#ifndef _IDS_VALIDATION_MODULE_H
#define _IDS_VALIDATION_MODULE_H

#include "OdaCommon.h"
#include "daiValidationTask.h"
#include "daiInstanceValidationTask.h"
#include "daiExtentValidationTask.h"

#define STL_USING_LIST
#include "OdaSTL.h"

#include "RxModule.h"

/** \details
A class that implements a module for working with IDS validation.
*/
class OdIdsValidationModule : public OdRxModule
{
public:
  /** \details
  Load validation tasks to the module from an IDS file.
  \param model [in] Path to the IDS file.
  */
  virtual void loadFile(OdAnsiString path) = 0;

  virtual std::map<OdAnsiString, std::list<OdDAI::ValidationTaskPtr> > idsValidationTasks() = 0;

  /** \details
  Removes all validation tasks from module.
  */
  virtual void clearValidationTaskLists() = 0;
protected:
  /** \details
  Initialization of the IDS validation module.
  */
  virtual void initApp() = 0;
  /** \details
  Uninitialization of the IDS validation module.
  */
  virtual void uninitApp() = 0;
};
/** \details
A data type that represents a smart pointer to an <link OdDAI::OdIdsValidationModule, OdIdsValidationModule> object.
*/
typedef OdSmartPtr<OdIdsValidationModule> OdIdsValidationModulePtr;

#endif // _IFC_VALIDATION_MODULE_H
