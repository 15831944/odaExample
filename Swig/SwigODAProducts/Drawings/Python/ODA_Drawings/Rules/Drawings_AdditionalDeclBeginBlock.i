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

%begin
%{
class RxSystemServicesImpl;
class OdDbDxfFiler;
class OdDbDwgFiler;
class OdGeAugPolyline3d;
class OdGeRay3d;
class OdGeSurfaceCurve2dTo3d;
class OdGeOffsetCurve3d;
class OdGeExternalCurve3d;
class OdGeCubicSplineCurve3d;
class OdGsProperties;
class OdGsRenderEnvironmentProperties;
class OdGsRenderSettingsProperties;
class OdGsVisualStyleProperties;
class OdGsBackgroundProperties;
class OdGsViewportProperties;
class OdRxMemberOverrule;
class OdRxPropertyOverrule;
class OdRxCollectionPropertyOverrule;
class OdGsBaseVectorizeDevice;
class OdGiXform;
class OdGiPerspectivePreprocessor;
class OdGiModelSection;
class OdGiHLRemover;
class OdGiConveyorEmbranchment;
class OdGiOrthoPrismIntersector;
class OdGiSelectProc;
class OdGiCollideProc;
class OdGiXformOptimizer;
class OdGiOrthoClipper;
class OdGiOrthoClipperEx;
class OdGiXformOptimizer;
class OdGiTranslationXform;
class OdGiXYProjector;
class OdGiPlaneProjector;
class OdGiExtAccum;
class OdGiOrthoClipper;
class OdGiMetafiler;
class OdGiRectIntersDetector;
class OdGiDgLinetyper;
class OdGiSelector;
class OdGiClippedGeometryConnector;
class OdGiDgLinetyper;
class OdGiLinetypeRedir;
class OdGiPlotGenerator;
class OdGsExtAccum;
class OdGiMapperItem;
class OdGiMapperRenderItem;
class OdGiBaseVectorizerImpl;
class OdGsBaseVectorizer;
class OdGsBaseMaterialViewPC;
class OdGsBaseMaterialVectorizer;
class OdSiRecursiveVisitorTf;
class OdGsSpQueryContextTf;
class OdMemoryStream;
class OdOleItemInitStream;
class OdGiViewportDraw_;
class OdGiBaseVectorizer;
class OdGiExtCalc;
class OdGiWorldDraw_;
class OdRxVariant;
class OdRxVariantValue;
class OdGiLayerTraitsTakerView;
class OdGiWorldDrawImpl;
class OdGsBaseModel;
class OdGsBlockReferenceNode;
class OdGsEntityNode;
class Metafile;
class OdGsMInsertBlockNode;
class OdFontMapper;
class OdGiClipBoundaryWithAbstractData;
class OdGiHatchPattern;
class OdGiLayerTraitsTaker;
class OdGiMaterialItem;
class TxErrorContext;
class OdApcQueue;
class OdApcQueueHelper;
class OdIBaseTraverser;
class OdITrEdgeLoop;
class OdRxAttribute;
class OdRxCumulativeAttribute;
class OdRxUiCascadingContextMenuAttribute;
class OdRxUseDialogForReferredCollectionAttribute;
class OdRxGenerateDynamicPropertiesAttribute;
class OdRxUnitTypeAttribute;
class OdRxFlagsAttribute;
class OdRxFilePathAttribute;
class OdRxCOMAttribute;
class OdRxRefersToAttribute;
class OdRxDescriptionAttribute;
class OdRxLMVAttribute;
class OdRxUiPlacementAttribute;
class OdRxLocalizedNameAttribute;
class OdRxAlternateLocalizedNameAttribute;
class OdRxLocalizedNameAttribute;
class OdRxAffinityAttribute;
class OdRxTypePromotionAttribute;
class OdRxUnionTypeAttribute;
class OdRxDefaultValueAttribute;
class OdRxAlternateLocalizedNameAttribute;
class OdPrcContextForPdfExportWrapper;
class OdGsBaseVectorizeView;
class OdGsViewImpl;
class OdOleItemHandlerBase;
class OdOleItemSimplestHandler;
class OdGiClipBoundaryWithAbstractData;
class OdDbAnnotScaleObjectContextData;
class OdDbObjectContextData;
class OdPrcContextForPdfExport;
class OdGsEntityNode;
class MetafileEx;
class Metafile;
class OdRxPropertyBase;
class OdRxProperty;
class OdRxCollectionProperty;
class OdRxIndexedProperty;
class OdRxDictionaryProperty;
class OdRxSubProperty;
class OdRxSubPropertyOfIndexedProperty;
class OdRxIndexedSubProperty;
class OdTfVariant;
class OdGiMaterialRenderItem;
class OdGiLayerTraits_;
class OdGiSubEntityTraits_;
class OdGiFaceDataStorage;
class OdGsCullingOBBox;
class OdGiClippedGeometryOutput;
class OdGiSectionGeometryOutput;
class OdGiCuttedGeometryOutput;
class OdGsCullingVolume;
class OdGsOrthoCullingVolume;
class OdGsFrustumCullingVolume;
class OdTfClass;
class OdRxValueType;
class OdShxFont;
class OdTrueTypeFontBase;
class OdGsCullingBBox;
class OdGsBlockNode;
class OdIBrMesh;
class OdIBrMesh2d;
class OdEdLispEngine;
class OdGsBackground;
class OdRxPropDesc;
class OdGiProceduralGeneratorPE;
class OdRxMember;
class OdIBrMeshEntity;
class OdIBrElement;
class OdIBrElement2d;
class OdGiMaterialTextureEntry;
class OdApcAtom;
class OdAsyncForEachBase;
class OdGiMapperItemEntry;
class OdPdf2ImageConverter;
class OdGiMaterialTraits_Stub;
class OdBrepBuilderFillerModule;
class OdDwfxSignatureHandlerModule;
class OdEdLispModule;
class OdTfObjectReactor;
class OdTfPersistentReactor;
class OdEdLispEngineReactor;
class OdRasterConvertPE;
class PdfExportGiDrawablePE;
class OdGiRasterImageLoaderPE;
class OdDbHyperlinkCollection;
class OdRxBoxedValue;
class OdGiDgLinetypeTraits;
class OdFontServices;
class OdRasterProcessingServices;
class OdRxRcsFileServices;
class OdRxRasterServices;
class OdRxPdfToRasterServices;
class OdGiTransientManagerPE;
class OdRxMemberQueryContext;
class OdRxMemberQueryContext;
class OdRxPromotingQueryContext;
class OdFontTable;
class OdGsBitMap;
class OdGiGeometryMetafile;
class OdApcThread;
class OdGiMaterialTextureData;
class OdGiSectionGeometryMap;
class OdGiMaterialTextureManager;
class OdGiTransientManager;
class OdGsPalette;
class OdGiModelToViewProc;
class PdfExportLayerPE;
class OdGiSpatialFilter;
class OdIBrNode;
class OdRxVoidStore;
class OdApcDataReadWriteDispatcher;
class OdTfPropertiesContainer;
class OdTfAttributesContainer;
class OdTfProperty;
class OdApcEvent;
class OdGiGeometryRecorderPlayer;
class OdTfAttribute;
class OdTfObject;
class OdApcObjectPool;
class OdApcGateway;
class OdApcLoopedGateway;
class OdGiClippedGeometryOutputCallback;
class OdGiMaterialTextureLoadPE;
class OdRxFacetProvider;
class OdTimeProvider;
class OdGiMaterialTraitsTaker;
class OdGiHlrResults;
class OdRxCategory;
class OdGiMaterialTextureLoaderExt;
class OdTfDatabase;
class OdGiRasterImageLoader;
class OdRxResourceLoader;
class OdGiProceduralGenerator;
class OdGiNoiseGenerator;
class OdRxValueIterator;
class OdRxMethod;
class OdDbEntityHyperlinkPE;
class OdRxEnumTag;
class TxError;
class OdError_WithId;
class OdGsDrawCancelException;
class OdBrException;
class OdBrVertex;
class OdBrComplex;
class OdBrFace;
class OdBrEdge;
class OdBrLoop;
class OdBrShell;
class OdRxSpecifiedValueType;
class OdRxHierarchyLevelAttribute;
class OdRxDisplayAsAttribute;
class OdGiProgressiveMesh;
class OdRxSpecifiedValueType;
class PdfExportServiceInterface;
class OdRxModelTreeBaseNode;
class OdRxModelHierarchyTreeBase;
class PyOdRxVariantValue;
class OdRxPropertyVariant;
class ExStringIO;
class OdError_InvalidRxPropertyVariantType;
class OdGiProgressiveMeshEx;
class OdGiDrawableSelectPE;
class OdBaseFileBuf;
class OdRdFileBuf;
class OdWrFileBuf;
class OdByteData;
class OdOleStorage;
class OdRawByteData;
class OdOleStorageError;
class OdGeOffsetCurve2d;
class OdGeExternalCurve2d;
class OdGeCubicSplineCurve2d;
class OdGeCompositeCurve2d;
class OdGeRay2d;
class OdGeOffsetCurve2d;
class OdGeExternalCurve2d;
class OdGiShellToolkit;
class OdGiPointCloudReceiver;
class OdGiPointCloudExtentsReceiver;
class OdGiPointCloudXformFilter;
class ExUndoController;
class ExFileUndoController;
class OdRxDynamicAttribute;
class OdRxDynamicCollectionAttribute;
class OdColorConverterCallback;
class OdGsLayoutHelperIntCache;
class OdGiFillHatch;
class OdGiPointCloudComponentsFilter;


namespace TD_THREEJSJSON_EXPORT
{
  class ThreejsJSONModule;
};
namespace TD_STL_EXPORT
{
  class STLModule;
};
namespace TD_PDF_2D_EXPORT
{
  class PdfExportModule;
  class OdPdfExport;
  class OdPdfExportPE;
};
namespace TD_DWF_EXPORT
{
  class DwfExportModule;
  class OdDwfExport;
};
namespace OdSi
{
  class BBox;
  class Extent3d;
};
namespace TD_COLLADA_EXPORT
{
  class ColladaModule;
  class ColladaImportModule;
};
namespace OD
{
  class Path;
};

#include "Gs/GsEntityNode.h"
#include "Gi/GiVisualStyleData.h"
#include "DbUnderlayItem.h"
#include "DbUndoController.h"
#include "OleItemHandler.h"
%}
