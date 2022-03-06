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

#include "stdafx.h"

#include "PrcCommon.h"
#include "ExPrcElementDumperPE.h"

//----------------------------------------------------------
//
// OdPrcRxObjectDumperPE
//
//----------------------------------------------------------
ODRX_NO_CONS_DEFINE_MEMBERS( OdPrcRxObjectDumperPE, OdRxObject )

OdPrcRxObjectDumperPE::OdPrcRxObjectDumperPE()
{
}

OdPrcRxObjectDumperPE::~OdPrcRxObjectDumperPE()
{
}

void OdPrcRxObjectDumperPE::dump( OdRxObjectPtr /*pObj*/, OdExPrcDumper* /*pDumper*/ ) const
{
}

//----------------------------------------------------------
//
// OdPrcObjectDumperPE
//
//----------------------------------------------------------
ODRX_NO_CONS_DEFINE_MEMBERS( OdPrcObjectDumperPE, OdPrcRxObjectDumperPE )

OdPrcObjectDumperPE::OdPrcObjectDumperPE()
{
}

OdPrcObjectDumperPE::~OdPrcObjectDumperPE()
{
}

void OdPrcObjectDumperPE::dump( OdRxObjectPtr pObj, OdExPrcDumper* pDumper ) const
{
  dumpData(pObj, pDumper);
}

void OdPrcObjectDumperPE::dumpData( OdRxObjectPtr pObj, OdExPrcDumper* pDumper ) const
{
//  OdPrcElementPtr pElm = pObj;
  //pDumper->writeFieldValue( "ElementId", pElm->elementId().getHandle().ascii() );
  //pDumper->writeFieldValue( "OwnerId", pElm->ownerId().getHandle().ascii() );
}

OdString OdPrcObjectDumperPE::getName( OdRxObjectPtr pObj ) const
{
  OdString s;
  s.format(L"<%ls>", pObj->isA()->name().c_str());
  return s;
}

//OdPrcElementIteratorPtr OdPrcElementDumperPE::createIterator( OdPrcElementPtr pElm, bool /*atBeginning = true*/, bool /*skipDeleted = true*/ ) const
//{
//  return OdPrcElementIteratorPtr();
//}

//----------------------------------------------------------
//
// OdPrcDumper
//
//----------------------------------------------------------
void OdPrcDumper::init()
{
  OdPrcRxObjectDumperPE::rxInit();
  OdPrcObjectDumperPE::rxInit();

//  OdPrcElement::desc()->addX( OdPrcObjectDumperPE::desc(), &m_objectsDumper );
  OdPrcFile::desc()->addX( OdPrcObjectDumperPE::desc(), &m_databaseDumper );

  //OdPrcProxyElement::desc()->addX( OdPrcElementDumperPE::desc(), &m_proxyDumper );
  //OdPrcComplexProxyElement::desc()->addX( OdPrcElementDumperPE::desc(), &m_complexProxyDumper );
}


void OdPrcDumper::uninit()
{
  OdPrcFile::desc()->delX( OdPrcObjectDumperPE::desc() );

  //OdPrcProxyElement::desc()->delX( OdPrcElementDumperPE::desc() );
  //OdPrcComplexProxyElement::desc()->delX( OdPrcElementDumperPE::desc() );

//  OdPrcElement::desc()->delX( OdPrcObjectDumperPE::desc() );

  OdPrcObjectDumperPE::rxUninit();
  OdPrcRxObjectDumperPE::rxUninit();
}

//----------------------------------------------------------
//
// OdPrcFileDumperPE
//
//----------------------------------------------------------
void OdPrcFileDumperPE::dumpData( OdRxObjectPtr pObj, OdExPrcDumper* pDumper ) const
{
  OdPrcFilePtr pDb = pObj;

  //simple fields
//  pDumper->writeFieldValue( "Filename", pDb->getFilename() );
  //...
}

