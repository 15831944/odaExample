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

#ifndef OdConstraintGroupNode_INCLUDED
#define OdConstraintGroupNode_INCLUDED

#include "DbConstraintsExports.h"
#include "RxObject.h"
#include "DbObjectId.h"
#include "OdArray.h"

class OdDbDwgFiler;
class OdDbDxfFiler;

#include "TD_PackPush.h"

class OdConstraintGroupNodeImpl;
class OdDbImpAssoc2dConstraintGroup;
//class OdDbAssoc2dConstraintGroupUtil;

typedef OdUInt32 OdConstraintGroupNodeId;

typedef OdArray < OdConstraintGroupNodeId, OdMemoryAllocator<OdConstraintGroupNodeId> > OdGroupNodeIdArray;

/** \details
  This class implements a node owned by a constraint group. This node is usually connected with 
  a number of other nodes for which connection is not directed between any two nodes.

  Library: Source code provided.
  <group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdConstraintGroupNode : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdConstraintGroupNode);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdConstraintGroupNode();

  /** \details
    Identifiers the node ID.
  */
  enum GroupNodeId
  {
    kNullGroupNodeId = 0
  };

  /** \details
    Returns the group node ID.
  */
  OdConstraintGroupNodeId nodeId() const;

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

protected:
  /** \details
    Constructor creates an instance of this class.
  */
  OdConstraintGroupNode();

  /*!DOM*/
  OdConstraintGroupNodeImpl* m_pImpl;

  /*!DOM*/
  friend class OdDbImpAssoc2dConstraintGroup;
  /*!DOM*/
  friend class OdDbAssoc2dConstraintGroup;
//  friend class OdDbAssoc2dConstraintGroupEvalHelper;
//  friend class OdDbAssoc2dConstaintGroupCloningHelper;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdConstraintGroupNode class.

  \sa
  <link smart_pointers, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdConstraintGroupNode> OdConstraintGroupNodePtr;

#include "TD_PackPop.h"

#endif
