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

#ifndef _ODTV_COMMONDATAACCESS_TREE_H_INCLUDED_ 
#define _ODTV_COMMONDATAACCESS_TREE_H_INCLUDED_

#include "Tv.h"
#include "RxModelHierarchyTreeBase.h"
#include "SmartPtr.h"
#include "TvCommonDataAccessTreeNode.h"
#include "TvGsDevice.h"
#include "TvGsView.h"

#define OdTvCDAPropNameForGrouping L"ClassName"

/** \details
  This class implements the hierarchy tree for the Common Data Access mechanism specific for using with Visualize SDK
*/
class ODTV_EXPORT OdTvCDATree : public OdRxModelHierarchyTreeBase
{
public:
  ODRX_DECLARE_MEMBERS(OdTvCDATree);
  ODRX_HEAP_OPERATORS();

  /** \details
    Add the node as a child to the existing node.
    
    \param pNode    [in] A pointer the node to which the new node should be added
    \param strName  [in] Name of the node which should be added
    \param type     [in] Type of the node which should be added
    \returns Returns a smart pointer to the newly created and added node.
    \remarks
    If the rc parameter is not null and the node was successfully added, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvCDATreeNodePtr addNode(OdTvCDATreeNodePtr& pNode, const OdString& strName, HierarchyTreeObjectType type, OdTvResult *rc = NULL);

  /** \details
    Restores all disabled viewport object's.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult enableViewports();

protected:
  /** \details
   Default constructor for the OdTvCDATree class.
  */
  OdTvCDATree();
};

/** \details
  A data type that represents a smart pointer to an <link OdTvCDATreeNode, OdTvCDATreeNode> object.
*/
typedef OdSmartPtr<OdTvCDATree> OdTvCDATreePtr;


/** \details
  This class is an interface for the object that contains the CDA (Common Data Access) tree
*/
class ODTV_EXPORT OdTvCDATreeStorage : public OdTvHandledIObject
{
public:

  /** \details
    Returns the pointer to the underlaying CDA tree
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the pointer to the underlaying CDA tree
    \remarks
    If the rc parameter is not null and the underlaying CDA tree was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvCDATreePtr getTree(OdTvResult* rc = NULL) const = 0;

  /** \details
    Returns the name of the underlaying CDA tree
    
    \param rc [out] The name of the underlaying tree
    \returns Returns the name of the underlaying CDA tree
    \remarks
    If the rc parameter is not null and the underlaying CDA tree name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getTreeName(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvCDATreeStorage, OdTvCDATreeStorage> object.
*/
typedef OdTvSmartPtr<OdTvCDATreeStorage> OdTvCDATreeStoragePtr;


/** \details
  The interface class for a database object identifier that allows access to the <link OdTvCDATreeStorage, OdTvCDATreeStorage> object.
*/
class ODTV_EXPORT OdTvCDATreeStorageId : public OdTvId
{
public:

  /** \details
    Opens the CDA tree data storage determined with its identifier for a read or write operation.
    
    \param mode [in] An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the CDA tree storage object.
    \remarks
    If the rc parameter is not null and the CDA tree storage is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvCDATreeStoragePtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;
};


/** \details
  The interface class for the iterator of <link OdTvCDATreeStorage, OdTvCDATreeStorage> objects.
  An iterator object provides sequential access to a collection of CDA tree storages.
*/
class ODTV_EXPORT OdTvCDATreeStoragesIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Retrieves the CDA tree storage that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the device identifier if the iterator refers to a CDA tree storage; otherwise it returns a null value identifier.
    \remarks
    If the rc parameter is not null and the CDA tree storage identifier is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    If the iterator refers to a CDA tree storage, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvCDATreeStorageId getCDATreeStorage(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches the CDA tree storage defined through its identifier and moves the iterator to this device if found.
    
    \param treeId [in] A CDA tree storage identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the CDA tree storage specified through its identifier is found, the method returns the tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvCDATreeStorageId& treeId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvCDATreeStoragesIterator, OdTvCDATreeStoragesIterator> object.
*/
typedef OdTvSmartPtr<OdTvCDATreeStoragesIterator> OdTvCDATreeStoragesIteratorPtr;

#endif //_ODTV_COMMONDATAACCESS_TREE_H_INCLUDED_

