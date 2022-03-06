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

#if !defined(ODA_ODMVDXMLUTILS_H_INCLUDED_)
#define ODA_ODMVDXMLUTILS_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OdaCommon.h"
#include "OdResult.h"
#include "MvdXmlRoot.h"

namespace OdMvdXml
{
  /** \details
    Array load template.
  */
  template<typename T>
  OdResult inFieldsArray(OdArray<OdSmartPtr<T> >& container, TiXmlNode* pParent, const char* pItemName)
  {
    for (TiXmlElement* pChild = pParent->FirstChildElement(); pChild; pChild = pChild->NextSiblingElement())
    {
      const char* name = pChild->Value();
      if (odStrICmpA(pItemName, name) == 0)
      {
        OdSmartPtr<T> pObj = T::createObject();
        if (pObj.isNull())
          return eNullPtr;

        RETURNNOTOK(pObj->inFields(pChild));

        container.append(pObj);
      }
    }
    return eOk;
  }

  template<typename T>
  OdResult outFieldsArray(OdArray<OdSmartPtr<T> >& container, TiXmlNode* pParent, const char* pGroupName)
  {
    if (container.length() > 0)
    {
      TiXmlNode* pItem;
      if (pGroupName)
      {
        pItem = new TiXmlElement(pGroupName);
        pParent->LinkEndChild(pItem);
      }
      else
        pItem = pParent;

      for (OdSmartPtr<T> item : container)
      {
        RETURNNOTOK(item->outFields(pItem));
      }
    }
    return eOk;
  }

}

#endif // !defined(ODA_ODMVDXMLUTILS_H_INCLUDED_)
