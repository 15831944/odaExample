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
#include "DbUserIO.h"
#include "DbCommandContext.h"

#include "Gs/Gs.h"
#include "DbPolyline.h"
#include "DbBlockTableRecord.h"
#include "DbViewportTable.h"
#include "DbDictionary.h"
#include "DbDictionaryVar.h"

#include "DbSortentsTable.h"
#include "DbBlockTableRecord.h"
#include "DbLayout.h"

#include "DbGeoData.h"
#include "DbGeoMap.h"
#include "OdDbGeoCoordinateSystem.h"
#include "OdDbGeoDataDrawingPE.h"

OdDbObjectId getActiveViewportIdForGeoMap(const OdDbDatabase * pDb)
{
  if (pDb->getTILEMODE())
  {
    OdDbViewportTablePtr pVt = pDb->getViewportTableId().openObject();
    return pVt->getActiveViewportId();
  }

  OdDbBlockTableRecordPtr pPS = pDb->getPaperSpaceId().openObject();
  OdDbLayoutPtr pLayout = pPS->getLayoutId().openObject();
  if (pLayout->overallVportId() == pLayout->activeViewportId())
  {
    return OdDbObjectId::kNull;
  }
  return pLayout->activeViewportId();
}

void setGeoDataValues(OdDbDatabase* pDb, OdDb::UnitsValue eUnits, const OdGePoint3d& ptGeoRSS, const OdGePoint3d& ptDesign, double dNorthDirectionRad, const OdString& sCSId)
{
  OdString sOldCSId;
  OdDbGeoDataPtr pGeoData;
  OdDbObjectId objIdGeoData;
  oddbGetGeoDataObjId(pDb, objIdGeoData);
  if (!objIdGeoData.isNull())
  {
    pGeoData = objIdGeoData.openObject(OdDb::kForWrite);
    OdDbGeoCoordinateSystemPtr pCS;
    if (eOk == OdDbGeoCoordinateSystem::create(pGeoData->coordinateSystem(), pCS) && !pCS.isNull())
    {
      pCS->getId(sOldCSId);
    }
  }
  else
  {
    pGeoData = OdDbGeoData::createObject();
    pGeoData->setBlockTableRecordId(pDb->getModelSpaceId());
    OdDbObjectId objId;
    ODA_VERIFY(eOk == pGeoData->postToDb(objId));
  }

  if (sOldCSId.compare(sCSId))
  {
    ODA_VERIFY(eOk == pGeoData->setCoordinateSystem(sCSId));
  }

  pGeoData->setCoordinateType(OdDbGeoData::kCoordTypLocal);
  pGeoData->setHorizontalUnits(eUnits);
  pGeoData->setVerticalUnits(eUnits);
  pGeoData->setDesignPoint(ptDesign);
  pGeoData->setUpDirection(OdGeVector3d::kZAxis);

  OdGeVector2d vNorthDirection = OdGeVector2d::kXAxis;
  vNorthDirection.rotateBy(dNorthDirectionRad);
  pGeoData->setNorthDirectionVector(vNorthDirection);

  OdGePoint3d ptReference;
  OdDbGeoCoordinateSystemTransformer::transformPoint(L"LL84", sCSId, OdGePoint3d(ptGeoRSS.y, ptGeoRSS.x, ptGeoRSS.z), ptReference);
  pGeoData->setReferencePoint(ptReference);
  pGeoData->setDoSeaLevelCorrection(false);
  pGeoData->setScaleEstimationMethod(OdDbGeoData::kScaleEstMethodUnity);

  double dEccentricity = 0.08181919092890674;
  OdDbGeoEllipsoid elipsoid;
  OdDbGeoCoordinateSystemPtr pCS;
  OdDbGeoCoordinateSystem::create(sCSId, pCS);
  if (!pCS.isNull() && eOk == pCS->getEllipsoid(elipsoid) && !elipsoid.id.isEmpty())
  {
    dEccentricity = elipsoid.eccentricity;
  }
  double dRadius = 6378137.;
  double dSinLat = sin(ptReference.y);
  double dCoordinateProjectionRadius = dRadius * (1 - dEccentricity * dEccentricity) / pow(1 - dEccentricity * dEccentricity * dSinLat * dSinLat, 1.5);
  pGeoData->setCoordinateProjectionRadius(dCoordinateProjectionRadius);

  pGeoData->setGeoRSSTag(OdString().format(L"<georss:point>%f %f</georss:point>", ptGeoRSS.x, ptGeoRSS.y));

  //database fields update:
  pDb->setLONGITUDE(ptGeoRSS.y);
  pDb->setLATITUDE(ptGeoRSS.x);
  //pDb->setELEVATION(ptGeoRSS.z);
  pDb->setNORTHDIRECTION(dNorthDirectionRad);

  pGeoData->updateTransformationMatrix();
}

