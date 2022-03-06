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

#ifndef _DAI_SPF_FILER_ERROR_PROCESSOR_H_
#define _DAI_SPF_FILER_ERROR_PROCESSOR_H_

#include "OdaCommon.h"
#include "daiBaseType.h"
#include "daiFilerErrorHandlers.h"

#include "RxObject.h"
#include "RxObjectImpl.h"


/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  class Model;

  /** \details
  A base class that should be used during read file error.
  */
  class DAI_EXPORT FilerErrorProcessorPE
    : public OdRxObject
  {
  public:
    ODRX_DECLARE_MEMBERS(FilerErrorProcessorPE);
    
    /** \details
    Provides a handler to process unknown entity name state
    \returns Returns a handler to process error. If the function 
    returns nullptr the handling does not run and exception occurred
    */
    virtual WrongEntityErrorHandler* UnknownTypeEntityAction() { return nullptr; }

    /** \details
    Provides a handler to process none instantiable entity state
    \returns Returns a handler to process error. If the function 
    returns nullptr the handling does not run and exception occurred
    */
    virtual WrongEntityErrorHandler* NonInstantiableEntityAction() { return nullptr; }

    /** \details
    Provides a handler to process corrupted start parameters state
    \returns Returns a handler to process error. If the function 
    returns nullptr the handling does not run and exception occurred
    */
    virtual CorruptedParametersStartErrorHandler* CorruptedStartParametersAction() { return nullptr; }

    /** \details
    Provides a handler to process duplicate handle state
    \returns Returns a handler to process error. If the function 
    returns nullptr the handling does not run and exception occurred
    */
    virtual DuplicateHandleHandler* DuplicateHandleAction() { return nullptr; }

    /** \details
    Provides a handler to process syntax error state
    \returns Returns a handler to process error. If the function 
    returns nullptr the handling does not run and exception occurred
    */
    virtual SyntaxErrorHandler* SyntaxErrorAction() { return nullptr; }

    /** \details
    This function should be called before the file reading
    \param model [in] A model read to
    */
    virtual void onStartReading(Model*  model) = 0;

    /** \details
    This function should be called after the file reading
    \param model [in] A model read to
    */
    virtual void onFinishReading(Model* model, OdResult executionResult) = 0;
  };

  
  typedef OdSmartPtr<FilerErrorProcessorPE> FilerErrorProcessorPEPtr;
}

#endif // _DAI_SPF_FILER_ERROR_PROCESSOR_H_
