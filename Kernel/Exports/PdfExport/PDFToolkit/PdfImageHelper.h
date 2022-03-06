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




#ifndef _PDF_IMAGE_HELPER_INCLUDED_
#define _PDF_IMAGE_HELPER_INCLUDED_

#include "PdfCommon.h"
#include "RxRasterServices.h"
#include "Gi/GiRasterWrappers.h"

#include "PdfImage.h"
#include "PdfResourceDictionary.h"




namespace TD_PDF
{
  namespace TD_PDF_HELPER_FUNCS
  {
    void PDFEXPORT_TOOLKIT dcImageToPdfImage(OdGiRasterImagePtr pRaster, PDFImagePtr pImage, bool bTransparency, double brightness, double contrast, double fade
      , ODCOLORREF entityColor, PDFDocument &PDFDoc, ODCOLORREF bgColor, OdUInt16 quality, PDFResourceDictionaryPtr pResDict);

    PDFImagePtr PDFEXPORT_TOOLKIT addNewImage(PDFDocument &PDFDoc, PDFResourceDictionaryPtr pResDict, bool bMask = false);
  }
}
#endif // _PDF_IMAGE_HELPER_INCLUDED_

