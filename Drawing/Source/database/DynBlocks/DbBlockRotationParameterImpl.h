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

#ifndef _DbBlockRotationParameterImpl_h_Included_
#define _DbBlockRotationParameterImpl_h_Included_

#include "DbBlockRotationParameter.h"
#include "DbBlock2PtParameterImpl.h"

class OdDbBlockRotationParameterImpl : public OdDbBlock2PtParameterImpl
{
  friend class OdDbBlockRotationParameter;
protected:
  OdString m_sLabel;
  OdString m_sLabelDesc;
  OdStaticRxObject<OdDbBlockParamValueSet> m_Angle;
  OdGePoint3d m_pStartPoint;
  double m_dLabelOffset;
  OdGePoint3d m_pCurrentPoint; // instance data;
public:
  DECLARE_GET_IMPL(OdDbBlockRotationParameter);
  virtual void getProperties( OdDbBlkParamPropertyDescriptorArray& ar ) const ODRX_OVERRIDE;
  virtual OdResBufPtr getPropertyValue( const OdString&, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity ) const ODRX_OVERRIDE;
  virtual bool setPropertyValue(const OdString& name , const OdResBuf* rb, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity ) ODRX_OVERRIDE;
  virtual bool loadInstanceData(OdDbObject* pThis, const OdResBuf*& rb, bool bRequireEvaluate) ODRX_OVERRIDE;
  virtual bool hasInstanceData()const ODRX_OVERRIDE;
  virtual OdResBufPtr saveInstanceData(const OdDbObject* pThis) const ODRX_OVERRIDE;
  virtual OdResult transformBy( const OdGeMatrix3d& ) ODRX_OVERRIDE;
  virtual void updateConnections() ODRX_OVERRIDE;
  virtual bool evaluate(const OdDbEvalContext* ctx) ODRX_OVERRIDE;
  double definitionBaseAngle() const
  {
    OdGeVector3d v = m_pStartPoint - m_pPoint1;
    return v.angleTo(m_pPoint2 - m_pPoint1, normal());
  }

  OdDbBlockRotationParameterImpl()
  {
    m_dLabelOffset = 0.;
  }
};

#endif // _DbBlockRotationParameterImpl_h_Included_
