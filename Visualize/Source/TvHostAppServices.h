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

#ifndef _ODTV_HOSTAPPSERVICES_H_INCLUDED_
#define _ODTV_HOSTAPPSERVICES_H_INCLUDED_

#include "TD_PackPush.h"

#include "DbHostAppServices.h"
#include "HatchPatternManager.h"
#include "StaticRxObject.h"
#include "ThreadsCounter.h"
#define STL_USING_SET
#include "OdaSTL.h"

typedef OdArray<OdTtfDescriptor> mapTrueTypeFont;
typedef std::set<OdString> stringSet;

/** \details
  This class implements platform-dependent operations and progress metering. (equal to 'ExHostAppServices' now) 
*/
class TvHostAppServices : public OdTvDbHostAppServices2, public OdDbHostAppProgressMeter
{  
  OdString  m_Prefix;
  long      m_MeterLimit;
  long      m_MeterCurrent;
  long      m_MeterOld;
  bool      m_disableOutput;

  stringSet m_pathesToCustomFolders;
  OdString m_strCustomImageFolder;
  // MT support
  OdMutexPtr m_mutex;

  OdHatchPatternManagerPtr m_patternManager;

  OdDbHostAppProgressMeter* m_pMeter;
public:
  TvHostAppServices();
  virtual ~TvHostAppServices();

  virtual OdString findFile(
    const OdString& filename,
    OdDbBaseDatabase* pDb = 0,
    FindFileHint hint = kDefault);
 // virtual OdTvDbKey* key() const;

  void setProgressMeter(OdDbHostAppProgressMeter* pMeter) { m_pMeter = pMeter; }

  OdDbHostAppProgressMeter* newProgressMeter();

  void releaseProgressMeter(OdDbHostAppProgressMeter* pProgressMeter);

  void warning(const char*, const OdString&) {}

  // OdDbHostAppProgressMeter functions

  void start(const OdString& displayString = OdString::kEmpty);

  void stop();

  void meterProgress();

  void setLimit(int max);

  bool ttfFileNameByDescriptor(const OdTtfDescriptor& description, OdString& filename);

  /** \details
    Controls display of this ProgressMeter.
    \param disable [in]  Disables this ProgressMeter. 
  */
  void disableOutput(bool disable) { m_disableOutput = disable; }

  /** \details
    Sets the prefix for this ProgressMeter.
    \param prefix [in]  Prefix for this ProgressMeter.
  */
  void setPrefix(const OdString& prefix) { m_Prefix = prefix; }

  OdRxClass* databaseClass() const;

  OdHatchPatternManager* patternManager();

  OdTvDbDatabasePtr readFile(const OdString& filename,
    bool allowCPConversion = false,
    bool partialLoad = false,
    Oda::FileShareMode shareMode = Oda::kShareDenyNo,
    const OdPassword& password = OdPassword());

  void addCustomFolderPath(const OdString& path);

  void setCustomImageFolder(const OdString& strFolderPath);

  /** \details
  Returns a the gsBitmapDevice associated with this HostAppServices object.

  \param pViewObj [in]  OdAbstractViewPE compatible object (OdGsView, OdTvDbViewport or etc.).
  \param pDb [in]  Pointer to the database context.
  \param flags [in]  Bitmap device flags.
  */
  virtual OdGsDevicePtr gsBitmapDevice(
    OdRxObject* pViewObj = NULL,
    OdDbBaseDatabase* pDb = NULL,
    OdUInt32 flags = 0);
};

#include "TD_PackPop.h"

#endif //_ODTV_HOSTAPPSERVICES_H_INCLUDED_

