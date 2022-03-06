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

/************************************************
 *
 * Dimension variables definitions new in R15 dwg
 */

//      Type        Name    DXF     Default value    DXF groupcode in XDATA  Cpp type   Real type
VAR_DEF(Int16,      azin,   79,     (0),                  70,                OdInt16,      OdInt16)
VAR_DEF(Double,     altrnd, 148,    (0.0),                40,                double,       double)// I'm not sure about last field(George)
VAR_DEF(Int16,      adec,   179,    (0),                  70,                OdInt16,      OdInt16)
VAR_DEF(Int16,      frac,   276,    (0),                  70,                OdInt16,      OdInt16)
VAR_DEF(Int16,      lunit,  277,    (2),                  70,                OdInt16,      OdInt16)
VAR_DEF(Int16,      dsep,   278,    ('.'),                70,                OdInt16,      OdChar)
VAR_DEF(Int16,      tmove,  279,    (0),                  70,                OdInt16,      OdInt16)
VAR_DEF(Int16,      atfit,  289,    (3),                  70,                OdInt16,      OdInt16)
VAR_DEF(Handle,     ldrblkHandle,
                            341,    OdDbHandle(0),        340,               OdDbHandle,   OdDbHandle)
VAR_DEF(Handle,     blkHandle,
                            342,    OdDbHandle(0),        340,               OdDbHandle,   OdDbHandle)
VAR_DEF(Handle,     blk1Handle,
                            343,    OdDbHandle(0),        340,               OdDbHandle,   OdDbHandle)
VAR_DEF(Handle,     blk2Handle,
                            344,    OdDbHandle(0),        340,               OdDbHandle,   OdDbHandle)
VAR_DEF(Int16,      lwd,    371,    (OdDb::kLnWtByBlock), 70,                OdInt16,      OdDb::LineWeight)//(OdDb::kLnWtByBlock)
VAR_DEF(Int16,      lwe,    372,    (OdDb::kLnWtByBlock), 70,                OdInt16,      OdDb::LineWeight)//(OdDb::kLnWtByBlock)
