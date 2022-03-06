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

#ifndef _ODDBMINSERTBLOCKIMPL_INCLUDED_
#define _ODDBMINSERTBLOCKIMPL_INCLUDED_

#include "DbMInsertBlock.h"
#include "DbBlockReferenceImpl.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeScale3d.h"

class OdTvDbMInsertBlockImpl : public OdTvDbBlockReferenceImpl
{
  static OdTvDbMInsertBlockImpl* getImpl(const OdTvDbMInsertBlock *pObj)
  { return (OdTvDbMInsertBlockImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  double  m_dRowDist;    
  double  m_dColDist;
  OdInt16 m_NumRows;
  OdInt16 m_NumCols;

public:
  OdTvDbMInsertBlockImpl();

  void setNumRows(OdUInt16 n);
  void setNumCols(OdUInt16 n);
  void setRowSpacing(double sp);
  void setColSpacing(double sp);

  void audit(OdTvDbAuditInfo* pAuditInfo);

  OdGeScale3d scaleFactorsItl(const OdTvDbMInsertBlock *pObj);

  OdResult getTransformedCopy(const OdTvDbBlockReference* pObj, const OdGeMatrix3d& mat, OdTvDbEntityPtr& pCopy) const;


  friend class OdTvDbMInsertBlock;
  friend class OdTvDwgR12FileLoader;
};

#endif // _ODDBMINSERTBLOCKIMPL_INCLUDED_
