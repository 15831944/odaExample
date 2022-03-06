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

#ifndef _PDF_3D_STREAM_EXTRACTOR_IMPL_INCLUDED_ 
#define _PDF_3D_STREAM_EXTRACTOR_IMPL_INCLUDED_

#include "Pdf3DStreamExtractor.h"


/** \details
  <group Pdf3DStreamExtractor_Classes> 

  This class implements the internal 3D streams extractor manager.
*/
class Pdf3DStreamExtractor : public OdPdf3DStreamExtractor
{
  FPDF_DOCUMENT                           m_pDocument;
  OdString                                m_Path;
  OdString                                m_Password;
  std::vector<std::vector<Stream3DInfo>>  m_StreamInfo;

public:
  /** Constructor. 
  */
  Pdf3DStreamExtractor();

  ~Pdf3DStreamExtractor();

  virtual ExtractResult openPdfDocument(const OdString& path, const OdString& password);

  virtual OdUInt32 getPageCount(ExtractResult& result) const;

  virtual OdUInt32 getCount3DStreamForPage(const int page_index, ExtractResult& result) const;

  virtual StreamType Get3DStreamType(const int page_index, const int stream_index, ExtractResult& result) const;

  virtual OdString Get3DStreamName(const int page_index, const int stream_index, ExtractResult& result) const;

  virtual ExtractResult fill3DStream(const int page_index, const int stream_index, OdStreamBufPtr& stream) const;

private:

  bool isDocumentLoaded() const;

  inline ExtractResult checkParams(const int page_index, const int stream_index) const
  {
    if (!isDocumentLoaded())
      return OdPdf3DStreamExtractor::document_not_loaded;

    if (page_index >= m_StreamInfo.size() || page_index < 0)
      return OdPdf3DStreamExtractor::invalid_page_number;


    if (stream_index >= m_StreamInfo[page_index].size() || stream_index < 0)
      return OdPdf3DStreamExtractor::invalid_stream_number;

    return OdPdf3DStreamExtractor::success;
  }

};

typedef OdSmartPtr<Pdf3DStreamExtractor> OdPdf3DStreamExtractorImplPtr;

#endif // _PDF_3D_STREAM_EXTRACTOR_IMPL_INCLUDED_
