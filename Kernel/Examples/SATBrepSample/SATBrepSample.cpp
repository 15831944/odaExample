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

/************************************************************************/
/* This console application reads an SAT file and dumps its contents    */
/* to the console.                                                      */
/*                                                                      */
/* Calling sequence:                                                    */
/*                                                                      */
/*    SATBrepSample <filename>                                          */
/*                                                                      */
/************************************************************************/

#include "StdAfx.h"

#include "OdaCommon.h"
#include "ExSystemServices.h"
#include "StaticRxObject.h"

/************************************************************************/
/* From OdBrEx                                                          */
/************************************************************************/
#define SATBREPSAMPLEMODE
#include "BrSearch.cpp"
#include "BrTraverse.cpp"
#include "BrProcess.cpp"

#include "Br/BrBrep.h"

#include "AcisBuilder/ISatConverter.h"

#include "OdFileBuf.h"

#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

bool dumpAll = false;

#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#ifdef OD_HAVE_CCOMMAND_FUNC
  argc = ccommand(&argv);
#endif

  /**********************************************************************/
  /* Verify the argument count and display an error message as required */
  /**********************************************************************/
  if (argc < 2) 
	{
    printf("usage: SATBrepSample <filename> [-DumpAll]\n");
  }
  else
  {
    /**********************************************************************/
    /* Dump all file            */
    /**********************************************************************/
    if (argc > 2)
    {
      OdString argv2 = OdString(argv[2]);
      if (!odStrICmp(argv2, OD_T("-DumpAll")))
      {
       dumpAll = true;
       printf("Full dump of file \n");
      }
    }

    OdStaticRxObject<ExSystemServices> sysServices;
    ::odrxInitialize(&sysServices);

    OdArray<ISATConverter*> out;

    try
    {
      OdString f(argv[1]);
      OdRdFileBuf inFile(f.c_str());
#ifdef ODA_WINDOWS
      printf("Proceed file : %ls\n", argv[1]);
#else
      printf("Proceed file : %s\n", argv[1]);
#endif
    
      if (!ABBreakToSingleBody( &inFile, NULL, true, out ))
      {
        printf("Error in ABBreakToSingleBody.\n");
        return 0;
      }
      else
      {
        printf("File consist of %d bodies.\n", out.size());
        if (!out.isEmpty())
        {
          printf("First body dumping ...\n\n");

          OdBrBrep brep;
          ISATConverter* pIS = out.first();
          brep.set(pIS->getIBr());
          if (!dumpAll)
          {
            int testToRun = menu();
            while (testToRun > 0)
            {
             processOption(brep, 0, testToRun);
             testToRun = menu();
            }
          }
          else
          {
#ifndef SATBREPSAMPLEMODE
           int testToRunsNum = 11;
#else
           int testToRunsNum = 10;
#endif
           for(int testToRun = 1; testToRun < testToRunsNum; testToRun++)
            processOption(brep, 0, testToRun);
          }
        }
      }
    }
    catch(const OdError_FileException &err)
    {
      printf("File error : %ls\n", err.description().c_str());
    }
    catch(const OdError &)
    {
      printf("Internal error\n");
    }

    for(OdUInt32 f = 0; f < out.size(); ++f)
      ABDeleteConverter(out[f]);
    
    out.clear();

    odrxUninitialize();
  }

  if (!dumpAll)
  {
    STD(cout) << "Press RETURN to exit..." << STD(endl);
    STD(cin).get();
  }

	return 0;
}

