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

#ifndef _IFC_GEOM_MODULE_IMPL_H_
#define _IFC_GEOM_MODULE_IMPL_H_

#include "OdPlatformSettings.h"
#include "ModuleNames.h"
#include "RxDynamicModule.h"

class OdIfcEntResolver;

/** \details 
Contains declarations related to working with IFC files content.
*/
namespace OdIfc {

/** \details 
A class that implements a module for working with IFC geometry. 
*/
class OdIfcGeomModule : public OdRxModule
{
public:

  /** \details 
  Initializes the IFC geometry module.
  */
  virtual void      initApp() = 0;
  
  /** \details 
  De-initializes the IFC geometry module.
  */
  virtual void      uninitApp() = 0;

  /** \details 
  Retrieves the current entity resolver object assigned to the module.
  \returns Returns a raw pointer to the entity resolver object.
  */
  virtual OdIfcEntResolver* getIfcEntResolver() = 0;

};

/** \details 
A data type that represents a smart pointer to an <link OdIfc::OdIfcGeomModule, OdIfcGeomModule> object.
*/
typedef OdSmartPtr<OdIfcGeomModule> OdIfcGeomModulePtr;

}

#endif // _IFC_GEOM_MODULE_IMPL_H_

