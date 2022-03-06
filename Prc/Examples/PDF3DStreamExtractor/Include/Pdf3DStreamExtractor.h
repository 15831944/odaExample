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

#ifndef _PDF_3D_STREAM_EXTRACTOR_INCLUDED_
#define _PDF_3D_STREAM_EXTRACTOR_INCLUDED_

#include "RxModule.h"
#include "RxDictionary.h"
#include "DynamicLinker.h"

//////////////////////////////////////////////////////////////////////////

#include "OdPlatformSettings.h"
#include "PrcModuleNames.h"

#ifdef PDF_3D_STREAM_EXTRACTOR_EXPORTS
  #define PDF_3D_STREAM_EXTRACTOR_TOOLKIT         OD_TOOLKIT_EXPORT
  #define PDF_3D_STREAM_EXTRACTOR_STATIC  OD_STATIC_EXPORT
#else                               
  #define PDF_3D_STREAM_EXTRACTOR_TOOLKIT         OD_TOOLKIT_IMPORT
  #define PDF_3D_STREAM_EXTRACTOR_TOOLKIT_STATIC  OD_STATIC_IMPORT
#endif

//////////////////////////////////////////////////////////////////////////

//DD:EXPORT_ON

/** \details
An abstract class that represents the interface for the extract 3D stream from a .pdf file.
<group OdPdf3DStreamExtractor_Classes>
*/
class OdPdf3DStreamExtractor : public OdRxObject
{
public:
  /** \details 
  Defines a list with possible results of the extract 3D stream data operation. 
  The result value is handled by a <link OdPdf3DStreamExtractorModule, module that contains 3D stream data extraction functionality>.
  */
  enum ExtractResult 
  {
    /** The extraction process has been successfully finished.*/
    success, 
    /**The extraction process failed.*/
    fail, 
    /** The extraction process failed because of an incorrect password.*/
    bad_password, 
    /** The extraction process failed because of an incorrect input .pdf file.*/
    bad_file, 
    /** The extraction process failed because of an invalid page number of the input .pdf file.*/
    invalid_page_number,
    /** The extraction process failed because of an invalid stream number in the input .pdf file.*/
    invalid_stream_number,
    /** The extraction process failed because the .pdf document was not loaded.*/
    document_not_loaded
  };

  /** \details
  Defines a list of 3D stream types to be extracted. 
  Stream type value is handled by a <link OdPdf3DStreamExtractorModule, module that contains 3D stream data extraction functionality>.
  */
  enum StreamType
  {
    /**PRC stream type.*/
    ePRC,
    /**U3D stream type.*/
    eU3D,
    /**Undefined stream type.*/
    eUndefined
  };

  /** \details
  Opens a PDF document.
  \param path     [in] A reference to an <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> object that contains the path to the PDF document.
  \param password [in] A reference to an <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> object that contains the password for the PDF document.
  \returns A value of the <link OdPdf3DStreamExtractor::ExtractResult, ExtractResult> enumeration that contains the result of the process.
  */
  virtual ExtractResult openPdfDocument(const OdString& path, const OdString& password) = 0;

  /** \details
  Requests the number of pages in the PDF document.
  \param result [out] A reference to a value of the <link OdPdf3DStreamExtractor::ExtractResult, ExtractResult> enumeration that contains the result of the method execution.
  \returns An unsigned 32-bit integer value that contains the number of pages in the PDF document.
  */
  virtual OdUInt32 getPageCount(ExtractResult& result) const = 0;

  /** \details
  Requests the number of 3D streams that are contained within a specified page of the PDF document.
  \param page_index [in] A page index within the PDF document.
  \param result     [out] A reference to a value of the <link OdPdf3DStreamExtractor::ExtractResult, ExtractResult> enumeration that contains the result of the method execution.
  \returns An unsigned 32-bit integer value that contains the number of 3D streams within the specified page of the PDF document.
  */
  virtual OdUInt32 getCount3DStreamForPage(const int page_index, ExtractResult& result) const = 0;

