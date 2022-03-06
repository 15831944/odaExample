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

#ifndef _DbBlock2PtParameterImpl_h_Included_
#define _DbBlock2PtParameterImpl_h_Included_

#include "DbBlock2PtParameter.h"
#include "DbBlockParameterImpl.h"

class OdTvDbBlock2PtParameterImpl : public OdTvDbBlockParameterImpl
{
  friend class OdTvDbBlock2PtParameter;
protected:
  OdGePoint3d m_pPoint1;
  OdGePoint3d m_pPoint2;
  OdTvDbEvalNodeId m_pGripNodes[4];
  OdTvDbBlockParameterImpl::PropertyInfo m_pProperties[4];
  OdInt16 m_nBasePoint; // 0 = start point, 1 = mid point
  OdGePoint3d m_pCurrentPoint1, m_pCurrentPoint2; // instance data
  OdGePoint3d m_pUpdatedPoint1, m_pUpdatedPoint2; // instance data
  OdGeVector3d m_Normal; // instance data
  virtual bool loadInstanceData(OdTvDbObject* pThis, const OdTvResBuf*&, bool bRequireEvaluate); // loads instance data from xdata chain
  virtual OdTvResBufPtr saveInstanceData(const OdTvDbObject* pThis)const;
  virtual OdTvResBufPtr getConnectionValue (const OdString& name) const;
  virtual void getConnectionNames(OdStringArray&) const;
  virtual OdResult transformBy( const OdGeMatrix3d& );
  virtual void getStretchPoints( OdGePoint3dArray& )const;
  virtual void moveStretchPointsAt( const OdIntArray &, const OdGeVector3d &);
  virtual OdTvDbBlockParameter::ParameterComponent getComponentForGrip( OdTvDbEvalNodeId id);
public:
  OdTvDbBlock2PtParameter::ParameterBaseLocation baseLocation() const { return (OdTvDbBlock2PtParameter::ParameterBaseLocation) m_nBasePoint; }
  OdGeVector3d normal() const { return m_Normal; }

  OdGePoint3d basePoint() const{ return m_pCurrentPoint1; }
  OdGePoint3d endPoint()const { return m_pCurrentPoint2; }
  double distance() const { return m_pCurrentPoint1.distanceTo(m_pCurrentPoint2); }
  double angle() const { return OdGeVector3d::kXAxis.angleTo(m_pCurrentPoint2 - m_pCurrentPoint1,m_Normal); }

  OdGePoint3d definitionBasePoint() const { return m_pPoint1; }
  OdGePoint3d definitionEndPoint() const { return m_pPoint2; }
  double definitionDistance() const { return m_pPoint1.distanceTo(m_pPoint2); }
  double definitionAngle() const { return OdGeVector3d::kXAxis.angleTo(m_pPoint2-m_pPoint1,m_Normal); }

  OdGePoint3d updatedBasePoint()const { return m_pUpdatedPoint1; }
  OdGePoint3d updatedEndPoint()const { return m_pUpdatedPoint2; }
  double updatedDistance() const { return m_pUpdatedPoint1.distanceTo(m_pUpdatedPoint2); }
  double updatedAngle() const { return OdGeVector3d::kXAxis.angleTo(m_pUpdatedPoint2-m_pUpdatedPoint1,m_Normal); }

  void setBaseLocation(OdTvDbBlock2PtParameter::ParameterBaseLocation l){ m_nBasePoint = (OdInt16)l;}
  void setBasePoint( const OdGePoint3d& p ) { m_pCurrentPoint1 = p; }
  void setEndPoint(const OdGePoint3d& p) { m_pCurrentPoint2 = p; }
  void setDefinitionBasePoint( const OdGePoint3d& p ){ m_pPoint1 = p; }
  void setDefinitionEndPoint( const OdGePoint3d& p ){ m_pPoint2 = p; }
  void setUpdatedBasePoint(const OdGePoint3d& p ){ m_pUpdatedPoint1 = p; }
  void setUpdatedEndPoint(const OdGePoint3d& p ){ m_pUpdatedPoint2 = p; }
  
  void updateConnections();
  virtual bool isModified() const { return m_pUpdatedPoint1 != m_pCurrentPoint1 || m_pUpdatedPoint2 != m_pCurrentPoint2; }

  OdTvDbBlock2PtParameterImpl();
  DECLARE_GET_IMPL(OdTvDbBlock2PtParameter);
};

#endif // _DbBlock2PtParameterImpl_h_Included_
