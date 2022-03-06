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

#ifndef _BFC_MODULE_H
#define _BFC_MODULE_H

#include "OdPlatformSettings.h"
#include "IfcBuildOptions.h"

#include "RxModule.h"
#include "SmartPtr.h"

/** \details
Initializes BCF SDK functionality.
\returns eOk if BCF SDK was successfully initialized; otherwise, the function returns an appropriate error code.
\remarks
The function checks whether all needed modules are loaded and loads them if they are not.
If at least one of the necessary modules is not loaded, the function returns the eNullPtr error code.
*/
BCF_EXPORT OdResult odBcfInitialize();

/** \details
De-initializes BCF SDK functionality.
\returns Returns eOk if BCF SDK was successfully de-initialized; otherwise, the function returns an appropriate error code.
\remarks
The function checks whether the needed modules are loaded and decreases the reference counters for them.
If a reference counter for any appropriate module becomes equal to zero, the function unloads the module.
If no BCF-related modules are loaded, the function returns the eNullPtr error code.
*/
BCF_EXPORT OdResult odBcfUninitialize();

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

/** \details
An abstract class that provides the interface for a module that contains BCF functionality.
*/
class BCF_EXPORT OdBcfModule : public OdRxModule
{
public:

  /** \details 
  Initializes the BCF module.
  */
  virtual void initApp();
  
  /** \details 
  De-initializes the BCF module.
  */
  virtual void uninitApp();
};

/** \details 
A data type that represents a smart pointer to an <link OdBcf::OdBcfModule, OdBcfModule> object.
*/
typedef OdSmartPtr<OdBcfModule> OdBcfModulePtr;

} //namespace OdBcf

#endif // _BFC_MODULE_H