  /** \details
  Requests the type of a specified 3D stream.
  \param page_index   [in] A page index within the PDF document.
  \param stream_index [in] An index of the stream contained in the PDF document.
  \param result       [out] A reference to a value of the <link OdPdf3DStreamExtractor::ExtractResult, ExtractResult> enumeration that contains the result of the method execution.
  \returns A value of the <link OdPdf3DStreamExtractor::StreamType, StreamType> enumeration that contains the type of the specified 3D stream.
  */
  virtual StreamType Get3DStreamType(const int page_index, const int stream_index, ExtractResult& result) const = 0;

  /** \details
  Requests the name of a specified 3D stream.
  \param page_index   [in] A page index within the PDF document.
  \param stream_index [in] An index of the stream contained in the PDF document.
  \param result       [out] A reference to a value of the <link OdPdf3DStreamExtractor::ExtractResult, ExtractResult> enumeration that contains the result of the method execution.
  \returns An <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> object that contains the name of the specified 3D stream.
  \remarks
  If there is no name for the stream in the PDF document, the default name 3D_&lt;stream_number_in_the_document&gt; is returned (e.g. 3D_1, 3D_2, etc.).
  */
  virtual OdString Get3DStreamName(const int page_index, const int stream_index, ExtractResult& result) const = 0;

  /** \details
  Fills a specified <exref target="https://docs.opendesign.com/tkernel/OdStreamBuf.html">OdStreamBuf</exref> object with data from a specified 3D stream.
  \param page_index   [in] A page index within the PDF document.
  \param stream_index [in] An index of the stream contained in the PDF document.
  \param stream       [out] A reference to a smart pointer to an <exref target="https://docs.opendesign.com/tkernel/OdStreamBuf.html">OdStreamBuf</exref> object to be filled with the 3D stream data.
  \returns A value of the <link OdPdf3DStreamExtractor::ExtractResult, ExtractResult> enumeration that contains the result of the method execution.
  */
  virtual ExtractResult fill3DStream(const int page_index, const int stream_index, OdStreamBufPtr& stream) const = 0;
};

/** \details
A data type that represents a smart pointer to a <link OdPdf3DStreamExtractor, PDF 3D stream extractor> object.
*/
typedef OdSmartPtr<OdPdf3DStreamExtractor> OdPdf3DStreamExtractorPtr;

/** \details
An abstract class that provides an interface of a module containing the functionality for extraction 3D stream data from a PDF file. 
<group OdPdf3DStreamExtractor_Classes> 
*/
class OdPdf3DStreamExtractorModule : public OdRxModule
{
public:
    
    /** \details
    Creates an extractor object for 3D streams contained in a PDF file if it has not been created yet (at the moment of the method call). 
    If the extractor object has already been created, the method only returns the smart pointer to it.
    \returns A smart pointer to the <link OdPdf3DStreamExtractor, extractor object> for 3D streams in a PDF file. 
    */
    virtual OdPdf3DStreamExtractorPtr create () = 0;
    
};

/** \details
A data type that represents a smart pointer to a <link OdPdf3DStreamExtractorModule, module object that provides 3D stream data extraction functionality>.
*/
typedef OdSmartPtr<OdPdf3DStreamExtractorModule> OdPdf3DStreamExtractorModulePtr;


/** \details 
Creates a new <link OdPdf3DStreamExtractor, object-extractor of 3D stream data from a PDF file>.
\returns A smart pointer to the created instance of the <link OdPdf3DStreamExtractor, OdPdf3DStreamExtractor> class. 
<group OdPdf3DStreamExtractor_Classes>
*/
inline OdPdf3DStreamExtractorPtr createExtractor()
{
     OdPdf3DStreamExtractorModulePtr pModule = ::odrxDynamicLinker()->loadApp(OdPdf3DStreamExtractorModuleName);
     if ( !pModule.isNull() ) return pModule->create ();
     return (OdPdf3DStreamExtractor*)0;
}

//DD:EXPORT_OFF

#endif // _PDF_3D_STREAM_EXTRACTOR_INCLUDED_
