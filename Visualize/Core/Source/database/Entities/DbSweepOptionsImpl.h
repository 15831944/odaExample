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

#include "DbSweepOptions.h"

class DBENT_EXPORT OdTvDbSweepOptionsImpl
{
public:
  OdTvDbSweepOptionsImpl();
  double m_draftAngle;
  double m_startDraftDist;
  double m_endDraftDist;
  double m_twistAngle;
  double m_scaleFactor;
  double m_alignAngle;
  OdTvDbSweepOptions::AlignOption m_align;
  OdTvDbSweepOptions::MiterOption m_miterOption;
  bool m_alignStart;
  OdGePoint3d m_basePoint;
  bool m_bank;
  bool m_checkIntersections;
  OdGeVector3d m_twistRefVec;
  OdGeMatrix3d m_sweepEntityTransform;
  OdGeMatrix3d m_pathEntityTransform;
  bool m_bAlignStartFlag;
  bool m_bBankFlag;
  bool m_bBasePointSetFlag;
  bool m_bSweepTransformComputed;
  bool m_bPathTransformComputed;
  bool m_bSolid;
  void dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  static OdTvDbSweepOptionsImpl* getImpl(OdTvDbSweepOptions& opt)
  {
    return opt.m_pImpl;
  }
  static const OdTvDbSweepOptionsImpl* getImpl(const OdTvDbSweepOptions& opt)
  {
    return opt.m_pImpl;
  }
  static OdResult rdMatrix(OdTvDbDwgFiler* pFiler, OdGeMatrix3d& m)
  {
    for (int i = 0; i < 4; ++i)
    {
      for( int j = 0; j < 4; ++j)
      {
        m.entry[i][j] = pFiler->rdDouble();
      }
    }
    return eOk;
  }

  static void wrMatrix(OdTvDbDwgFiler* pFiler, const OdGeMatrix3d& m)
  {
    for (int i = 0; i < 4; ++i)
    {
      for( int j = 0; j < 4; ++j)
      {
        pFiler->wrDouble(m.entry[i][j]);
      }
    }
  }
  static OdResult rdMatrix(OdTvDbDxfFiler* pFiler, int gc, OdGeMatrix3d& m)
  {
    for (int i = 0; i < 4; ++i)
    {
      for( int j = 0; j < 4; ++j)
      {
        if(pFiler->nextItem() != gc)
          return eBadDxfSequence;
        m.entry[i][j] = pFiler->rdDouble();
      }
    }
    return eOk;
  }

  static void wrMatrix(OdTvDbDxfFiler* pFiler, int gc, const OdGeMatrix3d& m)
  {
    for (int i = 0; i < 4; ++i)
    {
      for( int j = 0; j < 4; ++j)
      {
        pFiler->wrDouble(gc, m.entry[i][j]);
      }
    }
  }
};
