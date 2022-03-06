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

#include "OdaCommon.h"
#include "StaticRxObject.h"
#include "RxDynamicModule.h"

#include "IfcCore.h"
#include "IfcExamplesCommon.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_)
  using namespace OdIfc;                                                             \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);                              \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);                           \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);                            \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);                              \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxThreadPoolService);                     \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxPropertiesModule);                      \
  ODRX_BEGIN_STATIC_MODULE_MAP()                                                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)               \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName, OdIfc2x3Module)                 \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName, OdIfc4Module)                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdThreadPoolModuleName, OdRxThreadPoolService)      \
    ODRX_DEFINE_STATIC_APPMODULE(RxPropertiesModuleName, OdRxPropertiesModule)       \
  ODRX_END_STATIC_MODULE_MAP()
#endif

#include <iostream>
#include <cstdlib>

class AbstractNotifier
{
public:

  virtual ~AbstractNotifier() {};

  virtual void onLevelBegin(const OdRxObject *inst) = 0;
  virtual void onLevelEnd(const OdRxObject *inst) = 0;
  virtual void onHierarchyAttributeFound(const OdRxObject *inst, OdRxMember *member) = 0;
  virtual void onHasRepresentation(const OdRxObject *inst, const OdRxObject *reprInst) = 0;
  virtual void onAttribute(const OdRxMember *member, const OdRxValue &rxVal) = 0;
};

class CDATreePrinter : public AbstractNotifier
{
  int m_level;

public:

  CDATreePrinter()
    : m_level(0)
  {}

  virtual void onLevelBegin(const OdRxObject *inst)
  {
    ++m_level;

    odPrintConsoleString(L"%sHierarchy level: %d\n", tabulation(m_level).c_str(), m_level);

    const OdString &className = inst->isA()->name();
    odPrintConsoleString(L"%sClass: %s\n", tabulation(m_level).c_str(), className.c_str());

    OdString entityName;

    OdRxPropertyPtr propName = OdRxMemberQueryEngine::theEngine()->find(inst, L"Name");
    if (!propName.isNull())
    {
      OdRxValue valName;
      (eOk == propName->getValue(inst, valName)) &&
        (valName >> entityName);
    }

    odPrintConsoleString(L"%sName: `%s`\n", tabulation(m_level).c_str(), entityName.c_str());
  }

  virtual void onLevelEnd(const OdRxObject *inst)
  {
    --m_level;
  }

  virtual void onHierarchyAttributeFound(const OdRxObject *inst, OdRxMember *member)
  {
    const OdString &propName = member->name();
    odPrintConsoleString(L"%sHierarchy property name: %s\n", tabulation(m_level).c_str(), propName.c_str());
  }

  virtual void onHasRepresentation(const OdRxObject *inst, const OdRxObject *reprInst)
  {
    const OdString &reprClassName = reprInst->isA()->name();
    odPrintConsoleString(L"%sCan be vectorized here (Representation: %s)\n", tabulation(m_level).c_str(), reprClassName.c_str());
    // vectorize(inst); // not reprInst, inst should be casted appropriately to OdGiDrawable/OdIfcEntity
  }

  virtual void onAttribute(const OdRxMember *member, const OdRxValue &rxVal)
  {
    OdString memberName = member->name();
    odPrintConsoleString(L"\n%s%s: ", tabulation(m_level).c_str(), memberName.c_str());

    const OdRxValueType &vt = rxVal.type();
    if (vt == OdRxValueType::Desc<OdDAIObjectId>::value())
    {
      OdDAIObjectId idVal = *rxvalue_cast<OdDAIObjectId>(&rxVal);
      odPrintConsoleString(L"#%ull", (OdUInt64)idVal.getHandle());
    }
    if (vt == OdRxValueType::Desc<OdAnsiString>::value())
    {
      OdAnsiString strVal = *rxvalue_cast<OdAnsiString>(&rxVal);
      odPrintConsoleString(L"'%hs'", strVal.c_str());
    }
    if (vt == OdRxValueType::Desc<OdString>::value())
    {
      OdString strVal = *rxvalue_cast<OdString>(&rxVal);
      odPrintConsoleString(L"'%s'", strVal.c_str());
    }
    if (vt == OdRxValueType::Desc<double>::value())
    {
      double dblVal = *rxvalue_cast<double>(&rxVal);
      odPrintConsoleString(L"%.4f", dblVal);
    }
    if (vt.isEnum())
    {
      OdAnsiString strVal;
      rxVal >> strVal;
      odPrintConsoleString(L"'%hs'", strVal.c_str());
    }
    // ...
  }

protected:

  OdString tabulation(int tab)
  {
    if (tab < 0)
      tab = 0;
    OdString res;
    while (tab > 0)
    {
      res += OD_T("  ");
      --tab;
    }
    return res;
  }

};

class CDAWalker
{
  AbstractNotifier *m_pNotifier;

public:

  CDAWalker(AbstractNotifier *notifier)
    : m_pNotifier(notifier)
  {}

  ~CDAWalker()
  {
    delete m_pNotifier;
  }

  void run(const OdRxObject *inst)
  {
    return walkCDA(inst);
  }

protected:

