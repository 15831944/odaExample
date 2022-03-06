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

#ifndef _ODDBSPATIALINDEXIMPL_INCLUDED_
#define _ODDBSPATIALINDEXIMPL_INCLUDED_

#include "DbIndexImpl.h"
#include "OdBinaryData.h"
#include "DbSystemInternals.h"
#include "DbSpatialIndex.h"

class OdTvDbSpatialIndexImpl : public OdTvDbIndexImpl
{
  static OdTvDbSpatialIndexImpl* getImpl(const OdTvDbSpatialIndex *pObj)
  { return (OdTvDbSpatialIndexImpl*)OdTvDbSystemInternals::getImpl(pObj);}


public:
  OdTvDbObjectId      m_objectBeingIndexedId;
	OdBinaryData      m_BinaryData;
	OdSoftPtrIdArray  m_ids;
	OdBitBinaryData   m_BinaryData2;
	double            m_x1;
	double            m_x2;
	double            m_y1;
	double            m_y2;
	double            m_z1;
	double            m_z2;

  friend class OdTvDbSpatialIndex;
  friend class OdTvDbSpatialIndexIteratorImpl;
};

#endif // _ODDBSPATIALINDEXIMPL_INCLUDED_
