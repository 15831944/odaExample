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

#ifndef _DbBlockPolarParameterImpl_h_Included_
#define _DbBlockPolarParameterImpl_h_Included_

#include "DbBlockPolarParameter.h"
#include "DbBlock2PtParameterImpl.h"

class OdDbBlockPolarParameterImpl : public OdDbBlock2PtParameterImpl
{
  friend class OdDbBlockPolarParameter;
protected:
  OdString m_sLabel;
  OdString m_sLabelDesc;
  OdString m_sAngleLabel;
  OdString m_sAngleLabelDesc;
  double m_dLabelOffset;
  OdStaticRxObject<OdDbBlockParamValueSet> m_Distance;
  OdStaticRxObject<OdDbBlockParamValueSet> m_Angle;
  OdGePoint3d m_pCurrentPoint; // instance data
public:
  DECLARE_GET_IMPL(OdDbBlockPolarParameter);
  virtual void getProperties( OdDbBlkParamPropertyDescriptorArray& ar )const;
  virtual OdResBufPtr getPropertyValue( const OdString&, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity )const;
  virtual bool setPropertyValue(const OdString& name , const OdResBuf* rb, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity );
  virtual bool hasInstanceData()const; // has instance data loaded
  virtual bool loadInstanceData(OdDbObject* pThis, const OdResBuf*&, bool bRequireEvaluate); // loads instance data from xdata chain
  virtual OdResBufPtr saveInstanceData(const OdDbObject* pThis)const;
  bool evaluate(const OdDbEvalContext* ctx);
  OdResult transformBy( const OdGeMatrix3d& m );
  OdDbBlockPolarParameterImpl()
  {
    m_dLabelOffset = 0.;
  }
};

#endif // _DbBlockPolarParameterImpl_h_Included_
