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

#ifndef _ODDBHATCHIMPL_INCLUDED_
#define _ODDBHATCHIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "IdArrays.h"
#include "DbHatch.h"
#include "Ge/GeSegmentChain2d.h"
#include "DbSystemInternals.h"
#include "HatchPatternManager.h"
#include "Ge/GeLineSeg2dArray.h"
#include "DbBlockReference.h"
#include "CmEntityColorArray.h"
#include "DbObjectContextData.h"

#include "Ge/GeLineSeg2dArrayArray.h"
#include "GeHatch.h"
#include "Si/SiSpatialIndex.h"
#include "Si/SiExtents.h"
#define STL_USING_SET
#include "OdaSTL.h"
#include "UInt32Array.h"


#define DEFAULT_MAXHATCHDENSITY 100000 // value from ARX help

class OdGeSegmentChain2d;
class OdGeCurve2d;
class OdDbContextDataSubManager;
struct LoopListCustom;

struct SegmentDescription : OdSiEntity
{
  SegmentDescription() :segment(0) {};
  virtual ~SegmentDescription() {}
  virtual bool extents(OdGeExtents3d& extents) const ODRX_OVERRIDE
  {
    extents = ext;
    return true;
  }
  int segment;
  OdGeExtents3d ext;
};

struct LoopDescription : OdSiEntity
{
  LoopDescription() :loop(0), area(0.0) {};
  virtual ~LoopDescription() {}
  virtual bool extents(OdGeExtents3d& extents) const ODRX_OVERRIDE
  {
    extents = ext;
    return true;
  }
  int loop;
  OdGeExtents3d ext;
  double area;
};

class DBENT_EXPORT OdDbHatchImpl : public OdDbEntityImpl
{
public:
  

  struct EdgeData
  {
    OdDbObjectId id;                        // id of according entity
    bool bTextBox;                          // is this textbox contour
    EdgeData() :bTextBox(false) {};
  };

  static OdDbHatchImpl* getImpl(const OdDbHatch *pObj)
  { return (OdDbHatchImpl*)OdDbSystemInternals::getImpl(pObj);}

  // The internal representations of hatch boundary edges are GELIB 2D geometry,
  // including OdGeLineSeg2d, OdGeCircArc2d, OdGeEllipArc2d and OdGeNurbCurve2d.
  // If the hatch boundary consists of a polyline, special methods are provided to
  // construct the loop.
  class DBENT_EXPORT Loop
  {
    void clearBoundary();
  
  public:
    Loop& operator=(const Loop& src);

    Loop(const Loop& src)
    {
      m_Flags = OdDbHatch::kDefault; // prevent UMR
      m_bAnnotativeMpolygonLoop = src.m_bAnnotativeMpolygonLoop;
      m_bUnknownMpolygonVar = src.m_bUnknownMpolygonVar;
      *this = src;
    }

    OdSoftPtrIdArray m_SourceEntIds;
    OdUInt32 m_Flags;
    union BOUNDARIES
    {
      EdgeArray*      pSegments;
      OdGeSegmentChain2d* pPolyline;
      BOUNDARIES() : pSegments(0) {}   //NOTE: Only 1 member of a union can be initialized on SGI
    } m_Boundaries;
    bool m_bAnnotativeMpolygonLoop;
    bool m_bUnknownMpolygonVar;

    ~Loop();
    Loop() : m_Flags(OdDbHatch::kDefault), m_bAnnotativeMpolygonLoop(false), m_bUnknownMpolygonVar(false) { }

  public:
    EdgeArray& segments()
    {
      if(isPolyline())
      {
        throw OdError(eInvalidInput); // Invalid loop
      }
      if(!m_Boundaries.pSegments)
      {
        m_Boundaries.pSegments = new EdgeArray;
      }
      return *(m_Boundaries.pSegments);
    }
    void setPolyline(bool bPolyline)
    {
      SETBIT(m_Flags, OdDbHatch::kPolyline, bPolyline);
    }
    inline bool isPolyline() const
    {
      return GETBIT(m_Flags, OdDbHatch::kPolyline);
    }

    inline void setDerived(bool value)
    {
      SETBIT(m_Flags, OdDbHatch::kDerived, value);
    }
    inline bool isDerived() const
    {
      return GETBIT(m_Flags, OdDbHatch::kDerived);
    }

    inline void setTextBox(bool value)
    {
      SETBIT(m_Flags, OdDbHatch::kTextbox, value);
    }
    inline bool isTextBox() const
    {
      return GETBIT(m_Flags, OdDbHatch::kTextbox);
    }

