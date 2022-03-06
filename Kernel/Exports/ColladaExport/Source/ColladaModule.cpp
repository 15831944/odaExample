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

#include "ColladaModule.h"
#include "ColladaExport.h"

using namespace TD_COLLADA_EXPORT;

//DD:EXPORT_ON
ODRX_DEFINE_DYNAMIC_MODULE(ColladaModule);
//DD:EXPORT_OFF

namespace TD_COLLADA_EXPORT
{
void ColladaModule::initApp()
{
}

void ColladaModule::uninitApp()
{
}

OdResult ColladaModule::exportCollada(OdDbBaseDatabase *pDb, 
  const OdString& pFileName, 
  const ODCOLORREF* pPallete, 
  int numColors, 
  const OdGeMatrix3d& matTransform,
  const std::map<OdDbStub*, double>* pMapDeviations,
  bool useDoublePrecision,
  bool exportWires,
  OdDbBaseHostAppServices* pHostApp)
{
  return TD_COLLADA_EXPORT::exportCollada(pDb, pFileName, pPallete, numColors, NULL, matTransform, pMapDeviations, useDoublePrecision, exportWires, pHostApp);
}

OdResult ColladaModule::exportCollada(OdDbBaseDatabase *pDb, 
  const OdGiDrawable &pEntity, 
  const OdString& pFileName, 
  const ODCOLORREF* pPallete, 
  int numColors, 
  const OdGeMatrix3d& matTransform,
  const std::map<OdDbStub*, double>* pMapDeviations,
  bool useDoublePrecision,
  bool exportWires,
  OdDbBaseHostAppServices* pHostApp)
{
  return TD_COLLADA_EXPORT::exportCollada(pDb, pFileName, pPallete, numColors, &pEntity, matTransform, pMapDeviations, useDoublePrecision, exportWires, pHostApp);
}
}
