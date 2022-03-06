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

#ifndef _DAI_SPF_FILER_ERROR_HANDLERS_H_
#define _DAI_SPF_FILER_ERROR_HANDLERS_H_

#include "OdaCommon.h"
#include "daiBaseType.h"

#include "RxObject.h"
#include "RxObjectImpl.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  An interface that provides functionality for working with read data stream in readonly mode.
  */
  class IBufferDataProvider
  {
  public:

    /** \details
    virtual destructor
    */
    virtual ~IBufferDataProvider() {}
    
    /** \details
    Reads current char
    \returns Returns a char from the current cursor
    */
    virtual char  getCurrentChar() const = 0;

    /** \details
    Move cursor to the next position
    \returns Returns EoF state. False if current position in not at EoF, otherwise false.
    */
    virtual bool  goToNextChar() = 0;
  };

}

namespace OdDAI
{
  /** \details
  Defines the type or error handling
  */
  enum class UnknownTypeEntityWorkOrder
  {
    /** Fails and stop file reading. */
    failAndStop,

    /** Skips wrong data. */
    skipWrongData,

    /** Maps wrong name to normal. */
    mapName,

    /** Creates application instance mapped to wrong name. */
    mapInstance,

    /** Creates application instance mapped to wrong name and try to parse its params. */
    mapInstanceWithParam,
  };

  /** \details
  A interface that handles wrong entity state. Handles the abnormal situation when
  we read name of the entity but can not create entity instance for it. 
  */
  class WrongEntityErrorHandler
  {
  public:

    /** \details
    Provides the type or error handling
    \returns Returns the type or error handling
    */
    virtual UnknownTypeEntityWorkOrder getWorkOrder() = 0;

    /** \details
    Skips abnormal data. Case when getWorkOrder() returns skipWrongData.
    \param dataBuffer [in] buffer to read and skip data. 
    \returns Returns true if the file reading should be continued, 
    and false otherwise.
    */
    virtual bool skipData(IBufferDataProvider* dataBuffer) = 0;

    /** \details
    Gets abnormal entity name from read buffer and provides normal entity name. 
    Case when getWorkOrder() returns mapName.
    \param entityTypeName [in] abnormal entity name from read buffer.
    \returns Returns mapped normal name.
    */
    virtual const char* handleError(const char* entityTypeName) = 0;

    /** \details
    Creates an application instance by abnormal entity name which was get from read buffer.+
    Case when getWorkOrder() returns mapInstance.
    \param model [in] current model.
    \param entityTypeName [in] abnormal entity name from read buffer.
    \returns Returns created instance.
    */
    virtual ApplicationInstancePtr  handleError(OdDAI::Model* model, const char* entityTypeName) = 0;

    /** \details
    Creates an application instance by abnormal entity name which was get from read buffer. 
    And try to parse parameters and set it to created application instance.
    Case when getWorkOrder() returns mapInstanceWithParam.
    \param model [in] current model.
    \param entityTypeName [in] abnormal entity name from read buffer.
    \param paramReader [in] buffer for params parsing.
    \returns Returns created instance with settled from read buffer attributes.
    */
    virtual ApplicationInstancePtr  handleError(OdDAI::Model* model, const char* entityTypeName, IBufferDataProvider* paramReader) = 0;
  };
}

namespace OdDAI
{
  /** \details
  Defines the type or error handling
  */
  enum class CorruptedParametersStartWorkOrder
  {
    /** Fails and stop file reading. */
    failAndStop,
    
    /** Skips wrong data. */
    skipWrongData,
    
    /** Try to parse manualy wrong data. */
    parseWrongData
  };

  /** \details
  The interface that should handle situation when the file reader determine and create entity instance 
  but can not find parameters start of this entity instance.
  */
  class CorruptedParametersStartErrorHandler
  {
  public:
    /** \details
    Provides the type or error handling
    \returns Returns the type or error handling
    */
    virtual CorruptedParametersStartWorkOrder getWorkOrder() = 0;

    /** \details
    Skips abnormal data. Case when getWorkOrder() returns skipWrongData.
    \param wrongDataReader [in] buffer to read and skip data. 
    \returns Returns true if the file reading should be continued, 
    and false otherwise.
    */
    virtual bool skipData(IBufferDataProvider* wrongDataReader) = 0;

    /** \details
    Provides buffer to parse parameters block manualy.
    Case when getWorkOrder() returns parseWrongData.
    \param model [in] the filling model .
    \param alreadyCreatedInstance [in] created instance.
    \param wrongDataReader [in] read buffer for manual parameters pasing.
    \returns Returns true if the file reading should be continued,
    and false otherwise.
    */
    virtual bool handleError(OdDAI::Model*  model, ApplicationInstancePtr alreadyCreatedInstance, IBufferDataProvider* wrongDataReader) = 0;
  };
}


namespace OdDAI
{
  /** \details
  Defines the type or error handling
  */
  enum class DuplicateHandleWorkOrder
  {
    /** Fails and stop file reading. */
    failAndStop,

    /** Try to process duplicate instance. */
    processInstance,
    
    /** Skips entity instance w/o handling and continue reading. */
    skipWrongData,
  };

  /** \details
  A interface helps reader to solve the problem when the handlers are 
  not unique during the stream reading 
  */
  class DuplicateHandleHandler
  {
  public:

    /** \details
    Provides the type or error handling
    \returns Returns the type or error handling
    */
    virtual DuplicateHandleWorkOrder getWorkOrder() = 0;

    /** \details
    Try to process situation with dupliccxate instance.
    Case when getWorkOrder() returns processInstance.
    \param model [in] the filling model .
    \param handle [in] not unique handle.
    \param alreadyAdded [in] the instance already added.
    \param instanceToAdd [in] the new instance with the same handle.
    \returns Returns true if the file reading should be continued,
    and false otherwise.
    */
    virtual bool handleError(OdDAI::Model* model, OdDbHandle& handle, OdRxObjectPtr& alreadyAdded, OdDAI::ApplicationInstancePtr& instanceToAdd) = 0;
  };
}

namespace OdDAI
{
  /** \details
  Defines the type or error handling
  */
  enum class SyntaxErrorWorkOrder
  {
    /** Fails and stop file reading. */
    failAndStop,
    
    /** Skips wrong data. */
    skipWrongData,
  };

  /** \details
  This interface can be used by stream reader when global syntax error accured.
  */
  class SyntaxErrorHandler
  {
  public:
    /** \details
    Provides the type or error handling
    \returns Returns the type or error handling
    */
    virtual SyntaxErrorWorkOrder getWorkOrder() = 0;

    /** \details
    Skips abnormal data. Case when getWorkOrder() returns skipWrongData.
    \param dataBuffer [in] buffer to read and skip data. 
    \returns Returns true if the file reading should be continued, 
    and false otherwise.
    */
    virtual bool skipData(IBufferDataProvider* dataBuffer) = 0;
  };
}

#endif // _DAI_SPF_FILER_ERROR_PROCESSOR_H_
