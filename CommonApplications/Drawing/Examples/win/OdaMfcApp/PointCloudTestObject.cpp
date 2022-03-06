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
// Point Cloud test object and Point Cloud test object command

#include "OdaCommon.h"
#include "DbDatabase.h"
#include "DbEntity.h"
#include "DbFiler.h"
#include "DbProxyEntity.h"
#include "DbBlockTableRecord.h"
#include "DbCommandContext.h"
#include "Ed/EdCommandStack.h"
#include "Ge/GeScale3d.h"
#include "Gi/GiWorldDraw.h"
#include "Gi/GiViewport.h"
#if 1
#include "Gi/GiPointCloud.h"

/* -------------------------------------------------------------------------------------- */
/* Abstraction layer for communication with database entity                               */
/* -------------------------------------------------------------------------------------- */
class ExPointCloudCom
{
  public:
    virtual OdUInt32 minDensity() const = 0;
    virtual OdUInt32 maxDensity() const = 0;
    virtual OdUInt32 numLODs() const = 0;
    virtual OdUInt32 componentsMask() const = 0;
};

/* -------------------------------------------------------------------------------------- */
/* Implementation of Point Cloud testing data                                             */
/* -------------------------------------------------------------------------------------- */

#define GEN_FP_DATA
//#define SUPPORT_PARTIAL_UPDATE

