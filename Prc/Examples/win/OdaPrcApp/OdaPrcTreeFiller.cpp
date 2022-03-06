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

// optimization broke topology tree
#pragma optimize ("", off)

#include "stdafx.h"
#include "PrcCommon.h"
#include "OdaPrcTreeFiller.h"
#include "ExPrcElementDumperPE.h"

HTREEITEM OdaPrcTreeFiller::addTreeItem(const CString& sName, bool bHasChildren,
  HTREEITEM hParent, HTREEITEM hInsertAfter)
{
  HTREEITEM hItem = m_pObjTree->InsertItem(sName, hParent, TVI_LAST);
  TVITEM item = { 0 };
  item.mask   = TVIF_HANDLE | TVIF_CHILDREN | TVIF_PARAM;
  item.hItem  = hItem;

  return hItem;
}

HTREEITEM OdaPrcTreeFiller::addTreeItemWithId(const CString& sName, OdPrcObjectId objId,
  bool bHasChildren, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
  
  /*HTREEITEM hItem = m_pObjTree->InsertItem(sName, hParent, TVI_LAST);
  TVITEM item = { 0 };
  item.mask   = TVIF_HANDLE | TVIF_CHILDREN | TVIF_PARAM;
  item.hItem  = hItem;*/  

  OdDbStub* pStub(static_cast<OdDbStub*>(objId));
  UINT mask = TVIF_TEXT | TVIF_HANDLE | TVIF_PARAM;
  if (bHasChildren) mask |= TVIF_CHILDREN;

  HTREEITEM hItem = m_pObjTree->InsertItem(mask, sName, 0, 0, 0, 0,
      (LPARAM) pStub, hParent, hInsertAfter);

  return hItem;
}

OdPrcObjectId getObjectId(const OdRxObject *pObj);
HTREEITEM OdaPrcTreeFiller::addPrcObject(OdRxObjectPtr pPrcObj, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
  if (!pPrcObj.isNull())
  {
    CString sName;
    OdPrcEntity_DumperPtr pObjDumper = OdPrcEntity_Dumper::cast( pPrcObj );
    int hasChildren = 0;
    if (pObjDumper.get())
    {
      sName = (LPCTSTR)(pObjDumper->getName(pPrcObj.get()));
      hasChildren = true;
    }
    else
    {
      sName.Format(_T("<%s>"), (LPCTSTR)(pPrcObj->isA()->name()));
    }

    HTREEITEM hItem = m_pObjTree->InsertItem(sName, hParent, hInsertAfter);
    TVITEM item = { 0 };
    item.mask   = TVIF_HANDLE | TVIF_CHILDREN | TVIF_PARAM;
    item.hItem  = hItem;
    item.cChildren  = hasChildren;
    
    m_nonDBROItems[hItem] = pPrcObj;

    OdPrcObjectId id = getObjectId(pPrcObj);
    OdDbStub* pIdStub = (OdDbStub*)(id);
    item.lParam = (LPARAM)pIdStub;
    // Save NonDBRO collections in separate map
    if ( pIdStub == 0 )
    {
      m_nonDBROItems[hItem] = pPrcObj;
    }
    m_pObjTree->SetItem(&item);
    //if ( m_sset->isMember(id) )
    //{
    //  m_pObjTree->SetItemState( hItem, TVIS_BOLD, TVIS_BOLD );
    //}*/
    return hItem;
  }
  return 0;
}

HTREEITEM OdaPrcTreeFiller::addClass(const OdString& className, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
  CString sName;
  sName.Format(_T("<%s>"), (LPCTSTR)(className));
  int hasChildren = 1;

  HTREEITEM hItem = m_pObjTree->InsertItem(sName, hParent, hInsertAfter);
  TVITEM item = { 0 };
  item.mask   = TVIF_HANDLE | TVIF_CHILDREN | TVIF_PARAM;
  item.hItem  = hItem;
  item.cChildren  = hasChildren;

  m_pObjTree->SetItem(&item);
  //if ( m_sset->isMember(id) )
  //{
  //  m_pObjTree->SetItemState( hItem, TVIS_BOLD, TVIS_BOLD );
  //}
  return hItem;
}

