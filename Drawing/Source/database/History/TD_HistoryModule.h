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

#if !defined(_TD_HISTORYMODULE_INCLUDED_)
#define _TD_HISTORYMODULE_INCLUDED_

#include "RxModule.h"
#include "DbHistoryController.h"

struct TD_HistoryModuleInterface : OdRxModule
{
  virtual OdDbHistoryControllerPtr newController(OdDbDatabase* pDb) = 0;
};

class TD_HistoryModule : public TD_HistoryModuleInterface
{
  bool m_TfIOFactorySet;
protected:
  TD_HistoryModule();
  void initApp();
  void uninitApp();
public:
  virtual OdDbHistoryControllerPtr newController(OdDbDatabase* pDb) ODRX_OVERRIDE;
  ~TD_HistoryModule();
};



#endif // _TD_HISTORYMODULE_INCLUDED_
