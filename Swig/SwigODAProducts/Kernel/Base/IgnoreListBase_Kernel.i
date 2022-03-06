%include "IgnoreAsNotImplemented.i"

#ifdef SWIGJAVA
%ignore OdGsBaseVectorizer::doCollide;
%ignore OdGsBaseVectorizeView::collide;
%ignore OdGiVisualStyle::trait;
%ignore OdGsBaseVectorizer::displayNode;
%ignore OdGsBaseVectorizer::displaySubnode;
%ignore OdGsBaseVectorizeViewDef::displayNode;
%ignore OdGsBaseVectorizeViewDef::displaySubnode;
%ignore OdGsBaseVectorizeViewMT::displayNode;
%ignore OdGsBaseVectorizeViewMT::displaySubnode;
#endif

%ignore *::rxInit;
%ignore *::rxUninit;
%ignore OdGiLayerTraitsTaker::OdGiLayerTraitsTaker;
// ignore those methods excluding OdRxClass
%rename("%s") OdRxClass::rxInit;
%rename("%s") OdRxClass::rxUninit;

%ignore OdCmEntityColor::trueColor;
%ignore OdCmEntityColor::trueColorMethod;
%ignore OdCmEntityColor::setTrueColorMethod;
%ignore OdCmEntityColor::color(const RGBM* pRGBM);
%ignore OdCmEntityColor::mLUT;

%ignore OdCmTransparency::dwgIn;
%ignore OdCmTransparency::dwgOut;

#ifdef SWIGCSHARP
%ignore OdFlatMemStream::createObject();
#endif

%ignore OdRxSystemServices::formatMessage;
%ignore OdRxSystemServices::formatMsg(unsigned int formatId, ...);
%feature("nodirector") OdRxSystemServices::formatMsg;
%ignore OdRxSystemServices::createOdGUID;

%ignore RxSystemServicesImpl::systemCodePage;
%ignore RxSystemServicesImpl::formatMessage;
%ignore RxSystemServicesImpl::formatMsg;
%feature("nodirector") RxSystemServicesImpl::formatMsg;

%ignore ::operator *(double scale, const OdGePoint2d& point);
%ignore OdGeMatrix2d::entry;
%ignore OdGeContext::gOrthoVector;
%ignore OdGeContext::gAllocMem;
%ignore OdGeContext::gFreeMem;
%ignore OdGeContext::gErrorFunc;
%ignore OdGe::gLibVersion;
%ignore OdGeCurve2d::isDegenerate;
%ignore OdGeCurve3d::isDegenerate;

%ignore OdGePoint2d::operator [](unsigned int i);

#if defined(SWIGJAVA)
%ignore OdGeMatrix2d::entry;
%ignore OdRxSystemServices::systemCodePage;
#endif

%ignore OdGeMatrix2d::operator [](int row) const;
%ignore OdGeMatrix2d::operator [](int row);
%ignore OdGeMatrix2d::operator ()(int row, int column);
%ignore OdGeMatrix3d::operator [](int row) const;
%ignore OdGeMatrix3d::operator [](int row);
%ignore OdGeMatrix3d::operator ()(int row, int column);

%ignore OdGeMatrix3d::entry;

#if defined(SWIGJAVA)
%ignore OdGeInterval::operator >;
%ignore OdGeInterval::operator <;
%ignore operator >(double,const OdGeInterval&);
%ignore operator <(double,const OdGeInterval&);
#endif

%ignore OdGeScale3d::preMultBy;
%ignore OdGeScale3d::postMultBy;
%ignore ::operator*(double, OdGeScale3d const &);

%ignore OdGeKnotVector::operator [](int i);
%ignore OdGeKnotVector::isEqualTo(const OdGeKnotVector& knotVector) const;
%ignore OdGeKnotVector::getPtr() const;
%ignore OdGeKnotVector::asArrayPtr();
%ignore OdGeKnotVector::asArrayPtr() const;

%ignore derivArraySize;
%ignore VectorDerivArrayWr::Data;

