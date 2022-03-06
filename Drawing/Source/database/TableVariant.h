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




#if !defined(_ODTABLEVARIANT_H_INCLUDED_)
#define _ODTABLEVARIANT_H_INCLUDED_

#include "TD_PackPush.h"

#include "RxVariant.h"
#include "CmColor.h"
#include "DbObjectId.h"

class OdFormatData
{
public:
  OdFormatData() : m_dataType(0)
    , m_unitType(0){}

    OdInt32     m_dataType;
    OdInt32     m_unitType;
    OdString    m_strFormat;
};

const int nOdTableVariantDataSize = sizeof(OdCmColor);

/** Description:

    {group:Other_Classes}
*/
class TOOLKIT_EXPORT OdTableVariant : public OdVariant
{
protected:
  OdUInt8 m_data2[nOdTableVariantDataSize - nOdVariantDataSize];

  void setVarType(int newType, int& type, void* data);
public:
  static const OdVariant::TypeFactory* typeFactory(int type);
  typedef enum
  {
    kCmColor    = OdVariant::kNextType,
    kObjectId,
    kFormatData,
    kNextType
  } Type;

  OdTableVariant();
  OdTableVariant(const OdVariant& val);
  OdTableVariant(const OdTableVariant& val);
  OdTableVariant& operator =(const OdTableVariant& val);
  //OdTableVariant& operator =(const OdVariant& val);

  OdTableVariant(const OdCmColor& val);
  OdTableVariant(const OdDbObjectId& val);
  OdTableVariant(const OdFormatData& val);

  ~OdTableVariant();

  const OdCmColor&        getCmColor()        const;
  const OdDbObjectId&     getObjectId()       const;
  const OdFormatData&     getFormatData()     const;

  /*
  OdCmColor*              getCmColorPtr()     const;
  const OdCmColorArray&   getCmColorArray()   const;
  OdCmColorArray&         asCmColorArray();
  OdCmColorArray*         getStringArrayPtr() const;
  */

  OdTableVariant& setCmColor(const OdCmColor& val);
  OdTableVariant& setObjectId(const OdDbObjectId& val);
  OdTableVariant& setFormatData(const OdFormatData& val);
  /*
  OdTableVariant& setCmColorPtr(OdCmColor* pVal);
  OdTableVariant& setCmColorArray(const OdCmColorArray& array);
  OdTableVariant& setCmColorArrayPtr(OdCmColorArray* pArray);
  */
};

inline
OdTableVariant::OdTableVariant(const OdCmColor& val)
{
  setCmColor(val);
}

inline
OdTableVariant::OdTableVariant(const OdDbObjectId& val)
{
  setObjectId(val);
}

inline
OdTableVariant::OdTableVariant(const OdFormatData& val)
{
  setFormatData(val);
}


#include "TD_PackPop.h"

#endif //_OdTableVariant_H_INCLUDED_


