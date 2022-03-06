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

#ifndef OdConstraintGroupNodeImpl_INCLUDED_
#define OdConstraintGroupNodeImpl_INCLUDED_/*!DOM*/

#include "DbConstraintsExports.h"
#include "DbAudit.h"
#include "DbObjectId.h"
#include "OdArray.h"
#include "OdConstraintGroupNode.h"
#include "DbImpAssoc2dConstraintGroup.h"

class OdDbDwgFiler;
class OdDbDxfFiler;

#include "TD_PackPush.h"

/** \details
  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdConstraintGroupNodeImpl
{
public:
  /** \details
    Constructor creates an instance of this class.
  */
  OdConstraintGroupNodeImpl();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdConstraintGroupNodeImpl();

  /** \details
    Sets an owner action using given object ID.
  */
  OdResult setOwnerAction(OdDbObjectId id);

  /** \details
    Adds a connection using the given constraint group node ID.
  */
  OdResult addConnection(OdConstraintGroupNodeId id);

  /** \details
    Deletes a connection using the given constraint group node ID.
  */
  OdResult removeConnection(OdConstraintGroupNodeId id, bool &isNoConnection);

  /** \details
    Returns the connection QTY.
  */
  unsigned int getConnectionQty() const;

  /** \details
    Returns the constraint group node ID at given index.
  */
  OdConstraintGroupNodeId getConnectionAt(int idx) const;

  /** \details
    Returns the constraint group node ID.
  */
  OdConstraintGroupNodeId nodeId() const;

  /** \details
    Sets the constraint group node ID.
  */
  void setNodeId(OdConstraintGroupNodeId val);

  /** \details
    Returns the owing group node ID.
  */
  OdDbObjectId owningConstraintGroupId()const;

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

  /** \details
    Performs an audit of internal data of constraint group node.
  */
  virtual void audit(OdConstraintGroupNode*, OdAuditInfo* pAuditInfo);

protected:
  /*!DOM*/
  OdConstraintGroupNodeId   m_Id;
  /*!DOM*/
  OdDbObjectId              m_groupObjectId;
  /*!DOM*/
  OdGroupNodeIdArray        m_connections;
  /*!DOM*/
  OdUInt8     m_Unk_UInt8;
};

#include "TD_PackPop.h"
#endif
