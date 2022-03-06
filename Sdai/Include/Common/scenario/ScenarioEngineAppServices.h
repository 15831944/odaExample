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

#ifndef _SCENARIO_ENGINE_APPSERVICES_H_
#define _SCENARIO_ENGINE_APPSERVICES_H_

#include "ExSystemServices.h"

namespace ScenarioEngine
{
  template<class HostAppServices>
  class AppServices
    : public ExSystemServices
    , public HostAppServices
  {
  protected:
    ODRX_USING_HEAP_OPERATORS(HostAppServices);

  public:
    virtual ~AppServices();

    OdString getBugDirectory() const;
    OdString getCurrentDirectory() const;
    void setBugDirectory(const OdString& searchPath);
    void setCurrentDirectory(const OdString& currentPath);
    void setCurrentDirectoryByFile(const OdString& currentFile);

    OdString formatPathToBugDirectory(const OdString& filename);
    OdString formatPathToCurrentDirectory(const OdString& filename);

  protected:
    OdString m_searchPath;
    OdString m_executablePath;

    static OdString getDirectory(const OdString& directory);
    static void setDirectory(const OdString& searchPath, OdString& directory);
    static OdString formatPathToDirectory(const OdString& filename, const OdString& directory);
  };
}

namespace ScenarioEngine
{
  template<class HostAppServices>
  AppServices<HostAppServices>::~AppServices()
  {
  }

  template<class HostAppServices>
  OdString AppServices<HostAppServices>::getBugDirectory() const
  {
    return getDirectory(m_searchPath);
  }

  template<class HostAppServices>
  OdString AppServices<HostAppServices>::getCurrentDirectory() const
  {
    return getDirectory(m_executablePath);
  }

  template<class HostAppServices>
  void AppServices<HostAppServices>::setBugDirectory(const OdString& searchPath)
  {
    setDirectory(searchPath, m_searchPath);
  }

  template<class HostAppServices>
  void AppServices<HostAppServices>::setCurrentDirectory(const OdString& currentPath)
  {
    setDirectory(currentPath, m_executablePath);
  }

  template<class HostAppServices>
  void AppServices<HostAppServices>::setCurrentDirectoryByFile(const OdString& currentFile)
  {
    m_executablePath = currentFile;
#if defined(ODA_WINDOWS)
    m_executablePath.replace('/', '\\');
    m_executablePath = m_executablePath.left(m_executablePath.reverseFind('\\'));
#else
    m_executablePath.replace('\\', '/');
    m_executablePath = m_executablePath.left(m_executablePath.reverseFind('/'));
#endif
  }

  template<class HostAppServices>
  OdString AppServices<HostAppServices>::formatPathToBugDirectory(const OdString& filename)
  {
    return formatPathToDirectory(filename, m_searchPath);
  }

  template<class HostAppServices>
  OdString AppServices<HostAppServices>::formatPathToCurrentDirectory(const OdString& filename)
  {
    return formatPathToDirectory(filename, m_executablePath);
  }

  template<class HostAppServices>
  OdString AppServices<HostAppServices>::formatPathToDirectory(const OdString& filename, const OdString& directory)
  {
#ifdef _MSC_VER
    if (filename.find(":") == 1)
      return filename;
#endif

    OdString path;
    path.format(L"%ls\\%ls", directory.c_str(), filename.c_str());

#if defined(ODA_WINDOWS)
    path.replace('/', '\\');
#else
    path.replace('\\', '/');
#endif

    return path;
  }

  template<class HostAppServices>
  OdString AppServices<HostAppServices>::getDirectory(const OdString& directory)
  {
    OdString s = directory;
    if (s.isEmpty())
    {
      return s;
    }

    OdChar last = s.getAt(s.getLength() - 1);
    if (last != '/' && last != '\\' && !s.isEmpty())
    {
#if defined(ODA_WINDOWS)
      s += '\\';
#else
      s += '/';
#endif
    }

    return s;
  }

  template<class HostAppServices>
  void AppServices<HostAppServices>::setDirectory(const OdString& searchPath, OdString& directory)
  {
    directory = searchPath;
#if defined(ODA_WINDOWS)
    directory.replace('/', '\\');
#else
    directory.replace('\\', '/');
#endif

  }
}

#endif