//this function describes limitation for GeoMap creation:
bool validateGeoDataSettings(OdDbDatabase* pDb, OdDbUserIO * pIO)
{
  OdDbObjectId objIdGeoData;
  oddbGetGeoDataObjId(pDb, objIdGeoData);
  if (objIdGeoData.isNull())
  {
    pIO->putString("Command Error: There is no GeoData in drawing, specify it with GEO command.");
    return false;
  }
  return true;
}

void _Geo_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();

  //Lat, Lon, Elevation
  OdGePoint3d ptDefaultGeoRSS(pDb->getLATITUDE(), pDb->getLONGITUDE(), pDb->getELEVATION());
  OdGePoint3d ptGeoRSS = pIO->getPoint(OdString().format(L"Set GeoRSS (Lat, Lon, Elevation) <%f, %f, %f>:", ptDefaultGeoRSS.x, ptDefaultGeoRSS.y, ptDefaultGeoRSS.z), OdEd::kInpDefault, &ptDefaultGeoRSS);

  OdArray<OdDbGeoCoordinateSystemPtr> allCoordSys;
  if (eOk != OdDbGeoCoordinateSystem::createAll(OdGePoint3d(ptGeoRSS.y, ptGeoRSS.x, ptGeoRSS.z), allCoordSys) || !allCoordSys.size())
  {
    pIO->putString("Command Error: Can't create Coordinate System by current GeoRSS.");
    return;
  }

  {
    //dump supported Coordinate Systems for current GeoRSS:
    OdString sName;
    OdDbGeoCoordinateSystem::Unit eUnit = OdDbGeoCoordinateSystem::kUnitUnknown;
    int nEpsgCode = 0;
    OdDbGeoDatum datum;
    OdDbGeoEllipsoid ellipsoid;
    OdString sResult;
    pIO->putString(L"================================");
    pIO->putString(L"Name, Reference, Unit, EPSG code");
    for (OdUInt32 i = 0; i < allCoordSys.size(); ++i)
    {
      OdDbGeoCoordinateSystemPtr pCS = allCoordSys[i];
      if (eOk == pCS->getId(sName))
      {
        sResult = sName;
        sResult += ", ";
        sResult += (eOk == pCS->getDatum(datum) && !datum.id.isEmpty()) ? datum.id : (eOk == pCS->getEllipsoid(ellipsoid) && !ellipsoid.id.isEmpty()) ? ellipsoid.id : L"-";
        sResult += ", ";
        sResult += (eOk == pCS->getUnit(eUnit)) ? OdDbGeoCoordinateSystem::unitNameToString(eUnit) : L"-";
        sResult += ", ";
        sResult += (eOk == pCS->getEpsgCode(nEpsgCode) && nEpsgCode != 0) ? OdString().format(L"%d", nEpsgCode) : L"-";
        pIO->putString(sResult);
      }
    }
    pIO->putString(L"================================");
  }

  //pDb->setTIMEZONE(); // TODO: Do we need this?

  OdString sCSId = pIO->getString("Specify Coordinate System name <WORLD-MERCATOR>:", OdEd::kInpDefault, L"WORLD-MERCATOR");

  int nDefUnitsVal;
  {
    OdDbGeoCoordinateSystemPtr pCS;
    OdDbGeoCoordinateSystem::create(sCSId, pCS);
    if (eOk != OdDbGeoCoordinateSystem::create(sCSId, pCS) || pCS.isNull())
    {
      pIO->putString("Command Error: invalid coordinate system name.");
      return;
    }
    else
    {
      OdDb::UnitsValue eDefUnits;
      pCS->getUnit(eDefUnits);
      switch (eDefUnits)
      {
        case OdDb::kUnitsInches: nDefUnitsVal = 1; break;
        case OdDb::kUnitsFeet: nDefUnitsVal = 2; break;
        case OdDb::kUnitsMiles: nDefUnitsVal = 3; break;
        case OdDb::kUnitsMillimeters: nDefUnitsVal = 4; break;
        case OdDb::kUnitsCentimeters: nDefUnitsVal = 5; break;
        case OdDb::kUnitsMeters: nDefUnitsVal = 6; break;
        case OdDb::kUnitsKilometers: nDefUnitsVal = 7; break;
        case OdDb::kUnitsYards: nDefUnitsVal = 8; break;
        case OdDb::kUnitsDecimeters: nDefUnitsVal = 9; break;
        case OdDb::kUnitsDekameters: nDefUnitsVal = 10; break;
        case OdDb::kUnitsHectometers: nDefUnitsVal = 11; break;
        case OdDb::kUnitsUSSurveyFeet: nDefUnitsVal = 12; break;
        default: nDefUnitsVal = 6; break;
      }
    }
  }

  pIO->putString(L"================================");
  pIO->putString("Index, Drawing Units\n1) Inches\n2) Feet\n3) Miles\n4) Millimeters\n5) Centimeters\n6) Meters\n7) Kilometers\n8) Yards\n9) Decimeters\n10) Dekameters\n11) Hectometers\n12) US Survey Feet");
  pIO->putString(L"================================");
  OdUInt32 nUnitType = pIO->getInt(OdString().format(L"Select Drawing Units <%d>:", nDefUnitsVal), OdEd::kInpDefault, nDefUnitsVal);

  OdDb::UnitsValue eUnits = OdDb::kUnitsMillimeters;
  switch (nUnitType)
  {
    case 1: eUnits = OdDb::kUnitsInches; break;
    case 2: eUnits = OdDb::kUnitsFeet; break;
    case 3: eUnits = OdDb::kUnitsMiles; break;
    case 4: eUnits = OdDb::kUnitsMillimeters; break;
    case 5: eUnits = OdDb::kUnitsCentimeters; break;
    case 6: eUnits = OdDb::kUnitsMeters; break;
    case 7: eUnits = OdDb::kUnitsKilometers; break;
    case 8: eUnits = OdDb::kUnitsYards; break;
    case 9: eUnits = OdDb::kUnitsDecimeters; break;
    case 10: eUnits = OdDb::kUnitsDekameters; break;
    case 11: eUnits = OdDb::kUnitsHectometers; break;
    case 12: eUnits = OdDb::kUnitsUSSurveyFeet; break;
    default: eUnits = OdDb::kUnitsMeters; break;
  }

  OdGePoint3d ptDesign = pIO->getPoint(OdString().format(L"Specify design point <0., 0., 0.>:"), OdEd::kInpDefault, &OdGePoint3d::kOrigin);

  double dNorthDirectionRad = pIO->getAngle(L"Specify the north direction angle <90>:", OdEd::kInpDefault, OdaToRadian(90.));
  setGeoDataValues(pDb, eUnits, ptGeoRSS, ptDesign, dNorthDirectionRad, sCSId);
}

