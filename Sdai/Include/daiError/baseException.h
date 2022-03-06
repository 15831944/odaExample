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

#ifndef _DAI_BASEEXCEPTION_H_
#define _DAI_BASEEXCEPTION_H_

#include "OdaCommon.h"
#include "OdPlatformSettings.h"
#include "daiBuildOptions.h"

#include "daiError/daiErrorId.h"

#include "DebugStuff.h"
#include "OdError.h"
#include "OdResult.h"

namespace OdDAI {

  /** \details
    This is the base class for exceptions used in SDAI.
    \sa
    <link ifc_sdai_error_handling, Standard Data Access Interface Error Handling>
  */
  class DAI_EXPORT BaseException 
    : public OdError
  {
  public:
    /** \details
      Constructor for the BaseException class.
      
      \param minor            [in] Error identifier.
      \param errorDescription [in/out] Error description text, can be NULL. If NULL, receives description text of an error code in a human-readable form.
      \param functionId       [in] Function in which the exception occurred.
    */
    BaseException(daiErrorId minor, const char* errorDescription, const char* functionId);
    
    /** \details
      Copy constructor for the BaseException class.
    */
    BaseException(const BaseException&);
    
    /** \details
      Destructor for the BaseException class.
    */
    virtual ~BaseException();

    /** \details
      Assignment operator for the BaseException class.
    */
    BaseException& operator=(const BaseException&);

    /** \details
      Returns the error identifier of the exception.
      \returns
      Error identifier of the exception as daiErrorId type.
    */
    virtual daiErrorId errorId() const = 0;
    
    /** \details
      Returns the error description text of the exception.
      \returns
      const char pointer to the error description text.
    */
    virtual const char* description() const = 0;
    
    /** \details
      Returns the name of the function in which the exception occurred.
      \returns
      const char pointer to the name of the function in which the exception occurred.
    */
    virtual const char* functionId() const = 0;

  protected:
    BaseException();
  };

}

#endif
