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

#ifndef _DAI_SESSION_H
#define _DAI_SESSION_H

#include "daiBuildOptions.h"
#include "daiSessionInstance.h"
#include "daiError/daiErrorId.h"
#include "daiError/daiErrorEvent.h"

#include "daiAggr/daiList.h"

#define STL_USING_SET
#include "OdaSTL.h"

//DOM-IGNORE-BEGIN
DAI_EXPORT bool oddaiCloseCurrentSession();
//DOM-IGNORE-END

namespace OdDAI {

#if defined(_MSC_VER)
#pragma warning(push) 
#pragma warning(disable:4150)
#endif
  /** \details
    Class should used as custom error event list flusher. 
  */
  class IEventCollector
  {
  public:

    /** \details
    virtual destructor
    */
    virtual ~IEventCollector() {}

    /** \details
    Should be called when starting event recording.
    */
    virtual void onStartEventRecording() = 0;

    /** \details
    Should be called when the event recording is end.
    */
    virtual void onStopEventRecording() = 0;

    /** \details
     Put error data to error event list.
    \param functionID [in] function name.
    \param error [in] error id.
    \param descpt [in] error description.
   */
    virtual void logEvent(const char* functionID, daiErrorId error, const char* descpt) = 0;

    /** \details
    Puts error event data to error event list.
    \param eventToRecord [in] event to put.
    */
    virtual void logEvent(const ErrorEventPtr& eventToRecord) = 0;
  };

  typedef OdSharedPtr<IEventCollector> EventCollectorPtr;

  class Repository;
  typedef OdSmartPtr<Repository> RepositoryPtr;

  class Model;
  typedef OdSmartPtr<Model> ModelPtr;

  /** \details
  A class that implements functionality for working with session data as repositories,
  error logging and non-persistent lists.
  \remarks
  The single current session instance can be created by calling oddaiCreateSession() function,
  it can be deleted only by calling oddaiCloseCurrentSession(). The currently opened session
  can be accessed by oddaiSession() function calling.
  */
  class DAI_EXPORT Session : public SessionInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(Session);
    //DOM-IGNORE-END

    /** \details
    Session class default constructor.
    */
    Session();

    /** \details
    Tries to find repository with defined name inside current session. Changes and
    returns updated name of repository in the case if repository with provided
    name already exists in current session.
    \param session [in] A pointer to session to find repository with name provided.
    \param name [in] A supposed name of repository to create inside a session.
    \returns Returns a name of repository which is available to create inside a session.
    */
    static OdAnsiString generateRepositoryUniqueName(const Session *session, const OdAnsiString &name);

    /** \details
    Creates an empty repository with defined name inside current session.
    \param name [in] A name of repository to create.
    \returns Returns a smart pointer to the newly created repository.
    */
    RepositoryPtr createRepo(const OdAnsiString &name);

    /** \details
    Creates repository with defined name inside current session and opens a fileName as part of the
    newly created repository.
    \param fileName [in] A file name to open as part of newly created repository.
    \param name [in] A name of repository to create.
    \returns Returns a smart pointer to the newly created repository.
    */
    RepositoryPtr createRepoFromFile(const OdAnsiString &fileName, const OdAnsiString &name = "");

    /** \details
    Finds a repository which exists in the current session.
    \param name [in] A name of repository to find.
    \returns Returns a smart pointer to the repository if found, and the null if repository
    doesn't exist in current session.
    */
    RepositoryPtr findRepo(const OdAnsiString &name) const;

    /** \details
    Opens an unopened repository which exists in the current session. 
    */
    void openRepo(RepositoryPtr &repo);

    /** \details
    Closes an opened repository assigned with this session.
    \param repo [in] repository to close.
    */
    void closeRepo(RepositoryPtr &repo);

    /** \details
    Deletes repository record from the session container.
    \param repo [in] repository to delete.
    */
    void deleteRepoRecord(RepositoryPtr &repo);

    /** \details
    Provides error event list.
    \returns Returns current list of error events.
    */
    const OdDAI::List<ErrorEventPtr>&  errors();
    
    /** \details
    Put error record to error event list.
    \param functionID [in] function name.
    \param error [in] error id.
    \param descpt [in] error description.
    */
    void recordError(const char* functionID, daiErrorId error, const char* descpt);
    
    /** \details
    Provides information about error logging activity.
    \returns Returns true if error events recording mode is on, otherwise returns false.
    */
    bool isRecordingOn();
    
    /** \details
    Activate error events recording mode.
    */
    void startEventRecording();
    
    /** \details
    Deactivate error events recording mode.
    */
    void stopEventRecording();

    /** \details
    Sets event collector to handle error events in runtime.
    \param eventCollector [in] - custom event collector. In case when custom event collector was settled, 
    the default collector become inactive, that is why error events recording is not working. To restore 
    default collector and events recording call resetEventCollector without param.
    */
    void resetEventCollector(const EventCollectorPtr& eventCollector = EventCollectorPtr());

    /** \details
    Creates an instance of Non-Persistent List.
    returns A pointer to non-persistent list.
    */
    NonPersistentList* createNPL();

    /** \details
    Deletes an instance of Non-Persistent List.
    */
    void deleteNPL(NonPersistentList *npl);
    
    /** \details
    Retrieves the current value of an attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns Returns the current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    */
    virtual OdRxValue getAttr(const char* attrName) const;

  //DOM-IGNORE-BEGIN

  protected:
    class DefaultEventCollector;

  private:

    mutable OdMutex m_mutex;

    //Implementation m_sdaiImplementation;
    bool m_recordingActive;
    
    OdDAI::List<ErrorEventPtr> m_errors;

    OdArray<RepositoryPtr>  m_knownServers;
    OdArray<RepositoryPtr>  m_activeServers;
    OdArray<ModelPtr>       m_activeModels;

    EventCollectorPtr       m_eventCollector;

    std::set<NonPersistentList*> m_NPLSet;

    void appendActiveModel(ModelPtr &pModel);
    void removeActiveModel(ModelPtr pModel);

    /** \details
    Closes current session instance.
    \remarks
    This method is for internal use only.
    */
    void closeSession();

    friend DAI_EXPORT bool ::oddaiCloseCurrentSession();

    friend class Repository;
    friend class Model;
    class EventHandler;
  };
  typedef OdSmartPtr<Session> SessionPtr;

#if defined(_MSC_VER)
#pragma warning(pop) 
#endif
  //DOM-IGNORE-END

}

#endif // _DAI_SESSION_H