class ExPointCloudImpl : public OdStaticRxObject<OdGiPointCloud>
{
  protected:
    const ExPointCloudCom *m_pCom;
    mutable struct BoxSide
    { enum Flags { kVisible = 1 };
      OdUInt32 m_numLOD, m_nFlags;
      OdArray<OdGiPointCloud::Components> m_lods;
      BoxSide() : m_numLOD(0), m_nFlags(kVisible) {}
    } m_boxSide[6];
  protected:
    // Box encoding: -X, +X, -Y, +Y, -Z, +Z
    static const struct BoxEncoding { int x, y, z; } boxEncoding[6];
    OdUInt32 computeVisibleSides(const OdGeVector3d &viewDir) const
    { OdUInt32 rVal = 0;
      for (OdUInt32 nSide = 0; nSide < 6; nSide++)
      {
        if (OdNegative(OdGeVector3d(1.0 * boxEncoding[nSide].x, 1.0 * boxEncoding[nSide].y, 1.0 * boxEncoding[nSide].z).dotProduct(viewDir)))
          rVal |= 1 << nSide;
      }
      return rVal;
    }
    OdGeVector3d modelDirection(const OdGiViewport &pVp) const
    {
      return pVp.viewDir().transformBy(pVp.getEyeToModelTransform() * pVp.getWorldToEyeTransform());
    }
    OdUInt32 computeLOD(const OdGiViewport &pVp) const
    {
      OdGePoint2d lowerLeft, upperRight;
      pVp.getViewportDcCorners(lowerLeft, upperRight);
      const double vpSize = odmin(odmax(upperRight.x, lowerLeft.x) - odmin(upperRight.x, lowerLeft.x),
                                  odmax(upperRight.y, lowerLeft.y) - odmin(upperRight.y, lowerLeft.y));
      OdGeBoundBlock3d bb;
      getExtents(bb);
      bb.transformBy(pVp.getModelToEyeTransform());
      OdGePoint3d minPt, maxPt;
      bb.getMinMaxPoints(minPt, maxPt);
      const double bbSize = odmax(maxPt.x - minPt.x, maxPt.y - minPt.y);
      double coef = bbSize / vpSize * m_pCom->numLODs();
      if (coef >= m_pCom->numLODs()) coef = m_pCom->numLODs() - 1;
      if (coef < 1.0) coef = 1.0;
      return (OdUInt32)coef;
    }
  public:
    ExPointCloudImpl(const ExPointCloudCom *pCom = NULL)
      : m_pCom(pCom) { }
    void setupCom(const ExPointCloudCom *pCom) { m_pCom = pCom; }
    // OdGiPointCloud interface implementation
    virtual OdUInt32 totalPointsCount() const
    {
      return m_pCom->maxDensity() * m_pCom->maxDensity() * 6;
    }
    virtual OdUInt32 componentsMask() const
    {
      return m_pCom->componentsMask();
    }
#ifdef GEN_FP_DATA
#ifndef SUPPORT_PARTIAL_UPDATE
    virtual OdUInt32 supportFlags(Component component = kNumComponents) const
    { return (component == kNumComponents) ? 0 : ((component == kColorComponent) ? 1 : 4); }
#else
    virtual OdUInt32 supportFlags(Component component = kNumComponents) const
    { return (component == kNumComponents) ? kPartialData : ((component == kColorComponent) ? 1 : 4); }
#endif
#else
#ifdef SUPPORT_PARTIAL_UPDATE
    virtual OdUInt32 supportFlags(Component component = kNumComponents) const
    { return (component == kNumComponents) ? kPartialData : OdGiPointCloud::supportFlags(component); }
#endif
#endif
    virtual bool getExtents(OdGeBoundBlock3d &bb) const
    {
      bb.set(OdGePoint3d(-0.5, -0.5, -0.5), OdGePoint3d(0.5, 0.5, 0.5));
      return true;
    }
    virtual bool isDataCompatible(const OdGiViewport &pVp1, const OdGiViewport &pVp2) const
    {
      return computeVisibleSides(modelDirection(pVp1)) == computeVisibleSides(modelDirection(pVp2)) &&
             computeLOD(pVp1) == computeLOD(pVp2);
    }
    virtual bool updatePointsData(OdGiPointCloudReceiver *pReceiver, OdUInt32 components = kNoComponents,
                                  OdUInt32 flags = 0, const OdGiViewport *pVp = NULL, const OdGiViewport *pVpFrom = NULL,
                                  OdUInt32 /*pointSize*/ = 0) const
    {
#ifdef SUPPORT_PARTIAL_UPDATE
      const OdUInt32 prevSideMask = (pVpFrom) ? computeVisibleSides(modelDirection(*pVpFrom)) : 0x3F;
      const OdUInt32 prevLod = (pVpFrom) ? computeLOD(*pVpFrom) : 1;
#endif
      const OdUInt32 sideMask = (pVp) ? computeVisibleSides(modelDirection(*pVp)) : 0x3F;
      const OdUInt32 lod = (pVp) ? computeLOD(*pVp) : 1;
      const OdUInt32 minDensity = m_pCom->minDensity();
      const OdUInt32 maxDensity = m_pCom->maxDensity();
      const OdUInt32 numPtLod = (maxDensity - minDensity) / m_pCom->numLODs();
      const OdUInt32 numPoints = minDensity + numPtLod * lod;
      for (OdUInt32 nSide = 0; nSide < 6; nSide++)
      {
        if (GETBIT(sideMask, 1 << nSide))
        {
          if (m_boxSide[nSide].m_numLOD > 0)
          { // Check does all neccessary data is available
            OdUInt32 nLodFrom = 0xFFFFFFFF;
            for (OdUInt32 nLOD = 0; nLOD < m_boxSide[nSide].m_numLOD; nLOD++)
            { bool bBreak = false;
              if (GETBIT(components, kColors) && !m_boxSide[nSide].m_lods[nLOD].hasComponent(kColorComponent))
                bBreak = true;
              if (GETBIT(components, kNormals) && !m_boxSide[nSide].m_lods[nLOD].hasComponent(kNormalComponent))
                bBreak = true;
              if (bBreak)
              {
                nLodFrom = nLOD;
                break;
              }
            }
            if (nLodFrom < m_boxSide[nSide].m_numLOD)
              m_boxSide[nSide].m_numLOD = nLodFrom;
          }
          if (m_boxSide[nSide].m_numLOD < lod)
          { m_boxSide[nSide].m_lods.resize(lod);
            for (OdUInt32 nLod = m_boxSide[nSide].m_numLOD; nLod < lod; nLod++)
            {
              OdGiPointCloud::Components &genComps = m_boxSide[nSide].m_lods[nLod];
              const OdUInt32 density = (!nLod) ? minDensity : numPtLod;
              genComps.m_nPoints = density * density;
#ifndef GEN_FP_DATA
              const double exOffset = (!nLod) ? 0.0 : ((1.0 / minDensity / m_pCom->numLODs()) * nLod);
              genComps.m_component[OdGiPointCloud::kVertexComponent].resize(density * density * sizeof(OdGePoint3d));
              if (GETBIT(components, OdGiPointCloud::kColors))
                genComps.m_component[OdGiPointCloud::kColorComponent].resize(density * density * sizeof(OdCmEntityColor));
              if (GETBIT(components, OdGiPointCloud::kNormals))
                genComps.m_component[OdGiPointCloud::kNormalComponent].resize(density * density * sizeof(OdGeVector3d));
              OdGePoint3d *pVertexData = (OdGePoint3d*)genComps.m_component[OdGiPointCloud::kVertexComponent].asArrayPtr();
              double *pCoordA = (!boxEncoding[nSide].x) ? &pVertexData->x : &pVertexData->y;
              double *pCoordB = (!boxEncoding[nSide].z) ? &pVertexData->z : &pVertexData->y;
              double *pCoord0 = (boxEncoding[nSide].x) ? &pVertexData->x : ((boxEncoding[nSide].y) ? &pVertexData->y : &pVertexData->z);
              OdCmEntityColor *pColors = (OdCmEntityColor*)genComps.m_component[OdGiPointCloud::kColorComponent].asArrayPtr();
              OdGeVector3d *pNormals = (OdGeVector3d*)genComps.m_component[OdGiPointCloud::kNormalComponent].asArrayPtr();
              const double offset = 0.5 * (boxEncoding[nSide].x + boxEncoding[nSide].y + boxEncoding[nSide].z);
              const OdCmEntityColor color(OdUInt8(255 * ((nSide + 1) & 1)), OdUInt8(255 * (((nSide + 1) & 2) >> 1)), OdUInt8(255 * (((nSide + 1) & 4) >> 2)));
              const OdGeVector3d normal(1.0 * boxEncoding[nSide].x, 1.0 * boxEncoding[nSide].y, 1.0 * boxEncoding[nSide].z);
              const double delta = 1.0 / density;
              for (OdUInt32 a = 0; a < density; a++)
              {
                const double coordA = -0.5 + delta * a + exOffset;
                for (OdUInt32 b = 0; b < density; b++, pCoordA += 3, pCoordB += 3, pCoord0 += 3)
                {
                  *pCoordA = coordA; *pCoordB = -0.5 + delta * b + exOffset; *pCoord0 = offset;
                  if (pColors) *pColors++ = color;
                  if (pNormals) *pNormals++ = normal;
                }
              }
#else
              const float exOffset = (!nLod) ? 0.0f : ((1.0f / minDensity / m_pCom->numLODs()) * nLod);
              genComps.m_component[OdGiPointCloud::kVertexComponent].resize(density * density * sizeof(float) * 3);
              if (GETBIT(components, OdGiPointCloud::kColors))
                genComps.m_component[OdGiPointCloud::kColorComponent].resize(density * density * 4);
              if (GETBIT(components, OdGiPointCloud::kNormals))
                genComps.m_component[OdGiPointCloud::kNormalComponent].resize(density * density * sizeof(float) * 3);
              float *pVertexData = (float*)genComps.m_component[OdGiPointCloud::kVertexComponent].asArrayPtr();
              float *pCoordA = (!boxEncoding[nSide].x) ? (pVertexData + 0) : (pVertexData + 1);
              float *pCoordB = (!boxEncoding[nSide].z) ? (pVertexData + 2) : (pVertexData + 1);
              float *pCoord0 = (boxEncoding[nSide].x) ? (pVertexData + 0) : ((boxEncoding[nSide].y) ? (pVertexData + 1) : (pVertexData + 2));
              OdUInt8 *pColors = genComps.m_component[OdGiPointCloud::kColorComponent].asArrayPtr();
              float *pNormals = (float*)genComps.m_component[OdGiPointCloud::kNormalComponent].asArrayPtr();
              const float offset = 0.5f * (boxEncoding[nSide].x + boxEncoding[nSide].y + boxEncoding[nSide].z);
              const OdUInt8 color[4] = { OdUInt8(255 * ((nSide + 1) & 1)), OdUInt8(255 * (((nSide + 1) & 2) >> 1)), OdUInt8(255 * (((nSide + 1) & 4) >> 2)), 255 };
              const float normal[3] = { 1.0f * boxEncoding[nSide].x, 1.0f * boxEncoding[nSide].y, 1.0f * boxEncoding[nSide].z };
              const float delta = 1.0f / density;
              for (OdUInt32 a = 0; a < density; a++)
              {
                const float coordA = -0.5f + delta * a + exOffset;
                for (OdUInt32 b = 0; b < density; b++, pCoordA += 3, pCoordB += 3, pCoord0 += 3)
                {
                  *pCoordA = coordA; *pCoordB = -0.5f + delta * b + exOffset; *pCoord0 = offset;
                  if (pColors) *pColors++ = color[0], *pColors++ = color[1], *pColors++ = color[2], *pColors++ = color[3];
                  if (pNormals) *pNormals++ = normal[0], *pNormals++ = normal[1], *pNormals++ = normal[2];
                }
              }
#endif
            }
          }
          else if (m_boxSide[nSide].m_numLOD > lod)
          {
            m_boxSide[nSide].m_lods.resize(lod);
          }
          m_boxSide[nSide].m_numLOD = lod;
#ifdef SUPPORT_PARTIAL_UPDATE
          if (!GETBIT(flags, kPartialData) || !GETBIT(prevSideMask, 1 << nSide))
          {
#endif
            OdGiPointCloud::ComponentsRawArray raws(m_boxSide[nSide].m_numLOD, 1);
            raws.resize(m_boxSide[nSide].m_numLOD);
            for (OdUInt32 nLod = 0; nLod < m_boxSide[nSide].m_numLOD; nLod++)
              raws[nLod].fromComponents(m_boxSide[nSide].m_lods[nLod], components);
#ifndef GEN_FP_DATA
            if (!pReceiver->addPoints(raws.getPtr(), raws.size(),
                                      OdGiPointCloud::getDefaultDataSizeFlags(), nSide))
#else
            if (!pReceiver->addPoints(raws.getPtr(), raws.size(),
                                      OdGiPointCloud::addDataSizeFlags(NULL, OdGiPointCloud::kVertexComponent, OdGiPointCloud::kDataSizeFloat) |
                                      OdGiPointCloud::addDataSizeFlags(NULL, OdGiPointCloud::kColorComponent, OdGiPointCloud::kDataSizeByte) |
                                      OdGiPointCloud::addDataSizeFlags(NULL, OdGiPointCloud::kNormalComponent, OdGiPointCloud::kDataSizeFloat), nSide))
#endif
              return true;
#ifdef SUPPORT_PARTIAL_UPDATE
          }
          else
          {
            if (lod > prevLod)
            {
              OdGiPointCloud::ComponentsRawArray raws(lod - prevLod, 1);
              raws.resize(lod - prevLod);
              for (OdUInt32 nLod = 0; nLod < lod - prevLod; nLod++)
                raws[nLod].fromComponents(m_boxSide[nSide].m_lods[prevLod + nLod], components);
#ifndef GEN_FP_DATA
              if (!pReceiver->addPoints(raws.getPtr(), raws.size(),
                                        OdGiPointCloud::getDefaultDataSizeFlags() | kPartialData, nSide))
#else
              if (!pReceiver->addPoints(raws.getPtr(), raws.size(),
                                        OdGiPointCloud::addDataSizeFlags(NULL, OdGiPointCloud::kVertexComponent, OdGiPointCloud::kDataSizeFloat) |
                                        OdGiPointCloud::addDataSizeFlags(NULL, OdGiPointCloud::kColorComponent, OdGiPointCloud::kDataSizeByte) |
                                        OdGiPointCloud::addDataSizeFlags(NULL, OdGiPointCloud::kNormalComponent, OdGiPointCloud::kDataSizeFloat) | kPartialData, nSide))
#endif
                return true;

            }
            else
            {
              if (!pReceiver->removePoints((prevLod - lod) * numPtLod, nSide))
                return true;
            }
          }
#endif
        }
        // Current mechanism differs. In case if LOD isn't changed - simply call removePoints with 0.
        // If cell must be removed - simply don't call addPoints or removePoints.
        // Looks like this mechanist is easier for implementing at client side.
//#ifdef SUPPORT_PARTIAL_UPDATE
//        else if (GETBIT(flags, kPartialData) && GETBIT(prevSideMask, 1 << nSide))
//        {
//          if (!pReceiver->removePoints(minDensity + numPtLod * prevLod, nSide))
//            return true;
//        }
//#endif
      }
      return true;
    }
};
const ExPointCloudImpl::BoxEncoding ExPointCloudImpl::boxEncoding[6] = 
{
  { -1, 0, 0 }, { 1, 0, 0 }, { 0, -1, 0 }, { 0, 1, 0 }, { 0, 0, -1 }, { 0, 0, 1 }
};