%ignore OdGeNurbSurface::getDerivativesAt;
#if defined(SWIGCSHARP)
%ignore OdGeExternalBoundedSurface::getBaseSurface;
#endif
%ignore OdGeExternalBoundedSurface::getContours;
%ignore OdGeCurveBoundary::getContour;
%ignore OdBrException;
%ignore OdBrFace::getSurfaceAsTrimmedNurbs;
#if defined(SWIGJAVA)
%ignore OdGiIndirectEntityAccessor::getLiveSection;
#endif
#if defined(SWIGJAVA)
%ignore kInvalidateRefExtentsMask;
%ignore OdGsBlockNode::createDef;
%ignore OdGsBlockNode::findCreateDef;
%ignore OdGsBlockNode::removeDef;
#endif

%ignore OdGiMaterialTraits_Stub;

%ignore OdGiMaterialTraitsTaker;
%ignore OdGiBaseVectorizer::setPlotStyleNameType;
%ignore OdGiBaseVectorizer::setPlotStyleNameId;

%ignore OdGiBaseVectorizer::updateViewProps;
%ignore OdGiBaseVectorizer::propagateInvalidVpFlag;
%ignore OdGiBaseVectorizer::propagateLayersChanges;

%ignore OdGiVariant::set(const OdChar *value);
%ignore OdGiVariant::createObject(const OdChar *value);
#ifdef SWIGJAVA
%ignore OdGiMetafile::bitsData(OdUInt8* pBytes);
#endif

#ifdef SWIGCSHARP
%ignore OdGiClipBoundarySaver;
#endif
%ignore OdGiEdgeData;
%ignore OdGsModel::setOpenDrawableFn;
%ignore OdGsSelectionReactor::kNotImplemented;
%ignore OdGsCollisionDetectionReactor::kNotImplemented;

%ignore OdGiLinetypeTraits::kByBlock;
%ignore OdGiLinetypeTraits::kByLayer;
%ignore OdGiLinetypeTraits::kContinuous;
%ignore OdGiLinetypeTraits::kScaleToFit;
%ignore OdGiLinetypeTraits::kScalability;
%ignore OdGiLinetypeTraits::kDgLinetype;
%ignore OdGiLinetypeTraits::kGiLinetypeFlagMax;

%ignore OdGiLayerTraits::kByBlock;
%ignore OdGiLayerTraits::kFrozen;
%ignore OdGiLayerTraits::kOff;
%ignore OdGiLayerTraits::kPlottable;
%ignore OdGiLayerTraits::kLocked;

%ignore OdGiLightTraitsData::kPointLight;
%ignore OdGiLightTraitsData::kSpotLight;
%ignore OdGiLightTraitsData::kDistantLight;
%ignore OdGiLightTraitsData::kWebLight;

%ignore OdGiMaterialTraits::kByBlock;
%ignore OdGiMaterialTraits::kByLayer;

%ignore OdGiLightTraitsVpDep::kVpDep;

%ignore OdGiVariant::EnumType;
%ignore OdGiVariant::asEnum;
#ifdef SWIGJAVA
%ignore OdGiMaterialTraitsData::normalMap;
#endif
#ifdef SWIGCSHARP
%ignore OdGiConveyorContextWrapper::OdGiConveyorContextWrapper;
#endif

%ignore OdGsViewImpl::usesDept;
%ignore OdGsViewImpl::getFrozenLayersDiff;

#ifdef SWIGCSHARP
%ignore OdGsBaseVectorizeDevice::getPalette;
#endif
%ignore OdGsViewImpl::clientViewInfo;

%ignore OdGsBaseVectorizeView::getRootNode;
%ignore OdGsBaseVectorizeView::clone;
%ignore OdGsBaseVectorizeView::copyFrom;

%ignore OdGsBaseMaterialVectorizer::OdGsBaseMaterialVectorizer(OdUInt32 uMaterialViewFlags = kProcessMappersAndMaterials);
%ignore OdGsBaseMaterialViewPC::OdGsBaseMaterialViewPC();

%ignore OdGsBaseMaterialView::updateViewProps;
%ignore OdGsBaseMaterialView::propagateInvalidVpFlag;
%ignore OdGsBaseMaterialView::propagateLayersChanges;

%ignore OdGsBaseMaterialView::OdGsBaseMaterialView(OdUInt32 uMaterialViewFlags = kProcessMappersAndMaterials);
%ignore OdGsBaseMaterialViewMT::OdGsBaseMaterialViewMT(OdUInt32 uMaterialViewFlags = kProcessMappersAndMaterials);

