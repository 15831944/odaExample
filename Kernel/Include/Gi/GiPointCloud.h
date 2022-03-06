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

#ifndef __ODGIPOINTCLOUD_H__
#define __ODGIPOINTCLOUD_H__

#include "Gi/GiViewport.h"
#include "Ge/GePoint3dArray.h"
#include "Ge/GeVector3dArray.h"
#include "Ge/GeMatrix3d.h"
#include "Ge/GeBoundBlock3d.h"
#include "UInt8Array.h"

#include "TD_PackPush.h"

#include "Gi/GiExport.h"

// Forward declarations
class OdGiPointCloudFilter;
typedef OdSmartPtr<OdGiPointCloudFilter> OdGiPointCloudFilterPtr;
class OdGiPointCloudReceiver;
typedef OdSmartPtr<OdGiPointCloudReceiver> OdGiPointCloudReceiverPtr;

/** \details
  Basic point cloud interface object.

  <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiPointCloud : public OdRxObject
{
  public:
    enum Component
    {
      kVertexComponent = 0, // Vertexes data component
      kColorComponent,      // Colors data component
      kNormalComponent,     // Normals data component
      //
      kNumComponents        // Number of data components
    };
    enum ExtraComponent
    { // Extra components (available in Components structure, but not in Flags)
      kTransparencyComponent = kNumComponents,
      kNumExtraComponents
    };
    enum ComponentMask
    { kNoComponents   = 0,        // No data components
      kColors         = (1 << 0), // Colors data component
      kTransparencies = (1 << 1), // Transparencies data component
      kNormals        = (1 << 2)  // Normals data component
    };
    enum DataSize
    {
      kDataSizeByte   = 0,
      kDataSizeWord,
      kDataSizeFloat,
      kDataSizeDouble
    };
    enum Flags
    {
      kLastComponentFlag = (1 << (kNumComponents << 1)), // Flags offset
      // Flags
      kAsyncCall   = (kLastComponentFlag << 0),  // Support asynchronic calls.
      kPartialData = (kLastComponentFlag << 1),  // Support partial data updates.
      //
      kLastFlag = kPartialData // Last flag
    };
    /** \details
      Helper function to set data type size into flags.
    */
    static OdUInt32 addDataSizeFlags(OdUInt32 *pFlags, Component component, DataSize ds)
    { const OdUInt32 addSet = (OdUInt32)ds << (component << 1);
      if (!pFlags) return addSet;
      return *pFlags = (*pFlags & ~(3 << (component << 1))) | addSet;
    }
    /** \details
      Helper function extracts data type size from flags.
    */
    static DataSize getDataSizeFlags(OdUInt32 flags, Component component)
    {
      return DataSize((flags >> (component << 1)) & 3);
    }
    /** \details
      Returns default point cloud setting (actual for Gi implementation).
    */
    static OdUInt32 getDefaultDataSizeFlags()
    { return OdGiPointCloud::addDataSizeFlags(NULL, OdGiPointCloud::kVertexComponent, OdGiPointCloud::kDataSizeDouble) |
             OdGiPointCloud::addDataSizeFlags(NULL, OdGiPointCloud::kColorComponent, OdGiPointCloud::kDataSizeWord) |
             OdGiPointCloud::addDataSizeFlags(NULL, OdGiPointCloud::kNormalComponent, OdGiPointCloud::kDataSizeDouble);
    }
    struct Components
    {
      OdUInt8Array m_component[kNumExtraComponents];
      OdUInt32 m_nPoints;
      bool hasComponent(long nComponent) const { return !m_component[nComponent].isEmpty(); }
      Components() : m_nPoints(0) {}
    };
    typedef OdArray<Components> ComponentsArray;
    struct ComponentsRaw
    {
      const void *m_pComponent[kNumExtraComponents];
      OdUInt32 m_nPoints;
      bool hasComponent(long nComponent) const { return m_pComponent[nComponent] != NULL; }
      ComponentsRaw &fromComponents(Components &comps, OdUInt32 components = 0xFFFFFFFF)
      { const bool bNeedComponent[kNumExtraComponents] = /* Vertexes is always true */
          { true, GETBIT(components, kColors), GETBIT(components, kNormals), GETBIT(components, kTransparencies) };
        for (long nComponent = 0; nComponent < kNumExtraComponents; nComponent++)
          m_pComponent[nComponent] = (bNeedComponent[nComponent] && comps.hasComponent(nComponent)) ?
                                       comps.m_component[nComponent].getPtr() : NULL;
        m_nPoints = comps.m_nPoints;
        return *this; }
      ComponentsRaw &construct(const void *pPoints, OdUInt32 nPoints, const void *pColors = NULL, const void *pTransparencies = NULL,
                               const void *pNormals = NULL)
      { m_pComponent[kVertexComponent] = pPoints;               m_pComponent[kColorComponent] = pColors;
        m_pComponent[kTransparencyComponent] = pTransparencies; m_pComponent[kNormalComponent] = pNormals;
        m_nPoints = nPoints;
        return *this; }
    };
    typedef OdArray<ComponentsRaw, OdMemoryAllocator<ComponentsRaw> > ComponentsRawArray;
  public:
    ODRX_DECLARE_MEMBERS(OdGiPointCloud);

    /** \details
      Returns total number of points, contained by point cloud entity.
    */
    virtual OdUInt32 totalPointsCount() const = 0;
    /** \details
      Returns set of data components available for point cloud entity (see ComponentsMask enum).
    */
    virtual OdUInt32 componentsMask() const { return kNoComponents; }
    /** \details
      Returns format support flags.
      If set to any component except kNumComponents returns bit flags represent support data type sizes:
      1 - byte, 2 - short, 4 - float, 8 - double. For color 2 means OdCmEntityColor+OdCmTransparency combination.
      If set to kNumComponents return flags (see Flags enum).
      By default: Vertex as doubles, Colors as OdCmEntityColor, Normals as doubles and No Flags.
    */
    virtual OdUInt32 supportFlags(Component component = kNumComponents) const
    { return (component == kNumComponents) ? 0 : ((component == kColorComponent) ? 2 : 8); }

    /** \details
      Returns global transformation, which should be applied by underlying renderer to render point could data.
    */
    virtual const OdGeMatrix3d &globalTransform() const { return OdGeMatrix3d::kIdentity; }
    /** \details
      Returns default point size.
    */
    virtual OdInt32 defaultPointSize() const { return 0; }

    /** \details
      Return extents of point cloud entity.
    */
    virtual bool getExtents(OdGeBoundBlock3d & /*bb*/) const { return false; }
    /** \details
      Return extents of point cloud entity.
    */
    virtual bool calculateExtents(OdGeExtents3d &extents, const OdGiPointCloudFilter *pFilter = NULL) const;

    /** \details
      Check that point data compatible for specified viewports.
    */
    virtual bool isDataCompatible(const OdGiViewport &pVp1, const OdGiViewport &pVp2) const = 0;
    /** \details
      Compute point cloud data.
    */
    virtual bool updatePointsData(OdGiPointCloudReceiver *pReceiver, OdUInt32 components = kNoComponents,
                                  OdUInt32 flags = 0, const OdGiViewport *pVp = NULL, const OdGiViewport *pVpFrom = NULL,
                                  OdUInt32 pointSize = 0) const = 0;
};