/* -------------------------------------------------------------------------------------- */
/* ExPointCloud custom entity                                                             */
/* -------------------------------------------------------------------------------------- */

class ExPointCloud : public OdDbEntity, protected ExPointCloudCom
{
  protected:
    ExPointCloudImpl m_impl;
  protected:
    OdGePoint3d m_position;
    OdGeScale3d m_scale;
    OdGeVector3d m_rotate;
    OdUInt32 m_minDensity, m_maxDensity;
    OdUInt32 m_lods, m_components;
  protected:
    OdUInt32 componentsMask() const
    { //assertReadEnabled();
      return m_components; }
  public:
    ODDB_DECLARE_MEMBERS(ExPointCloud);

    ExPointCloud()
      : m_minDensity(100), m_maxDensity(1100), m_lods(10)
      , m_components(OdGiPointCloud::kColors | OdGiPointCloud::kNormals)
    { m_impl.setupCom(this); }
    ~ExPointCloud()
    { }

    const OdGePoint3d &position() const
    {
      assertReadEnabled();
      return m_position;
    }
    void setPosition(const OdGePoint3d &pos)
    {
      assertWriteEnabled();
      m_position = pos;
    }
    const OdGeScale3d &scale() const
    {
      assertReadEnabled();
      return m_scale;
    }
    void setScale(const OdGeScale3d &scale)
    {
      assertWriteEnabled();
      m_scale = scale;
    }
    const OdGeVector3d &rotate() const
    {
      assertReadEnabled();
      return m_rotate;
    }
    void setRotate(const OdGeVector3d &rot)
    {
      assertWriteEnabled();
      m_rotate = rot;
    }

