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




#ifndef _PDFFONT_INCLUDED_
#define _PDFFONT_INCLUDED_ /*!DOM*// 

#include "PdfDictionary.h"
#include "UInt16Array.h"

namespace TD_PDF
{

class PDFIStream;
class PDFVersion;

class PDFEXPORT_TOOLKIT PDFFont : public PDFDictionary
{
  // These members indicate that the font does not contain bold/italic glyphs as needed,
  // and as a result the text using these fonts should emulate these styles (e.g.
  // by drawing the text with thick outlines for bold style, or by applying a slanting
  // transform for italic style). These flags are not saved in the PDF file.
  bool m_bPseudoBold;
  bool m_bPseudoItalic;

  PDF_DECLARE_OBJECT(PDFFont, PDFDictionary, kFont)

protected:
  virtual void InitObject();
public:

  virtual bool truncateFont(OdUInt16 nFirstChar, OdUInt16 nLastChar);
  virtual bool truncateFont(OdUInt16 nFirstChar, OdUInt16 nLastChar, const OdUInt16Array &fontUsedUnicodeChars, bool bEmbedded = true);

  virtual void setPseudoBold(bool bBold) { m_bPseudoBold = bBold; };
  virtual void setPseudoItalic(bool bItalic) { m_bPseudoItalic = bItalic; };

  virtual bool isPseudoBold() const { return m_bPseudoBold; };
  virtual bool isPseudoItalic() const { return m_bPseudoItalic; };

#include "PdfDictKeysDefs.h"
#include "PdfFontKeys.h"
#include "PdfDictKeysUnDefs.h"

};

typedef PDFSmartPtr<PDFFont> PDFFontPtr;

};

#endif //_PDFFONT_INCLUDED_

