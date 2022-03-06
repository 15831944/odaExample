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

// ODA Platform
#include "OdaCommon.h"
#include "RxDynamicModule.h"
#include "RxVariantValue.h"

// Brep
#include "Br/BrBrep.h"
#include "BrepRenderer/BrepRendererImpl.h"

// Tv
#include "TvGeomCollector.h"
#include "TvFilerTimer.h"
#include "Obj2Visualize.h"
#include "TvDatabaseUtils.h"
#include "ObjProperties.h"

#define START_TV_OBJ_TIMER                            \
  if (pTvTimer)                                       \
    pTvTimer->start();

#define END_TV_OBJ_TIMER                              \
  if (pTvTimer)                                       \
  {                                                   \
    nTotalTvTime += pTvTimer->permanentSec();         \
    pTvTimer->stop();                                 \
  }

using namespace OBJToolkit;

OdTvVisualizeObjFilerProperties::OdTvVisualizeObjFilerProperties()
  : m_defaultColor(ODRGB(191, 191, 191))
  , m_flags(false)
{
}

OdRxDictionaryPtr OdTvVisualizeObjFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeObjFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeObjFilerProperties::~OdTvVisualizeObjFilerProperties()
{
}

namespace OBJToolkit {
  ODRX_DECLARE_PROPERTY(DefaultColor)
  ODRX_DECLARE_PROPERTY(DirectlyFromFile)
  ODRX_DECLARE_PROPERTY(BrepFlipUVCoordinates)
  ODRX_DECLARE_PROPERTY(CalculateVertexNormals)
  ODRX_DECLARE_PROPERTY(AppendTransform)
  ODRX_DECLARE_PROPERTY(NeedCDATree)
  ODRX_DECLARE_PROPERTY(ImportBrepAsBrep)
  ODRX_DECLARE_PROPERTY(DefaultUnits)

  ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeObjFilerProperties);
  ODRX_GENERATE_PROPERTY(DefaultColor)
  ODRX_GENERATE_PROPERTY(DirectlyFromFile)
  ODRX_GENERATE_PROPERTY(BrepFlipUVCoordinates)
  ODRX_GENERATE_PROPERTY(CalculateVertexNormals)
  ODRX_GENERATE_PROPERTY(AppendTransform)
  ODRX_GENERATE_PROPERTY(NeedCDATree)
  ODRX_GENERATE_PROPERTY(ImportBrepAsBrep)
  ODRX_GENERATE_PROPERTY(DefaultUnits)
  ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeObjFilerProperties);

  ODRX_DEFINE_PROPERTY_METHODS(DefaultColor, OdTvVisualizeObjFilerProperties, getDefaultColor, setDefaultColor, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(DirectlyFromFile, OdTvVisualizeObjFilerProperties, getDirectlyFromFile, setDirectlyFromFile, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(BrepFlipUVCoordinates, OdTvVisualizeObjFilerProperties, getBrepFlipUVCoordinates, setBrepFlipUVCoordinates, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(CalculateVertexNormals, OdTvVisualizeObjFilerProperties, getCalculateVertexNormals, setCalculateVertexNormals, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizeObjFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(NeedCDATree, OdTvVisualizeObjFilerProperties, getNeedCDATree, setNeedCDATree, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ImportBrepAsBrep, OdTvVisualizeObjFilerProperties, getImportBrepAsBrep, setImportBrepAsBrep, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(DefaultUnits, OdTvVisualizeObjFilerProperties, getDefaultUnits, setDefaultUnits, getIntPtr);
}

void OdTvVisualizeObjFilerProperties::setDefaultColor(OdIntPtr ptr)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(ptr);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_defaultColor = *pColor;
}

OdIntPtr OdTvVisualizeObjFilerProperties::getDefaultColor() const
{
  return (OdIntPtr)(&m_defaultColor);
}

void OdTvVisualizeObjFilerProperties::setAppendTransform(OdIntPtr pTransform)
{
  const OdTvMatrix* pAppendTransform = (const OdTvMatrix*)(pTransform);

  if (pAppendTransform)
  {
    m_appendTransform = *pAppendTransform;
  }
  else
  {
    m_appendTransform = OdTvMatrix::kIdentity;
  }
}

OdIntPtr OdTvVisualizeObjFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}

//***************************************************************************//
// 'OdTvVisualizeObjFiler' methods implementation
//***************************************************************************//

OdString generateMtlName(OdString strPrefix, int nAttempt)
{
  OdString str;
  str.format(L"%s_%d", strPrefix.c_str(), nAttempt++);
  return str;
}

OdTvMaterialId OdTvVisualizeObjFiler::importMaterial(OdTvDatabasePtr pDb, OdMtlPtr mtl) const
{
  OdString stDefrMaterialName = OD_T("OBJ_DEFAULT_MATERIAL");

  bool bIsDefault = false;
  if (mtl->getName() == OD_T("Default_Plain_White"))
    bIsDefault = true;

  if (bIsDefault)
  {
    OdTvResult rc;
    OdTvMaterialId materialId = pDb->createMaterial(stDefrMaterialName, &rc);
    if (rc != tvOk)
    {
      materialId = pDb->findMaterial(stDefrMaterialName, &rc);
      if (rc != tvOk)
        return OdTvMaterialId();
      else
        return materialId;
    }
    else
    {
      {
        OdTvMaterialPtr pDefaultMaterial = materialId.openObject(OdTv::kForWrite);
        if (!pDefaultMaterial.isNull())
        {
          OdTvMaterialColor matColor;
          matColor.setColor(OdTvColorDef(193, 193, 193));
          matColor.setMethod(OdTvMaterialColor::kOverride);

          pDefaultMaterial->setSpecular(matColor, 0.3);
        }
      }
      return materialId;
    }
  }

  OdTvResult rc;
  OdTvMaterialId materialId = pDb->createMaterial(mtl->getName(), &rc);
  if (rc != tvOk)
  {
    OdString mtlName = mtl->getName() + L"Generated_";

#define _MTL_ATTEMPTS 100
    int nAttempt = 0;
    while (rc != tvOk && nAttempt < _MTL_ATTEMPTS)
    {
      ++nAttempt;
      OdString mtlNameGen = generateMtlName(mtlName, nAttempt);
      materialId = pDb->createMaterial(mtlNameGen, &rc);
    }
    if (materialId.isNull())
      return materialId;
  }

  OdTvMaterialPtr pMaterial = materialId.openObject(OdTv::kForWrite);
  pMaterial->setSpecularGloss(mtl->getNs());
  pMaterial->setOpacity(mtl->getD());

  double p1;
  double p2;
  double p3;
  OdString mapRflFilename;
  OdString sTextureFName;
  double factor;
  OdMtl::eMtlDataType diffuseType = mtl->getDiffuseReflectivity(p1, p2, p3, mapRflFilename, factor);
  if (diffuseType == OdMtl::eMtlRGB)
  {
    OdTvMaterialMap materialMap;

    OdMtlOptionsPtr kdOpts = mtl->getOptions(mtMapKd);
    if (kdOpts.isNull() == false)
    {
      OdVariant strVal = kdOpts->getOption(mopvFilename);
      if (strVal.type() == OdVariant::kString)
      {
        sTextureFName = strVal.getString();
        if (sTextureFName.find((OdChar)'.') > 0)
        {
          if (sTextureFName.find(':') < 0)
            sTextureFName.format(L"%ls%ls", mtl->getPath().c_str(), sTextureFName.c_str());
          materialMap.setSourceFileName(sTextureFName);
        }
      }
    }

    OdTvMaterialColor color(OdTvColorDef(p1 * 255.0, p2 * 255.0, p3 * 255.0));
    pMaterial->setDiffuse(color, materialMap);
  }

  OdMtl::eMtlDataType ambientType = mtl->getAmbientReflectivity(p1, p2, p3, mapRflFilename, factor);
  if (ambientType == OdMtl::eMtlRGB)
  {
    OdTvMaterialMap materialMap;

    OdMtlOptionsPtr kaOpts = mtl->getOptions(mtMapKa);
    if (kaOpts.isNull() == false)
    {
      OdVariant strVal = kaOpts->getOption(mopvFilename);
      if (strVal.type() == OdVariant::kString)
      {
        sTextureFName = strVal.getString();
        if (sTextureFName.find((OdChar)'.') > 0)
        {
          if (sTextureFName.find(':') < 0)
            sTextureFName.format(L"%ls%ls", mtl->getPath().c_str(), sTextureFName.c_str());
          materialMap.setSourceFileName(sTextureFName);
        }
      }
    }

    pMaterial->setAmbient(OdTvMaterialColor(OdTvColorDef(p1 * 255.0, p2 * 255.0, p3 * 255.0)));// , materialMap);
  }

  OdMtl::eMtlDataType specularType = mtl->getSpecularReflectivity(p1, p2, p3, mapRflFilename, factor);
  if (specularType == OdMtl::eMtlRGB)
  {
    OdTvMaterialMap materialMap;

    OdMtlOptionsPtr ksOpts = mtl->getOptions(mtMapKs);
    if (ksOpts.isNull() == false)
    {
      OdVariant strVal = ksOpts->getOption(mopvFilename);
      if (strVal.type() == OdVariant::kString)
      {
        sTextureFName = strVal.getString();
        if (sTextureFName.find((OdChar)'.') > 0)
        {
          if (sTextureFName.find(':') < 0)
            sTextureFName.format(L"%ls%ls", mtl->getPath().c_str(), sTextureFName.c_str());
          materialMap.setSourceFileName(sTextureFName);
        }
      }
    }

    pMaterial->setSpecular(OdTvMaterialColor(OdTvColorDef(p1 * 255.0, p2 * 255.0, p3 * 255.0)), factor);
  }

  OdMtl::eMtlDataType transmissionType = mtl->getTransmissionFilter(p1, p2, p3, mapRflFilename, factor);
  if (transmissionType == OdMtl::eMtlRGB)
  {
    OdTvMaterialMap materialMap;

    /*OdMtlOptionsPtr tfOpts = mtl->getOptions(mtMapT);
    if (tfOpts.isNull() == false)
    {
    OdMtlValueString *strVal = (OdMtlValueString*)tfOpts->getOption(mopvFilename);
    if (strVal)
    {
    if (mapRflFilename.find((OdChar)'.') > 0)
    materialMap.setSourceFileName(mtl->getPath() + mapRflFilename);
    }
    }*/

    pMaterial->setEmission(OdTvMaterialColor(OdTvColorDef(p1 * 255.0, p2 * 255.0, p3 * 255.0)));// , materialMap);
  }

  return materialId;
}

OdTvVisualizeObjFiler::OdTvVisualizeObjFiler() : m_properties(OdTvVisualizeObjFilerProperties::createObject())
{

}

OdTvDatabaseId OdTvVisualizeObjFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;
  OdTvModelId modelId;
  {
    if (rc)
      *rc = tvOk;
    LoadObjOptions opt(filePath);
    importObj(tvDbId, modelId, opt, pProfileRes, rc);
  }

  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeObjFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;
  OdTvModelId modelId;
  {
    if (rc)
      *rc = tvOk;
    LoadObjOptions opt(pBuffer);
    importObj(tvDbId, modelId, pBuffer, pProfileRes, rc);
  }

  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeObjFiler::loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvDatabaseId();
}

OdTvDatabaseId OdTvVisualizeObjFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizeObjFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId dbId = databaseId;
  OdTvModelId tvModelId;
  {
    if (rc)
      *rc = tvOk;
    LoadObjOptions opt(filePath);
    importObj(dbId, tvModelId, opt, pProfileRes, rc);
  }

  return tvModelId;
}