    inline void setOuterMost(bool value)
    {
      SETBIT(m_Flags, OdDbHatch::kOutermost, value);
    }
    inline bool isOuterMost() const
    {
      return GETBIT(m_Flags, OdDbHatch::kOutermost);
    }

    inline void setNotClosed(bool value)
    {
      SETBIT(m_Flags, OdDbHatch::kNotClosed, value);
    }
    inline bool isNotClosed() const
    {
      return GETBIT(m_Flags, OdDbHatch::kNotClosed);
    }

    inline void setDuplicate(bool value)
    {
      SETBIT(m_Flags, OdDbHatch::kDuplicate, value);
    }
    inline bool isDuplicate() const
    {
      return GETBIT(m_Flags, OdDbHatch::kDuplicate);
    }

    inline bool isTextIsland() const
    {
      return GETBIT(m_Flags, OdDbHatch::kTextIsland);
    }

    inline bool isAnnotative() const
    {
      return GETBIT(m_Flags, OdDbHatch::kIsAnnotative);
    }

    OdSoftPtrIdArray& sourceEntIds() { return m_SourceEntIds; }
    const OdSoftPtrIdArray& getSourceEntIds() const { return m_SourceEntIds; }
    void setFromIds(const OdDbObjectIdArray& dbObjIds, const OdGePlane& hatchPlane, 
      OdInt32 loopType, bool bAssociative, OdDbObjectId hatchId, bool bIsSolidFill );
    void orderToBeClosed();
    void transformBy(const OdGeMatrix2d& xform, bool bNoPolylines = false);
    OdResult dwgInFields(OdDbDwgFiler* pFiler, bool bReadPolylines = true);
    void dwgOutFields(OdDbDwgFiler* pFiler, bool bWritePolylines = true) const;
    bool setFromIdsProjected(const OdSoftPtrIdArray& dbObjIds, const OdGePlane& hatchPlane, const OdInt32 loopType, const bool isSolid);
  };
  Loop& operator=(const Loop& src);

  typedef OdArray<Loop>       LoopList;
  typedef std::multimap<OdUInt32, OdUInt32> OrderedLoopStorage;
  typedef std::set<OdUInt16> ModifiedLoopList;
  mutable OdGeExtents3d       m_extents3d;
  OdGeVector3d                m_Normal;
  double                      m_dElevation;
  OdString                    m_strName;
  LoopList                    m_LoopsList;
  ModifiedLoopList            m_modifiedLoopList;
  double                      m_dAngle;
  double                      m_dScaleOrSpacing;
  bool                        m_bAssociative;
  bool                        m_bSolidFill;
  bool                        m_bGradientFill;
  bool                        m_bDoubleHatch;
  bool                        m_originPointModified;
  bool                        m_isMPolygon;
  double                      m_dPixelSize;
  OdGePoint2dArray            m_SeedPoints;
  OdDbHatch::HatchStyle       m_Style;
  OdDbHatch::HatchPatternType m_PatternType;
  // The cache of the hatch geometry
  
  // GU it is not very good that there are too much mutable data
  // need to truncate its size in some way (todo)

  mutable OdGePoint2dArray    m_startPts;
  mutable OdGePoint2dArray    m_endPts;
  mutable OdSharedPtr<OdGeShellData> m_pShell;
  mutable double              m_dDeviation; // Hmm...
  mutable double              m_dDeviationNonClosedHatch;
  mutable bool                m_bCacheValid;
  mutable bool                m_bHatchTooDense;
  
  // gradient hatch data (probably should be moved to separate structure)
  bool                        m_bSingColGrad;
  double                      m_dShift;
  double                      m_dColorTint;
  OdString                    m_gradName;
  OdCmColorArray              m_gradColors;
  OdGeDoubleArray             m_gradValues;

  // MPolygon may contain offset vector
  OdGeVector2d m_vOffset;

public:
  OdDbHatchImpl() :
    m_Normal(OdGeVector3d::kZAxis),
    m_dElevation(0.),
    m_bAssociative(true),
    m_bSolidFill(false),
    m_bGradientFill(false),
    m_bDoubleHatch(false),
    m_Style(OdDbHatch::kNormal),
    m_PatternType(OdDbHatch::kUserDefined),
    m_dAngle(0.0),
    m_dScaleOrSpacing(1.0),
    m_dPixelSize(0.0),
    m_dDeviation(0.0),
    m_dDeviationNonClosedHatch(0.0),

