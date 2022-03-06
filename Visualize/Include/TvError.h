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

#ifndef _ODTV_ERROR_H_INCLUDED_
#define _ODTV_ERROR_H_INCLUDED_

#include "Tv.h"

/** \details
  This is an interface class for an OdTvError object.

  \remarks
  This object is created for supporting exception handling (in catch expressions).
  \sa
  <link tv_working_with_base_classes_results_errors, Get Operation Results and Error Handling>
*/  
class ODTV_EXPORT OdTvError
{
public:
  
  /** \details
    Retrieves the current error code.
    
    \returns Returns the current error code represented with an <link OdTvResult, OdTvResult> value.
  */
  virtual OdTvResult code() const = 0;
    
    
  /** \details
    Retrieves the current description of this error object.
    \returns Returns a string that contains the description of the error.
    \remarks
    Returns a string containing the concatenation of
    all of the description strings in the Error stack.
      
    The default implementation of this function returns a string in the following format:
    Description n-1\n
    Previous error: Description n-2\n
    Previous error: Description n-3\n
    ...
    Previous error: Description 0\n
  */ 
  virtual OdString description() const = 0;
};

#endif //_ODTV_ERROR_H_INCLUDED_