OdTvModelId OdTvVisualizeObjFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId dbId = databaseId;
  OdTvModelId tvModelId;
  {
    if (rc)
      *rc = tvOk;
    LoadObjOptions opt(pBuffer);
    importObj(dbId, tvModelId, opt, pProfileRes, rc);
  }

  return tvModelId;
}

OdTvModelId OdTvVisualizeObjFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvModelId();
}

bool OdTvVisualizeObjFiler::importObj(OdTvDatabaseId& databaseId, OdTvModelId& tvModelId, const LoadObjOptions& opt, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/
  , OdTvResult* rc /*= NULL*/) const
{
  bool bImport = databaseId.isNull();

  OdTvGsDeviceId activeTvGsDeviceId;
  if(!bImport)
  {
    OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);
    //check that we are in the real append mode
    {
      OdTvDevicesIteratorPtr devicesIteratorPtr = pDb->getDevicesIterator();
      while (!devicesIteratorPtr->done())
      {
        activeTvGsDeviceId = devicesIteratorPtr->getDevice();
        if (activeTvGsDeviceId.openObject()->getActive())
          break;
      }
    }
  }

  // get default color from properties
  ODCOLORREF* pDefColor = (ODCOLORREF*)m_properties->getDefaultColor();
  OdUInt8 r, g, b;
  r = ODGETRED(*pDefColor);
  g = ODGETGREEN(*pDefColor);
  b = ODGETBLUE(*pDefColor);

  //check that time profiling is need
  bool bUseTimeProfiling = false;
  if (pProfileRes)
    bUseTimeProfiling = true;

  //
  // prepare OBJ Importer timing object
  //
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();
  OdObjImportPtr pObjImporter = OBJToolkit::createObjImporter();
  if (pObjImporter.isNull())
  {
    if (rc)
      *rc = tvMissingFilerModule;
    ::odrxDynamicLinker()->unloadUnreferenced();
    return false;
  }

  OdObjImportOptions importOptions;
  if (m_properties->has(OD_T("BrepFlipUVCoordinates")))
  {
    bool bBrepFlipUVCoordinates = m_properties->getBrepFlipUVCoordinates();
    importOptions.m_bFlipUVForBRepSurfaces = bBrepFlipUVCoordinates;
  }
  if (m_properties->has(OD_T("CalculateVertexNormals")))
  {
    bool calculateVertexesNormals = m_properties->getCalculateVertexNormals();
    importOptions.m_bCalculateNormals = calculateVertexesNormals;
  }

  bool directlyFromFile = m_properties->getDirectlyFromFile();
  OdResult res = eFileInternalErr;
  OdString filePath;
  if (opt.m_type == LoadObjOptions::kFilePath)
  {
    filePath = opt.m_filePath;
    if (!directlyFromFile)
    {
      try
      {
        res = pObjImporter->importFile(filePath, &importOptions);
      }
      catch (...)
      {
        res = eCantOpenFile;
      }
    }
    else
    {
      try
      {
        OdStreamBufPtr pFileBuf = odrxSystemServices()->createFile(filePath, Oda::kFileRead);
        if (pFileBuf.isNull())
          res = eFileAccessErr;
        else
          res = pObjImporter->importFile(pFileBuf, &importOptions);
      }
      catch (...)
      {
        res = eFileAccessErr;
      }
    }
  }
  else if(opt.m_type == LoadObjOptions::kBuffer)
  {
    try
    {
      if (!opt.m_pBuffer)
        res = eFileAccessErr;
      else
      {
        filePath = opt.m_pBuffer->fileName();
        res = pObjImporter->importFile(opt.m_pBuffer, &importOptions);
      }
    }
    catch (...)
    {
      res = eFileAccessErr;
    }
  }

  if (res != eOk)
  {
    if (rc)
      *rc = tvErrorDuringOpenFile;
    ::odrxDynamicLinker()->unloadUnreferenced();
    return false;
  }

  timing.startVectorizing();

  OdObjDbPtr pObjDb = pObjImporter->getObjDb();
  if (pObjDb->isEmpty())
  {
    if (rc)
      *rc = tvFilerEmptyInternalDatabase;
    ::odrxDynamicLinker()->unloadUnreferenced();
    return false;
  }

  OdMtlDbPtr pMtlDb = pObjDb->getMtlDb();
  OdUInt32 nMaterials = pMtlDb->getMaterialsCount();

  //generate model name
  OdString filename = OdTvDatabaseUtils::getFileNameFromPath(filePath);

  //
  // prepare Visualize timing object
  //
  OdPerfTimerBase* pTvTimer = 0;
  double nTotalTvTime = 0.;
  if (bUseTimeProfiling)
    pTvTimer = OdPerfTimerBase::createTiming();

  START_TV_OBJ_TIMER

    // create tv database
  if(databaseId.isNull())
  {
    OdTvFactoryId tvFactoryId = odTvGetFactory();
    databaseId = tvFactoryId.createDatabase();
  }
  OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);

  // save filename to database user data
  OdTvDatabaseUtils::writeFileNameToTvDatabase(databaseId, filename);

  // Generate model name
  if(!bImport)
   filename = OdTvDatabaseUtils::generateModelName(databaseId, filename);
  //create tv model
  tvModelId = pDb->createModel(filename);

  END_TV_OBJ_TIMER

  OdTvGeomCollector wd(bUseTimeProfiling);

  std::map<OdMtl*, OdTvMaterialId> mapMaterials;
  std::map<OdMtl*, OdTvMaterialId>::iterator it;

  // Create RegApp
  bool alreadyExist = false;
  OdTvRegAppId appId = pDb->registerAppName(L"ExGsVisualizeDevice", alreadyExist);

  //map for storing the information about the group's contents
  GroupInfoMap        groupsInfoMap;
  GroupTvMap          groupsTvMap;

  OdObjGroupIteratorPtr itGroups = pObjDb->createGroupsIterator();
  while (itGroups->done() == false)
  {
    OdObjGroupPtr pGroup = itGroups->element();
    if (pGroup.isNull() == false && pGroup->isEmpty() == false)
    {
      OdString          sGroupName = pGroup->getGroupName();
      OdArray<OdString> materialNames;
      OdGePoint3dArray  vertices;
      OdGePoint2dArray  texCoo;
      OdGeVector3dArray normals;
      OdUInt32Array     faces;
      OdUInt32Array     faceMaterials;
      OdArray< OdMtlPtr > faceMtls;
      OdTvVisualizeObjFilerGroupInfo groupInfo;

      OdTvModelPtr pTvModel = tvModelId.openObject(OdTv::kForWrite);
      OdTvEntityId entId = pTvModel->appendEntity(sGroupName);
      OdTvEntityPtr entPtr = entId.openObject(OdTv::kForWrite);
      entPtr->setColor(OdTvColorDef(r, g, b));

      if (importOptions.m_bCalculateNormals)
        pObjDb->calculateVertexNormals(pGroup);

      if (eOk == pGroup->getGroupShell(vertices, texCoo, normals, faces, faceMtls) && faces.size() > 0)
      {
        if (faceMtls.size() == 1)
        {
          OdTvMaterialId materialId;

          OdMtlPtr mtl = faceMtls.at(0);
          it = mapMaterials.find(mtl);
          if (it == mapMaterials.end())
          {
            materialId = importMaterial(pDb, mtl);
            mapMaterials[mtl.get()] = materialId;
            START_TV_OBJ_TIMER

              entPtr->setMaterial(materialId);

            END_TV_OBJ_TIMER
          }
          else
          {
            START_TV_OBJ_TIMER
              entPtr->setMaterial(it->second);
            END_TV_OBJ_TIMER
          }

          START_TV_OBJ_TIMER
            OdTvGeometryDataId shellId = createShell(entId, vertices, texCoo, normals, faces);
          END_TV_OBJ_TIMER

            groupInfo.m_nShells++;
          groupInfo.m_nVertices += vertices.size();
          OdTvShellDataPtr pShell = shellId.openAsShell();
          if (!pShell.isNull())
            groupInfo.m_nFaces += pShell->getFacesCount();

        }
        else
        {
          // Beat shell by materials
          if (faceMtls.size() > 1)
          {
            // Data for new shell
            OdGePoint3dArray  newVertices;
            OdGePoint2dArray  newTexCoo;
            OdGeVector3dArray newNormals;
            OdUInt32Array     newFaces;
            OdArray< OdMtlPtr > newFaceMtls;

            OdInt32 faceListSize = faces.length();
            OdInt32 nbVertex = vertices.length();
            OdInt32 startPosFc(0);
            OdInt32 endPosFc(0);
            OdInt32 startPosFcDt(0);
            OdInt32 endPosFcDt(0);
            OdInt32 startPosEdgeDt(0);
            OdInt32 endPosEdgeDt(0);
            OdInt32 sumVtx(0);
            OdInt32 curNumVtx(0);
            OdInt32 curAtt = faces[startPosFc];
            OdInt32 attempts = curAtt;

            START_TV_OBJ_TIMER

              OdMtlPtr pPrevMaterial = faceMtls.at(0);
            curNumVtx = faces[startPosFc];
            while (endPosFc < faceListSize)
            {
              OdMtlPtr pCurMaterial = faceMtls[endPosFcDt];

              if (endPosFc + curNumVtx + 1 < faceListSize && pCurMaterial == pPrevMaterial)
              {
                endPosFcDt++;
                sumVtx += curNumVtx;
                endPosFc += (curNumVtx + 1);
                curNumVtx = faces[endPosFc];
              }
              else
              {
                if (endPosFc + curNumVtx + 1 == faceListSize)
                {
                  endPosFcDt++;
                  sumVtx += curNumVtx;
                  endPosFc += (curNumVtx + 1);
                }

                OdInt32 j(0);
                OdGePoint3dArray pCurVertexList;
                OdInt32Array pMapVertexList;
                OdInt32Array pCurFaceList;
                OdGiVertexData pCurVertexData;
                OdGeVector3dArray pCurVerNormals;
                OdCmEntityColorArray pCurVerTrueColors;
                OdGePoint2dArray pCurVertexMappintCoords;
                OdGiFaceData pCurFaceData;
                OdGiEdgeData pCurEdgeData;
                pMapVertexList.resize(nbVertex, -1);
                curAtt = faces[startPosFc];
                attempts = curAtt;
                for (OdInt32 i = startPosFc; i < endPosFc; i++)
                {
                  if (attempts == curAtt)
                  {
                    pCurFaceList.push_back(faces[i]);
                    attempts--;
                  }
                  else if (0 < attempts)
                  {
                    endPosEdgeDt++;
                    if (pMapVertexList[faces[i]] < 0)
                    {
                      pCurVertexList.push_back(vertices[faces[i]]);
                      pMapVertexList[faces[i]] = j++;

                      pCurVerNormals.append(normals[faces[i]]);
                      pCurVertexMappintCoords.append(texCoo[faces[i]]);
                    }

                    pCurFaceList.push_back(pMapVertexList[faces[i]]);
                    attempts--;
                  }
                  else
                  {
                    endPosEdgeDt++;
                    if (pMapVertexList[faces[i]] < 0)
                    {
                      pCurVertexList.push_back(vertices[faces[i]]);
                      pMapVertexList[faces[i]] = j++;

                      pCurVerNormals.append(normals[faces[i]]);
                      pCurVertexMappintCoords.append(texCoo[faces[i]]);
                    }

                    pCurFaceList.push_back(pMapVertexList[faces[i]]);
                    if (i + 1 < endPosFc)
                    {
                      curAtt = faces[i + 1];
                      attempts = curAtt;
                    }
                  }
                } // for (OdInt32 i = startPosFc; i < endPosFc; i++)

                // Create new shell
                //append shell to the entity
                OdTvGeometryDataId shellId = entPtr->appendShell((OdInt32)pCurVertexList.size(), pCurVertexList.getPtr(), (OdInt32)pCurFaceList.size(), (const OdInt32*)pCurFaceList.getPtr());
                //set normals to the shell
                OdTvShellDataPtr shellPtr = shellId.openAsShell();
                OdTvGeometryDataPtr pShellGeometryData = shellId.openObject();
                if (pCurVerNormals.size() == pCurVertexList.size())
                  shellPtr->setVertexNormalsViaRange(0, (OdInt32)pCurVerNormals.size(), pCurVerNormals.getPtr());
                else
                {
                  // TODO: Calculate normals by visualize or something else
                }
                if (pCurVertexMappintCoords.size() == pCurVertexList.size())
                  shellPtr->setVertexMappingCoordsViaRange(0, (OdInt32)pCurVertexMappintCoords.size(), pCurVertexMappintCoords.getPtr());

                // enable spatial tree
                shellPtr->setUseSpatialTreeForSelection(true);

                //update group's info
                groupInfo.m_nShells++;
                groupInfo.m_nVertices += pCurVertexList.size();
                groupInfo.m_nFaces += shellPtr->getFacesCount();

                // Set material
                OdTvMaterialId materialId;
                it = mapMaterials.find(pPrevMaterial);
                if (it == mapMaterials.end())
                {
                  materialId = importMaterial(pDb, pPrevMaterial);
                  mapMaterials[pPrevMaterial.get()] = materialId;
                  pShellGeometryData->setMaterial(materialId);
                }
                else
                {
                  pShellGeometryData->setMaterial(it->second);
                }

                sumVtx = 0;
                startPosFc = endPosFc;
                startPosFcDt = endPosFcDt;
                startPosEdgeDt = endPosEdgeDt;
                pPrevMaterial = pCurMaterial;
              }
            } // while (endPosFc < faceListSize)

            END_TV_OBJ_TIMER
          } // if (faceMtls.size() > 1)

        }
      } // if (eOk == pGroup->getGroupShell(vertices, texCoo, normals, faces, faceMtls) && faces.size() > 0)

      int groupBrepsCounter = 0;

      OdObjEntityIteratorPtr it = pGroup->createEntitiesIterator();
      int groupEntitiesCounter = 0;
      while (it->done() == false)
      {
        const OdObjGeomEntity *pEntity = it->element();
        const eOBJEntType entType = pEntity->type();
        switch (entType)
        {
        case eOBJEntPoints:
        {
          if (!pEntity->m_vind.isEmpty())
          {
            vertices.clear();
            if (pObjDb->getVS(vertices, pEntity->m_vind))
            {
              START_TV_OBJ_TIMER
                OdTvGeometryDataId pointCloudId = entPtr->appendPointCloud(vertices.size(), vertices.asArrayPtr());
              END_TV_OBJ_TIMER
                groupInfo.m_nPointObjects++;
              groupInfo.m_nPoints += vertices.size();
            }
          }
        }
        break;

        case eOBJEntLine:
        {
          if (!pEntity->m_vind.isEmpty())
          {
            vertices.clear();
            if (pObjDb->getVS(vertices, pEntity->m_vind))
            {
              START_TV_OBJ_TIMER
                OdTvGeometryDataId polylineId = entPtr->appendPolyline(vertices.size(), vertices.asArrayPtr());
              END_TV_OBJ_TIMER
                groupInfo.m_nPolylines++;
              groupInfo.m_nPoints += vertices.size();
            }
          }
        }
        break;

        case eOBJEntCurve:
        {
          if (!pEntity->m_vind.isEmpty())
          {
            vertices.clear();
            if (pObjDb->getVS(vertices, pEntity->m_vind))
            {
              unsigned int size = vertices.size();
              const OdObjCurve* curve = static_cast<const OdObjCurve*>(pEntity);
              double startU = curve->m_startU;
              double endU = curve->m_endU;
              OdDoubleArray knots = curve->m_knots;
              if (startU >= 1.) {
                endU -= startU;
                for (unsigned int i = 0; i < knots.size(); i++)
                  knots.at(i) -= startU;
                startU -= startU;
              }
              if (endU > 1.)
              {
                double coef = endU - startU;
                startU /= coef;
                endU /= coef;
                for (unsigned int i = 0; i < knots.size(); i++)
                  knots.at(i) = knots.at(i) / coef;
              }
              if (curve != NULL) {
                START_TV_OBJ_TIMER
                  OdTvGeometryDataId nurbsId = entPtr->appendNurbs(curve->m_degree, size,
                    vertices.asArrayPtr(),
                    curve->m_weights.size() ? curve->m_weights.asArrayPtr() : NULL,
                    knots.size(),
                    knots.asArrayPtr(),
                    startU,
                    endU
                  );
                END_TV_OBJ_TIMER
                  groupInfo.m_nNurbs++;
                groupInfo.m_nPoints += vertices.size();
              }
            }
          }
        }
        break;

        case eOBJEntSurface:
        {
          OdBrBrep brep;
          if (pObjDb->getBrep(brep, (OdObjSurface*)pEntity) == eOk)
          {
            ++groupBrepsCounter;

            bool bImportBrepAsBrep = false;
            if (m_properties->has(OD_T("ImportBrepAsBrep")))
              bImportBrepAsBrep = m_properties->getImportBrepAsBrep();

            if(bImportBrepAsBrep)
              entPtr->appendBrep(brep, (OdDbBaseDatabase*)pDb->getInternalDatabase());
            else
            {
              OdBrepRendererImpl brepRenderer;

              // Set triangulation params to some defaults.
              wrTriangulationParams m_DefaultTriangulationParams = wrTriangulationParams();
              m_DefaultTriangulationParams.BetweenKnots = 30;
              brepRenderer.setTriangulationParams(&m_DefaultTriangulationParams);

              // Set the brep data for the renderer
              brepRenderer.setBrep(brep);

              // append Tv Entity
              OdString entityName;
              entityName.format(OD_T("%s_%s%d"), sGroupName.c_str(), OD_T("Surface "), groupBrepsCounter);

              OdTvGeometryDataId entityId = entPtr->appendSubEntity(entityName);
              entityId.openObject()->setColor(OdTvColorDef(r, g, b));

              // Do rendering
              wd.setTargetDisplayMode(OdTvGeometryData::kRender);
              wd.setTvEntity(entityId);
              brepRenderer.draw(&wd, BrepRenderModes::kShells, 0);

              wd.setTargetDisplayMode(OdTvGeometryData::kWireframe);
              wd.setColorForByLayer(OdCmEntityColor(0, 0, 0));
              brepRenderer.draw(&wd, BrepRenderModes::kEdges, 0);
              brepRenderer.draw(&wd, BrepRenderModes::kIsolines, 0);
              wd.setColorForByLayer(OdCmEntityColor::kNone);
            }

            groupInfo.m_nBReps++;
          }
        }
        break;

        default:
          // Not implemented yet
          break;
        }
        it->step();
      }

      //remember the group info in the map
      OdUInt64 handle = (OdUInt64)pGroup.get();
      groupsInfoMap[handle] = groupInfo;
      //remember the tv entity in the map
      groupsTvMap[handle] = entId;
    }

    itGroups->step();
  }

  START_TV_OBJ_TIMER

    if (bImport)
    {
      OdTvDatabaseUtils::createDeviceAndView(databaseId, tvModelId, OdTvGsView::kGouraudShaded, true);
    }
    else
    {
      //add model to view
      if (activeTvGsDeviceId.isNull())
        OdTvDatabaseUtils::createDeviceAndView(databaseId, tvModelId, OdTvGsView::kGouraudShaded, true);
      else
      {
        OdTvGsViewId viewId = activeTvGsDeviceId.openObject()->getActiveView();
        if (!viewId.isNull())
          viewId.openObject(OdTv::kForWrite)->addModel(tvModelId);
      }

      //apply transform if need 
      OdTvMatrix* pTransfrom = (OdTvMatrix*)m_properties->getAppendTransform();
      if (pTransfrom)
      {
        OdTvDatabaseId& tvDvId = const_cast<OdTvDatabaseId&>(databaseId);
        OdTvDatabaseUtils::applyTransformToTheModel(tvDvId, filename, *pTransfrom);
      }
    }
    
  //set units
  if (databaseId.isValid() && !tvModelId.isNull())
  {
    OdTvModelPtr pModel = tvModelId.openObject(OdTv::kForWrite);
    if (!pModel.isNull())
    {
      //get units
      OdTv::Units tvUnits = (OdTv::Units)m_properties->getDefaultUnits();
      pModel->setUnits(tvUnits, 1.);
    }
  }

  END_TV_OBJ_TIMER

  timing.endVectorizing();

  timing.startMisc();
  if (!databaseId.isNull() && m_properties->getNeedCDATree())
    createCommonDataAccessTree(pDb, pObjDb.get(), filename + OD_T(".obj"), groupsInfoMap, groupsTvMap);
  timing.endMisc();

  if (pProfileRes)
    pProfileRes->setCDATreeCreationTime(OdInt64((timing.getMiscTime()) * 1000.));

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64(timing.getVectorizingTime() * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64(nTotalTvTime * 1000.));
#endif
  }

  ::odrxDynamicLinker()->unloadUnreferenced();

  return true;
}