void _GeoRemove_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();
  OdUInt32 nKeyword = pIO->getKeyword(
    L"Delete geodata from file [Yes/No] ",
    L"Yes No", 1
  );
  if (0 == nKeyword)
  {
    OdDbObjectId objIdGeoData;
    oddbGetGeoDataObjId(pDb, objIdGeoData);
    if (!objIdGeoData.isNull())
    {
      OdDbGeoDataPtr pOldGeoData = objIdGeoData.openObject(OdDb::kForWrite);
      pOldGeoData->eraseFromDb();
    }
  }
}

void _GeoReorientMarker_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();

  OdDbObjectId objIdGeoData;
  if (eOk != oddbGetGeoDataObjId(pDb, objIdGeoData) || objIdGeoData.isNull())
  {
    pIO->putString("Command Error: There is no GeoData in drawing, specify it with GEO command.");
    return;
  }

  OdDbGeoDataPtr pGeoData = objIdGeoData.openObject(OdDb::kForWrite);
  OdGePoint3d ptDesignCurrent = pGeoData->designPoint();
  OdGePoint3d ptDesign = pIO->getPoint(L"Select a point for the location:", OdEd::kInpDefault, &ptDesignCurrent);
  double dNorthDirectionRad = pIO->getAngle(L"Specify the north direction angle:", OdEd::kInpDefault, pGeoData->northDirection());
  OdString sCSId;
  OdDbGeoCoordinateSystemPtr pCS;
  if (eOk == OdDbGeoCoordinateSystem::create(pGeoData->coordinateSystem(), pCS) && !pCS.isNull())
  {
    pCS->getId(sCSId);
  }
  OdGePoint3d ptGeoRSS(pDb->getLATITUDE(), pDb->getLONGITUDE(), pDb->getELEVATION());
  setGeoDataValues(pDb, pGeoData->horizontalUnits(), ptGeoRSS, ptDesign, dNorthDirectionRad, sCSId);
}

