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

#ifndef _ODDB_CURVEIMPL_INCLUDED_
#define _ODDB_CURVEIMPL_INCLUDED_

#include "DbCurveImpl.h"
#include "EntityContainer.h"
#include "Gi/GiPolyline.h"

class OdDbPolyline;

class OdPolylineBaseImpl : public OdDbCurveImpl, public OdEntitySeqEndContainer
{
  const OdDbObjectImpl* dbObjectImpl() const { return this; }
  OdEntityContainer* entContainer() { return this; }
public:
  typedef enum
  {
    ODA_PLINE_CLOSED        = 1,
    ODA_PLINE_CURVEFIT      = 2,
    ODA_PLINE_SPLINEFIT     = 4,
    ODA_PLINE_3DPLINE       = 8,
    ODA_PLINE_3DMESH        = 16,
    ODA_PLINE_CLOSEDN       = 32,
    ODA_PLINE_POLYFACEMESH  = 64,
    ODA_PLINE_CONTINUELT    = 128
  } OdaPLineFlags;

	OdUInt16 m_PolyFlags;
	OdInt16  m_FitType;

public:
  OdPolylineBaseImpl();

  OdResult dxfIn(OdDbDxfFiler* pFiler);
  void audit (OdDbAuditInfo* pAuditInfo);

  virtual void recvPropagateModify(OdDbObject* pOwner, const OdDbObject* pSubObj);
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  TD_USING(OdDbCurveImpl::setLayer);
};


class DBENT_EXPORT OdGiPolylineImplForDbPolyline : public OdGiPolyline
{
  OdSmartPtr<OdDbPolyline> m_pLwBuf;
public:
  OdGiPolylineImplForDbPolyline();

  OdGiPolylineImplForDbPolyline(const OdDbPolyline* pLwBuf);

  OdGiPolylineImplForDbPolyline(OdDbPolyline* pLwBuf);

  void set(OdSmartPtr<OdDbPolyline> pLwBuf);

  OdRxObjectPtr clone() const;

  void addRef();
  void release();

  unsigned int numVerts() const;
  bool isClosed() const;
  OdGeVector3d normal() const;
  double thickness() const;
  double getConstantWidth() const;
  bool hasWidth() const;
  bool hasPlinegen() const;
  double elevation() const;
  OdGiPolyline::SegType segType(unsigned int index) const;
  void getLineSegAt(unsigned int index, OdGeLineSeg2d& ln) const;
  void getLineSegAt(unsigned int index, OdGeLineSeg3d& ln) const;
  void getArcSegAt(unsigned int index, OdGeCircArc2d& arc) const;
  void getArcSegAt(unsigned int index, OdGeCircArc3d& arc) const;
  void getPointAt(unsigned int index, OdGePoint2d& pt) const;
  void getPointAt(unsigned int index, OdGePoint3d& pt) const;
  double hasBulges() const;
  double getBulgeAt(unsigned int index) const;
  void getWidthsAt(unsigned int index, double& startWidth, double& endWidth) const;

  OdRxObjectPtr getDbPolyline() const;
};


#endif // _ODDBCURVEIMPL_INCLUDED_
