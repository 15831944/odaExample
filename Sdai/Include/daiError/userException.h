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

#ifndef _DAI_USEREXCEPTION_H_
#define _DAI_USEREXCEPTION_H_

#include "OdPlatformSettings.h"
#include "daiBuildOptions.h"

#include "baseException.h"

namespace OdDAI {

  /** \details
    This class represents user exceptions used in SDAI module.
    \sa
    <link ifc_sdai_error_handling, Standard Data Access Interface Error Handling>
  */
  class DAI_EXPORT UserException
    : public BaseException
  {
  public:
    /** \details
      Constructor for the UserException class.
      
      \param minor            [in] Error identifier.
      \param errorDescription [in/out] Error description text, can be NULL. If NULL, receives description text of an error code.
      \param functionId       [in] Function in which the exception occurred.
    */
    UserException(daiErrorId minor = sdaiSY_ERR, const char* errorDescription = "Internal error", const char* functionId = "Unknown function name");

    /** \details
      Destructor for the UserException class.
    */
    ~UserException();
  };

}

#endif
