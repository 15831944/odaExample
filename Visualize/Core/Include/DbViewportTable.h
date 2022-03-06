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




#ifndef _ODDBVIEWPORTTABLE_INCLUDED
#define _ODDBVIEWPORTTABLE_INCLUDED

#include "TD_PackPush.h"

#include "DbAbstractViewTable.h"
#include "DbObject.h"
#include "DwgDeclareMembers.h"

class OdTvDbViewportTableRecord;

/** \details
    This class implements the ViewportTable, which represents tiled viewports in an OdTvDbDatabase instance.

    \sa
    TD_Db

    \remarks
    Do not derive from this class.
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbViewportTable: public OdTvDbAbstractViewTable
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbViewportTable);

  /** \details
    Client applications typically will not use this constructor, insofar as 
    this class is a base class.
  */
  OdTvDbViewportTable();

  /** \details
    Makes the specified viewport the active viewport of this ViewportTable object.

    \param viewportId [in]  Object ID of the active viewport.      
  */
  void SetActiveViewport(
    OdTvDbObjectId viewportId);

  /** \details
    Returns the active viewport of this ViewportTable object.
  */
  OdTvDbObjectId getActiveViewportId() const;

  /** \details
    Deletes the specified configuration from this ViewportTable object.
    
    \param configName [in]  Configuration name to delete.
  */
  void DeleteConfiguration(
    const OdString& configName);

  OdTvDbObjectId add(
    OdTvDbSymbolTableRecord* pRecord);

  OdResult dxfIn(
    OdTvDbDxfFiler* pFiler);

 /* OdResult subGetClassID(
    void* pClsid) const;*/

  void subClose();
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbTextStyleTable object pointers.
*/
typedef OdSmartPtr<OdTvDbViewportTable> OdTvDbViewportTablePtr;

#include "TD_PackPop.h"

#endif // _ODDBVIEWPORTTABLE_INCLUDED

