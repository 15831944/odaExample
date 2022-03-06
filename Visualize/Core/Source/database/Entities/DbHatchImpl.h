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


#define DEFAULT_MAXHATCHDENSITY 100000 // value from ARX help

class OdGeSegmentChain2d;
class OdGeCurve2d;
class OdTvDbContextDataSubManager;
struct LoopListCustom;

struct SegmentDescription : OdSiEntity
{
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

class DBENT_EXPORT OdTvDbHatchImpl : public OdTvDbEntityImpl
{
public:
  
  enum GradientType
  {
    GR_INVALID = 0,
    GR_SPHERE,
    GR_HEMISPHERE, 
    GR_CURVED,
    GR_LINEAR,
    GR_CYLINDER
  };

  struct EdgeData
  {
    OdTvDbObjectId id;                        // id of according entity
    bool bTextBox;                          // is this textbox contour
  };

  static OdTvDbHatchImpl* getImpl(const OdTvDbHatch *pObj)
  { return (OdTvDbHatchImpl*)OdTvDbSystemInternals::getImpl(pObj);}

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
      m_Flags = OdTvDbHatch::kDefault; // prevent UMR
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
    Loop() : m_Flags(OdTvDbHatch::kDefault), m_bAnnotativeMpolygonLoop(false), m_bUnknownMpolygonVar(false){}

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
      SETBIT(m_Flags, OdTvDbHatch::kPolyline, bPolyline);
    }
    inline bool isPolyline() const
    {
      return GETBIT(m_Flags, OdTvDbHatch::kPolyline);
    }

    inline void setDerived(bool value)
    {
      SETBIT(m_Flags, OdTvDbHatch::kDerived, value);
    }
    inline bool isDerived() const
    {
      return GETBIT(m_Flags, OdTvDbHatch::kDerived);
    }

    inline void setTextBox(bool value)
    {
      SETBIT(m_Flags, OdTvDbHatch::kTextbox, value);
    }
    inline bool isTextBox() const
    {
      return GETBIT(m_Flags, OdTvDbHatch::kTextbox);
    }

    inline void setOuterMost(bool value)
    {
      SETBIT(m_Flags, OdTvDbHatch::kOutermost, value);
    }
    inline bool isOuterMost() const
    {
      return GETBIT(m_Flags, OdTvDbHatch::kOutermost);
    }

    inline void setNotClosed(bool value)
    {
      SETBIT(m_Flags, OdTvDbHatch::kNotClosed, value);
    }
    inline bool isNotClosed() const
    {
      return GETBIT(m_Flags, OdTvDbHatch::kNotClosed);
    }

    inline void setDuplicate(bool value)
    {
      SETBIT(m_Flags, OdTvDbHatch::kDuplicate, value);
    }
    inline bool isDuplicate() const
    {
      return GETBIT(m_Flags, OdTvDbHatch::kDuplicate);
    }

    inline bool isTextIsland() const
    {
      return GETBIT(m_Flags, OdTvDbHatch::kTextIsland);
    }

    inline bool isAnnotative() const
    {
      return GETBIT(m_Flags, OdTvDbHatch::kIsAnnotative);
    }

