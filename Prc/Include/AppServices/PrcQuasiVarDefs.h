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

#define SVARS_FUNC_MODIFIER virtual

//for binary compatibility
#undef SVARS_FUNC_MODIFIER
#define SVARS_FUNC_MODIFIER

/**
  <title TESSDRAWMODE>
  <toctitle TESSDRAWMODE>
   
  <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Runtime
   <b>Versions</b>        all
  </table>
   
  TESSDRAWMODE controls wich entity has more priority: OdPrcBaseTessData or OdPrcBody.
   
  <table>
   <b>Value</b>   <b>Description</b>
   0              OdPrcBaseTessData has more priority then OdPrcBody.
   1              OdPrcBody has more priority then OdPrcBaseTessData.
  </table>
   
  <table>
   <b>Access Methods</b>
   OdPrcFile::getTESSDRAWMODE()
   OdPrcFile::setTESSDRAWMODE()
  </table>    

<group TP_SysVars_T>
  */
QVAR_DEF(OdUInt16, TESSDRAWMODE, (0), (0), ValidateRange(0,1))
QVAR_DEF(OdUInt16, BEHAVIORBITFIELDMODE, (0), (0), ValidateRange(0,1))

#undef SVARS_FUNC_MODIFIER