    // gradient hatch data (probably should be moved to separate structure)
    m_bSingColGrad(true),
    m_dShift(0.0),
    m_dColorTint(0.0),
    m_bCacheValid(false),
    m_bHatchTooDense(false),
    m_originPointModified(false),
    m_isMPolygon(false)
    {
      createContextDataManager();
    }

  ~OdDbHatchImpl();

  // Database converting functions
  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave (OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  
  // decomposes for save hatch data only.
  // doesn't call OdDbEntity::decomposeForSave 
  // is NOT called by framework.
  OdDbObjectPtr decomposeForSaveHatchDataOnly(OdDbObject *pObj, OdDb::DwgVersion version);
  
  
  void composeForLoad   (OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  bool prepareFromBlkRef(OdResBufPtr pXdata, OdDbBlockReferencePtr pObj);

  void audit (OdDbAuditInfo* pAuditInfo);
  OdResult checkForHatchPattern(OdDbHostAppServices  *pService);

  /** Transforms hatch data by the specified matrix.
  */
  virtual OdResult transformBy(const OdGeMatrix3d& xform);

  OdHatchPattern& hatchPattern();
  const OdHatchPattern& getHatchPattern(bool forceReload = false);//SRC-815

  // Builds the graphics representation of the hatch
  OdResult evaluateHatch(OdGiSubEntityTraits* pTraits, OdGiGeometry* geom, OdUInt32 maxHatchDensity, OdDbHatchScaleContextDataPtr ctx, double viewRotation, const bool isEvaluateHatchArea = false, const bool bNewGiEvaluate = true) const;
  
  void evaluateNonSolidHatchGi(OdGeLineSeg2dArray& segmentArray, OdIntArray& loopArray, OdIntArray& loopTypes, OdGeTol& hatchTolerance, OdGiGeometry*const geom, OdGiSubEntityTraits*const pTraits, const OdDbHatchScaleContextDataPtr &ctx,
                                                                                                       const LoopListCustom& loopListCustom, const OdUInt32 maxHatchDensity, const double viewRotation) const;
  OdResult evaluateHatchArea(double& area) const;

  bool checkDenstiy(const OdGeLineSeg2dArray& segmentArray, const OdIntArray& loopArray, const OdHatchPattern &hp, const OdUInt32& maxHatchDensity, bool &bHatchTooDense) const;

  /** This method provides a way to evaluate the interpolated color that the current 
      gradient definition and colors will produce at a specified location along 
      the gradient. The point of evaluation is indicated by the argument value.
  */
  OdCmEntityColor evaluateGradientColorAt(double value) const;

  /** Internal method. Evaluating constants to use with inline internal member
  */
  void evaluateGradColConsts(int& r1, int& g1, int& b1, int& r2, int& g2, int& b2) const;

  OdDbRegionPtr getRegionArea() const;
  // Override OdDbEntityImpl
  //
  void createGrData(const OdDbEntity* pEnt, OdBinaryData& data, OdDb::DwgVersion ver);

  // Tries to make loops closed. Throws exception if operation is unsuccessful
  void tryCloseLoops();

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }
  void regeneratePattern(bool forceReload = true);//SRC-815

  OdGePoint2d originPoint() const;
  void setPattern(OdDbHatch::HatchPatternType patType, const OdString& patName);
  void setPatternAngle(double angle, OdDbObject* pThis);
  void setPatternSpace(double space, OdDbObject* pThis);
  void setPatternScale(double scale, OdDbObject* pThis);
  void setPatternDouble(bool isDouble, OdDbObject* pThis);
  void getPatternDefinitionAt(int index, double& angle, double& baseX,
    double& baseY, double& offsetX, double& offsetY, OdGeDoubleArray& dashes);
  void setGradientColors(OdUInt32 count, const OdCmColor* colors, const double* values, OdDbObject* pThis);
  void dxfInBoundary(OdDbDxfFiler* pFiler, LoopList& loopList);
  void dxfOutGradient(OdDbDxfFiler* pFiler, bool mpoly = false) const;

  static OdResult dxfInFields(OdDbDxfFiler& pFiler, OdHatchPattern& pat);
  static void dxfOutFields(OdDbDxfFiler& pFiler, const OdHatchPattern& pat);
  static OdResult dwgInFields(OdDbDwgFiler& pFiler, OdHatchPattern& pat);
  static void dwgOutFields(OdDbDwgFiler& pFiler, const OdHatchPattern& pat);
  
  virtual void copyFromContextData(OdDbObject*,OdDbObjectContextData*, OdDbObjectContextData*) ODRX_OVERRIDE;
  void appendLoop(OdInt32 loopType, const OdGePoint2dArray& vertices, const OdGeDoubleArray& bulges, OdDbHatchImpl::LoopList& loopList) const;
  void insertLoopAt(int loopIndex, OdInt32 loopType, const OdGePoint2dArray& vertices, const OdGeDoubleArray& bulges, LoopList& loopList) const;
  double getDeviation(OdGiCommonDraw* pWd, OdGiGeometry &geom) const;
  void fillGiLoopListCustom(OdDbHatchScaleContextData* ctx, GiLoopListCustom& edgeArray2d, const LoopListCustom& loopListCustom) const;
  void fillGiEdge(const OdDbHatchScaleContextData *const ctx, OdGiEdge2dArray & edgeArray2d, OdUInt32Array & loopsFlags, OdUInt32Array& loopsMerker, const LoopListCustom & loopListCustom) const;
private:
  // Must be accessed using getPattern
  mutable OdHatchPattern m_HatchDefLineList;

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  // virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler, OdDbHatchScaleContextData *ctx = NULL);

  // void dxfOutFields(OdDbDxfFiler* pFiler) const;
  void dxfOutFields(OdDbDxfFiler* pFiler, OdDbHatchScaleContextData *ctx = NULL) const;

  void assurePatDataConsistence(OdDbFiler* pFiler);

  
  OdUInt32 fillSegmentLoopLtArrays(OdGeLineSeg2dArrayArray& segmentArray) const;
  void draw(OdGiCommonDraw* pWd, OdGiGeometry& geom, const OdDbHatch* pObj, bool bAnnotative = true);

  void removeAssocObjIds();
  
  bool processGradientHatch() const;
  OdCmColor backgroundColor() const;
  void setBackgroundColor(const OdCmColor& color);
  bool hatchTooDense(OdGiCommonDraw* pWd, OdGiGeometry& geom) const;
  bool drawBoundaryForClipping(OdGiCommonDraw* pWd, const OdDbHatch* pObj);
  OdGeMatrix3d ecs2Wcs(const OdGeVector2d& vOffset = OdGeVector2d()) const;
  void clearCache(OdDbHatchScaleContextData* ctx);
  bool isCacheEmpty(OdDbHatchScaleContextData* ctx);
  void propagateContextPattern();
  void propagateContextPatternRotation(double r);
  
  OdDbContextDataSubManager* createContextDataForLoops(OdDbHatch* pThis);
  void updateAnnotativeLoops(OdDbHatch* pThis);
  void findAssociativeLoop(OdDbHatch* pThis, const OdDbHandle pObjHandle);
  bool updateAssociativeLoops(OdDbHatch* pThis);
  bool loopsAreClosedAndNotIntesecting(const OdGeLineSeg2dArray& segmentArray, const OdIntArray& loopArray, bool& intersecting, const LoopList* loopsOverride, 
                                       std::map<OdUInt32, LoopDescription>& loopDesc, const double& areaDeviation) const;
  double calculateAreaDeviation(const OdDbHatchImpl::LoopList& loops, const OdDbHatchImpl::LoopList* otherLoopList = 0) const;
  bool boundaryNeedsReordering(const OdDbHatchImpl::LoopList& loops, const double& tol) const;
  bool reorderLoops(const OdDbHatchImpl::LoopList& loops, OdDbHatchImpl::LoopList& orderedLoops, const double& tol) const;
  void removeZeroLengthSegments(OdGeLineSeg2dArray& segmentArray, OdIntArray& loopArray) const;
  bool calculateLoopSign(const OdGeLineSeg2dArray& segmentArray, const OdIntArray& loopArray, const OdIntArray&loopTypes, OdDbHatch::HatchStyle style, const OdInt32& loop, bool& hole,
                         const std::map<OdUInt32, LoopDescription>& loopsDesc, const OdGeTol& tol = OdGeContext::gTol, OdUInt32* pOuterLoops = 0) const;
  bool findLoopRelation(const OdGeLineSeg2dArray& segmentArray, const OdIntArray& loopArray, const OdIntArray& loopTypes, OdDbHatch::HatchStyle style, OdUInt32 loop, bool& insideTextLoop,
                        const std::map<OdUInt32, LoopDescription>& loopsDesc, OdArray<OdArray<OdInt32> >& relationLoopsArr, std::multimap<OdUInt32, OdUInt32>& equalLoopsArr, const bool& bFindLoop = false) const;

  friend class OdDbHatch;
  friend class OdDbBlockReferenceImpl;
  friend class OdDbHatchWatcherPE;
  friend class OdDbMPolygonImpl;
  friend class OdDbHatchScaleContextData;
};

//clearStrokeCache used in pattern properties setters
inline void clearStrokeCache(OdDbHatchImpl * pImpl)
{
  pImpl->m_startPts.clear();
  pImpl->m_endPts.clear();
  pImpl->m_pShell = (OdSharedPtr<OdGeShellData>)0;
  pImpl->m_bCacheValid = false;
  pImpl->m_bHatchTooDense = false;//reset flag HatchTooDense in pattern properties setters
}

class HatchXDataFiler : public OdRxObjectImpl<OdDbDwgFiler>
{
  OdResBufPtr m_pRb;
  HatchXDataFiler() { ODA_FAIL(); }
public:
  ODRX_DECLARE_MEMBERS(HatchXDataFiler);
  HatchXDataFiler(OdResBufPtr& pRb) : m_pRb(pRb) {}
  OdResBufPtr getResBuf() { return m_pRb; }

