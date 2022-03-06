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

#ifndef __OD_GS_VISUALIZE_GEOMETRY__
#define __OD_GS_VISUALIZE_GEOMETRY__

#include "TD_PackPush.h"

#include "Gs/GsBaseInclude.h"
#include "Gi/GiGeometrySimplifier.h"
#include "TvFactory.h"
#include "OdPerfTimer.h"
#include "ThreadsCounter.h"
#include "TvImportUserData.h"

class ExGsVisualizeDevice;
class ExGsVisualizeVectorizer;
class ExGsVisualizeView;

typedef OdStack<OdGeMatrix3d> OdTvMatrix3dStack;

struct ExGsVisualizeTvEntityId
{
  OdTvEntityId m_entId;
  OdTvGeometryDataId m_subEntId;
  ExGsVisualizeTvEntityId()
  {
    m_entId.setNull();
    m_subEntId.setNull();
  }

  void reset()
  {
    m_entId.setNull();
    m_subEntId.setNull();
  }

  bool exist() const
  {
    if( !m_entId.isNull() ) return true;
    if( !m_subEntId.isNull() ) return true;
    return false;
  }
};

struct ExGsVisualizeGeometryEntityDef
{
  OdTvGeometryDataId subEntityId;
  bool               traitsValid;
  OdGiSubEntityTraitsData traits;
  bool               byTransform;
  ExGsVisualizeTvEntityId parentEntityId;

  ExGsVisualizeGeometryEntityDef( OdTvGeometryDataId id, bool tv, const OdGiSubEntityTraitsData& data = OdGiSubEntityTraitsData(), bool bTr = false, ExGsVisualizeTvEntityId parentId = ExGsVisualizeTvEntityId() )
  {
    subEntityId = id;
    traitsValid = tv;
    traits = data;
    byTransform = bTr;
    parentEntityId = parentId;
  }

  ExGsVisualizeGeometryEntityDef()
  {
  }
};

class ExGsVisualizeTimer
{
public:
  ExGsVisualizeTimer( bool bTiming );
  ~ExGsVisualizeTimer();

  void start();
  void stop();
  void reset();

  double time() const;

protected:
   OdPerfTimerBase* m_pTimer;
   double m_dElapsed;
   OdUInt32 m_nStarts;
};

class ExGsVisualizeTiming
{
public:
  ExGsVisualizeTiming( ExGsVisualizeTimer* );
  ~ExGsVisualizeTiming();
protected:
  ExGsVisualizeTimer* m_pTimer;
};

typedef OdStack< ExGsVisualizeGeometryEntityDef > OdVisualizeEntityStack;

class ExGsVisualizeGeometry : public OdGiGeometrySimplifier
{
public:
  ExGsVisualizeGeometry( ExGsVisualizeVectorizer* );
  virtual ~ExGsVisualizeGeometry();
//geometry
  virtual void polylineProc(OdInt32 /*nbPoints*/, const OdGePoint3d* /*pVertexList*/,
              const OdGeVector3d* /*pNormal*/,
              const OdGeVector3d* /*pExtrusion*/, OdGsMarker /*lBaseSubEntMarker*/);
  virtual void circleProc(
    const OdGePoint3d& center, double radius,
    const OdGeVector3d& normal,
    const OdGeVector3d* pExtrusion = 0);
  
  virtual void circleProc(
    const OdGePoint3d& firstPoint, const OdGePoint3d& secondPoint, const OdGePoint3d& thirdPoint,
    const OdGeVector3d* pExtrusion = 0);

  virtual void circularArcProc(
    const OdGePoint3d& center,
    double radius,
    const OdGeVector3d& normal,
    const OdGeVector3d& startVector,
    double sweepAngle,
    OdGiArcType arcType = kOdGiArcSimple,
    const OdGeVector3d* pExtrusion = 0);
  