%ignore OdGiBaseVectorizerImpl::affectTraits;
%ignore OdGsBaseVectorizer::updateExtentsInThreadInit;
%ignore OdGsBaseVectorizer::selectionMarkerOnChange;
%ignore OdGsBaseVectorizer::display;
%ignore OdGsBaseVectorizer::updateExtents;
%ignore OdGsBaseVectorizer::effectiveLayerTraits;
%ignore OdGsBaseVectorizer::switchLayer;
%ignore OdGsBaseVectorizer::renderTypeOnChange;
%ignore VectorizerAutoPtr;//::updateExtentsInThreadInit;
%ignore OdGsBaseVectorizeView::updateGeometryByDevice;

%ignore OdGsBaseModel::ViewProps;

%ignore OdGsBaseModel::m_pViewIDs;
%ignore OdGsBaseModel::impl;

%ignore OdGsBaseModel::setOpenDrawableFn;
%ignore OdGsBaseModel::openDrawableFn;

%ignore OdGsBaseModel::m_views;
%ignore OdGsBaseModel::m_modules;

%ignore OdGsNode::update;
%ignore OdGsNode::display;
%ignore OdSi::properExtents;
%ignore OdGsEntityNode::convertToViewportDependent;
%ignore OdGsEntityNode::setMetafile;
%ignore OdGsEntityNode::convertToViewportDependent;
%ignore OdGsEntityNode::Metafile;
%ignore OdGsEntityNode::setMetafile;
%ignore OdGsEntityNode::update;
%ignore OdGsEntityNode::findMetafileInStock;
%ignore OdGsEntityNode::MetafileHolder::get;
%ignore OdGsEntityNode::MetafileHolder::set;
%ignore OdGsEntityNode::MetafileHolder::setAtRegenType;
%ignore OdGsEntityNode::MetafileHolder::getAtRegenType;
%ignore OdGsEntityNode::MetafileHolder::setAt;
%ignore OdGsEntityNode::getEmptyMetafile;
%ignore OdGsEntityNode::metafileAt;
%ignore OdGsEntityNode::setMetafileAt;
%ignore OdGsEntityNode::metafile;
%ignore OdGsEmptyMetafileCache::get;


%ignore OdGsBlockReferenceNode::kValid;
%ignore OdGsBlockReferenceNode::kLastFlag;
%ignore OdGsBlockReferenceNode::kXrefUnloaded;
//%typemap(cscode) OdGsBlockReferenceNode %{public const uint kXrefUnloaded = (uint)OdGsEntityNode.kLastFlag << 1;%}
%ignore OdGsAwareFlagsArray::kChildrenNotUpToDate;
%ignore OdSiSelectVisitorTf;
%ignore OdGsBlockReferenceNode::highlightSubnodes;
%ignore OdGsBlockReferenceNode::updateImpl;
%ignore OdGsBlockReferenceNodeImpl::updateSubitems;
%ignore OdGsBlockReferenceNodeImpl::display;

%ignore OdGsMInsertBlockNode::doUpdateImpl;

%ignore OdGsBlockReferenceNode::postUpdateStep;
%ignore OdGsBlockReferenceNode::addEntPropsFromState;
%ignore OdGsBlockReferenceNode::checkCancelledSharedRef;
%ignore OdGsBlockReferenceNode::actionPostUpdateStep;
%ignore OdGsBlockReferenceNode::actionAddEntPropsFromState;
%ignore OdGsBlockReferenceNode::actionCheckCancelledSharedRef;
%ignore OdGsBlockReferenceNode::actionStretchExtents;
%ignore OdSiRecursiveVisitorTf;
%ignore OdGsSpQueryContextTf;

%ignore OdGsBlockReferenceNode::kValid;
%ignore OdGsBlockReferenceNode::kBrExcludeFromViewExt;
%ignore OdGsBlockReferenceNode::kBrClipped;
%ignore OdGsBlockReferenceNode::kForceNotEmpty;
%ignore OdGsBlockReferenceNode::kLastFlag;

%ignore kInvalidateRefExtentsMask;
%ignore OdGsBlockNode::createDef;
%ignore OdGsBlockNode::findCreateDef;
%ignore OdGsBlockNode::removeDef;