void OdaPrcTreeFiller::addChilds(const OdRxObject *pObj, HTREEITEM hParentItem, OdUInt32 childLevelCounter)
{
  if (childLevelCounter == 0)
  {
    return;
  }

  TreeListener pListener(0);
  OdPrcEntity_Dumper *pDumper = OdPrcEntity_Dumper::cast(pObj);
  if (pDumper != 0)
  {
    pDumper->dump(pObj, &pListener);

    OdPrcObjectId parentId = getObjectId(pObj);
    const OdArray<OdPrcObjectId> &childs = pListener.childs();
    for(OdUInt32 i=0; i<childs.size(); ++i)
    {
      OdPrcObjectId id = childs[i];
      if (!id.isNull() && id != parentId)
      {
        OdPrcObjectPtr pObj = id.safeOpenObject(kForRead);
        OdString tmp = pObj->isA()->name() + " (" + id.getHandle().ascii() + ")";
        HTREEITEM hItem = addTreeItemWithId(tmp.c_str(), id, true, hParentItem);

        addChilds(pObj, hItem, childLevelCounter - 1);
      }
    }

    // Special processing for subentities without objectId
    {
      OdRxObjectPtrArray subs = pDumper->subElements(pObj);
      for(OdUInt32 f=0; f<subs.size(); ++f)
      {
        HTREEITEM hItem = addPrcObject(subs[f], hParentItem);
        addChilds(subs[f], hItem, childLevelCounter - 1);
      }
    }
  }
}

void OdaPrcTreeFiller::expandItem(TVITEM itemNew)
{
  OdRxObjectPtr pElm = getObject(itemNew);

  if ( !pElm.isNull() )
  {
    addChilds(pElm, itemNew.hItem, 1);
  }
}

HTREEITEM OdaPrcTreeFiller::getDbTreeItem() 
{
  // Add root database node
  if (!m_dbTreeItem)
  {
    CString sName;
    sName.Format(_T("<%s>"), (LPCTSTR)(m_pDb->isA()->name()));
    m_dbTreeItem = m_pObjTree->InsertItem(sName, TVI_ROOT, TVI_LAST);
    TVITEM item = { 0 };
    item.mask   = TVIF_HANDLE | TVIF_CHILDREN | TVIF_PARAM;
    item.hItem  = m_dbTreeItem;
    item.cChildren  = 1;
    item.lParam = 0;
    m_pObjTree->SetItem(&item);
  }

  return m_dbTreeItem; 
}

void OdaPrcTreeFiller::clear()
{
  m_pObjTree->DeleteAllItems();
  m_dbTreeItem = 0;
}

OdString OdaPrcTreeFiller::getItemName(TVITEM hItem)
{
  return (LPCTSTR)m_pObjTree->GetItemText(hItem.hItem);
}

OdRxObjectPtr OdaPrcTreeFiller::getObject(TVITEM tvitem)
{
  OdPrcObjectId elmId = reinterpret_cast<OdDbStub*>(tvitem.lParam);
  if (!elmId.isNull())
  {
    return elmId.openObject();
  }
  else
  {
    TableMap::iterator it = m_nonDBROItems.find(tvitem.hItem);
    if (it != m_nonDBROItems.end())
    {
      return it->second;
    }
    /*else if (tvitem.hItem == m_dbTreeItem)
    {
      return database();
    }*/
  }
  return OdPrcObjectPtr();
}

void OdaPrcListFiller::clear()
{
  m_pObjList->DeleteAllItems();
}

void OdaPrcListFiller::dumpFieldName( const OdString& fieldName )
{
  m_pObjList->InsertItem(m_pObjList->GetItemCount(), fieldName);
}

void OdaPrcListFiller::dumpFieldValue( const OdString& fieldValue )
{
  m_pObjList->SetItemText(m_pObjList->GetItemCount() - 1, 1, fieldValue);
}

void OdaPrcListFiller::dumpFieldType( const OdString& fieldType )
{
  m_pObjList->SetItemText(m_pObjList->GetItemCount() - 1, 2, fieldType);
}

int OdaPrcListFiller::addElement(OdString propertyType, 
  OdString propertyName, OdString propertyValue, int elPos)
{
  m_pObjList->InsertItem(elPos, propertyType.c_str());
  m_pObjList->SetItemText(elPos, 1, propertyName.c_str());
  m_pObjList->SetItemText(elPos, 2, propertyValue.c_str());
  return elPos;
}

void OdaPrcListFiller::addLParam(int elPos, LPARAM param)
{
  LVITEM lvi = {0};
  lvi.mask = LVIF_PARAM;
  lvi.iItem = elPos;
  if (m_pObjList->GetItem(&lvi))
  {
    lvi.lParam = param;
    m_pObjList->SetItem(&lvi);
  }
}

void OdaPrcListFiller::writeFieldValue(const OdString& name, const OdPrcUniqueId &id)
{
  dumpFieldName( name );
  OdString val;
  OdUInt32 id0, id1, id2, id3;
  ((OdPrcUniqueId &)id).getID(id0, id1, id2, id3);
  val.format( L"%x %x %x %x", id0, id1, id2, id3);
  dumpFieldValue( val );
}

void OdaPrcListFiller::dump(OdRxObjectPtr pObj)
{
  TreeListener pListener(this);
  OdPrcEntity_Dumper *pDumper = OdPrcEntity_Dumper::cast(pObj);
  if (pDumper)
  {
    pDumper->dump(pObj, &pListener);
  }
  else
  {
    addElement("No dumper", "", "", 0);
  }
}

