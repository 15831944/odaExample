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

#ifndef _DbBlockXYParameterImpl_h_Included_
#define _DbBlockXYParameterImpl_h_Included_

#include "DbBlockXYParameter.h"
#include "DbBlock2PtParameterImpl.h"

class OdTvDbBlockXYParameterImpl : public OdTvDbBlock2PtParameterImpl
{
  friend class OdTvDbBlockXYParameter;
protected:
  OdString m_sXLabel;
  OdString m_sXLabelDesc;
  double m_dXLabelOffset;
  OdString m_sYLabel;
  OdString m_sYLabelDesc;
  double m_dYLabelOffset;
  OdStaticRxObject<OdTvDbBlockParamValueSet> m_X, m_Y;
public:
  DECLARE_GET_IMPL(OdTvDbBlockXYParameter);

  OdTvDbBlockXYParameterImpl()
  {
    m_dYLabelOffset = 0.;
    m_dXLabelOffset = 0.;
  }

  virtual void getProperties( OdTvDbBlkParamPropertyDescriptorArray& ar ) const ODRX_OVERRIDE;
  virtual OdTvResBufPtr getPropertyValue( const OdString&, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity ) const ODRX_OVERRIDE;
  virtual bool setPropertyValue( const OdString& name, const OdTvResBuf* rb, const OdGeMatrix3d&) ODRX_OVERRIDE;
  virtual bool hasInstanceData() const ODRX_OVERRIDE;
  virtual bool evaluate(const OdTvDbEvalContext*) ODRX_OVERRIDE;
};

#endif // _DbBlockXYParameterImpl_h_Included_
