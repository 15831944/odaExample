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


///////////////////////////////////////////////////////////////////////////////
//
// PrcExport.h - Open Design Prc Export definitions
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PRC_EXPORT_INCLUDED_
#define _PRC_EXPORT_INCLUDED_

#include "Pdf2PrcExportParams.h"
#include "OdStreamBuf.h"
#include "DbBaseDatabase.h"
#include "PrcTriangleInfo.h"
#include "PrcExportContext.h"

  /** \details
  Export mesh into prc file (into context), prc file (from context) into stream, or both - depending on export params.
  \param mesh     [in] An array with triangleInfo structs that represents the mesh.
  \param pContext [in] An output context (PRCExportContext) to write entity's data to.
  \returns eOk if the export is successfully done or an appropriate error code in the other case.
  <group PRC_Export_Functions> 
  */
  OdResult OD_TOOLKIT_EXPORT exportMeshToPrc(const TriangleInfoPtrArray &mesh, OdRxObject *pContext);

  /** \details
  Export pDrawable as mesh into prc file (into context), prc file (from context) into stream, or both - depending on export params.
  \param pDrawable [in] A pointer to an entity to export.
  \param pDb       [in] A pointer to a database where the exported entity is allocated.
  \param params    [in] Export parameters.
  \param pContext  [in] An output context (PRCExportContext) to write entity's data to.
  \returns eOk if the export is successfully done or an appropriate error code in the other case.
  <group PRC_Export_Functions> 
  */
  OdResult OD_TOOLKIT_EXPORT exportMeshToPrc(const OdGiDrawable *pDrawable, const PDF2PRCExportParams &params, OdRxObject *pContext);

#endif // _PRC_EXPORT_INCLUDED_
