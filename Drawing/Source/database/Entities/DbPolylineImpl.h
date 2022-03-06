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

#ifndef _ODDBPOLYLINEIMPL_INCLUDED_
#define _ODDBPOLYLINEIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DbSystemInternals.h"
#include "DbPolyline.h"
#include "Ge/GePoint2dArray.h"

class GrDataDrawer;

class OdDbPolylineImpl : public OdDbEntityImpl, public OdDb2dEntityImpl
{
  static OdDbPolylineImpl* getImpl(const OdDbPolyline *pObj)
  { return (OdDbPolylineImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdGePoint2dArray     m_Points; // in OCS!!
  OdGeDoubleArray      m_Bulges;
  OdInt32Array         m_Identifiers;
  OdGePoint2dArray     m_Widths;
  double               m_dElevation;
  double               m_dConstWidth;

  bool                 m_bClosed;
  // PLINEGEN is the attribute that causes linetype generation to be patterned
  // across the entire polyline instead of done individually at each segment.
  bool                 m_bPLineGen;

  virtual double thickness() const {return m_dThickness;}
  virtual void setThickness(double val) { m_dThickness = val; }

  OdDbPolylineImpl();

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void audit (OdDbAuditInfo* pAuditInfo);

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  OdResult dwgInFields(OdDbDwgFiler* pFiler, bool bCheckCopmression);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
  void dwgOutFields(OdDbDwgFiler* pFiler, bool bCheckCopmression) const;

  bool hasBulges() const;
  bool hasVertexIdentifiers() const;
  bool hasWidth() const;

  OdResult dxfInFields(OdDbDxfFiler* pFiler);

  // Override OdDbEntityImpl
  //
  void createGrData(const OdDbEntity* pEnt, OdBinaryData& data, OdDb::DwgVersion ver);
  static OdResult convert(OdDbPolyline* pRes, const OdDb2dPolyline* pPline, bool bCopyGeomOnly);

protected:
  double getBulgeAt(unsigned ind) const;
  void setBulgeAt(unsigned ind, double bulge);
  void getWidthsAt(unsigned ind, double& start, double& end) const;
  void setWidthsAt(unsigned ind, double start, double end);
  OdInt32 getVertexIdentifierAt(unsigned ind) const;
  void setVertexIdentifierAt(unsigned ind, OdInt32 id);

private:
  void addVertexAt(unsigned int index,
                   const OdGePoint2d& pt,
                   double bulge,
                   double startWidth,
                   double endWidth,
                   OdInt32 vertexIdentifier);

  // The function adds missing vertices.
  // DbPolyline entry must have at least 2 vertices.
  // Acad always adjusts a pline which had no vertices or had only one vertex.
  inline void adjustVertices();

  friend class OdDbPolyline;
  friend void pline(GrDataDrawer*, OdGiWorldDraw*);
  friend class OdGrDataSaver;
  friend class OdDb2dPolylineImpl;
  friend class OdDbMPolygon;
};


//----------------------------------------------------------
//
// Inline implementation
//
//----------------------------------------------------------
inline void OdDbPolylineImpl::adjustVertices()
{
  unsigned pnts = m_Points.size();
  if (pnts < 2)
  {
    if (pnts == 0) addVertexAt(0, OdGePoint2d(), 0.0, 0.0, 0.0, 0);
    OdGePoint2d pt = m_Points[0];
    addVertexAt(1, pt, 0.0, 0.0, 0.0, 0);
  }
}

#endif // _ODDBPOLYLINEIMPL_INCLUDED_
