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

#ifndef _DbBlockPointParameterImpl_h_Included_
#define _DbBlockPointParameterImpl_h_Included_

#include "DbBlockPointParameter.h"
#include "DbBlock1PtParameterImpl.h"

class OdTvDbBlockPointParameterImpl : public OdTvDbBlock1PtParameterImpl
{
  friend class OdTvDbBlockPointParameter;
protected:
  OdString m_sLabel;
  OdString m_sDescription;
  OdGePoint3d m_pLabelPosition;
public:
  virtual void getProperties( OdTvDbBlkParamPropertyDescriptorArray& ar )const;
  virtual bool setPropertyValue( const OdString& name, const OdTvResBuf* rb, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity );
  virtual OdTvResBufPtr getPropertyValue( const OdString&, const OdGeMatrix3d& = OdGeMatrix3d::kIdentity )const;
  virtual bool hasInstanceData()const; // has instance data loaded
  bool evaluate(const OdTvDbEvalContext*);
  DECLARE_GET_IMPL(OdTvDbBlockPointParameter);
};

#endif // _DbBlockPointParameterImpl_h_Included_
