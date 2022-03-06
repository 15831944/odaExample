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

// Visualize SDK
#include "TvFactory.h"

#include "TvFactory.h"
#include "TvGeomCollector.h"
#include "TvFilerTimer.h"
#include "TvDatabaseUtils.h"

//STL import
#include "STLImport.h"

#include "Stl2Visualize.h"
#include "TvFilerTimer.h"
#include "TvDatabaseUtils.h"
#include "StlProperties.h"

using namespace STLFileImport;
using namespace STL2Visualize;

//***************************************************************************//
// 'OdTvVisualizeStlFilerProperties' methods implementation
//***************************************************************************//

OdTvVisualizeStlFilerProperties::OdTvVisualizeStlFilerProperties() : m_defaultColor(ODRGB(191, 191, 191)), m_flags(kFixNormals | kUnifyDuplicatedVertices)
{
}

OdRxDictionaryPtr OdTvVisualizeStlFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeStlFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeStlFilerProperties::~OdTvVisualizeStlFilerProperties()
{
}

namespace STL2Visualize {
  ODRX_DECLARE_PROPERTY(DefaultColor)
  ODRX_DECLARE_PROPERTY(FixNormals)
  ODRX_DECLARE_PROPERTY(UnifyDuplicatedVertices)
  ODRX_DECLARE_PROPERTY(CalcNormalsAtVertices)
  ODRX_DECLARE_PROPERTY(AppendTransform)
  ODRX_DECLARE_PROPERTY(NeedCDATree)
  ODRX_DECLARE_PROPERTY(DefaultUnits)

  ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeStlFilerProperties);
  ODRX_GENERATE_PROPERTY(DefaultColor)
  ODRX_GENERATE_PROPERTY(FixNormals)
  ODRX_GENERATE_PROPERTY(UnifyDuplicatedVertices)
  ODRX_GENERATE_PROPERTY(CalcNormalsAtVertices)
  ODRX_GENERATE_PROPERTY(AppendTransform)
  ODRX_GENERATE_PROPERTY(NeedCDATree)
  ODRX_GENERATE_PROPERTY(DefaultUnits)
  ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeStlFilerProperties);

  ODRX_DEFINE_PROPERTY_METHODS(DefaultColor, OdTvVisualizeStlFilerProperties, getDefaultColor, setDefaultColor, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(FixNormals, OdTvVisualizeStlFilerProperties, getFixNormals, setFixNormals, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(UnifyDuplicatedVertices, OdTvVisualizeStlFilerProperties, getUnifyDuplicatedVertices, setUnifyDuplicatedVertices, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(CalcNormalsAtVertices, OdTvVisualizeStlFilerProperties, getCalcNormalsAtVertices, setCalcNormalsAtVertices, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizeStlFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(NeedCDATree, OdTvVisualizeStlFilerProperties, getNeedCDATree, setNeedCDATree, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(DefaultUnits, OdTvVisualizeStlFilerProperties, getDefaultUnits, setDefaultUnits, getIntPtr);
}

void OdTvVisualizeStlFilerProperties::setDefaultColor(OdIntPtr ptr)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(ptr);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_defaultColor = *pColor;
}

OdIntPtr OdTvVisualizeStlFilerProperties::getDefaultColor() const
{
  return (OdIntPtr)(&m_defaultColor);
}

void OdTvVisualizeStlFilerProperties::setAppendTransform(OdIntPtr pTransform)
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

OdIntPtr OdTvVisualizeStlFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}

//***************************************************************************//
// 'OdTvVisualizeRcsFiler' methods implementation
//***************************************************************************//

OdTvVisualizeStlFiler::OdTvVisualizeStlFiler() : m_properties(OdTvVisualizeStlFilerProperties::createObject())
{
}

OdTvDatabaseId OdTvVisualizeStlFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;
  OdTvModelId modelId;
  LoadStlOptions opt(filePath);
  importStl(tvDbId, modelId, opt, pProfileRes, rc);
  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeStlFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;
  OdTvModelId modelId;
  LoadStlOptions opt(pBuffer);
  importStl(tvDbId, modelId, opt, pProfileRes, rc);
  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeStlFiler::loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvDatabaseId();
}

OdTvDatabaseId OdTvVisualizeStlFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizeStlFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;
  OdTvModelId modelId;
  LoadStlOptions opt(filePath);
  importStl(tvDbId, modelId, opt, pProfileRes, rc);
  return modelId;
}

OdTvModelId OdTvVisualizeStlFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvDatabaseId tvDbId;
  OdTvModelId modelId;
  LoadStlOptions opt(pBuffer);
  importStl(tvDbId, modelId, opt, pProfileRes, rc);
  return modelId;
}

