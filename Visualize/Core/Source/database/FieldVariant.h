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




#if !defined(_ODFIELDVARIANT_H_INCLUDED_)
#define _ODFIELDVARIANT_H_INCLUDED_

#include "TD_PackPush.h"

#include "RxVariant.h"
// #include "CmColor.h"
#include "DbObjectId.h"
#include "Ge/GePoint3d.h"
#include "Ge/GePoint2d.h"
#include "ResBuf.h"
#include "OdBinaryData.h"

const int nOdFieldVariantDataSize = 32;

/** Description:

    {group:Other_Classes}
*/
class DBENT_EXPORT OdFieldVariant : public OdVariant
{
protected:
  OdUInt8 m_data2[nOdFieldVariantDataSize - nOdVariantDataSize];

  void setVarType(int newType, int& type, void* data);
public:
  static const OdVariant::TypeFactory* typeFactory(int type);
  typedef enum
  {
    kObjectId = OdVariant::kNextType,
    kPoint,
    k3dPoint,
    kBuffer,
    kNextType
  } Type;

  OdFieldVariant();
  OdFieldVariant(const OdVariant& val);
  OdFieldVariant(const OdFieldVariant& val);
  OdFieldVariant& operator =(const OdFieldVariant& val);

  OdFieldVariant(const OdTvDbObjectId& val);
  OdFieldVariant(const OdGePoint3d& val);
  OdFieldVariant(const OdGePoint2d& val);
  OdFieldVariant(const OdTvResBuf& val);
  OdFieldVariant(const OdBinaryData& val);

  //OdFieldVariant& operator =(const OdVariant& val);

  ~OdFieldVariant();

  const OdTvDbObjectId&     getObjectId()      const;
  const OdGePoint3d&      getPoint3d()       const;
  const OdGePoint2d&      getPoint2d()       const;
  const OdBinaryData&     getBinaryData()    const;


  OdFieldVariant& setObjectId(const OdTvDbObjectId& val);
  OdFieldVariant& setPoint3d(const OdGePoint3d& val);
  OdFieldVariant& setPoint2d(const OdGePoint2d& val);
  OdFieldVariant& setBinaryData(const OdBinaryData& val);
};

inline
OdFieldVariant::OdFieldVariant(const OdTvDbObjectId& val)
{
  setObjectId(val);
}

#include "TD_PackPop.h"

#endif //_ODFIELDVARIANT_H_INCLUDED_