    OdSoftPtrIdArray& sourceEntIds() { return m_SourceEntIds; }
    const OdSoftPtrIdArray& getSourceEntIds() const { return m_SourceEntIds; }
    void setFromIds(const OdTvDbObjectIdArray& dbObjIds, const OdGePlane& hatchPlane, 
      OdInt32 loopType, bool bAssociative, OdTvDbObjectId hatchId, bool bIsSolidFill );
    void orderToBeClosed();
    void transformBy(const OdGeMatrix2d& xform, bool bNoPolylines = false);
    OdResult dwgInFields(OdTvDbDwgFiler* pFiler, bool bReadPolylines = true);
    void dwgOutFields(OdTvDbDwgFiler* pFiler, bool bWritePolylines = true) const;
    bool setFromIdsProjected(const OdSoftPtrIdArray& dbObjIds, const OdGePlane& hatchPlane, const OdInt32 loopType);
  };
  Loop& operator=(const Loop& src);

  typedef OdArray<Loop>       LoopList;
  typedef std::multimap<OdUInt32, OdUInt32> OrderedLoopStorage;
  typedef std::set<OdUInt16> ModifiedLoopList;

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
  double                      m_dPixelSize;
  OdGePoint2dArray            m_SeedPoints;
  OdTvDbHatch::HatchStyle       m_Style;
  OdTvDbHatch::HatchPatternType m_PatternType;
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
  OdTvDbHatchImpl() :
    m_Normal(OdGeVector3d::kZAxis),
    m_dElevation(0.),
    m_bAssociative(true),
    m_bSolidFill(false),
    m_bGradientFill(false),
    m_bDoubleHatch(false),
    m_Style(OdTvDbHatch::kNormal),
    m_PatternType(OdTvDbHatch::kUserDefined),
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
    m_originPointModified(false)
    {
      createContextDataManager();
    }

  ~OdTvDbHatchImpl();

  // Database converting functions
  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave (OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  
  // decomposes for save hatch data only.
  // doesn't call OdTvDbEntity::decomposeForSave 
  // is NOT called by framework.
  OdTvDbObjectPtr decomposeForSaveHatchDataOnly(OdTvDbObject *pObj, OdDb::DwgVersion version);
  
  
  void composeForLoad   (OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  bool prepareFromBlkRef(OdTvResBufPtr pXdata, OdTvDbBlockReferencePtr pObj);

  void audit (OdTvDbAuditInfo* pAuditInfo);
  OdResult checkForHatchPattern(OdTvDbHostAppServices  *pService);

  /** Transforms hatch data by the specified matrix.
  */
  virtual OdResult transformBy(const OdGeMatrix3d& xform);

  OdHatchPattern& hatchPattern();
  const OdHatchPattern& getHatchPattern(bool forceReload = false);//SRC-815

  // Builds the graphics representation of the hatch
  OdResult evaluateHatch(OdUInt32 maxHatchDensity, OdTvDbHatchScaleContextDataPtr ctx, double viewRotation, const bool& isEvaluateHatchArea = false) const;
  
  OdResult evaluateHatchArea(double& area) const;

  void checkDenstiy(const OdGeLineSeg2dArray& segmentArray, const OdHatchPattern &hp, const OdGeExtents2d &ext, const OdUInt32& maxHatchDensity, bool &bHatchTooDense) const;

  /** This method provides a way to evaluate the interpolated color that the current 
      gradient definition and colors will produce at a specified location along 
      the gradient. The point of evaluation is indicated by the argument value.
  */
  OdCmEntityColor evaluateGradientColorAt(double value) const;

  /** Internal method. Evaluating constants to use with inline internal member
  */
  void evaluateGradColConsts(int& r1, int& g1, int& b1, int& r2, int& g2, int& b2) const;

  /** Gets the value of gradient in specified point "gradPoint".
      (minPoint, maxPoint) - extents
  */
  double getGradientVal(const OdGePoint2d& minPoint, const OdGePoint2d& maxPoint, 
    const OdGePoint2d& gradPointTaken, GradientType gradType, bool toInvert) const;

  void getGradientType(GradientType& gradType, bool& gradToInvert) const;

  OdTvDbRegionPtr getRegionArea() const;
  // Override OdTvDbEntityImpl
  //
  void createGrData(const OdTvDbEntity* pEnt, OdBinaryData& data, OdDb::DwgVersion ver);

  // Tries to make loops closed. Throws exception if operation is unsuccessful
  void tryCloseLoops();

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }
  void regeneratePattern(bool forceReload = true);//SRC-815

  OdGePoint2d originPoint() const;
  void setPattern(OdTvDbHatch::HatchPatternType patType, const OdString& patName);
  void setPatternAngle(double angle, OdTvDbObject* pThis);
  void setPatternSpace(double space, OdTvDbObject* pThis);
  void setPatternScale(double scale, OdTvDbObject* pThis);
  void setPatternDouble(bool isDouble, OdTvDbObject* pThis);
  void getPatternDefinitionAt(int index, double& angle, double& baseX,
    double& baseY, double& offsetX, double& offsetY, OdGeDoubleArray& dashes);
  void setGradientColors(OdUInt32 count, const OdTvCmColor* colors, const double* values, OdTvDbObject* pThis);
  void dxfInBoundary(OdTvDbDxfFiler* pFiler, LoopList& loopList);
  void dxfOutGradient(OdTvDbDxfFiler* pFiler, bool mpoly = false) const;

  static OdResult dxfInFields(OdTvDbDxfFiler& pFiler, OdHatchPattern& pat);
  static void dxfOutFields(OdTvDbDxfFiler& pFiler, const OdHatchPattern& pat);
  static OdResult dwgInFields(OdTvDbDwgFiler& pFiler, OdHatchPattern& pat);
  static void dwgOutFields(OdTvDbDwgFiler& pFiler, const OdHatchPattern& pat);
  
  virtual void copyFromContextData(OdTvDbObject*,OdTvDbObjectContextData*, OdTvDbObjectContextData*) ODRX_OVERRIDE;
  void appendLoop(OdInt32 loopType, const OdGePoint2dArray& vertices, const OdGeDoubleArray& bulges, OdTvDbHatchImpl::LoopList& loopList) const;
  void insertLoopAt(int loopIndex, OdInt32 loopType, const OdGePoint2dArray& vertices, const OdGeDoubleArray& bulges, LoopList& loopList) const;
  double getDeviation(OdGiCommonDraw* pWd, OdGiGeometry &geom) const;
private:
  // Must be accessed using getPattern
  mutable OdHatchPattern m_HatchDefLineList;

  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  // virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbHatchScaleContextData *ctx = NULL);

  // void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbHatchScaleContextData *ctx = NULL) const;

  void assurePatDataConsistence(OdTvDbFiler* pFiler);
  void fillSegmentLoopLtArrays(OdTvDbHatchScaleContextData* ctx, OdGeLineSeg2dArray& segmentArray,
                               OdIntArray& loopArray, OdIntArray& loopTypes, LoopList* loopsOverride = 0, const LoopListCustom* loopListCustom = 0,
                               const bool& isEvaluateHatchArea = false, const bool& isRegionCreate = false) const;
  
  OdUInt32 fillSegmentLoopLtArrays(OdGeLineSeg2dArrayArray& segmentArray) const;
  void draw(OdGiCommonDraw* pWd, OdGiGeometry& geom, const OdTvDbHatch* pObj, bool bAnnotative = true);

  void removeAssocObjIds();
  
  bool processGradientHatch() const;
  OdTvCmColor backgroundColor() const;
  void setBackgroundColor(const OdTvCmColor& color);
  bool hatchTooDense(OdGiCommonDraw* pWd, OdGiGeometry& geom) const;
  bool drawBoundaryForClipping(OdGiCommonDraw* pWd, const OdTvDbHatch* pObj);
  OdGeMatrix3d ecs2Wcs() const;
  void clearCache(OdTvDbHatchScaleContextData* ctx);
  void propagateContextPattern();
  void propagateContextPatternRotation(double r);
  void buildGradientMesh(GradientType gradType, bool gradToInvert, const OdGeExtents2d& ocsExt, OdGeShellData& gradientMesh) const;
  void clipGradienMesh(const OdGeShellData& gradientMesh) const;
  
  OdTvDbContextDataSubManager* createContextDataForLoops(OdTvDbHatch* pThis);
  void updateAnnotativeLoops(OdTvDbHatch* pThis);
  void findAssociativeLoop(OdTvDbHatch* pThis, const OdDbHandle pObjHandle);
  bool updateAssociativeLoops(OdTvDbHatch* pThis);
  bool loopsAreClosedAndNotIntesecting(const OdGeLineSeg2dArray& segmentArray, const OdIntArray& loopArray, bool& intersecting, const LoopList* loopsOverride, 
                                       std::map<OdUInt32, LoopDescription>& loopDesc, const double& areaDeviation) const;
  double calculateAreaDeviation(const OdTvDbHatchImpl::LoopList& loops, const OdTvDbHatchImpl::LoopList* otherLoopList = 0) const;
  bool boundaryNeedsReordering(const OdTvDbHatchImpl::LoopList& loops, const double& tol) const;
  bool reorderLoops(const OdTvDbHatchImpl::LoopList& loops, OdTvDbHatchImpl::LoopList& orderedLoops, const double& tol) const;
  void removeZeroLengthSegments(OdGeLineSeg2dArray& segmentArray, OdIntArray& loopArray) const;
  bool calculateLoopSign(const OdGeLineSeg2dArray& segmentArray, const OdIntArray& loopArray, const OdIntArray&loopTypes, OdTvDbHatch::HatchStyle style, const OdInt32& loop, bool& hole,
                         const std::map<OdUInt32, LoopDescription>& loopsDesc, const OdGeTol& tol = OdGeContext::gTol, OdUInt32* pOuterLoops = 0) const;
  bool findLoopRelation(const OdGeLineSeg2dArray& segmentArray, const OdIntArray& loopArray, const OdIntArray& loopTypes, OdTvDbHatch::HatchStyle style, OdUInt32 loop, bool& insideTextLoop,
                        const std::map<OdUInt32, LoopDescription>& loopsDesc, OdArray<OdArray<OdInt32> >& relationLoopsArr, std::multimap<OdUInt32, OdUInt32>& equalLoopsArr, const bool& bFindLoop = false) const;

  friend class OdTvDbHatch;
  friend class OdTvDbBlockReferenceImpl;
  friend class OdTvDbHatchWatcherPE;
  friend class OdTvDbMPolygonImpl;
  friend class OdTvDbHatchScaleContextData;
};

