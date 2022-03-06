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

#ifndef _DAI_TCKIND_H_
#define _DAI_TCKIND_H_

/** \details 
Defines kinds of an <link OdTypeCode, OdTypeCode> object. 
\sa 
<link OdTypeCode, OdTypeCode Class Documentation>
<link ifc_overview_data_types, IFC Data Types>
*/
enum OdTCKind
{
  /** A NULL value.*/
  tkNull = 0,
  
  /** The long data type that corresponds to the C++ int type. It means that an attribute of the tkLong data type stores a C++ integer value.*/  
  tkLong,
  
  /** The double data type that corresponds to the C++ double.*/
  tkDouble,
  
  /** The Boolean data type that corresponds to the <link OdDAI::Boolean, Boolean> class.*/
  tkBoolean,
  
  /** The Logical data type that corresponds to the <link  OdDAI::Logical,  Logical> class.*/
  tkLogical,
  
  /** The Binary data type. It is not implemented yet.*/
  tkBinary,
  
  /** The data type of the <link OdAny, OdAny> class.*/
  tkAny,
  
  /** The data type of the <link OdTypeCode, OdTypeCode> class.*/
  tkTypeCode,
  
  /** The String data type that corresponds to the <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> class.*/
  tkString,
  
  /** The object identifier data type that corresponds to the <link OdDAIObjectId, OdDAIObjectId> class.*/
  tkObjectId,
  
  /** The Select data type that corresponds to the <link The OdDAI::Select, Select> class.*/
  tkSelect,
  
  /** The enumeration data type that corresponds to the <link OdDAI::Enum, Enum> class.*/
  tkEnum,
  
  /** The Sequence data type that corresponds to <link OdDAI::Aggr, Aggr> class and derived classes*/
  tkSequence,
  
  /** The Union data type. It is not implemented yet.*/
  tkUnion,
  
  /** The Octet data type. It is not implemented yet.*/
  tkOctet,
};

#endif // _DAI_TCKIND_H_
