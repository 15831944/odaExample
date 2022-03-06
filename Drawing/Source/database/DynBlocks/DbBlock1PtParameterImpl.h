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

#ifndef _DbBlock1PtParameterImpl_h_Included_
#define _DbBlock1PtParameterImpl_h_Included_

#include "DbBlock1PtParameter.h"
#include "DbBlockParameterImpl.h"

class OdDbBlock1PtParameterImpl : public OdDbBlockParameterImpl
{
  friend class OdDbBlock1PtParameter;
protected:
  OdGePoint3d m_pBasePoint;
  OdDbEvalNodeId m_nGripId;
  OdDbBlockParameterImpl::PropertyInfo m_pProperties[2];
  OdGePoint3d m_pCurrentPoint; // instance data
  OdGePoint3d m_pUpdatedPoint; // instance data
public:
  DECLARE_GET_IMPL(OdDbBlock1PtParameter);
  virtual bool loadInstanceData(OdDbObject* pThis, const OdResBuf*& rb, bool bRequireEvaluate);
  virtual OdResBufPtr saveInstanceData(const OdDbObject* pThis)const;
  virtual OdResBufPtr getConnectionValue (const OdString& name) const;
  virtual void getConnectionNames(OdStringArray&) const;
  virtual OdResult transformBy( const OdGeMatrix3d& );
  void getStretchPoints( OdGePoint3dArray& a )const;
  void moveStretchPointsAt( const OdIntArray& ia, const OdGeVector3d& v );
  void updateConnections();
  OdDbBlockParameter::ParameterComponent getComponentForGrip( OdDbEvalNodeId id);
  OdDbBlock1PtParameterImpl() : m_nGripId(0) {}
  virtual bool isModified() const { return m_pUpdatedPoint != m_pCurrentPoint; }
  OdDbBlockGripPtr getAssociatedGrip(OdDb::OpenMode mode);
};

#endif // _DbBlock1PtParameterImpl_h_Included_