%ignore OdGsContainerNode::spatialQuery;
%ignore OdGsContainerNode::spatialSequentalQuery;
%ignore OdGsContainerNode::displayEntityList;
%ignore OdGsContainerNode::updateEntityList;
%ignore OdGsContainerNode::updateEntities;
%ignore OdGsContainerNode::safeEntityUpdate;
%ignore OdGsContainerNode::addEntProps;
%ignore OdGsContainerNode::doMTUpdate;
%ignore OdGsContainerNode::doSTUpdate;
%ignore OdGsLayerNode::onModified;

%ignore OdGsProperties::setOpenDrawableFn;

#ifdef SWIGCSHARP
%ignore OdSi::Volume::clone;
#endif


%ignore OdGiProceduralGeneratorPE::operator +;
%ignore OdGiGradientGenerator::operator +;
%ignore OdGiProceduralGenerator::operator +;
%ignore OdGiRasterImageLoaderPE::operator +;
%ignore OdGiRasterImageLoader::operator +;
%ignore OdGiShellFaceIterator::operator +;
%ignore operator +(const OdGiGradientGenerator &g1, const OdGiGradientGenerator &g2);

#if defined(SWIGCSHARP)
%ignore OdGiSelectProc::input;
%ignore OdGiSelectProc::output;
%ignore OdGiSelectProc::kCheckMarkerFinish;
#endif
%ignore OdGiToneOperatorParametersStatic;
%ignore OdGiPhotographicExposureParametersStatic;

%ignore OdGsBaseVectorizeViewDef::affectTraits;
%ignore OdGsBaseVectorizeViewDef::display;
%ignore OdGsBaseVectorizeViewDef::updateExtents;
%ignore OdGsBaseVectorizeViewDef::effectiveLayerTraits;
%ignore OdGsBaseVectorizeViewDef::switchLayer;
%ignore OdGsBaseVectorizeViewDef::renderTypeOnChange;
%ignore OdGsBaseVectorizeViewDef::updateGeometryByDevice;

%ignore OdGsBaseVectorizeViewMT::affectTraits;
%ignore OdGsBaseVectorizeViewMT::display;
%ignore OdGsBaseVectorizeViewMT::updateExtents;
%ignore OdGsBaseVectorizeViewMT::effectiveLayerTraits;
%ignore OdGsBaseVectorizeViewMT::switchLayer;
%ignore OdGsBaseVectorizeViewMT::renderTypeOnChange;
%ignore OdGsBaseVectorizeViewMT::updateGeometryByDevice;

%ignore OdTtfDescriptor::getTtfFlags;
%ignore OdDbHandle(const char* value);
%ignore OdDbHandle(const OdString& value);
%ignore OdDbHandle(const OdAnsiString& value);
%ignore OdDbHandle(const OdAnsiString& value);
%ignore operator=(const char* value);
%ignore OdDbHandle::getIntoAsciiBuffer(OdChar* pBuf) const;

%ignore OdBaseTextIterator::currPos;

%ignore OdDbBaseHostAppServices::formatMessage;


#if defined(SWIGCSHARP)
%ignore TD_DWF_EXPORT::DwExportParams::setPalette;
%ignore TD_DWF_EXPORT::DwExportParams::palette;
%ignore TD_DWF_EXPORT::Dwf3dExportParams::setPalette;
%ignore TD_DWF_EXPORT::Dwf3dExportParams::palette;
%ignore TD_DWF_EXPORT::DwfExportModule::create;

%ignore TD_DGN_IMPORT::OdDgnImportModule::create;
%ignore TD_DWF_IMPORT::OdDwfImportModule::create;
#endif
#if defined(SWIGJAVA)
%ignore TD_DWF_EXPORT::DwfExportModule::create;
%ignore TD_DGN_IMPORT::OdDgnImportModule::create;
%ignore TD_DWF_IMPORT::OdDwfImportModule::create;
#endif

%ignore oddbGetUnitsConversion;
%ignore oddbGetUnitsName;

%ignore ExFileUndoController::UndoRecord;

#if defined(SWIGJAVA)
%ignore OdRxVariantValue::OdRxVariantValue;
#endif

