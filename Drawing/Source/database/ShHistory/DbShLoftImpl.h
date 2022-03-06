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

#ifndef _OD_DB_SHLOFT_IMPL_
#define _OD_DB_SHLOFT_IMPL_

#include "ShHistory/DbShLoft.h"
#include "DbShPrimitiveImpl.h"
#include "DbLoftOptions.h"


class OdDbShLoftImpl : public OdDbShPrimitiveImpl
{
  bool                   m_bSolid;

  OdArray<OdDbEntityPtr> m_pCrossSectCurves;
  OdArray<OdDbEntityPtr> m_pGuideCurves;
  OdDbEntityPtr          m_pPath;
  OdDbLoftOptions        m_loftOptions;

  friend class OdDbShLoft;
public:
  OdDbShLoftImpl();

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler);

  void setCrossSectCurves(const OdArray<OdDbEntityPtr>& pCrossSectCurves);
  void setGuideCurves(const OdArray<OdDbEntityPtr>& pGuideCurves);
  void setPath(const OdDbEntityPtr& Path);

  //DbLoftProfileData * crossSection(int)
  //int endContinuity(void)
  //double endMagnitude(void)
  //void getCrossSections(OdArray< DbLoftProfileData *, OdMemoryAllocator<DbLoftProfileData *> > &)
  //void getGuides(OdArray<DbLoftProfileData *, OdMemoryAllocator<DbLoftProfileData *> > &)  
  //DbLoftProfileData * guide(int)
  //bool hasContinuity(bool,bool)
  //DbLoftProfileData * path(void)
  //OdResult setEndContinuity(int)
  //OdResult setEndMagnitude(double)
  //OdResult setProfiles(OdArray<DbLoftProfileData *, OdMemoryAllocator<DbLoftProfileData *> > &,AcArray<DbLoftProfileData *,OdMemoryAllocator<DbLoftProfileData *> > &,DbLoftProfileData *)
  //OdResult setStartContinuity(int)
  //OdResult setStartMagnitude(double)
  //int startContinuity()
  //double startMagnitude()

  DECLARE_GET_IMPL(OdDbShLoft);
private:
  virtual OdResult transformBy(const OdGeMatrix3d& mat);
  virtual bool evaluate(OdDbEvalContext const* ctx);
};

#endif
