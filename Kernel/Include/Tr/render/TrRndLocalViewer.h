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
// GLES2 device local viewer interface

#ifndef ODTRRNDLOCALVIEWER
#define ODTRRNDLOCALVIEWER

#include "OdVector.h"
#include "TrRndLocalRenderer.h"

#include "TD_PackPush.h"

/** \details
    <group ExRender_Windows_Classes>
*/
class OdTrRndLocalViewer
{
  public:
    virtual OdTrRndLocalRenderer *renderer() = 0;
    virtual const OdTrRndLocalRenderer *renderer() const = 0;

    virtual ODCOLORREF backgroundColor() const = 0;
    virtual void setBackgroundColor(ODCOLORREF rgba) = 0;

    // Viewer capabilities

    // Resize client area
    virtual void resize(const OdGsDCRect &dcRect) = 0;
    // Redraw graphics
    virtual void update(OdTrVisRenderClient *pDevice) = 0;

    // Returns active viewport index
    virtual OdUInt32 activeViewportIndex() const = 0;
    // Returns active viewport Id
    virtual OdTrVisViewportId activeViewportId() const = 0;
    // Compare viewport Id with active viewport Id
    virtual bool isActiveViewport(OdTrVisViewportId vpId) const = 0;
    // Set active viewport
    virtual void setActiveViewport(OdTrVisViewportId vpId) = 0;
    // Set active viewport index
    virtual void setActiveViewportIndex(int nViewport) = 0;

    // Returns active viewport intended for selection
    virtual OdTrVisViewportId activeSelectionViewportId() const = 0;

    // Produce panning operation
    virtual void pan(int nX, int nY) = 0;
    // Produce simple zooming operation
    virtual void zoom(float fDelta) = 0;
    // Zooming around point
    virtual void zoom(int nX, int nY, float fDelta) = 0;
    // Orbit
    enum OrbitType
    {
      kOrbitPerp = 0,
      kOrbitHorizontal,
      kOrbitVertical,
      kOrbitEye
    };
    virtual void orbit(int nX, int nY, OrbitType type = kOrbitPerp, float angle = 0.0f) = 0;
    // Zoom extents
    virtual void zoomExtents(float coef = 1.03f) = 0;

    // Low-level transformation routines
    virtual void translate(const OdGeVector3d &offset) = 0;
    virtual void rotate(double xAngle, double yAngle, double zAngle, bool bLocalCS = true) = 0;

    // Returns layers list
    typedef OdVector<OdTrVisLayerId, OdMemoryAllocator<OdTrVisLayerId> > LayersList;
    virtual void getLayersList(LayersList &layers) const = 0;
    // Returns layer data
    virtual const OdTrVisLayerDef *getLayerDef(OdTrVisLayerId layerId) const = 0;
    // Returns layer name
    virtual const OdString &getLayerName(OdTrVisLayerId layerId) const = 0;

    // Enable layer
    virtual void enableLayer(OdTrVisLayerId layerId, bool bByViewport = false) = 0;
    // Disable layer
    virtual void disableLayer(OdTrVisLayerId layerId, bool bByViewport = false) = 0;
    // Toggle (invert) layer state
    virtual void toggleLayer(OdTrVisLayerId layerId, bool bByViewport = false) = 0;

    // Highlighting
    virtual void highlightAll(bool bHighlight, bool bByViewport = true) = 0;
    virtual void highlightByOwnerId(OdTrVisOwning ownerId, bool bHighlight, bool bByViewport = true) = 0;

    // Select viewport
    virtual OdTrVisViewportId pickViewport(int nX, int nY) = 0;

    // Render mode support (will be deprecated after VisualStyles implementation)
    virtual OdGsView::RenderMode renderMode(OdTrVisViewportId vpId) const = 0;
    virtual void setRenderMode(OdTrVisViewportId vpId, OdGsView::RenderMode rm) = 0;

    // Section planes
    virtual void addSectionPlane(OdTrVisViewportId vpId, const OdTrVisSectionPlane &plane) = 0;
    virtual void removeSectionPlane(OdTrVisViewportId vpId) = 0;
    virtual OdUInt32 sectionPlanesNumber(OdTrVisViewportId vpId) const = 0;
    virtual const OdTrVisSectionPlane *getSectionPlane(OdTrVisViewportId vpId, OdUInt32 nPlane = 0) const = 0;
    virtual void transformSectionPlanes(OdTrVisViewportId vpId, const OdGeMatrix3d &xForm) = 0;

    // Mark viewport modified
    virtual void markViewportModified(OdTrVisViewportId id, bool bViewProps = true, bool bRenderMode = false) = 0;
    //virtual OdUInt32 viewportIndex(OdTrVisViewportId id) const = 0;

    // Recompute scene depth
    virtual bool recomputeSceneDepth(OdTrVisViewportId vpId) = 0;
};

/** \details
    <group ExRender_Windows_Classes>
*/
class OdTrRndLocalViewerTPtrAdaptor : public OdTrRndLocalRendererTPtrAdaptor
{
  public:
    static void addRef(OdTrRndLocalViewer* pObj)  { if (pObj) OdTrRndLocalRendererTPtrAdaptor::addRef (pObj->renderer()); }
    static void release(OdTrRndLocalViewer* pObj) { if (pObj) OdTrRndLocalRendererTPtrAdaptor::release(pObj->renderer()); }
};

/** \details
    <group ExRender_Windows_Classes>
*/
class OdTrRndLocalViewerPtr : public TPtr<OdTrRndLocalViewer, OdTrRndLocalViewerTPtrAdaptor>
{
  public:
    OdTrRndLocalViewerPtr()
      : TPtr<OdTrRndLocalViewer, OdTrRndLocalViewerTPtrAdaptor>() {}
    OdTrRndLocalViewerPtr(const OdTrRndLocalViewerPtr& ref)
      : TPtr<OdTrRndLocalViewer, OdTrRndLocalViewerTPtrAdaptor>(ref) {}
    OdTrRndLocalViewerPtr(const OdTrRndLocalViewer* pObj, bool bAttach = false)
      : TPtr<OdTrRndLocalViewer, OdTrRndLocalViewerTPtrAdaptor>(pObj, bAttach) {}
    OdTrRndLocalViewerPtr(const OdTrRndLocalRenderer *pRenderer)
      : TPtr<OdTrRndLocalViewer, OdTrRndLocalViewerTPtrAdaptor>(pRenderer->viewer()) {}
    OdTrRndLocalViewerPtr &operator =(OdTrRndLocalViewer *pObj)
    { return static_cast<OdTrRndLocalViewerPtr&>(TPtr<OdTrRndLocalViewer, OdTrRndLocalViewerTPtrAdaptor>::operator =(pObj)); }
    OdTrRndLocalViewerPtr &operator =(const OdTrRndLocalViewerPtr& ref)
    { return static_cast<OdTrRndLocalViewerPtr&>(TPtr<OdTrRndLocalViewer, OdTrRndLocalViewerTPtrAdaptor>::operator =(ref)); }
    OdTrRndLocalViewerPtr &operator =(OdTrRndLocalRenderer *pRenderer)
    { TPtr<OdTrRndLocalViewer, OdTrRndLocalViewerTPtrAdaptor>::operator =(pRenderer->viewer()); return *this; }
    void release() { *this = TPtr<OdTrRndLocalViewer, OdTrRndLocalViewerTPtrAdaptor>::operator =(NULL); }
};

#include "TD_PackPop.h"

#endif // ODTRRNDLOCALVIEWER
