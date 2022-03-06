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

#ifndef _DbBlockParameterImpl_h_Included_
#define _DbBlockParameterImpl_h_Included_

#include "DbBlockParameter.h"
#include "DbBlockElementImpl.h"

class OdDbBlockParameterImpl : public OdDbBlockElementImpl
{
  friend class OdDbBlockParameter;
protected:
  bool m_bShowProperties;
  bool m_bChainActions;
public:
  struct PropertyInfo
  {
    OdInt16 m_nMessages;
    OdArray<OdDbConnectionPoint> m_pConnections;

    PropertyInfo() : m_nMessages(0) { }

    void dwgIn(OdDbDwgFiler* pFiler);
    void dwgOut(OdDbDwgFiler* pFiler);
    void dxfIn(OdDbDxfFiler* pFiler,int n1, int n2, int n3);
    void dxfOut(OdDbDxfFiler* pFiler,int n1, int n2, int n3);
  };

  OdDbBlockParameterImpl() : m_bShowProperties(true), m_bChainActions(false)
  {
  }
  DECLARE_GET_IMPL(OdDbBlockParameter);
  virtual void getProperties( OdDbBlkParamPropertyDescriptorArray& ar )const;
  virtual OdResBufPtr getPropertyValue( const OdString&, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity )const;
  virtual bool setPropertyValue( const OdString&, const OdResBuf*, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity );
  virtual OdString getPropertyConnectionName( const OdString& )const;
  static void makeResBufArrayFromDoubleArray( const OdGeDoubleArray&, OdResBufArray& res );
  virtual OdDbBlockParameter::ParameterComponent getComponentForGrip( OdDbEvalNodeId id) = 0;
  virtual OdDbEvalNodeId addGrip( OdDbBlockParameter::ParameterComponent ){ ODA_FAIL_ONCE(); return (OdDbEvalNodeId)-1; }
  virtual bool historyRequired() const { return true; }
};

#endif // _DbBlockParameterImpl_h_Included_