OdTvGeometryDataId OdTvVisualizeObjFiler::createShell(OdTvEntityId& entityId, OdGePoint3dArray& vertices, OdGePoint2dArray& texCoo, OdGeVector3dArray& normals, OdUInt32Array& faces) const
{
  OdTvEntityPtr entPtr = entityId.openObject(OdTv::kForWrite);

  //append shell to the entity
  OdTvGeometryDataId shellId = entPtr->appendShell((OdInt32)vertices.size(), vertices.getPtr(), (OdInt32)faces.size(), (const OdInt32*)faces.getPtr());

  //set normals to the shell
  OdTvShellDataPtr shellPtr = shellId.openAsShell();

  if (normals.size() == vertices.size())
    shellPtr->setVertexNormalsViaRange(0, (OdInt32)normals.size(), normals.getPtr());
  else
  {
    // TODO: Calculate normals by visualize or something else
  }

  if (texCoo.size() == vertices.size())
    shellPtr->setVertexMappingCoordsViaRange(0, (OdInt32)texCoo.size(), texCoo.getPtr());

  // enable spatial tree
  shellPtr->setUseSpatialTreeForSelection(true);

  return shellId;
}

void addPropertyToDbNode(OdTvCDATreeNodePtr pNode, const OdString& name, const OdString& localName, OdUInt32 weight, OdUInt32 value)
{
  PropertyInfo info;
  info.localizedName = localName;
  info.uiPlacement = OD_T("Contents");
  info.weight = weight;
  info.name = name;
  info.value = value;
  pNode->addProperty(info);
}

