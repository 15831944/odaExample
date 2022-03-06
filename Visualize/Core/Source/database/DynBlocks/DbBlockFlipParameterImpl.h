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

#ifndef _DbBlockFlipParameterImpl_h_Included_
#define _DbBlockFlipParameterImpl_h_Included_

#include "DbBlockFlipParameter.h"
#include "DbBlock2PtParameterImpl.h"

class OdTvDbBlockFlipParameterImpl : public OdTvDbConnectionPointsImpl<1, OdTvDbBlock2PtParameterImpl>
{
  friend class OdTvDbBlockFlipParameter;
protected:
  OdString m_sLabel;
  OdString m_sLabelDesc;
  OdString m_sNotFlippedState, m_sFlippedState;
  OdGePoint3d m_pLabelPosition;
  bool m_bCurrentState;
  bool m_bUpdatedState;
public:
  DECLARE_GET_IMPL(OdTvDbBlockFlipParameter);
  OdTvDbBlockFlipParameterImpl();
  virtual void getProperties( OdTvDbBlkParamPropertyDescriptorArray& ar )const;
  virtual OdTvResBufPtr getPropertyValue( const OdString&, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity )const;
  virtual bool setPropertyValue( const OdString&, const OdTvResBuf*, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity );
  virtual bool loadInstanceData(OdTvDbObject* pThis, const OdTvResBuf*& rb, bool bRequireEvaluate);
  virtual OdTvResBufPtr saveInstanceData(const OdTvDbObject* pThis)const;
  virtual bool hasInstanceData()const;
  virtual void getConnectionNames( OdStringArray& a ) const;
  virtual OdTvResBufPtr getConnectionValue(const OdString& name) const;
  virtual bool isModified() const { return m_bCurrentState != m_bUpdatedState; }
  bool evaluate(const OdTvDbEvalContext* ctx);
  void updateConnections();
};

#endif // _DbBlockFlipParameterImpl_h_Included_
