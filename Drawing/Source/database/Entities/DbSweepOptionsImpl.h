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
#pragma once

#include "DbSweepOptions.h"


class DBENT_EXPORT OdDbSweepOptionsImpl
{
public:
  OdDbSweepOptionsImpl();
  double m_draftAngle;
  double m_startDraftDist;
  double m_endDraftDist;
  double m_twistAngle;
  double m_scaleFactor;
  double m_alignAngle;
  OdDbSweepOptions::AlignOption m_align;
  OdDbSweepOptions::MiterOption m_miterOption;
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
  void dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;
  static OdDbSweepOptionsImpl* getImpl(OdDbSweepOptions& opt)
  {
    return opt.m_pImpl;
  }
  static const OdDbSweepOptionsImpl* getImpl(const OdDbSweepOptions& opt)
  {
    return opt.m_pImpl;
  }
  static OdResult rdMatrix(OdDbDwgFiler* pFiler, OdGeMatrix3d& m)
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

  static void wrMatrix(OdDbDwgFiler* pFiler, const OdGeMatrix3d& m)
  {
    for (int i = 0; i < 4; ++i)
    {
      for( int j = 0; j < 4; ++j)
      {
        pFiler->wrDouble(m.entry[i][j]);
      }
    }
  }
  static OdResult rdMatrix(OdDbDxfFiler* pFiler, int gc, OdGeMatrix3d& m)
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

  static void wrMatrix(OdDbDxfFiler* pFiler, int gc, const OdGeMatrix3d& m)
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