inline void clearStrokeCache(OdTvDbHatchImpl * pImpl)
{
  pImpl->m_startPts.clear();
  pImpl->m_endPts.clear();
  pImpl->m_pShell = (OdSharedPtr<OdGeShellData>)0;
  pImpl->m_bCacheValid = false;
}

class HatchXDataFiler : public OdRxObjectImpl<OdTvDbDwgFiler>
{
  OdTvResBufPtr m_pRb;
  HatchXDataFiler() { ODA_FAIL(); }
public:
  ODRX_DECLARE_MEMBERS(HatchXDataFiler);
  HatchXDataFiler(OdTvResBufPtr& pRb) : m_pRb(pRb) {}
  OdTvResBufPtr getResBuf() { return m_pRb; }

  void seek(OdInt64, OdDb::FilerSeekType) { ODA_FAIL(); }
  OdUInt64 tell() const { ODA_FAIL(); return 0; }
  FilerType filerType() const { return OdTvDbFiler::kCopyFiler; }

  bool         rdBool();
  OdInt16      rdInt16();
  OdInt32      rdInt32();
  OdInt64      rdInt64();
  OdDbHandle   rdDbHandle();
  OdTvDbObjectId rdSoftOwnershipId();
  OdTvDbObjectId rdHardOwnershipId() { return rdSoftOwnershipId(); }
  OdTvDbObjectId rdHardPointerId() { return rdSoftOwnershipId(); }
  OdTvDbObjectId rdSoftPointerId() { return rdSoftOwnershipId(); }
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
  void wrSoftOwnershipId(const OdTvDbObjectId& id);
  void wrHardOwnershipId(const OdTvDbObjectId& id);
  void wrSoftPointerId(const OdTvDbObjectId& id);
  void wrHardPointerId(const OdTvDbObjectId& id);
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
  const OdTvDbHatchImpl::LoopList* mLoopList;
  LoopListCustom(const OdUInt32 startLoopNumIn, const OdUInt32 countLoopsIn, const OdTvDbHatchImpl::LoopList* pLoopList) 
    : startLoopNum(startLoopNumIn), countLoops(countLoopsIn)
  {
    ODA_ASSERT_ONCE(pLoopList);
    mLoopList = pLoopList;
  }
private:
  LoopListCustom();
};


#endif // _ODDBHATCHIMPL_INCLUDED_
