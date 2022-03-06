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

#ifndef OD_VISUALIZE_APP_SAMPLES_H
#define OD_VISUALIZE_APP_SAMPLES_H
#include "TD_PackPush.h"
#include "OdaCommon.h"
#include "TvDatabase.h"
#include "TvFactory.h"

/**
\details
An interface for sample context
*/
class OdVisualizeSampleContext
{
public:
  /**
  \details
  File types for filePath() method.
  */
  enum FileType
  {
    kOBJ = 0,
    kPNG = 1
  };
  /**
  \details
  Returns path to file
  */
  virtual OdString filePath( FileType type ) const = 0;
  /**
  \details
  Creates a device in specified database
  \remarks
  Device creation required some application settings (window handle, vectorization device) so it should happen on application side
  */
  virtual OdTvGsDeviceId createDevice( OdTvDatabaseId dbId ) = 0;
  /**
  \details
  Setup the incoming device
  \remarks
  Device setup required some application settings (window handle) so it should happen on application side
  */
  virtual OdTvDCRect setupDevice(OdTvGsDeviceId devId) = 0;
  /**
  \details
  Notifies application about changing of active device
  */
  virtual void setActiverDevice( OdTvGsDeviceId id ) const = 0;
  /**
  \details
  Notifies application about changing of active database
  */
  virtual void setActiveDatabase( OdTvDatabaseId id ) const = 0;
  /**
  \details
  Notifies application about changing of active view
  \param id [in] ID of active view
  \param num [in] Index of active in device view list
  */
  virtual void setActiveView( OdTvGsViewId id, OdUInt8 num = 0 ) const = 0;
  /**
  \details
  Show message box
  \param lpTex [in] message text
  \param lpCaption [in] caption
  \param uType [in] set of different flags
  */
  virtual int showMessageBox(LPCTSTR lpText, LPCTSTR lpCaption, UINT uType) = 0;
};

/**
\details
An interface for visualize sample
*/
class OdVisualizeSample
{
public:
  /**
  \details
  Executes sample
  */
  virtual bool run( OdVisualizeSampleContext* pContext ) = 0;
};

/**
\details
A sample manager
*/
class OdVisualizeSampleManager
{
public:
  /**
  \details
  A list of available samples
  */
  enum Samples
  {
    kInvalidSample = 0,
    kMultiViewSample = 1,
    kWalkingAnimation = 2
  };
  /**
  \details
  Executes sample
  */
  static bool run( Samples sample, OdVisualizeSampleContext* pContext );
};

#include "TD_PackPop.h"
#endif //OD_VISUALIZE_APP_SAMPLES_H

