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

#ifndef _IFC_CORE_TOOLS_H
#define _IFC_CORE_TOOLS_H

#include "RxModule.h"
#include "IfcBuildOptions.h"

#include "OdaCommon.h"
#include "DynamicLinker.h"

#include "daiModel.h"

class OdBrBrep;

/** \details
An abstract class that provides the interface for a module that implements core tools IFC functionality.
*/
class IFCCORETOOLS_EXPORT OdIfcCoreToolsModule : public OdRxModule
{
public:

  /** \details
  Initializes the core tools IFC module.
  */
  virtual void initApp();

  /** \details
  De-initializes the core tools IFC module.
  */
  virtual void uninitApp();
};

/** \details
Adds brep object to the model as new shape representation. If shape representation is already create, adds IfcAdvancedBrep to it; otherwice creats new shape representation.
\param brep            [in] A brep object.
\param pModel          [in] A raw pointer to the instance of the <link , OdIfcModel> class that represents the current model of the file.
\param shapeId         [in/out] A placeholder for the identifier of the created shape representation object. If shapeId is zero creates new IfcProductDefinitionShape and sets it identifier.
\param surfacesAsNurbs [in] If parameter is true all surfaces crearted as a nurbs; otherwise surfaces crearted of the same type as in the brep if it posible.
\returns eOk if the shape representation object was successfully created; otherwise, the function returns an appropriate error code.
\remarks
Beta version of brep objects to ifc conversion.
*/
IFCCORETOOLS_EXPORT OdResult addBrep2Model(const OdBrBrep& brep,
  OdDAI::Model* pModel,
  OdDAIObjectId& shapeId,
  bool surfacesAsNurbs = false);
#endif //_IFC_CORE_TOOLS_H