  virtual void circularArcProc(
    const OdGePoint3d& firstPoint,
    const OdGePoint3d& secondPoint,
    const OdGePoint3d& thirdPoint,
    OdGiArcType arcType = kOdGiArcSimple,
    const OdGeVector3d* pExtrusion = 0);
  
  virtual void polygonProc(
    OdInt32 numPoints, const OdGePoint3d* vertexList,
    const OdGeVector3d* pNormal = 0, const OdGeVector3d* pExtrusion = 0);

  virtual void meshProc(
    OdInt32 rows,
    OdInt32 columns,
    const OdGePoint3d* vertexList,
    const OdGiEdgeData* pEdgeData = 0,
    const OdGiFaceData* pFaceData = 0,
    const OdGiVertexData* pVertexData = 0);
  
  virtual void shellProc(
    OdInt32 numVertices,
    const OdGePoint3d* vertexList,
    OdInt32 faceListSize,
    const OdInt32* faceList,
    const OdGiEdgeData* pEdgeData = 0,
    const OdGiFaceData* pFaceData = 0,
    const OdGiVertexData* pVertexData = 0);

  virtual void textProc(
    const OdGePoint3d& position,
    const OdGeVector3d& direction, const OdGeVector3d& upVector,
    const OdChar* msg, OdInt32 numChars, bool raw, const OdGiTextStyle* pTextStyle,
    const OdGeVector3d* pExtrusion = 0);
  
  virtual void shapeProc(
    const OdGePoint3d& position,
    const OdGeVector3d& direction, const OdGeVector3d& upVector,
    int shapeNumber, const OdGiTextStyle* pTextStyle,
    const OdGeVector3d* pExtrusion = 0);

  virtual void xlineProc(
    const OdGePoint3d& firstPoint, const OdGePoint3d& secondPoint);
  
  virtual void rayProc( const OdGePoint3d& basePoint, const OdGePoint3d& throughPoint);
  
  virtual void nurbsProc( const OdGeNurbCurve3d& nurbsCurve);

  virtual void ellipArcProc(
    const OdGeEllipArc3d& ellipArc,
    const OdGePoint3d* endPointsOverrides = 0,
    OdGiArcType arcType = kOdGiArcSimple, const OdGeVector3d* pExtrusion = 0);

  virtual void rasterImageProc(
    const OdGePoint3d& origin,
    const OdGeVector3d& u,
    const OdGeVector3d& v,
    const OdGiRasterImage* pImage, 
    const OdGePoint2d* uvBoundary,
    OdUInt32 numBoundPts,
    bool transparency = false,
    double brightness = 50.0,
    double contrast = 50.0,
    double fade = 0.0);

	virtual void metafileProc(
    const OdGePoint3d& origin,
		const OdGeVector3d& u,
		const OdGeVector3d& v,
    const OdGiMetafile* pMetafile,
    bool dcAligned = true,           
    bool allowClipping = false);

  virtual void polypointProc(
    OdInt32 numPoints,
    const OdGePoint3d* vertexList,
    const OdCmEntityColor* pColors,
    const OdCmTransparency* pTransparency = 0,
    const OdGeVector3d* pNormals = 0,
    const OdGeVector3d* pExtrusions = 0,
    const OdGsMarker* pSubEntMarkers = 0,
    OdInt32 nPointSize = 0);

  virtual void rowOfDotsProc(OdInt32 numPoints, const OdGePoint3d& startPoint, const OdGeVector3d& dirToNextPoint);

  virtual bool brep(const OdGiBrep& brep);

