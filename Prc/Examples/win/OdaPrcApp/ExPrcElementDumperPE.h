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

#ifndef _EX_PRCELEMENTDUMPERPE_H_
#define _EX_PRCELEMENTDUMPERPE_H_

#include "PrcCommon.h"
#include "RxObjectImpl.h"
#include "PrcFile.h"
#include "ExPrcDumper.h"

class OdPrcRxObjectDumperPE : public OdRxObjectImpl<OdRxObject>
{
public:
  ODRX_DECLARE_MEMBERS( OdPrcRxObjectDumperPE );

  OdPrcRxObjectDumperPE();
  virtual ~OdPrcRxObjectDumperPE();
  virtual void dump( OdRxObjectPtr pObj, OdExPrcDumper* pDumper ) const;
};

typedef OdSmartPtr< OdPrcRxObjectDumperPE > OdPrcRxObjectDumperPEPtr;


class OdPrcObjectDumperPE : public OdPrcRxObjectDumperPE
{
public:
  ODRX_DECLARE_MEMBERS( OdPrcObjectDumperPE );

  OdPrcObjectDumperPE();
  virtual ~OdPrcObjectDumperPE();

  virtual void dump( OdRxObjectPtr pObj, OdExPrcDumper* pDumper ) const;

  virtual OdString getName( OdRxObjectPtr pObj ) const;

  //virtual OdPrcElementIteratorPtr createIterator( OdPrcElementPtr pElm, bool atBeginning = true, bool skipDeleted = true ) const;

protected:
  virtual void dumpData( OdRxObjectPtr pObj, OdExPrcDumper* pDumper ) const;
};

typedef OdSmartPtr< OdPrcObjectDumperPE > OdPrcObjectDumperPEPtr;

class OdPrcFileDumperPE : public OdPrcObjectDumperPE
{
public:
  virtual void dumpData( OdRxObjectPtr pObj, OdExPrcDumper* pDumper ) const;
};

class OdPrcProxyElementDumperPE : public OdPrcObjectDumperPE
{
public:
  virtual void dumpData( OdRxObjectPtr pObj, OdExPrcDumper* pDumper ) const;
};

//class OdPrcComplexProxyElementDumperPE : public OdPrcProxyElementDumperPE
//{
//public:
//  virtual OdPrcElementIteratorPtr createIterator( OdPrcElementPtr pElm, bool atBeginning = true, bool skipDeleted = true ) const;
//};

//
// OdPrcDumper
//
class OdPrcDumper
{
public:
  void init();
  void uninit();

private:
  OdPrcObjectDumperPE                    m_objectsDumper;
  OdPrcFileDumperPE                  m_databaseDumper;

  OdPrcProxyElementDumperPE              m_proxyDumper;
  //OdPrcComplexProxyElementDumperPE       m_complexProxyDumper;
};

#endif // _EX_PRCELEMENTDUMPERPE_H_
