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




#ifndef OD_DBCELLSTYLEMAP_H
#define OD_DBCELLSTYLEMAP_H

#include "TD_PackPush.h"

#include "DbObject.h"

/** Description:
    This class represents *CellStyleMap* objects in an OdTvDbDatabase instance.

    Library:
    Db

*/
class TOOLKIT_EXPORT OdTvDbCellStyleMap : public OdTvDbObject
{
public:

  ODDB_DECLARE_MEMBERS(OdTvDbCellStyleMap);

  OdTvDbCellStyleMap();

  /** Description:
  Used to read in an OdTvDbCellStyleMap's data from a DWG file.

  Arguments:
  filer (I) Actual filer used to read in an OdTvDbCellStyleMap's data from a DWG file.

  Remarks:
  Used to read in an OdTvDbCellStyleMap's data from a DWG file.
  */
  virtual OdResult dwgInFields (OdTvDbDwgFiler* filer);


  /** Description:
  Used to persist the OdTvDbCellStyleMap's data to a DWG file.

  Argumets:
  filer (I) Actual filer used to persist the OdTvDbCellStyleMap's data to a DWG file.

  Remarks:
  Used to persist the OdTvDbCellStyleMap's data to a DWG file.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* filer) const;

  /** Description:
  Used to read in an OdTvDbCellStyleMap's data from a DXF file.

  Aruments:
  filer (I) Actual filer used to read in an OdTvDbCellStyleMap's data from a DXF file.

  Remarks:
  Used to read in an OdTvDbCellStyleMap's data from a DXF file.
  */
  virtual OdResult dxfInFields (OdTvDbDxfFiler* filer);

  /** Description:
  Used to persist the OdTvDbCellStyleMap's data to a DXF file.

  Arguments:
  filer (I) Actual filer used to persist the OdTvDbCellStyleMap's data to a DXF file.

  Remarks:
  Used to persist the OdTvDbCellStyleMap's data to a DXF file.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* filer) const;

};
typedef OdSmartPtr<OdTvDbCellStyleMap> OdTvDbCellStyleMapPtr;

#include "TD_PackPop.h"

#endif // OD_DBCELLSTYLEMAP_H
