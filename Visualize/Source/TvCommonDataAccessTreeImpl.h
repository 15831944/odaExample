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

#ifndef _ODTV_COMMONDATAACCESS_TREE_IMPL_H_INCLUDED_ 
#define _ODTV_COMMONDATAACCESS_TREE_IMPL_H_INCLUDED_

#include "OdaCommon.h"
#include "DbObject.h"
#include "DbDictionary.h"
#include "TvCommonDataAccessTree.h"
#include "TvUserDataImpl.h"
#include "TvInterfaceWrappers.h"
#include "RxModelHierarchyTreeBaseImpl.h"


typedef std::set<OdTvGsViewId> ViewSet;
typedef std::map<OdTvGsDeviceId, ViewSet> DeviceViewMap;

class OdTvCDATreeImpl : public OdRxModelHierarchyTreeBaseImpl
{
public:
  OdTvCDATreeImpl()
    : OdRxModelHierarchyTreeBaseImpl()
    , m_bSiblingNodesExist(false)
  {

  }

  OdRxModelTreeBaseNodePtr createNodeObject();

  void addDisabledViewport(const OdTvGsDeviceId& deviceId, const OdTvGsViewId& viewportId);

  void activateDisabledViewports();

  DeviceViewMap* getDisabledViewportsMap() { return &m_disabledViewports; }

  void setDisabledViewportsMap(const DeviceViewMap& disabledViewports) { m_disabledViewports = disabledViewports; }

  OdTvCDATreeNodePtr getNodeById(OdUInt64 id);

  void fillMap(const OdTvCDATreeNodePtr& pNode);

  void setSiblingNodesExist(bool bExist) { m_bSiblingNodesExist = bExist; }
  bool getSiblingNodesExist() const { return m_bSiblingNodesExist; }

  void addSiblingNode(OdUInt64 current, OdUInt64 sibling);

  void connectSiblingNodes();

private:
  DeviceViewMap m_disabledViewports;
  std::map<OdUInt64, OdTvCDATreeNodePtr> m_nodes;
  std::map<OdUInt64, OdUInt64>  m_siblingUniqIdMap;
  bool m_bSiblingNodesExist;
};

/** \details
This class is the DB implementation of the object owner over device 'OdTvCDATree'.
Here it is important to note that 'assertWriteEnabled' not need here.
*/
class OdTvCDATreeStorageImpl : public OdTvDbObject, public OdTvXDataStorage
{
  OdTvCDATreeStorageImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvCDATreeStorageImpl);

  virtual ~OdTvCDATreeStorageImpl();

  /** \details
  Set underlaying CDA tree
  */
  void setTree(OdTvCDATreePtr pTree);

  /** \details
  Returns the underlaying CDA tree
  */
  OdTvCDATreePtr getTree() const;

  /** \details
  Set underlaying CDA tree name
  */
  void setTreeName(const OdString& strName);

  /** \details
  Returns the underlaying CDA tree naem
  */
  OdString getTreeName() const;

  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
 
private:

  //Underlaying CDA tree
  OdTvCDATreePtr m_CDATreePtr;

  //Underlaying CDA tree name
  OdString m_CDATreeName;
};

typedef OdSmartPtr<OdTvCDATreeStorageImpl> OdTvCDATreeStorageImplPtr;


/** \details
This is an wrapper of the interface class for OdTvCDATreeStorage object.

\remarks
The purpose of this class is to connect the internal tree storage object with an interface object
*/

class OdTvCDATreeStorageWrapper : public OdTvCDATreeStorage
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvCDATreeStorage, OdTvCDATreeStorageImpl)

protected:
  ODRX_HEAP_OPERATORS();

public:

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Interface implementation
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Returns the underlaying CDA tree
  */
  virtual OdTvCDATreePtr getTree(OdTvResult* rc = NULL) const;

  /** \details
  Returns the name of the underlaying CDA tree
  */
  virtual OdString getTreeName(OdTvResult* rc = NULL) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
};


/** \details
This is an implementation of the iterator class for the CDA tree storages
*/
class ODTV_EXPORT OdTvCDATreeStoragesIteratorImpl : public OdTvCDATreeStoragesIterator
{
  friend class OdTvDatabaseImpl;
public:

  virtual ~OdTvCDATreeStoragesIteratorImpl();

  /** \details
  Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done(OdTvResult* rc = NULL) const;

  /** \details
  Steps this Iterator object.
  */
  virtual OdTvResult step();

  /** \details
  Returns the CDA tree storage currently referenced by this Iterator object.
  */
  virtual OdTvCDATreeStorageId getCDATreeStorage(OdTvResult* rc = NULL) const;

  /** \details
  Positions this Iterator object at the specified device.
  \param objectId [in]  CDA tree storage.
  */
  virtual OdTvResult seek(const OdTvCDATreeStorageId& treeId);

  /** \details
  Methods for creating the object
  */
  static OdTvCDATreeStoragesIteratorPtr createObject(OdTvDbDictionaryIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvCDATreeStoragesIteratorImpl();
  OdTvCDATreeStoragesIteratorImpl(OdTvDbDictionaryIterator* pDbIterator);

  // Db iterator
  OdTvDbDictionaryIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;
};


#endif // _ODTV_COMMONDATAACCESS_TREE_IMPL_H_INCLUDED_
