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
// GLES2 metafiles stream definitions

#ifndef _EXTRVISMETAFILESTREAM_INCLUDED_
#define _EXTRVISMETAFILESTREAM_INCLUDED_

#include "TD_PackPush.h"

#include "MetafileStreamBase.h"
#include "Gs/Gs.h"
#include "TrVisDefs.h"
#include "Ps/PlotStyles.h"

// Enable conversion from double to float for vertex and normal buffers
#define OD_TRVIS_ENABLEFLOATCONVERSION

#ifdef OD_TRVIS_ENABLEFLOATCONVERSION
typedef float OdTrVisVertexType;
#else
typedef double OdTrVisVertexType;
#endif

void od_dbl2float(float *pFloats, const double *pDoubles, size_t numData);

enum OdTrVisMetaRecType // Currently packed as one byte
{
  OdTrVisMetaRecType_Empty              = 0x00, // No data record (useful for padding)
  OdTrVisMetaRecType_EnableOpt          = 0x01, // Enable rendering option
  OdTrVisMetaRecType_DisableOpt         = 0x02, // Disable rendering option
  OdTrVisMetaRecType_Color              = 0x03, // Setup color
  OdTrVisMetaRecType_EnableArray        = 0x04, // Enable rendering array
  OdTrVisMetaRecType_DisableArray       = 0x05, // Disable rendering array
  OdTrVisMetaRecType_DrawArrays         = 0x06, // Draw primitive
  OdTrVisMetaRecType_DrawElements       = 0x07, // Draw indexed primitive
  OdTrVisMetaRecType_CullFace           = 0x08, // Setup faces culling
  OdTrVisMetaRecType_LStipple           = 0x09, // Setup line pattern
  OdTrVisMetaRecType_PStipple           = 0x0A, // Setup fill pattern
  OdTrVisMetaRecType_VPoint             = 0x0B, // Draw single point (32 bit float format)
  OdTrVisMetaRecType_VLine              = 0x0C, // Draw single line (32 bit float format)
  OdTrVisMetaRecType_IPoint             = 0x0D, // Draw single indexed point
  OdTrVisMetaRecType_ILine              = 0x0E, // Draw single indexed line
  OdTrVisMetaRecType_HLRStencil         = 0x0F, // Enable HLR shading mode
  OdTrVisMetaRecType_EnableShading      = 0x10, // Enable shading option
  OdTrVisMetaRecType_DisableShading     = 0x11, // Disable shading option
  OdTrVisMetaRecType_Material           = 0x12, // Change material (shaded mode)
  OdTrVisMetaRecType_UserEntry          = 0x13, // User can process own data entries
  OdTrVisMetaRecType_InitTexture        = 0x14, // Set texture for raster image
  OdTrVisMetaRecType_UninitTexture      = 0x15, // Reset texture for raster image
  OdTrVisMetaRecType_SelectionMarker    = 0x16, // Stand-alone selection marker
  OdTrVisMetaRecType_EnableMarkerArray  = 0x17, // Enable markers array
  OdTrVisMetaRecType_DisableMarkerArray = 0x18, // Disable markers array
  OdTrVisMetaRecType_VisibilityFlags    = 0x19, // Display and selection geometry visibility flags
  OdTrVisMetaRecType_Lineweight         = 0x1A, // Lineweight
  OdTrVisMetaRecType_Linestyle          = 0x1B, // Cap&Joint style
  OdTrVisMetaRecType_Program            = 0x1C, // Shader program
  OdTrVisMetaRecType_TtfText            = 0x1D, // Cached TtfFont
  OdTrVisMetaRecType_PushMatrix         = 0x1E, // Push transformation matrix
  OdTrVisMetaRecType_PopMatrix          = 0x1F, // Pop transformation matrix
  OdTrVisMetaRecType_Metafile           = 0x20, // Play nested metafile
  OdTrVisMetaRecType_GeomMarker         = 0x21, // Geometry marker
  OdTrVisMetaRecType_VisualStyle        = 0x22, // Visual Style
  OdTrVisMetaRecType_MetafileMarker     = 0x23, // Stand-alone metafile marker
  OdTrVisMetaRecType_ExtensionObject    = 0x24, // Play extension object graphics
  OdTrVisMetaRecType_SelectionStyle     = 0x25, // Highlighting with non-default style
  OdTrVisMetaRecType_DPoint             = 0x26, // Draw single point (64 bit float format)
  OdTrVisMetaRecType_DLine              = 0x27, // Draw single line (64 bit float format)
  OdTrVisMetaRecType_Block              = 0x28, // Nested block marker

