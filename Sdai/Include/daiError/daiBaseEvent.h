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

#ifndef _DAI_BASEEVENT_H_
#define _DAI_BASEEVENT_H_

#include "OdPlatformSettings.h"
#include "daiSessionInstance.h"
#include "daiBuildOptions.h"

#include "SharedPtr.h"
#include "OdString.h"
#include "OdTimeStamp.h"

namespace OdDAI {

  class Session;

  class Event;
  /** \details
    A data type that represents a smart pointer to an <link OdDAI__Event, Event> object.
  */
  typedef OdSmartPtr<Event> EventPtr;

  /** \details
    The base class for events that can be manipulated with the Data Access Interface (DAI).
    \sa
    <link ifc_sdai_error_handling, Standard Data Access Interface Error Handling>
  */
  class DAI_EXPORT Event
    : public SessionInstance
  {
  public:
    ODRX_DECLARE_MEMBERS(Event);

    /** \details
      Default constructor for the Event class. Creates an event at the workstation date in local time.
    */
    Event();
    
    /** \details
      Destructor for the Event class.
    */
    virtual ~Event();

    /** \details
      Copy constructor for the Event class.
      
      \param other            [in] Event to copy.
      \remarks
      Inaccessible.
    */
    Event(const Event& other) = delete;
    
    /** \details
      Assignment operator for the Event class.
      
      \param other            [in] Event to assign.
      \remarks
      Inaccessible.
    */
    Event& operator= (const Event& other) = delete;

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
      Retrieves a name of the function for the event.

      \returns 
      const char pointer to the name of the function.
    */
    const char* functionId() const;
    
    /** \details
      Retrieves event time.

      \returns 
      Event time as OdTimeStamp class.
    */
    const OdTimeStamp& time() const;

    /** \details
      Creates an event with the specified function.
      
      \param functionName [in] Pointer to a name of the function for the event.

      \returns 
      Smart pointer to the created event.
    */
    static EventPtr makeEvent(const char* functionName);

  protected:
    void setFunctionId(const OdAnsiString& functionId);

  private:
    OdTimeStamp   m_time;
    OdAnsiString  m_functionId;

  };

  #define MAKE_EVENT() Event::makeEvent(TD_FUNC)

}


#endif