    OdUInt32 minDensity() const
    {
      //assertReadEnabled();
      return m_minDensity;
    }
    OdUInt32 maxDensity() const
    {
      //assertReadEnabled();
      return m_maxDensity;
    }
    void setDensity(OdUInt32 minDensity, OdUInt32 maxDensity)
    {
      if (minDensity < 1 || maxDensity < minDensity)
        throw OdError(eOutOfRange);
      assertWriteEnabled();
      m_minDensity = minDensity;
      m_maxDensity = maxDensity;
    }

    OdUInt32 numLODs() const
    {
      //assertReadEnabled();
      return m_lods;
    }
    void setNumLODs(OdUInt32 lods)
    {
      if (lods < 1)
        throw OdError(eOutOfRange);
      assertWriteEnabled();
      m_lods = lods;
    }

    bool colorsEnabled() const
    {
      assertReadEnabled();
      return GETBIT(m_components, OdGiPointCloud::kColors);
    }
    void enableColors(bool bEnable)
    {
      assertWriteEnabled();
      SETBIT(m_components, OdGiPointCloud::kColors, bEnable);
    }
    bool normalsEnabled() const
    {
      assertReadEnabled();
      return GETBIT(m_components, OdGiPointCloud::kNormals);
    }
    void enableNormals(bool bEnable)
    {
      assertWriteEnabled();
      SETBIT(m_components, OdGiPointCloud::kNormals, bEnable);
    }