typedef OdSmartPtr<OdGiPointCloud> OdGiPointCloudPtr;

/** \details
  Point cloud filter.

  <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiPointCloudFilter : public OdRxObject
{
  protected:
    OdGiPointCloudFilterPtr m_pPrevFilter;
  public:
    ODRX_DECLARE_MEMBERS(OdGiPointCloudFilter);

    void attachFilter(const OdGiPointCloudFilter *pFilter)
    { m_pPrevFilter = pFilter; }
    OdGiPointCloudFilterPtr detachFilter()
    { OdGiPointCloudFilterPtr pFilter = m_pPrevFilter; m_pPrevFilter.release(); return pFilter; }
  protected:
    virtual bool filterPointsImpl(OdGiPointCloud::ComponentsRaw *&pArrays, OdUInt32 &nArrays, OdUInt32 &compFlags, const OdGeBoundBlock3d *&pExtents) const = 0;
    virtual bool filterBoundingBoxImpl(OdGeBoundBlock3d &bb) const = 0;
    virtual void extractTransformImpl(OdGeMatrix3d & /*xForm*/) const { }
  public:
    bool filterPoints(OdGiPointCloud::ComponentsRaw *&pArrays, OdUInt32 &nArrays, OdUInt32 &compFlags, const OdGeBoundBlock3d *&pExtents) const
    { if (m_pPrevFilter.isNull() || m_pPrevFilter->filterPoints(pArrays, nArrays, compFlags, pExtents))
        return filterPointsImpl(pArrays, nArrays, compFlags, pExtents);
      return false;
    }
    bool filterBoundingBox(OdGeBoundBlock3d &bb) const
    { if (m_pPrevFilter.isNull() || m_pPrevFilter->filterBoundingBox(bb))
        return filterBoundingBoxImpl(bb);
      return false;
    }
    OdGeMatrix3d extractTransform() const
    { if (!m_pPrevFilter.isNull())
      { OdGeMatrix3d xForm = m_pPrevFilter->extractTransform();
        extractTransformImpl(xForm);
        return xForm;
      } else {
        OdGeMatrix3d xForm; extractTransformImpl(xForm); return xForm;
      }
    }
};

