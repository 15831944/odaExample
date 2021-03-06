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



///////////////////////////////////////////////////////////////////////////////
// This code auto-generated by ODA internal tool OdSwigProductsSynchronization
// Tool location: https://svn.opendesign.com/svn/internal/trunk/swig/tools/SwigTools/
///////////////////////////////////////////////////////////////////////////////


//SWIG include rules :
//    
%include "DbObjectId.h"
%include "DbTypedId.h"
%include "ResBuf.h"
%include "IdArrays.h"
%include "DbObjectReactor.h"
%include "OdValue.h"
%include "DbObject.h"
%include "DbObjectContext.h"
%include "DbDataLink.h"
%include "DbAnnotationScale.h"
%include "DbSystemServices.h"
%include "DbSecurity.h"
%include "CmColor.h"
%include "OdToolKit.h"
%include "DbDate.h"
%include "DbSubentId.h"
%include "DbDatabase.h"
%include "DwgDeclareMembers.h"
%include "DbEntity.h"
%include "DbRegion.h"
%include "DbVertex.h"
%include "Db3dSolid.h"
%include "Sm/SmPersist.h"
%include "DbCurve.h"
%include "DbSurface.h"
%include "Sm/SmFileReference.h"
%include "DbSymbolTableRecord.h"
%include "DbEvalGraph.h"
%include "DbColor.h"
%include "ModelerGeometryDefs.h"
%include "DbNurbSurface.h"
%include "DbSubDMesh.h"
%include "DbPlotSettings.h"
%include "Sm/SmDbObjectReference.h"
%include "Sm/SmEnum.h"
%include "Sm/SmCustomProperty.h"
%include "DbDictionary.h"
%include "DbTextStyleTableRecord.h"
%include "DbSymbolTable.h"
%include "DbDynBlockReference.h"
%include "DynamicBlocks/DbBlockElement.h"
%include "DbTableStyle.h"
%include "DbFieldValue.h"
%include "ModelerGeometry.h"
%include "DbLayout.h"
%include "Sm/SmNamedDbObjectReference.h"
%include "Sm/SmComponent.h"
%include "DbSymUtl.h"
%include "DynamicBlocks/DbBlockParameter.h"
%include "DbTableIterator.h"
%include "DbField.h"
%include "DbLinkedData.h"
%include "DbObjectIterator.h"
%include "ModelerGeometryCreator.h"
%include "DbPlotSettingsValidator.h"
%include "DbLayoutManager.h"
%include "DbAbstractViewportData.h"
%include "Sm/SmProjectPointLocation.h"
%include "Sm/SmSheet.h"
%include "Sm/SmEvents.h"
%include "DbFilter.h"
%include "DbRasterImageDef.h"
%include "DbImage.h"
%include "Db2dVertex.h"
%include "DynamicBlocks/DbBlock1PtParameter.h"
%include "DynamicBlocks/DbBlock2PtParameter.h"
%include "DbFiler.h"
%include "DgnLS/DbLSObject.h"
%include "DbFrame.h"
%include "DbLinkedTableData.h"
%include "DbPointCloudObj/DbPointCloudObjExports.h"
%include "DbText.h"
%include "DbMText.h"
%include "DbGraph.h"
%include "CmColorArray.h"
%include "DbSSet.h"
%include "Ve/AveExport.h"
%include "DbHostAppServices.h"
%include "DbAbstractViewTable.h"
%include "DbAbstractViewTableRecord.h"
%include "Sm/SmCalloutBlocks.h"
%include "Sm/SmSheetView.h"
%include "Sm/SmProjectPointLocations.h"
%include "Sm/SmSubset.h"
%include "ShHistory/DbShHistoryNode.h"
%include "DbBlockIterator.h"
%include "DbIndex.h"
%include "ModelDocObj/DbViewRep.h"
%include "DbModelDocViewStyle.h"
%include "DbWipeoutVariables.h"
%include "DbRasterImage.h"
%include "Db2dPolyline.h"
%include "DbDimension.h"
%include "RxEvent.h"
%include "DynamicBlocks/DbBlockLookUpParameter.h"
%include "DynamicBlocks/DbBlockFlipParameter.h"
%include "DgnLS/DbLSStroke.h"
%include "DgnLS/DbLSComponent.h"
%include "DbXrefObjectId.h"
%include "DbPolygonMeshVertex.h"
%include "DbOleFrame.h"
%include "DbSpline.h"
%include "DbBlockReference.h"
%include "DbDimStyleTableRecord.h"
%include "DbFormattedTableData.h"
%include "DbPointCloudObj/DbArgbColor.h"
%include "DbAttribute.h"
%include "DbMLeaderStyle.h"
%include "OdDbGeoCoordinateSystem.h"
%include "DbCompoundObjectId.h"
%include "DbDgnUnderlayHost.h"
%include "DbXrefGraph.h"
%include "DbHatch.h"
%include "DbUnitsFormatter.h"
%include "DbUserIO.h"
%include "Ve/AveDefs.h"
%include "Tf/TfSchemaManager.h"
%include "DbBlockTable.h"
%include "DbTextStyleTable.h"
%include "DbDimStyleTable.h"
%include "DbViewTable.h"
%include "DbViewTableRecord.h"
%include "DbViewportTable.h"
%include "DbViewportTableRecord.h"
%include "DbLinetypeTable.h"
%include "DbUCSTable.h"
%include "DbUCSTableRecord.h"
%include "DbRegAppTable.h"
%include "DbRegAppTableRecord.h"
%include "DbLayerTable.h"
%include "DbLayerTableRecord.h"
%include "SpaModeler/SpaModelerExport.h"
%include "Sm/SmViewCategory.h"
%include "Sm/SmSheetSelSet.h"
%include "Sm/SmObjectId.h"
%include "Sm/SmSheetSet.h"
%include "ShHistory/DbShPrimitive.h"
%include "DbMaterial.h"
%include "DbLayerFilter.h"
%include "CAseDLPNTableRecord.h"
%include "DbVbaProject.h"
%include "DbSpatialIndex.h"
%include "DbSpatialFilter.h"
%include "DbSortentsTable.h"
%include "DbRasterVariables.h"
%include "DbPlaceHolder.h"
%include "DbLayerIndex.h"
%include "DbIdBuffer.h"
%include "DbDictionaryWithDefault.h"
%include "DbDictionaryVar.h"
%include "DbMlineStyle.h"
%include "DbGroup.h"
%include "ModelerGeometry/ModelGeomExport.h"
%include "ModelDocObj/RxSketchObject.h"
%include "ModelDocObj/DbViewRepOrientationDef.h"
%include "ModelDocObj/DbViewRepSource.h"
%include "ModelDocObj/DbViewRepCutDefinition.h"
%include "DbDetailViewStyle.h"
%include "ModelDocObj/DbViewSymbol.h"
%include "DbProxyObject.h"
%include "DbWipeout.h"
%include "RText.h"
%include "DbArcAlignedText.h"
%include "DbXrecord.h"
%include "DbTrace.h"
%include "DbSolid.h"
%include "DbPolyFaceMesh.h"
%include "DbDiametricDimension.h"
%include "DbRadialDimension.h"
%include "Db2LineAngularDimension.h"
%include "Db3PointAngularDimension.h"
%include "DbRotatedDimension.h"
%include "DbOrdinateDimension.h"
%include "DbProxyEntity.h"
%include "DbPolyline.h"
%include "DbXline.h"
%include "DbFaceRecord.h"
%include "DbPolyFaceMeshVertex.h"
%include "DbFcf.h"
%include "DbShape.h"
%include "DbSequenceEnd.h"
%include "DbRay.h"
%include "DbPoint.h"
%include "DbMline.h"
%include "DbMInsertBlock.h"
%include "DbFace.h"
%include "DbBlockEnd.h"
%include "DbAlignedDimension.h"
%include "DbBlockBegin.h"
%include "DbAttributeDefinition.h"
%include "DbIdMapping.h"
%include "Editor.h"
%include "DynamicBlocks/DbBlockRepresentationData.h"
%include "DynamicBlocks/DbBlockGrips.h"
%include "DynamicBlocks/DbBlockParamValueSet.h"
%include "DgnLS/DbLSSymbolReference.h"
%include "DgnLS/DbLSStrokePatternComponent.h"
%include "DbRenderSettings.h"
%include "DbViewport.h"
%include "DbPolygonMesh.h"
%include "DbOle2Frame.h"
%include "DbGeoPositionMarker.h"
%include "DbHelix.h"
%include "DbTable.h"
%include "DbLeader.h"
%include "Db3dPolylineVertex.h"
%include "Db3dPolyline.h"
%include "DbTableContent.h"
%include "DbLight.h"
%include "DbSection.h"
%include "DbTransactionReactor.h"
%include "DbRevolveOptions.h"
%include "DbPointCloudObj/DbPointCloudCropping.h"
%include "DbPointCloudObj/DbPointCloudIntensityStyle.h"
%include "DbPointCloudObj/DbPointCloudClipping.h"
%include "ShHistory/DbManagerSubentData.h"
%include "DbObjectContextData.h"
%include "DbObjectContextCollection.h"
%include "DbObjectContextInterface.h"
%include "DbMLeader.h"
%include "DbLoftOptions.h"
%include "DbGeoData.h"
%include "DbSweepOptions.h"
%include "DbLinetypeTableRecord.h"
%include "DbDimAssoc.h"
%include "DbAbstractViewportDataForAbstractViewTabRec.h"
%include "DbAbstractPlotData.h"
%include "DbGeomRef.h"
#if !defined(SWIG_MSC_VER) || SWIG_MSC_VER >= 1900
%include "PdfImport/Include/PdfImport.h"
#endif //!defined(SWIG_MSC_VER) || SWIG_MSC_VER >= 1900
%include "PlotSettingsValidator/PlotSettingsDefs.h"
%include "DbPlotSettingsValidatorPE.h"
%include "DbUnderlayHost.h"
%include "DbUnderlayReference.h"
%include "DbLine.h"
%include "DbEllipse.h"
%include "DbCircle.h"
%include "DbArc.h"
%include "IdViewObjectEnablers/IdViewExport.h"
%include "DbBlockTableRecord.h"
%include "DbDatabaseReactor.h"
%include "HatchPatternManager.h"
%include "DbUnitsFormatterImpl.h"
%include "DbCommandContext.h"
%include "DbJoinEntityPE/Include/DbJoinEntityPEDef.h"
%include "DbBody.h"
%include "AutoSurfServices/AsSubSurfaces.h"
%include "AeciIbEnablers/AeciIbExport.h"
%include "DgnImportTextNodeBase.h"
%include "DgnImport.h"
%include "XRefMan.h"
%include "VLObject.h"
%include "Ve/AveScene.h"
%include "Ve/AveRender.h"
%include "Ve/AveMaterial.h"
%include "Ve/AveMapping.h"
%include "Ve/AveLight.h"
%include "Tf/TfRevisionControl.h"
%include "Tf/DbObjectSchemaIterator.h"
%include "Tables.h"
%include "SysVarInfo.h"
%include "summinfo.h"
%include "SpaModeler/SpaParameters.h"
%include "SpaModeler/SpaModeler.h"
%include "Sm/SmViewCategories.h"
%include "Sm/SmSheetViews.h"
%include "Sm/SmSheetSetMgr.h"
%include "Sm/SmSheetSelSets.h"
%include "Sm/SmResources.h"
%include "Sm/SmPublishOptions.h"
%include "Sm/SmPersistProxy.h"
%include "Sm/SmFiler.h"
%include "Sm/SmDatabase.h"
%include "ShHistory/DbShWedge.h"
%include "ShHistory/DbShTorus.h"
%include "ShHistory/DbShSweep.h"
%include "ShHistory/DbShSubentMaterial.h"
%include "ShHistory/DbShSubentColor.h"
%include "ShHistory/DbShSphere.h"
%include "ShHistory/DbShRevolve.h"
%include "ShHistory/DbShPyramid.h"
%include "ShHistory/DbShLoft.h"
%include "ShHistory/DbShHistory.h"
%include "ShHistory/DbShFillet.h"
%include "ShHistory/DbShExtrusion.h"
%include "ShHistory/DbShCylinder.h"
%include "ShHistory/DbShChamfer.h"
%include "ShHistory/DbShBrep.h"
%include "ShHistory/DbShBox.h"
%include "ShHistory/DbShBoolean.h"
%include "ShHistory/DbAssocPersSubentManager.h"
%include "RemoteGeomProxy.h"
%include "odole.h"
%include "OdFileDepMgr.h"
%include "OdDbGeoDataMarker.h"
%include "OdDbGeoDataDrawingPE.h"
%include "OdDbGeoCoordinateSystemPE.h"
%include "Objects.h"
%include "NextCodeDefs.h"
%include "ModelerTools.h"
%include "ModelerHistory.h"
%include "ModelerGeometry/ModelerModule.h"
%include "ModelDocObj/RxSketchManager.h"
%include "ModelDocObj/DbViewRepStandard.h"
%include "ModelDocObj/DbViewRepSourceMgr.h"
%include "ModelDocObj/DbViewRepSectionDefinition.h"
%include "ModelDocObj/DbViewRepProjectionDef.h"
%include "ModelDocObj/DbViewRepOrientation.h"
%include "ModelDocObj/DbViewRepModelSpaceViewSelSet.h"
%include "ModelDocObj/DbViewRepModelSpaceSource.h"
%include "ModelDocObj/DbViewRepModelPlaneDef.h"
%include "ModelDocObj/DbViewRepInventorSource.h"
%include "ModelDocObj/DbViewRepImage.h"
%include "ModelDocObj/DbViewRepDetailDefinition.h"
%include "ModelDocObj/DbViewRepBlockReference.h"
%include "ModelDocObj/DbViewBorder.h"
%include "ModelDocObj/DbSynergy.h"
%include "ModelDocObj/DbSectionSymbol.h"
%include "ModelDocObj/DbDetailSymbol.h"
%include "ModelDocObj/DbAssocProjectedEntityPersSubentIdHolder.h"
%include "LyLayerFilter.h"
%include "IdArraysIO.h"
%include "GiContextForDbDatabase.h"
%include "GeometryFromProxy.h"
%include "GeDxfIO.h"
%include "GeDwgIO.h"
%include "FdField.h"
%include "Entities.h"
%include "EmbeddedASMEntPE.h"
%include "EditorImpl.h"
%include "DynamicBlocks/DbDynamicBlockPurgePreventer.h"
%include "DynamicBlocks/DbDynamicBlockProxyNode.h"
%include "DynamicBlocks/DbConstraintsInterfacePE.h"
%include "DynamicBlocks/DbBlockXYParameter.h"
%include "DynamicBlocks/DbBlockVisibilityParameter.h"
%include "DynamicBlocks/DbBlockRotationParameter.h"
%include "DynamicBlocks/DbBlockRepresentation.h"
%include "DynamicBlocks/DbBlockPropertiesTable.h"
%include "DynamicBlocks/DbBlockPolarParameter.h"
%include "DynamicBlocks/DbBlockPointParameter.h"
%include "DynamicBlocks/DbBlockLinearParameter.h"
%include "DynamicBlocks/DbBlockConstraintParameters.h"
%include "DynamicBlocks/DbBlockActions.h"
%include "DgnLS/DbLSXData.h"
%include "DgnLS/DbLSSymbolComponent.h"
%include "DgnLS/DbLSPointComponent.h"
%include "DgnLS/DbLSMisc.h"
%include "DgnLS/DbLSInternalComponent.h"
%include "DgnLS/DbLSDefinition.h"
%include "DgnLS/DbLSCompoundComponent.h"
%include "DbVisualStyle.h"
%include "DbValueTypes.h"
%include "DbUndoDisablerAuto.h"
%include "DbUnderlayDefinition.h"
%include "DbTextIterator.h"
%include "DbTableTemplate.h"
%include "DbSweptSurface.h"
%include "DbSun.h"
%include "DbSetPlotSettingsPE.h"
%include "DbSectionViewStyle.h"
%include "DbSectionManager.h"
%include "DbScale.h"
%include "DbSafeTransaction.h"
%include "DbRevolvedSurface.h"
%include "DbRadialDimensionLarge.h"
%include "DbProxyExt.h"
%include "DbPointCloudObj/DbPointCloudObjModule.h"
%include "DbPointCloudObj/DbPointCloudHostPE.h"
%include "DbPointCloudObj/DbPointCloudEx.h"
%include "DbPointCloudObj/DbPointCloudDefEx.h"
%include "DbPointCloudObj/DbPointCloudDef.h"
%include "DbPointCloudObj/DbPointCloudColorMap.h"
%include "DbPointCloudObj/DbPointCloud.h"
%include "DbPlaneSurface.h"
%include "DbPersSubentManager.h"
%include "DbPageController.h"
%include "DbObjPtrArray.h"
%include "DbObjectOverrule.h"
%include "DbObjectIdGraph.h"
%include "DbObjectContextPE.h"
%include "DbObjectContextManager.h"
%include "DbNamedPath.h"
%include "DbMPolygon.h"
%include "DbMotionPath.h"
%include "DbMLeaderBreaks.h"
%include "DbMatchProperties.h"
%include "DbLongTransaction.h"
%include "DbLoftedSurface.h"
%include "DbLayoutPaperPE.h"
%include "DbLayerState.h"
%include "DbJoinEntityPE.h"
%include "DbHistoryManager.h"
%include "DbHatchPE.h"
%include "DbGsManager.h"
%include "DbGripPoints.h"
%include "DbGeoDataPE.h"
%include "DbGeEdgesDxfIO.h"
%include "DbGeEdgesDwgIO.h"
%include "DbExtrudedSurface.h"
%include "DbEvalWatchers.h"
%include "DbErrorInvalidSysvar.h"
%include "DbEntityWithGrData.h"
%include "DbEntityOverrule.h"
%include "DbEntityIntersectionPE.h"
%include "DbDimData.h"
%include "DbDiesel.h"
%include "DbDgnLSPE.h"
%include "DbDataTable.h"
%include "DbDatabaseCollection.h"
%include "DbCurvePE.h"
%include "DbClass.h"
%include "DbCamera.h"
%include "DbBreakData.h"
%include "DbBlendOptions.h"
%include "DbBackground.h"
%include "DbAudit.h"
%include "DbArcDimension.h"
%include "DbAppEntityGrips.h"
%include "DbAnnotativeObjectPE.h"
%include "DbAcisIO.h"
%include "DbAbstractViewportDataForDbVpTabRec.h"
%include "DbAbstractViewportDataForDbViewTabRec.h"
%include "DbAbstractViewportDataForDbViewport.h"
%include "DbAbstractPlotDataForDbViewport.h"
%include "DbAbstractPlotDataForDbPlotSettings.h"
%include "Db3dProfile.h"
%include "CloneFilers.h"
%include "ArraysIO.h"
%include "ApLongTransactions.h"
#if !defined(SWIG_MSC_VER) || SWIG_MSC_VER >= 1900
%include "PdfImport/Include/PdfImportEx.h"
#endif //!defined(SWIG_MSC_VER) || SWIG_MSC_VER >= 1900
%include "DwfImport/Include/DwfImport.h"
%include "ColladaImport/Include/ColladaImportDef.h"
%include "ColladaImport/Include/ColladaImport.h"
%include "PlotSettingsValidator/PlotSettingsValidatorCustomMediaPE.h"
%include "PdfUnderlayCommon/PdfUnderlay.h"
%include "PdfUnderlayCommon/OdColorAdjuster.h"
%include "IdViewObjectEnablers/IdViewSpline.h"
%include "IdViewObjectEnablers/IdViewLine.h"
%include "IdViewObjectEnablers/IdViewEllipse.h"
%include "IdViewObjectEnablers/IdViewCircle.h"
%include "IdViewObjectEnablers/IdViewArc.h"
%include "IdViewObjectEnablers/IdObjects.h"
%include "IdViewObjectEnablers/IdComplexEntity.h"
%include "IdViewObjectEnablers/IdBlockReference.h"
%include "ExServices/ExHostAppServices.h"
%include "ExServices/ExDbCommandContext.h"
%include "DbJoinEntityPE/Include/DbJoinEntityPEModule.h"
%include "AutoSurfServices/AsSurfBodyModule.h"
%include "AutoSurfServices/AsSurfBody.h"
%include "AeciIbEnablers/DbEmbeddedRasterImageDef.h"
%include "AeciIbEnablers/DbEmbeddedRasterImage.h"
%include "AeciIbEnablers/DbEmbeddedImageData.h"