void OdaPrcListFiller::dumpByName(const OdString& itemName)
{
  TreeListener pListener(this);
  if (itemName == "<OdPrcFileDoc>")
  {
    OdPrcEntity_Dumper::cast(m_pDb)->dump(m_pDb, &pListener);
  }
  else if (itemName == "Schema")
  {
    OdPrcEntity_Dumper::cast(&m_pDb->schema())->dump(&m_pDb->schema(), &pListener);
  }
  else if (itemName == "ModelFileData")
  {
    OdPrcEntity_Dumper::cast(&m_pDb->modelFileData())->dump(&m_pDb->modelFileData(), &pListener);
  }
  else
  {
    addElement("No information", "", "", 0);
  }
}

// void OdaPrcListFiller::dumpVariant(const OdChar* sPropertyName,
//   const OdTfVariant& propertyValue, int insertPos, int indent)
// {
//   const OdString spaces(OD_T("                                                            "));
//   if (insertPos == -1) insertPos = m_pObjList->GetItemCount();
// 
//   OdString type(TfToString::tfVarTypeToString(propertyValue));
//   if (propertyValue.isVariantArray()) {
//     const OdTfVariantArray& arr = propertyValue.getVariantArray();
//     if (arr.size() != 0) {
//       int elId = addElement(spaces.left(indent) + L"+ " + type, sPropertyName,
//           OdString(L"[Array of properties]"), insertPos);
// 
//       /*
//         m_TfArrays allows us to get OdTfVariantArray by LVITEM::lParam
//         after clicking on certain CListCtrl element.
//         OdTfVariant::getVariantArray()::getPtr() was chosen as a key
//         for m_TfArrays because we shouldn't use LVITEM::iItem for this purpose
//         as it changes during work (when some items are inserted or removed).
//       */
//       addLParam(elId, (LPARAM) arr.getPtr());
//       m_TfArrays[(LPARAM) arr.getPtr()] = arr;
//     } else {      
//       addElement(spaces.left(indent) + type, sPropertyName,
//           OdString(L"[Empty array]"), insertPos);
//     }
//     return;
//   }
// 
//   switch(propertyValue.type()) {
//     case OdTfVariant::kRxObjectWeakPtr: {
//       OdRxObject *obj = propertyValue.getRxObjectWeakPtr();
//       size_t pObjSize = reinterpret_cast<size_t>(obj);
//       OdString sValue = (pObjSize == 0) ? L"[Null pointer]" : L"[Object weak pointer]";
//       addElement(spaces.left(indent) + type, sPropertyName, sValue, insertPos);
//     } break;
//     case OdTfVariant::kRxObjectPtr: {
//       const OdRxObject *obj = propertyValue.getRxObjectPtr().get();
//       size_t pObjSize = reinterpret_cast<size_t>(obj);
//       if (pObjSize == 0) {
//         addElement(spaces.left(indent) + type, sPropertyName,
//             OdString().format(L"[Null pointer]"), insertPos);
//       } else if ((OdPrcObjectPtr(obj))->getClass()->getProperties().size() == 0) {
//         addElement(spaces.left(indent) + type, sPropertyName,
//             OdString().format(L"[Empty object]"), insertPos);
//       } else {
//         int elId = addElement(spaces.left(indent) + L"+ " + type, sPropertyName,
//             OdString().format(L"[Object pointer]"), insertPos);
//         addLParam(elId, (LPARAM) propertyValue.getRxObjectPtr().get());
//       }
//     } break;
//     case OdTfVariant::kDbStubPtr: {
//       OdDbStub* pStub = propertyValue.getDbStubPtr();
//       OdString sValue(OdString().format(
//           L"%i", (pStub == NULL) ? -1 : static_cast<OdUInt64>(
//               OdDbBaseDatabasePEPtr(m_pDb)->getHandle(propertyValue.getDbStubPtr()))));
//       addElement(spaces.left(indent) + type, sPropertyName, sValue, insertPos);
//     } break;
//     case OdTfVariant::kGeVariant: {
//       addElement(spaces.left(indent) + TfToString::geVarTypeToString(propertyValue.getGeVariant()),
//           sPropertyName, TfToString::geVarValueToString(propertyValue.getGeVariant()), insertPos);
//     } break;
//     case OdTfVariant::kEmpty: {
//       addElement(spaces.left(indent) + type, sPropertyName, 
//           OdString().format(L"[Empty]"), insertPos);
//     } break;
//     default: {
//       addElement(spaces.left(indent) + type, sPropertyName, toString(propertyValue), insertPos);
//     }
//   } // switch
// 
//   return;
// }