  OdTrVisMetaRecType_NTypes                     // == last + 1
};

// Convert OdTrVisMetaRecType into string representation
const OdChar *chunkDecode(OdTrVisMetaRecType rt);

enum OdTrVisMetaRecArrayType // Type of rendering array
{
  OdTrVisMetaRecArrayType_Vertex          = 0x00, // Vertexes array
  OdTrVisMetaRecArrayType_Color           = 0x01, // Colors array
  OdTrVisMetaRecArrayType_DiffuseTexCoord = 0x02, // Texture coordinates array
  OdTrVisMetaRecArrayType_OpacityTexCoord = 0x03, // Opacity texture coordinates array
  OdTrVisMetaRecArrayType_BumpMapTexCoord = 0x04, // Bump-mapping texture coordinates array
  OdTrVisMetaRecArrayType_Normal          = 0x05, // Primary normals array
  OdTrVisMetaRecArrayType_Normal2         = 0x06, // Secondary normals array
  OdTrVisMetaRecArrayType_BumpTNormal     = 0x07, // First bump-mapping normals
  OdTrVisMetaRecArrayType_BumpBNormal     = 0x08, // Second bump-mapping normals
  OdTrVisMetaRecArrayType_Depth           = 0x09, // Depths array
  OdTrVisMetaRecArrayType_SpriteCoord     = 0x0A, // Trails data array

  OdTrVisMetaRecArrayType_NTypes               // == last + 1
};

enum OdTrVisMetaRecMarkerType // Type of markers array
{
  OdTrVisMetaRecMarkerType_Selection   = 0x00, // Selection markers array
  OdTrVisMetaRecMarkerType_Metafile    = 0x01, // Metafile markers array

  OdTrVisMetaRecMarkerType_NTypes              // == last + 1
};

enum OdTrVisAttribute // List of attributes which modifies rendering conveyor states
{
  OdTrVisAttribute_Depth               = 0x00, // Disable depth buffer
  OdTrVisAttribute_Blend               = 0x01, // Enable colors blending (transparency)
  OdTrVisAttribute_Lighting            = 0x02, // Faces lighting state
  OdTrVisAttribute_Highlighting        = 0x03, // Highlighting state

  OdTrVisAttribute_NTypes,                     // == last + 1
  OdTrVisAttribute_Mask                = 0x0F
};

enum OdTrVisShading // List of shading attributes which modifies geometry behavior
{
  OdTrVisShading_Gouraud               = 0x00, // Vertex colors state
  OdTrVisShading_MultiNormals          = 0x01, // Face come with vertex and face normals for gouraud and flat shading
  OdTrVisShading_Disable2dLineweights  = 0x02, // Disable lineweight display in 2d
  OdTrVisShading_NoColorOverride       = 0x03, // Avoid all color overrides
  OdTrVisShading_LinkedLinesList       = 0x04, // Marks geometry with linked line lists

  OdTrVisShading_NTypes,                       // == last + 1
  OdTrVisShading_Mask                  = 0x1F
};

enum OdTrVisFaceCulling // List of face culling states
{
  // Culling modes for faces
  OdTrVisCullFace_None                 = 0x00, // Disable face culling (default state)
  OdTrVisCullFace_Back                 = 0x01, // Enable back faces culling
  OdTrVisCullFace_Front                = 0x02, // Enable front faces culling
  OdTrVisCullFace_Default              = 0x03, // Invoke default faces culling method
  // Culling modes for edges
  OdTrVisCullEdge_None                 = 0x00, // Disable edge culling (default state)
  OdTrVisCullEdge_Back                 = 0x04, // Back edges culling
  OdTrVisCullEdge_Front                = 0x08, // Front edges culling
  OdTrVisCullEdge_Default              = 0x0C, // Default edges culling method
  // Number of invoked flags
  OdTrVisCullEdge_NFlags               = 4
};

