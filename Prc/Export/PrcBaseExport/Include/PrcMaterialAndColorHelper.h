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

// PrcMaterialAndColorHelper.h: interface for the PrcMaterialAndColorHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PRCMATERIALANDCOLORHELPER_H_INCLUDED_)
#define _PRCMATERIALANDCOLORHELPER_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PrcToolkitExportDef.h"
#include "BaseMaterialAndColorHelper.h"
#include "Pdf2PrcExportParams.h"
#include "PrcExportContext.h"

/** \details 
  The class implements resolving color and material operations during export to PRC format. 
  <group PRC_Export_Import_Classes>
*/
class OD_TOOLKIT_EXPORT PrcMaterialAndColorHelper : public OdBaseMaterialAndColorHelper
{
public:
  /** \details 
  Creates an instance of material and color helper. 
  \param params             [in] A set of PDF to PRC export parameters.
  \param pSourceDb          [in] A smart pointer to a source database.
  \param pDestinationDb     [in] A smart pointer to a destination database.
  \param pContext           [in] A smart pointer to an object that contains export context information.
  \param pDefaultMaterial   [in] A pointer to a data stream with information about default material.
  */
  explicit PrcMaterialAndColorHelper(
    const PDF2PRCExportParams * params,
    OdPrcExportContextPtr pContext,
    OdDbStub* pDefaultMaterial = NULL);

//DOM-IGNORE-BEGIN
protected:
  /** \details
  Return color specific to destinion database.
  \param sourceDbColor [in] color from source B-Rep.
  \param destinationDbColor [out] color for BrepBuilder.
  */
  virtual OdResult convertColor(
    const OdCmEntityColor& sourceDbColor,
    OdCmEntityColor& destinationDbColor
  ) ODRX_OVERRIDE;

  virtual OdDbStub * findMaterialInUserCache(const MaterialDataStore & matData) ODRX_OVERRIDE;
  virtual void addMaterialToUserCache(const MaterialDataStore & matData) ODRX_OVERRIDE;
private:
  OdPrcExportContextPtr m_pContext;
  const PDF2PRCExportParams * m_pParams;
//DOM-IGNORE-END
};

#endif // _PRCMATERIALANDCOLORHELPER_H_INCLUDED_

