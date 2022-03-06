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




#ifndef OD_DBSPINDX_H
#define OD_DBSPINDX_H

#include "TD_PackPush.h"

#include "DbIndex.h"
#include "DbBlockIterator.h"

/** \details
    This class implements Spatial Index objects in an OdTvDbDatabase instance.

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbSpatialIndex : public OdTvDbIndex
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbSpatialIndex);

  OdTvDbSpatialIndex();

  OdTvDbFilteredBlockIteratorPtr newIterator(
    const OdTvDbFilter* pFilter) const;
  
  void rebuildFull(
    OdTvDbIndexUpdateData* pIdxData);
  
  OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

protected:

  void rebuildModified(
    OdTvDbBlockChangeIterator* iterator);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbSpatialIndex object pointers.
*/
typedef OdSmartPtr<OdTvDbSpatialIndex> OdTvDbSpatialIndexPtr;

class OdTvDbSpatialIndexIteratorImpl;
class OdTvDbSpatialFilter;


class OdTvDbSpatialIndexIterator;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbSpatialIndexIterator object pointers.
*/
typedef OdSmartPtr<OdTvDbSpatialIndexIterator> OdTvDbSpatialIndexIteratorPtr;

/** \details
    This class implements Iterator objects that traverse queries defined by OdTvDbSpatialFilter objects.
    \sa
    TD_Db
    
    \remarks
    This class is used by OcDbSpatialIndex.
     
    <group OdTvDb_Classes>
*/
class OdTvDbSpatialIndexIterator : public OdTvDbFilteredBlockIterator
{
protected:
  OdTvDbSpatialIndexIterator();
public:
  ODRX_DECLARE_MEMBERS(OdTvDbSpatialIndexIterator);

  static OdTvDbSpatialIndexIteratorPtr newIterator(
    const OdTvDbSpatialIndex* pIndex, 
    const OdTvDbSpatialFilter* pFilter);
};


#include "TD_PackPop.h"

#endif // OD_DBSPINDX_H