  void seek(OdInt64, OdDb::FilerSeekType) { ODA_FAIL(); }
  OdUInt64 tell() const { ODA_FAIL(); return 0; }
  FilerType filerType() const { return OdDbFiler::kCopyFiler; }

  bool         rdBool();
  OdInt16      rdInt16();
  OdInt32      rdInt32();
  OdInt64      rdInt64();
  OdDbHandle   rdDbHandle();
  OdDbObjectId rdSoftOwnershipId();
  OdDbObjectId rdHardOwnershipId() { return rdSoftOwnershipId(); }
  OdDbObjectId rdHardPointerId() { return rdSoftOwnershipId(); }
  OdDbObjectId rdSoftPointerId() { return rdSoftOwnershipId(); }
  double       rdDouble();
  OdGePoint2d  rdPoint2d();
  OdGePoint3d  rdPoint3d();
  OdGeVector2d rdVector2d();
  OdGeVector3d rdVector3d();
  OdGeScale3d  rdScale3d();
  OdInt8       rdInt8() { ODA_FAIL(); return 0; }
  OdUInt8      rdUInt8() { return rdInt8(); }
  void         rdString(OdString &) { ODA_FAIL(); }
  OdString     rdString() { ODA_FAIL(); return OdString::kEmpty; }
  void         rdBytes(void*, OdUInt32) { ODA_FAIL(); }

