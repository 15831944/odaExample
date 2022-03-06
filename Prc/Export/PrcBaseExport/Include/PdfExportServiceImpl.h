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


#ifndef _PDFEXPORTSERVICEIMPL_BASE_INCLUDED_
#define _PDFEXPORTSERVICEIMPL_BASE_INCLUDED_

#include "PdfExportService.h"
#include "TD_PackPush.h"

  /** \details 
  The class provides an implementation of the helper service functionality for PDF export. 
  <group PRC_Export_Import_Classes>
  */
class PdfExportServiceInterface_Impl : public PdfExportServiceInterface
{
public:  
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE(PdfExportServiceInterface_Impl);
  //DOM-IGNORE-END

  /** \details 
  Destroys the PDF export service interface object.
  */
  virtual ~PdfExportServiceInterface_Impl() {}
  
  /** \details 
    Creates a new instance of the PRC export context.
    \param pDb [in] A raw pointer for the resident drawing database for the created context object.
    \returns A smart pointer to the newly created export context object represented with an OdRxObject instance.
  */  
  virtual OdRxObjectPtr createPrcExportContext(OdDbBaseDatabase *pDb);
  
  /** \details 
    Exports specified drawable entity to PDF format as PRC content with specifies parameters.
    \param context    [out] A PRC context object.
    \param pDrawable  [in] A raw pointer to a drawable entity.
    \param params     [in] A raw pointer to an object that encapsulates a set of parameters for export.
    \returns eOk if the export was successful; otherwise, the method returns an appropriate error.
  */
  virtual OdResult exportPrc(OdRxObjectPtr &context, const OdGiDrawable *pDrawable, const PDF2PRCExportParams * params);
  
    /** \details 
    Serializes the PRC export context with specified export parameters.
    \param pBuffer [in] A smart pointer to a stream buffer to serialize data in.
    \param context [in] A smart pointer to a context object to be serialized.
    \param params  [in] A raw pointer to an object that encapsulates a set of parameters for export.
    \returns eOk if the context object was successfully serialized; otherwise, the method returns an appropriate error.
  */
  virtual OdResult serialize(OdStreamBufPtr pBuffer, OdRxObjectPtr context, const PDF2PRCExportParams *params);
};

#include "TD_PackPop.h"

#endif // _PDFEXPORTSERVICEIMPL_BASE_INCLUDED_