OdTvModelId OdTvVisualizeStlFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  if (rc)
    *rc = tvNotImplementedYet;

  return OdTvModelId();
}

void OdTvVisualizeStlFiler::createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName,
                                                       OdTvEntityId entId, OdTvGeometryDataId geomId) const
{
  ::odrxDynamicLinker()->loadModule(L"RxProperties");

  //Create CDA tree
  OdTvCDATreePtr pTree = OdTvCDATree::createObject();
  pTree->createDatabaseHierarchyTree(pDatabase, true);

  OdStlImport* pStlImport = (OdStlImport*)pDatabase;
  OdString strSolidName = OD_T("Solid");
  pStlImport->getSolidName(strSolidName);

  if (strSolidName == OD_T("STL_BINARY"))
    strSolidName = OD_T("Solid");

  //get root node
  OdTvCDATreeNodePtr pRootNode = dynamic_cast<OdTvCDATreeNode*>(pTree->getDatabaseNode().get());
 
  PropertyInfo info;
  info.localizedName = OD_T("Unified vertices");
  info.uiPlacement = OD_T("General");
  info.weight = 2;
  info.name = OD_T("UnifiedVertices");
  info.value = m_properties->getUnifyDuplicatedVertices();
  pRootNode->addProperty(info);

  info.localizedName = OD_T("Fixed normals");
  info.uiPlacement = OD_T("General");
  info.weight = 3;
  info.name = OD_T("FixedNormals");
  info.value = m_properties->getFixNormals();
  pRootNode->addProperty(info);

  OdTvCDATreeNodePtr pTvCDANode = pTree->addNode(pRootNode, strSolidName, eEntity);
  if (!pTvCDANode.isNull())
  {
    pTvCDANode->addTvEntityId(entId);

    int weight = 1;

    info.localizedName = OD_T("Name");
    info.uiPlacement = OD_T("General");
    info.weight = weight++;
    info.name = OD_T("Name");
    info.value = strSolidName;
    pTvCDANode->addProperty(info);

    if (geomId.getType() == OdTv::kShell)
    {
      OdTvShellDataPtr pShell = geomId.openAsShell();

      info.localizedName = OD_T("Faces");
      info.weight = weight++;
      info.name = OD_T("FacesNum");
      info.value = OdUInt32(pShell->getFacesCount());
      pTvCDANode->addProperty(info);

      info.localizedName = OD_T("Vertices");
      info.weight = weight++;
      info.name = OD_T("VerticesNum");
      info.value = OdUInt32(pShell->getVerticesCount());
      pTvCDANode->addProperty(info);
    }
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

bool OdTvVisualizeStlFiler::importStl(OdTvDatabaseId& databaseId, OdTvModelId& tvModelId, const LoadStlOptions& opt, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  if (rc)
    *rc = tvOk;

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

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  //try to get STL importer
  OdStlImportPtr pStlImporter = createStlImporter();
  if (pStlImporter.isNull())
  {
    if (rc)
      *rc = tvMissingFilerModule;
    return false;
  }

  //try to perform import
  OdString filePath;
  if(opt.m_type == LoadStlOptions::kFilePath)
  {
    filePath = opt.m_filePath;
    if (pStlImporter->import(filePath) != STLFileImport::eNoError)
    {
      if (rc)
        *rc = tvErrorDuringOpenFile;
      return false;
    }
  }
  else if (opt.m_type == LoadStlOptions::kBuffer)
  {
    if (pStlImporter->import(opt.m_pBuffer) != STLFileImport::eNoError)
    {
      if (rc)
        *rc = tvErrorDuringOpenFile;
      return false;
    }

    filePath = opt.m_pBuffer->fileName();
  }

  timing.startVectorizing();

  //try to get the data about the readed STL file
  OdGePoint3dArray vertices;
  OdUInt32Array faces;
  OdGeVector3dArray normals;

  OdUInt8 flags = 0;
  if (m_properties->getFixNormals())
    SETBIT(flags, OdStlImport::kFixNormals, true);

  if (m_properties->getUnifyDuplicatedVertices())
    SETBIT(flags, OdStlImport::kUnifyDuplicatedVertices, true);

  if (m_properties->getCalcNormalsAtVertices())
    SETBIT(flags, OdStlImport::kCalcNormalsAtVertices, true);

  if (pStlImporter->getShell(vertices, faces, normals, flags) != STLFileImport::eNoError)
  {
    if (rc)
      *rc = tvErrorDuringOpenFile;
    return false;
  }

  //get the solid name
  OdString strSolidName = OD_T("STL_SOLID");
  pStlImporter->getSolidName(strSolidName);

  timing.endVectorizing();
  timing.endTotal();

  //prepare timing object
  OdTvFilerTimer tvTiming(bUseTimeProfiling);
  tvTiming.startTotal();

  // create tv database
  bool isDbEmpty = databaseId.isNull();
  if (isDbEmpty)
  {
    OdTvFactoryId tvFactoryId = odTvGetFactory();
    databaseId = tvFactoryId.createDatabase();
  }
  OdTvDatabasePtr pDb = databaseId.openObject(OdTv::kForWrite);

  //get file name
  OdString filename = OdTvDatabaseUtils::getFileNameFromPath(filePath);

  // save filename to database user data
  if (isDbEmpty)
    OdTvDatabaseUtils::writeFileNameToTvDatabase(databaseId, filename);

  //create tv model
  tvModelId = pDb->createModel(filename);

  //create entity
  OdTvModelPtr pTvModel = tvModelId.openObject(OdTv::kForWrite);
  OdTvEntityId entId = pTvModel->appendEntity(strSolidName);
  OdTvEntityPtr entPtr = entId.openObject(OdTv::kForWrite);
  entPtr->setColor(OdTvColorDef(r, g, b));

  //append shell to the entity
  OdTvGeometryDataId shellId = entPtr->appendShell((OdInt32)vertices.size(), vertices.getPtr(), (OdInt32)faces.size(), (const OdInt32*)faces.getPtr());

  //set normals to the shell
  OdTvShellDataPtr shellPtr = shellId.openAsShell();
  if (GETBIT(flags, OdStlImport::kCalcNormalsAtVertices))
    shellPtr->setVertexNormalsViaRange(0, (OdInt32)normals.size(), normals.getPtr());
  else
    shellPtr->setFaceNormalsViaRange(0, (OdInt32)normals.size(), normals.getPtr());

  // enable spatial tree
  shellPtr->setUseSpatialTreeForSelection(true);

  //apply material
  OdString strMaterialName = OD_T("STL_DEFAULT_MATERIAL");
  OdTvResult retCode;
  OdTvMaterialId materialId = pDb->createMaterial(strMaterialName, &retCode);
  if (retCode == tvOk)
  {
    OdTvMaterialPtr pDefaultMaterial = materialId.openObject(OdTv::kForWrite);
    if (!pDefaultMaterial.isNull())
    {
      OdTvMaterialColor matColor;
      matColor.setColor(OdTvColorDef(255, 255, 255));

      pDefaultMaterial->setSpecular(matColor, 0.3);
      entPtr->setMaterial(materialId);
    }
  }

  OdTvDatabaseUtils::createDeviceAndView(databaseId, tvModelId, OdTvGsView::kFlatShaded, true);

  timing.startMisc();
  if (!databaseId.isNull() && m_properties->getNeedCDATree())
    createCommonDataAccessTree(pDb, pStlImporter.get(), filename + OD_T(".stl"), entId, shellId);
  timing.endMisc();

  if (pProfileRes)
    pProfileRes->setCDATreeCreationTime(OdInt64((timing.getMiscTime()) * 1000.));

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

  tvTiming.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime()) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.));
    pProfileRes->setTvTime(OdInt64((tvTiming.getTotalTime()) * 1000.));
#else
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime() + tvTiming.getTotalTime()) * 1000.));
#endif
  }

  pStlImporter.release();
  ::odrxDynamicLinker()->unloadUnreferenced();

  return true;
}

//***************************************************************************//
// 'OdTvVisualizeStlFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeStlFilerModule);

void OdTvVisualizeStlFilerModule::initApp()
{
  //load module
  m_pModule = ::odrxDynamicLinker()->loadModule(L"STLImport", false);

  // initialize the Visualize SDK
  odTvInitialize();

  ::odrxSetMemberConstructor(OdStlImport::desc(), constructOdStlImportProperties);
}

void OdTvVisualizeStlFilerModule::uninitApp()
{
  // Clear properties
  for (unsigned i = 0; i < properties.size(); ++i)
    OdRxMember::deleteMember(properties[i]);
  properties.clear();

  //unload module
  m_pModule = NULL;
  ::odrxDynamicLinker()->unloadModule(L"STLImport");

  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeStlFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pStlFiler = new OdTvVisualizeStlFiler();

  return pStlFiler;
}

void OdTvVisualizeStlFilerModule::constructOdStlImportProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdStlImportTypeProperty::createObject(b.owner()));
  b.add(properties.last());
}
