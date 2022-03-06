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
/* This console application reads an SAT file and renders the shell     */
/* and/or silhouette.                                                   */
/*                                                                      */
/* Calling sequence:                                                    */
/*                                                                      */
/*    SATGeomTracer <filename>                                          */
/*                                                                      */
/************************************************************************/
#include "StdAfx.h"

#include "OdaCommon.h"
#include "ExSystemServices.h"
#include "StaticRxObject.h"

#include "Br/BrBrep.h"

#include "AcisBuilder/ISatConverter.h"
#include "BrepTrace.h"

#include "OdFileBuf.h"
#include "BrepTrace.h"
#include "BrepRenderer/BrepRendererImpl.h"

#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  
  /**********************************************************************/
  /* Set command line defaults                                          */
  /**********************************************************************/
  bool disableWait = false;

#ifdef OD_HAVE_CCOMMAND_FUNC
  argc = ccommand(&argv);
#endif

  /**********************************************************************/
  /* Verify the argument count and display an error message as required */
  /**********************************************************************/
  if (argc < 2) 
	{
    printf("usage: SATGeomTracer <filename> [-NoWait]\n");
  }
  else
  {
    /**********************************************************************/
    /* Disable prompt of pressing ENTER and answer on questions           */
    /**********************************************************************/
    if (argc > 2)
    {
      OdString argv2 = OdString(argv[2]);
      if (!odStrICmp(argv2, OD_T("-NoWait")))
      {
        disableWait = true;
      }
    }

    /******************************************************************/
    /* Initialize ODA library                                         */
    /******************************************************************/
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

      /******************************************************************/
      /* Read each body into its own converter                          */
      /******************************************************************/
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
          /**************************************************************/
          /* Dump the first body                                        */
          /**************************************************************/
          printf("First body dumping ...\n\n");

          /**************************************************************/
          /* Create a renderer                                          */
          /*******************(******************************************/
          OdBrepRendererImpl *pRenderer = new OdBrepRendererImpl;
          if (pRenderer)
          {
            
            OdBrBrep brep;
            /************************************************************/
            /* Set the acis data for brep from the converter (file)     */
            /************************************************************/
            ISATConverter* pIS = out.first();
            brep.set(pIS->getIBr());
            /************************************************************/
            /* Set the brep data for the renderer                       */
            /************************************************************/
            pRenderer->setBrep(brep);

            /************************************************************/
            /* Render the brep data                                     */
            /************************************************************/
            BrepGeometryTracer(pRenderer);

            /************************************************************/
            /* Dump the shell                                           */
            /************************************************************/
            char ch;
            if (!disableWait)
            {
              printf("\n Dump shell ? (y/n) \n");
              STD(cin).get(ch); STD(cin).ignore();
            }
            else
            {
              ch = 'y';
            }
            if (ch == 'y' || ch == 'Y')
            {
              /**********************************************************/
              /* Set the triangulation (rendering) parameters           */
              /**********************************************************/
              wrTriangulationParams TriangulationParams;
              TriangulationParams.normalTolerance = 20;
              /**********************************************************/
              /* Render the shell                                       */
              /**********************************************************/
              BrepShellTracer(pRenderer, TriangulationParams);
              /**********************************************************/
              /* Render the silhouettes                                 */
              /**********************************************************/
              if (!disableWait)
              {
              printf("\n Dump silhouettes ? (y/n) \n");
              STD(cin).get(ch); STD(cin).ignore();
              }
              else
              {
                ch = 'y';
              }
              if (ch == 'y' || ch == 'Y')
              {
                BrepSilhouetteTracer(pRenderer, TriangulationParams);
              }
            }
          }
          else
          {
            printf("Not enough memory.\n");
          }

          delete pRenderer;
        }
      }
    }
    catch(const OdError_FileException &err)
    {
      wprintf(OD_T("File error : %ls\n"), err.description().c_str());
    }
    catch(const OdError &)
    {
      printf("Internal error\n");
    }

    /********************************************************************/
    /* Delete the converters                                            */
    /************************(*******************************************/
    for(OdUInt32 f = 0; f < out.size(); ++f)
      ABDeleteConverter(out[f]);
    
    /********************************************************************/
    /* Clear the pointers                                               */
    /************************(*******************************************/
    out.clear();

    /******************************************************************/
    /* Finalize ODA library                                           */
    /******************************************************************/
    odrxUninitialize();
  }
  if (!disableWait)
  {
    STD(cout) << "Press RETURN to exit..." << STD(endl);
    STD(cin).get();
  }

	return 0;
}