//----------------------------------------------------------
//
// OdPrcProxyElementDumperPE
//
//----------------------------------------------------------
#define DUMP_FIELD_OPTS(FdName) \
if (pProxy->get##FdName() != 0xffffffff) \
  pDumper->writeFieldValueHex( #FdName, pProxy->get##FdName() ); \
else \
  pDumper->writeFieldValue( #FdName, OdString(L"<null>") );

#define DUMP_FIELD_ELEMID_OPTS(FdName) \
  if ((OdUInt32)(pProxy->get##FdName().getHandle()) != 0xffffffff) \
  pDumper->writeFieldValueHex( #FdName, pProxy->get##FdName().getHandle() ); \
else \
  pDumper->writeFieldValue( #FdName, OdString(L"<null>") );

void OdPrcProxyElementDumperPE::dumpData( OdRxObjectPtr pObj, OdExPrcDumper* pDumper ) const
{
  OdPrcObjectDumperPE::dumpData(pObj, pDumper);
  /*OdPrcProxyElementPtr pProxy = pObj;
  pDumper->writeFieldValue( "Category", pProxy->getCategoryName() );

  pDumper->writeFieldValue( "IsGraphics", pProxy->isGraphics());
  if (pProxy->isGraphics())
  {
    pDumper->writeFieldValue( "Extents", pProxy->getExtents() );
  }
  OdString name;
  unsigned i;
  OdUInt32Array params = pProxy->getParams1();
  for (i = 0; i < params.size(); ++i)
  {
    name.format(L"RefType1 ID %d", i);
    pDumper->writeFieldValueHex(name, params[i]);
  }
  params = pProxy->getParams2();
  for (i = 0; i < params.size(); ++i)
  {
    name.format(L"RefType2 ID %d", i);
    pDumper->writeFieldValueHex(name, params[i]);
  }
  OdUInt16Array paramsInt16 = pProxy->getParams3();
  for (i = 0; i < paramsInt16.size(); ++i)
  {
    name.format(L"RefType3 ID %d", i);
    pDumper->writeFieldValueHex(name, paramsInt16[i]);
  }
  params = pProxy->getParams4();
  for (i = 0; i < params.size(); ++i)
  {
    name.format(L"RefType4 ID %d", i);
    pDumper->writeFieldValueHex(name, params[i]);
  }
  params = pProxy->getParams5();
  for (i = 0; i < params.size(); ++i)
  {
    name.format(L"RefType5 ID %d", i);
    pDumper->writeFieldValueHex(name, params[i]);
  }
  params = pProxy->getParams6();
  for (i = 0; i < params.size(); ++i)
  {
    name.format(L"RefType6 ID %d", i);
    pDumper->writeFieldValueHex(name, params[i]);
  }

  DUMP_FIELD_OPTS(FamilyId)
  DUMP_FIELD_OPTS(GroupTypeId)
  DUMP_FIELD_OPTS(ViewPlanId)
  DUMP_FIELD_OPTS(PhaseCreatedId)
  DUMP_FIELD_OPTS(PhaseDemolishedId)
  DUMP_FIELD_OPTS(DesignOptionId)


  if (!pProxy->getText().isEmpty())
  {
    pDumper->writeFieldValue("Text", pProxy->getText());
    if (!pProxy->getFontName().isEmpty())
    {
      pDumper->writeFieldValue("Font", pProxy->getFontName());
    }
    pDumper->writeFieldValue("TextPosition", pProxy->getTextPosition());
  }

  OdBinaryData data;
  for (OdUInt8 i = 0; i < 3; ++i)
  {
    pProxy->getData(i, data);
    name.format(L"Chunk %d Data", i);
    pDumper->writeFieldValue( name, data );
  }*/
}

//OdPrcElementIteratorPtr OdPrcComplexProxyElementDumperPE::createIterator( OdPrcElementPtr pElm, bool atBeginning, bool skipDeleted) const
//{
//  OdPrcComplexProxyElementPtr pComplElm = pElm;
//  return pComplElm->createIterator( atBeginning, skipDeleted );
//}