// OdTrVisFaceCulling helpers
inline OdTrVisFaceCulling combineCullingModes(OdTrVisFaceCulling faceMode, OdTrVisFaceCulling edgeMode)
{ return (OdTrVisFaceCulling)(faceMode | edgeMode); }
inline void splitCullingModes(OdTrVisFaceCulling &cullingMode, OdTrVisFaceCulling &edgeMode)
{ edgeMode = (OdTrVisFaceCulling)(cullingMode & OdTrVisCullEdge_Default); cullingMode = (OdTrVisFaceCulling)(cullingMode & OdTrVisCullFace_Default); }
inline OdTrVisFaceCulling faceCullingModeAsEdge(OdTrVisFaceCulling faceMode)
{ return (OdTrVisFaceCulling)((faceMode & OdTrVisCullFace_Default) << 2); }
inline OdTrVisFaceCulling edgeCullingModeAsFace(OdTrVisFaceCulling edgeMode)
{ return (OdTrVisFaceCulling)((edgeMode >> 2) & OdTrVisCullFace_Default); }

enum OdTrVisVisibilityFlags
{
  OdTrVisVblFlag_DontDisplayUnhighlighted = (1 << 0), // Don't display underlying geometry if it is not highlighted.
  OdTrVisVblFlag_DontSelectUnhighlighted  = (1 << 1), // Don't select underlying geometry if it is not highlighted.
  OdTrVisVblFlag_DontDisplayHighlighted   = (1 << 2), // Don't display underlying geometry if it is highlighted.
  OdTrVisVblFlag_DontSelectHighlighted    = (1 << 3), // Don't select underlying geometry if it is highlighted.
  OdTrVisVblFlag_DontDisplayIn2d          = (1 << 4), // Don't display underlying geometry in 2d rendering mode.
  OdTrVisVblFlag_DontSelectIn2d           = (1 << 5), // Don't select underlying geometry in 2d rendering mode.
  OdTrVisVblFlag_DontDisplayIn3d          = (1 << 6), // Don't display underlying geometry in 3d rendering modes.
  OdTrVisVblFlag_DontSelectIn3d           = (1 << 7), // Don't select underlying geometry in 3d rendering modes.
  OdTrVisVblFlag_FlagsMask                = 255,
  OdTrVisVblFlag_Default                  = 0
};

enum OdTrVisAffection // List of metafile affections
{
  OdTrVisAffection_Attributes          =  0x01,        // Affects attributes/disable/enable
  OdTrVisAffection_Colors              = (0x01 << 1),  // Affects color
  OdTrVisAffection_Materials           = (0x01 << 2),  // Affects materal
  OdTrVisAffection_Arrays              = (0x01 << 3),  // Affects arrays
  OdTrVisAffection_Geometry            = (0x01 << 4),  // Call's geometry rendering
  OdTrVisAffection_Proxy               = (0x01 << 5)   // Proxy rendering invoked
};

enum OdTrVisPushMatrixType // Type of matrixes utilized by PushMatrix metafile entries
{
  OdTrVisPushMatrixType_Identity = 0, // Identity matrix, no input matrix
  OdTrVisPushMatrixType_Full          // Complete 4x4 matrix
};

enum OdTrVisBlockRecType // Type of block record utilized by Block metafile entries
{
  OdTrVisBlockRecType_Auto      = 0x41, // 'A' : Renderer should automatically filter embedded metafiles list.
  OdTrVisBlockRecType_BuiltIn   = 0x42, // 'B' : Render already registered block stream list.
  OdTrVisBlockRecType_SizedAuto = 0x43, // 'C' : "Auto" with precalculated number of metafile entries.
  OdTrVisBlockRecType_Sized     = 0x44, // 'D' : "Embedded" with precalculated number of metafile entries.
  OdTrVisBlockRecType_Embedded  = 0x45, // 'E' : Store single copy of embedded metafiles list.
  OdTrVisBlockRecType_EOF       = 0x46  // 'F' : EOF for 'A' and 'E'. Ignored elsewhere.
};

