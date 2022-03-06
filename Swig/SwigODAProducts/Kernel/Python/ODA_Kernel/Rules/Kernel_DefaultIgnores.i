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

%include "Base/IgnoreListBase_Kernel.i"

%ignore *::rxInit;
%ignore *::rxUninit;
// ignore those methods excluding OdRxClass
%rename("%s") OdRxClass::rxInit;
%rename("%s") OdRxClass::rxUninit;

%ignore *::g_pDesc;
//%ignore *::addRef;
//%ignore *::release;
//%ignore *::numRefs;
%ignore OdArrayBuffer;
%ignore OdRefCounter;
%ignore OdRxObjectPtr;
%ignore *::constructor;
%ignore *::setConstructor;
%ignore OdRxObject::x;
%ignore OdRxObject::comparedTo;
%ignore OdRxObject::isEqualTo;

%feature("nodirector") OdRxObject::x;
%feature("nodirector") OdRxObject::addRef;
%feature("nodirector") OdRxObject::release;

%ignore OdGeInterval::operator >;
%ignore OdGeInterval::operator <;
%ignore OdGeInterval::operator >=;
%ignore OdGeInterval::operator <=;
%ignore operator >(double,const OdGeInterval&);
%ignore operator <(double,const OdGeInterval&);

%ignore OdGsBaseVectorizeViewDef::displayNode;
%ignore OdGsBaseVectorizeViewDef::displaySubnode;

%ignore ::ddTypeLibReg;
%ignore ::ddTypeLibUnreg;

%ignore OdRxValueType;

%ignore OdRxValue::toString(OdRxValueType::StringFormat format = OdRxValueType::kStringFormatGlobal) const throw();

%ignore OdDbGripData::inputPointFunc;
%ignore OdDbGripData::setInputPointFunc;
%ignore OdDbGripData::hoverDimensionFunc;
%ignore OdDbGripData::setHoverDimensionFunc;
%ignore OdDbGripData::hotGripDimensionFunc;
%ignore OdDbGripData::setHotGripDimensionFunc;

%ignore OdRxMember::type;
%ignore OdRxValue::type;
%ignore OdRxValue::OdRxValue(const OdRxValueType& type, const OdRxValue& value) throw();
%ignore OdGsBaseVectorizeViewDef;
%ignore OdGsBaseVectorizeViewMT;
%ignore OdGsBaseMaterialViewMT;
%ignore OdGiMetafile::bitsData(OdUInt8* pBytes);
%ignore OdGsStateBranch;
