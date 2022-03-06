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

#ifndef _ODDBMLINEIMPL_INCLUDED_
#define _ODDBMLINEIMPL_INCLUDED_

#include "DbMline.h"
#include "DbSystemInternals.h"
#include "DbEntityImpl.h"
#include "OdList.h"
#include "DbMlineStyle.h"
#include "DbMlineStyleImpl.h"

struct MLVertex
{
  OdGePoint3d       m_Point;
  OdGeVector3d      m_VertDir;
  OdGeVector3d      m_MiterDir;
  OdMLSegmentArray  m_Segments;
  // #12754/#12846 : store previous vertex params to apply recalculation
  OdSharedPtr<MLVertex> m_pPrevVertex;
  void storePrev(bool bIsPrevFalse = true)
  {
    if (!bIsPrevFalse || !isPrevStored())
    {
      MLVertex *pPrev = new MLVertex;
      *pPrev = *this;
      m_pPrevVertex = pPrev;
    }
  }
  void clearPrev() { m_pPrevVertex = NULL; }
  bool isPrevStored() const { return !m_pPrevVertex.isNull(); }
};

typedef OdArray<MLVertex> OdMLVertexArray;

class OdDbMlineImpl : public OdDbEntityImpl
{
  static OdDbMlineImpl* getImpl(const OdDbMline *pObj)
  { return (OdDbMlineImpl*)OdDbSystemInternals::getImpl(pObj);}

  double            m_dZeroOffset;

public:
  double            m_dScale;
  OdGePoint3d       m_basePoint;
  OdGeVector3d      m_vNormal;
  OdInt16           m_Flags;
  OdUInt8           m_Justification;
  OdUInt8           m_LinesInStyle;
  OdMLVertexArray   m_Vertexes;
  OdDbHardPointerId m_MLinestyleId;

public:
  OdDbMlineImpl() :
      m_vNormal(OdGeVector3d::kZAxis)
      , m_dScale(1.0)
      , m_Justification(Mline::kZero)
      , m_LinesInStyle(0)
      , m_Flags(0)
      , m_dZeroOffset(DBL_MAX)
      {}

  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format,
                                      OdDb::DwgVersion version);
  void audit (OdDbAuditInfo* pAuditInfo);
  void Recalculate();

private:
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  void SetMLStyle2StandardOrSomething();

  bool calculateProperties(OdDbMlineStyleImpl* MStyle);
  void calculateSegments(OdDbMlineStyleImpl* MStyle);
  void recalculateElement(OdUInt32 index);
//  void calculateOffset(OdDbMlineStyleImpl* MStyle);
  bool calculateElementProperties(OdUInt32 index, OdDbMlineStyleImpl* MStyle);
  void setStyleProperties(OdDbMlineStyleImpl* MStyle);

  void setStyleProperties();
  double zeroOffset();
  void invalidateZeroOffset();
  void invalidateVertices();
  bool isClosed()
  {
    return GETBIT(m_Flags, 2);
  }

  friend class OdDbMline;
};

#endif // _ODDBMLINEIMPL_INCLUDED_