void _GeoMapImageUpdate_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();

  if (!validateGeoDataSettings(pDb, pIO))
  {
    return;
  }

  OdDbSelectionSetPtr pSSet = pIO->select(L"Select map image(s) to update:", OdEd::kSelDefault);
  OdUInt32 nKeyword = pIO->getKeyword(
    L"Enter action [Optimize/Reload] ",
    L"Optimize Reload", 1
    );

  bool bMod;
  switch (nKeyword)
  {
  case 0:
    bMod = true;
    break;
  case 1:
  default:
    bMod = false;
    break;
  }

  if (pSSet->numEntities())
  {
    OdDbSelectionSetIteratorPtr pIter = pSSet->newIterator();

    pDb->startTransaction();
    while (!pIter->done())
    {
      OdDbObjectId objId = pIter->objectId();
      OdDbGeoMapPtr pEnt = OdDbGeoMap::cast(objId.openObject(OdDb::kForWrite));
      if (!pEnt.isNull())
      {
        pEnt->updateMapImage(bMod);
      }
      pIter->next();
    }
    pDb->endTransaction();
  }
}

void _GeoMapImageSetResolution_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();

  if (!validateGeoDataSettings(pDb, pIO))
  {
    return;
  }

  OdDbSelectionSetPtr pSSet = pIO->select(L"Select map image(s) to change their resolution:", OdEd::kSelDefault);
  OdUInt32 nKeyword = pIO->getKeyword(
    L"Enter resolution [Cource/Optimal/Fine/VeryFine] ",
    L"Cource Optimal Fine VeryFine", 1
    );

  int nResolution;
  switch(nKeyword)
  {
  case 0:
    nResolution = kCoarse;
    break;
  case 2:
    nResolution = kFine;
    break;
  case 3:
    nResolution = kFiner;
    break;
  case 1:
  default:
    nResolution = kOptimal;
    break;
  }

  if (pSSet->numEntities())
  {
    OdDbSelectionSetIteratorPtr pIter = pSSet->newIterator();

    pDb->startTransaction();
    while (!pIter->done())
    {
      OdDbObjectId objId = pIter->objectId();
      OdDbGeoMapPtr pEnt = OdDbGeoMap::cast(objId.openObject(OdDb::kForWrite));
      if (!pEnt.isNull())
      {
        pEnt->setResolution(OdGeoMapResolution(nResolution));
        pEnt->updateMapImage();
      }
      pIter->next();
    }
    pDb->endTransaction();
  }
}

