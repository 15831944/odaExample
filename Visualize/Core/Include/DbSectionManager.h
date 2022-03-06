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


#ifndef _DbSectionManager_h_Included_
#define _DbSectionManager_h_Included_

#include "DbSection.h"
#include "TD_PackPush.h"


class OdTvDbSection;
class OdTvDbSectionManagerIterator;
typedef OdSmartPtr<OdTvDbSectionManagerIterator> OdTvDbSectionManagerIteratorPtr;


//*************************************************************************
// OdTvDbSectionManager
//*************************************************************************

/** \details

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbSectionManager : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbSectionManager);

  OdTvDbObjectId getSection(const OdString& pszName ) const;
  OdTvDbSectionPtr getSection(const OdString& pszName, OdDb::OpenMode mode) const;
  OdTvDbObjectId getLiveSection() const;
  OdTvDbSectionPtr getLiveSection(OdDb::OpenMode mode) const;
  int numSections() const;
  OdTvDbSectionManagerIteratorPtr newIterator () const;
  OdResult getUniqueSectionName(const OdString& pszBaseName, 
    OdString& pszUniqueName) const;

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  virtual OdResult subGetClassID(
    void* pClsid) const;
protected:
  OdTvDbSectionManager();
};

typedef OdSmartPtr<OdTvDbSectionManager> OdTvDbSectionManagerPtr;

//*************************************************************************
// OdTvDbSectionManagerIterator
//*************************************************************************

class OdTvDbSectionManagerIteratorImpl;

/** \details

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbSectionManagerIterator : public OdRxObject
{
  OdTvDbSectionManagerIteratorImpl* m_pImpl;
  friend class OdTvDbSectionManager;
public:
  ODRX_DECLARE_MEMBERS(OdTvDbSectionManagerIterator);
  OdTvDbSectionManagerIterator();
  ~OdTvDbSectionManagerIterator();

  void  start();
  void  step();
  bool  done() const;

  OdTvDbObjectId getSection() const;
  OdTvDbSectionPtr getSection(OdDb::OpenMode openMode) const;
};

#include "TD_PackPop.h"
#endif