enum OdTrVisGeomType
{
  OdTrVisGeomType_Default           = 0, // Non-classified geometry which take part in any rendering mode, like simple lines
  // Facet markers
  OdTrVisGeomType_2dFacets          = 1, // Non-shaded facets (visible in all modes except hidden line)
  OdTrVisGeomType_2dFacetsNoFill    = 2, // Non-shaded facets (visible in all modes except hidden line), invisible in 2d
  OdTrVisGeomType_3dFacets          = 3, // Shaded facets (invisible in 2d in case if filling disabled)
  OdTrVisGeomType_3dFacetsNoFill    = 4, // Shaded facets (invisible in 2d in case if filling disabled), invisible in 2d
  OdTrVisGeomType_RasterImageFacets = 5, // Raster image facets (visible in all modes)
  // Edge markers
  OdTrVisGeomType_2dFacetEdges      = 6, // Non-shaded facet edges (invisible in shaded modes w/o wireframe)
  OdTrVisGeomType_3dFacetEdges      = 7, // Shaded facet edges (available with isolines only)
  OdTrVisGeomType_Isolines          = 8, // Isolines (simple polylines doesn't marked)
  OdTrVisGeomType_EdgesWithIsolines = 9, // Represent shaded facet edges and isolines together
  OdTrVisGeomType_HatchIsolineEdges = 10, // Hatch isoline edges (invisible in HiddenLine)
  OdTrVisGeomType_FillPatternEdges  = 11, // Shell filling patterns (for ODA BimRv filling patterns support)
  OdTrVisGeomType_IntersectionEdges = 12, // Intersection edges
  OdTrVisGeomType_Silhouettes       = 13, // Silhouettes (stub for future needs)
  // Number of registered geometry visibility types
  OdTrVisGeomType_NTypes
};

// Check visibility of geometry type for specified rendering mode
bool isGeomTypeVisible(OdTrVisGeomType geomType, OdGsView::RenderMode rMode);

// Geometry primitives
enum OdTrVisGeomPrim
{
  kTrVisGeomPrimInvalid = -1,
  kTrVisPoints          = 0,
  kTrVisLines           = 1,
  kTrVisLineLoop        = 2,
  kTrVisLineStrip       = 3,
  kTrVisTriangles       = 4,
  kTrVisTriangleStrip   = 5,
  kTrVisTriangleFan     = 6
};

/** \details
    This structure extends flat metafile containers by specific array elements.

    <group !!RECORDS_TD_APIRef>
*/
struct OdTrVisArrayWrapper
{
  void *m_pData;
  OdUInt32 m_uData : 4;  // Data type size (0-1, 1-2, 3-4, 4-8, etc). 
  OdUInt32 m_uSize : 28; // Number of data types (Full data size = m_uSize << m_uData).
  OdUInt32 m_type : 4;   // Data type layout
  OdUInt32 m_bind : 28;  // Binding index (depends from renderer)

  enum Type
  { // Actually represents only data layout. Physically can be used for different processes.
    Type_Vertex = 0, // Flt*3
    Type_Normal,     // Flt*3 (normalized)
    Type_Color,      // Flt*4
    Type_TexCoord,   // Flt*2
    Type_Depth,      // Flt*1
    Type_Index,      // U16*1
    Type_Marker,     // Marker

    Type_Cache,      // For internal use
    Type_Selection,  //Mapped vertices for gpu selection
    Type_Invalid = 0x0F,
    Type_NoReset = Type_Invalid
  };

  enum DataSize
  { DS_1 = 0, DS_2 = 1, DS_4 = 2, DS_8 = 3, DS_16 = 4, DS_32 = 5, DS_64 = 6 };

  OdTrVisArrayWrapper()
    : m_pData(NULL)
    , m_uData(0)
    , m_uSize(0)
    , m_type(Type_Invalid)
    , m_bind(0)
  { }

  inline OdUInt32 arraySize() const { return m_uSize << m_uData; }
  inline Type type() const { return (Type)m_type; }
  inline DataSize dataSize() const { return (DataSize)m_uData; }
  static OD_CONSTEXPR_FUNC DataSize dataSizeEst(size_t dataSize)
  { return ((dataSize == 1) ? DS_1 : ((dataSize == 2) ? DS_2 : ((dataSize == 4) ? DS_4 : ((dataSize == 8) ? DS_8 :
           ((dataSize == 16) ? DS_16 : ((dataSize == 32) ? DS_32 : ((dataSize == 64) ? DS_64 : DS_1)))))));
  }

