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

#ifndef _DWGR21UTILS_H_
#define _DWGR21UTILS_H_

// TODO: 'int' -> 'OdInt64'
#if defined(_MSC_VER)
#pragma warning ( disable : 4244 ) // conversion from 'OdInt64' to 'int', possible loss of data
#endif

//----------------------------------------------------------
//
// Trace R21 format macros
//
//----------------------------------------------------------
#ifdef _DEBUG
  //#define _DWG_TRACE_         // uncomment to trace file loading
  //#define _DWG_TRACE_BYTES_   // uncomment to trace bytes
  //#define _DWG_DUMP_          // uncomment to dump to file

  //#define _DWG_OBJ_TRACE_
  //#define _DWG_R12_TRACE_
  //#define _DWG_R15_TRACE_
  //#define _DWG_R18_TRACE_
  //#define _DWG_R21_TRACE_
  //#define _DWG_R24_TRACE_
#endif

#ifdef _DWG_TRACE_

  #ifdef _DWG_DUMP_

    #include "DbFilerController.h"
    extern TOOLKIT_EXPORT FILE* G_pDumpFile;
    class OdDwgDumper
    {
    public:
      OdDwgDumper(OdDbFilerController* pCtrl)
      {
        ODA_ASSERT(!G_pDumpFile);
        OdString fName = OdString(OD_T(".dmp"));
        fName.insert(0, pCtrl->getStreamBuf()->fileName());
        G_pDumpFile = fopen(fName, "wt");
      }
      ~OdDwgDumper()
      { 
        if (G_pDumpFile)
        {
          fclose(G_pDumpFile);
          G_pDumpFile = 0;
        }
      }
    };
    #define DD_DWG_DUMPER_DEFINE() FILE* G_pDumpFile = 0;
    #define DD_DWG_DUMPER_CREATE(pCtrl) OdDwgDumper dwgDumper(pCtrl);

    #define DWG_TRACE1(str, par1) if (G_pDumpFile) { fprintf(G_pDumpFile, str, par1); fflush(G_pDumpFile); }

    #ifdef TM_DASHBOARD
      TOOLKIT_EXPORT_GLOBAL FILE* getDumpFilePtr();
    #endif

  #else // _DWG_DUMP_

    #define DD_DWG_DUMPER_DEFINE()
    #define DD_DWG_DUMPER_CREATE(pCtrl)
    #define DWG_TRACE1 ODA_TRACE1

  #endif // _DWG_DUMP_

  inline
  void odTraceBytes(OdUInt8* buffer, int num, bool asBits = false)
  {
    int index = 0; 
    for (OdInt32 k = 0; k < num; k++)
    {
      OdUInt8 c = buffer[index++];
      if (k && (k % 16) == 0)
      //if (k && (k % 8) == 0)
      {
        DWG_TRACE1("%s", "\n");
      }
      if (asBits)
      {
        int mask = 0x80;
        for (int i = 0; i < 8; i++)
        {
          DWG_TRACE1("%d", (c & mask) ? 1 : 0);
          mask >>= 1;
        }
        DWG_TRACE1("%s", " "); 
      }
      else
      {
        DWG_TRACE1("%02X ", c);
      }
    }
    DWG_TRACE1("%s", "\n");
  }

  #ifdef _DWG_TRACE_BYTES_
    #define DWG_TRACE_BYTES(buff,num,title) \
      { \
        if (strlen(title)) DWG_TRACE1("\n//\n// %s\n//\n", title); \
        odTraceBytes(buff,num); \
      }
  #else //_DWG_TRACE_BYTES_
    #define DWG_TRACE_BYTES(buff,num,title)
  #endif // _DWG_TRACE_BYTES_

#else // _DWG_TRACE_

  #define DD_DWG_DUMPER_DEFINE()
  #define DD_DWG_DUMPER_CREATE(pCtrl)
  #define DWG_TRACE1(str, par1)
  #define DWG_TRACE_BYTES(buff,num,title)

  #undef _DWG_TRACE_BYTES_
  #undef _DWG_DUMP_

#endif // _DWG_TRACE_

#ifdef _DWG_OBJ_TRACE_
  #define OBJ_TRACE1 DWG_TRACE1
  #define OBJ_TRACE_BYTES DWG_TRACE_BYTES
#else
  #define OBJ_TRACE1
  #define OBJ_TRACE_BYTES
#endif

#ifdef _DWG_R12_TRACE_
#define R12_TRACE1 DWG_TRACE1
#define R12_TRACE_BYTES DWG_TRACE_BYTES
#else
#define R12_TRACE1
#define R12_TRACE_BYTES
#endif

#ifdef _DWG_R15_TRACE_
  #define R15_TRACE1 DWG_TRACE1
  #define R15_TRACE_BYTES DWG_TRACE_BYTES
#else
  #define R15_TRACE1
  #define R15_TRACE_BYTES
#endif

#ifdef _DWG_R18_TRACE_
  #define R18_TRACE1 DWG_TRACE1
  #define R18_TRACE_BYTES DWG_TRACE_BYTES
#else
  #define R18_TRACE1
  #define R18_TRACE_BYTES
#endif

#ifdef _DWG_R21_TRACE_
  #define R21_TRACE1 DWG_TRACE1
  #define R21_TRACE_BYTES DWG_TRACE_BYTES
#else
  #define R21_TRACE1
  #define R21_TRACE_BYTES
#endif

#ifdef _DWG_R24_TRACE_
  #define R24_TRACE1 DWG_TRACE1
  #define R24_TRACE_BYTES DWG_TRACE_BYTES
#else
  #define R24_TRACE1
  #define R24_TRACE_BYTES
#endif

#endif //_DWGR21UTILS_H_
