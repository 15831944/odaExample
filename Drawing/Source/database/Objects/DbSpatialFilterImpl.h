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

#ifndef _ODDBSPATIALFILTERIMPL_INCLUDED_
#define _ODDBSPATIALFILTERIMPL_INCLUDED_

#include "DbFilterImpl.h"
#include "Ge/GePoint2dArray.h"
#include "DbSystemInternals.h"
#include "DbSpatialFilter.h"
#include "Ge/GeMatrix3d.h"
#include "Ge/GeExtents3d.h"
#include "Gi/GiGeometry.h"
#include "Gi/GiClipBoundary.h"

class OdGeBoundBlock2d;

class OdDbSpatialFilterImpl : public OdDbFilterImpl, public OdGiClipBoundary
{
  static OdDbSpatialFilterImpl* getImpl(const OdDbSpatialFilter *pObj)
  { return (OdDbSpatialFilterImpl*)OdDbSystemInternals::getImpl(pObj);}

  mutable OdGeExtents3d m_clipExtents;
  mutable bool          m_bClipExtValid;

  const OdGeExtents3d& clipExtents() const;

  bool                  m_bHasPerspectiveCamera;
  OdGePoint3d           m_ptFromPointForPerspectiveCamera;

  bool                  m_bIsInvertedClip;
  mutable OdGePoint2dArray m_invertedClip;

  const OdGePoint2dArray& invertedClip() const;
public:
  bool              m_bEnabled;
  // bool              m_bSkipCrossing;

public:
  OdDbSpatialFilterImpl();

  static void getMatrices(const OdDbSpatialFilter& filter,
                          OdGeMatrix3d& inverseBlockMatrix,
                          OdGeMatrix3d& clipBoundMatrix)
  {
    filter.assertReadEnabled();
    OdDbSpatialFilterImpl * pImpl = OdDbSpatialFilterImpl::getImpl(&filter);
    inverseBlockMatrix = pImpl->m_xInverseBlockRefXForm;
    clipBoundMatrix = pImpl->m_xToClipSpace;
  }

  static void setMatrices(OdDbSpatialFilter& filter,
                          OdGeMatrix3d& inverseBlockMatrix,
                          OdGeMatrix3d& clipBoundMatrix)
  {
    filter.assertWriteEnabled();
    OdDbSpatialFilterImpl * pImpl = OdDbSpatialFilterImpl::getImpl(&filter);
    pImpl->m_xInverseBlockRefXForm = inverseBlockMatrix;
    pImpl->m_xToClipSpace = clipBoundMatrix;
  }

  // AMark : #6241 : m_xToClipSpace can be singular. We should return identity matrix in this case.
  const OdGeMatrix3d &getSafeClipMatrix() const
  {
    if (m_xToClipSpace.isSingular(1e-300))
      return OdGeMatrix3d::kIdentity;
    return m_xToClipSpace;
  }
  const OdGeMatrix3d &getSafeInvBlockMatrix() const
  {
    if (m_xInverseBlockRefXForm.isSingular(1e-300))
      return OdGeMatrix3d::kIdentity;
    return m_xInverseBlockRefXForm;
  }

private:
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  friend class OdDbSpatialFilter;
  friend class OdDbSpatialIndexIteratorImpl;
};

#endif // _ODDBSPATIALFILTERIMPL_INCLUDED_
