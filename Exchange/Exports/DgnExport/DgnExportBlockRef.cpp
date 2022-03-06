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

#include <OdaCommon.h>
#include "DgnExportText.h"
#include "DgnExportBlockRef.h"
#include "DgnExportImpl.h"
#include "DgnExportCommon.h"
#include "DgnExportContext.h"
#include "DgnExportImages.h"
#include <DgSharedCellReference.h>
#include <DbBlockReference.h>
#include <DbBlockTableRecord.h>
#include <DbAttributeDefinition.h>
#include <DbAttribute.h>
#include <DgTagSetDefinition.h>
#include <DgTagElement.h>
#include <DgText.h>
#include <DgTextNode.h>
#include <DbDictionary.h>
#include <DbRasterImage.h>
#include <DbSpatialFilter.h>
#include <DgReferenceAttach.h>
#include <DgLevelTableRecord.h>
#include <DbViewport.h>
#include <DbLayerTable.h>
#include <DbLayerTableRecord.h>
#include <DgLevelMask.h>
#include <ModelDocObj/DbViewRepBlockReference.h>
#include <DgShape.h>
#include <DbWipeout.h>

namespace TD_DGN_EXPORT {

//---------------------------------------------------------------------------------------------------

OdDbObjectId getAttrDefBlockId(OdDbAttributeDefinition* pDbAttrDef)
{
  OdDbObjectId idBlock = pDbAttrDef->ownerId();
  OdDbObjectPtr pBlockObj = idBlock.safeOpenObject();

  while (!pBlockObj.isNull() && !pBlockObj->isKindOf(OdDbBlockTableRecord::desc()))
  {
    idBlock = pBlockObj->ownerId();
    pBlockObj = idBlock.safeOpenObject();
  }

  return idBlock;
}

//---------------------------------------------------------------------------------------------------

void OdDbAttributeDefinitionExportPE::subExportElement(OdDbEntity* pDbEntity, OdDgElement* owner)
{
  OdDbAttributeDefinition* pDbAttrDef = (OdDbAttributeDefinition*)(pDbEntity);

  OdDbObjectId idAttrDefBlock = getAttrDefBlockId(pDbAttrDef);

  if (idAttrDefBlock.isNull())
    return;

  OdDgElementId idDgAttrDefSet = OdDgnExportContext::getAttrDefSetForBlock(idAttrDefBlock);

  if( idDgAttrDefSet.isNull() )
  {
    OdDbBlockTableRecordPtr pBlock = idAttrDefBlock.openObject(OdDb::kForRead);
    OdDgTagDefinitionSetTablePtr pTagSetTable = owner->database()->getTagDefinitionSetTable(OdDg::kForWrite);

    OdDgTagDefinitionSetPtr pNewSet = OdDgTagDefinitionSet::createObject();

    OdString strDefSetNameBase = pBlock->getName() + L"_Attrs";

    OdString strDefSetName = strDefSetNameBase;

    if (strDefSetName.getLength() > 32)
      strDefSetNameBase.left(32);

    if (strDefSetNameBase.getLength() > 29)
      strDefSetNameBase.left(29);

    OdUInt32 uCount = 0;

    while( !pTagSetTable->getAt(strDefSetName).isNull() )
    {
      uCount++;
      strDefSetName.format(L"_%d", uCount);
      strDefSetName = strDefSetNameBase + strDefSetName;
    }

    pNewSet->setName(strDefSetName);
    pTagSetTable->add(pNewSet);
    OdDgnExportContext::bindAttrDefSetToBlock(pNewSet->elementId(), idAttrDefBlock);
    idDgAttrDefSet = pNewSet->elementId();
  }


  if (idDgAttrDefSet.isNull())
    return;

  OdDgTagDefinitionSetPtr pDgBlockSet = idDgAttrDefSet.openObject(OdDg::kForWrite);

  // Apppend tag definition

  OdString strKey = pDbAttrDef->tag();

  if( !pDgBlockSet->getByName(strKey).isNull() )
  {
    OdString strNewKey;
    OdUInt32 uIndex = 1;
    do
    {
      strNewKey.format(L"_%d", uIndex);
      strNewKey = strKey + strNewKey;
      uIndex++;
    } 
    while (!pDgBlockSet->getByName(strNewKey).isNull());

    strKey = strNewKey;
  }

  pDgBlockSet->addDefinition(OdDgTagDefinition::kChar, strKey);

  OdDgTagDefinitionPtr pTagDef = pDgBlockSet->getByName(strKey);

  if (pTagDef.isNull())
    return;

  pTagDef->setPrompt(pDbAttrDef->prompt());

  if (pDbAttrDef->isMTextAttributeDefinition())
  {
    OdDbMTextPtr pMText = pDbAttrDef->getMTextAttributeDefinition();

    if( pMText.isNull() )
      pTagDef->setString(pMText->contents());
    else
      pTagDef->setString(pDbAttrDef->textString());
  }
  else
    pTagDef->setString(pDbAttrDef->textString());

  pTagDef->setDisplayTagFlag(!pDbAttrDef->isInvisible());
  pTagDef->setVariableFlag(!pDbAttrDef->isConstant());
  pTagDef->setConfirmFlag(pDbAttrDef->isVerifiable());
  pTagDef->setDefaultFlag(true);

  // Append tag

  OdDgTagElementPtr pTag = OdDgTagElement::createObject();
  pTag->setDatabaseDefaults(owner->database());
  pTag->set3dFlag(OdDgnExportContext::is3d());
  pTag->setTagDefinitionId(pDgBlockSet->elementId(), pTagDef->getEntryId());
  pTag->setAssociatedFlag(false);
  pTag->setOffsetUsedFlag(false);
  pTag->setJustificationUsedFlag(true);
  pTag->setHideForSharedCellFlag(true);
  pTag->setOrigin(pDbAttrDef->position());

  if( OdDgnExportContext::is3d() )
  {
    OdGeVector3d vrZAxis = pDbAttrDef->normal();
    OdGeVector3d vrXAxis = OdGeVector3d::kXAxis;
    double dRotation = pDbAttrDef->rotation();

    if (fabs(dRotation) < 1.e16)
      vrXAxis.rotateBy(dRotation, OdGeVector3d::kZAxis);

    vrXAxis.transformBy(OdGeMatrix3d::planeToWorld(vrZAxis));
    OdGeMatrix3d matRotation;
    matRotation.setCoordSystem(OdGePoint3d::kOrigin, vrXAxis, vrZAxis.crossProduct(vrXAxis), vrZAxis);
    matRotation.transposeIt();
    OdGeQuaternion quatRot;
    quatRot.set(matRotation);
    pTag->setRotation3d(quatRot);
  }
  else
  {
    pTag->setRotation2d(pDbAttrDef->rotation());
  }

  pTag->setString(pTagDef->getString());

  OdDgElementId idDgTextStyle = OdDgnExportContext::getElementId(pDbAttrDef->textStyle());

  if (!idDgTextStyle.isNull())
    pTag->applyTextStyle(idDgTextStyle);

  pTag->setHeightMultiplier(pDbAttrDef->height());
  pTag->setLengthMultiplier(pTag->getHeightMultiplier() * pDbAttrDef->widthFactor());
  pTag->setSlant(pDbAttrDef->oblique());

  OdDg::TextJustification uDgJust = getDgTextJustification(pDbAttrDef->horizontalMode(), pDbAttrDef->verticalMode());
  pTag->setJustification(uDgJust);

  if (pDbAttrDef->isMirroredInX())
    pTag->setBackwardsFlag(true);

  if (pDbAttrDef->isMirroredInY())
    pTag->setUpsideDownFlag(true);

  if( !pTag.isNull() )
  {
    addElementToDatabase(pTag, owner);
    copyElementProperties(pTag, pDbAttrDef, owner->database());
    appendOdDgElementToOwner(owner, pTag);

    OdDgnExportContext::addDgnElement(pDbAttrDef->objectId(), pTag->elementId());
  }
}

//---------------------------------------------------------------------------------------------------

OdDbAttributePtr convertConstDbAttrDefToAttribute(const OdDbAttributeDefinitionPtr& pAttrDef, const OdGeMatrix3d& matBlockTransform )
{
  OdDbAttributePtr pRet = OdDbAttribute::createObject();
  pRet->setDatabaseDefaults(pAttrDef->database());
  pRet->setAttributeFromBlock(pAttrDef, matBlockTransform);
  pRet->adjustAlignment();

  return pRet;
}

//---------------------------------------------------------------------------------------------------

void getBlockAttributes(OdDbBlockReference* pDbRef,
                          OdArray<OdDbAttributePtr>& arrAttributes,
                            OdArray<OdDbObjectId>& arrRasterImages,
                              OdArray<OdDbObjectId>& arrAttributeOwners,
                                OdArray<OdGeMatrix3d>& arrTransforms,
                                  OdArray<OdGeMatrix3d>& arrRasterTransforms,
                                    const OdGeMatrix3d& matBaseTransform)
{
  OdDbObjectId idDbBlock = pDbRef->blockTableRecord();

  if (idDbBlock.isNull())
    return;

  OdGeMatrix3d matRefTransform = pDbRef->blockTransform();

  OdDbObjectIteratorPtr pAttrIter = pDbRef->attributeIterator();

  OdArray<OdDbAttributePtr> arrCurBlockTags;

  for(; !pAttrIter->done(); pAttrIter->step())
  {
    OdDbAttributePtr pAttribute = pAttrIter->entity();

    if (pAttribute.isNull())
      continue;

    arrAttributes.push_back(pAttribute);
    arrCurBlockTags.push_back(pAttribute);
    arrAttributeOwners.push_back(idDbBlock);
    arrTransforms.push_back(matBaseTransform);
  }

  OdDbBlockTableRecordPtr pBlock = idDbBlock.openObject(OdDb::kForRead, true);

  OdDbObjectIteratorPtr pBlockIter = pBlock->newIterator();

  for (; !pBlockIter->done(); pBlockIter->step())
  {
    OdDbEntityPtr pItem = pBlockIter->entity();

    if( pItem.isNull() )
      continue;

    if( pItem->isKindOf(OdDbBlockReference::desc()) )
    {
      OdDbBlockReferencePtr pSubBlockRef = pItem;
      getBlockAttributes(pSubBlockRef.get(), arrAttributes, arrRasterImages, arrAttributeOwners, arrTransforms, arrRasterTransforms, matRefTransform*matBaseTransform);
    }
    else if (pItem->isKindOf(OdDbRasterImage::desc()))
    {
      arrRasterImages.push_back(pItem->id());
      arrRasterTransforms.push_back(matRefTransform*matBaseTransform);
    }
    else if( pItem->isKindOf(OdDbAttributeDefinition::desc()) )
    {
      OdDbAttributeDefinitionPtr pAttrDef = pItem;

      if( pAttrDef->isConstant() )
      {
        bool bAddAttribute = true;

        OdString strAttrDefName = pAttrDef->tag();
        strAttrDefName.makeUpper();

        for( OdUInt32 k = 0; k < arrCurBlockTags.size(); k++ )
        {
          OdString strTagName = arrCurBlockTags[k]->tag();
          strTagName.makeUpper();

          if( strAttrDefName == strTagName )
          {
            bAddAttribute = false;
            break;
          }
        }

        if( bAddAttribute )
        {
          OdDbAttributePtr pAttribute = convertConstDbAttrDefToAttribute(pAttrDef, matRefTransform);

          if( !pAttribute.isNull() )
          {
            arrAttributes.push_back(pAttribute);
            arrAttributeOwners.push_back(idDbBlock);
            arrTransforms.push_back(matBaseTransform);
          }
        }
      }
    }
  }
}

//---------------------------------------------------------------------------------------------------

OdUInt32 getNextFileNumber(const OdDgModelPtr& pModel)
{
  OdUInt32 uRet = 0;

  OdDgElementIteratorPtr pIter = pModel->createControlElementsIterator();

  for(; !pIter->done(); pIter->step() )
  {
    OdDgElementPtr pItem = pIter->item().openObject(OdDg::kForRead);

    if( !pItem.isNull() && pItem->isKindOf(OdDgReferenceAttachmentHeader::desc()) )
    {
      OdDgReferenceAttachmentHeaderPtr pXRef = pItem;

      if (pXRef->getFileNumber() > uRet)
        uRet = pXRef->getFileNumber();
    }
  }

  return uRet + 1;
}

//---------------------------------------------------------------------------------------------------

void exportBlockReferenceThroughExplode(OdDbBlockTableRecord* pDbBlock, OdDbBlockReference* pDbRef, OdDgElement* owner)
{
  OdGeMatrix3d matTransform = pDbRef->blockTransform();
  OdGeMatrix3d matUniScale  = matTransform;

  if( !matTransform.isUniScaledOrtho() )
  {
    OdGePoint3d ptOrigin;
    OdGeVector3d vrX, vrY, vrZ;
    matTransform.getCoordSystem(ptOrigin, vrX, vrY, vrZ);
    double dScale = vrX.length();

    vrY = vrZ.crossProduct(vrX);
    vrX = vrY.crossProduct(vrZ);

    vrX.setLength(dScale);
    vrY.setLength(dScale);
    vrZ.setLength(dScale);

    matUniScale.setCoordSystem(ptOrigin, vrX, vrY, vrZ);
  }

  OdDbObjectIteratorPtr pIter = pDbBlock->newIterator();

  OdUInt32 uColorByBlock       = OdDgnExportContext::getColorByBlockIndex();
  OdUInt32 uLineStyleByBlock   = OdDgnExportContext::getLineStyleByBlockIndex();
  OdUInt32 uLineWeightByBlock  = OdDgnExportContext::getLineWeightByBlockIndex();

  OdCmColor         curColor   = pDbRef->color();
  OdDbObjectId      idLineType = pDbRef->linetypeId();
  OdDb::LineWeight  lineWeight = pDbRef->lineWeight();

  OdDgnExportContext::setColorByBlockIndex(getDgnColorIndex(curColor, owner->database()));
  OdDgnExportContext::setLineStyleByBlockIndex(getDgnLineStyleEntryId(idLineType));
  OdDgnExportContext::setLineWeightByBlockIndex(odDgnExportLineweightMapping(lineWeight));

  for(; !pIter->done(); pIter->step())
  {
    OdDbEntityPtr pEnt = pIter->entity();
    OdDbEntityPtr pEntClone = pEnt->clone();

    if( pEntClone->transformBy(matTransform) == eCannotScaleNonUniformly )
    {
      pEntClone->transformBy(matUniScale);
    }

    if (!pEntClone.isNull())
    {
      OdDgnExportPE* pExportPE = (OdDgnExportPE*)pEntClone->queryX(OdDgnExportPE::desc());

      if (pExportPE)
        pExportPE->exportElement(pEntClone, owner);
    }
  }

  OdDgnExportContext::setColorByBlockIndex(uColorByBlock);
  OdDgnExportContext::setLineStyleByBlockIndex(uLineStyleByBlock);
  OdDgnExportContext::setLineWeightByBlockIndex(uLineWeightByBlock);
}

//---------------------------------------------------------------------------------------------------

bool exportBlockReference(OdDbBlockReference* pDbRef, OdDgElement* owner, OdArray<OdDgElementId>& arrAppendedElements)
{
  if (!pDbRef)
    return true;

  OdDbObjectId idDbBlock = pDbRef->blockTableRecord();

  if (idDbBlock.isNull())
    return true;

  OdDbBlockTableRecordPtr pDbBlock = idDbBlock.openObject(OdDb::kForRead);

  if (pDbBlock.isNull())
    return true;

  if (OdDgnExportContext::isBlockOnProcessing(pDbBlock->id()))
  {
    ODA_ASSERT_ONCE(!"Circular block references.");
    return true;
  }

  if (OdDgnExportContext::isBlockWithXRefInsert(idDbBlock))
  {
    exportBlockReferenceThroughExplode(pDbBlock, pDbRef, owner);
    return true;
  }

  if (isXRef(pDbBlock)) // X-Ref
  {
    OdDgElementId idModel = getOwnerModelId(owner);

    if( idModel.isNull() )
    {
      ODA_ASSERT_ONCE(!"Can't get dgn model.");
      return true;
    }

    OdDgModelPtr pModel = idModel.openObject(OdDg::kForWrite);

    OdDgReferenceAttachmentHeaderPtr pDgXRef = OdDgReferenceAttachmentHeader::createObject();
    OdString strFileName = pDbBlock->pathName();
    pDgXRef->setFullFileName(strFileName);
    strFileName.replace(L'\\', L'/');

    if (strFileName.reverseFind(L'/') != -1)
      strFileName = strFileName.right(strFileName.getLength() - strFileName.reverseFind(L'/') - 1);
    else
    {
      OdDbHostAppServices* pAppServices = pDbRef->database()->appServices();

      if (pAppServices)
      {
        OdString strFullFileName = pAppServices->findFile(strFileName, pDbRef->database(), OdDbBaseHostAppServices::kXRefDrawing);

        if( !strFullFileName.isEmpty() )
          pDgXRef->setFullFileName(strFullFileName);
      }
    }

    pDgXRef->setFileName(strFileName);
    OdGeMatrix3d matTransform = pDbRef->blockTransform();

    OdGeVector3d vrXAxis = matTransform.getCsXAxis();
    OdGeVector3d vrYAxis = matTransform.getCsYAxis();
    OdGeVector3d vrZAxis = matTransform.getCsZAxis();

    double dScale = vrXAxis.length();

    if( !vrZAxis.isParallelTo(OdGeVector3d::kZAxis))
      dScale = matTransform.scale();
    else
    {
      if (vrYAxis.length() > dScale)
        dScale = vrYAxis.length();
    }

    double dNativeScale = dScale;

    dScale /= pModel->getMeasuresConversion(OdDgModel::kWuWorldUnit, pModel->getWorkingUnit());

    vrXAxis.normalize();
    vrYAxis.normalize();
    vrZAxis.normalize();

    OdGeMatrix3d matRotation;
    matRotation.setCoordSystem(OdGePoint3d::kOrigin, vrXAxis, vrYAxis, vrZAxis);

    pDgXRef->setTransformation(matRotation);
    pDgXRef->setScale(dScale);
    pDgXRef->setMasterOrigin(pDbRef->position());

    pDgXRef->setDisplayFlag(true);
    pDgXRef->setNestDepth(99);
    pDgXRef->setFileNumber(getNextFileNumber(pModel));

    OdDgElementId idDgLayer = OdDgnExportContext::getElementId(pDbRef->layerId());

    if (!idDgLayer.isNull())
    {
      OdDgLevelTableRecordPtr pLevel = idDgLayer.openObject(OdDg::kForRead);
      pDgXRef->setLevelEntryId(pLevel->getEntryId());
    }
    else
      pDgXRef->setLevelEntryId(0);

    // set clipping
    
    OdDbObjectId idDictionary = pDbRef->extensionDictionary();

    if (!idDictionary.isNull() && owner->isKindOf(OdDgModel::desc()))
    {
      OdDbDictionaryPtr pXDic = OdDbDictionary::cast(OdDbObjectId(idDictionary).openObject(OdDb::kForRead));

      if (!pXDic.isNull())
      {
        OdDbDictionaryPtr pFilterDic = pXDic->getAt(OD_T("ACAD_FILTER"), OdDb::kForRead);

        if (!pFilterDic.isNull())
        {
          OdDbSpatialFilterPtr pSpFilter = pFilterDic->getAt(OD_T("SPATIAL"), OdDb::kForRead);

          if (!pSpFilter.isNull() && pSpFilter->isEnabled())
          {
            OdGiClipBoundary boundary;
            bool bEnabled;
            pSpFilter->getDefinition(boundary, bEnabled);

            if (bEnabled)
            {              
              OdUInt32 uNumPts = boundary.m_Points.size();

              if (boundary.m_Points.size() == 2)
              {
                OdGePoint2d ptMin = boundary.m_Points[0];
                OdGePoint2d ptMax = boundary.m_Points[1];

                OdGePoint2dArray arrRect;
                arrRect.push_back(ptMin);
                arrRect.push_back(ptMin + OdGeVector2d::kXAxis*(ptMax.x - ptMin.x));
                arrRect.push_back(ptMax);
                arrRect.push_back(ptMin + OdGeVector2d::kYAxis*(ptMax.y - ptMin.y));

                boundary.m_Points = arrRect;

                uNumPts = boundary.m_Points.size();
              }

              if( !boundary.m_Points.first().isEqualTo(boundary.m_Points.last()) )
              {
                boundary.m_Points.push_back(boundary.m_Points.first());
                uNumPts++;
              }

              pDgXRef->setClipPointsCount(uNumPts);

              OdGeMatrix3d matClipTransform = boundary.m_xToClipSpace * OdGeMatrix3d::scaling(dNativeScale) * boundary.m_xInverseBlockRefXForm;
              
              for (OdUInt32 k = 0; k < boundary.m_Points.size(); k++)
              {
                OdGePoint3d ptClip(boundary.m_Points[k].x, boundary.m_Points[k].y, 0.0);
                ptClip.transformBy(matClipTransform);
                pDgXRef->setClipPoint(k, ptClip.convert2d());
              }
            }
          }
        }
      }
    }

    pModel->addElement(pDgXRef);
    arrAppendedElements.push_back(pDgXRef->elementId());
  }
  else
  {
    OdDgElementId idDgBlock = OdDgnExportContext::getElementId(idDbBlock);

    if (idDgBlock.isNull())
    {
      OdDgSharedCellDefinitionTablePtr pDgBlockTable = owner->database()->getSharedCellDefinitionTable(OdDg::kForWrite);

      OdDgSharedCellDefinitionPtr pDgBlockDef = OdDgSharedCellDefinition::createObject();
      pDgBlockDef->setName(pDbBlock->getName());
      pDgBlockDef->setDescription(pDbBlock->comments());
      pDgBlockDef->setOrigin(pDbBlock->origin());
      pDgBlockDef->set3dFormatFlag(OdDgnExportContext::is3d());
      pDgBlockTable->add(pDgBlockDef);

      double dOldScaleFactor = OdDgnExportContext::getLineStyleScaleCorrectionFactor();
      OdDgnExportContext::setLineStyleScaleCorrectionFactor(1.0 / OdDgnExportContext::getMasterToUORsScale());

      OdDgnExportContext::addProcessingBlockId(pDbBlock->id());
      DgnExporter::copyBlock(pDbBlock, pDgBlockDef);
      OdDgnExportContext::removeProcessingBlockId(pDbBlock->id());

      OdDgnExportContext::setLineStyleScaleCorrectionFactor(dOldScaleFactor);

      OdDgnExportContext::addDgnElement(pDbBlock->objectId(), pDgBlockDef->elementId());

      pDgBlockDef->transformBy(OdGeMatrix3d::scaling(OdDgnExportContext::getMasterToUORsScale()));

      idDgBlock = pDgBlockDef->elementId();
    }

    if (!idDgBlock.isNull())
    {
      // create shared cell reference

      OdDgSharedCellReferencePtr pCellRef = OdDgSharedCellReference::createObject();

      OdDgElementId idOwnerModel = getOwnerModelId(owner);
      pCellRef->setOrigin(pDbRef->OdDbBlockReference::position());
      pCellRef->setTransformation(pDbRef->blockTransform()*OdGeMatrix3d::scaling(1.0 / OdDgnExportContext::getMasterToUORsScale()));
      pCellRef->setDefinitionName(pDbBlock->getName());

      // get clipping

      OdGiClipBoundary boundary;
      bool bClipEnabled = false;

      OdDbObjectId idDictionary = pDbRef->extensionDictionary();

      if (!idDictionary.isNull())
      {
        OdDbDictionaryPtr pXDic = OdDbDictionary::cast(OdDbObjectId(idDictionary).openObject(OdDb::kForRead));

        if (!pXDic.isNull())
        {
          OdDbDictionaryPtr pFilterDic = pXDic->getAt(OD_T("ACAD_FILTER"), OdDb::kForRead);

          if (!pFilterDic.isNull())
          {
            OdDbSpatialFilterPtr pSpFilter = pFilterDic->getAt(OD_T("SPATIAL"), OdDb::kForRead);

            if (!pSpFilter.isNull() && pSpFilter->isEnabled())
            {
              pSpFilter->getDefinition(boundary, bClipEnabled);

              if (bClipEnabled)
              {
                if (boundary.m_Points.size() == 2)
                {
                  OdGePoint2d ptMin = boundary.m_Points[0];
                  OdGePoint2d ptMax = boundary.m_Points[1];

                  OdGePoint2dArray arrRect;
                  arrRect.push_back(ptMin);
                  arrRect.push_back(ptMin + OdGeVector2d::kXAxis*(ptMax.x - ptMin.x));
                  arrRect.push_back(ptMax);
                  arrRect.push_back(ptMin + OdGeVector2d::kYAxis*(ptMax.y - ptMin.y));

                  boundary.m_Points = arrRect;
                }

                OdDgSharedCellDefinitionPtr pDgBlockDef = idDgBlock.openObject(OdDg::kForRead);

                OdGeMatrix3d matBlockToWorld = OdGeMatrix3d::translation(-pDgBlockDef->getOrigin().asVector()) * boundary.m_xInverseBlockRefXForm;
                OdGeMatrix3d matCellTransform = OdGeMatrix3d::translation(pCellRef->getOrigin().asVector()) * OdGeMatrix3d::scaling(OdDgnExportContext::getMasterToUORsScale()) * pCellRef->getTransformation();
                OdGeMatrix3d matWorldToBlock = boundary.m_xToClipSpace;
                OdGeMatrix3d matClipTransform = matWorldToBlock * matCellTransform * matBlockToWorld;

                for (OdUInt32 i = 0; i < boundary.m_Points.size(); i++)
                {
                  OdGePoint3d pt3d(boundary.m_Points[i].x, boundary.m_Points[i].y, 0.0);
                  pt3d.transformBy(matClipTransform);
                  boundary.m_Points[i] = pt3d.convert2d();
                }
              }
            }
          }
        }
      }

      // add shared cell to database

      addElementToDatabase(pCellRef, owner);
      copyElementProperties(pCellRef, pDbRef, owner->database());
      appendOdDgElementToOwner(owner, pCellRef);

      OdDgnExportContext::addDgnElement(pDbRef->objectId(), pCellRef->elementId());

      OdUInt32 uOldColorByBlock   = OdDgnExportContext::getColorByBlockIndex();
      OdUInt32 uOldLineWeightByBlock = OdDgnExportContext::getLineWeightByBlockIndex();

      OdDgnExportContext::setColorByBlockIndex(pCellRef->getColorIndex());
      OdDgnExportContext::setLineWeightByBlockIndex(pCellRef->getLineWeight());

      arrAppendedElements.push_back(pCellRef->elementId());

      // set clip

      if( bClipEnabled )
        pCellRef->setClipBoundary(boundary);

      // copy attributes and raster images of the block

      if( !idOwnerModel.isNull() )
      {
        OdDgModelPtr pModel = idOwnerModel.openObject(OdDg::kForRead);
        bool b3dTag = pModel->getModelIs3dFlag();

        OdArray<OdDbAttributePtr> arrAttributes;
        OdArray<OdDbObjectId> arrRasterImages;
        OdArray<OdDbObjectId> arrAttributeOwners;
        OdArray<OdGeMatrix3d> arrRasterTransforms;
        OdArray<OdGeMatrix3d> arrTransforms;

        getBlockAttributes(pDbRef, arrAttributes, arrRasterImages, arrAttributeOwners, arrTransforms, arrRasterTransforms, OdGeMatrix3d::kIdentity);

        for (OdUInt32 k = 0; k < arrAttributes.size(); k++)
        {
          OdDgElementId idAttrSetDef = OdDgnExportContext::getAttrDefSetForBlock(arrAttributeOwners[k]);

          if (idAttrSetDef.isNull())
            continue;

          OdDbAttributePtr pAttribute = arrAttributes[k];

          if (pAttribute.isNull())
            continue;

          OdDgTagDefinitionPtr pTagDef;

          if (!idAttrSetDef.isNull())
          {
            OdDgTagDefinitionSetPtr pTagSet = idAttrSetDef.openObject(OdDg::kForRead);

            pTagDef = pTagSet->getByName(pAttribute->tag());

            if( pTagDef.isNull() )
            {
              OdString strAttrName = pAttribute->tag();
              strAttrName.makeUpper();

              for (OdUInt32 n = 0; n < pTagSet->getCount(); n++)
              {
                OdDgTagDefinitionPtr pDef = pTagSet->getByEntryId(n);
                
                if( !pDef.isNull())
                {
                  OdString strDefName = pDef->getName();
                  strDefName.makeUpper();

                  if (strAttrName == strDefName)
                  {
                    pTagDef = pDef;
                    break;
                  }
                }
              }
            }
          }

          if (pTagDef.isNull())
            continue;

          OdDgTagElementPtr pTag = OdDgTagElement::createObject();
          pTag->setDatabaseDefaults(owner->database());
          pTag->set3dFlag(b3dTag);
          pTag->setTagDefinitionId(idAttrSetDef, pTagDef->getEntryId());
          pTag->setAssociatedFlag(true);
          pTag->setOffsetUsedFlag(true);
          pTag->setJustificationUsedFlag(true);
          pTag->setHideForSharedCellFlag(true);
          pTag->setOrigin(pAttribute->position());

          if (b3dTag)
          {
            OdGeVector3d vrZAxis = pAttribute->normal();
            OdGeVector3d vrXAxis = OdGeVector3d::kXAxis;
            double dRotation = pAttribute->rotation();

            if (fabs(dRotation) < 1.e16)
              vrXAxis.rotateBy(dRotation, OdGeVector3d::kZAxis);

            vrXAxis.transformBy(OdGeMatrix3d::planeToWorld(vrZAxis));
            OdGeMatrix3d matRotation;
            matRotation.setCoordSystem(OdGePoint3d::kOrigin, vrXAxis, vrZAxis.crossProduct(vrXAxis), vrZAxis);
            matRotation.transposeIt();
            OdGeQuaternion quatRot;
            quatRot.set(matRotation);
            pTag->setRotation3d(quatRot);
          }
          else
          {
            pTag->setRotation2d(pAttribute->rotation());
          }

          if (pAttribute->isMTextAttribute())
            pTag->setString(OdString::kEmpty);
          else
            pTag->setString(pAttribute->textString());

          OdDgElementId idDgTextStyle = OdDgnExportContext::getElementId(pAttribute->textStyle());

          if (!idDgTextStyle.isNull())
            pTag->applyTextStyle(idDgTextStyle);

          pTag->setHeightMultiplier(pAttribute->height());
          pTag->setLengthMultiplier(pTag->getHeightMultiplier() * pAttribute->widthFactor());
          pTag->setSlant(pAttribute->oblique());

          //OdDg::TextJustification uDgJust = getDgTextJustification(pAttribute->horizontalMode(), pAttribute->verticalMode());
          pTag->setJustification(OdDg::kLeftBottom);

          if (pAttribute->isMirroredInX())
            pTag->setBackwardsFlag(true);

          if (pAttribute->isMirroredInY())
            pTag->setUpsideDownFlag(true);

          if (!pTag.isNull())
          {
            addElementToDatabase(pTag, owner);
            copyElementProperties(pTag, pAttribute, owner->database());
            pTag->setInvisibleFlag(pAttribute->isInvisible());
            appendOdDgElementToOwner(owner, pTag);

            arrAppendedElements.push_back(pTag->elementId());

            OdDgnExportContext::addDgnElement(pAttribute->objectId(), pTag->elementId());

            pTag->transformBy(arrTransforms[k]);

            if (pAttribute->isMTextAttribute())
            {
              OdDbMTextPtr pDbMText = pAttribute->getMTextAttribute();
              OdDgGraphicsElementPtr pDgMText = convertMText(pDbMText, owner->database());

              pDgMText->transformBy(arrTransforms[k]);

              if (!pDgMText.isNull())
              {
                if (pDgMText->isKindOf(OdDgText2d::desc()))
                {
                  OdDgText2dPtr pDgText = pDgMText;
                  pTag->setString(pDgText->getText());
                }
                else if (pDgMText->isKindOf(OdDgText3d::desc()))
                {
                  OdDgText3dPtr pDgText = pDgMText;
                  pTag->setString(pDgText->getText());
                }
                else
                {
                  addElementToDatabase(pDgMText, owner);
                  appendOdDgElementToOwner(owner, pDgMText);
                }
              }
            }

            pTag->setAssociationId(pCellRef->elementId(), true);
          }
        }

        // Add raster images from blocks

        for (OdUInt32 l = 0; l < arrRasterImages.size(); l++)
        {
          OdDbEntityPtr pDbImage = arrRasterImages[l].openObject(OdDb::kForRead);

          OdDgnExportPE* pImageExportPE = (OdDgnExportPE*)pDbImage->queryX(OdDgnExportPE::desc());

          if (pImageExportPE && !pDbImage->isKindOf(OdDbWipeout::desc()) )
          {
            pImageExportPE->exportElement(pDbImage, owner);
            OdDgElementId idDgRaster = OdDgnExportContext::getElementId(pDbImage->objectId());

            if (!idDgRaster.isNull())
            {
              OdDgGraphicsElementPtr pRasterFrame = idDgRaster.openObject(OdDg::kForWrite);

              if (!pRasterFrame.isNull())
              {
                pRasterFrame->transformBy(arrRasterTransforms[l]);
                arrAppendedElements.push_back(idDgRaster);
              }
            }
          }
        }
      }

      OdDgnExportContext::setColorByBlockIndex(uOldColorByBlock);
      OdDgnExportContext::setLineWeightByBlockIndex(uOldLineWeightByBlock);

      // Investigate annotation scale using
    }
  }

  return true;
}

//---------------------------------------------------------------------------------------------------

void OdDbBlockReferenceExportPE::subExportElement(OdDbEntity* pDbEntity, OdDgElement* owner)
{
  OdDbBlockReference* pDbRef = (OdDbBlockReference*)(pDbEntity);

  OdDbViewRepBlockReferencePtr pViewRepBlockRef = OdDbViewRepBlockReference::cast(pDbRef);

  OdArray<OdDgElementId> arrAppendedElements;

  if( !pViewRepBlockRef.isNull() && !pViewRepBlockRef->ownerViewportId().isNull() )
  {
    OdDgnExportContext::registerViewportDepBlockRef(pViewRepBlockRef->ownerViewportId());

//    if( exportBlockReference(pDbRef, owner, arrAppendedElements) && !arrAppendedElements.isEmpty() )
//    {
//      OdDgElementId idViewportLevel = OdDgnExportContext::getViewportBlockRefLevel(pViewRepBlockRef->ownerViewportId());
//
//     if( idViewportLevel.isNull() )
//      {
//        OdString strViewportLevelName;
//        strViewportLevelName.format(L"Viewport_%X_BlockRefs", pViewRepBlockRef->ownerViewportId().getHandle());
//
//        OdDgLevelTablePtr pLevelTable = owner->database()->getLevelTable(OdDg::kForWrite);
//
//        OdDbObjectId  idLayer = pDbRef->layerId();
//        OdDgElementId idLevel = OdDgnExportContext::getElementId(idLayer);
//
//        if( idLevel.isNull() )
//          idLevel = pLevelTable->getAt(0x40); // Default level
//
//        if( !idLevel.isNull() )
//        {
//          OdDgLevelTableRecordPtr pLevel = idLevel.openObject(OdDg::kForRead);
//          OdDgLevelTableRecordPtr pLevelClone = pLevel->clone();
//          pLevelClone->setName(strViewportLevelName);
//          pLevelTable->add(pLevelClone);
//          pLevelClone->setIsDisplayedFlag(false);
//          idViewportLevel = pLevelClone->elementId();
//          OdDgnExportContext::addViewportBlockRefLevel(pViewRepBlockRef->ownerViewportId(), idViewportLevel);
//        }
//      }
//
//      if( !idViewportLevel.isNull() )
//      {
//        for (OdUInt32 n = 0; n < arrAppendedElements.size(); n++)
//        {
//          if (arrAppendedElements[n].isNull())
//            continue;
//
//          OdDgGraphicsElementPtr pGrElm = OdDgGraphicsElement::cast(arrAppendedElements[n].openObject(OdDg::kForWrite));
//
//          if (!pGrElm.isNull())
//          {
//            pGrElm->setLevelId(idViewportLevel);
//            pGrElm->setInvisibleFlag(false);
//
//            OdDgSharedCellReferencePtr pSharedCellRef = OdDgSharedCellReference::cast(pGrElm);
//
//            if( !pSharedCellRef.isNull() )
//              pSharedCellRef->setLevelOverrideFlag(true);
//          }
//        }
//      }
//    }
  }
  else if (!exportBlockReference(pDbRef, owner, arrAppendedElements))
    OdDgnExportPE::subExportElement(pDbEntity, owner);
}

//---------------------------------------------------------------------------------------------------

void setRenderMode(OdDgReferenceAttachmentViewFlags& viewFlags, OdDb::RenderMode uRenderMode)
{
  switch( uRenderMode )
  {
    case OdDb::k2DOptimized:
    {
      viewFlags.setDisplayMode(OdDgView::kWireFrame);
    } break;

    case OdDb::kWireframe:
    {
      viewFlags.setDisplayMode(OdDgView::kWireMesh);
    } break;

    case OdDb::kHiddenLine:
    {
      viewFlags.setDisplayMode(OdDgView::kHiddenLine);
    } break;

    case OdDb::kFlatShaded:
    {
      viewFlags.setDisplayMode(OdDgView::kFilledHiddenLine);
    } break;

    case OdDb::kGouraudShaded:
    {
      viewFlags.setDisplayMode(OdDgView::kPhongShade);
    } break;

    case OdDb::kFlatShadedWithWireframe:
    {
      viewFlags.setDisplayMode(OdDgView::kFilledHiddenLine);
      viewFlags.setDisplayEdgesFlag(true);
    } break;

    case OdDb::kGouraudShadedWithWireframe:
    {
      viewFlags.setDisplayMode(OdDgView::kPhongShade);
      viewFlags.setDisplayEdgesFlag(true);
    } break;
  }
}

//---------------------------------------------------------------------------------------------------

void OdDbViewportExportPE::exportViewportThroughExplode(OdDbViewport* pViewport, OdDgElement* owner)
{
  OdDgElementId idViewportBlock;

  OdDgSharedCellDefinitionTablePtr pDgBlockTable = owner->database()->getSharedCellDefinitionTable(OdDg::kForWrite);

  OdString strViewportBlockName;
  strViewportBlockName.format(L"Viewport0x%X", (OdUInt32)(pViewport->objectId().getHandle()));

  idViewportBlock = pDgBlockTable->getAt(strViewportBlockName);
  OdGePoint3d ptCenterOfViewport = OdGePoint3d::kOrigin;

  if( idViewportBlock.isNull() )
  {
    OdDgSharedCellDefinitionPtr pDgBlockDef = OdDgSharedCellDefinition::createObject();
    pDgBlockDef->setName(strViewportBlockName);
    pDgBlockDef->setOrigin(OdGePoint3d::kOrigin);
    pDgBlockDef->set3dFormatFlag(OdDgnExportContext::is3d());
    pDgBlockTable->add(pDgBlockDef);

    double dOldScaleFactor = OdDgnExportContext::getLineStyleScaleCorrectionFactor();
    OdDgnExportContext::setLineStyleScaleCorrectionFactor(1.0 / OdDgnExportContext::getMasterToUORsScale());

    OdRxObjectPtrArray arrExplode;
    OdResult retVal = pViewport->explodeGeometry(arrExplode);

    for (OdUInt32 i = 0; i < arrExplode.size(); i++)
      OdDgnExportPE::subExportElement((OdDbEntityPtr)arrExplode[i], pDgBlockDef);

    OdGeExtents3d extBlockDef;

    if (pDgBlockDef->getGeomExtents(extBlockDef) == eOk)
    {
      pDgBlockDef->transformBy(-extBlockDef.center().asVector());
      ptCenterOfViewport = extBlockDef.center();
    }

    OdDgnExportContext::setLineStyleScaleCorrectionFactor(dOldScaleFactor);

    pDgBlockDef->transformBy(OdGeMatrix3d::scaling(OdDgnExportContext::getMasterToUORsScale()));

    idViewportBlock = pDgBlockDef->elementId();
  }

  if( !idViewportBlock.isNull() )
  {
    OdDgSharedCellReferencePtr pCellRef = OdDgSharedCellReference::createObject();

    OdDgElementId idOwnerModel = getOwnerModelId(owner);
    pCellRef->setOrigin(ptCenterOfViewport);
    pCellRef->setTransformation(OdGeMatrix3d::scaling(1.0 / OdDgnExportContext::getMasterToUORsScale()));
    pCellRef->setDefinitionName(strViewportBlockName);

    addElementToDatabase(pCellRef, owner);
    copyElementProperties(pCellRef, pViewport, owner->database());
    pCellRef->setInvisibleFlag(!pViewport->isOn());

    appendOdDgElementToOwner(owner, pCellRef);

    OdDgnExportContext::addDgnElement(pViewport->objectId(), pCellRef->elementId());
  }
}

//---------------------------------------------------------------------------------------------------

void OdDbViewportExportPE::subExportElement(OdDbEntity* pDbEntity, OdDgElement* owner)
{
  OdDbViewport* pViewport = (OdDbViewport*)(pDbEntity);

  if( OdDgnExportContext::hasViewportDepBlockRefs(pViewport->objectId()))
  {
    exportViewportThroughExplode(pViewport, owner);
    return;
  }

  OdDgElementId idMainModel = OdDgnExportContext::getDgnModelSpaceModelId();

  if( idMainModel.isNull() )
    return;

  OdDgElementId idModel = getOwnerModelId(owner);

  if (idModel.isNull())
  {
    ODA_ASSERT_ONCE(!"Can't get dgn model.");
    return;
  }

  OdDgModelPtr pModel     = idModel.openObject(OdDg::kForWrite);
  OdDgModelPtr pMainModel = idMainModel.openObject(OdDg::kForRead);
  OdAbstractViewPEPtr pDbAbstractView = OdAbstractViewPEPtr(pViewport);

  double dScale = pViewport->height() / pViewport->viewHeight();

  OdGePoint3d ptOrigin = pDbAbstractView->target(pViewport);
  OdGePoint3d ptCameraPos = ptOrigin + pViewport->viewDirection();

  ptOrigin    *= OdDgnExportContext::getMasterToUORsScale();
  ptCameraPos *= OdDgnExportContext::getMasterToUORsScale();
  double dFocalLength = pViewport->viewDirection().length() * OdDgnExportContext::getMasterToUORsScale();
  double dZFront = pViewport->frontClipDistance() * OdDgnExportContext::getMasterToUORsScale();
  double dZBack  = pViewport->backClipDistance() * OdDgnExportContext::getMasterToUORsScale();

  OdGeMatrix3d matTransform = pDbAbstractView->worldToEye(pViewport);
  matTransform.setTranslation(OdGeVector3d::kIdentity);

  OdGeVector3d vrXAxis = matTransform.getCsXAxis();
  OdGeVector3d vrYAxis = matTransform.getCsYAxis();
  OdGeVector3d vrZAxis = matTransform.getCsZAxis();

  vrXAxis.normalize();
  vrYAxis.normalize();
  vrZAxis.normalize();

  OdGeMatrix3d matRotation;
  matRotation.setCoordSystem(OdGePoint3d::kOrigin, vrXAxis, vrYAxis, vrZAxis);

  OdDgReferenceAttachmentHeaderPtr pDgXRef = OdDgReferenceAttachmentHeader::createObject();
  pDgXRef->setFileName(OdString::kEmpty);
  pDgXRef->setModelName(pMainModel->getName());
  pDgXRef->setMasterOrigin(pViewport->centerPoint());
  pDgXRef->setReferenceOrigin(ptOrigin);
  pDgXRef->setTransformation(matRotation);
  pDgXRef->setScale(dScale);

  OdInt16 uNumber = OdDgnExportContext::getNextViewportNumber();
  pDgXRef->setDisplayFlag(pViewport->isOn());
  pDgXRef->setFileNumber(uNumber);

  pDgXRef->setNestDepth(99);
  pDgXRef->setCameraPosition(ptCameraPos);
  pDgXRef->setCameraFocalLength(dFocalLength);
  pDgXRef->setZFront(dZFront);
  pDgXRef->setZBack(dZBack);
  pDgXRef->setClipBackFlag(false);
  pDgXRef->setClipFrontFlag(false);
  pDgXRef->setRotateClippingFlag(true);
  pDgXRef->setLineStyleScaleFlag(true);
  
  OdDgElementId idDgLayer = OdDgnExportContext::getElementId(pViewport->layerId());

  if (!idDgLayer.isNull())
  {
    OdDgLevelTableRecordPtr pLevel = idDgLayer.openObject(OdDg::kForRead);
    pDgXRef->setLevelEntryId(pLevel->getEntryId());
  }
  else
    pDgXRef->setLevelEntryId(0);

  OdString strName;
  strName.format(L"Viewport %d", uNumber);

  pDgXRef->setLogicalName(strName);
  pDgXRef->setViewportFlag(true);

  OdGePoint2dArray arrClipPts;

  OdGePoint2d ptCenter = OdGePoint2d::kOrigin;
  double dHeight = pViewport->height();
  double dWidth  = pViewport->width();

  pDgXRef->setClipPointsCount(5);
  pDgXRef->setClipPoint(0, ptCenter - OdGeVector2d::kXAxis * dWidth / 2.0 - OdGeVector2d::kYAxis * dHeight / 2.0);
  pDgXRef->setClipPoint(1, ptCenter + OdGeVector2d::kXAxis * dWidth / 2.0 - OdGeVector2d::kYAxis * dHeight / 2.0);
  pDgXRef->setClipPoint(2, ptCenter + OdGeVector2d::kXAxis * dWidth / 2.0 + OdGeVector2d::kYAxis * dHeight / 2.0);
  pDgXRef->setClipPoint(3, ptCenter - OdGeVector2d::kXAxis * dWidth / 2.0 + OdGeVector2d::kYAxis * dHeight / 2.0);
  pDgXRef->setClipPoint(4, ptCenter - OdGeVector2d::kXAxis * dWidth / 2.0 - OdGeVector2d::kYAxis * dHeight / 2.0);

  pDgXRef->setClipRotationMatrix(OdGeMatrix3d::kIdentity);

  OdDgReferenceAttachmentViewFlags viewFlags = pDgXRef->getViewFlags(0);
  setRenderMode(viewFlags, pViewport->renderMode());
  pDgXRef->setViewFlags(0, viewFlags);

  pModel->addElement(pDgXRef);

  if( !pViewport->objectId().isNull() )
    OdDgnExportContext::addDgnElement(pViewport->objectId(), pDgXRef->elementId());

  //Create level mask

  OdDbLayerTablePtr pLayerTable = pDbEntity->database()->getLayerTableId().openObject(OdDb::kForRead);
  OdDbSymbolTableIteratorPtr pIter = pLayerTable->newIterator();

  OdDgLevelMaskPtr pLevelMask = OdDgLevelMask::createObject();
  pLevelMask->setViewIndex(0);
  pLevelMask->setReferenceAttachId(pDgXRef->elementId());
  pDgXRef->add(pLevelMask);

  for(; !pIter->done(); pIter->step())
  {
    OdDbObjectId idLayer = pIter->getRecordId();
    bool bLayerIsFrozen = pViewport->isLayerFrozenInViewport(idLayer);
    OdDgElementId idLevel = OdDgnExportContext::getElementId(idLayer);

    if( idLevel.isNull() )
      continue;

    OdDgLevelTableRecordPtr pLevel = idLevel.openObject(OdDg::kForRead);

    pLevelMask->setLevelIsVisible(pLevel->getEntryId(), pLevel->getName(), !bLayerIsFrozen);
  }

  OdDbObjectId  idViewport;
  OdDgElementId idViewportBlockLevel;

//  for( OdUInt32 k = 0; k < OdDgnExportContext::getViewportBlockRefLevelsCount(); k++ )
//  {
//    OdDgnExportContext::getViewportBlockRefLevel(k, idViewport, idViewportBlockLevel);
//
//   if( !idViewportBlockLevel.isNull() )
//    {
//      OdDgLevelTableRecordPtr pLevel = idViewportBlockLevel.openObject(OdDg::kForRead);
//      bool bFreezeLevel = idViewport != pViewport->objectId();
//      pLevelMask->setLevelIsVisible(pLevel->getEntryId(), pLevel->getName(), !bFreezeLevel);
//    }
//  }
}

//---------------------------------------------------------------------------------------------------

void OdDbViewBorderExportPE::subExportElement(OdDbEntity* pDbEntity, OdDgElement* owner)
{
  if( OdDgnExportContext::is3d() )
  {
    OdDgCellHeader3dPtr pEmptyCell = OdDgCellHeader3d::createObject();
    pEmptyCell->setDatabaseDefaults(owner->database());
    OdDgnExportPE::subExportElement(pDbEntity, pEmptyCell);

    OdDgElementIteratorPtr pCellIter = pEmptyCell->createIterator();

    if( !pCellIter->done() )
    {
      OdDgElementPtr pBorderElm = pCellIter->item().openObject(OdDg::kForRead);

      if( !pBorderElm.isNull() && pBorderElm->isKindOf(OdDgShape3d::desc()) )
      {
        OdDgShape3dPtr pBorder = pBorderElm->clone();
        pBorder->setFillType(OdDg::kNoFill);
        pBorder->setColorIndex(0);
        appendOdDgElementToOwner(owner, pBorder);
        OdDgnExportContext::addDgnElement(pDbEntity->objectId(), pBorder->elementId());
      }
    }
  }
  else
  {
    OdDgCellHeader2dPtr pEmptyCell = OdDgCellHeader2d::createObject();
    pEmptyCell->setDatabaseDefaults(owner->database());
    OdDgnExportPE::subExportElement(pDbEntity, pEmptyCell);

    OdDgElementIteratorPtr pCellIter = pEmptyCell->createIterator();

    if (!pCellIter->done())
    {
      OdDgElementPtr pBorderElm = pCellIter->item().openObject(OdDg::kForRead);

      if (!pBorderElm.isNull() && pBorderElm->isKindOf(OdDgShape2d::desc()))
      {
        OdDgShape2dPtr pBorder = pBorderElm->clone();
        pBorder->setFillType(OdDg::kNoFill);
        pBorder->setColorIndex(0);
        appendOdDgElementToOwner(owner, pBorder);
        OdDgnExportContext::addDgnElement(pDbEntity->objectId(), pBorder->elementId());
      }
    }
  }
}

//---------------------------------------------------------------------------------------------------

}