  void wrBool(bool b);
  void wrInt16(OdInt16 val);
  void wrInt32(OdInt32 val);
  void wrInt64(OdInt64 val);
  void wrDouble(double val);
  void wrDbHandle(const OdDbHandle& val);
  void wrSoftOwnershipId(const OdDbObjectId& id);
  void wrHardOwnershipId(const OdDbObjectId& id);
  void wrSoftPointerId(const OdDbObjectId& id);
  void wrHardPointerId(const OdDbObjectId& id);
  void wrPoint2d(const OdGePoint2d& pt);
  void wrPoint3d(const OdGePoint3d& pt);
  void wrVector2d(const OdGeVector2d& vec);
  void wrVector3d(const OdGeVector3d& vec);
  void wrInt8(OdInt8) { ODA_FAIL(); }
  void wrUInt8(OdUInt8 val) { wrInt8(val); }
  void wrScale3d(const OdGeScale3d&) { ODA_FAIL(); }
  void wrString(const OdString&) { ODA_FAIL(); }
  void wrBytes(const void*, OdUInt32) { ODA_FAIL(); }
};

enum LoopTypeDetection
{
  kHole = 1,
  kIsland = 2,
  kOuter = 4,
  kExclusion = 8,
  kExclusionHole = 9,
  kExclusionIsland = 10,
  kExclusionOuter = 12
};

struct LoopListCustom
{//this struct using to get segments by fillSegmentLoopLtArrays for two loopList.
  //fillSegmentLoopLtArrays will call twice and second time segmentsArray will be continue to fill (we will get one big segment array from two loopList)
  const OdUInt32 startLoopNum;//startLoopNum == otherLoopList.size()
  const OdUInt32 countLoops;//mLoopList.size() + otherLoopList.size()
  const OdDbHatchImpl::LoopList* mLoopList;
  LoopListCustom(const OdUInt32 startLoopNumIn, const OdUInt32 countLoopsIn, const OdDbHatchImpl::LoopList* pLoopList) 
    : startLoopNum(startLoopNumIn), countLoops(countLoopsIn)
  {
    ODA_ASSERT_ONCE(pLoopList);
    mLoopList = pLoopList;
  }
private:
  LoopListCustom();
};

#endif // _ODDBHATCHIMPL_INCLUDED_