  virtual void edgeProc(const OdGiEdge2dArray& edges, const OdGeMatrix3d* pXform = 0);
  //transform
  virtual void pushModelTransform(const OdGeMatrix3d& xMat);
  virtual void popModelTransform();
  const OdGeMatrix3d& modelTransform() const;
protected:
  OdTvEntityId                             m_tvEntity;
  OdTvEntityPtr                            m_pCurrentTvEntity;
  OdTvEntityId                             m_tvInsert;
  OdTvGeometryDataId                       m_tvSubEntity;
  OdTvModelId                              m_tvModel;
  OdTvDatabaseId                           m_tvDbId;
  OdGiSubEntityTraitsData                  m_curTraits;
  OdUInt8                                  m_flagsEx;
  ExGsVisualizeTvEntityId                  m_parentEntityId;
  ExGsVisualizeVectorizer*                 m_pVectorizer;
  OdVisualizeEntityStack                   m_entStack;
  enum FlagValues
  {
    kTraitsValid = 1,
    kHasSubEntity = 2,
    kHasEntityInInsert = 4,
    kSilentMode = 8,
    kApplyTransform = 16,
    kPolygonProc = 32,
    kByTransformSubEntity = 64,
    kDisableEntityCaching = 128,
    kUseCurrentSubEntity = 256
  };

  class PolygonProcessingHelper
  {
  public:
    PolygonProcessingHelper( ExGsVisualizeGeometry* geom )
    {
      m_pGeom = geom;
      if( !m_pGeom ) return;
      m_bSetFlag = ( geom->m_flagsEx & kPolygonProc ) == 0;
      if( m_bSetFlag )
      {
        SETBIT( m_pGeom->m_flagsEx, kPolygonProc, true );
      }
    }
    ~PolygonProcessingHelper()
    {
      if( m_pGeom )
      {
        if( m_bSetFlag )
        {
          SETBIT( m_pGeom->m_flagsEx, kPolygonProc, false );
        }
      }
    }
  protected:
    bool m_bSetFlag;
    ExGsVisualizeGeometry* m_pGeom;
  };

  OdTvGeometryData::TargetDisplayMode     m_tvTargetDisplayMode;
  void setCurrentTargetDisplayMode( const OdTvGeometryDataId& id );

  bool isTraitsValid() const { return GETBIT( m_flagsEx, kTraitsValid ); }
  void setTraitsValid( bool b ) { SETBIT( m_flagsEx, kTraitsValid, b); }
  void parseDrawFlags( const OdGiSubEntityTraitsData& traits, bool &bFillMode, bool &bSecColor, bool& bDrawEdges );

  bool hasSubEntity() const { return GETBIT( m_flagsEx, kHasSubEntity ); }
  void setHasSubEntity( bool b ) { SETBIT( m_flagsEx, kHasSubEntity, b); }

  bool hasEntityForInsert() const { return GETBIT( m_flagsEx, kHasEntityInInsert ); }
  void setHasEntityForInsert( bool b ) { SETBIT( m_flagsEx, kHasEntityInInsert, b); }

  bool applyTransform() const { return GETBIT( m_flagsEx, kApplyTransform ); }
  void setApplyTransform( bool b ) { SETBIT( m_flagsEx, kApplyTransform, b); }

  bool isByTransformSubEntity() const { return GETBIT( m_flagsEx, kByTransformSubEntity ); }
  void setByTransformSubEntity( bool b ) { SETBIT( m_flagsEx, kByTransformSubEntity, b); } 

  bool isPolygonProc() const { return GETBIT( m_flagsEx, kPolygonProc ); }
  bool forceFill( const OdGiSubEntityTraitsData& traits );
  bool shellAsColoredArea( const OdGiSubEntityTraitsData& traits, bool& bFillIn2D );

  bool isInsertWithoutEntity() const;

  void newSubEntity( bool byTransform = false );
  void rollbackSubEntity( bool byTransform = false );

  bool isUseCurrentSubEntity() const { return GETBIT( m_flagsEx, kUseCurrentSubEntity ); }
  void setUseCurrentSubEntity( bool b ) { SETBIT( m_flagsEx, kUseCurrentSubEntity, b ); }

  void applyTraitsDifference( const OdGiSubEntityTraitsData& effectiveTraits, OdUInt32 diff );


  OdTvMatrix3dStack                        m_modelTransformStack;
  OdTvMatrix3dStack                        m_convolutionMatrixStack;

