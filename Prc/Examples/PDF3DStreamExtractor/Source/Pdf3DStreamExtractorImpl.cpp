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


#if defined(_MSC_VER)
// warning C4290: C++ Exception Specification ignored
#pragma warning ( disable : 4290 )
#if _MSC_VER <= 1200
// compiler stack overflows if these warning is enabled
#pragma warning ( disable : 4786)
#endif
#endif

#include "OdaCommon.h"
#include "oda_files/oda_functions.h"
#include "RxDispatchImpl.h"
#include "RxVariantValue.h"
#include "RxDynamicModule.h"
#include "StaticRxObject.h"
#include "Pdf3DStreamExtractorImpl.h"
#include "Ge/GeScale3d.h"
#include "OdPath.h"
#include "OdUtilAds.h"

#include <string>
#include <memory>
#include <functional>
#include "OdPlatform.h"
#include <set>


#if defined(_MSC_VER) && (_MSC_VER >= 1300)
#pragma warning(disable:4355)
#endif

Pdf3DStreamExtractor::Pdf3DStreamExtractor()
  : m_pDocument(nullptr)
{
}

Pdf3DStreamExtractor::~Pdf3DStreamExtractor()
{
  if (isDocumentLoaded())
  {
    FPDF_CloseDocument(m_pDocument);
  }
}

#define TOCHAR(a) ((char *)OdAnsiString(OdString(a)).c_str())

OdPdf3DStreamExtractor::ExtractResult Pdf3DStreamExtractor::openPdfDocument(const OdString& path, const OdString& password)
{
  if (isDocumentLoaded() && 0 == m_Path.compare(path) && 0 == m_Password.compare(password))
    return OdPdf3DStreamExtractor::success;
  
  m_Path = path;
  m_Password = password;

  m_pDocument = FPDF_LoadDocument(m_Path.c_str(), TOCHAR(m_Password.c_str()));

  if (nullptr == m_pDocument)
  {
    unsigned long error = FPDF_GetLastError();
    if (FPDF_ERR_PASSWORD == error)
      return OdPdf3DStreamExtractor::bad_password;
    return OdPdf3DStreamExtractor::fail;
  }

  FPDF_Fill_3D_StreamsInfo(m_pDocument, m_StreamInfo);

  return OdPdf3DStreamExtractor::success;
}

bool Pdf3DStreamExtractor::isDocumentLoaded() const
{
  return (nullptr != m_pDocument);
}

OdUInt32 Pdf3DStreamExtractor::getPageCount(ExtractResult& result) const
{
  if (!isDocumentLoaded())
  {
    result = OdPdf3DStreamExtractor::document_not_loaded;
    return 0;
  }
  result = OdPdf3DStreamExtractor::success;
  return (OdUInt32)m_StreamInfo.size();
}



OdUInt32 Pdf3DStreamExtractor::getCount3DStreamForPage(const int page_index, ExtractResult& result) const
{
  if (!isDocumentLoaded())
  {
    result = OdPdf3DStreamExtractor::document_not_loaded;
    return 0;
  }

  if(page_index >= m_StreamInfo.size() || page_index < 0)
  {
    result = OdPdf3DStreamExtractor::invalid_page_number;
    return 0;
  }   

  result = OdPdf3DStreamExtractor::success;
  return (OdUInt32)m_StreamInfo[page_index].size();
}

OdPdf3DStreamExtractor::StreamType Pdf3DStreamExtractor::Get3DStreamType(const int page_index, const int stream_index, ExtractResult& result) const
{
  result = checkParams(page_index, stream_index);
  if (OdPdf3DStreamExtractor::success != result)
    return StreamType::eUndefined;

  result = OdPdf3DStreamExtractor::success;
  return m_StreamInfo[page_index][stream_index].type == Stream3DType::kPRC? StreamType::ePRC : StreamType::eU3D;
}

OdString Pdf3DStreamExtractor::Get3DStreamName(const int page_index, const int stream_index, ExtractResult& result) const
{
  result = checkParams(page_index, stream_index);
  if (OdPdf3DStreamExtractor::success != result)
    return OdString();

  result = OdPdf3DStreamExtractor::success;
  return m_StreamInfo[page_index][stream_index].name.c_str();
}

OdPdf3DStreamExtractor::ExtractResult Pdf3DStreamExtractor::fill3DStream(const int page_index, const int stream_index, OdStreamBufPtr& stream) const
{
  const ExtractResult res = checkParams(page_index, stream_index);
  if (OdPdf3DStreamExtractor::success != res)
    return res;

  if(stream.isNull())
    return OdPdf3DStreamExtractor::fail;

  FPDF_Handle_3D_Streams(m_StreamInfo[page_index][stream_index].stream, [&stream](uint8_t* data, uint32_t data_len)
    {
      stream->putBytes(data, data_len);
    }
  );

  return OdPdf3DStreamExtractor::success;
}

class Pdf3DStreamExtractorModule : public OdPdf3DStreamExtractorModule
{
public:
  virtual void initApp()
  {
    FPDF_InitLibrary();
  }
  virtual void uninitApp()
  {
    FPDF_DestroyLibrary();
  }

  virtual OdPdf3DStreamExtractorPtr create()
  {
    return OdRxObjectImpl<Pdf3DStreamExtractor>::createObject();
  }

};

ODRX_DEFINE_DYNAMIC_MODULE(Pdf3DStreamExtractorModule)
