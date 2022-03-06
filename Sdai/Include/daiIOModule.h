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

#ifndef _DAI_IO_MODULE_H_
#define _DAI_IO_MODULE_H_

#include "OdaCommon.h"
#include "RxDynamicModule.h"

#include "daiBuildOptions.h"

namespace OdDAI {
  class Repository;
}

/** \details
Class of input/output of particular file format for SDAI repository.
*/
class DAI_EXPORT OdDAIIOModule : public OdRxModule
{
public:

  /** \details
  Serializes the repository into file of supported format.
  */
  virtual OdResult serialize(const OdString &fileName, OdDAI::Repository *repo) = 0;

  /** \details
  Deserializes the repository from the file of supported format.
  */
  virtual OdResult deserialize(const OdString &fileName, OdDAI::Repository *repo) = 0;

};
typedef OdSmartPtr<OdDAIIOModule> OdDAIIOModulePtr;

class OdDAIIOModuleLoader : public OdRxObject
{
  OdString m_fileExtension;
  OdString m_ioModuleName;

public:

  ODRX_DECLARE_MEMBERS(OdDAIIOModuleLoader);

  void init(const OdString &fileExtension, const OdString &ioModuleName);

  const OdString& moduleName() { return m_ioModuleName; };

  OdDAIIOModulePtr getIOModule();
};
typedef OdSmartPtr<OdDAIIOModuleLoader> OdDAIIOModuleLoaderPtr;

#endif // _DAI_IO_MODULE_H_
