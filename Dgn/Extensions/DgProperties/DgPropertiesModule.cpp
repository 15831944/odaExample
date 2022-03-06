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

#include "DgElementProperties.h"
#include "DgDatabaseProperties.h"
#include "DgPropertiesModule.h"
#include "DgGraphicsElmProperties.h"
#include "DgTableProperties.h"
#include "DgCurveElementProperties.h"
#include "DgLevelTableRecord.h"
#include "DgSharedCellDefinition.h"
#include "DgExtraProperties.h"
#include "DgComplexCurve.h"
#include "DgSharedCellReference.h"
#include "DgReferenceAttach.h"
#include "DgLevelFilterTableRecord.h"
#include "DgDimStyleTableRecord.h"
#include "DgMultilineStyleTableRecord.h"
#include "DgPrintStyleTableRecord.h"
#include "DgEnvironmentMap.h"

OdRxFacetProviderPtr OdDgCDAFacetProvider::instance;

/////////////////////////////////////////////////////////////////////
// OdDgCDAFacetProvider /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

OdRxFacetProviderPtr OdDgCDAFacetProvider::createObject()
{
  instance = OdRxObjectImpl<OdDgCDAFacetProvider>::createObject();
  return instance;
}

void OdDgCDAFacetProvider::addProvider()
{
  OdRxMemberQueryEngine::theEngine()->addFacetProvider(instance);
}

void OdDgCDAFacetProvider::removeProvider()
{
  OdRxMemberQueryEngine::theEngine()->removeFacetProvider(instance);
}

void OdDgCDAFacetProvider::getFacets(const OdRxObject* pO, const OdRxMemberQueryContext* pContext, OdArray<OdRxClassPtr>& facets)
{
  if (!(OdDgECClassInstance::cast(pO)).isNull())
  {
    OdRxClassPtr pClassInstanceFacet = OdDgECClassInstancePropertyFacet::createObject();
    ::odrxSetMemberConstructor(pClassInstanceFacet, &OdDgECClassInstancePropertyFacet::makeMembers, (void*)pO);
    facets.append(pClassInstanceFacet);
  }
  else if( !(OdDgElement::cast(pO)).isNull() )
  {
    OdRxClassPtr pElementFacet = OdDgElementPropertyFacet::createObject();
    ::odrxSetMemberConstructor(pElementFacet, &OdDgElementPropertyFacet::makeMembers, (void*)pO);
    facets.append(pElementFacet);
  }
}

inline void appendElementProperties(const OdDgElement* pElement, OdRxMemberCollectionBuilder& collectionBuilder)
{
  OdDgDatabase* pDb = pElement->database();

  try
  {
    if (!pElement)
      return;

    OdDgECClassInstanceElementPEPtr pECClassInstancePE = pElement;

    if (pECClassInstancePE.isNull())
      return;

    OdUInt32 uWeightCount = 1;

    for (OdUInt32 i = 0; i < pECClassInstancePE->getECClassInstanceCount(pElement); i++)
    {
      OdDgECClassInstancePtr pClassInstance = pECClassInstancePE->getECClassInstance(pElement, i);

      if (pClassInstance.isNull())
        continue;

      for (OdUInt32 j = 0; j < pClassInstance->getPropertyInstanceCount(); j++)
      {
        OdDgECPropertyInstance ecProp = pClassInstance->getPropertyInstance(j);

        switch (ecProp.getType())
        {
          case OdDgECPropertyInstance::kBool:
          case OdDgECPropertyInstance::kByte:
          case OdDgECPropertyInstance::kShort:
          case OdDgECPropertyInstance::kInt32:
          case OdDgECPropertyInstance::kInt64:
          case OdDgECPropertyInstance::kDouble:
          case OdDgECPropertyInstance::kString:
          case OdDgECPropertyInstance::kPoint3d:
          case OdDgECPropertyInstance::kDateAndTime:
          case OdDgECPropertyInstance::kECClassInstance:
          {
            collectionBuilder.add(OdDgElementECProperty::createObject(convertECSchemaItemNameToString(ecProp.getName()), ecProp, pClassInstance->getECClassReference(), uWeightCount, collectionBuilder.owner()));
            uWeightCount++;
          } break;

          case OdDgECPropertyInstance::kBoolArray:
          case OdDgECPropertyInstance::kByteArray:
          case OdDgECPropertyInstance::kShortArray:
          case OdDgECPropertyInstance::kInt32Array:
          case OdDgECPropertyInstance::kInt64Array:
          case OdDgECPropertyInstance::kDoubleArray:
          case OdDgECPropertyInstance::kStringArray:
          case OdDgECPropertyInstance::kPoint3dArray:
          case OdDgECPropertyInstance::kDateTimeArray:
          case OdDgECPropertyInstance::kECClassInstanceArray:
          {
            collectionBuilder.add(OdDgElementArrayECProperty::createObject(convertECSchemaItemNameToString(ecProp.getName()), ecProp, pClassInstance->getECClassReference(), uWeightCount, collectionBuilder.owner()));
            uWeightCount++;
          } break;
        }
      }
    }
  }
  catch (...)
  {}
}

