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

#if !defined(ODA_ODMVDXMLPROCESSOR_H_INCLUDED_)
#define ODA_ODMVDXMLPROCESSOR_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RxObject.h"
#include "mvdXMLBuildOptions.h"
#include "SharedPtr.h"
#include "IfcFile.h"
#include "Elements/MvdXmlRoot.h"
#include "tinyxml.h"

class TiXmlDocument;
typedef OdSharedPtr<TiXmlDocument> TiXmlDocumentPtr;

namespace OdMvdXml
{
  enum ProccesorType
  {
    kValidator,
    kFilter
  };

  class OdMvdXmlAuditInfo;

  class MVDXML_EXPORT OdMvdXmlProcessor : public OdRxObject
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlProcessor);

  public:
    OdMvdXmlRootPtr initRoot();
    virtual OdResult process(OdIfcFilePtr pFile, OdMvdXmlAuditInfo* pAudit) = 0;
    OdResult readFile(const OdString& filename, OdMvdXmlAuditInfo* pAudit, bool fixNamespace = false);
    OdResult writeFile(const OdString& filename, OdMvdXmlAuditInfo* pAudit);

  protected:
    OdMvdXmlRootPtr   m_pRoot;
  };
  typedef OdSmartPtr<OdMvdXmlProcessor> OdMvdXmlProcessorPtr;
}

#endif // !defined(ODA_ODMVDXMLPROCESSOR_H_INCLUDED_)

