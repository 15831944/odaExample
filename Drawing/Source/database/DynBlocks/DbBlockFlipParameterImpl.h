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

class OdDbBlockFlipParameterImpl : public OdDbConnectionPointsImpl<1, OdDbBlock2PtParameterImpl>
{
  friend class OdDbBlockFlipParameter;
protected:
  OdString m_sLabel;
  OdString m_sLabelDesc;
  OdString m_sNotFlippedState, m_sFlippedState;
  OdGePoint3d m_pLabelPosition;
  bool m_bCurrentState;
  bool m_bUpdatedState;
public:
  DECLARE_GET_IMPL(OdDbBlockFlipParameter);
  OdDbBlockFlipParameterImpl();
  virtual void getProperties( OdDbBlkParamPropertyDescriptorArray& ar )const;
  virtual OdResBufPtr getPropertyValue( const OdString&, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity )const;
  virtual bool setPropertyValue( const OdString&, const OdResBuf*, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity );
  virtual bool loadInstanceData(OdDbObject* pThis, const OdResBuf*& rb, bool bRequireEvaluate);
  virtual OdResBufPtr saveInstanceData(const OdDbObject* pThis)const;
  virtual bool hasInstanceData()const;
  virtual void getConnectionNames( OdStringArray& a ) const;
  virtual OdResBufPtr getConnectionValue(const OdString& name) const;
  virtual bool isModified() const { return m_bCurrentState != m_bUpdatedState; }
  bool evaluate(const OdDbEvalContext* ctx);
  void updateConnections();
};

#endif // _DbBlockFlipParameterImpl_h_Included_