#if defined(SWIGCSHARP)
//%ignore OdRxVariantValue::OdRxVariantValue(OdIntPtr value);
#endif

%ignore OdGsContainerNode::VpData;
%ignore OdGsContainerNode::loadVpData;
%ignore OdGsContainerNode::saveVpData;

%ignore OdGsLightNode::isOwnedBy;
%ignore OdGsLightNode::setLightOwner;
%ignore OdGsEntityNode::regenMetafile;
%ignore OdGsContainerNode::addLight;

%ignore OdGiSubEntityTraitsToData;
%ignore FaceSided; 

%ignore *::updateLineweightOverride;
%ignore *::updatePaletteOverride;
%ignore OdBrFace::getFaceSides;

#if defined(SWIGJAVA)
%ignore OdGsDevice::setLogicalPalette;
#endif
%ignore OdBrFace::getFaceSides;

// compiler complains about unresolved external when methods below aren't ignored
%ignore OdGsBaseModel::setAdditionMode;
%ignore OdGsBaseModel::additionMode;

%ignore OdGsDeviceSelfReference;
%ignore OdGiGeometry::worldLine;

%ignore OdGiGeometry::worldLine;

%ignore TD_PDF_2D_EXPORT::PDFExportParams::currentVersion;
%ignore TD_PDF_2D_EXPORT::SavedGsModelData;
%ignore TD_PDF_2D_EXPORT::AutoSavedGsModelData;
%ignore TD_PDF_2D_EXPORT::AutoRestoreGsModelData;

%ignore RX_RCS_FILE_SERVICES;
%ignore odgsCreateGsCacheRedirectionManager;
%ignore odgsDestroyGsCacheRedirectionManager;
%ignore OdGsModelRedirectionHandler;
%ignore OdGsCacheRedirectionManager;

%ignore BrepBuilderInitialSurface::setupVisualInfo; //Because BrepBuilderInitialSurface don't export to other libs. (struct not have marcos BREPBUILDERFILLER_DLL)
%ignore BrepBuilderInitialEdge::setupVisualInfo; //Because BrepBuilderInitialSurface don't export to other libs. (struct not have marcos BREPBUILDERFILLER_DLL)

#if defined(SWIGJAVA)
%ignore TD_PDF_2D_EXPORT::PDFExportParams::outputStream;
%ignore TD_PDF_2D_EXPORT::OdPdfExport::exportPdf;
#endif

%ignore TD_PDF_2D_EXPORT::PdfExportModule::create;

%ignore *::g_pDesc;
%ignore *::addRef;
%ignore *::release;
%ignore *::numRefs;

%ignore OdArrayBuffer;
%ignore OdRxObjectPtr;
%ignore *::constructor;
%ignore *::setConstructor;
%ignore OdRxObject::x;


%feature("nodirector") OdRxObject::x;
%feature("nodirector") OdRxObject::numRefs;
%feature("nodirector") OdRxObject::comparedTo;
%feature("nodirector") OdRxObject::isEqualTo;
%feature("nodirector") OdRxObject::clone;
%feature("nodirector") OdRxObject::copyFrom;
%ignore *::pseudoConstructor;
%ignore STATIC_MODULE_DESC;
%ignore odrxInitStaticModuleMap;
%ignore ::newOdRxClass;
%ignore ::deleteOdRxClass;

%ignore OdGiLayerTraitsTaker::OdGiLayerTraitsTaker;
%ignore OdGiLayerTraitsTaker::OdGiLayerTraitsTaker();
%ignore OdGiLayerTraitsTaker::OdGiLayerTraitsTaker(const OdGiBaseVectorizer pRefView, OdGiContext pContext = NULL);

%ignore OdDbFullSubentPath::less;


%ignore OdTextIterator::convertToCodePage;
%ignore FileToRemoveOnClose;

