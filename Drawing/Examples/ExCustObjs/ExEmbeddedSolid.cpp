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
/*ExEmbeddedSolid.cpp: example of implementation for a custom entity    */
/* with an embedded 3dSolid object                                      */
/************************************************************************/
#include "OdaCommon.h"
#include "ExEmbeddedSolid.h"
#include "Gi/GiWorldDraw.h"
#include "DbFiler.h"
#include "DbCommandContext.h"
#include "EmbeddedASMEntPE.h"
#include "DbProxyEntity.h"
#include "DbBlockTableRecord.h"
#include "DbCircle.h"

ODRX_DXF_DEFINE_MEMBERS(EmbeddedSolidWrapper,                                          // ClassName
                        OdDbEntity,                                                    // ParentClass
                        DBOBJECT_CONSTR,                                               // DOCREATE
                        OdDb::vAC27,                                                   // DwgVer
                        OdDb::kMRelease0,                                              // MaintVer
                        OdDbProxyEntity::kAllAllowedBits,                              // NProxyFlags
                        EmbeddedSolidWrapper,                                          // DxfName
                        ExCustObjs|Description: Teigha Run-time Extension Example)     // AppName


/************************************************************************/
/* A pointer to an OdDbEmbeddedASMEntPropsPE object implementing        */
/* protocol extension for embedded entity handling                      */
/************************************************************************/                        
static OdDbEmbeddedASMEntPropsPE* pPE = NULL;
static bool bInit = true;

/************************************************************************/
/* Get pointer to protocol extension object                             */
/************************************************************************/
static OdDbEmbeddedASMEntPropsPE* getEmbedPE()
{
  if (bInit)
  {
    bInit = false;
    OdRxClass* pCls = OdDb3dSolid::desc();
    OdRxClass* pPECls = OdRxClass::cast(odrxClassDictionary()->getAt(L"OdDbEmbeddedASMEntPropsPE"));
    if (pCls && pPECls)
    {
      pPE = (OdDbEmbeddedASMEntPropsPE*)pCls->getX(pPECls).get();
    }
  }
  return pPE;
}                        

/************************************************************************/
/*Set embedded flag for the entities                                    */
/************************************************************************/
void EmbeddedSolidWrapper::setEmbeddedFlag()
{
  OdDbEmbeddedASMEntPropsPE* pPE = getEmbedPE();

  if (!pPE)
    return;

  if (!m_pSolid.isNull())
    pPE->setIsEmbeddedEnt(m_pSolid);
  if (!m_pRegion.isNull())
    pPE->setIsEmbeddedEnt(m_pRegion);
  if (!m_pBody.isNull())
    pPE->setIsEmbeddedEnt(m_pBody);
  if (!m_pSurface.isNull())
    pPE->setIsEmbeddedEnt(m_pSurface);
}
                       
EmbeddedSolidWrapper::EmbeddedSolidWrapper()
{
  m_pSolid = OdDb3dSolid::createObject();
  m_pSurface = OdDbSurface::createObject();
  m_pBody = OdDbBody::createObject();
  m_pRegion = OdDbRegion::createObject();

  setEmbeddedFlag();
}

/************************************************************************/
/* Initialize embedded objects with specified database default          */
/* properties and create spheres                                        */
/************************************************************************/
void EmbeddedSolidWrapper::init(OdDbDatabase* pDb)
{
  /***********************************************************************/
  /* Create three spheres for 3dSolid, Surface, Body and circular Region */
  /**********************************************************************/

  {
    m_pSolid = OdDb3dSolid::createObject();
    m_pSolid->setDatabaseDefaults(pDb);
    m_pSolid->createSphere(2);

    {
      OdRxObjectPtrArray entitySet;
      m_pSolid->explode(entitySet);
      if (entitySet.size() == 1)
      {
        m_pSurface = entitySet.first();
        m_pSurface->setDatabaseDefaults(pDb);
        m_pSurface->transformBy(OdGeMatrix3d::translation(OdGeVector3d(4,0,0)));

        entitySet.clear();
        m_pSurface->explode(entitySet);

        if (entitySet.size() == 1)
        {
          m_pBody = entitySet.first();
          m_pBody->setDatabaseDefaults(pDb);
          m_pBody->transformBy(OdGeMatrix3d::translation(OdGeVector3d(4, 0, 0)));
        }
      }
    }
  }

  {
    OdRxObjectPtrArray curves, entitySet;

    OdDbCirclePtr pCircle = OdDbCircle::createObject();
    pCircle->setRadius(1.);
    pCircle->setCenter(OdGePoint3d(-4, 0, 0));
    pCircle->setNormal(OdGeVector3d(0, 0, 1));
    curves.push_back(pCircle.get());
    OdDbRegion::createFromCurves(curves, entitySet);
    if (entitySet.size() == 1)
    {
      m_pRegion = entitySet.first();
      m_pRegion->setDatabaseDefaults(pDb);
    }
  }

  setEmbeddedFlag();
}

EmbeddedSolidWrapper::~EmbeddedSolidWrapper()
{
}

