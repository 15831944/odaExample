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

#ifndef _SCENARIO_ENGINE_UTILS_H_
#define _SCENARIO_ENGINE_UTILS_H_

#include <stdlib.h>

#if defined(ODA_WINDOWS)
#include <psapi.h>
#endif

#include "OdString.h"
#include "ScenarioEngineDeclarations.h"
#include "OdPerfTimer.h"
#define ARGS_PREPROCESSING (argc, argv) \
#if defined(TARGET_OS_MAC) && !defined(__MACH__)\
    argc = ccommand(&argv);\
#endif

#ifdef OD_HAVE_WINBASE_H_FILE
#include <WinBase.h>
#endif
#ifdef OD_HAVE_UNISTD_FILE
#include <unistd.h>
#endif

namespace ScenarioEngine
{

  class PerformanceCounter;
  // Functions:

  static void printConsoleString(const wchar_t* fmt, ...)
  {
    va_list argList;
    va_start(argList, fmt);
    OdString s;
    s.formatV(fmt, argList);
    va_end(argList);
#if (defined(_WIN32) || defined(_WIN64)) && !defined(_WIN32_WCE)
    DWORD dw;
    HANDLE o = ::GetStdHandle(STD_OUTPUT_HANDLE);
    if (::GetFileType(o) == FILE_TYPE_CHAR)
      WriteConsoleW(o, s.c_str(), s.getLength(), &dw, 0);
    else
      WriteFile(o, (const char*)s, s.getLengthA(), &dw, 0);
#else
    printf("%ls", s.c_str());
#endif
  }

  static void LogMemoryInfo(OdUInt32 procID)
  {
#if defined (_MSC_VER) && (_MSC_VER > 1300)
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;

    if (!procID)
      procID = GetCurrentProcessId();

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, procID);
    if (!hProcess)
    {
      return;
    }

    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
    {
      printConsoleString(L"Memory allocation peak, in bytes : %d\n", pmc.PeakWorkingSetSize);
    }

    CloseHandle(hProcess);
#endif
  }

  static void LogMemoryInfoForCurrentProcess()
  {
    LogMemoryInfo(0);
  }


  template<class PTestFunc, class THostAppServices>
  int TestRun(PTestFunc pf, THostAppServices* app, int curRun)
  {
    try
    {
      pf(app, curRun);
    }
    catch (const OdError& e)
    {
      printConsoleString(L"%ls\n", e.description().c_str());
      return 1;
    }
    catch (const wchar_t* s)
    {
      printConsoleString(L"%ls\n", s);
      return 2;
    }
    catch (...)
    {
      printConsoleString(L"Unknown error\n");
      return 3;
    }
    printConsoleString(L"SUCCESS\n");
    return 0;
  }

  template<class PerfFunc, class THostAppServices>
  int PerfRun(PerfFunc pf, THostAppServices* app, int iterationNumber, OdPerfTimerBase* performanceCounter)
  {
    try
    {
      pf(app, iterationNumber, performanceCounter);
    }
    catch (const OdError& e)
    {
      printConsoleString(L"%ls\n", e.description().c_str());
      return 1;
    }
    catch (const wchar_t* s)
    {
      printConsoleString(L"%ls\n", s);
      return 2;
    }
    catch (...)
    {
      printConsoleString(L"Unknown error\n");
      return 3;
    }
    printConsoleString(L"SUCCESS\n");
    return 0;
  }

  template<class PerfFunc, class THostAppServices>
  int RenderRun(PerfFunc pf, THostAppServices* app, unsigned testNumber, const OdString &outBmpFile)
  {
    try
    {
      pf(app, testNumber, outBmpFile);
    }
    catch (const OdError& e)
    {
      printConsoleString(L"%ls\n", e.description().c_str());
      return 1;
    }
    catch (const wchar_t* s)
    {
      printConsoleString(L"%ls\n", s);
      return 2;
    }
    catch (...)
    {
      printConsoleString(L"Unknown error\n");
      return 3;
    }
    printConsoleString(L"SUCCESS\n");
    return 0;
  }


  template<class TType>
  bool tryParseTemplate(const test_arg_char* from, char* bufferTemplate, TType& to)
  {
    OdString  bufferForScanf(from);
    return sscanf(((OdAnsiString)bufferForScanf).c_str(), bufferTemplate, &to) == 1;
  }

  static bool tryParse(const test_arg_char* from, unsigned int& to)
  {
    int valueProxy = 0;
    if (tryParseTemplate<int>(from, "%d", valueProxy))
    {
      return false;
    }
    
    to = static_cast<unsigned int>(valueProxy);
    return true;
  }

  static bool tryParse(const test_arg_char* from, int& to)
  {
    return tryParseTemplate<int>(from, "%d", to);
  }

  static bool tryParse(const test_arg_char* from, float& to)
  {
    return tryParseTemplate<float>(from, "%f", to);
  }

  static bool tryParse(const test_arg_char* from, double& to)
  {
    return tryParseTemplate<double>(from, "%lf", to);
  }

  static bool tryParse(const test_arg_char* from, OdString& to)
  {
    to = from;
    return true;
  }

  class SafeDeleteTestFileHolder
  {
  public:
    SafeDeleteTestFileHolder(const OdString& tempRoot, int fileId, const OdString &extension = OD_T("ifc"), bool deleteOnDestroy = true)
      : m_deleteOnDestroy(deleteOnDestroy)
    {
      char fileNameOut[100] = {};
      OdTimeStamp timeStamp(OdTimeStamp::kInitLocalTime);
      OdUInt32 msecs = timeStamp.msecsPastMidnight();
#if !defined(ODA_WINDOWS)
      uintmax_t procId = (uintmax_t)getpid();
#else
      OdUInt32 procId = GetCurrentProcessId();
#endif
#if defined(_MSC_VER) && _MSC_VER < 1900
      _snprintf(fileNameOut, sizeof(fileNameOut) / sizeof(fileNameOut[0]), "tempCompare_p%u_f%d_t%u.", procId, fileId, msecs);
#else
      snprintf(fileNameOut, sizeof(fileNameOut) / sizeof(fileNameOut[0]), "tempCompare_p%u_f%d_t%u.", procId, fileId, msecs);
#endif
      m_ifcFileNameTo = tempRoot + fileNameOut + extension;
    }

    ~SafeDeleteTestFileHolder()
    {
      printConsoleString(L"~SafeDeleteTestFileHolder: ");
      if (m_deleteOnDestroy)
      {
        int removeResult = remove(static_cast<OdAnsiString>(m_ifcFileNameTo).c_str());

        OdString str = OdString().format(L"Remove %s result: %d\n", m_ifcFileNameTo.c_str(), removeResult);
        printConsoleString(str.c_str());
      }
      else
      {
        printConsoleString(L"Remove should not be called\n");
      }

    }

    bool  isFileExists()
    {
      FILE *file = fopen(static_cast<OdAnsiString>(m_ifcFileNameTo).c_str(), "r");
      if (file != NULL)
      {
        fclose(file);
        return true;
      }

      return false;
    }

    const OdString& get() { return m_ifcFileNameTo; }

  private:
    OdString  m_ifcFileNameTo;
    bool      m_deleteOnDestroy;
  };

}

#endif