/** \details
  Default implementation of point cloud data transformation filter.

  <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiPointCloudXformFilter : public OdGiPointCloudFilter
{
  protected:
    mutable OdGiPointCloud::ComponentsArray m_comps;
    mutable OdGeBoundBlock3d m_bb;
    OdGeMatrix3d m_xForm;
  public:
    ODRX_DECLARE_MEMBERS(OdGiPointCloudXformFilter);
  protected:
    virtual bool filterPointsImpl(OdGiPointCloud::ComponentsRaw *&pPoints, OdUInt32 &nArrays, OdUInt32 &compFlags, const OdGeBoundBlock3d *&pExtents) const;
    virtual bool filterBoundingBoxImpl(OdGeBoundBlock3d &bb) const
    {
      bb.transformBy(m_xForm);
      return true;
    }
    virtual void extractTransformImpl(OdGeMatrix3d &xForm) const
    { xForm.preMultBy(m_xForm); }
  public:
    void setXform(const OdGeMatrix3d &xForm) { m_xForm = xForm; }
    void addXform(const OdGeMatrix3d &xForm) { m_xForm.preMultBy(xForm); }
    const OdGeMatrix3d &getXform() const { return m_xForm; }
    void resetXform() { m_xForm.setToIdentity(); }
    bool hasXform() const { return m_xForm != OdGeMatrix3d::kIdentity; }
    OdGeMatrix3d &accessXform() { return m_xForm; }

    static OdGiPointCloudFilterPtr createObject(const OdGeMatrix3d &xForm, const OdGiPointCloudFilter *pPrevFilter = NULL);
};

/** \details
  Default implementation of point cloud data transformation filter.

  <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiPointCloudComponentsFilter : public OdGiPointCloudFilter
{
  protected:
    mutable OdGiPointCloud::ComponentsArray m_comps;
    OdUInt32 m_requestComps;
  public:
    ODRX_DECLARE_MEMBERS(OdGiPointCloudComponentsFilter);
  protected:
    virtual bool filterPointsImpl(OdGiPointCloud::ComponentsRaw *&pPoints, OdUInt32 &nArrays, OdUInt32 &compFlags, const OdGeBoundBlock3d *&pExtents) const;
    virtual bool filterBoundingBoxImpl(OdGeBoundBlock3d &bb) const { return true; }
  public:
    void setComponentsRequest(OdUInt32 compFlags) { m_requestComps = compFlags; }
    OdUInt32 componentsRequest() const { return m_requestComps; }

    OdGiPointCloud::ComponentsArray &components() const { return m_comps; }

    static OdGiPointCloudFilterPtr createObject(OdUInt32 compFlags, const OdGiPointCloudFilter *pPrevFilter = NULL);
};

typedef OdUInt64 OdGiPointCloudCellId;
const OdGiPointCloudCellId kGiPointCloudNegativeCellId = OdGiPointCloudCellId(-1);

/** \details
  Point cloud data receiver.

  <group OdGi_Classes> 
*/
class FIRSTDLL_EXPORT OdGiPointCloudReceiver : public OdRxObject
{
  protected:
    OdGiPointCloudFilterPtr m_pFilter;
    OdGiPointCloud::ComponentsRawArray m_comps;
  public:
    ODRX_DECLARE_MEMBERS(OdGiPointCloudReceiver);

