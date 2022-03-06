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

#ifndef RASTER_EXPORT_CMD_H_
#define RASTER_EXPORT_CMD_H_

#include "Ed/EdCommandStack.h"

class OdEdUserIO;

/** \details
  <group OdExport_Classes> 
*/
namespace TD_RASTER_EXPORT {

/** \details
  This class implements the BMPOUT command. 
*/
class _bmpout_cmd : public OdEdCommand
{
  virtual ODCOLORREF getBackgroundColor(OdEdUserIO* pIO);

public:
  const OdString groupName() const;
  const OdString globalName() const;
  void execute(OdEdCommandContext* pCmdCtx);
};

/** \details
  This class implements the BMPOUT background command. 
*/
class _bmpoutbg_cmd : public _bmpout_cmd
{
  virtual ODCOLORREF getBackgroundColor(OdEdUserIO* pIO);
public:
  const OdString groupName() const;
  const OdString globalName() const;
};
}
#endif // RASTER_EXPORT_CMD_H_