  void walkAttributes(const OdRxObject *inst)
  {
    OdRxMemberIteratorPtr memberIterator = OdRxMemberQueryEngine::theEngine()->newMemberIterator(inst);
    if (memberIterator)
    {
      OdUInt64 memberCount = memberIterator->size();
      for (; !memberIterator->done(); memberIterator->next())
      {
        OdRxMember *member = memberIterator->current();

        if (member->isKindOf(OdRxProperty::desc()))
        {
          //
          // Process single property
          //
          OdRxProperty *prop = OdRxProperty::cast(member); // dynamic_cast<OdRxProperty*>(member);

          OdRxValue rxVal;
          if (eOk == prop->getValue(inst, rxVal))
          {
            m_pNotifier->onAttribute(member, rxVal);
          }
        }
        else
          if (member->isKindOf(OdRxCollectionProperty::desc()))
          {
            //
            // Process collection
            //
            OdRxCollectionProperty *collection = dynamic_cast<OdRxCollectionProperty*>(member);
            OdRxValueIteratorPtr itValues = collection->newValueIterator(inst);

            if (!itValues.isNull())
            {
              for (; !itValues->done(); itValues->next())
              {
                OdRxValue rxVal = itValues->current();
                // Typed values extraction
              }
            }
          }
      }
    }
  }

  void walkCDA(const OdRxObject *inst)
  {
    if (m_pNotifier)
      m_pNotifier->onLevelBegin(inst);

    //walkAttributes(inst);

    //
    // Try to find attribute called Representation, if it isn't null, the instance can be vectorized.
    //
    OdRxMember *memRepr = OdRxMemberQueryEngine::theEngine()->find(inst, L"Representation");
    if (memRepr)
    {
      if (memRepr->isKindOf(OdRxProperty::desc()))
      {
        OdRxProperty *propRepr = OdRxProperty::cast(memRepr);

        OdRxValue idRepresentation;
        if (eOk == propRepr->getValue(inst, idRepresentation))
        {
          const IOdRxReferenceType *reference = idRepresentation.type().reference();
          if (reference)
          {
            OdRxObjectPtr reprInst = reference->dereference(idRepresentation, IOdRxReferenceType::kForRead);
            if (!reprInst.isNull())
            {
              if (m_pNotifier)
                m_pNotifier->onHasRepresentation(inst, reprInst);
            }
          }
        }
      }
    }

    //
    // Walk along all Rx Properties of instance and try to find Hierarchy Attribute
    //
    OdRxMemberIteratorPtr it = OdRxMemberQueryEngine::theEngine()->newMemberIterator(inst);
    for (; !it->done(); it->next())
    {
      OdRxMember *member = it->current();

      OdRxAttributeCollection &attrs = member->attributes();

      int numAttrs = attrs.count();
      for (int i = 0; i < numAttrs; ++i)
      {
        OdRxAttribute *attr = attrs.getAt(i);

        OdRxClass* pRx = attr->isA();
        if (pRx->isDerivedFrom(OdRxHierarchyLevelAttribute::desc()))
        {
          if (m_pNotifier)
            m_pNotifier->onHierarchyAttributeFound(inst, member);

          if (member->isKindOf(OdRxProperty::desc()))
          {
            OdRxProperty *prop = dynamic_cast<OdRxProperty*>(member);

            OdRxValue idHierarchy;
            if (eOk == prop->getValue(inst, idHierarchy))
            {
              const IOdRxReferenceType *reference = idHierarchy.type().reference();
              if (reference)
              {
                OdGiDrawablePtr pInst = reference->dereference(idHierarchy, IOdRxReferenceType::kForRead);
                walkCDA(pInst);
              }
            }
          }
          else
            if (member->isKindOf(OdRxCollectionProperty::desc()))
            {
              OdRxCollectionProperty *collection = dynamic_cast<OdRxCollectionProperty*>(member);
              OdRxValueIteratorPtr itValues = collection->newValueIterator(inst);

              if (!itValues.isNull())
                for (; !itValues->done(); itValues->next())
                {
                  OdRxValue treeNodeId = itValues->current();
                  const IOdRxReferenceType *reference = treeNodeId.type().reference();
                  if (reference)
                  {
                    OdGiDrawablePtr pInst = reference->dereference(treeNodeId, IOdRxReferenceType::kForRead);
                    walkCDA(pInst);
                  }
                }
            }
        }
      }
    }
    
    if (m_pNotifier)
      m_pNotifier->onLevelEnd(inst);
  }

};

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

#if defined(TARGET_OS_MAC) && !defined(__MACH__)
  argc = ccommand(&argv);
#endif

#ifdef _MSC_VER
  SetConsoleOutputCP(CP_UTF8);
#endif

  setlocale(LC_TIME, ""); // set current user locale (not OD_T("C")), for strftime

  /**********************************************************************/
  /* Create a Services object                                           */
  /**********************************************************************/
  OdStaticRxObject<MyServices> svcs;

  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nExIfcCDAWalker developed using %ls ver %ls", 
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
    odPrintConsoleString(L"\n\nusage: ExIfcCDAWalker <filename>");
    odPrintConsoleString(L"\n<filename> - input .ifc file\n");
    return nRes;
  }

#if !defined(_TOOLKIT_IN_DLL_) 
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA SDK                                                 */
  /**********************************************************************/
  odrxInitialize(&svcs);

  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize IfcCore                                                 */
  /**********************************************************************/
  odIfcInitialize(true /* CDA */, false /* No geometry calculation needed */);

  try
  {
    OdString ifcFileName(argv[1]);

    OdIfcFilePtr pIfcFile = svcs.createDatabase();
    OdResult res = pIfcFile->readFile(ifcFileName);

    if (res == eOk)
    {
      odPrintConsoleString(L"\nFile opened successfully.");
    }
    else
    {
      odPrintConsoleString(L"\nFile open error.");
    }

    odPrintConsoleString(L"\n");
    CDAWalker walker(new CDATreePrinter);
    walker.run(pIfcFile);

    std::cout << "Press any key.";
    getchar();
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
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  odIfcUninitialize();

  odDbRootUninitialize();
  /**********************************************************************/
  /* Uninitialize ODA SDK                                               */
  /**********************************************************************/
  odrxUninitialize();
  return nRes;
}
