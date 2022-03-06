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

#ifndef _DAI_DAIEXCEPTION_H_
#define _DAI_DAIEXCEPTION_H_

#include "OdPlatformSettings.h"
#include "daiBuildOptions.h"

#include "baseException.h"

#include "daiError/daiErrorId.h"

namespace OdDAI {

  /** \details
    This class represents exceptions used in SDAI module.
    \sa
    <link ifc_sdai_error_handling, Standard Data Access Interface Error Handling>
  */
  class DAI_EXPORT DaiException
    : public BaseException
  {
  public:
    /** \details
      Constructor for the DaiException class.
      
      \param minor            [in] Error identifier.
      \param errorDescription [in/out] Error description text, can be NULL. If NULL, receives description text of an error code.
      \param functionId       [in] Function in which the exception occurred.
    */
    DaiException(daiErrorId minor, const char* errorDescription, const char* functionId);
    
    /** \details
      Copy constructor for the DaiException class.
    */
    DaiException(const DaiException&);
    
    /** \details
      Destructor for the DaiException class.
    */
    ~DaiException();

    /** \details
      Assignment operator for the DaiException class.
      \returns
      Reference to this DaiException object.
    */
    DaiException& operator=(const DaiException&);
    
    /** \details
      Returns an error code of this exception.
      \returns
      Error code of this exception as daiErrorId type.
    */
    daiErrorId Minor() const;

    /** \details
      Returns an error code of this exception.
      \returns
      Error code of this exception as daiErrorId type.
    */
    virtual daiErrorId errorId() const;
    
    /** \details
      Returns description of an error code of this exception.
      \returns
      Const char pointer to a description of an Error code of this exception.
    */
    virtual const char* description() const;
    
    /** \details
      Returns the name of the function in which the exception occurred.
      \returns
      const char pointer to the name of the function in which the exception occurred.
    */
    virtual const char* functionId() const;

  private:
    daiErrorId m_minor;
    OdAnsiString  m_errorDescription;
    OdAnsiString  m_functionId;
  };

}

#endif
