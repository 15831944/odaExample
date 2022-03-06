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

#ifndef DbAssocNetworkDeepCloneReactor_INCLUDED_
#define DbAssocNetworkDeepCloneReactor_INCLUDED_ /*!DOM*/

#include "DbDatabase.h"
#include "RxEvent.h"

#define STL_USING_MAP
#include "OdaSTL.h"
#include "DbObjectOverrule.h"

class OdTvDbAssocAction;
class OdTvDbIdMapping;
class OdTvDbAssocNetCloneCtx;

/** \details
  This class implements the deep clone overrule for assoc. network deep/wblock cloning.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class OdTvDbAssocNetCloneOverrule : public OdStaticRxObject<OdTvDbObjectOverrule> {
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocNetCloneOverrule);

  virtual OdTvDbObjectPtr deepClone(const OdTvDbObject* subject, OdTvDbIdMapping& idMap, OdTvDbObject* owner, bool primary = true);

  virtual OdTvDbObjectPtr wblockClone(const OdTvDbObject* subject, OdTvDbIdMapping& idMap, OdTvDbObject* owner, bool primary = true);

  virtual bool isApplicable(const OdRxObject* subject) const;

  OdTvDbAssocNetCloneOverrule();

  void addOverruleClient();
  void removeOverruleClient();

private:
  unsigned m_clients;
  bool m_WasOverruling;
};


/** \details
  This class implements the deep clone reactor.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class OdTvDbAssocNetworkDeepCloneReactor: public OdTvRxEventReactor
{
public:
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocNetworkDeepCloneReactor();

  /** \details
    Destructor destroys an instance of this class.
  */
  ~OdTvDbAssocNetworkDeepCloneReactor();

  /** \details
    Adds the reference to the deep clone reactor.
  */
  void addRefReactor();

  /** \details
    Releases the deep clone reactor.
  */
  void releaseReactor();

  // OdTvRxEventReactor methods

  void beginDeepClone(OdTvDbDatabase* pToDb, OdTvDbIdMapping& idMap);

  void beginDeepCloneXlation(OdTvDbIdMapping& idMap);

  /** \details
    Aborts the deep clone.
  */
  void abortDeepClone(OdTvDbIdMapping& idMap);

  /** \details
    Ends the deep clone.
  */
  void endDeepClone(OdTvDbIdMapping& idMap);

  void databaseToBeDestroyed(OdTvDbDatabase* pDb);

private:
  /*!DOM*/
  class ContextTerminator
  {
  public:
    ContextTerminator(OdTvDbAssocNetworkDeepCloneReactor& reactor,
                      OdTvDbDatabase* pContextDb);

    ~ContextTerminator();

  private:
    OdTvDbAssocNetworkDeepCloneReactor& m_reactor;
    OdTvDbDatabase* m_pContextDb;
  };

  /*!DOM*/
  void startProcess(OdTvDbIdMapping& idMap);
  /*!DOM*/
  ContextTerminator endProcessDeferred(OdTvDbDatabase* pDb);
  /*!DOM*/
  OdSmartPtr<OdTvDbAssocNetCloneCtx> getProcessContext(OdTvDbIdMapping& idMap);

  /*!DOM*/
  int m_Counter;
  /*!DOM*/
  OdTvDbAssocNetCloneOverrule m_Overrule;
  /*!DOM*/
  typedef void(*EventHandler)(OdTvDbAssocAction* source, OdTvDbAssocNetCloneCtx& ctx);
  /*!DOM*/
  void processEvent(OdTvDbAssocNetCloneCtx& ctx, EventHandler eventHandler);
};

#endif