inline void appendClassInstanceProperties(const OdDgECClassInstance* pClassInstance, OdRxMemberCollectionBuilder& collectionBuilder)
{
  try
  {
    if (!pClassInstance)
      return;

    OdUInt32 uWeightCount = 1;

    for (OdUInt32 j = 0; j < pClassInstance->getPropertyInstanceCount(); j++)
    {
      OdDgECPropertyInstance ecProp = pClassInstance->getPropertyInstance(j);

      switch (ecProp.getType())
      {
        case OdDgECPropertyInstance::kBool:
        case OdDgECPropertyInstance::kByte:
        case OdDgECPropertyInstance::kShort:
        case OdDgECPropertyInstance::kInt32:
        case OdDgECPropertyInstance::kInt64:
        case OdDgECPropertyInstance::kDouble:
        case OdDgECPropertyInstance::kString:
        case OdDgECPropertyInstance::kPoint3d:
        case OdDgECPropertyInstance::kDateAndTime:
        case OdDgECPropertyInstance::kECClassInstance:
        {
          collectionBuilder.add(OdDgElementECProperty::createObject(convertECSchemaItemNameToString(ecProp.getName()), ecProp, pClassInstance->getECClassReference(), uWeightCount, collectionBuilder.owner()));
          uWeightCount++;
        } break;

        case OdDgECPropertyInstance::kBoolArray:
        case OdDgECPropertyInstance::kByteArray:
        case OdDgECPropertyInstance::kShortArray:
        case OdDgECPropertyInstance::kInt32Array:
        case OdDgECPropertyInstance::kInt64Array:
        case OdDgECPropertyInstance::kDoubleArray:
        case OdDgECPropertyInstance::kStringArray:
        case OdDgECPropertyInstance::kPoint3dArray:
        case OdDgECPropertyInstance::kDateTimeArray:
        case OdDgECPropertyInstance::kECClassInstanceArray:
        {
          collectionBuilder.add(OdDgElementArrayECProperty::createObject(convertECSchemaItemNameToString(ecProp.getName()), ecProp, pClassInstance->getECClassReference(), uWeightCount, collectionBuilder.owner()));
          uWeightCount++;
        } break;
      }
    }
  }
  catch (...)
  {
  }
}

/////////////////////////////////////////////////////////////////////
// OdDgElementPropertyFacet       ///////////////////////////////////
/////////////////////////////////////////////////////////////////////

void OdDgElementPropertyFacet::makeMembers(OdRxMemberCollectionBuilder& collectionBuilder, void* data)
{
  const OdRxObject* pO = (const OdRxObject*)data;
  OdDgElementPtr pElement = OdDgElement::cast(pO);
  if (pElement.isNull())
    return;

  appendElementProperties(pElement, collectionBuilder);
}

/////////////////////////////////////////////////////////////////////
// OdDgECClassInstancePropertyFacet /////////////////////////////////
/////////////////////////////////////////////////////////////////////

