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

#ifndef _DAI_ERRORHANDLER_BASE_H_
#define _DAI_ERRORHANDLER_BASE_H_

#include "daiError/daiErrorId.h"
#include "SharedPtr.h"

namespace OdDAI {

  /** \details
    The base class for error handlers that can be manipulated with the Data Access Interface (DAI).
    \sa
    <link ifc_sdai_error_handling, Standard Data Access Interface Error Handling>
  */
  class daiErrorHandlerBase
  {
  public:
    /** \details
      Destructor for the daiErrorHandlerBase class.
    */
    virtual ~daiErrorHandlerBase() {}
    
    /** \details
      The () operator for the daiErrorHandlerBase class.
      
      \param minor              [in] Error code.
      \param errorDescription   [in] Error description in a human-readable form.
      \param functionId         [in] Pointer to a name of the function where an error is handled.
    */
    virtual void operator()(daiErrorId minor, const char* errorDescription, const char* functionId) = 0;
  };

  /** \details
    A data type that represents a smart pointer to an <link OdDAI__daiErrorHandlerBase, daiErrorHandlerBase> object.
  */
  typedef OdSharedPtr<daiErrorHandlerBase> daiErrorHandlerPtr;
}

#endif