  static const struct ReallocLogic
  { OdInt32 m_nGrowOption;
    ReallocLogic(OdInt32 nGrowOption = 0)
      : m_nGrowOption(nGrowOption) { }
    void *extendArray(OdTrVisArrayWrapper &arry, OdUInt32 nBytesAlloc) const;
  } g_defaultReallocLogic;

  void setArray(Type type, const void *pPtr, OdUInt32 size, DataSize ds);
  void clearArray();
  void optimizeArray();
  void truncateArray(OdUInt32 size, DataSize ds);
  void concatArray(const void *pPtr, OdUInt32 size, DataSize ds, const ReallocLogic &racLg = g_defaultReallocLogic);

  OD_FORCEINLINE void setArray(Type type, const void *pPtr, OdUInt32 size, size_t ds)
  { setArray(type, pPtr, size, dataSizeEst(ds)); }
  OD_FORCEINLINE void concatArray(const void *pPtr, OdUInt32 size, size_t ds, const ReallocLogic &racLg = g_defaultReallocLogic)
  { concatArray(pPtr, size, dataSizeEst(ds), racLg); }

  // Double->float
  void setArray_flt(Type type, const double *pPtr, OdUInt32 size);
  void concatArray_flt(const double *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);
  // UInt8->float
  void setArray_flt(Type type, const OdUInt8 *pPtr, OdUInt32 size);
  void concatArray_flt(const OdUInt8 *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);
  // UInt8->double
  void setArray_dbl(Type type, const OdUInt8 *pPtr, OdUInt32 size);
  void concatArray_dbl(const OdUInt8 *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);
  // Float->double
  void setArray_dbl(Type type, const float *pPtr, OdUInt32 size);
  void concatArray_dbl(const float *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);
  // Float->UInt8
  void setArray_u8c(Type type, const float *pPtr, OdUInt32 size);
  void concatArray_u8c(const float *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);
  // Int32->UInt16
  void setArray_ush(Type type, const OdInt32 *pPtr, OdUInt32 size);
  void concatArray_ush(const OdInt32 *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);
  // UInt16->Int32
  void setArray_int(Type type, const OdUInt16 *pPtr, OdUInt32 size);
  void concatArray_int(const OdUInt16 *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);
  // Int32->UInt8
  void setArray_u8i(Type type, const OdInt32 *pPtr, OdUInt32 size);
  void concatArray_u8i(const OdInt32 *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);
  // UInt16->Int8
  void setArray_u8i(Type type, const OdUInt16 *pPtr, OdUInt32 size);
  void concatArray_u8i(const OdUInt16 *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);
  // Float->HalfFloat
  void setArray_hfl(Type type, const float *pPtr, OdUInt32 size);
  void concatArray_hfl(const float *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);
  // Double->HalfFloat
  void setArray_hfl(Type type, const double *pPtr, OdUInt32 size);
  void concatArray_hfl(const double *pPtr, OdUInt32 size, const ReallocLogic &racLg = g_defaultReallocLogic);

  // Convert vertex array to floats (possible for Vertex/Normal/Color/TexCoord and Depth array types only)
  bool asFloatsArray(OdFloatArray &result) const;

  void save(OdGsFiler *pFiler) const;
  void load(OdGsFiler *pFiler);
};

// Selection/metafile markers

template <typename UInt64Type>
struct OdTrVisMarkBase
{
  UInt64Type        m_nMark;
  OdUInt32          m_uFrom;
  typedef  UInt64Type data_type;
  private: OdUInt32 padding;
  public:  OdTrVisMarkBase() : padding(0) {} enum EnPosInit { kNone };
           OdTrVisMarkBase(UInt64Type nMark) : m_nMark(nMark), padding(0) {}
           OdTrVisMarkBase(UInt64Type nMark, OdUInt32 uFrom) : m_nMark(nMark), m_uFrom(uFrom), padding(0) {}
           OdTrVisMarkBase(EnPosInit, OdUInt32 uFrom) : m_uFrom(uFrom), padding(0) {}
};
// Default processing marker (for internal use only)
typedef OdTrVisMarkBase<OdUInt64>          OdTrVisDefProcMark;
// Selection marker
typedef OdTrVisMarkBase<OdTrVisGsMarker>   OdTrVisSelMark;
// Metafile marker
typedef OdTrVisMarkBase<OdTrVisMetafileId> OdTrVisMetaMark;

