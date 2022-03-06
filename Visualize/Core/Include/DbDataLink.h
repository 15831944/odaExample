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



#ifndef OD_DBDATALINK_H
#define OD_DBDATALINK_H

#include "DbObject.h"
#include "OdValue.h"
#include "StringArray.h"

#include "TD_PackPush.h"

namespace OdDb
{
  enum DataLinkOption
  { 
    kDataLinkOptionNone                         = 0,
    kDataLinkOptionAnonymous                    = 0x1,
    kDataLinkOptionPersistCache                 = 0x2,
    kDataLinkOptionDisableInLongTransaction     = 0x4,
    kDataLinkHasCustomData                      = 0x8
  };

  enum PathOption
  { 
    kPathOptionNone = 1,
    kPathOptionRelative,
    kPathOptionAbsolute,
    kPathOptionPathAndFile
  };

  enum UpdateDirection   
  { 
    kUpdateDirectionSourceToData   = 0x1,
    kUpdateDirectionDataToSource   = 0x2
  };

  enum UpdateOption 
  { 
    kUpdateOptionNone                                  = 0,
    kUpdateOptionSkipFormat                            = 0x20000,
    kUpdateOptionUpdateRowHeight                       = 0x40000,
    kUpdateOptionUpdateColumnWidth                     = 0x80000,
    kUpdateOptionAllowSourceUpdate                     = 0x100000,
    kUpdateOptionForceFullSourceUpdate                 = 0x200000,
    kUpdateOptionOverwriteContentModifiedAfterUpdate   = 0x400000,
    kUpdateOptionOverwriteFormatModifiedAfterUpdate    = 0x800000,
    kUpdateOptionForPreview                            = 0x1000000,
    kUpdateOptionIncludeXrefs                          = 0x2000000,
    kUpdateOptionSkipFormatAfterFirstUpdate            = 0x4000000
  };

  enum DataLinkGetSourceContext
  { 
    kDataLinkGetSourceContextUnknown,
    kDataLinkGetSourceContextEtransmit,
    kDataLinkGetSourceContextXrefManager,
    kDataLinkGetSourceContextFileWatcher,
    kDataLinkGetSourceContextOther
  };
};

/** \details
    This class links a table to data in another file.

    \sa
    TD_Db
    
    <group OdTvDb_Classes> 

*/
class DBENT_EXPORT OdTvDbDataLink : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbDataLink);

  OdTvDbDataLink(void);
  
  OdString name (void) const;
  void setName (const OdString& sName);
  OdString description (void) const;
  void setDescription (const OdString& sDescription);
  OdString getToolTip (void) const;
  void setToolTip (const OdString& sToolTip);
  OdString  dataAdapterId (void) const;
  void setDataAdapterId (const OdString& sAdapterId);
  OdString  connectionString (void) const;
  void setConnectionString(const OdString& sConnectionString);
  OdDb::DataLinkOption option (void) const;
  void setOption (OdDb::DataLinkOption nOption);
  OdInt32 updateOption (void) const;
  void setUpdateOption(OdInt32 nOption);
  void update (OdDb::UpdateDirection nDir, OdDb::UpdateOption nOption);
  void getUpdateStatus(OdDb::UpdateDirection* pDir, OdTimeStamp* pTime, OdString* pErrMessage) const;
  void setUpdateStatus(const OdString& sErrMessage);
  bool isValid (void) const;
  OdInt32 getTargets (OdTvDbObjectIdArray& targetIds) const;
  void getSourceFiles(OdDb::DataLinkGetSourceContext nContext, OdStringArray& files) const;
  void repathSourceFiles(OdString& sBasePath, OdDb::PathOption nOption);
  OdTvDbObjectId contentId() const;
  OdValue getCustomData(const OdString& sKey) const;
  void setCustomData(const OdString& sKey, const OdValue* pData);

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};

typedef OdArray<OdTvDbDataLink*> OdTvDbDataLinkArray;

typedef OdSmartPtr<OdTvDbDataLink> OdTvDbDataLinkPtr;


//*************************************************************************
// OdTvDbDataLinkManager
//*************************************************************************
class OdTvDbDataLinkManagerImpl;

/** \details
    <group OdTvDb_Classes> 
*/
class DBENT_EXPORT OdTvDbDataLinkManager : public OdStaticRxObject<OdRxObject>
{
public:
  ODRX_HEAP_OPERATORS();

  ODRX_DECLARE_MEMBERS(OdTvDbDataLinkManager);
  
  OdTvDbDataLinkManager(void);
  ~OdTvDbDataLinkManager(void);
  OdTvDbObjectId createDataLink(const OdString& adapterId, const OdString& name,
    const OdString& description, const OdString& connectionString);

  OdTvDbObjectId getDataLink(const OdString& name) const;

  OdTvDbDataLinkPtr getDataLink(const OdString& name, OdDb::OpenMode mode) const;

  int   dataLinkCount(void) const;

  int   getDataLink(OdTvDbObjectIdArray& dataLinks) const;

  OdTvDbObjectId addDataLink(OdTvDbDataLink* pDataLink);

  void removeDataLink(const OdString& sKey, OdTvDbObjectId& idDataLink);

  void removeDataLink(const OdTvDbObjectId& idDataLink);

  void update(const OdTvDbObjectIdArray& dataIds, OdDb::UpdateDirection nDir, OdDb::UpdateOption nOption);
  void update(OdDb::UpdateDirection nDir, OdDb::UpdateOption nOption);

  void setDatabase(OdTvDbDatabase* pDb);
protected:
  OdTvDbDataLinkManager(OdTvDbDataLinkManagerImpl* pValImpl);
  OdTvDbDataLinkManagerImpl* m_pImpl;
  friend class OdTvDbSystemInternals;
};

typedef OdSmartPtr<OdTvDbDataLinkManager> OdTvDbDataLinkManagerPtr;

/** \details
    <group OdTvDb_Classes> 
*/
class DBDIM_EXPORT OdTvDbDataLinkUpdatePE : public OdRxObject
{
public:
  virtual OdError dataLinkUpdate(OdTvDbDataLink* pDataLink, OdDb::UpdateDirection nDir, OdDb::UpdateOption nOption) = 0;
  virtual OdError repathSourceFiles(OdString& sBasePath, OdDb::PathOption nOptionm, OdString& path) = 0;

  ODRX_DECLARE_MEMBERS(OdTvDbDataLinkUpdatePE);
};

typedef OdSmartPtr<OdTvDbDataLinkUpdatePE> OdTvDbDataLinkUpdatePEPtr;

#include "TD_PackPop.h"

#endif // OD_DBDATALINK_H