/************************************************************************/
/* Read the DWG format data of the object from the specified file       */
/************************************************************************/
OdResult EmbeddedSolidWrapper::dwgInFields(OdDbDwgFiler* filer)
{
  /**********************************************************************/
  /* Determining whether an entity should be loaded as a proxy          */
  /* (when OdDbEmbeddedASMEntPropsPE is not available)                  */
  /**********************************************************************/
  if (!getEmbedPE() && filer->filerType() == OdDbFiler::kFileFiler)
    return eMakeMeProxy;

  /**********************************************************************/
  /* If the entity is opened for writing, read fields common to all     */
  /* entities                                                           */
  /**********************************************************************/
  assertWriteEnabled();
  OdResult es = OdDbEntity::dwgInFields(filer);
  if (es != eOk)
    return es;

  /**********************************************************************/
  /* Read data for 3dSolid object from the specified file               */
  /**********************************************************************/
  es = m_pSolid->dwgInFields(filer);
  if (es != eOk)
    return es;

  /**********************************************************************/
  /* Read data for Region object from the specified file               */
  /**********************************************************************/
  es = m_pRegion->dwgInFields(filer);
  if (es != eOk)
    return es;

  /**********************************************************************/
  /* Read data for Body object from the specified file               */
  /**********************************************************************/
  es = m_pBody->dwgInFields(filer);
  if (es != eOk)
    return es;

  /**********************************************************************/
  /* Read data for Surface object from the specified file               */
  /**********************************************************************/
  es = m_pSurface->dwgInFields(filer);

  return es;
}

/************************************************************************/
/* Write the DWG format data of the custom entity to the specified file */
/* through two steps: write common fields and write fields for the      */
/* embedded objects                                                     */
/************************************************************************/
void EmbeddedSolidWrapper::dwgOutFields(OdDbDwgFiler* filer) const
{
  assertReadEnabled();
  OdDbEntity::dwgOutFields(filer);
  m_pSolid->dwgOutFields(filer);
  m_pRegion->dwgOutFields(filer);
  m_pBody->dwgOutFields(filer);
  m_pSurface->dwgOutFields(filer);
}

/************************************************************************/
/* Read the DXF format data of this object from the specified file      */
/************************************************************************/
OdResult EmbeddedSolidWrapper::dxfInFields(OdDbDxfFiler* filer)
{
  /**********************************************************************/
  /* Determining whether a proxy creating is required                   */
  /* (when OdDbEmbeddedASMEntPropsPE is not available)                  */
  /**********************************************************************/
  if (!getEmbedPE())
    return eMakeMeProxy;

  /**********************************************************************/
  /* If the entity is opened for writing, read fields common to all     */
  /* entities                                                           */
  /**********************************************************************/
  assertWriteEnabled();

  OdResult es = OdDbEntity::dxfInFields(filer);
  if (es != eOk)
    return es;

  es = eBadDxfSequence;
  if (filer->atEmbeddedObjectStart())
  {
    es = m_pSolid->dxfInFields(filer);
  }
  if (es != eOk)
    return es;

  es = eBadDxfSequence;
  if (filer->atEmbeddedObjectStart())
  {
    es = m_pRegion->dxfInFields(filer);
  }
  if (es != eOk)
    return es;

  es = eBadDxfSequence;
  if (filer->atEmbeddedObjectStart())
  {
    es = m_pBody->dxfInFields(filer);
  }
  if (es != eOk)
    return es;

  es = eBadDxfSequence;
  if (filer->atEmbeddedObjectStart())
  {
    es = m_pSurface->dxfInFields(filer);
  }
        
  return es;
}

/************************************************************************/
/* Write the DXF format data of this object to the specified file       */
/************************************************************************/
void EmbeddedSolidWrapper::dxfOutFields(OdDbDxfFiler* filer) const
{
  /************************************************************************/
  /* Checking whether the entity is opened for reading, then write common */
  /* fields                                                               */
  /************************************************************************/
  assertReadEnabled();
  OdDbEntity::dxfOutFields(filer);
  /************************************************************************/
  /* Write fields for the embedded objects                                */
  /************************************************************************/
  filer->wrEmbeddedObjectStart();
  m_pSolid->dxfOutFields(filer);
  filer->wrEmbeddedObjectStart();
  m_pRegion->dxfOutFields(filer);
  filer->wrEmbeddedObjectStart();
  m_pBody->dxfOutFields(filer);
  filer->wrEmbeddedObjectStart();
  m_pSurface->dxfOutFields(filer);
}

/************************************************************************/
/* Creates a viewport-independent geometric representation of the       */
/* embedded objects                                                     */
/************************************************************************/
bool EmbeddedSolidWrapper::subWorldDraw(OdGiWorldDraw* pWd) const
{
  pWd->geometry().draw(m_pSolid);
  pWd->geometry().draw(m_pRegion);
  pWd->geometry().draw(m_pBody);
  pWd->geometry().draw(m_pSurface);
  return true;
}

/************************************************************************/
/* Create EmbeddedSolidWrapper command                                       */
/************************************************************************/
void _EmbeddedSolidWrapper_func(OdEdCommandContext* pCmdCtx)
{
  if (!getEmbedPE())
    return;

  /**********************************************************************/
  /* Establish command context, database, and UserIO                    */
  /**********************************************************************/
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  
  OdDbBlockTableRecordPtr pMS = pDb->getModelSpaceId().openObject(OdDb::kForWrite);

  EmbeddedSolidWrapperPtr pWrapper = EmbeddedSolidWrapper::createObject();

  pWrapper->setDatabaseDefaults(pDb);
  pWrapper->init(pDb);

  pMS->appendOdDbEntity(pWrapper);
}
