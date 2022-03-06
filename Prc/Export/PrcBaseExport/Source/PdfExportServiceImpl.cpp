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

#include "PrcCommon.h"
#include "PrcCompressedFiler.h"
#include "PrcBrepData.h"
#include "PdfExportServiceImpl.h"
#include "RxObjectImpl.h"
#include "DynamicLinker.h"
#include "Ge/GeExtents3d.h"
#include "PrcFile.h"
#include "RxVariantValue.h"
#include "PrcExport.h"
#include "PrcExportContext.h"
#include "PdfExportGiDrawablePE.h"

ODRX_CONS_DEFINE_MEMBERS(PdfExportServiceInterface_Impl, PdfExportServiceInterface, RXIMPL_CONSTR);

OdRxObjectPtr PdfExportServiceInterface_Impl::createPrcExportContext(OdDbBaseDatabase *pDb)
{
  OdPrcExportContextPtr pContext = OdPrcExportContext::createObject();
  pContext->setDatabase(pDb);
  return pContext;
}

OdResult PdfExportServiceInterface_Impl::exportPrc(OdRxObjectPtr &context, const OdGiDrawable *pDrawable, const PDF2PRCExportParams * params)
{
  if (context.isNull())
  {
    return eInvalidInput;
  }

  if (!pDrawable)
  {
    return eInvalidInput;
  }

  PdfExportGiDrawablePEPtr ex = PdfExportGiDrawablePE::cast(pDrawable);
  if (ex.isNull())
  {
    return eNotImplementedYet;
  }
  return ex->drawableToPRC(pDrawable, params, context.get());
}


OdResult exportWritePrc(const PDF2PRCExportParams &params, const OdRxObject *pContext, OdStreamBuf* pOut)
{
  // cast rxobject to context
  OdPrcExportContextPtr ptrContext = pContext;
  if (ptrContext.isNull())
  {
    return eInvalidContext;
  }

  // write file
  OdPrcFilePtr pFile = ptrContext->getFile();
  try
  {
    OdPrcFileSettings pSettings;
    PDF3D_ENUMS::PRCCompressionLevel compressionLev;
    bool hasCompression = params.hasPrcBrepCompression(compressionLev);
    pSettings.setCompressTopoBrepsFlag(hasCompression);
    bool hasTessCompression = params.hasPrcTessellationCompression();
    pSettings.setCompressTessellationFlag(hasTessCompression);

    switch (compressionLev)
    {
    case PDF3D_ENUMS::kA3DLooseCompression:
    {
      pSettings.setCompressTopoBrepTolerance(0.001);
      break;
    }
    case PDF3D_ENUMS::kA3DMeddiumCompression:
    {
      pSettings.setCompressTopoBrepTolerance(0.01);
      break;
    }
    case PDF3D_ENUMS::kA3DHighCompression:
    {
      pSettings.setCompressTopoBrepTolerance(0.1);
      break;
    }
    }

    if (pOut)
    {
      pFile->writeFile(pOut, &pSettings);
    }
    else
    {
      pFile->compressFile(pSettings);
    }
  }
  catch (OdError &e)
  {
    return e.code();
  }
  catch (...)
  {
    return eExtendedError;
  }

  return eOk;
}

OdResult PdfExportServiceInterface_Impl::serialize(OdStreamBufPtr pBuffer, OdRxObjectPtr context, const PDF2PRCExportParams *params)
{
#if 0
  OdResult res = exportWritePrc(*params, context, pBuffer);
  if (pBuffer->length() > 0)
  {
    pBuffer->rewind();
    OdStreamBufPtr pS = odrxSystemServices()->createFile(L"D:\\1.prc", Oda::kFileWrite, Oda::kShareDenyNo, Oda::kCreateAlways);
    pBuffer->copyDataTo(pS);
    pBuffer->rewind();
  }
  return res;
#else
  return exportWritePrc(*params, context, pBuffer);
#endif
}

PdfExportServiceInterface_Impl::PdfExportServiceInterface_Impl()
{
}
