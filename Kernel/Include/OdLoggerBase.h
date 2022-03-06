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

#ifndef __OD_LOGGER_BASE__
#define __OD_LOGGER_BASE__

#include "OdaCommon.h"

/** \details
  This abstract class for rendering process of device logging.
  Corresponding C++ library: TD_Gs
  <group OdGs_Classes>
*/
class GS_TOOLKIT_EXPORT OdLoggerBase
{
public:
  //Simple logging

  /** \details
    Log message.

    \param msg [in] Message string.
  */
  virtual void logMessage(const OdString& msg) = 0;

  /** \details
  Log warning.

  \param wrn [in] Warning string.
  */
  virtual void logWarning(const OdString& wrn) = 0;

  /** \details
  Log error.

  \param err [in] Error string.
  */
  virtual void logError(const OdString& err) = 0;
};


#endif // __OD_LOGGER_BASE__
