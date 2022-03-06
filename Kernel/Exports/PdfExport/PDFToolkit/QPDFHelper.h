/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance"). 
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



//////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////

#ifndef _PDF_QPDFHELPER_
#define _PDF_QPDFHELPER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OdStreamBuf.h"
#include "PdfVersion.h"


//////////////////////////////////////////////////////////////////////

/** \details
  <group OdExport_Classes> 
*/
namespace TD_PDF {

  namespace TD_PDF_HELPER_FUNCS
  {
    /** \details
    Access permissions params for the PDF document
    */
    struct PDFAccessPermissionsParams
    {
      /** Allows copy or otherwise extract text and graphics from the document*/
      bool AllowExtract;
      /** Allows assemble the document (insert, rotate, or delete pages and create bookmarks or thumbnail images), even if kAllowModifyOther is clear.*/
      bool AllowAssemble;
      /** Allows add/modify annotations (comment), fill in interactive form fields, and, if kAllowModifyOther is also set,
      create or modify interactive form fields (including signature fields).*/
      bool AllowAnnotateAndForm;
      /** Allows fill in existing interactive form fields (including signature fields), even if kAllowAnnotateAndForm is clear*/
      bool AllowFormFilling;
      /** Allows modify the contents of the document by operations other than those controlled by flags kAllowAssemble, kAllowAnnotateAndForm, and kAllowFormFilling.*/
      bool AllowModifyOther;
      /** Allows print the document to a representation from which a faithful digital copy of the PDF content could be generated.*/
      bool AllowPrintAll;
      /** Allows print the document (possibly not at the highest quality level). Ignored if kAllowPrintAll is set.*/
      bool AllowPrintLow;

      PDFAccessPermissionsParams()
        : AllowExtract(false)
        , AllowAssemble(false)
        , AllowAnnotateAndForm(false)
        , AllowFormFilling(false)
        , AllowModifyOther(false)
        , AllowPrintAll(false)
        , AllowPrintLow(false)
      {

      }
    };

    /** \details
      QPDF wrapper for PDF export.
    */
    namespace QPDFHelper
    {
      void PDFEXPORT_TOOLKIT process(OdStreamBufPtr& inStream, OdStreamBufPtr& outStream, const bool linearize,
        const OdString& user_password, const OdString& owner_password, const PDFAccessPermissionsParams& access_permission_params,
        const PDFVersion version);
    };

  }

}
#endif // #ifndef _PDF_QPDFHELPER_
