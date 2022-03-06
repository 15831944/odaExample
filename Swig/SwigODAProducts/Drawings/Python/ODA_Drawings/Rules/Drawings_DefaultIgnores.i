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

%include "Base/IgnoreListBase_Drawings.i"

%ignore ExHostAppServices::warning1;
%ignore STATIC_MODULE_DESC;
%ignore OdBaseObjectPtr;
%ignore OdDbXrecord::OdDbXrecord();
%ignore OdDbNurbSurface::OdDbNurbSurface;
%ignore OdDbDynBlockReference::OdDbDynBlockReference;
%ignore OdDbDynBlockTableRecord::OdDbDynBlockTableRecord;
%ignore OdDbTableIterator::OdDbTableIterator;
%ignore OdModelerGeometryCreator::OdModelerGeometryCreator;
%ignore OdDbViewRep::OdDbViewRep;
%ignore OdDbFormattedTableData::OdDbFormattedTableData;
%ignore OdDbCommandContext;
%ignore OdDbUnitsFormatterImpl;
%ignore OdDbBlockTableRecord::OdDbBlockTableRecord;
%ignore OdDbUnitsFormatterImpl;
%ignore OdDbColor::OdDbColor;
%ignore OdGiContextForDbDatabase::getSectionGeometryManager;
%ignore *::rxInit;
%ignore *::rxUninit;
%ignore OdDbSafeTransaction;
// ignore those methods excluding OdRxClass
%rename("%s") OdRxClass::rxInit;
%rename("%s") OdRxClass::rxUninit;

%ignore OdDbGraphNode::markTree;
%ignore ::break_edge;
%ignore OdDbModelDocViewStyle::isModifiedForRecompute;
%ignore OdDbModelDocViewStyle::defaultViewName;
%ignore OdDbModelDocViewStyle::isViewNameValid;
%ignore ::processBTRIndexObjects;
%ignore OdDbXrefObjectId;
%ignore ::getSnapGeometry;
%ignore OdColorAdjuster;
%ignore OdDbGeEdgesDwgIO;
%ignore OdDbSpatialIndexIterator;
%ignore OdDbPdfUnderlayItemPE;
%ignore OdAveMaterial::setSpecularColorCurrent;
%ignore dst::OdSmPersistProxy;
%ignore OdDbBlockXYParameter::getAssociatedXYGrip;
%ignore OdDbPointCloudEx::getVisiblePointCount( OdGeExtents3d extents );
%ignore OdDbPointCloudEx::getLoadedVisiblePointCount( OdGeExtents3d extents );
%ignore OdDbPointCloudEx::getDisplayedVisiblePointCount( OdGeExtents3d extents );
%ignore OdLyLayerFilterManager;
%ignore OdDbHatchPE;
%ignore OdDbBreakData::updateAssociativity;
%ignore OdDbAppEntityGrips;
%ignore OdDbAbstractViewportDataForDbViewport;
%ignore OdDbAbstractPlotDataForDbViewport;
%ignore OdDbGeEdgesDxfIO::OdGeDxfIOVersion;
%ignore OdDbBlockInsertionPoints::desc;
%ignore OdDbBlockInsertionPoints::cast;
%ignore OdDbBlockInsertionPoints::createObject;
%ignore OdDbHistoryInternal::FaceData;
%ignore OdDbHistoryInternal::FilletSubentData;
%ignore OdDbHistoryInternal::FilletInternalData;
%ignore OdDbHistoryInternal::FilletData;
%ignore OdDbHistoryInternal::EdgeData;
//Need exclude after 21.11 release
%ignore OdTfRevisionControl::dryMerge;