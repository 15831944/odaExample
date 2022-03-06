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




#ifndef _PDFANNOTATIONDICTIONARY_INCLUDED_
#define _PDFANNOTATIONDICTIONARY_INCLUDED_ /*!DOM*// 

#include "PdfDictionary.h"
#include "PdfRectangle.h"
#include "PdfStream.h"

namespace TD_PDF
{

class PDFIStream;
class PDFVersion;

class PDFEXPORT_TOOLKIT PDFAnnotationDictionary : public PDFDictionary
{
  PDF_DECLARE_OBJECT(PDFAnnotationDictionary, PDFDictionary, kAnnotationDictionary)

protected:
  virtual void InitObject();

public:

#include "PdfDictKeysDefs.h"
#include "PdfAnnotationDictionaryKeys.h"
#include "PdfDictKeysUnDefs.h"

};

typedef PDFSmartPtr<PDFAnnotationDictionary> PDFAnnotationDictionaryPtr;

};

#endif //_PDFANNOTATIONDICTIONARY_INCLUDED_