/** \details

  <group ExRender_Classes> 
*/
struct OdTrVisLwdStyle
{
  protected:
    OdUInt8 m_curStyleDef : 1;
    OdUInt8 m_curUsesDef  : 1;
    OdUInt8 m_curLesStyle : 3;
    OdUInt8 m_curLjsStyle : 3;
  public:
    void reset() { m_curStyleDef = m_curUsesDef = 1; m_curLesStyle = m_curLjsStyle = 0; }
    OdTrVisLwdStyle() { reset(); }
    OdTrVisLwdStyle(bool bByDefault, OdPs::LineEndStyle lesStyle, OdPs::LineJoinStyle ljsStyle)
    { m_curStyleDef = 1; setCurUsesDef(bByDefault); setCurLesStyle(lesStyle); setCurLjsStyle(ljsStyle); }
    void setCurStyleDef(bool bSet) { m_curStyleDef = (bSet) ? 1 : 0; }
    bool curStyleDef() const { return m_curStyleDef != 0; }
    void setCurUsesDef(bool bSet) { m_curUsesDef = (bSet) ? 1 : 0; }
    bool curUsesDef() const { return m_curUsesDef != 0; }
    void setCurLesStyle(OdPs::LineEndStyle curLesStyle) { m_curLesStyle = (OdUInt8)curLesStyle; }
    OdPs::LineEndStyle curLesStyle() const { return (OdPs::LineEndStyle)m_curLesStyle; }
    void setCurLjsStyle(OdPs::LineJoinStyle curLjsStyle) { m_curLjsStyle = (OdUInt8)curLjsStyle; }
    OdPs::LineJoinStyle curLjsStyle() const { return (OdPs::LineJoinStyle)m_curLjsStyle; }
    bool operator ==(const OdTrVisLwdStyle &sec) const
    { if (m_curUsesDef == sec.m_curUsesDef)
      { if (m_curUsesDef) return true;
        return (m_curLesStyle == sec.m_curLesStyle) && (m_curLjsStyle == sec.m_curLjsStyle);
      } return false;
    }
    bool operator !=(const OdTrVisLwdStyle &sec) const
    { if (m_curUsesDef == sec.m_curUsesDef)
      { if (m_curUsesDef) return false;
        return (m_curLesStyle != sec.m_curLesStyle) || (m_curLjsStyle != sec.m_curLjsStyle);
      } return true;
    }
};

/** \details

  <group ExRender_Classes>
*/
struct OdTrVisLwdSetting
{
  enum LwdType
  { kDatabase = 0, kPlotStyle, kPixels, kAbsolute };
  protected:
    union {
      double  m_dLineWeight;
      OdInt64 m_iLineWeight;
    } m_val;
    OdUInt8   m_type;
  public:
    OdTrVisLwdSetting() : m_type(0) { m_val.m_iLineWeight = 0; }
    OdTrVisLwdSetting(double dVal, LwdType typ = kPlotStyle) : m_type(typ) { m_val.m_dLineWeight = dVal; }
    OdTrVisLwdSetting(OdDb::LineWeight lw, LwdType typ = kDatabase) : m_type(typ) { m_val.m_iLineWeight = (OdInt64)lw; }
    OdTrVisLwdSetting(OdInt32 pix, LwdType typ = kPixels) : m_type(typ) { m_val.m_iLineWeight = (OdInt64)pix; }
    // Type
    void setType(LwdType typ) { m_type = (OdUInt8)typ; }
    LwdType type() const      { return (LwdType)m_type; }
    bool isForcedLineweight() const { return (m_type == kPixels) && (m_val.m_iLineWeight > 0); }
    // dLineWeight
    void setDLineWeight(double dVal, LwdType typ = kPlotStyle) { m_val.m_dLineWeight = dVal; m_type = typ; }
    double dLineWeight() const { return m_val.m_dLineWeight; }
    // lwLineWeight
    void setLwLineWeight(OdDb::LineWeight lw, LwdType typ = kDatabase) { m_val.m_iLineWeight = (OdInt64)lw; m_type = typ; }
    OdDb::LineWeight lwLineWeight() const { return (OdDb::LineWeight)m_val.m_iLineWeight; }
    // pixLineWeight
    void setPixLineWeight(OdInt32 pix, LwdType typ = kPixels) { m_val.m_iLineWeight = pix; m_type = typ; }
    OdInt32 pixLineWeight() const { return (OdInt32)m_val.m_iLineWeight; }
    // Comparators
    bool operator ==(const OdTrVisLwdSetting &sec) const
    { if (m_type == sec.m_type)
      { switch (m_type)
        { case kDatabase:
          case kPixels:    return m_val.m_iLineWeight == sec.m_val.m_iLineWeight;
          case kAbsolute:
          case kPlotStyle: return OdEqual(m_val.m_dLineWeight, sec.m_val.m_dLineWeight);
      } }
      return false;
    }
    bool operator !=(const OdTrVisLwdSetting &sec) const
    { if (m_type == sec.m_type)
      { switch (m_type)
        { case kDatabase:
          case kPixels:    return m_val.m_iLineWeight != sec.m_val.m_iLineWeight;
          case kAbsolute:
          case kPlotStyle: return !OdEqual(m_val.m_dLineWeight, sec.m_val.m_dLineWeight);
      } }
      return true;
    }
    bool hasLineweight() const
    { switch (m_type)
      { case kDatabase:  return m_val.m_iLineWeight != OdDb::kLnWt000;
        case kAbsolute:
        case kPlotStyle: return OdNonZero(m_val.m_dLineWeight);
        case kPixels:    return m_val.m_iLineWeight > 1;
      }
      return false;
    }
    bool isPs() const { return GETBIT(m_type, 1); }
    static bool isPs(LwdType type) { return GETBIT(type, 1); }
};

