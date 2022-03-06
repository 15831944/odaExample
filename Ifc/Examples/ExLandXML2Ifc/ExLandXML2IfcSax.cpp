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

#include "OdaCommon.h"

#include "ExLandXML2IfcConverter.h"
#include "ElementProcessor.h"

namespace OdLandXML2Ifc
{
  void _startDocumentSAXFunc(void *ctx)
  {
    odPrintConsoleString(L"\nLandXML2Ifc_startDocumentSAXFunc\n");
  }

  void _elementDeclSAXFunc(void *ctx,
    const xmlChar *name,
    int type,
    xmlElementContentPtr content)
  {
    odPrintConsoleString(L"\nelementDeclSAXFunc: %hs\n", name);
  }

  void _endDocumentSAXFunc(void *ctx)
  {
    odPrintConsoleString(L"\nLandXML2Ifc_endDocumentSAXFunc\n");
  }

  void _attributeDeclSAXFunc(
    void *ctx,
    const xmlChar *elem,
    const xmlChar *fullname,
    int type,
    int def,
    const xmlChar *defaultValue,
    xmlEnumerationPtr tree)
  {
    odPrintConsoleString(L"\nLandXML2Ifc_attributeDeclSAXFunc: %hs (%hs)\n", elem, fullname);
  }

  void _entityDeclSAXFunc(
    void *ctx,
    const xmlChar *name,
    int type,
    const xmlChar *publicId,
    const xmlChar *systemId,
    xmlChar *content)
  {
    odPrintConsoleString(L"\nLandXML2Ifc_attributeDeclSAXFunc: %hs\n", name);
  }

  void _startElementSAXFunc(void *ctx,
    const xmlChar *name,
    const xmlChar **attrs)
  {
    OdLandXML2IfcConverter *converter = reinterpret_cast<OdLandXML2IfcConverter*>(ctx);

    ElementProcessor *subProcessor = converter->pushProcessor(name);
    if (subProcessor)
      subProcessor->onStart(name, attrs);
    else
    {
      ElementProcessor *processor = converter->currentProcessor();
      if (processor)
        processor->onSubElement(name, attrs);
    }

    odPrintConsoleString(L"\nLandXML2Ifc_startElementSAXFunc: %hs\n", name);
  }

  void _endElementSAXFunc(
    void *ctx,
    const xmlChar *name)
  {
    OdLandXML2IfcConverter *converter = reinterpret_cast<OdLandXML2IfcConverter*>(ctx);

    ElementProcessor *processor = converter->currentProcessor();

#ifdef _DEBUG
    if (processor)
    {
      OdAnsiString name1 = (const char *)processor->name();
      if (name1 == "alignment")
      {
        int breakpoint = 1;
      }
    }
#endif

    if (processor /* && odStrICmpA((const char *)processor->name(), (const char *)name) == 0 */)
      converter->popProcessor(name);

    odPrintConsoleString(L"\nLandXML2Ifc_endElementSAXFunc: %hs\n", name);
  }

  void _charactersSAXFunc(
    void *ctx,
    const xmlChar *ch,
    int len)
  {
    OdLandXML2IfcConverter *converter = reinterpret_cast<OdLandXML2IfcConverter*>(ctx);
    ElementProcessor *processor = converter->currentProcessor();
    if (processor)
    {
      OdAnsiString subStr;
      strncpy(subStr.getBufferSetLength(len + 1), (const char *)ch, len);
      subStr.getBuffer(len + 1)[len] = 0;

      processor->onCharactersProcess(subStr);
    }
  }

  void _startElementNsSAX2Func(void *ctx,
    const xmlChar *localname,
    const xmlChar *prefix,
    const xmlChar *URI,
    int nb_namespaces,
    const xmlChar **namespaces,
    int nb_attributes,
    int nb_defaulted,
    const xmlChar **attributes)
  {
    odPrintConsoleString(L"\nLandXML2Ifc_startElementNsSAX2Func: %hs\n", localname);
  }

  void _endElementNsSAX2Func(void *ctx,
    const xmlChar *localname,
    const xmlChar *prefix,
    const xmlChar *URI)
  {
    odPrintConsoleString(L"\nLandXML2Ifc_endElementNsSAX2Func: %hs\n", localname);
  }

  //
  // SAX Parser configuration
  //
  xmlSAXHandlerPtr saxHandler()
  {
    static xmlSAXHandler sax;

    static bool initialized = false;
    if (!initialized)
    {
      memset(&sax, 0, sizeof(sax));

      //sax.internalSubset = _internalSubsetSAXFunc;
      //sax.isStandalone = _isStandaloneSAXFunc;
      //sax.hasInternalSubset = _hasInternalSubsetSAXFunc;
      //sax.hasExternalSubset = _hasExternalSubsetSAXFunc;
      //sax.resolveEntity = _resolveEntitySAXFunc ;
      //sax.getEntity = _getEntitySAXFunc;
      sax.entityDecl = _entityDeclSAXFunc;
      //sax.notationDecl = _notationDeclSAXFunc;
      sax.attributeDecl = _attributeDeclSAXFunc;
      sax.elementDecl = _elementDeclSAXFunc;
      //unparsedEntityDeclSAXFunc unparsedEntityDecl;
      //setDocumentLocatorSAXFunc setDocumentLocator;
      sax.startDocument = _startDocumentSAXFunc;
      sax.endDocument = _endDocumentSAXFunc;
      sax.startElement = _startElementSAXFunc;
      sax.endElement = _endElementSAXFunc;
      //sax.reference = _referenceSAXFunc;
      sax.characters = _charactersSAXFunc;
      //sax.ignorableWhitespace = _ignorableWhitespaceSAXFunc;
      //sax.processingInstruction = _processingInstructionSAXFunc;
      //sax.comment = _commentSAXFunc;
      //sax.warning = _warningSAXFunc;
      //sax.error = _errorSAXFunc;
      //sax.fatalError = _fatalErrorSAXFunc; /* unused error() get all the errors */
      //sax.getParameterEntity = _getParameterEntitySAXFunc;
      //sax.cdataBlock = _cdataBlockSAXFunc;
      //sax.externalSubset = _externalSubsetSAXFunc;
      //sax.initialized = 1;
      /* The following fields are extensions available only on version 2 */
      /*void *_private;*/
      sax.startElementNs = _startElementNsSAX2Func;
      sax.endElementNs = _endElementNsSAX2Func;
      //sax.serror = _xmlStructuredErrorFunc;

      initialized = true;
    }
    return &sax;
  }
}