  ExGsVisualizeDevice* getExGsVisualizeDevice();
  const ExGsVisualizeView*   getExGsVisualizeView();

  struct GeometryState
  {
    OdTvEntityId entityId;
    OdTvEntityId insertId;
    OdTvGeometryDataId subEntityId;
    OdGiSubEntityTraitsData traits;
    OdUInt8 flags;
    ExGsVisualizeTvEntityId parentId;
    OdArray< ExGsVisualizeGeometryEntityDef > entStack;
    OdArray< OdGeMatrix3d > matrixStack;
    OdArray< OdGeMatrix3d > convMatrixStack;
  };

  OdStack< GeometryState > m_stateStack;

  bool isRenderFrontfaceOnly() const;

  OdTvHatchPatternDef getTvHatchPatternDefFromGiHatchPattern(const OdGiHatchPatternPtr& pPtrn);
public:

  bool isSilentMode() const { return GETBIT( m_flagsEx, kSilentMode ); }
  void setSilentMode( bool b ) { SETBIT( m_flagsEx, kSilentMode, b); }

  void setTvEntity( OdTvEntityId entityId, bool forInsert = false );
  OdTvEntityId getTvEntityId() const { return m_tvEntity; }
  OdTvEntityPtr getCurrentEntityPtr( OdTv::OpenMode mode = OdTv::kForRead );
  void setTvInsert( OdTvEntityId entityId ) { m_tvInsert = entityId; }
  OdTvEntityId getTvInsertId() const { return m_tvInsert; }
  bool hasCurrentEntity() const;

  void setTvModel( OdTvModelId id );
  OdTvModelId getTvModelId() const { return m_tvModel; }
  void setTvDatabaseId( OdTvDatabaseId id ) { m_tvDbId = id; }
  OdTvDatabaseId getTvDatabaseId() const { return m_tvDbId; }
  void applyEffectiveTraits( const OdGiSubEntityTraitsData& effectiveTraits );

  void applyEffectiveTraitsToInsert( const OdGiSubEntityTraitsData& effectiveTraits, OdGeMatrix3d* pCustomTransform = NULL );
  void applyClipBoundaryToInsert( OdGiClipBoundary* pBoundary, OdGiAbstractClipBoundary* pAbsBoundary );

  OdVisualizeEntityStack& subEntityStack() { return m_entStack; }

  void pushState();
  void popState();

  void setDrawableId( const OdTvRegAppId&, OdDbStub* );

  OdTvGeometryData::TargetDisplayMode targetDisplayMode() const { return m_tvTargetDisplayMode; }
  void setTargetDisplayMode( OdTvGeometryData::TargetDisplayMode mode );

  bool getDisableEntityCaching() const { return m_bDisableEntityCaching; } 
  void setDisableEntityCaching( bool b ) { m_bDisableEntityCaching = b; }

protected:
  ExGsVisualizeTimer* m_pTimer;
  bool m_bDisableEntityCaching;
public:
  void setTimer( ExGsVisualizeTimer* timer )
  {
    m_pTimer = timer;
  }
  void resetApplyTransform() { setApplyTransform( false ); }
};

OdTvColorDef fromDbColor( const OdCmEntityColor& dbColor, ExGsVisualizeDevice* pDevice );
OdTvTransparencyDef fromCmTransparency(const OdCmTransparency& transparency);
OdTvLineWeightDef fromDbLineWeight(const OdDb::LineWeight& dbLw);

typedef OdSharedPtr<ExGsVisualizeGeometry> ExGsVisualizeGeometryPtr;

OdTvMapperDef::Projection fromGiMapperProjection( const OdGiMapper::Projection& p );
OdTvMapperDef::AutoTransform fromGiMapperAutoTransform( const OdGiMapper::AutoTransform& a );

#include "TD_PackPop.h"

#endif // __OD_GS_VISUALIZE_GEOMETRY__