/** \details
  .

  Library: Source code provided.

  <group ExRender_Classes>
*/
class OdTrVisFlatMetafileContainer : public OdFlatMetafileContainer
{
  public:
    OdArray<OdTrVisArrayWrapper> m_ArrayElements; // Array contain pointers to some memory elements
  public:
    OdTrVisFlatMetafileContainer();
    ~OdTrVisFlatMetafileContainer();

    void clearTrVisFlatContainer();

    OdTrVisArrayId appendArrayElement(const OdTrVisArrayWrapper &element)
    {
      m_ArrayElements.push_back(static_cast<const OdTrVisArrayWrapper&>(element));
      return OdTrVisArrayId(m_ArrayElements.size() - 1);
    }
    OdUInt32 arrayElementsSize() const
    {
      return m_ArrayElements.size();
    }
    OdTrVisArrayWrapper &arrayElement(OdTrVisArrayId nElem)
    {
      return m_ArrayElements.at((OdUInt32)nElem);
    }
    const OdTrVisArrayWrapper &arrayElement(OdTrVisArrayId nElem) const
    {
      return m_ArrayElements.at((OdUInt32)nElem);
    }

    OdTrVisArrayId lastArrayElement() const { return OdTrVisArrayId(arrayElementsSize() - 1); }

    OdUInt64 calcArrayElementsSize() const
    { OdUInt64 calcSize = 0;
      const OdUInt32 nArrays = arrayElementsSize(); // Include size of arrays
      for (OdUInt32 nArray = 0; nArray < nArrays; nArray++)
        calcSize += arrayElement((OdTrVisArrayId)nArray).arraySize() + sizeof(OdTrVisArrayWrapper);
      return calcSize;
    }

    // Base container overrides
    void optimizeMemory(OdUInt32 uSize);

    // OdFlatMetafileContainer overrides
    OdFlatMetafileContainer *createMe() const { return new OdTrVisFlatMetafileContainer; }
    // Clone stream data with gaps elimination
    OdFlatMetafileContainer *clone(const Gap *pGaps = NULL) const
    { OdTrVisFlatMetafileContainer *pCont = static_cast<OdTrVisFlatMetafileContainer*>(OdFlatMetafileContainer::clone(pGaps));
      for (OdUInt32 nArray = 0, nArrays = arrayElementsSize(); nArray < nArrays; nArray++)
      { const OdTrVisArrayWrapper &fromArr = arrayElement((OdTrVisArrayId)nArray);
        OdTrVisArrayWrapper newArr; newArr.setArray((OdTrVisArrayWrapper::Type)fromArr.m_type, fromArr.m_pData, fromArr.m_uSize, fromArr.m_uData);
        pCont->appendArrayElement(newArr);
      }
      return pCont;
    }