void OdDgECClassInstancePropertyFacet::makeMembers(OdRxMemberCollectionBuilder& collectionBuilder, void* data)
{
  const OdRxObject* pO = (const OdRxObject*)data;
  OdDgECClassInstancePtr pClassInstance = OdDgECClassInstance::cast(pO);
  if (pClassInstance.isNull())
    return;

  appendClassInstanceProperties(pClassInstance , collectionBuilder);
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgElementProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgElementElementIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgElementODAUniqueIDProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgElementElementTypeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgElementElementSubTypeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgElementNameProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgElementModificationTimeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgElementNewProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgElementModifiedProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgElementLockedProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgElementECClassInstancesProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgDatabaseProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgDatabaseLevelTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseLevelFilterTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseFontTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseTextStyleTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseLineStyleTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseModelsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseMajorVersionProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseMinorVersionProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseFileNameProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseColorPaletteProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseMaterialTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseDisplayStyleTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSharedCellDefinitionsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseRetainOriginalThumbnailBitmapProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseDimStyleTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseMultilineStyleTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseRegAppsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseViewGroupsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseNamedViewsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabasePrintStylesProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseModelTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseTagDefinitionsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseElementTemplatesProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseLinkSetsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseNonModelElementCollectionProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseEnvironmentMapsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabasePrototypeElementsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseDictionaryTableIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseControlFlagsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseLockFlagsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseExtLockFlagsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSaveMaterialAssignmentTableFileFlagProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAngleRndProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseXActScaleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseYActScaleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseZActScaleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseRoundScaleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAzimuthProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseExtMinProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseExtMaxProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActiveLevelEntryIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActiveLineStyleEntryIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActiveLineWeightProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActiveColorIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseFillColorProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActivePropsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseLineStyleInfoProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseLineStyleScaleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseMultiLineFlagsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActiveTextStyleEntryIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseTextScaleLockProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActiveViewGroupIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActiveModelIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAngleFormatProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAngleReadoutPrecProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAngleReadoutDirectionModeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAngleReadoutBaseAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAngleReadoutClockwiseFlagProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseTentativeModeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseTentativeSubModeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseKeyPointDividendProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseDefaultSnapModeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSystemClassProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseDMRSFlagProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseDMRSLinkageGenerationModeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAutoDimFlagsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAssocLockMaskProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActiveCellProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActiveTermCellProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActiveTermScaleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActivePatternCellProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActivePatternScaleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActivePatternAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActivePatternAngle2Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActivePatternRowSpacingProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActivePatternColumnSpacingProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabasePatternToleranceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActivePointTypeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActivePointSymbolProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseActivePointCellProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAreaPatternAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAreaPatternRowSpacingProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAreaPatternColumnSpacingProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseReservedCellProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseZRange2dLowProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseZRange2dHighProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseStreamDeltaProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseStreamToleranceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAngleToleranceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAreaToleranceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseHighlightColorIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseXorColorIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAxisLockAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAxisLockOriginProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseChamferDist1Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseChamferDist2Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAutochainToleranceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseConslineDistanceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseArcRadiusProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseArcLengthProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseConeRadius1Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseConeRadius2Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabasePolygonRadiusProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSurrevAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseExtendDistanceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseFilletRadiusProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseCopparDistanceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseArrayRowDistanceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseArrayColumnDistanceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseArrayFillAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabasePointDistanceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabasePolygonEdgesProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabasePointsBetweenProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseArrayNumItemsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseArrayNumRowsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseArrayNumColsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseArrayRotateProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseBSplineOrderProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseDispAttrTypeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAmbientFlagProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseFlashbulbFlagProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSolarFlagProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSolarShadowsFlagProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSolarShadowResolutionProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseKeepSolarDirectionFlagProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseLatitudeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseLongitudeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSolarTimeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSolarYearProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseGMTOffsetProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSolarDirectionProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSolarVectorOverrideProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSolarIntensityProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseAmbientIntensityProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseFlashIntensityProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseNearDepthDensityProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseFarDepthDensityProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseNearDepthDistanceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseHazeColorProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseShadowToleranceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseStrokeToleranceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseMaxPolygonSizeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseArcMinimumProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseExactHLineAccuracyProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseExactHLineToleranceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSelectionHighlightOverrideProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseSelectionHighlightColorProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseCellFileNameProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseBackgroundFileProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseDesignCenterUnitsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseNextGraphicGroupProperty::createObject(b.owner()));
  b.add(properties.last()); 
  properties.append(OdDgDatabaseHandseedProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseLastSaveTimeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseDefaultModelIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDatabaseOriginalFileVersionProperty::createObject(b.owner()));
  b.add(properties.last());

}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgGraphicsElementProperties(OdRxMemberCollectionBuilder& b, void*)
{
  //properties.append(OdDgGraphicsElementColorIndexProperty::createObject(b.owner()));
  //b.add(properties.last());
  properties.append(OdDgGraphicsElementColorProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementGraphicsGroupIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementClassProperty::createObject(b.owner()));
  b.add(properties.last());
  //properties.append(OdDgGraphicsElementLevelIndexProperty::createObject(b.owner()));
  //b.add(properties.last());
  properties.append(OdDgGraphicsElementLevelProperty::createObject(b.owner()));
  b.add(properties.last());
  //properties.append(OdDgGraphicsElementLevelNameProperty::createObject(b.owner()));
  //b.add(properties.last());
  //properties.append(OdDgGraphicsElementLineStyleIndexProperty::createObject(b.owner()));
  //b.add(properties.last());
  properties.append(OdDgGraphicsElementLineStyleProperty::createObject(b.owner()));
  b.add(properties.last());
  //properties.append(OdDgGraphicsElementLineStyleNameProperty::createObject(b.owner()));
  //b.add(properties.last());
  properties.append(OdDgGraphicsElementLineWeightProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementThicknessProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementPriorityProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementInvisibleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElement3DProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementViewIndependentProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementNonPlanarProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementNotSnappableProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementHBitProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementTransparencyProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementExtentsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgGraphicsElementDisplayStyleProperty::createObject(b.owner()));
  b.add(properties.last());
  //properties.append(OdDgGraphicsElementDisplayStyleNameProperty::createObject(b.owner()));
  //b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLevelTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLevelTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLineStyleTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLineStyleTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgMaterialTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgMaterialTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgModelTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgModelTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgDisplayStyleTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgDisplayStyleTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLevelFilterTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLevelFilterTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgDimStyleTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgDimStyleTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgMultilineStyleTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgMultilineStyleTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgViewGroupTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgViewGroupTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgPrintStyleTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgPrintStyleTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgTagDefinitionSetTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgTagDefinitionSetTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLinkSetTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLinkSetTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgEnvironmentMapTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgEnvironmentMapTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgPrototypeElementTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgPrototypeElementTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgDictionaryTableProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgDictionaryTableItemsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLevelProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLevelTableRecordIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLevelTableRecordNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLineStyleProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLineStyleTableRecordIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLineStyleTableRecordNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgMaterialProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgMaterialTableRecordNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgDisplayStyleProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgDisplayStyleTableRecordIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDisplayStyleTableRecordNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLevelFilterProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLevelFilterTableRecordIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLevelFilterTableRecordNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//---------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgDimStyleProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgDimStyleTableRecordIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDimStyleTableRecordNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgMultilineStyleProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgMultilineStyleTableRecordIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgMultilineStyleTableRecordNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgViewGroupProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgViewGroupIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgViewGroupNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgPrintStyleProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgPrintStyleTableRecordNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgTagDefinitionSetProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgTagDefinitionSetNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLinkSetProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLinkSetNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgPrototypeElementProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgPrototypeElementIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgPrototypeElementNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgDictionaryProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgDictionaryTableRecordIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDictionaryTableRecordNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgCurveElement2dProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgCurveElement2dLineStyleScaleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement2dLineStyleModifiersProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement2dClosedProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement2dPeriodicProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement2dStartParamProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement2dEndParamProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement2dStartPointProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement2dEndPointProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgCurveElement3dProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgCurveElement3dLineStyleScaleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement3dLineStyleModifiersProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement3dClosedProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement3dPeriodicProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement3dStartParamProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement3dEndParamProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement3dStartPointProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCurveElement3dEndPointProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLine2dProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLine2dStartPointProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLine2dEndPointProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLine3dProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLine3dStartPointProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLine3dEndPointProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgArc2dProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgArc2dPrimaryAxisProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc2dSecondaryAxisProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc2dPrimaryAxisProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc2dRotationAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc2dOriginProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc2dStartAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc2dSweepAngleProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgArc3dProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgArc3dPrimaryAxisProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc3dSecondaryAxisProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc3dPrimaryAxisProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc3dRotationProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc3dNormalProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc3dOriginProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc3dStartAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgArc3dSweepAngleProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgCellHeader2dProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgCellHeader2dNameProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader2dColorProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader2dLevelProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader2dLineStyleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader2dLineWeightProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader2dOriginProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader2dTransformationProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader2dElementsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader2dGroupedHoleProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgCellHeader3dProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgCellHeader3dNameProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader3dColorProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader3dLevelProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader3dLineStyleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader3dLineWeightProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader3dOriginProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader3dTransformationProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader3dElementsProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCellHeader3dGroupedHoleProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgShape2dProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgShape2dVerticesProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgShape2dMaterialProperty::createObject(b.owner()));
  b.add(properties.last());
  //properties.append(OdDgShape2dMaterialNameProperty::createObject(b.owner()));
  //b.add(properties.last());
  properties.append(OdDgShape2dFillProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgShape2dHatchPatternProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgShape3dProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgShape3dVerticesProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgShape3dMaterialProperty::createObject(b.owner()));
  b.add(properties.last());
  //properties.append(OdDgShape3dMaterialNameProperty::createObject(b.owner()));
  //b.add(properties.last());
  properties.append(OdDgShape3dFillProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgShape3dHatchPatternProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgSharedCellDefinitionProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgSharedCellDefinitionNameProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSharedCellDefinitionElementsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgSharedCellReferenceProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgSharedCellReferenceBlockDefinitionProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgReferenceAttachmentHeaderProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgReferenceAttachmentHeaderReferencedModelProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgComplexCurveProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgComplexCurveElementsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgECClassInstanceProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgECClassInstanceSchemaNameProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgECClassInstanceClassNameProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgModelProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgModelNameProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgModelElementsProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgHatchPatternProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgHatchPatternPatternTypeProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPatternToleranceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPatternUseToleranceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPatternRotationProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPattern2dRotationProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPatternUseRotationProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPatternLowMultilineIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPatternHighMultilineIndexProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPatternUseMultilineIndicesProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPatternOffsetProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPatternUseOffsetProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgHatchPatternSnappableProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgLinearHatchPatternProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgLinearHatchPatternSpaceProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLinearHatchPatternAngleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLinearHatchPatternLineStyleEntryIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLinearHatchPatternUseLineStyleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLinearHatchPatternLineWeightProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLinearHatchPatternUseLineWeightProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLinearHatchPatternLineColorProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgLinearHatchPatternUseLineColorProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgCrossHatchPatternProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgCrossHatchPatternSpace1Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCrossHatchPatternSpace2Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCrossHatchPatternAngle1Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCrossHatchPatternAngle2Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCrossHatchPatternLineStyleEntryIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCrossHatchPatternUseLineStyleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCrossHatchPatternLineWeightProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCrossHatchPatternUseLineWeightProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCrossHatchPatternLineColorProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgCrossHatchPatternUseLineColorProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgSymbolHatchPatternProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgSymbolHatchPatternSpace1Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternSpace2Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternAngle1Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternAngle2Property::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternLineStyleEntryIdProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternUseLineStyleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternLineWeightProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternUseLineWeightProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternColorProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternUseColorProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternTrueScaleProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgSymbolHatchPatternSymbolIdProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::constructOdDgDWGHatchPatternProperties(OdRxMemberCollectionBuilder& b, void*)
{
  properties.append(OdDgDWGHatchPatternPatternNameProperty::createObject(b.owner()));
  b.add(properties.last());
  properties.append(OdDgDWGHatchPatternDwgLinesProperty::createObject(b.owner()));
  b.add(properties.last());
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::initApp()
{
  OdRxFacetProviderPtr instance = OdDgCDAFacetProvider::createObject();

  ::odrxDynamicLinker()->loadModule(L"RxProperties");
  ::odrxSetMemberConstructor(OdDgElement::desc(), constructOdDgElementProperties);
  ::odrxSetMemberConstructor(OdDgDatabase::desc(), constructOdDgDatabaseProperties);
  ::odrxSetMemberConstructor(OdDgGraphicsElement::desc(), constructOdDgGraphicsElementProperties);
  ::odrxSetMemberConstructor(OdDgLevelTable::desc(), constructOdDgLevelTableProperties);
  ::odrxSetMemberConstructor(OdDgLineStyleTable::desc(), constructOdDgLineStyleTableProperties);
  ::odrxSetMemberConstructor(OdDgMaterialTable::desc(), constructOdDgMaterialTableProperties);
  ::odrxSetMemberConstructor(OdDgModelTable::desc(), constructOdDgModelTableProperties);
  ::odrxSetMemberConstructor(OdDgDisplayStyleTable::desc(), constructOdDgDisplayStyleTableProperties);
  ::odrxSetMemberConstructor(OdDgLevelFilterTable::desc(), constructOdDgLevelFilterTableProperties);
  ::odrxSetMemberConstructor(OdDgDimStyleTable::desc(), constructOdDgDimStyleTableProperties);
  ::odrxSetMemberConstructor(OdDgMultilineStyleTable::desc(), constructOdDgMultilineStyleTableProperties);
  ::odrxSetMemberConstructor(OdDgViewGroupTable::desc(), constructOdDgViewGroupTableProperties);
  ::odrxSetMemberConstructor(OdDgPrintStyleTable::desc(), constructOdDgPrintStyleTableProperties);
  ::odrxSetMemberConstructor(OdDgTagDefinitionSetTable::desc(), constructOdDgTagDefinitionSetTableProperties);
  ::odrxSetMemberConstructor(OdDgLinkSetTable::desc(), constructOdDgLinkSetTableProperties);
  ::odrxSetMemberConstructor(OdDgEnvironmentMapTable::desc(), constructOdDgEnvironmentMapTableProperties);
  ::odrxSetMemberConstructor(OdDgPrototypeElementTable::desc(), constructOdDgPrototypeElementTableProperties);
  ::odrxSetMemberConstructor(OdDgDictionaryTable::desc(), constructOdDgDictionaryTableProperties);
  ::odrxSetMemberConstructor(OdDgLevelTableRecord::desc(), constructOdDgLevelProperties);
  ::odrxSetMemberConstructor(OdDgLineStyleTableRecord::desc(), constructOdDgLineStyleProperties);
  ::odrxSetMemberConstructor(OdDgMaterialTableRecord::desc(), constructOdDgMaterialProperties);
  ::odrxSetMemberConstructor(OdDgDisplayStyleTableRecord::desc(), constructOdDgDisplayStyleProperties);
  ::odrxSetMemberConstructor(OdDgLevelFilterTableRecord::desc(), constructOdDgLevelFilterProperties);
  ::odrxSetMemberConstructor(OdDgDimStyleTableRecord::desc(), constructOdDgDimStyleProperties);
  ::odrxSetMemberConstructor(OdDgMultilineStyleTableRecord::desc(), constructOdDgMultilineStyleProperties);
  ::odrxSetMemberConstructor(OdDgViewGroup::desc(), constructOdDgViewGroupProperties);
  ::odrxSetMemberConstructor(OdDgPrintStyleTableRecord::desc(), constructOdDgPrintStyleProperties);
  ::odrxSetMemberConstructor(OdDgTagDefinitionSet::desc(), constructOdDgTagDefinitionSetProperties);
  ::odrxSetMemberConstructor(OdDgLinkSet::desc(), constructOdDgLinkSetProperties);
  ::odrxSetMemberConstructor(OdDgPrototypeElement::desc(), constructOdDgPrototypeElementProperties);
  ::odrxSetMemberConstructor(OdDgDictionaryTableRecord::desc(), constructOdDgDictionaryProperties);
  ::odrxSetMemberConstructor(OdDgCurveElement2d::desc(), constructOdDgCurveElement2dProperties);
  ::odrxSetMemberConstructor(OdDgCurveElement3d::desc(), constructOdDgCurveElement3dProperties);
  ::odrxSetMemberConstructor(OdDgLine2d::desc(), constructOdDgLine2dProperties);
  ::odrxSetMemberConstructor(OdDgLine3d::desc(), constructOdDgLine3dProperties);
  ::odrxSetMemberConstructor(OdDgArc2d::desc(), constructOdDgArc2dProperties);
  ::odrxSetMemberConstructor(OdDgArc3d::desc(), constructOdDgArc3dProperties);
  ::odrxSetMemberConstructor(OdDgCellHeader2d::desc(), constructOdDgCellHeader2dProperties);
  ::odrxSetMemberConstructor(OdDgCellHeader3d::desc(), constructOdDgCellHeader3dProperties);
  ::odrxSetMemberConstructor(OdDgShape2d::desc(), constructOdDgShape2dProperties);
  ::odrxSetMemberConstructor(OdDgShape3d::desc(), constructOdDgShape3dProperties);
  ::odrxSetMemberConstructor(OdDgSharedCellDefinition::desc(), constructOdDgSharedCellDefinitionProperties);
  ::odrxSetMemberConstructor(OdDgHatchPattern::desc(), constructOdDgHatchPatternProperties);
  ::odrxSetMemberConstructor(OdDgLinearHatchPattern::desc(), constructOdDgLinearHatchPatternProperties);
  ::odrxSetMemberConstructor(OdDgCrossHatchPattern::desc(), constructOdDgCrossHatchPatternProperties);
  ::odrxSetMemberConstructor(OdDgSymbolHatchPattern::desc(), constructOdDgSymbolHatchPatternProperties);
  ::odrxSetMemberConstructor(OdDgDWGHatchPattern::desc(), constructOdDgDWGHatchPatternProperties);
  ::odrxSetMemberConstructor(OdDgModel::desc(), constructOdDgModelProperties);
  ::odrxSetMemberConstructor(OdDgSharedCellReference::desc(), constructOdDgSharedCellReferenceProperties);
  ::odrxSetMemberConstructor(OdDgReferenceAttachmentHeader::desc(), constructOdDgReferenceAttachmentHeaderProperties);
  ::odrxSetMemberConstructor(OdDgComplexCurve::desc(), constructOdDgComplexCurveProperties);
  ::odrxSetMemberConstructor(OdDgECClassInstance::desc(), constructOdDgECClassInstanceProperties);

  OdDgCDAFacetProvider::addProvider();
}

//-----------------------------------------------------------------------------------------------------------------------

void OdDgPropertiesModule::uninitApp()
{
  OdDgCDAFacetProvider::removeProvider();

  for (unsigned i = 0; i < properties.size(); ++i)
    OdRxMember::deleteMember(properties[i]);
  properties.clear();
}

//-----------------------------------------------------------------------------------------------------------------------