void _GeoMapImageSetMapType_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();

  if (!validateGeoDataSettings(pDb, pIO))
  {
    return;
  }

  OdDbSelectionSetPtr pSSet = pIO->select(L"Select map image(s) to change their type:", OdEd::kSelDefault);
  OdUInt32 nKeyword = pIO->getKeyword(
    L"Enter map type [Aerial/Road/Hybrid] ",
    L"Aerial Road Hybrid", 0
    );

  int nType;
  switch(nKeyword)
  {
  case 1:
    nType = kRoad;
    break;
  case 2:
    nType = kHybrid;
    break;
  case 0:
  default:  
    nType = kAerial;
    break;
  }

  if (pSSet->numEntities())
  {
    OdDbSelectionSetIteratorPtr pIter = pSSet->newIterator();

    pDb->startTransaction();
    while (!pIter->done())
    {
      OdDbObjectId objId = pIter->objectId();
      OdDbGeoMapPtr pEnt = OdDbGeoMap::cast(objId.openObject(OdDb::kForWrite));
      if (!pEnt.isNull())
      {
        pEnt->setMapType(OdGeoMapType(nType));
        pEnt->updateMapImage();
      }
      pIter->next();
    }
    pDb->endTransaction();
  }
}

void _GeoMapImage_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

  if (!validateGeoDataSettings(pDb, pIO))
  {
    return;
  }

  OdDbObjectId viewportId = getActiveViewportIdForGeoMap(pDb);
  if (viewportId.isNull())
  {
    pIO->putString("Command Error: Can't create geomap in overall viewport.");
    return;
  }

  OdDbObjectPtr pVp = viewportId.openObject();
  OdDbDictionaryPtr pExtDictionary = pVp->extensionDictionary().openObject();
  OdDbDictionaryVarPtr pDictionaryVar;
  if (pExtDictionary.get())
  {
    OdDbDictionaryPtr pExtVariableDictionary = pExtDictionary->getAt(L"AcDbVariableDictionary").openObject();
    if (pExtVariableDictionary.get())
    {
      pDictionaryVar = pExtVariableDictionary->getAt(L"GEOMAPMODE").openObject();
    }
  }
  if (pDictionaryVar.isNull())
  {
    pIO->putString("Command Error: GeoMap type is set as kNoMap, specify it with GEOMAP command.");
    return;
  }

  OdGePoint3d ptStart = pIO->getPoint(L"Specify first corner:");

  struct GeoMapTracker : OdStaticRxObject<OdEdPointTracker>
  {
    OdDbPolylinePtr m_ClipBoundary;
    OdGePoint3d m_ptFirst;

    GeoMapTracker(const OdGePoint3d & ptFirst) 
    {
      m_ptFirst = ptFirst;
      m_ClipBoundary = OdDbPolyline::createObject();
      m_ClipBoundary->reset(false, 5);
      for (int i = 0; i < 5; ++i)
      {
        m_ClipBoundary->addVertexAt(i, OdGePoint2d(ptFirst.x, ptFirst.y));
      }
    }

    virtual void setValue(const OdGePoint3d & val)
    {
      m_ClipBoundary->reset(false, 5);
      m_ClipBoundary->addVertexAt(0, OdGePoint2d(m_ptFirst.x, m_ptFirst.y));
      m_ClipBoundary->addVertexAt(1, OdGePoint2d(m_ptFirst.x, val.y));
      m_ClipBoundary->addVertexAt(2, OdGePoint2d(val.x, val.y));
      m_ClipBoundary->addVertexAt(3, OdGePoint2d(val.x, m_ptFirst.y));
      m_ClipBoundary->addVertexAt(4, OdGePoint2d(m_ptFirst.x, m_ptFirst.y));
    }

    virtual int addDrawables(OdGsView* pView)
    {
      return pView->add(m_ClipBoundary, 0);
    }

    virtual void removeDrawables(OdGsView* pView)
    {
      pView->erase(m_ClipBoundary);
    }
  } GeoMapTracker(ptStart);

  OdGePoint3d ptEnd = pIO->getPoint(L"Specify opposite corner:", 0, 0, OdString::kEmpty, &GeoMapTracker);

  OdDbObjectIdArray arObjId;
  {
    OdDbGeoMapPtr pGeoMap = OdDbGeoMap::createObject();
    pGeoMap->setDatabaseDefaults(pDb);
    OdGeExtents3d ext;
    ext.addPoint(ptStart);
    ext.addPoint(ptEnd);
    pGeoMap->setOrientation(ext.minPoint(),
                            OdGeVector3d(ext.maxPoint().x - ext.minPoint().x, 0., 0.),
                            OdGeVector3d(0., ext.maxPoint().y - ext.minPoint().y, 0.));

    OdString sGeoMapType = pDictionaryVar->value();
    pGeoMap->setMapType(OdGeoMapType(Od_strtoint(sGeoMapType)));
    pGeoMap->setDisplayOpt(OdDbRasterImage::kShow, true);
    OdDbObjectId modelSpaceId = pDb->getModelSpaceId();
    OdDbBlockTableRecordPtr pM = modelSpaceId.openObject(OdDb::kForWrite);
    pM->appendOdDbEntity(pGeoMap);
    arObjId.append(pGeoMap->id());
    pGeoMap->updateMapImage(true);
  }
  
  OdDbBlockTableRecordPtr pModelSpace = pDb->getModelSpaceId().safeOpenObject();
  OdDbSortentsTablePtr pSortentsTable = pModelSpace->getSortentsTable(true);
  pSortentsTable->moveToBottom(arObjId);
}


