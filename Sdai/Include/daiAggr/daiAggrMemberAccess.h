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

#ifndef _DAI_AGGR_MEMBER_ACCESS_H
#define _DAI_AGGR_MEMBER_ACCESS_H

#include "OdArray.h"

namespace OdDAI
{
#define _AGGR_RETURN_PTR
#ifdef _AGGR_RETURN_PTR

  template<class TType>
  inline TType* _getCurrentMemberTyped(OdArray<TType>* internalArray, unsigned int index)
  {
    return (internalArray->begin() + index);
  }

  template<class TType>
  inline OdSmartPtr<TType> _getCurrentMemberTyped(OdArray< OdSmartPtr<TType> > * internalArray, unsigned int index)
  {
    return *(internalArray->begin() + index);
  }

  inline OdDAIObjectId _getCurrentMemberTyped(OdArray<OdDAIObjectId> * internalArray, unsigned int index)
  {
    return *(internalArray->begin() + index);
  }

  inline int _getCurrentMemberTyped(OdArray<int> * internalArray, unsigned int index)
  {
    return *(internalArray->begin() + index);
  }

  inline double _getCurrentMemberTyped(OdArray<double> * internalArray, unsigned int index)
  {
    return *(internalArray->begin() + index);
  }

  inline OdAnsiString _getCurrentMemberTyped(OdArray<OdAnsiString> * internalArray, unsigned int index)
  {
    return *(internalArray->begin() + index);
  }

  inline OdDAI::Aggr* _getCurrentMemberTyped(OdArray<OdDAI::Aggr*> * internalArray, unsigned int index)
  {
    return *(internalArray->begin() + index);
  }

  inline OdDAI::Entity* _getCurrentMemberTyped(OdArray<OdDAI::Entity*> * internalArray, unsigned int index)
  {
    return *(internalArray->begin() + index);
  }

  class OdDAIObjectSDAI;
  inline OdDAI::OdDAIObjectSDAI* _getCurrentMemberTyped(OdArray<OdDAI::OdDAIObjectSDAI*> * internalArray, unsigned int index)
  {
    return *(internalArray->begin() + index);
  }

#endif // _AGGR_RETURN_PTR 
}


#endif // _DAI_AGGR_MEMBER_ACCESS_H