%ignore OdGeLibVersion;
%ignore TD_PDF::PDFBaseObject::PDFBaseObject;
%ignore TD_PDF::PDFBaseObject::operator=(const PDFBaseObject&);
%ignore TD_PDF::PDFFieldDictionary::createObject;
%ignore OdGeTess::Contour::vectorIntersects;
%ignore OdGeContext::gErrorFunc;
%ignore OdGeScale2d::OdGeScale2d();
%ignore OdGeScale2d::preMultBy;
%ignore OdGeScale2d::postMultBy;
%ignore OdGeScale2d::postMultBy;
%ignore OdGeScale2d::set;
%ignore OdGeScale2d::Mul;
%ignore OdGeScale2d::operator*;
%ignore OdGeScale2d::operator *(double factor);
%ignore OdGeScale2d::operator *(const OdGeScale2d& scaleVec);
%ignore OdGeScale2d::operator *(double factor, const OdGeScale2d& scaleVec);
%ignore OdGeScale2d::operator *(double s, const OdGeScale2d& scl);
%ignore ::operator *(double s, const OdGeScale2d& scl);
%ignore OdQuickHeap;
%ignore OdRxRefersToAttribute::parseReference;
%ignore initPdfSupport;
%ignore uninitPdfSupport;
%ignore OdGeScale2d::kIdentity;
%ignore OdRxResourceLoader::loadString;
%ignore OdRxResourceLoader::desc;
%ignore OdRxResourceLoader::cast;
%ignore OdRxResourceLoader::createObject;
%ignore GiMesh::TrMeshSew::TrMeshSew;
%ignore GiMesh::TrMeshSew::joinVertexes;
%ignore GiMesh::TrMeshSew::sewVertexes;
%ignore GiMesh::TrMeshSew::sewEdges;
%ignore OdGsBitMap::desc;
%ignore OdGsBitMap::cast;
%ignore OdGsBitMap::createObject;
%ignore OdGsPalette::desc;
%ignore OdGsPalette::cast;
%ignore OdGsPalette::createObject;
%ignore GeMesh::VertexPair::replace;
%ignore GeMesh::VertexPair::nb;
%ignore OdRxMemberOverrule::addOverrule;
%ignore OdRxMemberOverrule::removeOverrule;
%ignore TD_PDF::PDFUnicodeTextStream::addString(const OdChar* chars);
%ignore TD_PDF::PDFUnicodeTextStream::addString(const OdChar* chars, const OdUInt32 size);
%ignore TD_PDF::PDFType1Font::getTextBaseWidth(const StandardType1FontsEnum font_type, const OdAnsiString& text);
%ignore TD_PDF::PDFTextString::createObject(PDFDocument &pDoc, OdAnsiString pStr, bool isIndirect = false);
%ignore TD_PDF::PDFTextString::set(OdAnsiString stringSrc);
%ignore OD::Path;
%ignore OdVariant::OdVariant(const OdAnsiString& val);
%ignore OdVariant::getAnsiStringPtr();
%ignore OdShxFont::getEnd;
%ignore OdShxFont::find;
%ignore OdGsFiler::wrUInt16Array(OdUInt32 count, const OdUInt16* arr);
%ignore OdGsFiler::wrUInt32Array(const OdUInt32Vector& arr);
%ignore OdGsFiler::wrUInt64Array(const OdUInt64Vector& vec);
%ignore OdGsFiler::wrUInt64Array(OdUInt32 count, const OdUInt64* arr);
%ignore OdGsFiler::wrFloatArray(OdUInt32 count, const float* arr);
%ignore OdGsFiler::rdUInt16Array(OdUInt32 count, OdUInt16* arr);
%ignore OdGsFiler::rdUInt32Array(OdUInt32Vector& arr);
%ignore OdGsFiler::rdUInt64Array(OdUInt64Vector& vec);
%ignore OdGsFiler::rdUInt64Array(OdUInt32 count, OdUInt64* arr);
%ignore OdGsFiler::rdFloatArray (OdUInt32 count, float* arr);
%ignore OdGsBlockRefNodeDesc::getImpl;
%ignore FontCircle;
%ignore FontArc;
%ignore _TypeShapeInfo;
%ignore _OdShapeInfo;
%ignore OdShapeMap;
%ignore OdShapePositionStack;
%ignore OdGiExtents3dSpaceChainPolyline::getPoints(OdGePoint3dVector& pts);
%ignore OdGiExtents3dSpaceChainPolyline::getPoints_closed(OdGePoint3dVector& pts);
%ignore GeMesh::OdGeTrMesh::dump;
%ignore OdAuxData::set;
%ignore OdAuxData::get;
%ignore OdApcQueueHelper::OdApcQueueHelper(const OdRxObjectPtr& pObject);
%ignore OdApcQueueHelper::OdApcQueueHelper(const OdRxObject* pObject);
%ignore OdApcQueueHelper::OdApcQueueHelper(const OdSmartPtr<OdApcQueue>& pObject);
%ignore odStrToD(const char* p, char** ppend = 0);
%ignore odStrToD(const OdAnsiString&);
%ignore odStrToD(const OdChar* p, OdChar** ppend = 0);
%ignore OdGeTess::Contour::intersections_lv;
%ignore OdGeScale2d::inverse;
%ignore OdGeScale2d::operator[](unsigned int i);
%ignore OdGeScale2d::operator [](unsigned int i);
%ignore TD_PDF::TD_PDF_HELPER_FUNCS::getUnicodeTextString(const OdAnsiString &pStr, PDFTextStringPtr pUnicodeStr);
%ignore OdVariant::getStringPtr;
%ignore OdVariant::getAnsiStringPtr;
%ignore OdVariant::getRxObjectPtrPtr;
%ignore OdVariant::getBoolPtr;
%ignore OdVariant::getInt8Ptr;
%ignore OdVariant::getUInt8Ptr;
%ignore OdVariant::getInt16Ptr;
%ignore OdVariant::getUInt16Ptr;
%ignore OdVariant::getInt32Ptr;
%ignore OdVariant::getUInt32Ptr;
%ignore OdVariant::getInt64Ptr;
%ignore OdVariant::getUInt64Ptr;
%ignore OdVariant::getDoublePtr;
%ignore OdVariant::setStringPtr;
%ignore OdVariant::setAnsiStringPtr;
%ignore OdVariant::setRxObjectPtrPtr;
%ignore OdVariant::setBoolPtr;
%ignore OdVariant::setInt8Ptr;
%ignore OdVariant::setUInt8Ptr;
%ignore OdVariant::setInt16Ptr;
%ignore OdVariant::setUInt16Ptr;
%ignore OdVariant::setInt32Ptr;
%ignore OdVariant::setUInt32Ptr;
%ignore OdVariant::setInt64Ptr;
%ignore OdVariant::setUInt64Ptr;
%ignore OdVariant::setDoublePtr;
%ignore OdGsLayoutHelperIntCache;
%ignore OdGsBaseVectorizeView::doCollide;
%ignore OdGsBaseVectorizeView::doCollideAll;



