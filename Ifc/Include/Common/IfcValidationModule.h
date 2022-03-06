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

#ifndef _IFC_VALIDATION_MODULE_H
#define _IFC_VALIDATION_MODULE_H

#include "OdaCommon.h"
#include "daiValidationTask.h"

#include "IfcValidationTaskCommon.h"

#define STL_USING_LIST
#include "OdaSTL.h"

#include "RxModule.h"

/** \details
A class that implements a module for working with IFC validation.
*/
class OdIfcValidationModule : public OdRxModule
{
public:

  /** \details
  Retrieves the list of the IFC model validation task classes.
  \returns A STD list of raw pointers to the OdRxClass.
  */
  virtual std::list<OdRxClass*> ifcModelValidationTasks() = 0;
  /** \details
  Retrieves the list of the IFC extent validation task classes.
  \returns A STD list of raw pointers to the OdRxClass.
  */
  virtual std::list<OdRxClass*> ifcExtentValidationTasks() = 0;
  /** \details
  Retrieves the list of the IFC instance validation task classes.
  \returns A STD list of raw pointers to the OdRxClass.
  */
  virtual std::list<OdRxClass*> ifcInstanceValidationTasks() = 0;

protected:
  /** \details
  Initialization of the IFC validation module.
  */
  virtual void initApp() = 0;
  /** \details
  Uninitialization of the IFC validation module.
  */
  virtual void uninitApp() = 0;
};
/** \details
A data type that represents a smart pointer to an <link OdDAI::OdIfcValidationModule, OdIfcValidationModule> object.
*/
typedef OdSmartPtr<OdIfcValidationModule> OdIfcValidationModulePtr;

#endif // _IFC_VALIDATION_MODULE_H