    OdGeMatrix3d getTransform() const
    {
      assertReadEnabled();
      return OdGeMatrix3d::translation(m_position.asVector()) *
             OdGeMatrix3d::rotation(m_rotate.x, OdGeVector3d::kXAxis) *
             OdGeMatrix3d::rotation(m_rotate.y, OdGeVector3d::kYAxis) *
             OdGeMatrix3d::rotation(m_rotate.z, OdGeVector3d::kZAxis) *
             OdGeMatrix3d::scaling(m_scale);
    }
    void setTransform(const OdGeMatrix3d &tm)
    {
      assertWriteEnabled();
      OdGeVector3d xAxis, yAxis, zAxis; OdGePoint3d origin;
      tm.getCoordSystem(origin, xAxis, yAxis, zAxis);
      m_position = origin;
      m_scale.set(xAxis.normalizeGetLength(), yAxis.normalizeGetLength(), zAxis.normalizeGetLength());
      m_rotate.set(OD_ATAN2(yAxis.z, zAxis.z), -OD_ASIN(xAxis.z), OD_ATAN2(xAxis.y, xAxis.x));
    }
    OdResult subTransformBy(const OdGeMatrix3d& xform)
    {
      setTransform(xform * getTransform());
      return eOk;
    }

    OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const
    {
      OdUInt32 rFlags = OdDbEntity::subSetAttributes(pTraits);
      // rFlags |= OdGiDrawable::kDrawableRegenDraw; // Enable permanent entity regeneration
      return rFlags;
    }
    bool subWorldDraw(OdGiWorldDraw* pWd) const
    {
      const OdGeMatrix3d tx = getTransform() * OdGeMatrix3d::rotation(OdaToRadian(90.0), OdGeVector3d::kXAxis)
                                             * OdGeMatrix3d::rotation(OdaToRadian(90.0), OdGeVector3d::kYAxis);
      pWd->geometry().pushModelTransform(tx);
      pWd->geometry().pointCloud(m_impl);
      pWd->geometry().popModelTransform();
      return true;
    }