%ignore OdDbGripData::OdDbGripData(const OdGePoint3d& pt, void* AppData, GripOperationPtr hotGrip, GripOperationPtr hoverGrip, GripRtClkHandler RtClk, GripWorldDrawPtr wd, GripViewportDrawPtr vd, GripOpStatusPtr stat, GripToolTipPtr tt, GripDimensionPtr hoverDim, GripDimensionPtr hotGripDim, unsigned bitFlags, OdGePoint3d* altBasePt, GripInputPointPtr inputPointFunc);

%ignore OdDbGripData::OdDbGripData(const OdGePoint3d& pt, void* AppData, OdRxClass* pAppDataClass, GripOperationPtr hotGrip, GripOperationPtr hoverGrip, GripRtClkHandler RtClk, GripWorldDrawPtr wd, GripViewportDrawPtr vd, GripOpStatusPtr stat, GripToolTipPtr tt, GripDimensionPtr hoverDim, GripDimensionPtr hotGripDim, unsigned bitFlags, OdGePoint3d* altBasePt, GripInputPointPtr inputPointFunc);

%ignore OdDbGripData::setAllData(const OdGePoint3d& pt, void* AppData, GripOperationPtr hotGrip, GripOperationPtr hoverGrip, GripRtClkHandler RtClk, GripWorldDrawPtr wd, GripViewportDrawPtr vd, GripOpStatusPtr stat, GripToolTipPtr tt, GripDimensionPtr hoverDim, GripDimensionPtr hotGripDim, unsigned bitFlags, OdGePoint3d* altBasePt, GripInputPointPtr inputPointFunc,  OdRxClass* pAppDataClass);

%ignore OdDbGripData::inputPointFunc;
%ignore OdDbGripData::setInputPointFunc;

