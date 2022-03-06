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

#include "PrcExamplesCommon.h"
#include "OdModuleNames.h"
#include "PrcDumpModule.h"

// Define module map for statically linked modules:
#if !defined(_TOOLKIT_IN_DLL_) 

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcDumpModule);

ODRX_BEGIN_STATIC_MODULE_MAP()
  ODRX_DEFINE_STATIC_APPLICATION(OdPrcModuleName, OdPrcModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdPrcDumpModuleName, OdPrcDumpModule)
ODRX_END_STATIC_MODULE_MAP()

#endif

class OdPrcListenerImpl : public OdPrcListener
{
  mutable OdArray<OdPrcObjectId> m_childs;
public:
  OdPrcListenerImpl()
  {
  }
  const OdArray<OdPrcObjectId> &childs()
  {
    return m_childs;
  }
  virtual void dumpInt8(const OdChar *pName, OdInt8 value) const
  {
    odPrintConsoleString(L"%ls = %d\n", pName, value);
  }
  virtual void dumpInt32(const OdChar *pName, OdInt32 value) const
  {
    odPrintConsoleString(L"%ls = %d\n", pName, value);
  }
  virtual void dumpUInt8(const OdChar *pName, OdUInt8 value) const
  {
    odPrintConsoleString(L"%ls = %u\n", pName, value);
  }
  virtual void dumpUInt16(const OdChar *pName, OdUInt16 value) const
  {
    odPrintConsoleString(L"%ls = %u\n", pName, value);
  }
  virtual void dumpUInt32(const OdChar *pName, OdUInt32 value) const
  {
    odPrintConsoleString(L"%ls = %u\n", pName, value);
  }
  virtual void dumpUInt32Hex(const OdChar *pName, OdUInt32 value) const
  {
    odPrintConsoleString(L"%ls = 0x%08X\n", pName, value);
  }
  virtual void dumpUniqueId(const OdChar *pName, OdPrcUniqueId value) const
  {
    OdUInt32 id0,id1,id2,id3;
    value.getID(id0,id1,id2,id3);
    odPrintConsoleString(L"%ls = %u, %u, %u, %u\n", pName, id0, id1, id2, id3);
  }
  virtual void dumpObjectId(const OdChar *pName, OdPrcObjectId value) const
  {
    m_childs.push_back(value);
    odPrintConsoleString(L"%ls = %s\n", pName, value.getHandle().ascii().c_str());
  }
  virtual void dumpUncompressedBlock(const OdChar *pName, OdBinaryData value) const
  {
    odPrintConsoleString(L"%ls = %u; Size = %u\n", pName, value.asArrayPtr(), value.size());
  }
  virtual void dumpBoolean(const OdChar *pName, OdBool value) const
  {
    OdString val;
    val.format(value ? L"true" : L"false");
    odPrintConsoleString(L"%ls: %ls\n", pName, val.c_str());
  }
  virtual void dumpDouble(const OdChar *pName, OdDouble value) const
  {
    odPrintConsoleString(L"%ls = %f\n", pName, value);
  }
  virtual void dumpFloat(const OdChar *pName, float value) const
  {
    odPrintConsoleString(L"%ls = %f\n", pName, value);
  }
  virtual void dumpBits(const OdChar *pName, const OdBitBinaryData &data) const
  {
    odPrintConsoleString(L"%ls: numBits = %u\n", pName, data.getBitSize());
  }
  virtual void dumpAnsiString(const OdChar *pName, OdAnsiString str) const
  {
    odPrintConsoleString(L"%ls: %ls\n", pName, OdString(str).c_str());
  }
  virtual void dumpString(const OdChar *pName, OdString str) const
  {
    odPrintConsoleString(L"%ls: %ls\n", pName, str.c_str());
  }
  virtual void dumpCharArray(const OdChar *pName, OdArray<char> str) const
  {
    odPrintConsoleString(L"%ls: %ls\n", pName ,str.asArrayPtr());
  }
};

