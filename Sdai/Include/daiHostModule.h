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

#ifndef DAI_HOST_MODULE_H
#define DAI_HOST_MODULE_H

#include "OdaCommon.h"
#include "RxModule.h"

#include "daiBuildOptions.h"

class OdExpSchemaModule;

class DAI_EXPORT OdDAIHostModule : public OdRxModule
{
public:
  
  /** \details
  Register .exprt module.
  \returns Returns eOk if .exprt module was successfully registered.
  */
  virtual OdResult registerSchemaModule(OdExpSchemaModule *expSchemaModule) = 0;

  /** \details 
  Retrieves if CDA is allowed for OdDAI host module.
  \returns Returns true if CDA is enabled.
  */
  virtual bool isCDAEnabled() = 0;
};
typedef OdSmartPtr<OdDAIHostModule> OdDAIHostModulePtr;


#endif
