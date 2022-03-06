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

#ifndef _DWFUBASE_INCLUDED_
#define _DWFUBASE_INCLUDED_

namespace DWFCore
{
  class DWFInputStream;
};

class DwfUBase
{
protected:
  virtual OdResult loadDwfXStream(DWFCore::DWFInputStream& /*stream*/) { return eOk; };
  virtual OdResult loadDwf6Stream(DWFCore::DWFInputStream& /*stream*/) { return eOk; };
  virtual OdResult loadDwf55Stream(DWFCore::DWFInputStream& /*stream*/) { return eOk; };

  DwfUBase() {}
public:

  virtual OdResult proceedDwf(OdString ActiveFileName, class OdDbBaseHostAppServices* pBaseSrv = NULL);
  virtual OdResult proceedDwf(class OdStreamBuf* pStream, class OdDbBaseHostAppServices* pBaseSrv = NULL);

  virtual ~DwfUBase() {}
};

#endif // _DWFUBASE_INCLUDED_
