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

#ifndef _DbBlockRepresentationData_h_Included_
#define _DbBlockRepresentationData_h_Included_

#include "DbEvalGraph.h"

/** \details

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockRepresentationData : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbBlockRepresentationData);
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  OdTvDbBlockRepresentationData();
  virtual void setBlock( const OdTvDbObjectId& );
};

#endif // _DbBlockRepresentationData_h_Included_
