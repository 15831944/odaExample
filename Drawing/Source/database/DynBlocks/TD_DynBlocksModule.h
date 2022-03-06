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

// TD_DynBlocks.h : main header file for the TD_DYNBLOCKS module
//

#if !defined(AFX_CODA1_14SOURCEDATABASEDYNBLOCKSDD_DYNBLOCKSMODULE_H__806CD5E6_F134_475A_91AD_BA4EC2BDE7E7__INCLUDED_)
#define AFX_CODA1_14SOURCEDATABASEDYNBLOCKSDD_DYNBLOCKSMODULE_H__806CD5E6_F134_475A_91AD_BA4EC2BDE7E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RxModule.h"

/////////////////////////////////////////////////////////////////////////////
// TD_DynBlocksModule
// See TD_DynBlocks.cpp for the implementation of this class
//

class TD_DynBlocksModule : public OdRxModule
{
protected:
	TD_DynBlocksModule();

  void initApp();

  void uninitApp();

public:
	~TD_DynBlocksModule();
};

typedef OdSmartPtr<TD_DynBlocksModule> TD_DynBlocksModulePtr;


#endif // !defined(AFX_CODA1_14SOURCEDATABASEDYNBLOCKSDD_DYNBLOCKSMODULE_H__806CD5E6_F134_475A_91AD_BA4EC2BDE7E7__INCLUDED_)