    OdResult dwgInFields(OdDbDwgFiler* pFiler)
    {
      OdResult res = OdDbEntity::dwgInFields(pFiler);
      if (res != eOk)
        return res;
      m_position = pFiler->rdPoint3d();
      m_scale = pFiler->rdScale3d();
      m_rotate = pFiler->rdVector3d();
      m_minDensity = (OdUInt32)pFiler->rdInt32();
      m_maxDensity = (OdUInt32)pFiler->rdInt32();
      m_lods = (OdUInt32)pFiler->rdInt32();
      m_components = (OdUInt32)pFiler->rdInt32();
      return eOk;
    }
    void dwgOutFields(OdDbDwgFiler* pFiler) const
    {
      OdDbEntity::dwgOutFields(pFiler);
      pFiler->wrPoint3d(m_position);
      pFiler->wrScale3d(m_scale);
      pFiler->wrVector3d(m_rotate);
      pFiler->wrInt32((OdInt32)m_minDensity);
      pFiler->wrInt32((OdInt32)m_maxDensity);
      pFiler->wrInt32((OdInt32)m_lods);
      pFiler->wrInt32((OdInt32)m_components);
    }
    OdResult dxfInFields(OdDbDxfFiler* pFiler)
    {
      OdResult res = OdDbEntity::dxfInFields(pFiler);
      if (res != eOk)
        return res;
      if (!pFiler->atSubclassData(desc()->name()))
        return eBadDxfSequence;
      m_position = pFiler->nextRb()->getPoint3d();
      m_scale.sx = pFiler->nextRb()->getDouble();
      m_scale.sy = pFiler->nextRb()->getDouble();
      m_scale.sz = pFiler->nextRb()->getDouble();
      m_rotate.x = (pFiler->nextRb(), pFiler->rdAngle());
      m_rotate.y = (pFiler->nextRb(), pFiler->rdAngle());
      m_rotate.z = (pFiler->nextRb(), pFiler->rdAngle());
      m_minDensity = (OdUInt32)pFiler->nextRb()->getInt32();
      m_maxDensity = (OdUInt32)pFiler->nextRb()->getInt32();
      m_lods = (OdUInt32)pFiler->nextRb()->getInt32();
      m_components = (OdUInt32)pFiler->nextRb()->getInt32();
      return eOk;
    }
    void dxfOutFields(OdDbDxfFiler* pFiler) const
    {
      OdDbEntity::dxfOutFields(pFiler);
      pFiler->wrSubclassMarker(desc()->name());
      pFiler->wrPoint3d(10, m_position);
      pFiler->wrDouble(40, m_scale.sx);
      pFiler->wrDouble(41, m_scale.sy);
      pFiler->wrDouble(42, m_scale.sz);
      pFiler->wrAngle(50, m_rotate.x);
      pFiler->wrAngle(51, m_rotate.y);
      pFiler->wrAngle(53, m_rotate.z);
      pFiler->wrInt32(90, m_minDensity);
      pFiler->wrInt32(91, m_maxDensity);
      pFiler->wrInt32(92, m_lods);
      pFiler->wrInt32(94, m_components);
    }
};

