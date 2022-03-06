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


#ifndef _PDF_3D_LIGHTING_SCHEME_DICTIONARY_INCLUDED_
#define _PDF_3D_LIGHTING_SCHEME_DICTIONARY_INCLUDED_

#include "PdfStreamDictionary.h"
#include "PdfRectangle.h"
#include "PdfStream.h"
#include "PdfNumber.h"
#include "PdfBoolean.h"

namespace TD_PDF
{

  class PDFIStream;
  class PDFVersion;

  class PDFEXPORT_TOOLKIT PDF3dLightingSchemeDictionary : public PDFDictionary
  {
    PDF_DECLARE_OBJECT(PDF3dLightingSchemeDictionary, PDFDictionary, k3DLightingSchemeDictionary)

    LightingMode m_Mode;

  protected:
    virtual void InitObject();

  public:
    virtual bool Export(PDFIStream *pStream, const PDFVersion &ver);
    void setSubtype(LightingMode mode);
    LightingMode getSubtype() const;

#include "PdfDictKeysDefs.h"
#include "Pdf3dLightingSchemeDictionaryKeys.h"
#include "PdfDictKeysUnDefs.h"

  };

  typedef PDFSmartPtr<PDF3dLightingSchemeDictionary> PDF3dLightingSchemeDictionaryPtr;
};

#endif //_PDF_3D_LIGHTING_SCHEME_DICTIONARY_INCLUDED_
