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

#include "ObjProperties.h"
using namespace OBJToolkit;

/**
Define array of the UI names of the properties
*/

const OdChar* objPropUINames[] = {
  OD_T("Objects"),
  OD_T("Materials"),
};

/** \details
Protocol extension to handle loading strings from resources (CDA properties)
*/

ODRX_NO_CONS_DEFINE_MEMBERS(OdTvVisualizeObjFilerPropResourceLoaderPE, OdRxResourceLoader);

OdResult OdTvVisualizeObjFilerPropResourceLoaderPE::subLoadString(unsigned int id, unsigned int sourceHint, OdString& result)
{
  result = objPropUINames[id];
  return eOk;
}

/** \details
Just for more accurate working with PE
*/

ODRX_NO_CONS_DEFINE_MEMBERS(OdTvVisualizeObjFilerPropertyWithResLoader, OdRxProperty);


/** \details
Implementation for the database properties
*/
OdResult OdObjDbGroupsProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  if (pO == NULL)
    return eNullPtr;

  OdObjDbPtr pDb = OdObjDb::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  value = OD_T("Obj database");

  return eOk;
}

OdResult OdObjDbObjectsNumProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  if (pO == NULL)
    return eNullPtr;

  OdObjDbPtr pDb = OdObjDb::cast(pO);
  
  if (pDb.isNull())
    return eNotApplicable;

  int N = 0;
  OdObjGroupIteratorPtr itGroups = pDb->createGroupsIterator();
  while (!itGroups->done())
  {
    ++N;
    itGroups->step();
  }
 
  value = N - 1; // we want to ignore 'default' empty group

  return eOk;
}

OdResult OdObjDbMaterialsNumProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  if (pO == NULL)
    return eNullPtr;

  OdObjDbPtr pDb = OdObjDb::cast(pO);

  if (pDb.isNull())
    return eNotApplicable;

  value = 0;
  OdMtlDbPtr pMtlDb = pDb->getMtlDb();
  if (!pMtlDb.isNull())
    value = pMtlDb->getMaterialsCount();

  return eOk;
}

void createOdObjDatabaseProperties(OdArray<OdRxMemberPtr>& properties, OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdObjDbGroupsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdObjDbObjectsNumProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdObjDbMaterialsNumProperty::createObject(b.owner()));
  b.add(properties.last());
}
