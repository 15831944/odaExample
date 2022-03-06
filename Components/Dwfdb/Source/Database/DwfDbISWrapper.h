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

#ifndef _DWFDBISW_H_
#define _DWFDBISW_H_

#include "OdString.h"
#include "dwfcore/InputStream.h"
#include "dwfcore/Exception.h"
#include "package/Resource.h"
#include "package/reader/PackageReader.h"

class DwfDbInputStreamWrapper : public DWFCore::DWFInputStream
{
  class OdStreamBuf* m_pStream;
  DWFToolkit::DWFPackageReader::tePackageType m_Ver;

  class OdDbBaseHostAppServices* m_pBaseSrv;
  class OdDbHostAppProgressMeter* m_pProgress;
  int m_currentProgress,
      m_maxProgress;

public:
  DwfDbInputStreamWrapper(OdStreamBuf* s, class OdDbBaseHostAppServices* pBaseSrv); // = NULL);
  virtual ~DwfDbInputStreamWrapper();
  virtual size_t available() const ;
  virtual size_t read( void*  pBuffer, size_t nBytesToRead ) ;
  virtual off_t seek( int eOrigin, off_t nOffset ) ;

  // version of DWF (6.00 = 600, 5.5 = 0.55 = 55, etc)
  //
  DWFToolkit::DWFPackageReader::tePackageType getDWFVersion( ) { return m_Ver; }
  OdStreamBuf* streamBuf() { return m_pStream; }

  void startMeter(const OdString& sText = L"DWF Package loading");
  void stopMeter();
  void stepMeter();
private:
  DwfDbInputStreamWrapper(); // disabled
  DwfDbInputStreamWrapper(const DwfDbInputStreamWrapper&); // disabled
};

#endif // _DWFDBISW_H_
