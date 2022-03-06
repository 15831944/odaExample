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


#ifndef _PDF_EXPORT_GIDRAWABLE_PE_DEF_INCLUDED_
#define _PDF_EXPORT_GIDRAWABLE_PE_DEF_INCLUDED_

#include "PdfExportGiDrawablePE.h"

/** \details 
A class for protocol extension with default implementation of the PDF export functionality of a Gi drawable entity.
This class reimplements the drawableToPRC() method of the PdfExportGiDrawablePE class. 
*/
class OD_TOOLKIT_EXPORT PdfExportGiDrawablePE_Default : public PdfExportGiDrawablePE
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Default);
  //DOM-IGNORE-END

  /** \details
  Exports a specified drawable entity to PRC format.
  \param pDrawable     [in] A raw pointer to the drawable to export.
  \param pPdfPrcParams [in] A raw pointer to an object that contains the set of export parameters.
  \param context       [in] A raw pointer to an object that contains the drawable context.
  \returns eOk if the drawable was successfully exported to PRC format; otherwise the method returns false.
  */
  virtual OdResult drawableToPRC(const OdGiDrawable *pDrawable,
    const PDF2PRCExportParams *pPdfPrcParams,
    OdRxObject *context
    ) const;
};

#endif //_PDF_EXPORT_GIDRAWABLE_PE_DEF_INCLUDED_