void OdTvVisualizeObjFiler::createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName, const GroupInfoMap& groupInfos,
                                                       const GroupTvMap& groupTvConnect) const
{
  ::odrxDynamicLinker()->loadModule(L"RxProperties");

  //Create CDA tree
  OdTvCDATreePtr pTree = OdTvCDATree::createObject();
  pTree->createDatabaseHierarchyTree(pDatabase, true);

  //direct add nodes to the tree base on the collected info
  OdObjDb* pObjDb = (OdObjDb*)pDatabase;
  if (pObjDb)
  {
    OdObjGroupIteratorPtr itGroups = pObjDb->createGroupsIterator();
    OdTvCDATreeNodePtr pRootNode = dynamic_cast<OdTvCDATreeNode*>(pTree->getDatabaseNode().get());
    OdUInt32 nShells = 0;
    OdUInt32 nNurbs = 0;
    OdUInt32 nPolylines = 0;
    OdUInt32 nPointObj = 0;
    OdUInt32 nBreps = 0;
    OdUInt32 nFaces = 0;
    OdUInt32 nVertices = 0;
    OdUInt32 nPoints = 0;

    while (itGroups->done() == false)
    {
      OdObjGroupPtr pGroup = itGroups->element();
      if (pGroup.isNull() == false && pGroup->isEmpty() == false)
      {
        OdString sGroupName = pGroup->getGroupName();
        GroupInfoMap::const_iterator itInfo = groupInfos.find((OdUInt64)pGroup.get());
        GroupTvMap::const_iterator itInfoTv = groupTvConnect.find((OdUInt64)pGroup.get());

        OdTvCDATreeNodePtr pTvCDANode = pTree->addNode(pRootNode, sGroupName, eEntity);
        if (!pTvCDANode.isNull())
        {
          if (itInfoTv != groupTvConnect.end())
            pTvCDANode->addTvEntityId(itInfoTv->second);

          if (groupInfos.end() != itInfo)
          {
            PropertyInfo info;
            int weight = 1;

            info.localizedName = OD_T("Name");
            info.uiPlacement = OD_T("General");
            info.weight = weight++;
            info.name = OD_T("Name");
            info.value = sGroupName;
            pTvCDANode->addProperty(info);

            info.localizedName = OD_T("Shells");
            info.weight = weight++;
            info.name = OD_T("ShellsNum");
            info.value = OdUInt32(itInfo->second.m_nShells);
            pTvCDANode->addProperty(info);
            nShells += OdUInt32(itInfo->second.m_nShells);

            if (itInfo->second.m_nNurbs > 0)
            {
              info.localizedName = OD_T("Nurbs");
              info.weight = weight++;
              info.name = OD_T("NurbsNum");
              info.value = OdUInt32(itInfo->second.m_nNurbs);
              pTvCDANode->addProperty(info);
              nNurbs += OdUInt32(itInfo->second.m_nNurbs);
            }

            if (itInfo->second.m_nPolylines > 0)
            {
              info.localizedName = OD_T("Polylines");
              info.weight = weight++;
              info.name = OD_T("PolylinesNum");
              info.value = OdUInt32(itInfo->second.m_nPolylines);
              pTvCDANode->addProperty(info);
              nPolylines += OdUInt32(itInfo->second.m_nPolylines);
            }

            if (itInfo->second.m_nPointObjects > 0)
            {
              info.localizedName = OD_T("Point objects");
              info.weight = weight++;
              info.name = OD_T("PointObjectsNum");
              info.value = OdUInt32(itInfo->second.m_nPointObjects);
              pTvCDANode->addProperty(info);
              nPointObj += OdUInt32(itInfo->second.m_nPointObjects);
            }

            if (itInfo->second.m_nBReps > 0)
            {
              info.localizedName = OD_T("BReps");
              info.weight = weight++;
              info.name = OD_T("BRepsNum");
              info.value = OdUInt32(itInfo->second.m_nBReps);
              pTvCDANode->addProperty(info);
              nBreps += OdUInt32(itInfo->second.m_nBReps);
            }

            info.localizedName = OD_T("Faces");
            info.weight = weight++;
            info.name = OD_T("FacesNum");
            info.value = OdUInt32(itInfo->second.m_nFaces);
            pTvCDANode->addProperty(info);
            nFaces += OdUInt32(itInfo->second.m_nFaces);

            info.localizedName = OD_T("Vertices");
            info.weight = weight++;
            info.name = OD_T("VerticesNum");
            info.value = OdUInt32(itInfo->second.m_nVertices);
            pTvCDANode->addProperty(info);
            nVertices += OdUInt32(itInfo->second.m_nVertices);

            if (itInfo->second.m_nPoints > 0)
            {
              info.localizedName = OD_T("Points");
              info.weight = weight++;
              info.name = OD_T("PointsNum");
              info.value = OdUInt32(itInfo->second.m_nPoints);
              pTvCDANode->addProperty(info);
              nPoints += OdUInt32(itInfo->second.m_nPoints);
            }
          }
        }
      }
      itGroups->step();
    }// eo while...

    int rootWeight = 0;
    // find the largest weight
    const OdArray<PropertyInfo>& rootProps = pRootNode->getProperties();
    for (unsigned int i = 0; i < rootProps.length(); i++)
    {
      if (rootProps.at(i).weight > rootWeight)
        rootWeight = rootProps.at(i).weight;
    }
    ++rootWeight;

    // add count of shell's property
    addPropertyToDbNode(pRootNode, OD_T("ShellsNum"), OD_T("Shells"), rootWeight++, nShells);
    // add count of faces property
    addPropertyToDbNode(pRootNode, OD_T("FacesNum"), OD_T("Faces"), rootWeight++, nFaces);
    // add count of vertices property
    addPropertyToDbNode(pRootNode, OD_T("VerticesNum"), OD_T("Vertices"), rootWeight++, nVertices);
    // add count of nurbs property
    if(nNurbs > 0)
      addPropertyToDbNode(pRootNode, OD_T("NurbsNum"), OD_T("Nurbs"), rootWeight++, nNurbs);
    // add count of polylines property
    if(nPolylines > 0)
      addPropertyToDbNode(pRootNode, OD_T("PolylinesNum"), OD_T("Polylines"), rootWeight++, nPolylines);
    // add count of point objects property
    if(nPointObj > 0)
      addPropertyToDbNode(pRootNode, OD_T("PointObjectsNum"), OD_T("Point objects"), rootWeight++, nPointObj);
    // add count of breps property
    if(nBreps > 0)
      addPropertyToDbNode(pRootNode, OD_T("BrepsNum"), OD_T("BRep's"), rootWeight++, nBreps);
    // add count of points property
    if(nPoints > 0)
      addPropertyToDbNode(pRootNode, OD_T("PointsNum"), OD_T("Points"), rootWeight++, nPoints);
  }

  //Add tree to the Tv database
  OdTvResult rc;
  OdTvCDATreeStorageId cdaTreeId = pTvDb->addCDATreeStorage(strTreeName, pTree, &rc);
  if (rc == tvAlreadyExistSameName)
  {
    OdUInt32 i = 1;
    while (rc != tvOk && i < MAX_CDATREENAME_GENERATION_ATTEMPTS)
    {
      OdString str;
      str.format(L"%s_%d", strTreeName.c_str(), i++); //not to fast but it is not a "bottle neck"
      cdaTreeId = pTvDb->addCDATreeStorage(str, pTree, &rc);
    }
  }

  //Add new CDA tree to the appropriate models
  OdTvModelsIteratorPtr modelsIterPtr = pTvDb->getModelsIterator();
  OdTvModelId modelId;
  if (!modelsIterPtr->done())
  {
    modelId = modelsIterPtr->getModel();
    OdTvModelPtr pModel = modelId.openObject();
    if (!pModel.isNull())
    {
      pModel->setCDATreeStorage(cdaTreeId);
    }
  }

  // add model id to node
  OdTvCDATreeNodePtr pTvNode = pTree->getDatabaseNode();
  if (!pTvNode.isNull())
  {
    const OdRxModelTreeBaseNodePtrArray nodes = pTvNode->getChildren();
    for (OdRxModelTreeBaseNodePtrArray::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
      OdTvCDATreeNodePtr pNode = *it;
      if (pNode.isNull())
        continue;
      pNode->setTvModelId(modelId);
    }
  }
}