    OdBaseMetafileContainerReader *createReader() const;
    OdBaseMetafileContainerWriter *createWriter() const;

    // Extended GLES2 container manipulators

    // Direct access to stream memory
    inline const OdUInt8 *memoryPtr() const
    {
      return m_pData;
    }
};

/** \details
  .

  Library: Source code provided.

  <group ExRender_Classes>
*/
class OdTrVisFlatMetafileContainerWriter : public OdFlatMetafileContainerWriter
{
  public:
    OdTrVisFlatMetafileContainerWriter() : OdFlatMetafileContainerWriter() { }
    OdTrVisFlatMetafileContainerWriter(OdBaseMetafileContainer *pContainer) : OdFlatMetafileContainerWriter(pContainer) { }

    inline OdBaseMetafileContainer *createContainer() const
    {
      return new OdTrVisFlatMetafileContainer();
    }

    inline OdTrVisFlatMetafileContainer *glContainer() const { return static_cast<OdTrVisFlatMetafileContainer*>(container()); }
};

/** \details
  .

  Library: Source code provided.

  <group ExRender_Classes>
*/
class OdTrVisFlatMetafileContainerReader : public OdFlatMetafileContainerReader
{
  public:
    OdTrVisFlatMetafileContainerReader() : OdFlatMetafileContainerReader() { }
    OdTrVisFlatMetafileContainerReader(OdBaseMetafileContainer *pContainer) : OdFlatMetafileContainerReader(pContainer) { }

    inline OdBaseMetafileContainer *createContainer() const
    {
      return new OdTrVisFlatMetafileContainer();
    }

    inline OdTrVisFlatMetafileContainer *glContainer() const { return static_cast<OdTrVisFlatMetafileContainer*>(container()); }
};

// Optimization definitions:
#define OD_OGL_RDR_SEEKFWD(pMemPtr, uSize) (pMemPtr) += (uSize)
#define OD_OGL_RDR_SEEKBWD(pMemPtr, uSize) (pMemPtr) -= (uSize)
#define OD_OGL_RDR_SEEKINC(pMemPtr) (pMemPtr)++
#define OD_OGL_RDR_SEEKDEC(pMemPtr) (pMemPtr)--

#define OD_OGL_RDR_READVAL(cType, pMemPtr) *(cType*)(pMemPtr)
#define OD_OGL_RDR_READVALOFFSET(cType, pMemPtr, uOffset) *(cType*)((pMemPtr) + (uOffset))
#define OD_OGL_RDR_READVALRETYPE(cOutType, cInType, pMemPtr) (cOutType)OD_OGL_RDR_READVAL(cInType, pMemPtr)
#define OD_OGL_RDR_READVALOFFSETRETYPE(cOutType, cInType, pMemPtr, uOffset) (cOutType)OD_OGL_RDR_READVALOFFSET(cInType, pMemPtr, uOffset)
#define OD_OGL_RDR_GETPTRNATIVE(cType, pMemPtr) (cType*)(pMemPtr)
#define OD_OGL_RDR_GETPTRNATIVEOFFSET(cType, pMemPtr, uSize) (cType*)((pMemPtr) + (uSize))
#define OD_OGL_RDR_GETPTRSTORAGE(imedType, name, count)
#define OD_OGL_RDR_GETPTR(cType, imedType, name, count, pMemPtr) OD_OGL_RDR_GETPTRNATIVE(cType, pMemPtr)
#define OD_OGL_RDR_GETPTROFFSET(cType, imedType, name, count, pMemPtr, uSize) OD_OGL_RDR_GETPTRNATIVEOFFSET(cType, pMemPtr, uSize)

#define OD_OGL_RDR_INITIATE(pMemPtr, uSize) const OdUInt8 *pMemPtrReadFor = (const OdUInt8*)pMemPtr + uSize
#define OD_OGL_RDR_CHECKEOF(pMemPtr) pMemPtr < pMemPtrReadFor

#include "TD_PackPop.h"

#endif // _EXTRVISMETAFILESTREAM_INCLUDED_
