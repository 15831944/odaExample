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

class OdTvDbBlockRotationParameterImpl : public OdTvDbBlock2PtParameterImpl
{
  friend class OdTvDbBlockRotationParameter;
protected:
  OdString m_sLabel;
  OdString m_sLabelDesc;
  OdStaticRxObject<OdTvDbBlockParamValueSet> m_Angle;
  OdGePoint3d m_pStartPoint;
  double m_dLabelOffset;
  OdGePoint3d m_pCurrentPoint; // instance data;
public:
  DECLARE_GET_IMPL(OdTvDbBlockRotationParameter);
  virtual void getProperties( OdTvDbBlkParamPropertyDescriptorArray& ar ) const ODRX_OVERRIDE;
  virtual OdTvResBufPtr getPropertyValue( const OdString&, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity ) const ODRX_OVERRIDE;
  virtual bool setPropertyValue(const OdString& name , const OdTvResBuf* rb, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity ) ODRX_OVERRIDE;
  virtual bool loadInstanceData(OdTvDbObject* pThis, const OdTvResBuf*& rb, bool bRequireEvaluate) ODRX_OVERRIDE;
  virtual bool hasInstanceData()const ODRX_OVERRIDE;
  virtual OdTvResBufPtr saveInstanceData(const OdTvDbObject* pThis) const ODRX_OVERRIDE;
  virtual OdResult transformBy( const OdGeMatrix3d& ) ODRX_OVERRIDE;
  virtual void updateConnections() ODRX_OVERRIDE;
  virtual bool evaluate(const OdTvDbEvalContext* ctx) ODRX_OVERRIDE;

  OdTvDbBlockRotationParameterImpl()
  {
    m_dLabelOffset = 0.;
  }
};

#endif // _DbBlockRotationParameterImpl_h_Included_
