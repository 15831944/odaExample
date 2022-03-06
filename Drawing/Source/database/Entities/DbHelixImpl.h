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


#ifndef __OD_DB_HELIX_IMPL__
#define __OD_DB_HELIX_IMPL__

#include "DbHelix.h"
#include "DbSplineImpl.h"

class OdDbHelixImpl : public OdDbSplineImpl
{
  OdDb::DwgVersion         m_dwgVer;     // stored in dwg, with some God(AutoCAD) knows purpose
  OdDb::MaintReleaseVer    m_mrVer;      // so we must store it in database too

  OdGePoint3d              m_axisBasePoint; // dxf 10,  Axis base point
  OdGePoint3d              m_startPoint;    // dxf 11,  Start point
  OdGeVector3d             m_axis;          // dxf 12,  Axis vector
  double                   m_dRadius;       // dxf 40,  Radius
  double                   m_dTurns;        // dxf 41,  Number of turns
  double                   m_dTurnHeight;   // dxf 42,  Turn height
  OdDbHelix::ConstrainType m_constrain;     // dxf 280, Constrain type  
  enum Flags
  {
    kIsCCW = 1,                             // dxf 290, Handedness
    kGeometryPresent = 2                    // is not stored in DWG
  };
  OdUInt32                 m_flags;

  static OdDbHelixImpl* getImpl(const OdDbHelix *pObj)
  { return (OdDbHelixImpl*)OdDbSystemInternals::getImpl(pObj);}

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  OdResult dxfInFields(OdDbDxfFiler* pFiler);  
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  void updateNurbsData();
  static OdDbSplinePtr getAsSpline(const OdDbHelix* pHelix);
public:

  OdDbHelixImpl();

  friend class OdDbHelix;
  friend class OdDbSurfaceImpl;

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }

  void drawFrame(const OdDbSpline *pSpline, OdGiWorldDraw* pWd) const;

  void setBaseRadius(double dRadius);
};

#endif // __OD_DB_HELIX_IMPL__
