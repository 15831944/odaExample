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

#ifndef _IFC_MODELERGEOMETRYMODULE_H_
#define _IFC_MODELERGEOMETRYMODULE_H_

#include "IfcModelerBuildOptions.h"
#include "RxDynamicModule.h"
#include "IfcModelerGeometry.h"

/** \details
A module that contains the interface of the geometry modeler functionality for IFC SDK.
*/
class IFCMODELER_EXPORT OdIfcModelerGeometryModule : public OdRxModule
{
//DOM-IGNORE-BEGIN
protected:

  void initApp();
  void uninitApp();
//DOM-IGNORE-END

public:

  /** \details
  Creates an IFC SDK geometry modeler instance.
  Should be reimplemented in inherited classes.
  \returns A smart pointer to the created modeler object.
  */
  virtual OdIfc::OdIfcModelerGeometryPtr createModeler() = 0;

};

/** \details 
A data type that represents a smart pointer to an <link OdIfcModelerGeometryModule, OdIfcModelerGeometryModule> object.
*/
typedef OdSmartPtr<OdIfcModelerGeometryModule> OdIfcModelerGeometryModulePtr;

#endif // _IFC_MODELERMODULE_H