//***************************************************************************//
// 'OdTvVisualizeObjFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeObjFilerModule);

void OdTvVisualizeObjFilerModule::initApp()
{
  //load module
  m_pModule = ::odrxDynamicLinker()->loadModule(L"OBJToolkit", false);

  // initialize the Visualize SDK
  odTvInitialize();

  OdTvVisualizeObjFilerPropertyWithResLoader::rxInit();

  ::odrxSetMemberConstructor(OdObjDb::desc(), constructOdObjDatabaseProperties);

  static OdStaticRxObject<OdTvVisualizeObjFilerPropResourceLoaderPE> resourceLoaderPE;
  OdTvVisualizeObjFilerPropertyWithResLoader::desc()->addX(OdRxResourceLoader::desc(), &resourceLoaderPE);
}

void OdTvVisualizeObjFilerModule::uninitApp()
{
  //remove protocol extension
  OdTvVisualizeObjFilerPropertyWithResLoader::desc()->delX(OdRxResourceLoader::desc());

  // Clear properties
  for (unsigned i = 0; i < properties.size(); ++i)
    OdRxMember::deleteMember(properties[i]);
  properties.clear();

  //unload module
  m_pModule = NULL;
  ::odrxDynamicLinker()->unloadModule(L"OBJToolkit");

  OdTvVisualizeObjFilerPropertyWithResLoader::rxUninit();

  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeObjFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pObjFiler = new OdTvVisualizeObjFiler();

  return pObjFiler;
}

void OdTvVisualizeObjFilerModule::constructOdObjDatabaseProperties(OdRxMemberCollectionBuilder& b, void* data)
{
  createOdObjDatabaseProperties(properties, b, data);
}