  protected:
    void attachFilter(const OdGiPointCloudFilter *pFilter)
    { m_pFilter = pFilter; }
    OdGiPointCloudFilterPtr detachFilter()
    { OdGiPointCloudFilterPtr pFilter = m_pFilter; m_pFilter.release(); return pFilter; }

    OdUInt32 numPointsTotal(const OdGiPointCloud::ComponentsRaw *pArrays, OdUInt32 nArrays) const
    { OdUInt32 nPoints = 0;
      for (OdUInt32 nArray = 0; nArray < nArrays; nArray++)
        nPoints += pArrays[nArray].m_nPoints;
      return nPoints;
    }

    virtual bool addPointsImpl(const OdGiPointCloud::ComponentsRaw *pArrays, OdUInt32 nArrays, OdUInt32 compFlags,
                               OdGiPointCloudCellId nCellId, const OdGeBoundBlock3d *pExtents) = 0;
    virtual bool removePointsImpl(OdUInt32 nPoints, OdGiPointCloudCellId nCellId) { return false; }
  private:
    bool addPointsFiltered(const OdGiPointCloud::ComponentsRaw *pArrays, OdUInt32 nArrays, OdUInt32 compFlags,
                           OdGiPointCloudCellId nCellId, const OdGeBoundBlock3d *pExtents)
    { OdGiPointCloud::ComponentsRaw pointsCopy;
      OdGiPointCloud::ComponentsRaw *pCopy = NULL;
      if (nArrays == 1) pointsCopy = *pArrays, pCopy = &pointsCopy;
      else if (nArrays > 1) m_comps.resize(nArrays),
        ::memcpy(m_comps.asArrayPtr(), pArrays, sizeof(OdGiPointCloud::ComponentsRaw) * nArrays), pCopy = m_comps.asArrayPtr();
      if (m_pFilter->filterPoints(pCopy, nArrays, compFlags, pExtents))
        return addPointsImpl(pCopy, nArrays, compFlags, nCellId, pExtents);
      return true;
    }
  public:
    bool addPoints(const OdGiPointCloud::ComponentsRaw *pArrays, OdUInt32 nArrays, OdUInt32 compFlags,
                   OdGiPointCloudCellId nCellId = kGiPointCloudNegativeCellId, const OdGeBoundBlock3d *pExtents = NULL)
    { 
      if (!m_pFilter.isNull())
        return addPointsFiltered(pArrays, nArrays, compFlags, nCellId, pExtents);
      else
        return addPointsImpl(pArrays, nArrays, compFlags, nCellId, pExtents);
    }
    bool removePoints(OdUInt32 nPoints, OdGiPointCloudCellId nCellId = kGiPointCloudNegativeCellId)
    {
      return removePointsImpl(nPoints, nCellId);
    }
};

/** \details
  Default implementation of point cloud data receiver for extents computation.

  <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiPointCloudExtentsReceiver : public OdGiPointCloudReceiver
{
  protected:
    OdGeExtents3d m_extents;
  public:
    ODRX_DECLARE_MEMBERS(OdGiPointCloudExtentsReceiver);

  protected:
    virtual bool addPointsImpl(const OdGiPointCloud::ComponentsRaw *pArrays, OdUInt32 nArrays, OdUInt32 compFlags,
                               OdGiPointCloudCellId /*nCellId*/, const OdGeBoundBlock3d *pExtents);
  public:
    static OdGiPointCloudReceiverPtr createObject(const OdGiPointCloudFilter *pFilter)
    { OdSmartPtr<OdGiPointCloudExtentsReceiver> pObj = createObject();
      pObj->attachFilter(pFilter);
      return pObj;
    }

    const OdGeExtents3d &getExtents() const { return m_extents; }
    void resetExtents() { m_extents = OdGeExtents3d::kInvalid; }
};

#include "TD_PackPop.h"

#endif  // __ODGIPOINTCLOUD_H__