ODRX_DXF_DEFINE_MEMBERS(ExPointCloud,
                        OdDbEntity,
                        DBOBJECT_CONSTR,
                        OdDb::vAC24,
                        OdDb::kMRelease0,
                        OdDbProxyEntity::kAllAllowedBits,
                        ExPointCloud,
                        OdaMfcApp|Description: Point Cloud provider example)

class OdExPointCloudCmd : public OdEdCommand
{
  public:
    const OdString groupName() const
    {
      return OD_T("ODAMFCAPP");
    }
    const OdString globalName() const
    {
      return OD_T("ExPointCloud");
    }
    void execute(OdEdCommandContext* pCmdCtx)
    {
      OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
      OdDbDatabasePtr pDb = pDbCmdCtx->database();
      OdSmartPtr<OdDbUserIO> pIO = pDbCmdCtx->userIO();
      OdDbBlockTableRecordPtr pBTR = pDb->getActiveLayoutBTRId().openObject(OdDb::kForWrite);
      OdSmartPtr<ExPointCloud> pPointCloud = ExPointCloud::createObject();
      pPointCloud->setDatabaseDefaults(pDb);

      pPointCloud->setPosition(pIO->getPoint(OD_T("\nSpecify center of Point Cloud: ")));
      pPointCloud->setScale(OdGeScale3d(pIO->getDist(OD_T("\nSpecify scale of Point Cloud: "))));
      pPointCloud->setRotate(OdGeVector3d(0.0, 0.0, pIO->getAngle(OD_T("\nSpecify rotation angle around z-axis: "))));

      pBTR->appendOdDbEntity(pPointCloud);
    }
};
static OdStaticRxObject<OdExPointCloudCmd> g_OdExPointCloudCmd;

// Export "extern" functions

void rxInitExPointCloud()
{
  ExPointCloud::rxInit();
  odedRegCmds()->addCommand(&g_OdExPointCloudCmd);
}

void rxUninitExPointCloud()
{
  odedRegCmds()->removeCmd(&g_OdExPointCloudCmd);
  ExPointCloud::rxUninit();
}

#else

void rxInitExPointCloud() { }
void rxUninitExPointCloud() { }

#endif

//
