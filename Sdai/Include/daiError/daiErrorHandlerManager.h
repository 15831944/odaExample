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


#ifndef _DAI_CATCH_H_
#define _DAI_CATCH_H_

#include "OdaCommon.h"
#include "OdPlatformSettings.h"
#include "daiBuildOptions.h"

#define STL_USING_STACK
#define STL_USING_VECTOR
#define STL_USING_ALGORITHM
#include "OdaSTL.h"

#include "OdError.h"
#include "daiError/daiErrorId.h"
#include "daiError/daiErrorHandlerBase.h"

namespace OdDAI {

#if defined(_MSC_VER)
#pragma warning(push) 
#pragma warning(disable:4150)
#endif

  class BaseException;

  /** \details
    This class represents an error handler manager that can be manipulated with the Data Access Interface (DAI).
    Usage of the class:
    <pre>
    try
    {
    }
    catch(const someYourException& )
    {
      // here you should place code to catch your own exceptions or maybe a standard exception.
    }
    catch(...)
    {
      daiErrorHandlerManager::catchFunction();
    }
      // Insert this part of code to places where you want use a standard exceptions handling.
    </pre>
    
    \sa
    <link ifc_sdai_error_handling, Standard Data Access Interface Error Handling>
  */
  class DAI_EXPORT daiErrorHandlerManager
  {
  public:
    /** \details
      A catch function for an exception. See the class description for more information.
    */
    static void catchFunction();
    
    /** \details
      Logs a given error.
      
      \param minor              [in] Error code.
      \param errorDescription   [in] Error description in a human-readable form.
      \param functionId         [in] Pointer to a name of the function where an error is handled.
    */
    static void log(daiErrorId minor, const char* errorDescription = 0, const char* functionId = 0);

    /** \details
      Queries the last error from the error stack.
      This error is popped from the error stack after it's queried.
      \returns
      Error code as daiErrorId value.
    */
    static daiErrorId errorQuery();
    
    /** \details
      Adds an error handler to the collection of error handlers.
      
      \param handlerToAdd       [in] Smart pointer to an error handler to add.
      \returns
      true if successfully pushed to a collection of error handlers, false otherwise.
    */
    static bool addHandler(const daiErrorHandlerPtr& handlerToAdd);
    
    /** \details
      Removes an error handler from the collection of error handlers.
      
      \param handlerToDelete       [in] Smart pointer to an error handler to remove.
      \returns
      true if successfully deleted from a collection of error handlers, false otherwise.
    */
    static bool removeHandler(const daiErrorHandlerPtr& handlerToDelete);

  protected:
    void processOdError(const OdError& odError);
    void processUnknown();

    void processError(daiErrorId minor, const char* errorDescription = 0, const char* functionId = 0);
    static daiErrorHandlerManager& instance();

  private:
    daiErrorHandlerManager();
    ~daiErrorHandlerManager();

  private:
    class ExceptionDataProvider;

    friend class Session;
    void resetSessionHandler(const daiErrorHandlerPtr& eventManagerHandler);

    daiErrorHandlerPtr              m_sessionHandler;
    
    std::vector<daiErrorHandlerPtr> m_handlersCollection;
    OdMutex                         m_mutexHandlers;

    std::stack<daiErrorId>          m_errorStateCollection;
    OdMutex                         m_mutexErrorState;
  };

#if defined(_MSC_VER)
#pragma warning(pop) 
#endif
}
#endif
