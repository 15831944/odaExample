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
#ifndef _ODA_PRC_APP_TREE_FILLER_
#define _ODA_PRC_APP_TREE_FILLER_

#define STL_USING_MAP
#include "OdaSTL.h"

#include "RxObjectImpl.h"
#include "OdaPrcApp.h"
#include "PrcFile.h"
#include "StaticRxObject.h"
#include "ExPrcDumper.h"
#include "PrcDumpModule.h"

extern COdaPrcApp theApp;

class OdaPrcTreeFiller
{
public:
  OdaPrcTreeFiller(OdPrcFile* pDb, CTreeCtrl *pObjTree)
    : m_pObjTree(pObjTree)
    , m_pDb(pDb)
    , m_dbTreeItem(0)
  {
    ODA_ASSERT(pObjTree && pDb);
  }
  ~OdaPrcTreeFiller()
  {
  }

  HTREEITEM addTreeItem(const CString& strName, bool bHasChildren = true,
      HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST );
  HTREEITEM addTreeItemWithId(const CString& strName, OdPrcObjectId objId,
      bool bHasChildren = true, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST );
  HTREEITEM addPrcObject(OdRxObjectPtr pPrcObj, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
  HTREEITEM addClass(const OdString& className, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
  void expandItem(TVITEM itemNew);
  void addChilds(const OdRxObject *pObj, HTREEITEM hParentItem, OdUInt32 childLevelCounter);
  
  OdRxObjectPtr getObject(TVITEM hItem);
  OdString getItemName(TVITEM hItem);

  void clear();

  HTREEITEM getDbTreeItem();
  OdPrcFile* database() const { return m_pDb; }

private:
  CTreeCtrl* m_pObjTree;
  OdPrcFile* m_pDb;

  HTREEITEM m_dbTreeItem;

  typedef std::map<HTREEITEM, OdRxObjectPtr> TableMap;
  TableMap m_nonDBROItems;
};


class OdaPrcListFiller : public OdRxObjectImpl< OdExPrcDumper >
{
public:
  ODRX_HEAP_OPERATORS();

  OdaPrcListFiller(OdPrcFile* pDb, CListCtrl* pObjList)
    : m_pObjList(pObjList)
    , m_pDb(pDb)
  {
    ODA_ASSERT(pObjList && pDb);
  }
  ~OdaPrcListFiller()
  {
  }

  void clear();

  // OdExPrcDumper overridden
  virtual void dumpFieldName(const OdString& fieldName);
  virtual void dumpFieldValue(const OdString& fieldValue);  
  virtual void dumpFieldType( const OdString& fieldType);

  virtual void dumpByName(const OdString& itemName);
  virtual void dump(OdRxObjectPtr pObj);

  void writeFieldValue(const OdString& fieldName, const OdPrcUniqueId &id);
private:
  CListCtrl* m_pObjList;
  OdPrcFile* m_pDb;

  int addElement(OdString propertyType, OdString propertyName, OdString propertyValue, int elPos);
  void addLParam(int elPos, LPARAM param);
};

class TreeListener : public OdPrcListener
{
  OdExPrcDumper *m_pDumper;
  mutable OdArray<OdPrcObjectId> m_childs;
  TreeListener()
  {
  }
public:
  TreeListener(OdExPrcDumper *pDumper)
    : m_pDumper(pDumper)
  {
  }

  const OdArray<OdPrcObjectId> &childs()
  {
    return m_childs;
  }

  virtual void dumpInt8(const OdChar *pName, OdInt8 value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpInt32(const OdChar *pName, OdInt32 value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpUInt8(const OdChar *pName, OdUInt8 value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpUInt16(const OdChar *pName, OdUInt16 value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpUInt32(const OdChar *pName, OdUInt32 value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpUInt32Hex(const OdChar *pName, OdUInt32 value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValueHex(pName, value);
  }
  virtual void dumpUniqueId(const OdChar *pName, OdPrcUniqueId value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpObjectId(const OdChar *pName, OdPrcObjectId value) const
  {
    m_childs.push_back(value);
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpUncompressedBlock(const OdChar *pName, OdBinaryData value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpBoolean(const OdChar *pName, OdBool value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpDouble(const OdChar *pName, OdDouble value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpFloat(const OdChar *pName, float value) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, value);
  }
  virtual void dumpBits(const OdChar *pName, const OdBitBinaryData &data) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, data);
  }
  virtual void dumpAnsiString(const OdChar *pName, OdAnsiString str) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, OdString(str));
  }
  virtual void dumpString(const OdChar *pName, OdString str) const
  {
    if (m_pDumper) m_pDumper->writeFieldValue(pName, str);
  }
};


#endif // _ODA_PRC_APP_TREE_FILLER_
