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

#ifndef __TNW_OBJ_TRANS_DYNAMIC_H__
#define __TNW_OBJ_TRANS_DYNAMIC_H__

#include "NwObjTransform.h"
#include "Ge/GeMatrix3d.h"

class NWDBEXPORT OdNwObjTransDynamic : public OdNwObjTransform
{
  ODRX_DECLARE_MEMBERS(OdNwObjTransDynamic);
  
public:
  OdNwObjTransDynamic();

public:
  virtual ~OdNwObjTransDynamic();

public:
  void setTransform(const OdGeMatrix3d& val);
  virtual OdGeMatrix3d getTransform() const override;

  void setTransformTypes(const OdUInt32 types);
  OdUInt32 getTransformTypes() const;

public:
  bool isIdentity() const;
  bool isRotation() const;
  bool isScale() const;
  bool isShift() const;
  bool isLinear() const;
  bool isTranslation() const;
  bool isFull() const;
  bool isAffine() const;

  void setIdentity();
  void setAsRotation();
  void setAsScale();
  void setAsShift();
  void setAsLinear();
  void setAsTranslation();
  void setAsFull();
  void setAsAffine();

protected:
  OdGeMatrix3d m_transform;
  OdUInt32     m_transformTypes;
};

typedef OdSmartPtr<OdNwObjTransDynamic> OdNwObjTransDynamicPtr;

#endif //__TNW_OBJ_TRANS_DYNAMIC_H__
