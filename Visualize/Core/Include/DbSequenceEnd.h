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




#ifndef _OD_DB_SEQUENCE_END_
#define _OD_DB_SEQUENCE_END_

#include "TD_PackPush.h"

#include "DbEntity.h"
#include "DwgDeclareMembers.h"

/** \details
    This class represents SequenceEnd (Seqend) entities in an OdTvDbDatabase instance.  
    
    \remarks
    OdTvDbSequenceEnd entities are automatically created and handled by the Drawings for
    complex objects such as OdTvDb2dPolyline and OdTvDbBlockReference.
     
    Client applications may add extended data or extension dictionaries to these 
    entities, but should not create or delete them.

    These entities have no associated geometries.
 
    \remarks
    Do not derive from this class.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbSequenceEnd: public OdTvDbEntity
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbSequenceEnd);

  OdTvDbSequenceEnd();

  // for lisp && bag filer - outputs (-2,owner)
  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;
  // for vertices post-processing, when called from lisp
  OdResult dxfIn(
    OdTvDbDxfFiler* pFiler);
  /** \remarks
    Always returns eInvalidExtents.
  */
  virtual OdResult subGetGeomExtents(OdGeExtents3d& extents) const;
  /** \remarks
  Always returns eInvalidExtents.
  */
  virtual OdResult subErase(bool erasing);

  virtual OdResult subGetTransformedCopy(const OdGeMatrix3d& mat, OdTvDbEntityPtr& pCopy) const;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbSequenceEnd object pointers.
*/
typedef OdSmartPtr<OdTvDbSequenceEnd> OdTvDbSequenceEndPtr;

#include "TD_PackPop.h"

#endif
