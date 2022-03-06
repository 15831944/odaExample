%ignore *::g_pDesc;
%ignore *::addRef;
%ignore *::release;
%ignore *::constructor;
%ignore *::setConstructor;
%ignore *::pseudoConstructor;
%ignore STATIC_MODULE_DESC;
%ignore OdBaseObjectPtr;

%ignore OdDbMPolygon::OdDbMPolygon;
%ignore OdDbPoint::OdDbPoint(const OdGePoint3d& position);
%ignore OdResBuf::newRb(int resType, const __wchar_t* resVal);
%ignore OdResBuf::newRb(int resType, const OdChar* resVal);
%ignore OdDbObject::subDeepClone(OdDbIdMapping& ownerIdMap, OdDbObject* pOwner, bool bPrimary) const;
%ignore OdDbObject::subWblockClone(OdDbIdMapping& ownerIdMap, OdDbObject* pOwner, bool bPrimary) const;
%ignore OdDbHostAppServices::key() const;
%ignore OdDbHostAppServices2::key() const;
%ignore ExDbHostAppServices::key() const;
%ignore OdDbXrecord::OdDbXrecord();
%ignore OdDbEntity::OdDbEntity(OdDbObjectImpl* pImpl);
%ignore OdDbSymbolTableRecord::OdDbSymbolTableRecord();
%ignore OdDbGraphNode::markTree(OdUInt8 flags, OdDbGraphNodeArray* pNodeArray = 0);
%ignore break_edge(OdDbGraphNode* , OdDbGraphNode* );
%ignore OdDbBlockBegin::OdDbBlockBegin();
%ignore OdDbBlockEnd::OdDbBlockEnd();
%ignore OdDbSortentsTable::OdDbSortentsTable();
%ignore OdDbBlockTableRecord::OdDbBlockTableRecord();
%ignore decompTransform(const OdGeMatrix3d& mTrans, OdGePoint3d& pOrigin, OdGeScale3d& sScale,double & dRotation, OdGeVector3d& vNormal );
%ignore OdDbMText::strikethroughOff;
%ignore OdDbMText::strikethroughOn;
%ignore OdDbNurbSurface::OdDbNurbSurface;
%ignore ::processBTRIndexObjects(OdDbBlockTableRecord* pBTR, int indexCtlVal, OdDbBlockChangeIterator* pBlkChgIter, OdDbIndexUpdateData* pIdxUpdData );
%ignore odPrintConsoleString;
%ignore ExHostAppServices::warning1;
%ignore OdDb::kszVSFlat;
%ignore OdDb::kszVSFlatWithEdges;
%ignore OdDb::kszVSGouraud;
%ignore OdDb::kszVSGouraudWithEdges;

// Visual Styles
%ignore OdDb::kszVS2DWireframe;
%ignore OdDb::kszVS3DWireframe;
%ignore OdDb::kszVSBasic;
%ignore OdDb::kszVSHidden;
%ignore OdDb::kszVSRealistic;
%ignore OdDb::kszVSConceptual;
%ignore OdDb::kszVSCustom;

// Highlight Visual Styles (internal use only)
%ignore OdDb::kszVSDim;
%ignore OdDb::kszVSBrighten;
%ignore OdDb::kszVSThicken;
%ignore OdDb::kszVSTransparent;
%ignore OdDb::kszVSLinePattern;
%ignore OdDb::kszVSFacePattern;
%ignore OdDb::kszVSColorChange;

%ignore odrxRegisterHyperlinkDestructorCallback(ODDBHYPERLINK_CALLBACK callbackFunc);
%ignore odrxUnregisterHyperlinkDestructorCallback();

#if defined(SWIGJAVA)
%ignore oddbGetObjectMesh;
#endif

%ignore OdDbUnderlayItem::version() const;
%ignore OdAveMaterial::setSpecularColorCurrent;
%ignore OdDbSection::OdDbSection;
%ignore OdDbSectionSettings::OdDbSectionSettings;
%ignore OdDbRasterVariables::OdDbRasterVariables(OdDbObjectImpl* pImpl);
%ignore OdDbIdBuffer::OdDbIdBuffer();
%ignore OdDbShHistoryNode::transformBy;

%ignore OdDbHistoryInternal::FaceData;

%ignore OdDbHistoryInternal::FilletInternalData;
%ignore OdDbHistoryInternal::FilletData;
%ignore OdDbHistoryInternal::EdgeData;

%ignore OdPdfImportModule::create;

#if defined(SWIGJAVA)
%ignore OdResBuf::newRb;
#endif

#if defined(SWIGJAVA)
%ignore OdDb::RowTypes;
%ignore OdDb::GridLineTypes;
#endif
#if defined(SWIGCSHARP)
%ignore OdDb::RowTypes;
%ignore OdDb::GridLineTypes;
#endif