void _GeoMap_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

  OdDbObjectId viewportId = getActiveViewportIdForGeoMap(pDb);
  if (viewportId.isNull())
  {
    pIO->putString(L"Command Error: Can't set geomap type for overall viewport.");
    return;
  }

  OdUInt32 nKeyword = pIO->getKeyword(
    L"Select map type [Aerial/Road/Hybrid/Off] ",
    L"Aerial Road Hybrid Off", 0
    );

  int nType;
  switch(nKeyword)
  {
  case 1:
    nType = kRoad;
    break;
  case 2:
    nType = kHybrid;
    break;
  case 3:
    nType = kNoMap;
    break;
  case 0:
  default:  
    nType = kAerial;
    break;
  }

  OdDbObjectPtr pVp = viewportId.openObject();
  OdDbDictionaryPtr pExtDictionary = pVp->extensionDictionary().openObject();
  if (pExtDictionary.isNull())
  {
    pVp->upgradeOpen();
    pVp->createExtensionDictionary();
    pExtDictionary = pVp->extensionDictionary().openObject();
  }

  OdDbDictionaryPtr pExtVariableDictionary = pExtDictionary->getAt(L"AcDbVariableDictionary").openObject(OdDb::kForWrite);
  if (pExtVariableDictionary.isNull())
  {
    pExtDictionary->upgradeOpen();
    pExtVariableDictionary = pExtDictionary->setAt(L"AcDbVariableDictionary", OdDbDictionary::createObject()).openObject(OdDb::kForWrite);
  }
  
  if (nType != kNoMap)
  {
    OdDbDictionaryVarPtr pDictionaryVar = OdDbDictionaryVar::createObject();
    pDictionaryVar->setValue(nType);
    pExtVariableDictionary->setAt(L"GEOMAPMODE", pDictionaryVar);
  }
  else
  {
    pExtVariableDictionary->remove(L"GEOMAPMODE");
  }
}

void _GeoMapMode_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();

  OdDbGeoDataChunksPEPtr ext = OdDbGeoData::desc()->getX(OdDbGeoDataChunksPE::desc());
  if (ext.isNull())
  {
    pIO->putString("Command Error: Geo Map extension is not loaded.");
    return;
  }

  OdUInt32 nKeyword = pIO->getKeyword(
    L"Geo Map mode [Enable/Disable] ",
    L"Enable Disable", ext->getMode()
  );
  ext->setMode(0 == nKeyword);
}
