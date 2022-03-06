/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance"). 
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
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
// ColorListCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "GenDlg.h"
#include "CDAPropertiesListCtrl.h"
#include "DbRootValueTypes.h"
#include "DgValueTypes.h"
#include "DgColorTable.h"
#include "RxProperty.h"
#include "RxValue.h"
#include "OdaCommon.h"
#include "OdSetLocale.h"
#include "CDAPropertiesDlg.h"

/////////////////////////////////////////////////////////////////////////////

bool getSimpleValue(OdRxObject* pObject, const OdRxPropertyBase* pProperty, OdInt32 iArrayIndex, OdRxValue& propValue)
{
  if (pProperty->isKindOf(OdRxProperty::desc()))
  {
    OdRxPropertyPtr pSimpleProp = pProperty;

    if (pSimpleProp->getValue(pObject, propValue) != eOk)
      return false;
  }
  else if (pProperty->isKindOf(OdRxIndexedProperty::desc()) && (iArrayIndex >= 0))
  {
    OdRxIndexedPropertyPtr pIndexedProp = pProperty;

    if (pIndexedProp->getValue(pObject, iArrayIndex, propValue) != eOk)
      return false;
  }
  else if (pProperty->isKindOf(OdRxCollectionProperty::desc()) && (iArrayIndex >= 0))
  {
    OdRxCollectionPropertyPtr pCollectionProp = pProperty;

    OdRxValueIteratorPtr pValIter = pCollectionProp->newValueIterator(pObject);

    bool bGetValue = false;

    if (!pValIter.isNull())
    {
      OdUInt32 iCount = 0;

      for (; !pValIter->done(); pValIter->next())
      {
        if (iCount == iArrayIndex)
        {
          propValue = pValIter->current();
          bGetValue = true;
          break;
        }
        iCount++;
      }
    }

    if (!bGetValue)
      return false;
  }
  else
    return false;

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool setSimpleValue(OdRxObject* pObject, OdRxPropertyBase* pProperty, OdInt32 iArrayIndex, OdRxValue& propValue)
{
  bool bRet = false;

  if (pProperty->isKindOf(OdRxProperty::desc()))
  {
    OdRxPropertyPtr pSimpleProp = pProperty;

    if (pSimpleProp->setValue(pObject, propValue) != eOk)
      return false;
  }
  else if (pProperty->isKindOf(OdRxIndexedProperty::desc()) && (iArrayIndex >= 0))
  {
    OdRxIndexedPropertyPtr pIndexedProp = pProperty;

    if (pIndexedProp->setValue(pObject, iArrayIndex, propValue) != eOk)
      return false;
  }
  else
    return false;

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool insertSimpleValueToEnd(OdRxObject* pObject, OdRxPropertyBase* pProperty, OdRxValue& propValue)
{
  bool bRet = false;

  if( pProperty->isKindOf(OdRxIndexedProperty::desc()) )
  {
    OdRxIndexedPropertyPtr pIndexedProp = pProperty;

    int iCount = -1;

    if( pIndexedProp->tryGetCount(pObject, iCount) != eOk )
    {
      OdRxValueIteratorPtr pIter = pIndexedProp->newValueIterator(pObject);

      if( !pIter.isNull() )
      {
        iCount = 0;

        for (; !pIter->done(); pIter->next())
          iCount++;
      }
    }

    if( (iCount < 0) || pIndexedProp->insertValue(pObject, iCount, propValue) != eOk)
      return false;
  }
  else
    return false;

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool deleteSimpleValue(OdRxObject* pObject, OdRxPropertyBase* pProperty, OdInt32 iIndex)
{
  bool bRet = false;

  if (pProperty->isKindOf(OdRxIndexedProperty::desc()))
  {
    OdRxIndexedPropertyPtr pIndexedProp = pProperty;

    if (pIndexedProp->removeValue(pObject, iIndex) != eOk)
      return false;
  }
  else
    return false;

  return true;
}

/////////////////////////////////////////////////////////////////////////////

OdRxPropertyBase* getActualProperty(OdRxObject* pObject, OdRxPropertyBase* pProperty, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex)
{
  OdRxPropertyBase* pRet = NULL;

  if (!pProperty)
    return pRet;

  if (iSubPropertyIndex < 0)
  {
    return pProperty;
  }

  OdRxMemberPtr pChild;
  
  if( pProperty->children() && ((OdInt32)pProperty->children()->size() > iSubPropertyIndex) )
    pChild = pProperty->children()->getAt(iSubPropertyIndex);

  if (pChild.isNull() || !pChild->isKindOf(OdRxPropertyBase::desc()))
  {
    OdRxValue curValue;

    if( !getSimpleValue(pObject, pProperty, iArrayIndex, curValue) )
      return pRet;

    OdRxMemberCollection* pMemberCollection = curValue.type().members();

    if( pMemberCollection && (pMemberCollection->count() > iSubPropertyIndex) )
    {
      pChild = pMemberCollection->getAt(iSubPropertyIndex);

      if (pChild.isNull() || !pChild->isKindOf(OdRxPropertyBase::desc()))
        pChild = NULL;
    }
  }

  pRet = (OdRxPropertyBase*)pChild.get();

  return pRet;
}

/////////////////////////////////////////////////////////////////////////////

bool getCDAPropertyValue(const OdRxPropertyBase* pPropertyBase, OdRxObject* pObject, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex, OdRxValue& propValue)
{
  bool bRet = false;

  try
  {
    if( iSubPropertyIndex < 0 )
      bRet = getSimpleValue(pObject, pPropertyBase, iArrayIndex, propValue);
    else
    {
      OdRxMemberPtr pChild;

      if (pPropertyBase->children() && ((OdInt32)pPropertyBase->children()->size() > iSubPropertyIndex))
        pChild = pPropertyBase->children()->getAt(iSubPropertyIndex);

      if (!pChild.isNull() && pChild->isKindOf(OdRxPropertyBase::desc()))
      {
        OdRxPropertyBasePtr pChildProp = pChild;
        bRet = getSimpleValue(pObject, pChildProp, iArrayIndex, propValue);
      }
      else
      {
        OdRxValue curValue;

        if (!getSimpleValue(pObject, pPropertyBase, iArrayIndex, curValue))
          return false;

        OdRxMemberCollection* pMemberCollection = curValue.type().members();

        if (pMemberCollection && (pMemberCollection->count() > iSubPropertyIndex))
        {
          pChild = pMemberCollection->getAt(iSubPropertyIndex);

          if( !pChild.isNull() && pChild->isKindOf(OdRxPropertyBase::desc()) )
          {
            OdRxPropertyBasePtr pSubProp = pChild;
            OdRxBoxedValueOnStack box(curValue);
            OdRxObjectPtr pRxValueObject = &box;

            bRet = getSimpleValue(pRxValueObject, pSubProp, iArrayIndex, propValue);
          }
        }
      }
    }
  }
  catch (...)
  {
    bRet = false;
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

bool setCDAPropertyValue(OdRxPropertyBase* pPropertyBase, OdRxObject* pObject, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex, OdRxValue& propValue)
{
  bool bRet = false;

  try
  {
    if( iSubPropertyIndex < 0 )
      bRet = setSimpleValue(pObject, pPropertyBase, iArrayIndex, propValue);
    else
    {
      OdRxMemberPtr pChild;

      if (pPropertyBase->children() && ((OdInt32)pPropertyBase->children()->size() > iSubPropertyIndex))
        pChild = pPropertyBase->children()->getAt(iSubPropertyIndex);

      if (!pChild.isNull() && pChild->isKindOf(OdRxPropertyBase::desc()))
      {
        OdRxPropertyBasePtr pChildProp = pChild;
        bRet = setSimpleValue(pObject, pChildProp, iArrayIndex, propValue);
      }
      else
      {
        OdRxValue curValue;

        if (!getSimpleValue(pObject, pPropertyBase, iArrayIndex, curValue))
          return false;

        OdRxMemberCollection* pMemberCollection = curValue.type().members();

        if (pMemberCollection && (pMemberCollection->count() > iSubPropertyIndex))
        {
          pChild = pMemberCollection->getAt(iSubPropertyIndex);

          if (!pChild.isNull() && pChild->isKindOf(OdRxPropertyBase::desc()))
          {
            OdRxPropertyBasePtr pSubProp = pChild;
            OdRxBoxedValueOnStack box(curValue);
            OdRxObjectPtr pRxValueObject = &box;

            if( setSimpleValue(pRxValueObject, pSubProp, iArrayIndex, propValue) )
            {
              bRet = setSimpleValue(pObject, pPropertyBase, iArrayIndex, curValue);
            }
          }
        }
      }
    }
  }
  catch (...)
  {
    bRet = false;
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

bool insertCDAPropertyValueToEnd(OdRxPropertyBase* pPropertyBase, OdRxObject* pObject, OdInt32 iSubPropertyIndex, OdRxValue& propValue)
{
  bool bRet = false;

  try
  {
    if (iSubPropertyIndex < 0)
      bRet = insertSimpleValueToEnd(pObject, pPropertyBase, propValue);
    else
    {
      OdRxMemberPtr pChild;

      if (pPropertyBase->children() && ((OdInt32)pPropertyBase->children()->size() > iSubPropertyIndex))
        pChild = pPropertyBase->children()->getAt(iSubPropertyIndex);

      if (!pChild.isNull() && pChild->isKindOf(OdRxPropertyBase::desc()))
      {
        OdRxPropertyBasePtr pChildProp = pChild;
        bRet = insertSimpleValueToEnd(pObject, pChildProp, propValue);
      }
      else
      {
        OdRxValue curValue;

        if (!getSimpleValue(pObject, pPropertyBase, -1, curValue))
          return false;

        OdRxMemberCollection* pMemberCollection = curValue.type().members();

        if (pMemberCollection && (pMemberCollection->count() > iSubPropertyIndex))
        {
          pChild = pMemberCollection->getAt(iSubPropertyIndex);

          if (!pChild.isNull() && pChild->isKindOf(OdRxPropertyBase::desc()))
          {
            OdRxPropertyBasePtr pSubProp = pChild;
            OdRxBoxedValueOnStack box(curValue);
            OdRxObjectPtr pRxValueObject = &box;

            if (insertSimpleValueToEnd(pRxValueObject, pSubProp, propValue))
            {
              bRet = setSimpleValue(pObject, pPropertyBase, -1, curValue);
            }
          }
        }
      }
    }
  }
  catch (...)
  {
    bRet = false;
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

bool deleteCDAPropertyValue(OdRxPropertyBase* pPropertyBase, OdRxObject* pObject, OdInt32 iSubPropertyIndex, OdUInt32 iIndex)
{
  bool bRet = false;

  try
  {
    if (iSubPropertyIndex < 0)
      bRet = deleteSimpleValue(pObject, pPropertyBase, iIndex);
    else
    {
      OdRxMemberPtr pChild;

      if (pPropertyBase->children() && ((OdInt32)pPropertyBase->children()->size() > iSubPropertyIndex))
        pChild = pPropertyBase->children()->getAt(iSubPropertyIndex);

      if (!pChild.isNull() && pChild->isKindOf(OdRxPropertyBase::desc()))
      {
        OdRxPropertyBasePtr pChildProp = pChild;
        bRet = deleteSimpleValue(pObject, pChildProp, iIndex);
      }
      else
      {
        OdRxValue curValue;

        if (!getSimpleValue(pObject, pPropertyBase, -1, curValue))
          return false;

        OdRxMemberCollection* pMemberCollection = curValue.type().members();

        if (pMemberCollection && (pMemberCollection->count() > iSubPropertyIndex))
        {
          pChild = pMemberCollection->getAt(iSubPropertyIndex);

          if (!pChild.isNull() && pChild->isKindOf(OdRxPropertyBase::desc()))
          {
            OdRxPropertyBasePtr pSubProp = pChild;
            OdRxBoxedValueOnStack box(curValue);
            OdRxObjectPtr pRxValueObject = &box;

            if (deleteSimpleValue(pRxValueObject, pSubProp, iIndex))
            {
              bRet = setSimpleValue(pObject, pPropertyBase, -1, curValue);
            }
          }
        }
      }
    }
  }
  catch (...)
  {
    bRet = false;
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

OdString getPropertyName(OdRxObject* pObject, OdRxPropertyBase* pPropertyBase, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex)
{
  OdString strRet;

  OdRxPropertyBase* pRealProp = getActualProperty(pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

  if (!pRealProp)
    return strRet;

  if (iSubPropertyIndex < 0)
    strRet = L"  " + pRealProp->name();
  else
    strRet = L"  - " + pRealProp->name();

  if (iArrayIndex >= 0)
  {
    OdString strIndex;
    strIndex.format(L"[%d]", iArrayIndex);
    strRet += strIndex;
  }

  strRet.replace(L"\\", L"/");

  if (strRet.find(L"/") != -1)
    strRet = L"  - " + strRet.right(strRet.getLength() - strRet.find(L"/") - 1);

  return strRet;
}

/////////////////////////////////////////////////////////////////////////////

OdUInt32 getSimpleIndexedPropertyCount(OdRxObject* pObject, OdRxPropertyBase* pPropertyBase)
{
  OdUInt32 uRet = 0;

  if (!pPropertyBase || !pObject)
    return uRet;

  if (pPropertyBase->isKindOf(OdRxIndexedProperty::desc()))
  {
    OdRxIndexedPropertyPtr pIndexedProperty = pPropertyBase;

    try
    {
      int iCount = 0;

      if (pIndexedProperty->tryGetCount(pObject, iCount) == eOk)
        return (OdUInt32)(iCount);
    }
    catch (...)
    {
      uRet = 0;
    }
  }

  if ((uRet == 0) && pPropertyBase->isKindOf(OdRxCollectionProperty::desc()))
  {
    OdRxCollectionPropertyPtr pCollectionProperty = pPropertyBase;

    OdRxValueIteratorPtr pIter = pCollectionProperty->newValueIterator(pObject);

    if (!pIter.isNull())
    {
      for (; !pIter->done(); pIter->next())
        uRet++;
    }
  }

  return uRet;
}

/////////////////////////////////////////////////////////////////////////////

OdUInt32 getIndexedPropertyCount(OdRxObject* pObject, OdRxPropertyBase* pPropertyBase, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex)
{
  OdUInt32 uRet = 0;

  if (!pPropertyBase || !pObject)
    return uRet;

  // No sub property

  if (iSubPropertyIndex < 0)
    return getSimpleIndexedPropertyCount(pObject, pPropertyBase);

  // Has sub property

  if (pPropertyBase->children() && ((OdInt32)pPropertyBase->children()->size() > iSubPropertyIndex))
  {
    OdRxMemberPtr pSubPropertyMbr = pPropertyBase->children()->getAt(iSubPropertyIndex);

    if (!pSubPropertyMbr.isNull() && pSubPropertyMbr->isKindOf(OdRxPropertyBase::desc()))
    {
      OdRxPropertyBasePtr pSubProp = pSubPropertyMbr;

      return getSimpleIndexedPropertyCount(pObject, pSubProp);
    }
  }
  else
  {
    OdRxValue curValue;

    if (getSimpleValue(pObject, pPropertyBase, iArrayIndex, curValue))
    {
      OdRxMemberCollection* pCollection = curValue.type().members();

      if (pCollection && (pCollection->count() > iSubPropertyIndex))
      {
        OdRxMemberPtr pSubPropertyMbr = pCollection->getAt(iSubPropertyIndex);

        if (!pSubPropertyMbr.isNull() && pSubPropertyMbr->isKindOf(OdRxPropertyBase::desc()))
        {
          OdRxPropertyBasePtr pSubProp = pSubPropertyMbr;
          OdRxBoxedValueOnStack box(curValue);
          OdRxObjectPtr pRxValueObject = &box;
          uRet = getSimpleIndexedPropertyCount(pRxValueObject, pSubProp);
        }
      }
    }
  }

  return uRet;
}

/////////////////////////////////////////////////////////////////////////////

OdUInt32 getPropertyChildrenCount(OdRxObject* pObject, OdRxPropertyBase* pPropertyBase, OdInt32 iArrayIndex)
{
  OdUInt32 uRet = 0;

  if (!pPropertyBase || !pObject)
    return uRet;

  if (pPropertyBase->children() && pPropertyBase->children()->size() > 0)
    return pPropertyBase->children()->size();
  else
  {
    OdRxValue curValue;

    if (getSimpleValue(pObject, pPropertyBase, iArrayIndex, curValue))
    {
      OdRxMemberCollection* pCollection = curValue.type().members();

      if (pCollection)
        uRet = pCollection->count();
    }
  }

  return uRet;
}

/////////////////////////////////////////////////////////////////////////////

OdRxValueIteratorPtr getPropertyValueIterator(OdRxObject* pObject, OdRxPropertyBase* pPropertyBase, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex)
{
  OdRxValueIteratorPtr pRet;

  if (!pPropertyBase || !pObject)
    return pRet;

  // No sub property

  if (iSubPropertyIndex < 0)
  {
    if (pPropertyBase->isKindOf(OdRxCollectionProperty::desc()))
    {
      OdRxCollectionPropertyPtr pCollectionProperty = pPropertyBase;
      pRet = pCollectionProperty->newValueIterator(pObject);
    }

    return pRet;
  }

  // Has sub property

  if (pPropertyBase->children() && ((OdInt32)pPropertyBase->children()->size() > iSubPropertyIndex))
  {
    OdRxMemberPtr pSubPropertyMbr = pPropertyBase->children()->getAt(iSubPropertyIndex);

    if (!pSubPropertyMbr.isNull() && pSubPropertyMbr->isKindOf(OdRxPropertyBase::desc()))
    {
      OdRxPropertyBasePtr pSubProp = pSubPropertyMbr;

      if (pSubProp->isKindOf(OdRxCollectionProperty::desc()))
      {
        OdRxCollectionPropertyPtr pCollectionProperty = pSubProp;
        pRet = pCollectionProperty->newValueIterator(pObject);
      }
    }
  }
  else
  {
    OdRxValue curValue;

    if (getSimpleValue(pObject, pPropertyBase, iArrayIndex, curValue))
    {
      OdRxMemberCollection* pCollection = curValue.type().members();

      if (pCollection && (pCollection->count() > iSubPropertyIndex))
      {
        OdRxMemberPtr pSubPropertyMbr = pCollection->getAt(iSubPropertyIndex);

        if (!pSubPropertyMbr.isNull() && pSubPropertyMbr->isKindOf(OdRxPropertyBase::desc()))
        {
          OdRxPropertyBasePtr pSubProp = pSubPropertyMbr;
          OdRxBoxedValueOnStack box(curValue);
          OdRxObjectPtr pRxValueObject = &box;

          if (pSubProp->isKindOf(OdRxCollectionProperty::desc()))
          {
            OdRxCollectionPropertyPtr pCollectionProperty = pSubProp;
            pRet = pCollectionProperty->newValueIterator(pRxValueObject);
          }
        }
      }
    }
  }

  return pRet;
}

/////////////////////////////////////////////////////////////////////////////
// CCDAPropertiesListCtrl

IMPLEMENT_DYNCREATE(CCDAPropertiesListCtrl, CListCtrl)

/////////////////////////////////////////////////////////////////////////////

CCDAPropertiesListCtrl::CCDAPropertiesListCtrl()
{
  m_pDb = NULL;
  m_pObject = NULL;
  m_pNameStatic = NULL;
  m_pValueStatic = NULL;
  m_bDataInitialized = false;
  m_iDefaultRowHeight = 1;
  m_strPropertyName = OdString::kEmpty;
  m_iSubPropertyIndex = -1;
  m_iArrayIndex = -1;
  m_iTopOffset = 0;
  m_bIgnoreUnionType = false;
}

/////////////////////////////////////////////////////////////////////////////

CCDAPropertiesListCtrl::~CCDAPropertiesListCtrl()
{
  if (m_pNameStatic)
  {
    m_pNameStatic->DestroyWindow();
    delete m_pNameStatic;
    m_pNameStatic = NULL;
  }

  if (m_pValueStatic)
  {
    m_pValueStatic->DestroyWindow();
    delete m_pValueStatic;
    m_pValueStatic = NULL;
  }

  for (OdUInt32 i = 0; i < m_arrWndPtr.size(); i++)
  {
    m_arrWndPtr[i]->DestroyWindow();
    delete m_arrWndPtr[i];
  }
}

/////////////////////////////////////////////////////////////////////////////

void CCDAPropertiesListCtrl::OnDestroy()
{
  CImageList * pImageList = GetImageList(LVSIL_SMALL); 

  if( pImageList )
  {
    SetImageList(0, LVSIL_SMALL);
    delete pImageList;
  }
}

/////////////////////////////////////////////////////////////////////////////

void CCDAPropertiesListCtrl::OnVScroll(UINT SBCode, UINT Pos, CScrollBar *SB)
{
  CWnd::OnVScroll(SBCode, Pos, SB);

  updatePropertyCtrlPositions();

  Invalidate();
}

/////////////////////////////////////////////////////////////////////////////

BOOL CCDAPropertiesListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
  BOOL bRet = CListCtrl::OnMouseWheel(nFlags, zDelta, pt);

  if( !((nFlags & MK_CONTROL) || (nFlags & MK_SHIFT)) )
  {
    updatePropertyCtrlPositions();
    Invalidate();
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

struct CPropertyAndWeight
{
  OdUInt32    m_uWeight;
  OdRxMember* m_pProperty;
};

/////////////////////////////////////////////////////////////////////////////

void  CCDAPropertiesListCtrl::updateControlData()
{
  for (OdUInt32 i = 0; i < m_arrWndPtr.size(); i++)
  {
    m_arrWndPtr[i]->DestroyWindow();
    delete m_arrWndPtr[i];
  }

  m_arrWndPtr.clear();

  DeleteAllItems();

  OdRxMemberIteratorPtr pPropIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(m_pObject);

  std::map<OdString, OdArray<CPropertyAndWeight> > mapProperties;

  for (; !pPropIter->done(); pPropIter->next())
  {
    OdRxMember* pMember = pPropIter->current();

    if (!pMember)
      continue;

    OdRxAttributeCollection& propAttrs = pMember->attributes();

    OdRxAttribute* pAttr = propAttrs.get(OdRxUiPlacementAttribute::desc());

    OdString strCategory = OdString::kEmpty;
    OdUInt32 uWeight = 0;

    if (pAttr)
    {
      OdRxUiPlacementAttribute* pUIAttr = (OdRxUiPlacementAttribute*)(pAttr);
      strCategory = pUIAttr->getCategory(pMember);
      uWeight = pUIAttr->getWeight(pMember);
    }

    if (strCategory.isEmpty())
      strCategory = L"Base Element Data";

    CPropertyAndWeight curProp;
    curProp.m_uWeight = uWeight;
    curProp.m_pProperty = pMember;

    std::map<OdString, OdArray<CPropertyAndWeight> >::iterator pMapIter = mapProperties.find(strCategory);

    if (pMapIter == mapProperties.end())
    {
      OdArray<CPropertyAndWeight> arrNew;
      arrNew.push_back(curProp);

      mapProperties[strCategory] = arrNew;
    }
    else
    {
      OdArray<CPropertyAndWeight>& arrProps = pMapIter->second;

      bool bAddProp = false;

      for (OdUInt32 i = 0; i < arrProps.size(); i++)
      {
        if (arrProps[i].m_uWeight > curProp.m_uWeight)
        {
          arrProps.insert(arrProps.begin() + i, curProp);
          bAddProp = true;
          break;
        }
      }

      if (!bAddProp)
        arrProps.push_back(curProp);
    }
  }

  std::map<OdString, OdArray<CPropertyAndWeight> >::iterator pMapIter = mapProperties.begin();

  for (; pMapIter != mapProperties.end(); pMapIter++)
  {
    if (m_strPropertyName.isEmpty())
      addCategoryCtrl(pMapIter->first);

    for (OdUInt32 j = 0; j < pMapIter->second.size(); j++)
    {
      OdRxMember* pMember = pMapIter->second[j].m_pProperty;

      if (pMember->isKindOf(OdRxPropertyBase::desc()))
      {
        OdRxPropertyBase* pCDAProperty = (OdRxPropertyBase*)(pMember);
        addPropertyCtrl(pCDAProperty, m_iSubPropertyIndex, m_iArrayIndex, m_strPropertyName, m_iSubPropertyIndex);
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////

void CCDAPropertiesListCtrl::updatePropertyCtrlPositions()
{
  for (OdInt32 i = 0; i < GetItemCount(); i++)
  {
    OdInt32 nWnd = GetItemData(i);

    bool bCategory = false;

    if( nWnd > 10000 )
    {
      bCategory = true;
      nWnd -= 10000;
    }

    if (nWnd > 0)
    {
      CRect rItem;

      if( bCategory )
        GetItemRect(i, rItem, LVIR_BOUNDS);
      else
        GetSubItemRect(i, 1, LVIR_BOUNDS, rItem);

      rItem.InflateRect(-2, -2, -2, -3);

      CWnd* pWnd = m_arrWndPtr[nWnd - 1];
      pWnd->MoveWindow(rItem);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////

void CCDAPropertiesListCtrl::onMoveOwner()
{
  if (!m_bDataInitialized)
    return;

  RECT wndRect;
  GetOwner()->GetClientRect(&wndRect);

  OdInt32 iLength = wndRect.right - wndRect.left;
  OdInt32 iHeight = wndRect.bottom - wndRect.top;
  OdInt32 iScrollSize = GetSystemMetrics(SM_CXVSCROLL) + 4;
  OdInt32 iCaptionHeight;
  OdInt32 iRowHeight  = m_iDefaultRowHeight;

  if( m_pNameStatic )
  {
    RECT nameRect;
    m_pNameStatic->GetWindowRect(&nameRect);
    nameRect.left = 0;
    nameRect.right = (OdInt32)(iLength / 3.0);
    nameRect.bottom = nameRect.bottom - nameRect.top - m_iTopOffset;
    nameRect.top = m_iTopOffset;
    m_pNameStatic->MoveWindow(&nameRect);
    m_pNameStatic->SetWindowText(L"Name");
    iCaptionHeight = nameRect.bottom;
  }

  if (m_pValueStatic)
  {
    RECT valueRect;
    m_pValueStatic->GetWindowRect(&valueRect);
    valueRect.left = (OdInt32)(iLength / 3.0);
    valueRect.right = iLength;
    valueRect.bottom = valueRect.bottom - valueRect.top - m_iTopOffset;
    valueRect.top = m_iTopOffset;
    m_pValueStatic->MoveWindow(&valueRect);
    m_pValueStatic->SetWindowText(L"Value");
  }

  // Move list

  RECT listRect;
  GetWindowRect(&listRect);
  listRect.left   = 0;
  listRect.right  = iLength;
  listRect.top    = iCaptionHeight + m_iTopOffset;
  listRect.bottom = iHeight - iCaptionHeight - m_iTopOffset;

  MoveWindow(&listRect);

  SCROLLINFO curInfo;
  GetScrollInfo(SB_VERT, &curInfo);

  if( (int)curInfo.nPage > curInfo.nMax )
    iScrollSize = 4;

  SetColumnWidth(0, (OdInt32)(iLength / 3));
  SetColumnWidth(1, iLength - (OdInt32)(iLength / 3) - iScrollSize);

  updatePropertyCtrlPositions();
}

/////////////////////////////////////////////////////////////////////////////

bool getRxValueType(const OdString& strTypeNames, OdRxValue& typeValue)
{
  bool bRet = false;
  OdString strType = strTypeNames;
  strType.makeUpper();

  if( strType == L"BOOL" )
  {
    typeValue = OdRxValue(true);
    bRet = true;
  }
  else if (strType == L"BYTE")
  {
    typeValue = OdRxValue(OdUInt8(0));
    bRet = true;
  }
  else if (strType == L"ODINT8")
  {
    typeValue = OdRxValue(OdInt8(0));
    bRet = true;
  }
  else if (strType == L"ODUINT8")
  {
    typeValue = OdRxValue(OdUInt8(0));
    bRet = true;
  }
  else if (strType == L"ODUINT16")
  {
    typeValue = OdRxValue(OdUInt16(0));
    bRet = true;
  }
  else if (strType == L"ODINT16")
  {
    typeValue = OdRxValue(OdInt16(0));
    bRet = true;
  }
  else if (strType == L"ODUINT32")
  {
    typeValue = OdRxValue(OdUInt32(0));
    bRet = true;
  }
  else if (strType == L"ODINT32")
  {
    typeValue = OdRxValue(OdInt32(0));
    bRet = true;
  }
  else if (strType == L"ODUINT64")
  {
    typeValue = OdRxValue(OdUInt64(0));
    bRet = true;
  }
  else if (strType == L"ODINT64")
  {
    typeValue = OdRxValue(OdInt64(0));
    bRet = true;
  }
  else if (strType == L"DOUBLE")
  {
    typeValue = OdRxValue(double(0.0));
    bRet = true;
  }
  else if (strType == L"FLOAT")
  {
    typeValue = OdRxValue(float(0));
    bRet = true;
  }
  else if (strType == L"ODSTRING")
  {
    typeValue = OdRxValue(OdString::kEmpty);
    bRet = true;
  }
  else if (strType == L"ODANSISTRING")
  {
    typeValue = OdRxValue(OdAnsiString(OdString::kEmpty));
    bRet = true;
  }
  else if (strType == L"ODARRAY<BOOL>")
  {
    OdArray<bool> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<BYTE>")
  {
    OdArray<OdUInt8> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<ODINT8>")
  {
    OdArray<OdInt8> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<ODUINT8>")
  {
    OdArray<OdUInt8> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<ODUINT16>")
  {
    OdArray<OdUInt16> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<ODINT16>")
  {
    OdArray<OdInt16> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<ODUINT32>")
  {
    OdArray<OdUInt32> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<ODINT32>")
  {
    OdArray<OdInt32> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<ODUINT64>")
  {
    OdArray<OdUInt64> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<ODINT64>")
  {
    OdArray<OdInt64> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<DOUBLE>")
  {
    OdArray<double> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<FLOAT>")
  {
    OdArray<float> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<ODSTRING>")
  {
    OdArray<OdString> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else if (strType == L"ODARRAY<ODANSISTRING>")
  {
    OdArray<OdAnsiString> valArr;
    typeValue = OdRxValue(valArr);
    bRet = true;
  }
  else
  {
    strType = strTypeNames;

    if (strType.getLength() > 3 && strType.right(3).makeUpper() == L"PTR")
      strType = strType.left(strType.getLength() - 3);

    OdRxClassPtr pObjectClass = (OdRxObjectPtr)(::odrxClassDictionary()->getAt(strType));

    if( !pObjectClass.isNull() )
    {
      OdRxObjectPtr pDefaultValue;

      if( pObjectClass->constructor() )
        pDefaultValue = pObjectClass->create();

      if (!pDefaultValue.isNull())
      {
        typeValue = OdRxValue(pDefaultValue);
        bRet = true;
      }
      else if(pObjectClass->isKindOf(OdRxValueType::desc()) )
      {
        OdRxValueTypePtr pValueType = (OdRxValueTypePtr)(pObjectClass);

        if (!pValueType.isNull())
        {
          typeValue = pValueType->createValue();
          bRet = true;
        }
      }
      else
        pDefaultValue = NULL;
    }
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

bool isComplexProperty(OdRxObject* pObject, OdRxPropertyBase* pPropertyBase, OdInt32 iSubPropertyIndex)
{
  bool bRet = true;

  OdRxValue propValue;

  if( getCDAPropertyValue(pPropertyBase, pObject, iSubPropertyIndex, 0, propValue) )
  {
    OdString strType = propValue.type().name();
    strType.makeUpper();

    if( (strType == L"BOOL") ||
        (strType == L"BYTE") ||
        (strType == L"ODINT8") ||
        (strType == L"ODUINT8") ||
        (strType == L"ODUINT16") ||
        (strType == L"ODINT16") ||
        (strType == L"ODUINT32") ||
        (strType == L"ODINT32") ||
        (strType == L"ODUINT64") ||
        (strType == L"ODINT64") ||
        (strType == L"DOUBLE") ||
        (strType == L"FLOAT") ||
        (strType == L"ODSTRING") ||
        (strType == L"ODANSISTRING") ||
        (strType == L"ODGEPOINT2D") ||
        (strType == L"ODGEPOINT3D") ||
        (strType == L"ODGEVECTOR2D") ||
        (strType == L"ODGEVECTOR3D")
      )
    {
      bRet = false;
    }
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

void CCDAPropertiesListCtrl::addPropertyCtrl(OdRxPropertyBase* pPropertyBase, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex, const OdString& strPropertyName, OdInt32 iFixedSubPropertyIndex)
{
  OdRxPropertyBase* pPropBase = getActualProperty(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

  if( !strPropertyName.isEmpty() && (pPropertyBase->name() != strPropertyName) )
    return;

  if (!strPropertyName.isEmpty() && (iFixedSubPropertyIndex >= 0) && (iFixedSubPropertyIndex != iSubPropertyIndex))
    return;

  const OdRxAttributeCollection& attrs = pPropBase->attributes();
  const OdRxAttribute* pUnionTypeAttr = attrs.get(OdRxUnionTypeAttribute::desc());

  bool  bUnionType = false;
  OdString    strUnionType;

  if( !m_bIgnoreUnionType && pUnionTypeAttr && !pPropBase->isReadOnly(m_pObject) )
  {
    OdRxUnionTypeAttribute* pUnionXAttr = (OdRxUnionTypeAttribute*)(pUnionTypeAttr);
    strUnionType = pUnionXAttr->typenames();
    strUnionType.trimLeft();
    strUnionType.trimRight();

    bUnionType = strUnionType.find(L";") != -1;
  }

  OdRxValue propValue;

  bool bGetProperty = false;

  if (pPropBase->isKindOf(OdRxIndexedProperty::desc()))
  {
    OdRxIndexedPropertyPtr pIndexedProperty = pPropBase;

    if( (iArrayIndex == -1) && (iFixedSubPropertyIndex < 0) && (strPropertyName.isEmpty() || (iSubPropertyIndex >= 0)) )
    {
      bool bInitValueType = false;

      OdRxValue typeValue;
      OdString  strValueType = strUnionType;      

      if(bUnionType)
      {
        if(strUnionType.find(L";") == -1 )
          bInitValueType = getRxValueType(strUnionType, typeValue);
      }

      if( !bInitValueType )
        bInitValueType = getCDAPropertyValue(pPropertyBase, m_pObject, iSubPropertyIndex, 0, typeValue);

      OdString  strName = getPropertyName(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

      OdString strValue = L"Array Property";

      if( bInitValueType )
        strValue = typeValue.type().name();

      OdUInt32 uItemIndex = GetItemCount();
      InsertItem(LVIF_TEXT | LVIF_PARAM, uItemIndex, strName, 0, 0, 0, m_arrWndPtr.size() + 1);
      SetItem(uItemIndex, 1, LVIF_TEXT, strValue, 0, 0, 0, 1);
      CRect rItem;
      GetSubItemRect(uItemIndex, 1, LVIR_BOUNDS, rItem);
      rItem.InflateRect(-2, -2, -2, -3);

      CWnd* pPropCtrl = NULL;

      bool bEnable = (iSubPropertyIndex < 0) || !isComplexProperty(m_pObject, pPropertyBase, m_iSubPropertyIndex);

      if (bInitValueType)
        pPropCtrl = CCDACollectionButton::createCDACollectionButton(m_pDb, m_pObject, pPropertyBase, CCDACollectionButton::kArray, typeValue, rItem, this, uItemIndex + 1, iSubPropertyIndex, -1, bEnable);
      else if( !strValueType.isEmpty() )
        pPropCtrl = CCDACollectionButton::createCDACollectionButton(m_pDb, m_pObject, pPropertyBase, CCDACollectionButton::kArray, strValueType, rItem, this, uItemIndex + 1, iSubPropertyIndex, -1, bEnable);
      else
        pPropCtrl = createDefaultCDAControl(m_pObject, pPropertyBase, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);

      m_arrWndPtr.push_back(pPropCtrl);
    }
    else
    {
      if( strPropertyName.isEmpty() )
      {
        if( getCDAPropertyValue(pPropertyBase, m_pObject, iSubPropertyIndex, iArrayIndex, propValue) )
          bGetProperty = true;
      }
      else
      {
        int nItems = getIndexedPropertyCount(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);
      
        for( OdInt32 i = 0; i < nItems; i++ )
        {
          addPropertyCtrl(pPropertyBase, iSubPropertyIndex, i);
        }
      }
    }

    if( !bGetProperty )
      return;
  }
  else if (pPropBase->isKindOf(OdRxCollectionProperty::desc()))
  {
    OdRxCollectionPropertyPtr pCollectionProp = pPropBase;

    if( (iArrayIndex == -1) && m_strPropertyName.isEmpty() )
    {
      bool bInitValueType = false;

      OdRxValue typeValue;
      OdString  strValueType = strUnionType;

      if (bUnionType)
      {
        if (strUnionType.find(L";") == -1)
          bInitValueType = getRxValueType(strUnionType, typeValue);
      }

      if (!bInitValueType)
        bInitValueType = getCDAPropertyValue(pPropertyBase, m_pObject, iSubPropertyIndex, 0, typeValue);

      OdString  strName = getPropertyName(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

      OdString  strValue = L"Collection";

      if (bInitValueType)
      {
        if( typeValue.type().isReference() )
        {
          OdRxObjectPtr pObject = typeValue.type().reference()->dereference(typeValue, IOdRxReferenceType::kForWrite);

          if (!pObject.isNull())
            strValue = pObject->isA()->name();
          else
            strValue = typeValue.type().name();
        }
        else
          strValue = typeValue.type().name();
      }

      OdUInt32 uItemIndex = GetItemCount();
      InsertItem(LVIF_TEXT | LVIF_PARAM, uItemIndex, strName, 0, 0, 0, m_arrWndPtr.size() + 1);
      SetItem(uItemIndex, 1, LVIF_TEXT, strValue, 0, 0, 0, 1);
      CRect rItem;
      GetSubItemRect(uItemIndex, 1, LVIR_BOUNDS, rItem);
      rItem.InflateRect(-2, -2, -2, -3);

      CWnd* pPropCtrl = NULL;

      if (!bInitValueType)
        pPropCtrl = createDefaultCDAControl(m_pObject, pPropertyBase, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
      else
        pPropCtrl = CCDACollectionButton::createCDACollectionButton(m_pDb, m_pObject, pPropertyBase, CCDACollectionButton::kCollection, strValue, rItem, this, uItemIndex + 1, iSubPropertyIndex);

      m_arrWndPtr.push_back(pPropCtrl);
    }
    else
    {

      OdRxValueIteratorPtr pIndexedIter = getPropertyValueIterator(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

      if( strPropertyName.isEmpty() )
      {
        int iIndex = 0;

        for(; !pIndexedIter->done(); pIndexedIter->next() )
        {
          if (iIndex == iArrayIndex)
          {
            propValue = pIndexedIter->current();
            bGetProperty = true;
            break;
          }

          iIndex++;
        }
      }
      else
      {
        int iIndex = 0;

        for(; !pIndexedIter->done(); pIndexedIter->next())
        {
          addPropertyCtrl(pPropertyBase, iSubPropertyIndex, iIndex);
          iIndex++;
        }
      }
    }
  }
  else if (pPropBase->isKindOf(OdRxProperty::desc()))
  {
    OdRxPropertyPtr pProperty = pPropBase;

    if( getCDAPropertyValue(pPropertyBase, m_pObject, iSubPropertyIndex, iArrayIndex, propValue) )
      bGetProperty = true;
  }

  if( bUnionType && !bGetProperty )
    bGetProperty = true;

  if( bGetProperty )
  {
    CWnd* pPropCtrl = NULL;

    OdRxAttributeCollection& propAttrs = pPropBase->attributes();
    OdRxAttribute* pRefToAttr = propAttrs.get(OdRxRefersToAttribute::desc());

    OdString  strName = getPropertyName(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);
    OdString  strValue = propValue.toString();

    OdUInt32 uItemIndex = GetItemCount();
    InsertItem(LVIF_TEXT | LVIF_PARAM, uItemIndex, strName, 0, 0, 0, m_arrWndPtr.size() + 1);

    SetItem(uItemIndex, 1, LVIF_TEXT, strValue, 0, 0, 0, 1);

    CRect rItem;

    GetSubItemRect(uItemIndex, 1, LVIR_BOUNDS, rItem);

    rItem.InflateRect(-2, -2, -2, -3);

    if( bUnionType )
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kUnionType, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if( propValue.type() == OdRxValueType::Desc<bool>::value() )
      pPropCtrl = CCDABoolCheckBox::createCDABoolCheckBox(m_pDb, m_pObject, pPropertyBase, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdUInt8>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kUInt8, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdUInt16>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kUInt16, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdUInt32>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kUInt32, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdUInt64>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kUInt64, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdInt8>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kInt8, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdInt16>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kInt16, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdInt32>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kInt32, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdInt64>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kInt64, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<double>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kDouble, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<float>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kFloat, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdString>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kString, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdAnsiString>::value())
      pPropCtrl = CCDAEditCtrl::createCDAEditCtrl(m_pDb, m_pObject, pPropertyBase, CCDAEditCtrl::kAnsiString, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type().isEnum())
      pPropCtrl = CCDAComboBox::createCDAComboBox(m_pDb, m_pObject, pPropertyBase, CCDAComboBox::kEnum, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type().isReference() && pRefToAttr)
      pPropCtrl = CCDAComboBox::createCDAComboBox(m_pDb, m_pObject, pPropertyBase, CCDAComboBox::kCollection, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<bool> >::value() )
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kBoolArray, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdInt8> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kInt8Array, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdInt16> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kInt16Array, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdInt32> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kInt32Array, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdInt64> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kInt64Array, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdUInt8> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kUInt8Array, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdUInt16> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kUInt16Array, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdUInt32> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kUInt32Array, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdUInt64> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kUInt64Array, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<double> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kDoubleArray, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<float> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kFloatArray, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdString> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kStringArray, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdAnsiString> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kAnsiStringArray, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdArray<double> > >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kDouble2dArray, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdArray<int> > >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kInt322dArray, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdGePoint3d> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kPoint3dArray, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdArray<OdTimeStamp> >::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kTimeStampArray, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGePoint2d>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kPoint2d, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGePoint3d>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kPoint3d, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGeVector2d>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kVector2d, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGeVector3d>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kVector3d, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGeScale3d>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kScale3d, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdDbHandle>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kOdDbHandle, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<ODRECT>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kOdRect, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdTimeStamp>::value())
      pPropCtrl = CCDADateTimeCtrl::createCDADateTimeCtrl(m_pDb, m_pObject, pPropertyBase, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGeExtents2d>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kExtents2d, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGeExtents3d>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kExtents3d, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGeMatrix2d>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kMatrix2d, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGeMatrix3d>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kMatrix3d, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGeQuaternion>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kQuaternion, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGiColorRGB>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kDoubleColor, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdGiMaterialColor>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kMaterialColor, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdCmTransparency>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kCmTransparency, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdRxObjectPtr>::value())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kRxObject, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type().isReference())
      pPropCtrl = CCDAStdTypeButton::createCDAStdButton(m_pDb, m_pObject, pPropertyBase, CCDAStdTypeButton::kReference, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if (propValue.type() == OdRxValueType::Desc<OdCmEntityColor>::value())
      pPropCtrl = CCDAOdColorCombo::createCDAColorCombo(m_pDb, m_pObject, pPropertyBase, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);
    else if ( (iSubPropertyIndex < 0) && (getPropertyChildrenCount(m_pObject, pPropertyBase, iArrayIndex) > 0) )
    {
      OdUInt32 nChildren = getPropertyChildrenCount(m_pObject, pPropertyBase, iArrayIndex);

      for( OdUInt32 k = 0; k < nChildren; k++ )
        addPropertyCtrl(pPropBase, k, iArrayIndex, strPropertyName);
    }

    if (!pPropCtrl)
      pPropCtrl = createDefaultCDAControl(m_pObject, pPropertyBase, rItem, this, uItemIndex + 1, iSubPropertyIndex, iArrayIndex);

    m_arrWndPtr.push_back(pPropCtrl);

    SetItem(uItemIndex, 1, LVIF_TEXT, OdString::kEmpty, 0, 0, 0, 1);
  }
}

/////////////////////////////////////////////////////////////////////////////

CWnd* CCDAPropertiesListCtrl::createDefaultCDAControl(OdRxObject* pObject, 
                                                        OdRxPropertyBase* pProperty,
                                                          const CRect& rItem, 
                                                            CWnd* pParentWnd, 
                                                              OdInt32 iRescID, 
                                                                OdInt32 iSubPropertyIndex,
                                                                  OdInt32 iArrayIndex)
{
  OdRxPropertyBase* pPropBase = getActualProperty(m_pObject, pProperty, iSubPropertyIndex, iArrayIndex);

  OdRxValue propValue;

  bool bGetProperty = false;

  OdString  strName = getPropertyName(m_pObject, pProperty, iSubPropertyIndex, iArrayIndex);
  OdString  strValue = OdString::kEmpty;

  if (!getCDAPropertyValue(pProperty, m_pObject, iSubPropertyIndex, iArrayIndex, propValue))
  {
    if (pPropBase->isKindOf(OdRxIndexedProperty::desc()))
      strValue = L"Empty Array";
    else if (pPropBase->isKindOf(OdRxCollectionProperty::desc()))
      strValue = L"Empty Collection";
    else
      strValue = L"Empty";
  }
  else
    strValue = propValue.toString();

  CStatic* pStatic = new CStatic();
  pStatic->Create(strName, WS_BORDER | SS_LEFT | WS_VISIBLE | WS_CHILD, rItem, pParentWnd, iRescID);
  pStatic->SetFont(GetFont());
  pStatic->SetWindowText(strValue);

  return pStatic;
}

/////////////////////////////////////////////////////////////////////////////

void CCDAPropertiesListCtrl::addCategoryCtrl(const OdString& strCategory)
{
  OdUInt32 uItemIndex = GetItemCount();
  InsertItem(LVIF_TEXT | LVIF_PARAM, uItemIndex, L" ", 0, 0, 0, m_arrWndPtr.size() + 10001);

  CRect captionRect;

  GetItemRect(uItemIndex, captionRect, LVIR_BOUNDS);

  captionRect.InflateRect(-2, -2, -2, -3);

  CStatic* pCategoryStatic = new CStatic();
  pCategoryStatic->Create(strCategory, WS_BORDER | SS_CENTER | WS_VISIBLE | WS_CHILD, captionRect, this);
  pCategoryStatic->SetFont(GetFont());
  pCategoryStatic->SetWindowText(strCategory);

  m_arrWndPtr.push_back(pCategoryStatic);
}

/////////////////////////////////////////////////////////////////////////////

void  CCDAPropertiesListCtrl::setRxObject(OdRxObject* pObject, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex)
{
  m_pObject = pObject;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_iArrayIndex = iArrayIndex;
  updateControlData();
}

/////////////////////////////////////////////////////////////////////////////

void CCDAPropertiesListCtrl::initData(OdRxObject* pDb, OdRxObject* pObject, const RECT& wndRect, OdInt32 iSubPropertyIndex, 
  const OdString& strPropName, OdInt32 iArrayIndex, OdInt32 iTopOffset, bool bIgnoreUnionType )
{
  m_iTopOffset = iTopOffset;
  m_pDb     = pDb;
  m_pObject = pObject;
  m_pNameStatic = new CStatic();
  m_pValueStatic = new CStatic();
  m_strPropertyName = strPropName;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_iArrayIndex = iArrayIndex;
  m_bIgnoreUnionType = bIgnoreUnionType;

  OdInt32 iLength         = wndRect.right - wndRect.left;
  OdInt32 iHeight         = wndRect.bottom - wndRect.top;
  OdInt32 iScrollSize     = GetSystemMetrics(SM_CXVSCROLL) + 4;
  CSize   defaultSize     = ApproximateViewRect();
  m_iDefaultRowHeight     = defaultSize.cy + 8;
  OdInt32 iCaptionHeight  = defaultSize.cy + 3;

  // Craete "Name" Static

  RECT nameRect;
  nameRect.left   = 0;
  nameRect.right  = (OdInt32)(iLength / 3.0);
  nameRect.top    = m_iTopOffset;
  nameRect.bottom = iCaptionHeight + m_iTopOffset;

  CStatic* pStatic = (CStatic*)(m_pNameStatic);
  pStatic->Create(L"Name", WS_BORDER | SS_CENTER | WS_VISIBLE | WS_CHILD, nameRect, GetOwner());

  pStatic->SetFont(GetFont());
  pStatic->SetWindowText(L"Name");

  // Craete "Value" Static

  RECT valueRect;
  valueRect.left   = (OdInt32)(iLength / 3.0);
  valueRect.right  = iLength;
  valueRect.top    = m_iTopOffset;
  valueRect.bottom = iCaptionHeight + m_iTopOffset;

  pStatic = (CStatic*)(m_pValueStatic);
  pStatic->Create(L"Value", WS_BORDER | SS_CENTER | WS_VISIBLE | WS_CHILD, valueRect, GetOwner());

  pStatic->SetFont(GetFont());
  pStatic->SetWindowText(L"Value");

  // Set List Ctrl Style

  SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

  // Set List Ctrl Item height

  CImageList * pImageList = GetImageList(LVSIL_SMALL); 
  
  if( pImageList == NULL )
  {
    pImageList = new CImageList();
    pImageList->Create(1, m_iDefaultRowHeight, ILC_COLOR, 1, 1);
    SetImageList(pImageList, LVSIL_SMALL);
  }

  CBitmap bmp;
  pImageList->Add(&bmp, RGB(0, 0, 0));

  // Insert columns

  InsertColumn(0, _T("Name"), LVCFMT_LEFT, (OdInt32)(iLength / 3));
  InsertColumn(1, _T("Value"), LVCFMT_LEFT, iLength - (OdInt32)(iLength / 3) - iScrollSize);

  // Update data

  updateControlData();

  // Move list

  RECT listRect;
  listRect.left = 0;
  listRect.right = iLength;
  listRect.top = iCaptionHeight + m_iTopOffset;
  listRect.bottom = iHeight - iCaptionHeight - m_iTopOffset;

  MoveWindow(&listRect);

  SCROLLINFO curInfo;
  GetScrollInfo(SB_VERT, &curInfo);

  if ((int)curInfo.nPage > curInfo.nMax)
  {
    SetColumnWidth(1, iLength - (OdInt32)(iLength / 3) - 5);

    updatePropertyCtrlPositions();
  }

  SetFocus();

  m_bDataInitialized = true;
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCDAPropertiesListCtrl, CListCtrl)
  //{{AFX_MSG_MAP(CCDAPropertiesListCtrl)
  ON_WM_DESTROY()
  ON_WM_VSCROLL()
  ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDABoolCheckBox

IMPLEMENT_DYNCREATE(CCDABoolCheckBox, CButton)

/////////////////////////////////////////////////////////////////////////////

CCDABoolCheckBox::CCDABoolCheckBox()
{
  m_pDb     = NULL;
  m_pObject = NULL;
  m_pProperty = NULL;
  m_iArrayIndex = -1;
  m_iSubPropertyIndex = -1;
  m_bValue = false;
  m_bReadOnly = true;
  m_uRscIndex = 0;
}

/////////////////////////////////////////////////////////////////////////////

CCDABoolCheckBox::~CCDABoolCheckBox()
{}

/////////////////////////////////////////////////////////////////////////////

CWnd* CCDABoolCheckBox::createCDABoolCheckBox(OdRxObject* pDb,
                                                OdRxObject* pObject,
                                                  OdRxPropertyBase* pProperty,
                                                    const CRect& btnRect,
                                                      CWnd* pParentWnd,
                                                        OdUInt32 uRscIndex,
                                                          OdInt32 iSubPropertyIndex,
                                                            OdInt32 iArrayIndex)
{
  CCDABoolCheckBox* pRet = new CCDABoolCheckBox();

  if( pRet->initData(pDb, pObject, pProperty, btnRect, pParentWnd, uRscIndex, iSubPropertyIndex, iArrayIndex) )
    return pRet;

  delete pRet;

  return NULL;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDABoolCheckBox::getPropertyValue(bool& bValue) const
{
  OdRxValue propValue;

  bool bRet = getCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, propValue);

  if( bRet )
  {
    bool* pBool = rxvalue_cast<bool>(&propValue);

    if (pBool)
      bValue = *pBool;
    else
      bRet = false;
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

void CCDABoolCheckBox::setPropertyValue(bool bValue)
{
  OdRxValue boolValue(bValue);
  setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, boolValue);
}

/////////////////////////////////////////////////////////////////////////////

OdUInt32 CCDABoolCheckBox::getRscIndex() const
{
  return m_uRscIndex;
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CCDABoolCheckBox::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT pRet = CButton::WindowProc(message, wParam, lParam);

  if ((message == WM_LBUTTONUP) || ((message == WM_KEYUP) && (wParam == 32)))
  {
    bool bNewValue = (GetCheck() == BST_CHECKED);

    if (bNewValue != m_bValue)
    {
      setPropertyValue(bNewValue);
      m_bValue = bNewValue;
    }
  }

  return pRet;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDABoolCheckBox::initData(OdRxObject* pDb, 
                                  OdRxObject* pObject, 
                                    OdRxPropertyBase* pPropertyBase, 
                                      const CRect& btnRect,
                                        CWnd* pParentWnd,
                                          OdUInt32 uRscIndex,
                                            OdInt32 iSubPropertyIndex,
                                              OdInt32 iArrayIndex)
{
  bool bRet = false;
  m_pDb = pDb;
  m_pObject = pObject;
  m_pProperty = pPropertyBase;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_iArrayIndex = iArrayIndex;

  OdString  strName = getPropertyName(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

  m_bReadOnly = pPropertyBase->isReadOnly(m_pObject);

  if (pPropertyBase->isKindOf(OdRxCollectionProperty::desc()) && !pPropertyBase->isKindOf(OdRxIndexedProperty::desc()))
    m_bReadOnly = true;

  m_uRscIndex = uRscIndex;

  Create(strName, WS_VISIBLE | WS_CHILD | WS_BORDER | BS_CHECKBOX | ES_CENTER, btnRect, pParentWnd, 0);

  SetFont(pParentWnd->GetFont());
  SetWindowText(OdString::kEmpty);

  bRet = getPropertyValue(m_bValue);

  if( bRet )
  {
    EnableWindow(!m_bReadOnly);
    SetCheck(m_bValue ? BST_CHECKED : BST_UNCHECKED);
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCDABoolCheckBox, CButton)
  //{{AFX_MSG_MAP(CCDABoolCheckBox)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDAEditCtrl

IMPLEMENT_DYNCREATE(CCDAEditCtrl, CEdit)

/////////////////////////////////////////////////////////////////////////////

CCDAEditCtrl::CCDAEditCtrl()
{
  m_pDb = NULL;
  m_pObject = NULL;
  m_pProperty = NULL;
  m_iArrayIndex = -1;
  m_iSubPropertyIndex = -1;
  m_strValue = OdString::kEmpty;
  m_bReadOnly = true;
  m_uRscIndex = 0;
}

/////////////////////////////////////////////////////////////////////////////

CCDAEditCtrl::~CCDAEditCtrl()
{}

/////////////////////////////////////////////////////////////////////////////

CWnd* CCDAEditCtrl::createCDAEditCtrl(OdRxObject* pDb,
                                        OdRxObject* pObject,
                                          OdRxPropertyBase* pProperty,
                                            CCDAEditCtrlValueTypes uValueType,
                                              const CRect& btnRect,
                                                CWnd* pParentWnd,
                                                  OdUInt32 uRscIndex,
                                                    OdInt32 iSubPropertyIndex,
                                                      OdInt32 iArrayIndex)
{
  CCDAEditCtrl* pRet = new CCDAEditCtrl();

  if (pRet->initData(pDb, pObject, pProperty, uValueType, btnRect, pParentWnd, uRscIndex, iSubPropertyIndex, iArrayIndex))
    return pRet;

  delete pRet;

  return NULL;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDAEditCtrl::getPropertyValue(OdString& strValue) const
{
  OdRxValue propValue;
  bool bRet = getCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, propValue);

  if( bRet )
    strValue = propValue.toString();

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

bool createRxValue(const OdString& strValueData, 
                     CCDAEditCtrl::CCDAEditCtrlValueTypes uValueType,
                       OdRxValue& retVal)
{
  bool bRet = false;

  OdString strValue = strValueData;

  switch (uValueType)
  {
    case CCDAEditCtrl::kInt8:
    case CCDAEditCtrl::kInt16:
    case CCDAEditCtrl::kInt32:
    case CCDAEditCtrl::kInt64:
    case CCDAEditCtrl::kUInt8:
    case CCDAEditCtrl::kUInt16:
    case CCDAEditCtrl::kUInt32:
    case CCDAEditCtrl::kUInt64:
    {
      strValue.trimLeft();
      strValue.trimRight();
    } break;
  
    case CCDAEditCtrl::kDouble:
    case CCDAEditCtrl::kFloat:
    {
      strValue.trimLeft();
      strValue.trimRight(); 
      strValue.replace(L",", L".");
    }
  }

  switch (uValueType)
  {
    case CCDAEditCtrl::kInt8:
    {
      if (!strValue.isEmpty())
      {
        OdChar* pNextLong;
        OdInt8 iRet = wcstol(strValue.c_str(), &pNextLong, 10);
        retVal = OdRxValue(iRet);
        bRet = *pNextLong == 0;
      }
    } break;

    case CCDAEditCtrl::kInt16:
    {
      if (!strValue.isEmpty())
      {
        OdChar* pNextLong;
        OdInt16 iRet = wcstol(strValue.c_str(), &pNextLong, 10);
        retVal = OdRxValue(iRet);
        bRet = *pNextLong == 0;
      }
    } break;

    case CCDAEditCtrl::kInt32:
    {
      if (!strValue.isEmpty())
      {
        OdChar* pNextLong;
        OdInt32 iRet = wcstol(strValue.c_str(), &pNextLong, 10);
        retVal = OdRxValue(iRet);
        bRet = *pNextLong == 0;
      }
    } break;

    case CCDAEditCtrl::kInt64:
    {
      if (!strValue.isEmpty())
      {
        OdChar* pNextLong;
        OdInt64 iRet = wcstol(strValue.c_str(), &pNextLong, 10);
        retVal = OdRxValue(iRet);
        bRet = *pNextLong == 0;
      }
    } break;
    case CCDAEditCtrl::kUInt8:
    {
      if (!strValue.isEmpty())
      {
        OdChar* pNextLong;
        OdUInt8 iRet = wcstol(strValue.c_str(), &pNextLong, 10);
        retVal = OdRxValue(iRet);
        bRet = *pNextLong == 0;
      }
    } break;

    case CCDAEditCtrl::kUInt16:
    {
      if (!strValue.isEmpty())
      {
        OdChar* pNextLong;
        OdUInt16 iRet = wcstol(strValue.c_str(), &pNextLong, 10);
        retVal = OdRxValue(iRet);
        bRet = *pNextLong == 0;
      }
    } break;

    case CCDAEditCtrl::kUInt32:
    {
      if (!strValue.isEmpty())
      {
        OdChar* pNextLong;
        OdUInt32 iRet = wcstol(strValue.c_str(), &pNextLong, 10);
        retVal = OdRxValue(iRet);
        bRet = *pNextLong == 0;
      }
    } break;

    case CCDAEditCtrl::kUInt64:
    {
      if (!strValue.isEmpty())
      {
        OdChar* pNextLong;
        OdUInt64 iRet = wcstol(strValue.c_str(), &pNextLong, 10);
        retVal = OdRxValue(iRet);
        bRet = *pNextLong == 0;
      }
    } break;

    case CCDAEditCtrl::kDouble:
    {
      SET_LOCALE(LC_NUMERIC, "C");

      double dValue = 0.0;

      if (!strValue.isEmpty())
      {
        OdChar* pNextDouble;
        dValue = wcstod(strValue.c_str(), &pNextDouble);
        retVal = OdRxValue(dValue);
        bRet = *pNextDouble == 0;
      }

      RESET_LOCALE();
    } break;

    case CCDAEditCtrl::kFloat:
    {
      SET_LOCALE(LC_NUMERIC, "C");

      float dValue = 0.0;

      if (!strValue.isEmpty())
      {
        OdChar* pNextDouble;
        dValue = wcstod(strValue.c_str(), &pNextDouble);
        retVal = OdRxValue(dValue);
        bRet = *pNextDouble == 0;
      }

      RESET_LOCALE();
    } break;

    case CCDAEditCtrl::kString:
    {
      retVal = OdRxValue(strValue);
      bRet = true;
    } break;

    case CCDAEditCtrl::kAnsiString:
    {
      OdAnsiString strAnsi(strValue);
      retVal = OdRxValue(strAnsi);
      bRet = true;
    } break;
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDAEditCtrl::setPropertyValue(const OdString& strValue)
{
  OdRxValue newValue;

  if (!createRxValue(strValue, m_uValueType, newValue))
    return false;

  if (!setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newValue))
    return false;

  return true;
}

/////////////////////////////////////////////////////////////////////////////

OdUInt32 CCDAEditCtrl::getRscIndex() const
{
  return m_uRscIndex;
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CCDAEditCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT pRet = CEdit::WindowProc(message, wParam, lParam);

  if( (message == WM_KILLFOCUS) || ((message == WM_KEYUP) && (wParam == 13)) )
  {
    CString strCValue;
    GetWindowText(strCValue);

    OdString strValue = strCValue;

    if( strValue != m_strValue)
    {
      if( setPropertyValue(strValue) )
        m_strValue = strValue;
      else
      {
        SetWindowText(m_strValue);
      }
    }
  }

  return pRet;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDAEditCtrl::initData(OdRxObject* pDb,
                              OdRxObject* pObject,
                                OdRxPropertyBase* pPropertyBase,
                                  CCDAEditCtrlValueTypes uValueType,
                                    const CRect& btnRect,
                                      CWnd* pParentWnd,
                                        OdUInt32 uRscIndex,
                                          OdInt32 iSubPropertyIndex,
                                            OdInt32 iArrayIndex)
{
  bool bRet = false;
  m_pDb = pDb;
  m_pObject = pObject;
  m_pProperty = pPropertyBase;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_iArrayIndex = iArrayIndex;
  m_uValueType = uValueType;

  OdString  strName = getPropertyName(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

  m_bReadOnly = pPropertyBase->isReadOnly(m_pObject);

  if (pPropertyBase->isKindOf(OdRxCollectionProperty::desc()) && !pPropertyBase->isKindOf(OdRxIndexedProperty::desc()))
    m_bReadOnly = true;

  m_uRscIndex = uRscIndex;

  Create(WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, btnRect, pParentWnd, uRscIndex);

  bRet = getPropertyValue(m_strValue);

  if (bRet)
  {
    EnableWindow(!m_bReadOnly);
    SetFont(pParentWnd->GetFont());
    SetWindowText(m_strValue);
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCDAEditCtrl, CEdit)
  //{{AFX_MSG_MAP(CCDAEditCtrl)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDAComboBox

IMPLEMENT_DYNCREATE(CCDAComboBox, CComboBox)

/////////////////////////////////////////////////////////////////////////////

CCDAComboBox::CCDAComboBox()
{
  m_pDb = NULL;
  m_pObject = NULL;
  m_pProperty = NULL;
  m_iArrayIndex = -1;
  m_iSubPropertyIndex = -1;
  m_iCurIndex = 0;
  m_bReadOnly = true;
  m_uRscIndex = 0;
}

/////////////////////////////////////////////////////////////////////////////

CCDAComboBox::~CCDAComboBox()
{}

/////////////////////////////////////////////////////////////////////////////

CWnd* CCDAComboBox::createCDAComboBox(OdRxObject* pDb,
                                        OdRxObject* pObject,
                                          OdRxPropertyBase* pProperty,
                                            CCDAComboBoxValueTypes uValueType,
                                              const CRect& btnRect,
                                                CWnd* pParentWnd,
                                                  OdUInt32 uRscIndex,
                                                    OdInt32 iSubPropertyIndex,
                                                      OdInt32 iArrayIndex)
{
  CCDAComboBox* pRet = new CCDAComboBox();

  if (pRet->initData(pDb, pObject, pProperty, uValueType, btnRect, pParentWnd, uRscIndex, iSubPropertyIndex, iArrayIndex))
    return pRet;

  delete pRet;

  return NULL;
}

/////////////////////////////////////////////////////////////////////////////

OdRxCollectionPropertyPtr getCollectionProperty(const OdArray<OdString>& arrPath, OdRxObject* pDb, OdRxObjectPtr& pCollectionOwner)
{
  OdRxPropertyBasePtr pCollectionProp;
  OdRxObject*         pCurObject = pDb;

  try
  {
    for (OdUInt32 i = 0; i < arrPath.size(); i++)
    {
      OdRxMemberPtr pProp = OdRxMemberQueryEngine::theEngine()->find(pCurObject, arrPath[i]);

      if (i == arrPath.size() - 1)
      {
        pCollectionOwner = pCurObject;
        pCollectionProp = pProp;
      }
      else
      {
        if (pProp.isNull() || !pProp->isKindOf(OdRxProperty::desc()))
          break;

        OdRxPropertyPtr pCurProp = pProp;

        OdRxValue curVal;

        if (pCurProp->getValue(pCurObject, curVal) != eOk)
          break;

        if (!curVal.type().isReference())
          break;

        pCurObject = curVal.type().reference()->dereference(curVal, IOdRxReferenceType::kForWrite);

        if (!pCurObject)
          break;
      }
    }
  }
  catch (...)
  {
    pCollectionProp = NULL;
  }

  if( pCollectionProp.isNull() || !pCollectionProp->isKindOf(OdRxCollectionProperty::desc()) )
    return OdRxCollectionPropertyPtr();

  return pCollectionProp;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDAComboBox::getPropertyValueAndInitCBData()
{
  OdRxValue propValue;

  bool bRet = getCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, propValue);

  if( bRet )
  {
    if ((m_uValueType == CCDAComboBox::kEnum) && propValue.type().isEnum())
    {
      const IOdRxEnumeration* pEnumData = propValue.type().enumeration();
      const OdRxEnumTag*      pCurTag = propValue.getEnumTag();

      if (pCurTag)
      {
        m_iCurIndex = -1;

        OdString strItemName = pCurTag->name();

        for (OdInt32 i = 0; i < pEnumData->count(); i++)
        {
          const OdRxEnumTag& enumTag = pEnumData->getAt(i);
          OdString strName = enumTag.name();
          OdString strCBName = strName;

          if( strCBName.reverseFind(L':') != -1 )
            strCBName = strCBName.right(strCBName.getLength() - strCBName.reverseFind(L':') - 1);

          AddString(strCBName);

          if (strName == strItemName)
            m_iCurIndex = i;
        }

        if (m_iCurIndex >= 0)
        {
          SetCurSel(m_iCurIndex);
          SetWindowText(strItemName);
        }
        else
          bRet = false;
      }
      else
        bRet = false;
    }
    else if ((m_uValueType == CCDAComboBox::kCollection) && propValue.type().isReference())
    {
      OdRxPropertyBase* pActualProperty = getActualProperty(m_pObject, m_pProperty, m_iSubPropertyIndex, m_iArrayIndex);

      OdRxAttributeCollection& attrCollection = pActualProperty->attributes();

      OdRxAttribute* pRefToAttr = attrCollection.get(OdRxRefersToAttribute::desc());

      if( pRefToAttr )
      {
        OdRxRefersToAttribute* pRefTo = (OdRxRefersToAttribute*)(pRefToAttr);
        OdString strPath = pRefTo->path();
        strPath.replace(L'\\', L'/');

        while( !strPath.isEmpty() )
        {
          if( strPath.find(L'/') != -1 )
          {
            OdString strItem = strPath.left(strPath.find(L'/'));
            strPath = strPath.right(strPath.getLength() - strItem.getLength() - 1);

            if( !strItem.isEmpty() )
              m_arrPathToCollection.push_back(strItem);
          }
          else
          {
            m_arrPathToCollection.push_back(strPath);
            break;
          }
        }

        OdRxObjectPtr             pCollectionOwner;
        OdRxCollectionPropertyPtr pCollection = getCollectionProperty(m_arrPathToCollection, m_pDb, pCollectionOwner);

        if( !pCollection.isNull() )
        {
          OdRxValueIteratorPtr pCollectionIter = pCollection->newValueIterator(pCollectionOwner);

          OdInt32 iCount = 0;

          for(; !pCollectionIter->done(); pCollectionIter->next())
          {
            OdRxValue curVal = pCollectionIter->current();

            if( curVal == propValue )
            {
              m_iCurIndex = iCount;
              bRet = true;
            }

            iCount++;

            if( !curVal.type().isReference() )
            {
              bRet = false;
              break;
            }

            OdRxObjectPtr pItemObject = curVal.type().reference()->dereference(curVal, IOdRxReferenceType::kForWrite);

            if( pItemObject.isNull() )
              AddString(L"NULL");
            else
            {
              bool bSetDefaultName = true;

              OdRxMemberPtr pProp = OdRxMemberQueryEngine::theEngine()->find(pItemObject, L"Name");

              if( !pProp.isNull() && pProp->isKindOf(OdRxProperty::desc()) )
              {
                OdRxPropertyPtr pPropName = pProp;

                OdRxValue rxValName;

                if( pPropName->getValue(pItemObject, rxValName) == eOk )
                {
                  AddString(rxValName.toString());
                  bSetDefaultName = false;
                }
              }

              if (bSetDefaultName)
              {
                bRet = false;
                break;
              }
            }
          }
        }
        else
          bRet = false;

        if (bRet)
        {
          if( m_iCurIndex >= 0 )
            SetCurSel(m_iCurIndex);
          else
            bRet = false;
        }
      }
      else
        bRet = false;
    }
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDAComboBox::setPropertyValue(OdInt32 iCBIndex)
{
  OdRxValue newValue;

  bool bRet = false;

  if (m_uValueType == CCDAComboBox::kEnum)
  {
    OdRxValue oldValue;
    bRet = getCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, oldValue);

    if (bRet && oldValue.type().isEnum())
    {
      const IOdRxEnumeration* pEnumData = oldValue.type().enumeration();

      if (pEnumData && (pEnumData->count() > iCBIndex))
      {
        newValue = pEnumData->getAt(iCBIndex).value();
        bRet = setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newValue);
      }
    }
  }
  else if (m_uValueType == CCDAComboBox::kCollection)
  {
    OdRxObjectPtr             pCollectionOwner;
    OdRxCollectionPropertyPtr pCollection = getCollectionProperty(m_arrPathToCollection, m_pDb, pCollectionOwner);

    if (!pCollection.isNull())
    {
      OdRxValueIteratorPtr pCollectionIter = pCollection->newValueIterator(pCollectionOwner);

      OdInt32 iCount = 0;

      for (; !pCollectionIter->done(); pCollectionIter->next())
      {
        OdRxValue curVal = pCollectionIter->current();

        if( iCount == iCBIndex)
        {
          newValue = curVal;
          bRet = setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newValue);
          break;
        }

        iCount++;
      }
    }
    else
      bRet = false;
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

OdUInt32 CCDAComboBox::getRscIndex() const
{
  return m_uRscIndex;
}

/////////////////////////////////////////////////////////////////////////////

BOOL CCDAComboBox::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pRes)
{
  if (message == WM_COMMAND)
  {
    OdUInt32 uCommand = wParam;
    uCommand = uCommand >> 16;
    uCommand = uCommand & 0xFFFF;

    if (uCommand == CBN_SELCHANGE)
    {
      OdInt32 iCurSel = GetCurSel();

      if ((iCurSel >= 0) && iCurSel != m_iCurIndex)
      {
        if (setPropertyValue(iCurSel))
        {
          m_iCurIndex = iCurSel;
        }
        else
        {
          SetCurSel(m_iCurIndex);
        }
      }
    }
  }

  return CComboBox::OnChildNotify(message, wParam, lParam, pRes);
}

/////////////////////////////////////////////////////////////////////////////

bool CCDAComboBox::initData(OdRxObject* pDb,
                              OdRxObject* pObject,
                                OdRxPropertyBase* pPropertyBase,
                                  CCDAComboBoxValueTypes uValueType,
                                    const CRect& btnRect,
                                      CWnd* pParentWnd,
                                        OdUInt32 uRscIndex,
                                          OdInt32 iSubPropertyIndex,
                                            OdInt32 iArrayIndex)
{
  bool bRet = false;
  m_pDb = pDb;
  m_pObject = pObject;
  m_pProperty = pPropertyBase;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_iArrayIndex = iArrayIndex;
  m_uValueType = uValueType;

  OdString  strName = getPropertyName(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

  m_bReadOnly = pPropertyBase->isReadOnly(m_pObject);

  if (pPropertyBase->isKindOf(OdRxCollectionProperty::desc()) && !pPropertyBase->isKindOf(OdRxIndexedProperty::desc()))
    m_bReadOnly = true;

  m_uRscIndex = uRscIndex;

  CRect cbRect = btnRect;

  cbRect.bottom += (btnRect.bottom - btnRect.top) * 6;

  Create(WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | CBS_DROPDOWNLIST| CBS_HASSTRINGS | WS_VSCROLL, cbRect, pParentWnd, uRscIndex);

  bRet = getPropertyValueAndInitCBData();

  if (bRet)
  {
    EnableWindow(!m_bReadOnly);
    SetFont(pParentWnd->GetFont());
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCDAComboBox, CComboBox)
  //{{AFX_MSG_MAP(CCDAComboBox)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDADateTimeCtrl

IMPLEMENT_DYNCREATE(CCDADateTimeCtrl, CDateTimeCtrl)

/////////////////////////////////////////////////////////////////////////////

CCDADateTimeCtrl::CCDADateTimeCtrl()
{
  m_pDb = NULL;
  m_pObject = NULL;
  m_pProperty = NULL;
  m_iArrayIndex = -1;
  m_iSubPropertyIndex = -1;
  m_bReadOnly = true;
  m_uRscIndex = 0;
}

/////////////////////////////////////////////////////////////////////////////

CCDADateTimeCtrl::~CCDADateTimeCtrl()
{}

/////////////////////////////////////////////////////////////////////////////

CWnd* CCDADateTimeCtrl::createCDADateTimeCtrl(OdRxObject* pDb,
  OdRxObject* pObject,
  OdRxPropertyBase* pProperty,
  const CRect& btnRect,
  CWnd* pParentWnd,
  OdUInt32 uRscIndex,
  OdInt32 iSubPropertyIndex,
  OdInt32 iArrayIndex)
{
  CCDADateTimeCtrl* pRet = new CCDADateTimeCtrl();

  if (pRet->initData(pDb, pObject, pProperty, btnRect, pParentWnd, uRscIndex, iSubPropertyIndex, iArrayIndex))
    return pRet;

  delete pRet;

  return NULL;
}

/////////////////////////////////////////////////////////////////////////////

OdUInt32 CCDADateTimeCtrl::getRscIndex() const
{
  return m_uRscIndex;
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CCDADateTimeCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT pRet = CDateTimeCtrl::WindowProc(message, wParam, lParam);

  if(message == WM_NOTIFY)
  {
    UpdateData(true);
    CTime newTime;
    GetTime(newTime);
    SYSTEMTIME dateTime;

    if (newTime != m_oldTime && newTime.GetAsSystemTime(dateTime) )
    {
      
      OdTimeStamp odTime;
      odTime.setDate(dateTime.wMonth, dateTime.wDay, dateTime.wYear);
      odTime.setTime(dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds);

      OdRxValue newValue(odTime);

      if( setCDAPropertyValue( m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newValue) )
        m_oldTime = newTime;
    }
  }

  return pRet;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDADateTimeCtrl::initData(OdRxObject* pDb,
  OdRxObject* pObject,
  OdRxPropertyBase* pPropertyBase,
  const CRect& btnRect,
  CWnd* pParentWnd,
  OdUInt32 uRscIndex,
  OdInt32 iSubPropertyIndex,
  OdInt32 iArrayIndex)
{
  bool bRet = false;
  m_pDb = pDb;
  m_pObject = pObject;
  m_pProperty = pPropertyBase;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_iArrayIndex = iArrayIndex;

  OdString  strName = getPropertyName(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

  m_bReadOnly = pPropertyBase->isReadOnly(m_pObject);

  if (pPropertyBase->isKindOf(OdRxCollectionProperty::desc()) && !pPropertyBase->isKindOf(OdRxIndexedProperty::desc()))
    m_bReadOnly = true;

  m_uRscIndex = uRscIndex;

  CRect cbRect = btnRect;

  cbRect.bottom += (btnRect.bottom - btnRect.top) * 6;

  cbRect.InflateRect(0, 4, 0, 0);

  Create(WS_VISIBLE | WS_CHILD | WS_BORDER, cbRect, pParentWnd, uRscIndex);

  OdRxValue propValue;

  if( getCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, propValue) )
  {
    OdTimeStamp* pDateTime = rxvalue_cast<OdTimeStamp>(&propValue);

    if (pDateTime)
    {
      SYSTEMTIME dateTime;
      dateTime.wYear = pDateTime->year();
      dateTime.wMonth = pDateTime->month();
      dateTime.wDay = pDateTime->day();
      dateTime.wHour = pDateTime->hour();
      dateTime.wMinute = pDateTime->minute();
      dateTime.wSecond = pDateTime->second();
      dateTime.wMilliseconds = pDateTime->millisecond();
      CTime setTime(dateTime);
      SetTime(&setTime);
      SetFormat(L"dd.MM.yyyy HH:MM:ss");
      bRet = true;
      m_oldTime = setTime;
    }
    else
      bRet = false;
  }
  else
    bRet = false;

  if (bRet)
  {
    EnableWindow(!m_bReadOnly);
    SetFont(pParentWnd->GetFont());
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCDADateTimeCtrl, CDateTimeCtrl)
  //{{AFX_MSG_MAP(CCDADateTimeCtrl)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDAStdTypeButton

IMPLEMENT_DYNCREATE(CCDAStdTypeButton, CButton)

/////////////////////////////////////////////////////////////////////////////

CCDAStdTypeButton::CCDAStdTypeButton()
{
  m_pDb = NULL;
  m_pObject = NULL;
  m_pProperty = NULL;
  m_iArrayIndex = -1;
  m_iSubPropertyIndex = -1;
  m_bReadOnly = true;
  m_uRscIndex = 0;
}

/////////////////////////////////////////////////////////////////////////////

CCDAStdTypeButton::~CCDAStdTypeButton()
{}

/////////////////////////////////////////////////////////////////////////////

CWnd* CCDAStdTypeButton::createCDAStdButton(OdRxObject* pDb,
                                              OdRxObject* pObject,
                                                OdRxPropertyBase* pProperty,
                                                  CCDAStdButtonValueTypes uValueType,
                                                    const CRect& btnRect,
                                                      CWnd* pParentWnd,
                                                        OdUInt32 uRscIndex,
                                                          OdInt32 iSubPropertyIndex,
                                                            OdInt32 iArrayIndex)
{
  CCDAStdTypeButton* pRet = new CCDAStdTypeButton();

  if (pRet->initData(pDb, pObject, pProperty, uValueType, btnRect, pParentWnd, uRscIndex, iSubPropertyIndex, iArrayIndex))
    return pRet;

  delete pRet;

  return NULL;
}

/////////////////////////////////////////////////////////////////////////////

OdString CCDAStdTypeButton::getPropertyValueStr(const OdRxValue& propValue)
{
  OdString strRet = OdString::kEmpty;

  switch( m_uValueType )
  {
    case CCDAStdTypeButton::kUnionType:
    {
      if (propValue.type() == OdRxValueType::Desc<void>::value())
        strRet = L"Empty";
      else if (propValue.type() == OdRxValueType::Desc<OdRxObjectPtr>::value())
      {
        const OdRxObjectPtr* pValue = rxvalue_cast<OdRxObjectPtr>(&propValue);

        if( pValue && pValue->isNull() )
          strRet = L"Empty";
        else
          strRet = (*pValue)->isA()->name();
      }
      else
        strRet = propValue.toString();
    } break;

    case CCDAStdTypeButton::kRxObject:
    {
      const OdRxObjectPtr* pValue = rxvalue_cast<OdRxObjectPtr>(&propValue);

      if( pValue )
      {
        OdRxMemberPtr pProp = OdRxMemberQueryEngine::theEngine()->find(pValue->get(), L"Name");

        if (!pProp.isNull() && pProp->isKindOf(OdRxProperty::desc()))
        {
          OdRxPropertyPtr pPropName = pProp;
          OdRxValue nameValue;

          if (!pPropName.isNull() && pPropName->getValue(pValue->get(), nameValue) == eOk)
            strRet = nameValue.toString();
        }
        
        if (strRet.isEmpty() )
          strRet = (*pValue)->isA()->name();
      }
    } break;

    case CCDAStdTypeButton::kReference:
    {
      const OdRxObject* pValue = propValue.type().reference()->dereference(propValue, IOdRxReferenceType::kForWrite);

      if (pValue == m_pObject)
      {
        strRet = propValue.toString();
      }
      else if (pValue)
      {
        OdRxMemberPtr pProp = OdRxMemberQueryEngine::theEngine()->find(pValue, L"Name");

        if (!pProp.isNull() && pProp->isKindOf(OdRxProperty::desc()))
        {
          OdRxPropertyPtr pPropName = pProp;
          OdRxValue nameValue;

          if (!pPropName.isNull() && pPropName->getValue(pValue, nameValue) == eOk)
            strRet = nameValue.toString();
        }
      }
      

      if( strRet.isEmpty() )
        strRet = pValue->isA()->name();

    } break;

    case CCDAStdTypeButton::kBoolArray :
    {
      const OdArray<bool>* pValue = rxvalue_cast<OdArray<bool> >(&propValue);

      if( pValue )
      {
        strRet = L"{";

        for( OdUInt32 i = 0; i < pValue->size(); i++ )
          strRet += (*pValue)[i] ? L"true," : L"false,";

        if(strRet.getLength() > 1 )
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kInt8Array :
    {
      const OdArray<OdInt8>* pValue = rxvalue_cast<OdArray<OdInt8>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for( OdUInt32 i = 0; i < pValue->size(); i++ )
        {
          OdString strItem;
          strItem.format(L"%d,", (*pValue)[i]);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kInt16Array :
    {
      const OdArray<OdInt16>* pValue = rxvalue_cast<OdArray<OdInt16>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          strItem.format(L"%d,", (*pValue)[i]);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kInt32Array :
    {
      const OdArray<OdInt32>* pValue = rxvalue_cast<OdArray<OdInt32>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          strItem.format(L"%d,", (*pValue)[i]);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kInt64Array :
    {
      const OdArray<OdInt64>* pValue = rxvalue_cast<OdArray<OdInt64>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          strItem.format(L"%d,", (*pValue)[i]);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kUInt8Array:
    {
      const OdArray<OdUInt8>* pValue = rxvalue_cast<OdArray<OdUInt8>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          strItem.format(L"%d,", (*pValue)[i]);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kUInt16Array:
    {
      const OdArray<OdUInt16>* pValue = rxvalue_cast<OdArray<OdUInt16>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          strItem.format(L"%d,", (*pValue)[i]);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kUInt32Array:
    {
      const OdArray<OdUInt32>* pValue = rxvalue_cast<OdArray<OdUInt32>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          strItem.format(L"%d,", (*pValue)[i]);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kUInt64Array:
    {
      const OdArray<OdUInt64>* pValue = rxvalue_cast<OdArray<OdUInt64>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          strItem.format(L"%d,", (*pValue)[i]);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kDoubleArray :
    {
      const OdArray<double>* pValue = rxvalue_cast<OdArray<double>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          strItem.format(L"%0.3f,", (*pValue)[i]);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kFloatArray :
    {
      const OdArray<float>* pValue = rxvalue_cast<OdArray<float>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          strItem.format(L"%0.3f,", (*pValue)[i]);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kStringArray :
    {
      const OdArray<OdString>* pValue = rxvalue_cast<OdArray<OdString>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem = (*pValue)[i];
          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kAnsiStringArray :
    {
      const OdArray<OdAnsiString>* pValue = rxvalue_cast<OdArray<OdAnsiString>>(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem = (*pValue)[i];
          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kDouble2dArray :
    {
      const OdArray<OdArray<double> >* pValue = rxvalue_cast<OdArray<OdArray<double> > >(&propValue);

      if (pValue)
      {
        strRet = L"[";

        for (OdUInt32 i = 0; i < (*pValue).size(); i++)
        {
          OdString strRow;
          strRow = L"{";

          for (OdUInt32 j = 0; j < (*pValue)[i].size(); j++)
          {
            OdString strItem;
            strItem.format(L"%0.3f,", (*pValue)[i][j]);
            strRet += strItem;
          }

          if (strRow.getLength() > 1)
            strRow = strRow.left(strRet.getLength() - 1);

          strRet += strRow;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"]";
      }
    } break;

    case CCDAStdTypeButton::kInt322dArray :
    {
      const OdArray<OdArray<int> >* pValue = rxvalue_cast<OdArray<OdArray<int> > >(&propValue);

      if (pValue)
      {
        strRet = L"[";

        for (OdUInt32 i = 0; i < (*pValue).size(); i++)
        {
          OdString strRow;
          strRow = L"{";

          for (OdUInt32 j = 0; j < (*pValue)[i].size(); j++)
          {
            OdString strItem;
            strItem.format(L"%d,", (*pValue)[i][j]);
            strRet += strItem;
          }

          if (strRow.getLength() > 1)
            strRow = strRow.left(strRet.getLength() - 1);

          strRet += strRow;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"]";
      }
    } break;

    case CCDAStdTypeButton::kPoint3dArray :
    {
      const OdArray<OdGePoint3d>* pValue = rxvalue_cast<OdArray<OdGePoint3d> >(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          strItem.format(L"{%0.3f,%0.3f,%0.3f},", (*pValue)[i].x, (*pValue)[i].y, (*pValue)[i].z);

          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kTimeStampArray :
    {
      const OdArray<OdTimeStamp>* pValue = rxvalue_cast<OdArray<OdTimeStamp> >(&propValue);

      if (pValue)
      {
        strRet = L"{";

        for (OdUInt32 i = 0; i < pValue->size(); i++)
        {
          OdString strItem;
          (*pValue)[i].strftime(L"%d.%m.%Y %H:%M:%S,", strItem);
          strRet += strItem;
        }

        if (strRet.getLength() > 1)
          strRet = strRet.left(strRet.getLength() - 1);

        strRet += L"}";
      }
    } break;

    case CCDAStdTypeButton::kPoint2d :
    {
      const OdGePoint2d* pValue = rxvalue_cast<OdGePoint2d>(&propValue);

      if (pValue)
      {
        strRet.format(L"{%0.3f,%0.3f}", pValue->x, pValue->y);
      }
    } break;

    case CCDAStdTypeButton::kPoint3d :
    {
      const OdGePoint3d* pValue = rxvalue_cast<OdGePoint3d>(&propValue);

      if (pValue)
      {
        strRet.format(L"{%0.3f,%0.3f,%0.3f}", pValue->x, pValue->y, pValue->z);
      }
    } break;

    case CCDAStdTypeButton::kVector2d :
    {
      const OdGeVector2d* pValue = rxvalue_cast<OdGeVector2d>(&propValue);

      if (pValue)
      {
        strRet.format(L"{%0.3f,%0.3f}", pValue->x, pValue->y);
      }
    } break;

    case CCDAStdTypeButton::kVector3d :
    {
      const OdGeVector3d* pValue = rxvalue_cast<OdGeVector3d>(&propValue);

      if (pValue)
      {
        strRet.format(L"{%0.3f,%0.3f,%0.3f}", pValue->x, pValue->y, pValue->z);
      }
    } break;

    case CCDAStdTypeButton::kScale3d :
    {
      const OdGeScale3d* pValue = rxvalue_cast<OdGeScale3d>(&propValue);

      if (pValue)
      {
        strRet.format(L"{%0.3f,%0.3f,%0.3f}", pValue->sx, pValue->sy, pValue->sz);
      }
    } break;

    case CCDAStdTypeButton::kOdDbHandle :
    {
      const OdDbHandle* pValue = rxvalue_cast<OdDbHandle>(&propValue);

      if (pValue)
      {
        strRet.format(L"%d", (OdUInt64)(*pValue));
      }
    } break;

    case CCDAStdTypeButton::kOdRect:
    {
      const ODRECT* pValue = rxvalue_cast<ODRECT>(&propValue);

      if (pValue)
      {
        strRet.format(L"%d,%d,%d,%d", pValue->left, pValue->top, pValue->right, pValue->bottom);
      }
    } break;

    case CCDAStdTypeButton::kExtents2d :
    {
      const OdGeExtents2d* pValue = rxvalue_cast<OdGeExtents2d>(&propValue);

      if (pValue)
      {
        strRet.format(L"%0.3f,%0.3f - %0.3f,%0.3f", pValue->minPoint().x, pValue->minPoint().y, pValue->maxPoint().x, pValue->maxPoint().y);
      }
    } break;

    case CCDAStdTypeButton::kExtents3d :
    {
      const OdGeExtents3d* pValue = rxvalue_cast<OdGeExtents3d>(&propValue);

      if (pValue)
      {
        strRet.format(L"%0.3f,%0.3f,%0.3f - %0.3f,%0.3f,%0.3f", pValue->minPoint().x, pValue->minPoint().y, pValue->minPoint().z, pValue->maxPoint().x, pValue->maxPoint().y, pValue->maxPoint().z);
      }
    } break;

    case CCDAStdTypeButton::kMatrix2d :
    {
      const OdGeMatrix2d* pValue = rxvalue_cast<OdGeMatrix2d>(&propValue);

      if (pValue)
      {
        strRet.format(L"(%0.3f,%0.3f,%0.3f,%0.3f)", (*pValue)[0][0], (*pValue)[0][1], (*pValue)[1][0], (*pValue)[1][1]);
      }
    } break;

    case CCDAStdTypeButton::kMatrix3d :
    {
      const OdGeMatrix3d* pValue = rxvalue_cast<OdGeMatrix3d>(&propValue);

      if (pValue)
      {
        strRet.format(L"(%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f)", (*pValue)[0][0], (*pValue)[0][1], (*pValue)[0][2], 
          (*pValue)[1][0], (*pValue)[1][1], (*pValue)[1][2], (*pValue)[2][0], (*pValue)[2][1],(*pValue)[2][2]);
      }
    } break;

    case CCDAStdTypeButton::kQuaternion :
    {
      const OdGeQuaternion* pValue = rxvalue_cast<OdGeQuaternion>(&propValue);

      if (pValue)
      {
        strRet.format(L"(%0.3f,%0.3f,%0.3f,%0.3f)", pValue->x, pValue->y, pValue->z, pValue->w);
      }
    } break;

    case CCDAStdTypeButton::kDoubleColor :
    {
      const OdGiColorRGB* pValue = rxvalue_cast<OdGiColorRGB>(&propValue);

      if (pValue)
      {
        strRet.format(L"(%0.3f,%0.3f,%0.3f)", pValue->red, pValue->green, pValue->blue);
      }
    } break;

    case CCDAStdTypeButton::kMaterialColor :
    {
      const OdGiMaterialColor* pValue = rxvalue_cast<OdGiMaterialColor>(&propValue);

      if (pValue)
      {
        if( pValue->method() == OdGiMaterialColor::kInherit )
          strRet.format(L"kInherit, %0.3f - ", pValue->factor());
        else
          strRet.format(L"kOverride, %0.3f - ", pValue->factor());

        OdCmEntityColor clrColor = pValue->color();

        if (clrColor.isByLayer())
          strRet += L"kByLayer";
        else if (clrColor.isByBlock())
          strRet += L"kByLayer";
        else if (clrColor.isByACI() || clrColor.isByDgnIndex())
        {
          OdString indexStr;
          indexStr.format(L" kByIndex (%d)", clrColor.colorIndex());
          strRet += indexStr;
        }
        else if (clrColor.isByColor())
        {
          OdString indexStr;
          indexStr.format(L" kByColor (%d,%d,%d)", clrColor.red(), clrColor.green(), clrColor.blue());
          strRet += indexStr;
        }
      }
    } break;

    case CCDAStdTypeButton::kCmTransparency :
    {
      const OdCmTransparency* pValue = rxvalue_cast<OdCmTransparency>(&propValue);

      if (pValue)
      {
        strRet.format(L"%d", (OdUInt8)((1.0 - pValue->alphaPercent()) * 100.0));
        strRet += L"%";
      }
    } break;
  }

  return strRet;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDAStdTypeButton::onButtonClick()
{
  bool bRet = false;

  OdRxValue propValue;

  if (!getCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, propValue) && (m_uValueType != CCDAStdTypeButton::kUnionType))
    return bRet;

  switch( m_uValueType )
  {
    case CCDAStdTypeButton::kUnionType:
    {
      CCDAUnionTypeDlg dlg(NULL, m_pObject, m_pDb, m_pProperty, m_iSubPropertyIndex, m_iArrayIndex);

      dlg.DoModal();
    } break;

    case CCDAStdTypeButton::kReference:
    {
      if( propValue.type().isReference() )
      {
        OdRxObjectPtr pValue = propValue.type().reference()->dereference(propValue, IOdRxReferenceType::kForWrite);

        if( pValue )
        {
          CCDAPropertiesDlg dlg(NULL, m_pDb, pValue);

          dlg.DoModal();
        }
      }
    } break;

    case CCDAStdTypeButton::kRxObject:
    {
      OdRxObjectPtr* pObjValue = rxvalue_cast<OdRxObjectPtr>(&propValue);

      if( pObjValue && !pObjValue->isNull() )
      {
        OdRxObjectPtr pValue = *pObjValue;

        if (pValue)
        {
          CCDAPropertiesDlg dlg(NULL, m_pDb, pValue);

          dlg.DoModal();
        }
      }
    } break;

    case CCDAStdTypeButton::kBoolArray:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kBool, !m_bReadOnly, m_strName);

      OdArray<bool>* pArrValue = rxvalue_cast<OdArray<bool> >(&propValue);

      if( pArrValue )
        dlg.m_boolArr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_boolArr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kInt8Array:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kInt8, !m_bReadOnly, m_strName);

      OdArray<OdInt8>* pArrValue = rxvalue_cast<OdArray<OdInt8> >(&propValue);

      if (pArrValue)
        dlg.m_int8Arr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_int8Arr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
      else
        bRet = false;
    } break;

    case CCDAStdTypeButton::kInt16Array:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kInt16, !m_bReadOnly, m_strName);

      OdArray<OdInt16>* pArrValue = rxvalue_cast<OdArray<OdInt16>>(&propValue);

      if (pArrValue)
        dlg.m_int16Arr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_int16Arr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kInt32Array:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kInt32, !m_bReadOnly, m_strName);

      OdArray<OdInt32>* pArrValue = rxvalue_cast<OdArray<OdInt32>>(&propValue);

      if (pArrValue)
        dlg.m_int32Arr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_int32Arr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kInt64Array:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kInt64, !m_bReadOnly, m_strName);

      OdArray<OdInt64>* pArrValue = rxvalue_cast<OdArray<OdInt64>>(&propValue);

      if (pArrValue)
        dlg.m_int64Arr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_int64Arr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kUInt8Array:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kUInt8, !m_bReadOnly, m_strName);

      OdArray<OdUInt8>* pArrValue = rxvalue_cast<OdArray<OdUInt8>>(&propValue);

      if (pArrValue)
        dlg.m_uInt8Arr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_uInt8Arr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kUInt16Array:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kUInt16, !m_bReadOnly, m_strName);

      OdArray<OdUInt16>* pArrValue = rxvalue_cast<OdArray<OdUInt16>>(&propValue);

      if (pArrValue)
        dlg.m_uInt16Arr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_uInt16Arr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kUInt32Array:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kUInt32, !m_bReadOnly, m_strName);

      OdArray<OdUInt32>* pArrValue = rxvalue_cast<OdArray<OdUInt32>>(&propValue);

      if (pArrValue)
        dlg.m_uInt32Arr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_uInt32Arr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kUInt64Array:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kUInt64, !m_bReadOnly, m_strName);

      OdArray<OdUInt64>* pArrValue = rxvalue_cast<OdArray<OdUInt64>>(&propValue);

      if (pArrValue)
        dlg.m_uInt64Arr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_uInt64Arr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kDoubleArray:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kDouble, !m_bReadOnly, m_strName);

      OdArray<double>* pArrValue = rxvalue_cast<OdArray<double>>(&propValue);

      if (pArrValue)
        dlg.m_doubleArr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_doubleArr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kFloatArray:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kFloat, !m_bReadOnly, m_strName);

      OdArray<float>* pArrValue = rxvalue_cast<OdArray<float>>(&propValue);

      if (pArrValue)
        dlg.m_floatArr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_floatArr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kStringArray:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kString, !m_bReadOnly, m_strName);

      OdArray<OdString>* pArrValue = rxvalue_cast<OdArray<OdString>>(&propValue);

      if (pArrValue)
        dlg.m_stringArr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_stringArr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kAnsiStringArray:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kAnsiString, !m_bReadOnly, m_strName);

      OdArray<OdAnsiString>* pArrValue = rxvalue_cast<OdArray<OdAnsiString>>(&propValue);

      if (pArrValue)
        dlg.m_ansiStringArr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_ansiStringArr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kPoint3dArray:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kPoint3d, !m_bReadOnly, m_strName);

      OdArray<OdGePoint3d>* pArrValue = rxvalue_cast<OdArray<OdGePoint3d>>(&propValue);

      if (pArrValue)
        dlg.m_point3dArr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_point3dArr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kTimeStampArray:
    {
      CCDAStdArraySetValueDlg dlg(NULL, CCDAStdArraySetValueDlg::kDateTime, !m_bReadOnly, m_strName);

      OdArray<OdTimeStamp>* pArrValue = rxvalue_cast<OdArray<OdTimeStamp>>(&propValue);

      if (pArrValue)
        dlg.m_dateTimeArr = *pArrValue;

      if (pArrValue && dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(dlg.m_dateTimeArr);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kPoint2d:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kPoint2d, !m_bReadOnly, propValue, m_strName);

      if( dlg.DoModal() == IDOK && dlg.m_bDataModified )
      {
        OdRxValue newVal(OdGePoint2d(dlg.m_dX1, dlg.m_dY1));

        if( setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal) )
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kPoint3d:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kPoint3d, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(OdGePoint3d(dlg.m_dX1, dlg.m_dY1, dlg.m_dZ1));

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kVector2d:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kVector2d, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(OdGeVector2d(dlg.m_dX1, dlg.m_dY1));

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kVector3d:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kVector3d, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(OdGeVector3d(dlg.m_dX1, dlg.m_dY1, dlg.m_dZ1));

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kScale3d:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kScale3d, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(OdGeScale3d(dlg.m_dX1, dlg.m_dY1, dlg.m_dZ1));

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kOdDbHandle:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kHandle, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdRxValue newVal(OdDbHandle((OdUInt64)(dlg.m_dX1)));

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kOdRect:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kRect, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        ODRECT newRect;
        newRect.left  = (OdInt32)dlg.m_dX1;
        newRect.right = (OdInt32)dlg.m_dY1;
        newRect.top = (OdInt32)dlg.m_dZ1;
        newRect.bottom = (OdInt32)dlg.m_dW;
        OdRxValue newVal(newRect);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kExtents2d:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kExtents2d, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdGeExtents2d value;
        value.set(OdGePoint2d(dlg.m_dX1, dlg.m_dY1), OdGePoint2d(dlg.m_dX2, dlg.m_dY2));
        OdRxValue newVal(value);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kExtents3d:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kExtents3d, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdGeExtents3d value;
        value.set(OdGePoint3d(dlg.m_dX1, dlg.m_dY1, dlg.m_dZ1), OdGePoint3d(dlg.m_dX2, dlg.m_dY2, dlg.m_dZ2));
        OdRxValue newVal(value);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kMatrix2d:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kMatrix2d, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdGeMatrix2d value;
        value[0][0] = dlg.m_dX1;
        value[0][1] = dlg.m_dY1;
        value[1][0] = dlg.m_dX2;
        value[1][1] = dlg.m_dY2;

        OdRxValue newVal(value);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kMatrix3d:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kMatrix3d, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdGeMatrix3d value;
        value[0][0] = dlg.m_dX1;
        value[0][1] = dlg.m_dY1;
        value[0][2] = dlg.m_dZ1;
        value[1][0] = dlg.m_dX2;
        value[1][1] = dlg.m_dY2;
        value[1][2] = dlg.m_dZ2;
        value[2][0] = dlg.m_dX3;
        value[2][1] = dlg.m_dY3;
        value[2][2] = dlg.m_dZ3;

        OdRxValue newVal(value);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kQuaternion:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kQuaternion, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdGeQuaternion value;
        value.x = dlg.m_dX1;
        value.y = dlg.m_dY1;
        value.z = dlg.m_dZ1;
        value.w = dlg.m_dW;

        OdRxValue newVal(value);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kDoubleColor:
    {
      CCDAStdBtnSetValueDlg dlg(NULL, CCDAStdBtnSetValueDlg::kQuaternion, !m_bReadOnly, propValue, m_strName);

      if (dlg.DoModal() == IDOK && dlg.m_bDataModified)
      {
        OdGiColorRGB value;
        value.red   = dlg.m_dX1;
        value.green = dlg.m_dY1;
        value.blue  = dlg.m_dZ1;

        OdRxValue newVal(value);

        if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
        {
          OdString strBtnName = getPropertyValueStr(newVal);
          SetWindowTextW(strBtnName);
          bRet = true;
        }
      }
    } break;

    case CCDAStdTypeButton::kDouble2dArray:
    case CCDAStdTypeButton::kInt322dArray:
      bRet = false; break;
    case CCDAStdTypeButton::kMaterialColor:
      bRet = false; break;
    case CCDAStdTypeButton::kCmTransparency:
    {
      OdCmTransparency* pCurTrans = rxvalue_cast<OdCmTransparency>(&propValue);

      if( pCurTrans )
      {
        CCDASetTransperencyDlg dlg(NULL, *pCurTrans, !m_bReadOnly, m_strName);

        if( (dlg.DoModal() == IDOK) && dlg.m_bDataModified)
        {
          OdCmTransparency value;
          value.setAlphaPercent(1.0 - dlg.m_iValue / 100.0);

          OdRxValue newVal(value);

          if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newVal))
          {
            OdString strBtnName = getPropertyValueStr(newVal);
            SetWindowTextW(strBtnName);
            bRet = true;
          }
        }
      }
    } break;
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

OdUInt32 CCDAStdTypeButton::getRscIndex() const
{
  return m_uRscIndex;
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CCDAStdTypeButton::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT pRet = CButton::WindowProc(message, wParam, lParam);

  if( message == WM_LBUTTONUP )
  {
    onButtonClick();   
  }

  return pRet;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDAStdTypeButton::initData( OdRxObject* pDb,
                                    OdRxObject* pObject,
                                      OdRxPropertyBase* pPropertyBase,
                                        CCDAStdButtonValueTypes uValueType,
                                          const CRect& btnRect,
                                            CWnd* pParentWnd,
                                              OdUInt32 uRscIndex,
                                                OdInt32 iSubPropertyIndex,
                                                  OdInt32 iArrayIndex)
{
  bool bRet = false;
  m_pDb = pDb;
  m_pObject = pObject;
  m_pProperty = pPropertyBase;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_iArrayIndex = iArrayIndex;
  m_uValueType = uValueType;

  m_strName = getPropertyName(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

  m_bReadOnly = pPropertyBase->isReadOnly(m_pObject);

  if (pPropertyBase->isKindOf(OdRxCollectionProperty::desc()) && !pPropertyBase->isKindOf(OdRxIndexedProperty::desc()))
    m_bReadOnly = true;

  m_uRscIndex = uRscIndex;

  OdRxValue propValue;

  if(!getCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, propValue) && (m_uValueType != kUnionType))
    return false;

  OdRxObjectPtr pRxObj = NULL;

  if( (m_uValueType == CCDAStdButtonValueTypes::kRxObject) )
  {
    OdRxObjectPtr* pRxObjPtr = rxvalue_cast<OdRxObjectPtr>(&propValue);

    if (!pRxObjPtr || pRxObjPtr->isNull())
      return false;

    pRxObj = *pRxObjPtr;
  }
  else if ((m_uValueType == CCDAStdButtonValueTypes::kReference))
  {
    pRxObj = propValue.type().reference()->dereference(propValue, IOdRxReferenceType::kForWrite);

    if (!pRxObj)
      return false;
  }

  bRet = true;

  OdString strBtnName = getPropertyValueStr(propValue);

  Create(strBtnName, WS_VISIBLE | WS_BORDER | WS_CHILD | BS_CENTER | BS_PUSHBOX, btnRect, pParentWnd, uRscIndex);

  if (bRet)
  {
    switch (m_uValueType)
    {
      case CCDAStdTypeButton::kPoint2d:
      case CCDAStdTypeButton::kPoint3d:
      case CCDAStdTypeButton::kVector2d:
      case CCDAStdTypeButton::kVector3d:
      case CCDAStdTypeButton::kScale3d:
      case CCDAStdTypeButton::kOdDbHandle:
      case CCDAStdTypeButton::kCmTransparency:
        EnableWindow(!m_bReadOnly); break;
      case CCDAStdTypeButton::kRxObject:
      case CCDAStdTypeButton::kReference:
        EnableWindow(pRxObj.get() != m_pObject); break;
      default:
        EnableWindow(true); break;
    }
    SetFont(pParentWnd->GetFont());
    SetWindowText(strBtnName);
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCDAStdTypeButton, CButton)
  //{{AFX_MSG_MAP(CCDAStdTypeButton)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//=================================================================================
// CCDAStdBtnSetValueDlg dialog

IMPLEMENT_DYNAMIC(CCDAStdBtnSetValueDlg, CDialog)

CCDAStdBtnSetValueDlg::CCDAStdBtnSetValueDlg(CWnd* pParent, CCDAStdBtnSetValueDlgType uType, bool bEnable, const OdRxValue& propValue, const OdString& strPropName)
  : CDialog(CCDAStdBtnSetValueDlg::IDD, pParent)
{
  m_dX1 = 0.0;
  m_dX2 = 0.0;
  m_dX3 = 0.0;
  m_dY1 = 0.0;
  m_dY2 = 0.0;
  m_dY3 = 0.0;
  m_dZ1 = 0.0;
  m_dZ2 = 0.0;
  m_dZ3 = 0.0;
  m_dW  = 0.0;
  m_dOldX1 = 0.0;
  m_dOldX2 = 0.0;
  m_dOldX3 = 0.0;
  m_dOldY1 = 0.0;
  m_dOldY2 = 0.0;
  m_dOldY3 = 0.0;
  m_dOldZ1 = 0.0;
  m_dOldZ2 = 0.0;
  m_dOldZ3 = 0.0;
  m_dOldW = 0.0;
  m_uType = uType;
  m_bEnable = bEnable;
  m_value = propValue;
  m_strPropName = strPropName;
}

//=================================================================================

CCDAStdBtnSetValueDlg::~CCDAStdBtnSetValueDlg()
{}

//=================================================================================

void CCDAStdBtnSetValueDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Text(pDX, IDC_X1_EDIT, m_dX1);
  DDX_Text(pDX, IDC_X2_EDIT, m_dX2);
  DDX_Text(pDX, IDC_X3_EDIT, m_dX3);
  DDX_Text(pDX, IDC_Y1_EDIT, m_dY1);
  DDX_Text(pDX, IDC_Y2_EDIT, m_dY2);
  DDX_Text(pDX, IDC_Y3_EDIT, m_dY3);
  DDX_Text(pDX, IDC_Z1_EDIT, m_dZ1);
  DDX_Text(pDX, IDC_Z2_EDIT, m_dZ2);
  DDX_Text(pDX, IDC_Z3_EDIT, m_dZ3);
  DDX_Text(pDX, IDC_W_EDIT, m_dW);
}

//=================================================================================

BOOL CCDAStdBtnSetValueDlg::OnInitDialog()
{
  BOOL bRet = CDialog::OnInitDialog();

  OdString strCol1, strCol2;
  OdString strX1, strX2, strX3, strY1, strY2, strY3, strZ1, strZ2, strZ3, strW;
  bool     bVisibleX1, bVisibleX2, bVisibleX3, bVisibleY1, bVisibleY2, bVisibleY3, bVisibleZ1, bVisibleZ2, bVisibleZ3, bVisibleW, bVisibleCol1, bVisibleCol2;
  OdUInt32 nCols = 0, nRows = 0;

  switch( m_uType )
  {
  case CCDAStdBtnSetValueDlg::kHandle:
  {
    OdGePoint2d* pValue = rxvalue_cast<OdGePoint2d>(&m_value);
    m_dX1 = pValue->x;
    m_dY1 = pValue->y;

    strCol1 = L"DbHandle";
    strCol2 = L"DbHandle";
    strX1 = L"Value";
    strY1 = L"Y";
    strZ1 = L"Z";
    strX2 = L"X";
    strY2 = L"Y";
    strZ2 = L"Z";
    strX3 = L"X";
    strY3 = L"Y";
    strZ3 = L"Z";
    strW = L"W";
    bVisibleX1 = true;
    bVisibleY1 = false;
    bVisibleZ1 = false;
    bVisibleX2 = false;
    bVisibleY2 = false;
    bVisibleZ2 = false;
    bVisibleX3 = false;
    bVisibleY3 = false;
    bVisibleZ3 = false;
    bVisibleW = false;
    bVisibleCol1 = true;
    bVisibleCol2 = false;
    nCols = 1;
    nRows = 1;
  } break;

    case CCDAStdBtnSetValueDlg::kPoint2d:
    {
      OdGePoint2d* pValue = rxvalue_cast<OdGePoint2d>(&m_value);
      m_dX1 = pValue->x;
      m_dY1 = pValue->y;

      strCol1 = L"Point2d";
      strCol2 = L"Point2d";
      strX1   = L"X";
      strY1   = L"Y";
      strZ1   = L"Z";
      strX2   = L"X";
      strY2   = L"Y";
      strZ2   = L"Z";
      strX3   = L"X";
      strY3   = L"Y";
      strZ3   = L"Z";
      strW    = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = false;
      bVisibleX2 = false;
      bVisibleY2 = false;
      bVisibleZ2 = false;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = false;
      bVisibleCol1 = true;
      bVisibleCol2 = false;
      nCols = 1;
      nRows = 2;
    } break;

    case CCDAStdBtnSetValueDlg::kPoint3d:
    {
      OdGePoint3d* pValue = rxvalue_cast<OdGePoint3d>(&m_value);
      m_dX1 = pValue->x;
      m_dY1 = pValue->y;
      m_dZ1 = pValue->z;

      strCol1 = L"Point3d";
      strCol2 = L"Point3d";
      strX1 = L"X";
      strY1 = L"Y";
      strZ1 = L"Z";
      strX2 = L"X";
      strY2 = L"Y";
      strZ2 = L"Z";
      strX3 = L"X";
      strY3 = L"Y";
      strZ3 = L"Z";
      strW = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = true;
      bVisibleX2 = false;
      bVisibleY2 = false;
      bVisibleZ2 = false;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = false;
      bVisibleCol1 = true;
      bVisibleCol2 = false;
      nCols = 1;
      nRows = 3;
    } break;

    case CCDAStdBtnSetValueDlg::kVector2d:
    {
      OdGeVector2d* pValue = rxvalue_cast<OdGeVector2d>(&m_value);
      m_dX1 = pValue->x;
      m_dY1 = pValue->y;

      strCol1 = L"Vector2d";
      strCol2 = L"Vector2d";
      strX1 = L"X";
      strY1 = L"Y";
      strZ1 = L"Z";
      strX2 = L"X";
      strY2 = L"Y";
      strZ2 = L"Z";
      strX3 = L"X";
      strY3 = L"Y";
      strZ3 = L"Z";
      strW = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = false;
      bVisibleX2 = false;
      bVisibleY2 = false;
      bVisibleZ2 = false;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = false;
      bVisibleCol1 = true;
      bVisibleCol2 = false;
      nCols = 1;
      nRows = 2;
    } break;

    case CCDAStdBtnSetValueDlg::kVector3d:
    {
      OdGeVector3d* pValue = rxvalue_cast<OdGeVector3d>(&m_value);
      m_dX1 = pValue->x;
      m_dY1 = pValue->y;
      m_dZ1 = pValue->z;

      strCol1 = L"Vector3d";
      strCol2 = L"Vector3d";
      strX1 = L"X";
      strY1 = L"Y";
      strZ1 = L"Z";
      strX2 = L"X";
      strY2 = L"Y";
      strZ2 = L"Z";
      strX3 = L"X";
      strY3 = L"Y";
      strZ3 = L"Z";
      strW = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = true;
      bVisibleX2 = false;
      bVisibleY2 = false;
      bVisibleZ2 = false;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = false;
      bVisibleCol1 = true;
      bVisibleCol2 = false;
      nCols = 1;
      nRows = 3;
    } break;

    case CCDAStdBtnSetValueDlg::kScale3d:
    {
      OdGeScale3d* pValue = rxvalue_cast<OdGeScale3d>(&m_value);
      m_dX1 = pValue->sx;
      m_dY1 = pValue->sy;
      m_dZ1 = pValue->sz;

      strCol1 = L"Scale3d";
      strCol2 = L"Scale3d";
      strX1 = L"SX";
      strY1 = L"SY";
      strZ1 = L"SZ";
      strX2 = L"X";
      strY2 = L"Y";
      strZ2 = L"Z";
      strX3 = L"X";
      strY3 = L"Y";
      strZ3 = L"Z";
      strW = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = true;
      bVisibleX2 = false;
      bVisibleY2 = false;
      bVisibleZ2 = false;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = false;
      bVisibleCol1 = true;
      bVisibleCol2 = false;
      nCols = 1;
      nRows = 3;
    } break;

    case CCDAStdBtnSetValueDlg::kExtents2d:
    {
      OdGeExtents2d* pValue = rxvalue_cast<OdGeExtents2d>(&m_value);
      m_dX1 = pValue->minPoint().x;
      m_dY1 = pValue->minPoint().y;
      m_dX2 = pValue->maxPoint().x;
      m_dY2 = pValue->maxPoint().y;

      strCol1 = L"MinPoint2d";
      strCol2 = L"MaxPoint2d";
      strX1 = L"X";
      strY1 = L"Y";
      strZ1 = L"Z";
      strX2 = L"X";
      strY2 = L"Y";
      strZ2 = L"Z";
      strX3 = L"X";
      strY3 = L"Y";
      strZ3 = L"Z";
      strW = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = false;
      bVisibleX2 = true;
      bVisibleY2 = true;
      bVisibleZ2 = false;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = false;
      bVisibleCol1 = true;
      bVisibleCol2 = true;
      nCols = 2;
      nRows = 2;
    } break;

    case CCDAStdBtnSetValueDlg::kExtents3d:
    {
      OdGeExtents3d* pValue = rxvalue_cast<OdGeExtents3d>(&m_value);
      m_dX1 = pValue->minPoint().x;
      m_dY1 = pValue->minPoint().y;
      m_dZ1 = pValue->minPoint().z;
      m_dX2 = pValue->maxPoint().x;
      m_dY2 = pValue->maxPoint().y;
      m_dZ2 = pValue->maxPoint().z;

      strCol1 = L"MinPoint3d";
      strCol2 = L"MaxPoint3d";
      strX1 = L"X";
      strY1 = L"Y";
      strZ1 = L"Z";
      strX2 = L"X";
      strY2 = L"Y";
      strZ2 = L"Z";
      strX3 = L"X";
      strY3 = L"Y";
      strZ3 = L"Z";
      strW = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = true;
      bVisibleX2 = true;
      bVisibleY2 = true;
      bVisibleZ2 = true;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = false;
      bVisibleCol1 = true;
      bVisibleCol2 = true;
      nCols = 2;
      nRows = 3;
    } break;

    case CCDAStdBtnSetValueDlg::kMatrix2d:
    {
      OdGeMatrix2d* pValue = rxvalue_cast<OdGeMatrix2d>(&m_value);
      m_dX1 = (*pValue)[0][0];
      m_dY1 = (*pValue)[0][1];
      m_dX2 = (*pValue)[1][0];
      m_dY2 = (*pValue)[1][1];

      strCol1 = L"";
      strCol2 = L"";
      strX1 = L"M[0,0]";
      strY1 = L"M[0,1]";
      strZ1 = L"Z";
      strX2 = L"M[1,0]";
      strY2 = L"M[1,1]";
      strZ2 = L"Z";
      strX3 = L"X";
      strY3 = L"Y";
      strZ3 = L"Z";
      strW = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = false;
      bVisibleX2 = true;
      bVisibleY2 = true;
      bVisibleZ2 = false;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = false;
      bVisibleCol1 = false;
      bVisibleCol2 = false;
      nCols = 2;
      nRows = 2;
    } break;

    case CCDAStdBtnSetValueDlg::kMatrix3d:
    {
      OdGeMatrix3d* pValue = rxvalue_cast<OdGeMatrix3d>(&m_value);
      m_dX1 = (*pValue)[0][0];
      m_dY1 = (*pValue)[0][1];
      m_dZ1 = (*pValue)[0][2];
      m_dX2 = (*pValue)[1][0];
      m_dY2 = (*pValue)[1][1];
      m_dZ2 = (*pValue)[1][2];
      m_dX3 = (*pValue)[2][0];
      m_dY3 = (*pValue)[2][1];
      m_dZ3 = (*pValue)[2][2];

      strCol1 = L"";
      strCol2 = L"";
      strX1 = L"M[0,0]";
      strY1 = L"M[0,1]";
      strZ1 = L"M[0,2]";
      strX2 = L"M[1,0]";
      strY2 = L"M[1,1]";
      strZ2 = L"M[1,2]";
      strX3 = L"M[2,0]";
      strY3 = L"M[2,1]";
      strZ3 = L"M[2,2]";
      strW = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = true;
      bVisibleX2 = true;
      bVisibleY2 = true;
      bVisibleZ2 = true;
      bVisibleX3 = true;
      bVisibleY3 = true;
      bVisibleZ3 = true;
      bVisibleW = false;
      bVisibleCol1 = false;
      bVisibleCol2 = false;
      nCols = 3;
      nRows = 3;
    } break;

    case CCDAStdBtnSetValueDlg::kQuaternion:
    {
      OdGeQuaternion* pValue = rxvalue_cast<OdGeQuaternion>(&m_value);
      m_dX1 = pValue->x;
      m_dY1 = pValue->y;
      m_dZ1 = pValue->z;
      m_dW  = pValue->w;

      strCol1 = L"Quaternion";
      strCol2 = L"";
      strX1 = L"X";
      strY1 = L"Y";
      strZ1 = L"Z";
      strX2 = L"X";
      strY2 = L"Y";
      strZ2 = L"Z";
      strX3 = L"X";
      strY3 = L"Y";
      strZ3 = L"Z";
      strW = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = true;
      bVisibleX2 = false;
      bVisibleY2 = false;
      bVisibleZ2 = false;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = true;
      bVisibleCol1 = true;
      bVisibleCol2 = false;
      nCols = 1;
      nRows = 4;
    } break;

    case CCDAStdBtnSetValueDlg::kRect:
    {
      ODRECT* pValue = rxvalue_cast<ODRECT>(&m_value);
      m_dX1 = pValue->left;
      m_dY1 = pValue->right;
      m_dZ1 = pValue->top;
      m_dW = pValue->bottom;

      strCol1 = L"RECT";
      strCol2 = L"";
      strX1 = L"left";
      strY1 = L"right";
      strZ1 = L"top";
      strX2 = L"X";
      strY2 = L"Y";
      strZ2 = L"Z";
      strX3 = L"X";
      strY3 = L"Y";
      strZ3 = L"Z";
      strW = L"bottom";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = true;
      bVisibleX2 = false;
      bVisibleY2 = false;
      bVisibleZ2 = false;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = true;
      bVisibleCol1 = true;
      bVisibleCol2 = false;
      nCols = 1;
      nRows = 4;
    } break;

    case CCDAStdBtnSetValueDlg::kDoubleColor:
    {
      OdGiColorRGB* pValue = rxvalue_cast<OdGiColorRGB>(&m_value);
      m_dX1 = pValue->red;
      m_dY1 = pValue->green;
      m_dZ1 = pValue->blue;

      strCol1 = L"OdGiColorRGB";
      strCol2 = L"";
      strX1 = L"red";
      strY1 = L"green";
      strZ1 = L"blue";
      strX2 = L"X";
      strY2 = L"Y";
      strZ2 = L"Z";
      strX3 = L"X";
      strY3 = L"Y";
      strZ3 = L"Z";
      strW = L"W";
      bVisibleX1 = true;
      bVisibleY1 = true;
      bVisibleZ1 = true;
      bVisibleX2 = false;
      bVisibleY2 = false;
      bVisibleZ2 = false;
      bVisibleX3 = false;
      bVisibleY3 = false;
      bVisibleZ3 = false;
      bVisibleW = false;
      bVisibleCol1 = true;
      bVisibleCol2 = false;
      nCols = 1;
      nRows = 3;
    } break;
  }

  CWnd* pEditX1 = (CWnd*)GetDlgItem(IDC_X1_EDIT);
  CWnd* pEditX2 = (CWnd*)GetDlgItem(IDC_X2_EDIT);
  CWnd* pEditX3 = (CWnd*)GetDlgItem(IDC_X3_EDIT);
  CWnd* pEditY1 = (CWnd*)GetDlgItem(IDC_Y1_EDIT);
  CWnd* pEditY2 = (CWnd*)GetDlgItem(IDC_Y2_EDIT);
  CWnd* pEditY3 = (CWnd*)GetDlgItem(IDC_Y3_EDIT);
  CWnd* pEditZ1 = (CWnd*)GetDlgItem(IDC_Z1_EDIT);
  CWnd* pEditZ2 = (CWnd*)GetDlgItem(IDC_Z2_EDIT);
  CWnd* pEditZ3 = (CWnd*)GetDlgItem(IDC_Z3_EDIT);
  CWnd* pEditW  = (CWnd*)GetDlgItem(IDC_W_EDIT);
  CWnd* pStaticX1 = (CWnd*)GetDlgItem(IDC_X1_STATIC);
  CWnd* pStaticX2 = (CWnd*)GetDlgItem(IDC_X2_STATIC);
  CWnd* pStaticX3 = (CWnd*)GetDlgItem(IDC_X3_STATIC);
  CWnd* pStaticY1 = (CWnd*)GetDlgItem(IDC_Y1_STATIC);
  CWnd* pStaticY2 = (CWnd*)GetDlgItem(IDC_Y2_STATIC);
  CWnd* pStaticY3 = (CWnd*)GetDlgItem(IDC_Y3_STATIC);
  CWnd* pStaticZ1 = (CWnd*)GetDlgItem(IDC_Z1_STATIC);
  CWnd* pStaticZ2 = (CWnd*)GetDlgItem(IDC_Z2_STATIC);
  CWnd* pStaticZ3 = (CWnd*)GetDlgItem(IDC_Z3_STATIC);
  CWnd* pStaticW = (CWnd*)GetDlgItem(IDC_W_STATIC);
  CWnd* pStaticCol1 = (CWnd*)GetDlgItem(IDC_COL1_STATIC);
  CWnd* pStaticCol2 = (CWnd*)GetDlgItem(IDC_COL2_STATIC);
  CWnd* pOKBtn      = (CWnd*)GetDlgItem(IDOK);

  pStaticX1->SetWindowTextW(strX1);
  pStaticX2->SetWindowTextW(strX2);
  pStaticX3->SetWindowTextW(strX3);
  pStaticY1->SetWindowTextW(strY1);
  pStaticY2->SetWindowTextW(strY2);
  pStaticY3->SetWindowTextW(strY3);
  pStaticZ1->SetWindowTextW(strZ1);
  pStaticZ2->SetWindowTextW(strZ2);
  pStaticZ3->SetWindowTextW(strZ3);
  pStaticW->SetWindowTextW(strW);
  pStaticCol1->SetWindowTextW(strCol1);
  pStaticCol2->SetWindowTextW(strCol2);

  pEditX1->ShowWindow(bVisibleX1 ? SW_SHOW : SW_HIDE);
  pEditX2->ShowWindow(bVisibleX2 ? SW_SHOW : SW_HIDE);
  pEditX3->ShowWindow(bVisibleX3 ? SW_SHOW : SW_HIDE);
  pEditY1->ShowWindow(bVisibleY1 ? SW_SHOW : SW_HIDE);
  pEditY2->ShowWindow(bVisibleY2 ? SW_SHOW : SW_HIDE);
  pEditY3->ShowWindow(bVisibleY3 ? SW_SHOW : SW_HIDE);
  pEditZ1->ShowWindow(bVisibleZ1 ? SW_SHOW : SW_HIDE);
  pEditZ2->ShowWindow(bVisibleZ2 ? SW_SHOW : SW_HIDE);
  pEditZ3->ShowWindow(bVisibleZ3 ? SW_SHOW : SW_HIDE);
  pEditW->ShowWindow(bVisibleW ? SW_SHOW : SW_HIDE);
  pStaticX1->ShowWindow(bVisibleX1 ? SW_SHOW : SW_HIDE);
  pStaticX2->ShowWindow(bVisibleX2 ? SW_SHOW : SW_HIDE);
  pStaticX3->ShowWindow(bVisibleX3 ? SW_SHOW : SW_HIDE);
  pStaticY1->ShowWindow(bVisibleY1 ? SW_SHOW : SW_HIDE);
  pStaticY2->ShowWindow(bVisibleY2 ? SW_SHOW : SW_HIDE);
  pStaticY3->ShowWindow(bVisibleY3 ? SW_SHOW : SW_HIDE);
  pStaticZ1->ShowWindow(bVisibleZ1 ? SW_SHOW : SW_HIDE);
  pStaticZ2->ShowWindow(bVisibleZ2 ? SW_SHOW : SW_HIDE);
  pStaticZ3->ShowWindow(bVisibleZ3 ? SW_SHOW : SW_HIDE);
  pStaticW->ShowWindow(bVisibleW ? SW_SHOW : SW_HIDE);
  pStaticCol1->ShowWindow(bVisibleCol1 ? SW_SHOW : SW_HIDE);
  pStaticCol2->ShowWindow(bVisibleCol2 ? SW_SHOW : SW_HIDE);

  pEditX1->EnableWindow(m_bEnable ? TRUE : FALSE);
  pEditX2->EnableWindow(m_bEnable ? TRUE : FALSE);
  pEditX3->EnableWindow(m_bEnable ? TRUE : FALSE);
  pEditY1->EnableWindow(m_bEnable ? TRUE : FALSE);
  pEditY2->EnableWindow(m_bEnable ? TRUE : FALSE);
  pEditY3->EnableWindow(m_bEnable ? TRUE : FALSE);
  pEditZ1->EnableWindow(m_bEnable ? TRUE : FALSE);
  pEditZ2->EnableWindow(m_bEnable ? TRUE : FALSE);
  pEditZ3->EnableWindow(m_bEnable ? TRUE : FALSE);
  pEditW->EnableWindow(m_bEnable ? TRUE : FALSE);

  SetWindowTextW(m_strPropName);

  CRect editRect;
  CRect wndRect;
  CRect newRect;
  CRect btnRect;
  CRect newBtnRect;
  GetWindowRect(wndRect);
  pEditX1->GetWindowRect(editRect);
  pOKBtn->GetWindowRect(btnRect);

  OdUInt32 iTextWidth  = editRect.left - wndRect.left;
  OdUInt32 iTextHeight = editRect.top - wndRect.top;
  OdUInt32 iWidth  = (iTextWidth + editRect.right - editRect.left)*nCols + 25;
  OdUInt32 iHeight = iTextHeight * 2 + (editRect.bottom - editRect.top + 15)*nRows - 45;

  newRect = wndRect;
  newRect.bottom = wndRect.top + iHeight;
  newRect.right = wndRect.left + iWidth;

  MoveWindow(&newRect);

  newBtnRect.top = iHeight - 45 - btnRect.bottom + btnRect.top;
  newBtnRect.bottom = iHeight - 45;
  newBtnRect.left = iWidth / 2.0 - (btnRect.right - btnRect.left) / 2.0 - 5;
  newBtnRect.right = iWidth / 2.0 + (btnRect.right - btnRect.left) / 2.0 - 5;

  MoveWindow(&newRect);
  pOKBtn->MoveWindow(&newBtnRect);

  UpdateData(false);

  m_dOldX1 = m_dX1;
  m_dOldX2 = m_dX2;
  m_dOldX3 = m_dX3;
  m_dOldY1 = m_dY1;
  m_dOldY2 = m_dY2;
  m_dOldY3 = m_dY3;
  m_dOldZ1 = m_dZ1;
  m_dOldZ2 = m_dZ2;
  m_dOldZ3 = m_dZ3;
  m_dOldW  = m_dW;

  return bRet;
}

//=================================================================================

void CCDAStdBtnSetValueDlg::OnOk()
{
  UpdateData(true);

  m_bDataModified = false;

  if (!OdEqual(m_dX1, m_dOldX1) || !OdEqual(m_dX2, m_dOldX2) || !OdEqual(m_dX3, m_dOldX3) ||
    !OdEqual(m_dY1, m_dOldY1) || !OdEqual(m_dY2, m_dOldY2) || !OdEqual(m_dY3, m_dOldY3) ||
    !OdEqual(m_dZ1, m_dOldZ1) || !OdEqual(m_dZ2, m_dOldZ2) || !OdEqual(m_dZ3, m_dOldZ3) ||
    !OdEqual(m_dW, m_dOldW)
    )
  {
    m_bDataModified = true;
  }

  CDialog::OnOK();
}

//=================================================================================

BEGIN_MESSAGE_MAP(CCDAStdBtnSetValueDlg, CDialog)
  ON_WM_SIZE()
  ON_BN_CLICKED(IDOK, OnOk)
END_MESSAGE_MAP()

//=================================================================================
// CCDAStdArraySetValueDlg dialog

IMPLEMENT_DYNAMIC(CCDAStdArraySetValueDlg, CDialog)

CCDAStdArraySetValueDlg::CCDAStdArraySetValueDlg(CWnd* pParent, CCDAStdArraySetValueDlgType uType, bool bEnable, const OdString& strPropName)
  : CDialog(CCDAStdArraySetValueDlg::IDD, pParent)
{  
  m_uType = uType;
  m_bEnable = bEnable;
  m_strPropName = strPropName;

  m_dXValue = 0;
  m_dYValue = 0;
  m_dZValue = 0;
  m_strValue = L"";
  SYSTEMTIME curTime;
  GetSystemTime(&curTime);
  m_timeValue = CTime(curTime);
  m_iBoolRadio = 0;
  m_iSelectedItem = -1;
  m_iCurCount = 0;
  m_bSkipSelChange = false;
}

//=================================================================================

CCDAStdArraySetValueDlg::~CCDAStdArraySetValueDlg()
{}

//=================================================================================

void CCDAStdArraySetValueDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Text(pDX, IDC_VALUEEDIT, m_strValue);
  DDX_Text(pDX, IDC_XEDIT, m_dXValue);
  DDX_Text(pDX, IDC_YEDIT, m_dYValue);
  DDX_Text(pDX, IDC_ZEDIT, m_dZValue);
  DDX_Radio(pDX, IDC_TRUERADIO, m_iBoolRadio);
  DDX_DateTimeCtrl(pDX, IDC_VALUEEDIT + 2, m_timeValue);
}

//=================================================================================

BOOL CCDAStdArraySetValueDlg::OnInitDialog()
{
  CRect dataRect;
  dataRect.left = 16;
  dataRect.right = 268;
  dataRect.top = 308;
  dataRect.bottom = 334;

  m_dateTimeCtrl.Create(WS_VISIBLE | WS_CHILD | WS_BORDER, dataRect, this, IDC_VALUEEDIT + 2);
  m_dateTimeCtrl.SetFormat(L"dd.MM.yyyy HH:MM:ss");

  BOOL bRet = CDialog::OnInitDialog();

  m_arrValues.clear();

  bool bXYZEditVisible = false;
  bool bValueEditVisible = false;
  bool bRadioVisible = false;
  bool bDateTimeVisible = false;

  switch( m_uType )
  {
    case CCDAStdArraySetValueDlgType::kBool:
    {
      for( OdUInt32 i = 0; i < m_boolArr.size(); i++ )
      {
        m_arrValues.push_back(m_boolArr[i] ? L"True" : L"False");
      }

      bRadioVisible = true;

      if(m_arrValues.isEmpty() ) 
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kInt8:
    {
      for (OdUInt32 i = 0; i < m_int8Arr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%d", m_int8Arr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kUInt8:
    {
      for (OdUInt32 i = 0; i < m_uInt8Arr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%u", m_uInt8Arr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kInt16:
    {
      for (OdUInt32 i = 0; i < m_int16Arr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%d", m_int16Arr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kUInt16:
    {
      for (OdUInt32 i = 0; i < m_uInt16Arr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%u", m_uInt16Arr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kInt32:
    {
      for (OdUInt32 i = 0; i < m_int32Arr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%d", m_int32Arr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kUInt32:
    {
      for (OdUInt32 i = 0; i < m_uInt32Arr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%u", m_uInt32Arr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kInt64:
    {
      for (OdUInt32 i = 0; i < m_int64Arr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%lld", m_int64Arr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kUInt64:
    {
      for (OdUInt32 i = 0; i < m_uInt64Arr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%llu", m_uInt64Arr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kDouble:
    {
      for (OdUInt32 i = 0; i < m_doubleArr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%d", m_doubleArr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kFloat:
    {
      for (OdUInt32 i = 0; i < m_floatArr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%d", m_floatArr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kString:
    {
      for (OdUInt32 i = 0; i < m_stringArr.size(); i++)
      {
        OdString strValue = m_stringArr[i];
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kAnsiString:
    {
      for (OdUInt32 i = 0; i < m_ansiStringArr.size(); i++)
      {
        OdString strValue = OdString(m_ansiStringArr[i]);
        m_arrValues.push_back(strValue);
      }

      bValueEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kPoint3d:
    {
      for (OdUInt32 i = 0; i < m_point3dArr.size(); i++)
      {
        OdString strValue;
        strValue.format(L"%d, %d, %d", m_point3dArr[i].x, m_point3dArr[i].y, m_point3dArr[i].z);
        m_arrValues.push_back(strValue);
      }

      bXYZEditVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;

    case CCDAStdArraySetValueDlgType::kDateTime:
    {
      for (OdUInt32 i = 0; i < m_dateTimeArr.size(); i++)
      {
        OdString strValue;
        m_dateTimeArr[i].strftime(L"%d.%m.%Y %H:%M:%S", strValue);
        m_arrValues.push_back(strValue);
      }

      bDateTimeVisible = true;

      if (m_arrValues.isEmpty())
        m_iSelectedItem = -1;
      else
        m_iSelectedItem = 0;
    } break;
  }

  CWnd* pEditX = (CWnd*)GetDlgItem(IDC_XEDIT);
  CWnd* pEditY = (CWnd*)GetDlgItem(IDC_YEDIT);
  CWnd* pEditZ = (CWnd*)GetDlgItem(IDC_ZEDIT);
  CWnd* pTrueRadio  = (CWnd*)GetDlgItem(IDC_TRUERADIO);
  CWnd* pFalseRadio = (CWnd*)GetDlgItem(IDC_FALSERADIO);
  CWnd* pBoolStatic = (CWnd*)GetDlgItem(IDC_BOOL_STATIC);
  CWnd* pEditVal = (CWnd*)GetDlgItem(IDC_VALUEEDIT);
  CWnd* pAddBtn = (CWnd*)GetDlgItem(IDC_ADD);
  CWnd* pModifyBtn = (CWnd*)GetDlgItem(IDC_MODIFY);
  CWnd* pDelBtn = (CWnd*)GetDlgItem(IDC_DELETE);

  pEditX->ShowWindow(bXYZEditVisible ? SW_SHOW : SW_HIDE);
  pEditY->ShowWindow(bXYZEditVisible ? SW_SHOW : SW_HIDE);
  pEditZ->ShowWindow(bXYZEditVisible ? SW_SHOW : SW_HIDE);
  pTrueRadio->ShowWindow(bRadioVisible ? SW_SHOW : SW_HIDE);
  pFalseRadio->ShowWindow(bRadioVisible ? SW_SHOW : SW_HIDE);
  pBoolStatic->ShowWindow(bRadioVisible ? SW_SHOW : SW_HIDE);
  pEditVal->ShowWindow(bValueEditVisible ? SW_SHOW : SW_HIDE);
  m_dateTimeCtrl.ShowWindow(bDateTimeVisible ? SW_SHOW : SW_HIDE);

  pAddBtn->EnableWindow(m_bEnable);
  pModifyBtn->EnableWindow(m_bEnable);
  pDelBtn->EnableWindow(m_bEnable);

  CListCtrl* pList = (CListCtrl*)(GetDlgItem(IDC_ARRAYVALUES_LIST));

  pList->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
  pList->InsertColumn(0, L"N", LVCFMT_CENTER, (OdInt32)(25));
  pList->InsertColumn(1, L"Value", LVCFMT_LEFT, (OdInt32)(235));

  updateValuesList();

  SetWindowTextW(m_strPropName);

  UpdateData(false);

  m_bDataModified = false;

  return bRet;
}

//=================================================================================

void CCDAStdArraySetValueDlg::setSelectedValue(int iSelIndex)
{
  m_bSkipSelChange = true;

  CListCtrl* pList = (CListCtrl*)(GetDlgItem(IDC_ARRAYVALUES_LIST));
  pList->SetFocus();
  pList->SetSelectionMark(iSelIndex);
  pList->SetItemState(iSelIndex, LVIS_SELECTED, LVIS_SELECTED);

  CWnd* pAddBtn = (CWnd*)GetDlgItem(IDC_ADD);
  CWnd* pModifyBtn = (CWnd*)GetDlgItem(IDC_MODIFY);
  CWnd* pDelBtn = (CWnd*)GetDlgItem(IDC_DELETE);

  if( iSelIndex >= 0 )
  {
    switch (m_uType)
    {
      case CCDAStdArraySetValueDlg::kBool:
      {
        if ((int)m_boolArr.size() > iSelIndex)
          m_iBoolRadio = !m_boolArr[iSelIndex];
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kInt8:
      {
        if ((int)m_int8Arr.size() > iSelIndex)
          m_strValue.Format(L"%d", m_int8Arr[iSelIndex]);
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kUInt8:
      {
        if ((int)m_uInt8Arr.size() > iSelIndex)
          m_strValue.Format(L"%u", m_uInt8Arr[iSelIndex]);
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kInt16:
      {
        if ((int)m_int16Arr.size() > iSelIndex)
          m_strValue.Format(L"%d", m_int16Arr[iSelIndex]);
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kUInt16:
      {
        if ((int)m_uInt8Arr.size() > iSelIndex)
          m_strValue.Format(L"%u", m_uInt16Arr[iSelIndex]);
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kInt32:
      {
        if ((int)m_int32Arr.size() > iSelIndex)
          m_strValue.Format(L"%d", m_int32Arr[iSelIndex]);
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kUInt32:
      {
        if ((int)m_uInt32Arr.size() > iSelIndex)
          m_strValue.Format(L"%u", m_uInt32Arr[iSelIndex]);
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kInt64:
      {
        if ((int)m_int64Arr.size() > iSelIndex)
          m_strValue.Format(L"%lld", m_int64Arr[iSelIndex]);
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kUInt64:
      {
        if ((int)m_uInt64Arr.size() > iSelIndex)
          m_strValue.Format(L"%llu", m_uInt64Arr[iSelIndex]);
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kDouble:
      {
        if ((int)m_doubleArr.size() > iSelIndex)
          m_strValue.Format(L"%f", m_doubleArr[iSelIndex]);
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kFloat:
      {
        if ((int)m_floatArr.size() > iSelIndex)
          m_strValue.Format(L"%f", m_floatArr[iSelIndex]);
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kString:
      {
        if ((int)m_stringArr.size() > iSelIndex)
          m_strValue = CString(m_stringArr[iSelIndex].c_str());
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kAnsiString:
      {
        if ((int)m_ansiStringArr.size() > iSelIndex)
          m_strValue = CString(OdString(m_ansiStringArr[iSelIndex]).c_str());
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kPoint3d:
      {
        if( (int)m_point3dArr.size() > iSelIndex )
        {
          m_dXValue = m_point3dArr[iSelIndex].x;
          m_dYValue = m_point3dArr[iSelIndex].y;
          m_dZValue = m_point3dArr[iSelIndex].z;
        }
        else
          iSelIndex = -1;
      } break;

      case CCDAStdArraySetValueDlg::kDateTime:
      {
        if ((int)m_dateTimeArr.size() > iSelIndex)
        {
          SYSTEMTIME dateTime;
          dateTime.wYear = m_dateTimeArr[iSelIndex].year();
          dateTime.wMonth = m_dateTimeArr[iSelIndex].month();
          dateTime.wDay = m_dateTimeArr[iSelIndex].day();
          dateTime.wHour = m_dateTimeArr[iSelIndex].hour();
          dateTime.wMinute = m_dateTimeArr[iSelIndex].minute();
          dateTime.wSecond = m_dateTimeArr[iSelIndex].second();
          dateTime.wMilliseconds = m_dateTimeArr[iSelIndex].millisecond();
          CTime setTime(dateTime);
          m_timeValue = setTime;
        }
        else
          iSelIndex = -1;
      } break;
    }
  }

  if (iSelIndex < 0)
  {
    m_dXValue = 0;
    m_dYValue = 0;
    m_dZValue = 0;
    m_strValue = L"";
    SYSTEMTIME curTime;
    GetSystemTime(&curTime);
    m_timeValue = CTime(curTime);
    m_iBoolRadio = 0;

    pAddBtn->EnableWindow(m_bEnable);
    pModifyBtn->EnableWindow(false);
    pDelBtn->EnableWindow(false);
  }
  else
  {
    pAddBtn->EnableWindow(m_bEnable);
    pModifyBtn->EnableWindow(m_bEnable);
    pDelBtn->EnableWindow(m_bEnable);
  }

  m_iSelectedItem = iSelIndex;

  UpdateData(false);

  m_bSkipSelChange = false;
}

//=================================================================================

void CCDAStdArraySetValueDlg::updateValuesList()
{
  CListCtrl* pList = (CListCtrl*)(GetDlgItem(IDC_ARRAYVALUES_LIST));
  pList->DeleteAllItems();

  m_iCurCount = 0;

  for( OdUInt32 i = 0; i < m_arrValues.size(); i++ )
  {
    OdString strIndex;
    strIndex.format(L"%d", i);
    pList->InsertItem(LVIF_TEXT | LVIF_PARAM, m_iCurCount++, strIndex, 0, 0, 0, 0);
    pList->SetItem(m_iCurCount - 1, 1, LVIF_TEXT, m_arrValues[i], 0, 0, 0, 1);
  }

  if (m_iSelectedItem < 0 && !m_arrValues.isEmpty())
    setSelectedValue(0);
  else if (m_iSelectedItem < (int)m_arrValues.size())
    setSelectedValue(m_iSelectedItem);
  else if (!m_arrValues.isEmpty())
    setSelectedValue(m_arrValues.size() - 1);
  else
    setSelectedValue(-1);
}

//=================================================================================

void CCDAStdArraySetValueDlg::OnOk()
{
  UpdateData(true);
  CDialog::OnOK();
}

//=================================================================================

bool getStrValue(const CString& strValue, double& dRet)
{
  bool bRet = false;

  SET_LOCALE(LC_NUMERIC, "C");

  dRet = 0.0;

  OdString strODAValue = strValue;

  if( !strODAValue.isEmpty())
  {
    OdChar* pNextDouble;
    dRet = wcstod(strODAValue, &pNextDouble);
    bRet = *pNextDouble == 0;
  }

  RESET_LOCALE();

  return bRet;
}

//=================================================================================

void CCDAStdArraySetValueDlg::OnAddValue()
{
  UpdateData(true);

  bool bDataAdded = false;

  switch (m_uType)
  {
    case CCDAStdArraySetValueDlg::kBool:
    {
      if( m_iBoolRadio == 0 || m_iBoolRadio == 1 )
      {
        m_boolArr.push_back(m_iBoolRadio == 0);
        m_arrValues.push_back( (m_iBoolRadio == 0) ? L"True" : L"False");
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt8:
    {
      double dValue = 0;

      if( getStrValue(m_strValue, dValue ) )
      {
        OdInt8 value = (OdInt8)(dValue);
        m_int8Arr.push_back(value);
        OdString strNewValue;
        strNewValue.format(L"%d", value);
        m_arrValues.push_back(strNewValue);
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt8:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue))
      {
        OdUInt8 value = (OdUInt8)(dValue);
        m_uInt8Arr.push_back(value);
        OdString strNewValue;
        strNewValue.format(L"%u", value);
        m_arrValues.push_back(strNewValue);
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt16:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue))
      {
        OdInt16 value = (OdInt16)(dValue);
        m_int16Arr.push_back(value);
        OdString strNewValue;
        strNewValue.format(L"%d", value);
        m_arrValues.push_back(strNewValue);
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt16:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue))
      {
        OdUInt16 value = (OdUInt16)(dValue);
        m_uInt16Arr.push_back(value);
        OdString strNewValue;
        strNewValue.format(L"%u", value);
        m_arrValues.push_back(strNewValue);
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt32:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue))
      {
        OdInt32 value = (OdInt32)(dValue);
        m_int32Arr.push_back(value);
        OdString strNewValue;
        strNewValue.format(L"%d", value);
        m_arrValues.push_back(strNewValue);
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt32:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue))
      {
        OdUInt32 value = (OdUInt32)(dValue);
        m_uInt32Arr.push_back(value);
        OdString strNewValue;
        strNewValue.format(L"%u", value);
        m_arrValues.push_back(strNewValue);
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt64:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue))
      {
        OdInt64 value = (OdInt64)(dValue);
        m_int64Arr.push_back(value);
        OdString strNewValue;
        strNewValue.format(L"%lld", value);
        m_arrValues.push_back(strNewValue);
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt64:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue))
      {
        OdUInt64 value = (OdUInt64)(dValue);
        m_uInt64Arr.push_back(value);
        OdString strNewValue;
        strNewValue.format(L"%llu", value);
        m_arrValues.push_back(strNewValue);
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kDouble:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue))
      {
        m_doubleArr.push_back(dValue);
        OdString strNewValue;
        strNewValue.format(L"%f", dValue);
        m_arrValues.push_back(strNewValue);
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kFloat:
    {
      double dValue = 0;

      if( getStrValue(m_strValue, dValue) )
      {
        m_floatArr.push_back((float)dValue);
        OdString strNewValue;
        strNewValue.format(L"%f", (float)dValue);
        m_arrValues.push_back(strNewValue);
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kString:
    {
      OdString strOdaValue = m_strValue;
      m_stringArr.push_back(strOdaValue);
      m_arrValues.push_back(strOdaValue);
      bDataAdded = true;
    } break;

    case CCDAStdArraySetValueDlg::kAnsiString:
    {
      OdString strOdaValue = m_strValue;
      m_ansiStringArr.push_back(OdAnsiString(strOdaValue));
      m_arrValues.push_back(strOdaValue);
      bDataAdded = true;
    } break;

    case CCDAStdArraySetValueDlg::kPoint3d:
    {
      OdGePoint3d ptNew(m_dXValue, m_dYValue, m_dZValue);
      m_point3dArr.push_back(ptNew);
      OdString strValue;
      strValue.format(L"%d, %d, %d", ptNew.x, ptNew.y, ptNew.z);
      m_arrValues.push_back(strValue);
      bDataAdded = true;
    } break;

    case CCDAStdArraySetValueDlg::kDateTime:
    {
      SYSTEMTIME dateTime;

      if( m_timeValue.GetAsSystemTime(dateTime) )
      {
        OdTimeStamp odTime;
        odTime.setDate(dateTime.wMonth, dateTime.wDay, dateTime.wYear);
        odTime.setTime(dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds);
        m_dateTimeArr.push_back(odTime);
        OdString strValue;
        odTime.strftime(L"%d.%m.%Y %H:%M:%S", strValue);
        m_arrValues.push_back(strValue);
        bDataAdded = true;
      }
    } break;
  }

  if( bDataAdded )
  {
    OdString strIndex;
    strIndex.format(L"%d", m_iCurCount);

    CListCtrl* pList = (CListCtrl*)(GetDlgItem(IDC_ARRAYVALUES_LIST));
    pList->InsertItem(LVIF_TEXT | LVIF_PARAM, m_iCurCount++, strIndex, 0, 0, 0, 0);
    pList->SetItem(pList->GetItemCount()-1, 1, LVIF_TEXT, m_arrValues.last(), 0, 0, 0, 1);
    setSelectedValue(pList->GetItemCount() - 1);
    m_bDataModified = true;
  }
}

//=================================================================================

void CCDAStdArraySetValueDlg::OnModifyValue()
{
  UpdateData(true);

  bool bDataAdded = false;

  switch (m_uType)
  {
    case CCDAStdArraySetValueDlg::kBool:
    {
      if (m_iBoolRadio == 0 || m_iBoolRadio == 1)
      {
        if( m_boolArr.size() > (OdUInt32)m_iSelectedItem )
        {
          m_boolArr[m_iSelectedItem] = m_iBoolRadio == 0;
          m_arrValues[m_iSelectedItem] = (m_iBoolRadio == 0) ? L"True" : L"False";
          bDataAdded = true;
        }
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt8:
    {
      double dValue = 0;

      if( getStrValue(m_strValue, dValue) && (m_int8Arr.size() > (OdUInt32)m_iSelectedItem) )
      {
        OdInt8 value = (OdInt8)(dValue);
        m_int8Arr[m_iSelectedItem] = value;
        OdString strNewValue;
        strNewValue.format(L"%d", value);
        m_arrValues[m_iSelectedItem] = strNewValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt8:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue) && (m_uInt8Arr.size() > (OdUInt32)m_iSelectedItem))
      {
        OdUInt8 value = (OdUInt8)(dValue);
        m_uInt8Arr[m_iSelectedItem] = value;
        OdString strNewValue;
        strNewValue.format(L"%u", value);
        m_arrValues[m_iSelectedItem] = strNewValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt16:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue) && (m_int16Arr.size() > (OdUInt32)m_iSelectedItem))
      {
        OdInt16 value = (OdInt16)(dValue);
        m_int16Arr[m_iSelectedItem] = value;
        OdString strNewValue;
        strNewValue.format(L"%d", value);
        m_arrValues[m_iSelectedItem] = strNewValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt16:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue) && (m_uInt16Arr.size() > (OdUInt32)m_iSelectedItem))
      {
        OdUInt16 value = (OdUInt16)(dValue);
        m_uInt16Arr[m_iSelectedItem] = value;
        OdString strNewValue;
        strNewValue.format(L"%u", value);
        m_arrValues[m_iSelectedItem] = strNewValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt32:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue) && (m_int32Arr.size() > (OdUInt32)m_iSelectedItem))
      {
        OdInt32 value = (OdInt32)(dValue);
        m_int32Arr[m_iSelectedItem] = value;
        OdString strNewValue;
        strNewValue.format(L"%d", value);
        m_arrValues[m_iSelectedItem] = strNewValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt32:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue) && (m_uInt32Arr.size() > (OdUInt32)m_iSelectedItem))
      {
        OdUInt32 value = (OdUInt32)(dValue);
        m_uInt32Arr[m_iSelectedItem] = value;
        OdString strNewValue;
        strNewValue.format(L"%u", value);
        m_arrValues[m_iSelectedItem] = strNewValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt64:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue) && (m_int64Arr.size() > (OdUInt32)m_iSelectedItem))
      {
        OdInt64 value = (OdInt64)(dValue);
        m_int64Arr[m_iSelectedItem] = value;
        OdString strNewValue;
        strNewValue.format(L"%lld", value);
        m_arrValues[m_iSelectedItem] = strNewValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt64:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue) && (m_uInt64Arr.size() > (OdUInt32)m_iSelectedItem))
      {
        OdUInt64 value = (OdUInt64)(dValue);
        m_uInt64Arr[m_iSelectedItem] = value;
        OdString strNewValue;
        strNewValue.format(L"%llu", value);
        m_arrValues[m_iSelectedItem] = strNewValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kDouble:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue) && (m_doubleArr.size() > (OdUInt32)m_iSelectedItem))
      {
        m_doubleArr[m_iSelectedItem] = dValue;
        OdString strNewValue;
        strNewValue.format(L"%f", dValue);
        m_arrValues[m_iSelectedItem] = strNewValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kFloat:
    {
      double dValue = 0;

      if (getStrValue(m_strValue, dValue) && (m_floatArr.size() > (OdUInt32)m_iSelectedItem))
      {
        m_floatArr[m_iSelectedItem] = (float)dValue;
        OdString strNewValue;
        strNewValue.format(L"%f", dValue);
        m_arrValues[m_iSelectedItem] = strNewValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kString:
    {
      if (m_stringArr.size() > (OdUInt32)m_iSelectedItem)
      {
        OdString strOdaValue = m_strValue;
        m_stringArr[m_iSelectedItem] = strOdaValue;
        m_arrValues[m_iSelectedItem] = strOdaValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kAnsiString:
    {
      if (m_ansiStringArr.size() > (OdUInt32)m_iSelectedItem)
      {
        OdString strOdaValue = m_strValue;
        m_ansiStringArr[m_iSelectedItem] = OdAnsiString(strOdaValue);
        m_arrValues[m_iSelectedItem] = strOdaValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kPoint3d:
    {
      if (m_point3dArr.size() > (OdUInt32)m_iSelectedItem)
      {
        OdGePoint3d ptNew(m_dXValue, m_dYValue, m_dZValue);
        m_point3dArr[m_iSelectedItem] = ptNew;
        OdString strValue;
        strValue.format(L"%d, %d, %d", ptNew.x, ptNew.y, ptNew.z);
        m_arrValues[m_iSelectedItem] = strValue;
        bDataAdded = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kDateTime:
    {
      if (m_dateTimeArr.size() > (OdUInt32)m_iSelectedItem)
      {
        SYSTEMTIME dateTime;

        if (m_timeValue.GetAsSystemTime(dateTime))
        {
          OdTimeStamp odTime;
          odTime.setDate(dateTime.wMonth, dateTime.wDay, dateTime.wYear);
          odTime.setTime(dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds);
          m_dateTimeArr[m_iSelectedItem] = odTime;
          OdString strValue;
          odTime.strftime(L"%d.%m.%Y %H:%M:%S", strValue);
          m_arrValues[m_iSelectedItem] = strValue;
          bDataAdded = true;
        }
      }
    } break;
  }

  if (bDataAdded)
  {
    CListCtrl* pList = (CListCtrl*)(GetDlgItem(IDC_ARRAYVALUES_LIST));
    pList->SetItem(m_iSelectedItem, 1, LVIF_TEXT, m_arrValues[m_iSelectedItem], 0, 0, 0, 1);
    setSelectedValue(m_iSelectedItem);
    m_bDataModified = true;
  }
}

//=================================================================================

void CCDAStdArraySetValueDlg::OnDeleteValue()
{
  bool bDataRemoved = false;

  switch (m_uType)
  {
    case CCDAStdArraySetValueDlg::kBool:
    {
      if (m_boolArr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_boolArr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt8:
    {
      if( m_int8Arr.size() > (OdUInt32)m_iSelectedItem )
      {
        m_int8Arr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt8:
    {
      if (m_uInt8Arr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_uInt8Arr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt16:
    {
      if (m_int16Arr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_int16Arr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt16:
    {
      if (m_uInt16Arr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_uInt16Arr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt32:
    {
      if (m_int32Arr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_int32Arr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt32:
    {
      if (m_uInt32Arr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_uInt32Arr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kInt64:
    {
      if (m_int64Arr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_int64Arr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kUInt64:
    {
      if (m_uInt64Arr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_uInt64Arr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kDouble:
    {
      if (m_doubleArr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_doubleArr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kFloat:
    {
      if (m_floatArr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_floatArr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kString:
    {
      if (m_stringArr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_stringArr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kAnsiString:
    {
      if (m_ansiStringArr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_ansiStringArr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kPoint3d:
    {
      if (m_point3dArr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_point3dArr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;

    case CCDAStdArraySetValueDlg::kDateTime:
    {
      if (m_dateTimeArr.size() > (OdUInt32)m_iSelectedItem)
      {
        m_dateTimeArr.removeAt(m_iSelectedItem);
        m_arrValues.removeAt(m_iSelectedItem);
        bDataRemoved = true;
      }
    } break;
  }

  if (bDataRemoved)
  {
    CListCtrl* pList = (CListCtrl*)(GetDlgItem(IDC_ARRAYVALUES_LIST));
    pList->DeleteItem(m_iSelectedItem);

    if (m_iSelectedItem < 0 && !m_arrValues.isEmpty())
      setSelectedValue(0);
    else if (m_iSelectedItem < (int)m_arrValues.size())
      setSelectedValue(m_iSelectedItem);
    else if (!m_arrValues.isEmpty())
      setSelectedValue(m_arrValues.size() - 1);
    else
      setSelectedValue(-1);

    m_bDataModified = true;
  }
}

//=================================================================================

void CCDAStdArraySetValueDlg::OnLvnItemchangedValueList(NMHDR *pNMHDR, LRESULT *pResult)
{
  if( !m_bSkipSelChange )
  {
    CListCtrl* pList = (CListCtrl*)(GetDlgItem(IDC_ARRAYVALUES_LIST));
    int iItemSelected = pList->GetSelectionMark();
    setSelectedValue(iItemSelected);
  }
}

//=================================================================================

BEGIN_MESSAGE_MAP(CCDAStdArraySetValueDlg, CDialog)
  ON_NOTIFY(LVN_ITEMCHANGING, IDC_ARRAYVALUES_LIST, CCDAStdArraySetValueDlg::OnLvnItemchangedValueList)
  ON_BN_CLICKED(IDOK, OnOk)
  ON_BN_CLICKED(IDC_ADD, OnAddValue)
  ON_BN_CLICKED(IDC_MODIFY, OnModifyValue)
  ON_BN_CLICKED(IDC_DELETE, OnDeleteValue)
END_MESSAGE_MAP()

//=================================================================================
// CCDASetTransperencyDlg dialog

IMPLEMENT_DYNAMIC(CCDASetTransperencyDlg, CDialog)

CCDASetTransperencyDlg::CCDASetTransperencyDlg(CWnd* pParent, OdCmTransparency& curTrans, bool bEnable, const OdString& strPropName)
  : CDialog(CCDASetTransperencyDlg::IDD, pParent)
{
  m_bEnable     = bEnable;
  m_strPropName = strPropName;
   m_iValue      = (int)((1.0 - curTrans.alphaPercent())*100.0);
  m_bDataModified = false;
}

//=================================================================================

CCDASetTransperencyDlg::~CCDASetTransperencyDlg()
{}

//=================================================================================

BOOL CCDASetTransperencyDlg::OnInitDialog()
{
  BOOL bRet = CDialog::OnInitDialog();

  CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_STRANS);
  pSlider->SetRange(0, 100);
  pSlider->EnableWindow(m_bEnable ? TRUE : FALSE);
  CWnd*        pStatic = GetDlgItem(IDC_TRANS_VAL);
  OdString strValue;
  strValue.format(L"%d", m_iValue);
  strValue += L"%:";
  pStatic->SetWindowText(strValue);

  UpdateData(false);

  return bRet;
}

//=================================================================================

void CCDASetTransperencyDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

  UpdateData(true);

  CWnd*        pStatic = GetDlgItem(IDC_TRANS_VAL);
  OdString strValue;
  strValue.format(L"%d", m_iValue);
  strValue += L"%:";
  pStatic->SetWindowText(strValue);
  m_bDataModified = true;
}

//=================================================================================

void CCDASetTransperencyDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Slider(pDX, IDC_STRANS, m_iValue);
}

//=================================================================================

BEGIN_MESSAGE_MAP(CCDASetTransperencyDlg, CDialog)
  ON_WM_HSCROLL()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDAOdColorCombo

IMPLEMENT_DYNCREATE(CCDAOdColorCombo, CComboBox)

/////////////////////////////////////////////////////////////////////////////

CCDAOdColorCombo::CCDAOdColorCombo()
{
  m_pDb = NULL;
  m_pObject = NULL;
  m_pProperty = NULL;
  m_iArrayIndex = -1;
  m_iSubPropertyIndex = -1;
  m_bReadOnly = true;
  m_uRscIndex = 0;
}

/////////////////////////////////////////////////////////////////////////////

CCDAOdColorCombo::~CCDAOdColorCombo()
{}

/////////////////////////////////////////////////////////////////////////////

CWnd* CCDAOdColorCombo::createCDAColorCombo(OdRxObject* pDb,
  OdRxObject* pObject,
  OdRxPropertyBase* pProperty,
  const CRect& btnRect,
  CWnd* pParentWnd,
  OdUInt32 uRscIndex,
  OdInt32 iSubPropertyIndex,
  OdInt32 iArrayIndex)
{
  CCDAOdColorCombo* pRet = new CCDAOdColorCombo();

  if (pRet->initData(pDb, pObject, pProperty, btnRect, pParentWnd, uRscIndex, iSubPropertyIndex, iArrayIndex))
    return pRet;

  delete pRet;

  return NULL;
}

/////////////////////////////////////////////////////////////////////////////

OdUInt32 CCDAOdColorCombo::getRscIndex() const
{
  return m_uRscIndex;
}

/////////////////////////////////////////////////////////////////////////////

BOOL CCDAOdColorCombo::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pRes)
{
  if( message == WM_COMMAND )
  {
    OdUInt32 uCommand = wParam;
    uCommand = uCommand >> 16;
    uCommand = uCommand & 0xFFFF;

    if (uCommand == CBN_SELCHANGE)
    {
      OdInt32 iCurSel = GetCurSel();

      bool bSet = true;
      OdCmEntityColor newColor;

      OdRxPropertyBase* pBaseProperty = getActualProperty(m_pObject, m_pProperty, m_iSubPropertyIndex, m_iArrayIndex);

      if (pBaseProperty)
      {
        OdRxAttributeCollection& attrs = pBaseProperty->attributes();
        OdRxAttribute* pAttr = attrs.get(OdRxRefersToAttribute::desc());

        if ((iCurSel >= 0) && iCurSel != m_iItemIndex)
        {
          if (iCurSel == 0)
            newColor.setColorMethod(OdCmEntityColor::kByLayer);
          else if (iCurSel == 1)
            newColor.setColorMethod(OdCmEntityColor::kByBlock);
          else if (iCurSel < 258)
          {
            newColor.setColorIndex(iCurSel - 2);
            if (pAttr)
              newColor.setColorMethod(OdCmEntityColor::kByDgnIndex);
            else
              newColor.setColorMethod(OdCmEntityColor::kByACI);
          }
          else
          {
            CColorDialog colorDlg;

            if (colorDlg.DoModal())
            {
              ODCOLORREF curColor = colorDlg.GetColor();
              newColor.setRGB(ODGETRED(curColor), ODGETGREEN(curColor), ODGETBLUE(curColor));
            }
            else
              bSet = false;
          }

          if (bSet)
            m_iItemIndex = iCurSel;
        }
        else
          bSet = false;
      }
      else
        bSet = false;

      if (bSet)
      {
        OdRxValue newValue(newColor);

        if (!setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newValue))
        {
          SetCurSel(m_iItemIndex);
        }
        else
        {
          if( newColor.isByColor() )
            m_rgbColor = ODRGB(newColor.red(), newColor.green(), newColor.blue());
        }
      }
      else
      {
        SetCurSel(m_iItemIndex);
      }
    }
  }
  return CComboBox::OnChildNotify(message, wParam, lParam, pRes);
}

/////////////////////////////////////////////////////////////////////////////

OdArray<ODCOLORREF> CCDAOdColorCombo::getOdPalette(OdRxAttribute* pAttr, OdRxObject* pDb)
{
  OdArray<ODCOLORREF> retVal;

  if( pAttr )
  {
    OdRxRefersToAttribute* pRefTo = (OdRxRefersToAttribute*)pAttr;

    OdArray<OdString> arrPathToPalette;

    OdString strPath = pRefTo->path();
    strPath.replace(L'\\', L'/');

    while (!strPath.isEmpty())
    {
      if (strPath.find(L'/') != -1)
      {
        OdString strItem = strPath.left(strPath.find(L'/'));
        strPath = strPath.right(strPath.getLength() - strItem.getLength() - 1);

        if (!strItem.isEmpty())
          arrPathToPalette.push_back(strItem);
      }
      else
      {
        arrPathToPalette.push_back(strPath);
        break;
      }
    }

    OdRxObjectPtr             pCollectionOwner;
    OdRxCollectionPropertyPtr pCollection = getCollectionProperty(arrPathToPalette, m_pDb, pCollectionOwner);

    if (!pCollection.isNull())
    {
      OdRxValueIteratorPtr pCollectionIter = pCollection->newValueIterator(pCollectionOwner);

      OdInt32 iCount = 0;

      for (; !pCollectionIter->done(); pCollectionIter->next())
      {
        OdRxValue curVal = pCollectionIter->current();

        OdCmEntityColor* pColor = rxvalue_cast<OdCmEntityColor>(&curVal);

        if(pColor && (pColor->colorMethod() == OdCmEntityColor::kByColor) )
        {
          retVal.push_back(ODRGB(pColor->red(), pColor->green(), pColor->blue()));
        }
      }
    }
  }

  if( retVal.size() > 256 )
    retVal.resize(256);

  if( retVal.size() < 256 )
  {
    const ODCOLORREF* pACADPalette = OdDgColorTable::defaultACadPalette();

    for (OdUInt32 i = retVal.size(); i < 256; i++)
      retVal.push_back(pACADPalette[i]);
  }

  return retVal;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDAOdColorCombo::initData(OdRxObject* pDb,
  OdRxObject* pObject,
  OdRxPropertyBase* pPropertyBase,
  const CRect& btnRect,
  CWnd* pParentWnd,
  OdUInt32 uRscIndex,
  OdInt32 iSubPropertyIndex,
  OdInt32 iArrayIndex)
{
  bool bRet = false;
  m_pDb = pDb;
  m_pObject = pObject;
  m_pProperty = pPropertyBase;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_iArrayIndex = iArrayIndex;

  m_strName = getPropertyName(m_pObject, pPropertyBase, iSubPropertyIndex, iArrayIndex);

  m_bReadOnly = pPropertyBase->isReadOnly(m_pObject);

  if (pPropertyBase->isKindOf(OdRxCollectionProperty::desc()) && !pPropertyBase->isKindOf(OdRxIndexedProperty::desc()))
    m_bReadOnly = true;

  m_uRscIndex = uRscIndex;

  OdRxValue propValue;

  if (!getCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, propValue))
    return false;

  OdRxPropertyBase* pBaseProperty = getActualProperty(m_pObject, m_pProperty, m_iSubPropertyIndex, m_iArrayIndex);

  OdCmEntityColor* pColor = rxvalue_cast<OdCmEntityColor>(&propValue);

  if( pColor && pBaseProperty )
  {
    OdRxAttributeCollection& attrs = pBaseProperty->attributes();
    OdRxAttribute* pAttr = attrs.get(OdRxRefersToAttribute::desc());

    m_palette = getOdPalette(pAttr, m_pDb);
    
    m_curColor = *pColor;
    bRet = true;

    if (m_curColor.isByLayer())
      m_iItemIndex = 0;
    else if (m_curColor.isByBlock())
      m_iItemIndex = 1;
    else if (m_curColor.isByColor())
      m_iItemIndex = 258;
    else
      m_iItemIndex = m_curColor.colorIndex() + 2;

    m_rgbColor = ODRGB(0, 0, 0);

    if (m_curColor.isByColor())
      m_rgbColor = ODRGB(m_curColor.red(), m_curColor.green(), m_curColor.blue());

    CRect cbRect = btnRect;

    cbRect.bottom += (btnRect.bottom - btnRect.top) * 8;

    Create(WS_VISIBLE | WS_BORDER | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_OWNERDRAWFIXED, cbRect, pParentWnd, uRscIndex);

    for (OdUInt32 i = 0; i < 259; i++)
    {
      OdString strColor;
      strColor.format(L"Color %d", i);
      AddString(strColor);
    }

    SetCurSel(m_iItemIndex);

    EnableWindow(!m_bReadOnly);
    SetFont(pParentWnd->GetFont());
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

void CCDAOdColorCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  CDC dc;
  dc.Attach(lpDrawItemStruct->hDC);

  CRect btnRect = lpDrawItemStruct->rcItem;
  CRect textRect = btnRect;
  textRect.InflateRect(0, -3, 0, 0);

  if (lpDrawItemStruct->itemID == 0)
  {
    dc.DrawText(L"by layer", &textRect, DT_CENTER);
  }
  else if (lpDrawItemStruct->itemID == 1)
  {
    dc.DrawText(L"by block", &textRect, DT_CENTER);
  }
  else if (lpDrawItemStruct->itemID < 258)
  {
    if (lpDrawItemStruct->itemID < 70)
      dc.SetTextColor(ODRGB(0, 0, 0));
    else
      dc.SetTextColor(ODRGB(255, 255, 255));

    dc.FillSolidRect(btnRect, m_palette.getAt(lpDrawItemStruct->itemID - 2));

    CString strIndex;
    strIndex.Format(L"%d", lpDrawItemStruct->itemID - 2);
    dc.DrawText(strIndex, &textRect, DT_CENTER);
  }
  else
  {
    dc.FillSolidRect(btnRect, m_rgbColor);

    CString strIndex;
    strIndex.Format(L"(%d, %d, %d)", ODGETRED(m_rgbColor), ODGETGREEN(m_rgbColor), ODGETBLUE(m_rgbColor));
    dc.DrawText(strIndex, &textRect, DT_CENTER);
  }

  POINT arrPts[5];
  arrPts[0].x = btnRect.left;
  arrPts[0].y = btnRect.top;
  arrPts[1].x = btnRect.right;
  arrPts[1].y = btnRect.top;
  arrPts[2].x = btnRect.right;
  arrPts[2].y = btnRect.bottom;
  arrPts[3].x = btnRect.left;
  arrPts[3].y = btnRect.bottom;
  arrPts[4].x = btnRect.left;
  arrPts[4].y = btnRect.top;

  dc.Polyline(arrPts,5);
  dc.Detach();
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCDAOdColorCombo, CComboBox)
  //{{AFX_MSG_MAP(CCDAOdColorCombo)
  ON_WM_DRAWITEM()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDACollectionButton

IMPLEMENT_DYNCREATE(CCDACollectionButton, CButton)

/////////////////////////////////////////////////////////////////////////////

CCDACollectionButton::CCDACollectionButton()
{
  m_pDb = NULL;
  m_pObject = NULL;
  m_pProperty = NULL;
  m_iArrayIndex = -1;
  m_iSubPropertyIndex = -1;
  m_bReadOnly = true;
  m_uRscIndex = 0;
  m_uCtrlType = CCDACollectionButton::kCollection;
  m_strTypeName = OdString::kEmpty;
  m_strName = OdString::kEmpty;
}

/////////////////////////////////////////////////////////////////////////////

CCDACollectionButton::~CCDACollectionButton()
{}

/////////////////////////////////////////////////////////////////////////////

CWnd* CCDACollectionButton::createCDACollectionButton(OdRxObject* pDb,
                                                        OdRxObject* pObject,
                                                          OdRxPropertyBase* pProperty,
                                                            CCDACollectionButtonTypes uCtrlType,
                                                              OdRxValue& typeValue,
                                                                const CRect& btnRect,
                                                                  CWnd* pParentWnd,
                                                                    OdUInt32 uRscIndex,
                                                                      OdInt32 iSubPropertyIndex,
                                                                        OdInt32 iArrayIndex,
                                                                          bool bEnable)
{
  CCDACollectionButton* pRet = new CCDACollectionButton();

  if (pRet->initData(pDb, pObject, pProperty, uCtrlType, typeValue, OdString::kEmpty, btnRect, pParentWnd, uRscIndex, iSubPropertyIndex, iArrayIndex, bEnable))
    return pRet;

  delete pRet;

  return NULL;
}

/////////////////////////////////////////////////////////////////////////////

CWnd* CCDACollectionButton::createCDACollectionButton(OdRxObject* pDb,
                                                        OdRxObject* pObject,
                                                          OdRxPropertyBase* pProperty,
                                                            CCDACollectionButtonTypes uCtrlType,
                                                              const OdString& strValue,
                                                                const CRect& btnRect,
                                                                  CWnd* pParentWnd,
                                                                    OdUInt32 uRscIndex,
                                                                      OdInt32 iSubPropertyIndex,
                                                                        OdInt32 iArrayIndex,
                                                                          bool bEnable)
{
  CCDACollectionButton* pRet = new CCDACollectionButton();

  OdRxValue emptyValue;

  if (pRet->initData(pDb, pObject, pProperty, uCtrlType, emptyValue, strValue, btnRect, pParentWnd, uRscIndex, iSubPropertyIndex, iArrayIndex, bEnable))
    return pRet;

  delete pRet;

  return NULL;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDACollectionButton::onButtonClick()
{
  bool bRet = false;

  if( m_uCtrlType == CCDACollectionButton::kCollection )
  {
    OdString strPropName = m_pProperty->name();
    CCDAPropertiesDlg propDlg(NULL, m_pDb, m_pObject, m_iSubPropertyIndex, strPropName);
    propDlg.DoModal();
  }
  else
  {
    OdString strPropName = m_pProperty->name();
    CCDAIndexedArrayDlg propDlg(NULL, m_pDb, m_pObject, m_typeValue, m_strTypeName.isEmpty() && !m_bReadOnly, m_iSubPropertyIndex, strPropName);
    propDlg.DoModal();
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

OdUInt32 CCDACollectionButton::getRscIndex() const
{
  return m_uRscIndex;
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CCDACollectionButton::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT pRet = CButton::WindowProc(message, wParam, lParam);

  if (message == WM_LBUTTONUP)
  {
    onButtonClick();
  }

  return pRet;
}

/////////////////////////////////////////////////////////////////////////////

bool CCDACollectionButton::initData(OdRxObject* pDb,
                                      OdRxObject* pObject,
                                        OdRxPropertyBase* pPropertyBase,
                                          CCDACollectionButtonTypes uValueType,
                                            OdRxValue& typeValue,
                                              const OdString& strTypeValue,
                                                const CRect& btnRect,
                                                  CWnd* pParentWnd,
                                                    OdUInt32 uRscIndex,
                                                      OdInt32 iSubPropertyIndex,
                                                        OdInt32 iArrayIndex, 
                                                          bool bEnable)
{
  bool bRet = true;
  m_pDb = pDb;
  m_pObject = pObject;
  m_pProperty = pPropertyBase;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_iArrayIndex = iArrayIndex;
  m_uCtrlType = uValueType;
  m_bReadOnly = pPropertyBase->isReadOnly(m_pObject) || !bEnable;
  m_typeValue = typeValue;
  m_strTypeName = strTypeValue;

  m_uRscIndex = uRscIndex;

  OdString strBtnName = strTypeValue;

  if (m_uCtrlType == CCDACollectionButtonTypes::kArray)
  {
    if (!strTypeValue.isEmpty())
    {
      m_bReadOnly = true;
    }
    else if( typeValue.type().isReference() )
    {
      OdRxObjectPtr pObject = typeValue.type().reference()->dereference(typeValue, IOdRxReferenceType::kForWrite);

      if (!pObject.isNull())
        strBtnName = pObject->isA()->name();
      else
        strBtnName = typeValue.type().name();

    }
    else if (typeValue.type() == OdRxValueType::Desc<OdRxObjectPtr>::value())
    {
      OdRxObjectPtr* pObject = rxvalue_cast<OdRxObjectPtr>(&typeValue);

      if (pObject && !pObject->isNull())
      {
        OdRxObjectPtr pObj = *pObject;

        strBtnName = pObj->isA()->name();
      }
      else
        strBtnName = typeValue.type().name();
    }
    else
      strBtnName = typeValue.type().name();

    if (!strBtnName.isEmpty())
      strBtnName = L"Array of " + strBtnName;
  }
  else
  {
    OdRxPropertyBase* pPropBase = getActualProperty(m_pObject, m_pProperty, m_iSubPropertyIndex, m_iArrayIndex);

    bool bHierarchyCollection = false;

    if( pPropBase )
    {
      OdRxAttributeCollection& collectionAttr = pPropBase->attributes();

      for( OdInt32 l = 0; l < collectionAttr.count(); l++ )
      {
        if( collectionAttr.getAt(l)->isKindOf(OdRxHierarchyLevelAttribute::desc()) )
        {
          bHierarchyCollection = true;
          break;
        }
      }
    }

    if( bHierarchyCollection )
      strBtnName = L"Collection of OdRxObjects";
    else if( !strBtnName.isEmpty() )
      strBtnName = L"Collection of " + strBtnName;
  }

  Create(strBtnName, WS_VISIBLE | WS_BORDER | WS_CHILD | BS_CENTER | BS_PUSHBOX, btnRect, pParentWnd, uRscIndex);

  if (bRet)
  {
    SetFont(pParentWnd->GetFont());
    SetWindowText(strBtnName);
  }

  return bRet;
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCDACollectionButton, CButton)
  //{{AFX_MSG_MAP(CCDACollectionButton)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CCDAIndexedArrayDlg dialog

IMPLEMENT_DYNAMIC(CCDAIndexedArrayDlg, CDialog)

CCDAIndexedArrayDlg::CCDAIndexedArrayDlg(CWnd* pParent, OdRxObject* pDb, OdRxObject* pObject, OdRxValue& defaultValue, bool bEnable, OdInt32 iSubPropertyIndex, const OdString& strPropName)
  : CDialog(CCDAIndexedArrayDlg::IDD, pParent)
{
  m_pDb = pDb;
  m_pObject = pObject;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_strPropName = strPropName;
  m_defaultValue = defaultValue;
  m_bEnable = bEnable;
}

//=================================================================================

CCDAIndexedArrayDlg::~CCDAIndexedArrayDlg()
{
}

//=================================================================================

void CCDAIndexedArrayDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_PROP_LIST, m_listCtrl);
}

//=================================================================================

BOOL CCDAIndexedArrayDlg::OnInitDialog()
{
  BOOL bRet = CDialog::OnInitDialog();

  CWnd* pListCtrl = (CWnd*)(GetDlgItem(IDC_PROP_LIST));
  RECT wndRect;
  pListCtrl->GetClientRect(&wndRect);

  m_listCtrl.initData(m_pDb, m_pObject, wndRect, m_iSubPropertyIndex, m_strPropName);

  OdRxMemberPtr pProp = OdRxMemberQueryEngine::theEngine()->find(m_pObject, L"Name");

  if (!pProp.isNull() && pProp->isKindOf(OdRxProperty::desc()))
  {
    OdRxPropertyPtr pPropName = pProp;
    OdRxValue nameValue;

    if (!pPropName.isNull() && pPropName->getValue(m_pObject, nameValue) == eOk)
      SetWindowText(nameValue.toString() + L" Properties");
  }

  CWnd* pAddBtn = GetDlgItem(IDC_ADD);
  CWnd* pDelBtn = GetDlgItem(IDC_DELETE);
  pAddBtn->EnableWindow(m_bEnable);
  pDelBtn->EnableWindow(m_listCtrl.GetSelectionMark() >= 0 && m_bEnable);

  return bRet;
}

//=================================================================================

void CCDAIndexedArrayDlg::OnOk()
{
  CDialog::OnOK();
}

//=================================================================================

void CCDAIndexedArrayDlg::OnAddBtn()
{
  if( m_bEnable && !m_strPropName.isEmpty() )
  {
    OdRxMemberPtr pProp = OdRxMemberQueryEngine::theEngine()->find(m_pObject, m_strPropName);

    if (!pProp.isNull() && pProp->isKindOf(OdRxPropertyBase::desc()))
    {
      OdRxPropertyBasePtr pPropertyBase = pProp;
      OdRxPropertyBase* pActualProp = getActualProperty(m_pObject, pPropertyBase, m_iSubPropertyIndex, -1);

      if (pActualProp && pActualProp->isKindOf(OdRxIndexedProperty::desc()))
      {
        OdRxIndexedPropertyPtr pIndexedProp = pActualProp;

        int iCount = 0;
        pIndexedProp->tryGetCount(m_pObject, iCount);

        if( insertCDAPropertyValueToEnd(pPropertyBase, m_pObject, m_iSubPropertyIndex, m_defaultValue) )
        {
          m_listCtrl.updateControlData();
        }
      }
    }
  }
}

//=================================================================================

void CCDAIndexedArrayDlg::OnDeleteBtn()
{
  if (m_bEnable && !m_strPropName.isEmpty())
  {
    OdRxMemberPtr pProp = OdRxMemberQueryEngine::theEngine()->find(m_pObject, m_strPropName);

    if (!pProp.isNull() && pProp->isKindOf(OdRxPropertyBase::desc()))
    {
      OdRxPropertyBasePtr pPropertyBase = pProp;
      OdRxPropertyBase* pActualProp = getActualProperty(m_pObject, pPropertyBase, m_iSubPropertyIndex, -1);

      if (pActualProp && pActualProp->isKindOf(OdRxIndexedProperty::desc()))
      {
        int nItems = getIndexedPropertyCount(m_pObject, pPropertyBase, m_iSubPropertyIndex, -1);

        if (nItems == 0)
          nItems = 1;

        int nChildren = m_listCtrl.GetItemCount() / nItems;

        OdRxIndexedPropertyPtr pIndexedProp = pActualProp;

        int iCount = m_listCtrl.GetSelectionMark() / nChildren;

        if( (iCount >= 0) && deleteCDAPropertyValue(pPropertyBase, m_pObject, m_iSubPropertyIndex, iCount) )
        {
          m_listCtrl.updateControlData();
        }
      }
    }
  }
}

//=================================================================================

void CCDAIndexedArrayDlg::OnLvnItemchangedValueList(NMHDR *pNMHDR, LRESULT *pResult)
{
  int iCurSel = m_listCtrl.GetSelectionMark();
  CWnd* pDelBtn = GetDlgItem(IDC_DELETE);
  pDelBtn->EnableWindow(m_bEnable && (iCurSel >= 0));
}

//=================================================================================

BEGIN_MESSAGE_MAP(CCDAIndexedArrayDlg, CDialog)
  ON_NOTIFY(LVN_ITEMCHANGING, IDC_PROP_LIST, CCDAIndexedArrayDlg::OnLvnItemchangedValueList)
  ON_BN_CLICKED(IDOK, OnOk)
  ON_BN_CLICKED(IDC_ADD, OnAddBtn)
  ON_BN_CLICKED(IDC_DELETE, OnDeleteBtn)
END_MESSAGE_MAP()

//=================================================================================

// CCDAUnionTypeDlg dialog

IMPLEMENT_DYNAMIC(CCDAUnionTypeDlg, CDialog)

CCDAUnionTypeDlg::CCDAUnionTypeDlg(CWnd* pParent, OdRxObject* pObject, OdRxObject* pDb, OdRxPropertyBase* pProperty, OdInt32 iSubPropertyIndex, OdInt32 iArrayIndex)
  : CDialog(CCDAUnionTypeDlg::IDD, pParent)
{
  m_pDb       = pDb;
  m_pProperty = pProperty;
  m_pObject   = pObject;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_iArrayIndex = iArrayIndex;
}

//=================================================================================

CCDAUnionTypeDlg::~CCDAUnionTypeDlg()
{
}

//=================================================================================

void CCDAUnionTypeDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_PROP_LIST, m_listCtrl);
}

//=================================================================================

BOOL CCDAUnionTypeDlg::OnInitDialog()
{
  BOOL bRet = CDialog::OnInitDialog();

  OdRxPropertyBase* pPropBase = getActualProperty(m_pObject, m_pProperty, m_iSubPropertyIndex, m_iArrayIndex);
  const OdRxAttributeCollection& attrs = pPropBase->attributes();
  const OdRxAttribute* pUnionTypeAttr = attrs.get(OdRxUnionTypeAttribute::desc());
  OdString strUnionType;

  OdRxValue propValue;

  OdString strValType = L"NULL";

  if( getCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, propValue) )
  {
    if (propValue.type() == OdRxValueType::Desc<OdRxObjectPtr>::value())
    {
      OdRxObjectPtr* pRxObj = rxvalue_cast<OdRxObjectPtr>(&propValue);

      if (pRxObj && !pRxObj->isNull())
        strValType = (*pRxObj)->isA()->name();
    }
    else
      strValType = propValue.type().name();
  }

  int iTypeIndex = -1;

  if (pUnionTypeAttr && !pPropBase->isReadOnly(m_pObject))
  {
    OdRxUnionTypeAttribute* pUnionXAttr = (OdRxUnionTypeAttribute*)(pUnionTypeAttr);
    strUnionType = pUnionXAttr->typenames();
  }

  m_bRxObject = pPropBase->type() == OdRxValueType::Desc<OdRxObjectPtr>::value();

  CComboBox* pCombo = (CComboBox*)(GetDlgItem(IDC_PROPTYPE_COMBO));

  while (strUnionType.find(L";") != -1)
  {
    OdString strType = strUnionType.left(strUnionType.find(L";"));
    strUnionType = strUnionType.right(strUnionType.getLength() - strType.getLength() - 1);

    if (!strType.isEmpty())
    {
      if (strType == L"0")
        strType = L"NULL";

      if( strType == strValType )
        iTypeIndex = pCombo->GetCount();

      pCombo->AddString(strType);
    }
  }

  OdString strType = strUnionType;

  if (!strType.isEmpty())
  {
    if (strType == L"0")
      strType = L"NULL";

    if (strType == strValType)
      iTypeIndex = pCombo->GetCount();

    pCombo->AddString(strType);
  }

  if( m_bRxObject && (pCombo->FindString(0, L"NULL") == -1) )
    pCombo->AddString(L"NULL");

  if( iTypeIndex < 0 )
  {
    iTypeIndex = pCombo->GetCount();
    pCombo->AddString(strValType);
  }

  pCombo->SetCurSel(iTypeIndex);

  CWnd* pListCtrl = (CWnd*)(GetDlgItem(IDC_PROP_LIST));
  RECT wndRect;
  pListCtrl->GetClientRect(&wndRect);
  wndRect.bottom += 125;

  if( m_bRxObject )
  {
    OdRxObjectPtr* pRxObj = rxvalue_cast<OdRxObjectPtr>(&propValue);

    if (pRxObj && !pRxObj->isNull())
    {
      m_pCurListObject = *pRxObj;
      m_listCtrl.initData(m_pDb, m_pCurListObject, wndRect, -1, OdString::kEmpty, -1, 55, true);
    }
    else
      m_listCtrl.initData(m_pDb, m_pObject, wndRect, m_iSubPropertyIndex, m_pProperty->name(), m_iArrayIndex, 55, true);    
  }
  else
    m_listCtrl.initData(m_pDb, m_pObject, wndRect, m_iSubPropertyIndex, m_pProperty->name(), m_iArrayIndex, 55, true);

  return bRet;
}

//=================================================================================

void CCDAUnionTypeDlg::OnOk()
{
  CDialog::OnOK();
}

//=================================================================================

void CCDAUnionTypeDlg::OnPropTypeComboSelchange()
{
  CComboBox* pCombo = (CComboBox*)(GetDlgItem(IDC_PROPTYPE_COMBO));
  int iCurSel = pCombo->GetCurSel();
  CString strCValue;
  pCombo->GetLBText(iCurSel, strCValue);

  OdString strValue = strCValue;

  if( m_bRxObject )
  {
    OdRxObjectPtr pNewObj;

    if( strCValue != L"NULL" )
    {
      OdRxClassPtr pObjectClass = (OdRxObjectPtr)(::odrxClassDictionary()->getAt(strValue));

      if( !pObjectClass.isNull() )
      {
        if (pObjectClass->constructor())
          pNewObj = pObjectClass->create();
      }
    }

    OdRxValue newValue(pNewObj);

    if( setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newValue) )
    {
      m_pCurListObject = pNewObj;

      if( !m_pCurListObject.isNull() )
        m_listCtrl.setRxObject(m_pCurListObject, -1, -1);
      else
        m_listCtrl.setRxObject(m_pObject, m_iSubPropertyIndex, m_iArrayIndex);
    }
  }
  else
  {
    OdRxValue newValue;

    if (strCValue != L"NULL")
    {
      OdRxClassPtr pObjectClass = (OdRxObjectPtr)(::odrxClassDictionary()->getAt(strValue));

      if (!pObjectClass.isNull() && pObjectClass->isKindOf(OdRxValueType::desc()))
      {
        OdRxValueTypePtr pValueType = (OdRxValueTypePtr)(pObjectClass);

        if (!pValueType.isNull())
          newValue = pValueType->createValue();
      }
    }

    if (setCDAPropertyValue(m_pProperty, m_pObject, m_iSubPropertyIndex, m_iArrayIndex, newValue))
    {
      m_listCtrl.updateControlData();
    }
  }
}

//=================================================================================

BEGIN_MESSAGE_MAP(CCDAUnionTypeDlg, CDialog)
  ON_BN_CLICKED(IDOK, OnOk)
  ON_CBN_SELCHANGE(IDC_PROPTYPE_COMBO, CCDAUnionTypeDlg::OnPropTypeComboSelchange)
END_MESSAGE_MAP()

//=================================================================================