OdPrcObjectId getObjectId(const OdRxObject *pObj)
{
  OdPrcReferencedBasePtr pRef = OdPrcReferencedBase::cast(pObj);
  if (!pRef.isNull())
  {
    return pRef->objectId();
  }

  OdPrcBodyPtr pBody = OdPrcBody::cast(pObj);
  if (!pBody.isNull())
  {
    return pBody->objectId();
  }

  OdPrcFileStructurePtr pFS = OdPrcFileStructure::cast(pObj);
  if (!pFS.isNull())
  {
    return pFS->objectId();
  }

  return OdPrcObjectId();
}

void addChilds(const OdRxObject *pObj, OdUInt32 childLevelCounter)
{
//   if (childLevelCounter > 2)
//   {
//     return;
//   }

  OdPrcListenerImpl pListener;
  OdPrcEntity_Dumper *pDumper = OdPrcEntity_Dumper::cast(pObj);
  if (pDumper != 0)
  {
    OdString tmp = pObj->isA()->name();
    odPrintConsoleString(L"\n\t\t%ls\n", tmp.c_str());

    pDumper->dump(pObj, &pListener);

    OdPrcObjectId parentId = getObjectId(pObj);
    const OdArray<OdPrcObjectId> &childs = pListener.childs();
    for(OdUInt32 i=0; i<childs.size(); ++i)
    {
      OdPrcObjectId id = childs[i];
      if (!id.isNull() && id != parentId)
      {
        OdPrcObjectPtr pObj = id.safeOpenObject(kForRead);
        //OdString tmp = pObj->isA()->name() + " (" + id.getHandle().ascii() + ")";
        //odPrintConsoleString(L"\t\t%ls\n", tmp.c_str());
        addChilds(pObj,childLevelCounter + 1);
      }
    }

    // Special processing for subentities without objectId
    {
      OdRxObjectPtrArray subs = pDumper->subElements(pObj);
      for(OdUInt32 f=0; f<subs.size(); ++f)
      {
        //OdString tmp = subs[f]->isA()->name();
        //odPrintConsoleString(L"\t\t%ls\n", tmp.c_str());
        addChilds(subs[f],childLevelCounter + 1);
      }
    }
  }
}

void dump(const OdPrcFile *pFile)
{
  OdSmartPtr<OdPrcEntity_Dumper> pEntDumper = pFile;
  OdPrcListenerImpl listener;

  addChilds(pFile,0);
  
}


/************************************************************************/
/* Main                                                                 */
/************************************************************************/
#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  int nRes = 0; // Return value for main

  /**********************************************************************/
  /* Overload OdTimeStamp::getLocalTime internal implementation         */
  /**********************************************************************/
  g_pLocalTimeFunc = getLocalTime;

  /**********************************************************************/
  /* Set customized assert function                                     */
  /**********************************************************************/
  odSetAssertFunc(MyAssert);

#if defined(TARGET_OS_MAC) && !defined(__MACH__)
  argc = ccommand(&argv);
#endif

  setlocale(LC_TIME, ""); // set current user locale (not OD_T("C")), for strftime

  /**********************************************************************/
  /* Create a Services object                                           */
  /**********************************************************************/
  OdStaticRxObject<MyServices> svcs;

  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nOdPrcReadEx developed using %ls ver %ls", 
    svcs.product().c_str(), svcs.versionString().c_str());

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  bool bInvalidArgs = (argc != 2);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }
  if (bInvalidArgs)
  {
    odPrintConsoleString(L"\n\nusage: OdPrcReadEx <filename>");
    odPrintConsoleString(L"\n<filename> - input .prc file\n");

    return nRes;
  }

#if !defined(_TOOLKIT_IN_DLL_) 
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA Platform                                            */
  /**********************************************************************/
  odrxInitialize(&svcs);

  ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);
  ::odrxDynamicLinker()->loadApp(OdPrcDumpModuleName, false);

  try
  {
    OdString prcName(argv[1]);
    OdPrcFilePtr pFile = svcs.readFile(prcName);
    dump(pFile);
  }
  catch(OdError& e)
  {
    odPrintConsoleString(L"\n\nError: %ls", e.description().c_str());
    nRes = -1;
  }
  catch(...)
  {
    odPrintConsoleString(L"\n\nUnexpected error.");
    nRes = -1;
    throw;
  }

  /**********************************************************************/
  /* Uninitialize ODA Platform                                          */
  /**********************************************************************/
  odrxUninitialize();
  return nRes;
}
