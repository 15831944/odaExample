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

#ifndef _DAI_ERROREVENT_H_
#define _DAI_ERROREVENT_H_

#include "OdPlatformSettings.h"
#include "daiBuildOptions.h"
#include "daiError/daiErrorId.h"
#include "daiBaseEvent.h"

#include "OdString.h"

namespace OdDAI 
{
  class ErrorEvent;
  /** \details
    A data type that represents a smart pointer to an <link OdDAI__ErrorEvent, ErrorEvent> object.
  */
  typedef OdSmartPtr<ErrorEvent> ErrorEventPtr;

  /** \details
    The class represents error events that can be manipulated with the Data Access Interface (DAI).
    \sa
    <link ifc_sdai_error_handling, Standard Data Access Interface Error Handling>
  */
  class DAI_EXPORT ErrorEvent 
    : public Event
  {
  public:
    ODRX_DECLARE_MEMBERS(ErrorEvent);

    /** \details
      Default constructor for the ErrorEvent class. By default an error comes from the underlying system.
    */
    ErrorEvent();
    
    /** \details
      Destructor for the ErrorEvent class.
    */
    virtual ~ErrorEvent();

    /** \details
      Copy constructor for the ErrorEvent class.
      
      \param other            [in] Error event to copy.
      \remarks
      Inaccessible.
    */
    ErrorEvent(const ErrorEvent& other) = delete;
    
    /** \details
      Assignment operator for the ErrorEvent class.
      
      \param other            [in] Error event to assign.
      \remarks
      Inaccessible.
    */
    ErrorEvent& operator= (const ErrorEvent& other) = delete;

    /** \details
    Retrieves the current value of an attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns Returns the current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    */
    OdRxValue getAttr(const char* attrName) const override;

    /** \details
   Retrieves whether the attribute value is set or is unset.
   \param explicitAttrName [in] An ANSI string that contains the attribute name.
   \returns Returns true if the attribute has a value; otherwise, the method returns false (it means that the attribute value is not set).
   */
    bool testAttr(const char* attrName) const override;

    /** \details
      Retrieves error code of the event.
   
      \returns 
      Error code as daiErrorId value.
    */
    daiErrorId error() const;
    
    /** \details
      Retrieves description of an error event.

      \returns
      Const char pointer to description text of an error event.
    */
    const char* description() const;

    /** \details
      Creates an error event with the specified function, error code and description.
      
      \param errorId      [in] Error code.
      \param description  [in] Error event description in a human-readable form.
      \param functionName [in] Pointer to a name of the function for the event.

      \returns 
      Smart pointer to the created event.
    */
    static ErrorEventPtr makeErrorEvent(daiErrorId errorId, const char* description, const char* functionName);

  private:
    daiErrorId    m_error;
    OdAnsiString  m_description;
  };


#define MAKE_ERROR_EVENT(errorId, description) ErrorEvent::makeErrorEvent(errorId, description, TD_FUNC)
  

}

#endif