%ignore OdDbGripData::hoverDimensionFunc;
%ignore OdDbGripData::setHoverDimensionFunc;

%ignore OdDbGripData::hotGripDimensionFunc;
%ignore OdDbGripData::setHotGripDimensionFunc;

%ignore OdDbCustomOsnapMode;

%ignore TD_PDF_2D_EXPORT::PDFExportParams::currentVersion;
%ignore TD_PDF_2D_EXPORT::SavedGsModelData;
%ignore TD_PDF_2D_EXPORT::AutoSavedGsModelData;
%ignore TD_PDF_2D_EXPORT::AutoRestoreGsModelData;

%ignore OdGsBaseVectorizer::playMetafileMode;

%ignore OdRxPropertyVariant::operator=(const OdAnsiString& val);

%ignore OdByteData::desc;
%ignore OdByteData::cast;
%ignore OdByteData::createObject;

%ignore OdOleStorage::desc;
%ignore OdOleStorage::cast;
%ignore OdOleStorage::createObject;
%ignore OdOleStorage::createServiceObject;

%ignore OdTfObjectPE::createObject;
%ignore OdTfObjectPE::cast;
%ignore OdTfObjectPE::desc;

%ignore OdIBrFace::getSurfaceAsTrimmedNurbs;
%ignore TD_PDF::PDFObjectID::Export;

%ignore OdGiPsFillstyles::getGDIDefinitions;
%ignore OdGiPsFillstyles::getGDIDefinition;
%ignore OdGiPsFillstyles::getOpenGLDefinitions;
%ignore OdGiPsFillstyles::getOpenGLDefinition;
%ignore va_list;

%ignore OdRxSubProperty::createObject;

%ignore OdGsBlockNode::findDef;
%ignore OdGsBlockReferenceNodeImpl::doSpatialQuery;

%ignore OdGsContainerNode::isMetafilesCompatible;
%ignore OdGsEntityNode::findCompatibleCache;
%ignore OdGsEntityNode::isMetafilesCompatible;
%ignore OdGsNode::isMetafilesCompatible;

%ignore ThreadsCounter::ThreadsCounter;

%ignore OdVariant::getAnsiStringArray;
%ignore OdVariant::asAnsiStringArray;
%ignore OdVariant::getAnsiStringArrayPtr;
%ignore OdVariant::setAnsiStringArray;
%ignore OdVariant::setAnsiStringArrayPtr;

%ignore GeMesh::OdGeTrMesh::m_aTr;
%ignore GeMesh::OdGeTrMesh::m_vxToTr;

%ignore OdRxPropertyVariant::asAnsiStringArray;
%ignore OdRxPropertyVariant::setAnsiStringArray;
%ignore OdRxPropertyVariant::getAnsiStringArray;

%ignore OdGiMapperItemEntry::mapCoords(const double *trg, double *uv) const;
%ignore OdGiMapperItemEntry::mapCoords(const double *trg, const double *normal, double *uv) const;

%ignore OdRxSpecifiedValueType;
%ignore OdGiLayerTraitsTakerView::OdGiLayerTraitsTakerView;
%ignore OdGiLayerTraitsTaker::OdGiLayerTraitsTaker;
%ignore OdGiLayerTraitsTaker::OdGiLayerTraitsTaker();
%ignore OdGiLayerTraitsTaker::OdGiLayerTraitsTaker(const OdGiBaseVectorizer pRefView, OdGiContext pContext = NULL);

%ignore OdCharMapper::convertAlphaNumJapanese(const OdAnsiString& strText);
%ignore OdGiShell;

%ignore OdGUID::OdGUID(const OdAnsiString& value);
%ignore OdGUID::OdGUID(const char* value);
%ignore OdGUID::operator=(const OdAnsiString& other);
%ignore OdGUID::operator=(const char* other);

#ifdef SWIGJAVA
%ignore OdRxGenerateDynamicPropertiesAttribute::cast;
%ignore OdRxGenerateDynamicPropertiesAttribute::desc;
%ignore OdRxGenerateDynamicPropertiesAttribute::createObject;
#else
IGNORE_AS_NOT_IMPLEMENTED_4_desc(%arg(OdRxGenerateDynamicPropertiesAttribute))
#endif

%ignore OdGsBaseModel::trySetDisableInvalidate;