%ignore OdDbModelDocViewStyle::isModifiedForRecompute; //not implemented
%ignore OdDbModelDocViewStyle::defaultViewName; //not implemented
%ignore OdDbModelDocViewStyle::isViewNameValid; //not implemented

%ignore OdDbXrefObjectId::resolveObjectId; //not implemented
%ignore OdDbXrefObjectId::serializeToResbuf; //not implemented
%ignore OdDbXrefObjectId::serializeFromResbuf; //not implemented
%ignore OdDbXrefObjectId::seekToResbuf; //not implemented

%ignore OdDbSpatialIndexIterator::desc; //not implemented
%ignore OdDbSpatialIndexIterator::cast; //not implemented
%ignore OdDbSpatialIndexIterator::createObject; //not implemented
%ignore OdDbSpatialIndexIterator::newIterator; //not implemented

%ignore OdDbGeEdgesDwgIO::OdGeDwgIOVersion; //not exported
%ignore OdDbGeEdgesDxfIO::OdGeDxfIOVersion; //not exported

%ignore OdDbAbstractPlotDataForDbViewport::desc; //not implemented
%ignore OdDbAbstractPlotDataForDbViewport::cast; //not implemented
%ignore OdDbAbstractPlotDataForDbViewport::createObject; //not implemented

%ignore OdDbAbstractViewportDataForDbViewport::setUcsToWorld; //not implemented
%ignore OdDbAbstractViewportDataForDbViewport::desc; //not implemented
%ignore OdDbAbstractViewportDataForDbViewport::cast; //not implemented
%ignore OdDbAbstractViewportDataForDbViewport::createObject; //not implemented

%ignore OdDbBlockInsertionPoints::desc; //not implemented
%ignore OdDbBlockInsertionPoints::cast; //not implemented
%ignore OdDbBlockInsertionPoints::createObject; //not implemented

%ignore OdDbAppEntityGrips::desc; //not implemented
%ignore OdDbAppEntityGrips::cast; //not implemented
%ignore OdDbAppEntityGrips::createObject; //not implemented

%ignore OdDbBreakData::updateAssociativity; //not implemented

%ignore OdDbGeEdgesDwgIO::inFields; //not exported
%ignore OdDbGeEdgesDwgIO::outFields; //not exported

%ignore OdDbHatchPE::desc; //not implemented
%ignore OdDbHatchPE::cast; //not implemented
%ignore OdDbHatchPE::createObject; //not implemented

%ignore OdDbPointCloudEx::getDisplayedVisiblePointCount; //not implemented
%ignore OdDbPointCloudEx::getLoadedVisiblePointCount; //not implemented
%ignore OdDbPointCloudEx::getVisiblePointCount; //not implemented

%ignore OdDbBlockXYParameter::getAssociatedXYGrip; //not implemented

%ignore dst::OdSmPersistProxy::desc; //not implemented
%ignore dst::OdSmPersistProxy::cast; //not implemented
%ignore dst::OdSmPersistProxy::createObject; //not implemented

%ignore OdColorAdjuster; //not exported

%ignore OdDbSafeTransaction; //Not may wrapp at now
%ignore szPointCloudHostModuleName;

%ignore ::getSnapGeometry;

%ignore OdDbHistoryInternal::FilletSubentData::parseSubData;
%ignore OdModelerGeometry::generateSectionGeometry;
%ignore OdModelerGeometry::convertTo;

%ignore dst::OdSmFiler::readReference;
%ignore dst::OdSmFiler::writeReference;

%ignore OdLyLayerFilterManager::desc;
%ignore OdLyLayerFilterManager::cast;
%ignore OdLyLayerFilterManager::createObject;

%ignore OdDbOle2Frame::getOleClientItem;

#ifdef SWIGJAVA
%ignore OdDbVisualStyle::trait;
#endif

//Need exclude after 21.11 release
%ignore OdTfRevisionControl::dryMerge;

%ignore OdDbEdgeRef::createObject( const OdDbCompoundObjectIdPtr & pid, const OdGeCurve3d* pCurve );

%ignore TD_DGN_IMPORT::createSpecialSymbolString(const OdArray<OdDgTextExtendedProperties::OdDgSpecialSymbol>& arrSymbols);
%ignore TD_DGN_IMPORT::convertTextNodeJustification(OdDg::TextJustification uJust);
%ignore TD_DGN_IMPORT::addTextNodeSpecialSymbols(const OdDgElement* pText);
%ignore TD_DGN_IMPORT::convertColor(OdDgGraphicsElement* pElm);

#ifndef SWIGWIN
%ignore OdOxGetOleLinkManager;
#endif