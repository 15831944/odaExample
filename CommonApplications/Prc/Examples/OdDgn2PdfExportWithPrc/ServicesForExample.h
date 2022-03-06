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

// Main.cpp : Defines the entry point for the console application.
//

#ifndef SERVICESFOREXAMPLE_H
#define SERVICESFOREXAMPLE_H

#include "OdTimeStamp.h"
#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

typedef void (*PgetLocalTime)( OdTimeStamp& ts );
extern FIRSTDLL_EXPORT_STATIC PgetLocalTime g_pLocalTimeFunc; // global variable defined in TD_Root
static void getLocalTime(OdTimeStamp &localTime){ localTime.setToZero();}

#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

#include "ExPrintConsole.h"
#include "StaticRxObject.h"
#include "DgHostAppServices.h"
#include "ExDgnServices.h"
#include "ExDgnHostAppServices.h"
#include "ExPrcHostAppServices.h"

template <class T> class PrcHostFindFile : public T
{
public:
  OdString m_searchPath;
  OdString m_testDirectory;

private:
  OdString getBugDirectory()
  {
    OdString s = m_searchPath + "\\" + m_testDirectory + "\\";
    OdChar last = s.getAt(s.getLength()-1);
    if (last != '/' && last != '\\')
      s += '/';
    return s;
  }

  OdString formatPathToBugDirectory(const OdString& filename)
  {
    OdString path = getBugDirectory();

    OdChar last = path.getAt(path.getLength()-1);
    if (last != '/' && last != '\\')
      path += '/';

    path = path + filename.c_str();

#if defined(ODA_WINDOWS)
    path.replace('/', '\\');
    path.replace(L"\\\\", L"\\");
#else
    path.replace('\\', '/');
    path.replace(L"//", L"/");
#endif

    odPrintConsoleString(L"formatPathToBugDirectory:\n%ls\n", path.c_str());
    return path;
  }

public:

  virtual OdString findFile(const OdString& filename, OdDbBaseDatabase* pDb = 0, OdDbBaseHostAppServices::FindFileHint hint = OdDbBaseHostAppServices::kDefault)
  {
    OdString found;
    found = formatPathToBugDirectory(filename);
    if (!odrxSystemServices()->accessFile(found, Oda::kFileRead))
    {
      if (!odrxSystemServices()->accessFile(filename, Oda::kFileRead))
      {
        return OdString::kEmpty;
      }
      return filename;
    }
    return found;
  }
};
/************************************************************************/
/* Define a Custom Services class.                                      */
/*                                                                      */
/* Combines the platform dependent functionality of                     */
/* OdRxSystemServices and OdPrcHostAppServices                       */
/************************************************************************/

template <class PrcHost = OdExPrcHostAppServices, class TgHost = OdExDgnHostAppServices, class exServices = ExSystemServices>
class MyDgServicesBase
{
  OdStaticRxObject<PrcHost>    m_PrcHostAppServices;
  OdStaticRxObject<TgHost>     m_TgHostAppServices;
  OdStaticRxObject<exServices> m_systemServices;

public:

  virtual OdRxSystemServices *systemServices() { return &m_systemServices; }
  virtual TgHost &hostTG() { return m_TgHostAppServices; }
  virtual OdExPrcHostAppServices &hostPRC() { return m_PrcHostAppServices; }

  virtual const OdRxSystemServices *systemServices() const { return &m_systemServices; }
  virtual const TgHost &hostTG() const { return m_TgHostAppServices; }
  virtual const OdExPrcHostAppServices &hostPRC() const { return m_PrcHostAppServices; }

  virtual ~MyDgServicesBase() {}
};

class MyDgServices : public MyDgServicesBase<>
{
};

/********************************************************************************/
/* Define Assert function to not crash Debug application if assertion is fired. */
/********************************************************************************/
static void MyAssert(const char* expression, const char* fileName, int nLineNo)
{
  OdString message;
  message.format(L"\n!!! Assertion failed: \"%ls\"\n    file: %ls, line %d\n", OdString(expression).c_str(), OdString(fileName).c_str(), nLineNo);
  odPrintConsoleString(message);
}

class MyServicesForTest : public MyDgServicesBase<PrcHostFindFile<OdExPrcHostAppServices> >
{
public:
  void setSearchPath(const OdString& path)
  {
   ((PrcHostFindFile<OdExPrcHostAppServices>&)hostPRC()).m_searchPath = path;
  }
  
  void setTestFolder(const OdString& pathToFolder)
  {
    ((PrcHostFindFile<OdExPrcHostAppServices>&)hostPRC()).m_testDirectory = pathToFolder;
  }
  
};

#endif //SERVICESFOREXAMPLE_H
