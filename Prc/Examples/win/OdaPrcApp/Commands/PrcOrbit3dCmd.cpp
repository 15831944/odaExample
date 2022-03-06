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

#include "../stdafx.h"
#include "Gi/GiDrawableImpl.h"
#include "Gs/GsBaseVectorizer.h"
#include "PrcFile.h"
#include "PrcOrbit3dCmd.h"
#include "AbstractViewPE.h"

// 3d orbit command

const OdString OdExPrc3dOrbitCmd::groupName() const
{
  return globalName();
}

const OdString OdExPrc3dOrbitCmd::globalName() const
{
  return OD_T("3DORBIT");
}

class OrbitCtrl: public OdGiDrawableImpl<>
{
public:
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const
  {
    return kDrawableIsAnEntity | kDrawableRegenDraw;
  }
  bool subWorldDraw(OdGiWorldDraw* pWd) const
  {
    return false;
  }
  void subViewportDraw(OdGiViewportDraw* pVd) const
  {
    OdGiViewport& vp = pVd->viewport();
    OdGiGeometry& geom = pVd->geometry();
    pVd->subEntityTraits().setColor(OdCmEntityColor::kACIGreen);
    pVd->subEntityTraits().setFillType(kOdGiFillNever);

    OdGiModelTransformSaver mt(geom, vp.getEyeToModelTransform());
    OdGiDrawFlagsHelper _dfh(pVd->subEntityTraits(), OdGiSubEntityTraits::kDrawNoPlotstyle);

    OdGePoint3d pt1;
    OdGePoint2d pt2;
    vp.getViewportDcCorners((OdGePoint2d&)pt1, pt2);
    pt2.x -= pt1.x;
    pt2.y -= pt1.y;
    double r = odmin(pt2.x, pt2.y) / 9. * 7. / 2.;
    ((OdGePoint2d&)pt1) += (pt2.asVector() / 2.);
    geom.circle(pt1, r, OdGeVector3d::kZAxis);

    geom.circle(pt1 + OdGeVector3d(0., r, 0.), r / 20., OdGeVector3d::kZAxis);
    geom.circle(pt1 + OdGeVector3d(0.,-r, 0.), r / 20., OdGeVector3d::kZAxis);
    geom.circle(pt1 + OdGeVector3d( r, 0.,0.), r / 20., OdGeVector3d::kZAxis);
    geom.circle(pt1 + OdGeVector3d(-r, 0.,0.), r / 20., OdGeVector3d::kZAxis);
  }
};

class RTOrbitTracker : public OdEdPointTracker
{
  OdGsView*       m_pView;
  OdGePoint3d     m_pt;
  OdGiDrawablePtr m_pDrw;
  OdGePoint3d     m_pos;
  OdGePoint3d     m_trg;
  OdGeVector3d    m_up;
  OdGeVector3d    m_x;
  OdGePoint3d     m_viewCenter;
  OdGeMatrix3d    m_initViewingMatrixInv;
  double          m_D; // diameter of orbit control in projected coordinates
  OdGsModelPtr    m_pModel;

  enum Axis
  {
    kHorizontal,
    kVertical,
    kPerpDir, // orbit around perpendicular to mouse direction
    kEye,
  }
  m_axis;

  void viewportDcCorners(OdGePoint2d& lower_left, OdGePoint2d& upper_right) const
  {
    OdGePoint3d target = m_pView->viewingMatrix() * m_pView->target();
    double halfFieldWidth = m_pView->fieldWidth() / 2.0;
    double halfFieldHeight = m_pView->fieldHeight() / 2.0;
    lower_left.x = target.x - halfFieldWidth;
    lower_left.y = target.y - halfFieldHeight;
    upper_right.x = target.x + halfFieldWidth;
    upper_right.y = target.y + halfFieldHeight;
  }
public:
  RTOrbitTracker()
    : m_pView(0)
    , m_D(0)
  {
  }
  void reset() { m_pView = 0; }
  void init(OdGsView* pView, const OdGePoint3d& pt)
  {
    m_pView = pView;
    m_pos = pView->position();
    m_trg = pView->target();
    m_up = pView->upVector();
    m_x = m_up.crossProduct(pView->target() - m_pos).normal();

    m_initViewingMatrixInv = m_pView->viewingMatrix();
    m_pt = m_initViewingMatrixInv * pt;
    m_pt.z = 0.;
    m_initViewingMatrixInv.invert();

    OdGePoint3d pt1;
    OdGePoint2d pt2;
    viewportDcCorners((OdGePoint2d&)pt1, pt2);
    pt2.x -= pt1.x;
    pt2.y -= pt1.y;
    double r = odmin(pt2.x, pt2.y) / 9. * 7. / 2.;
    m_D = 2.0 * r;
    ((OdGePoint2d&)pt1) += (pt2.asVector() / 2.);
    double r2sqrd = r*r / 400.;

    pt1.y += r;
    if((pt1 - m_pt).lengthSqrd() <= r2sqrd)
    {
      m_axis = kHorizontal;
    }
    else
    {
      pt1.y -= r;
      pt1.y -= r;
      if((pt1 - m_pt).lengthSqrd() <= r2sqrd)
      {
        m_axis = kHorizontal;
      }
      else
      {
        pt1.y += r;
        pt1.x += r;
        if((pt1 - m_pt).lengthSqrd() <= r2sqrd)
        {
          m_axis = kVertical;
        }
        else
        {
          pt1.x -= r;
          pt1.x -= r;
          if((pt1 - m_pt).lengthSqrd() <= r2sqrd)
          {
            m_axis = kVertical;
          }
          else
          {
            pt1.x += r;
            if((pt1 - m_pt).lengthSqrd() <= r*r)
            {
              m_axis = kPerpDir;
            }
            else
            {
              m_axis = kEye;
            }
          }
        }
      }
    }

    OdAbstractViewPEPtr pAView = pView;
    OdGeBoundBlock3d extents;

    OdPrcFilePtr pFile;
    
    if( pView->device() && 
        pView->device()->userGiContext() &&  
        pView->device()->userGiContext()->database() 
      )
    {
      pFile = pView->device()->userGiContext()->database();
    }

    bool bUpdateExtents = true;

    if( !pFile.isNull() )
    {
      OdGsCache* pNode = pFile->modelFileData().gsNode();

      if( pNode )
      {
        OdGeExtents3d extWCS;

        if( pNode->extents( extWCS ) )
        {
          extents.set( extWCS.minPoint(), extWCS.maxPoint() );
          extents.transformBy( pView->viewingMatrix() );
          bUpdateExtents = false;
        }
      }
    }
    
    if( bUpdateExtents )
    {
      pAView->viewExtents(pView, extents);
    }

    m_viewCenter = extents.center();
    m_viewCenter.transformBy(m_initViewingMatrixInv);
  }
  
  double angle(const OdGePoint3d& value) const
  {
    OdGePoint3d pt2 = m_pView->viewingMatrix() * value;
    double dist = 0.0;
    if(m_axis == kHorizontal)
      dist = pt2.y - m_pt.y;
    else if(m_axis == kVertical)
      dist = pt2.x - m_pt.x;
    return dist * OdaPI / m_D;
  }
  
  double angleZ(const OdGePoint3d& value) const
  {
    OdGePoint3d pt2 = m_pView->viewingMatrix() * value;
    OdGePoint3d targ = m_pView->viewingMatrix() * m_viewCenter;
    pt2.z = targ.z = m_pt.z;
    return (pt2 - targ).angleTo((m_pt - targ), OdGeVector3d::kZAxis);
  }

  double anglePerp(const OdGePoint3d& value) const
  {
    OdGePoint3d pt2 = m_pView->viewingMatrix() * value;
    pt2.z = 0.0;
    return pt2.distanceTo(m_pt) * OdaPI / m_D;
  }
  
  void setValue(const OdGePoint3d& value)
  {
    if(m_pView)
    {
      OdGeMatrix3d x;
      switch(m_axis)
      {
      case kHorizontal:
        x.setToRotation(-angle(value), m_x, m_viewCenter);
        break;
      case kVertical:
        x.setToRotation(-angle(value), m_up, m_viewCenter);
        break;
      case kEye:
        x.setToRotation(-angleZ(value), m_trg - m_pos, m_viewCenter);
        break;
      case kPerpDir:
        {
          OdGePoint3d value1 = value;
          value1.transformBy(m_pView->viewingMatrix());
          value1.z = 0.0;
          OdGeVector2d dir = (value1 - m_pt).convert2d();
          OdGeVector2d perp = dir.perpVector();
          OdGeVector3d perp3d(perp.x, perp.y, 0.0);
          perp3d.normalizeGetLength();
          perp3d.transformBy(m_initViewingMatrixInv);
          x.setToRotation(-anglePerp(value), perp3d, m_viewCenter);
          break;
        }
      }
      OdGePoint3d newPos = x * m_pos, newTarget = x * m_trg;
      OdGeVector3d newPosDir = newPos - newTarget;
      newPosDir.normalizeGetLength();
      newPosDir *= m_pos.distanceTo(m_trg);
      newPos = newTarget + newPosDir;

      m_pView->setView(newPos,
                       newTarget,
                       x * m_up,
                       m_pView->fieldWidth(),
                       m_pView->fieldHeight(),
                       m_pView->isPerspective() ? OdGsView::kPerspective : OdGsView::kParallel
                      );
    }
  }

  int addDrawables(OdGsView* pView)
  {
    m_pDrw = OdRxObjectImpl<OrbitCtrl>::createObject();
    if (m_pModel.isNull())
    {
      m_pModel = pView->device()->createModel();
      if (!m_pModel.isNull())
        m_pModel->setRenderType(OdGsModel::kDirect);
    }
    pView->add(m_pDrw, m_pModel.get());
    return 1;
  }

  void removeDrawables(OdGsView* pView)
  {
    pView->erase(m_pDrw);
  }
};

void OdExPrc3dOrbitCmd::execute(OdEdCommandContext* pCmdCtx)
{
  OdPrcCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdPrcFilePtr pDb = pDbCmdCtx->database();
  OdSmartPtr<OdEdBaseUserIO> pIO = pDbCmdCtx->userIO();
  
  OdGsView* pView = pDb->getActiveView();

  OdStaticRxObject<RTOrbitTracker> tracker;
  for(;;)
  {
    try
    {
      tracker.init(pView, pIO->getPoint(OD_T("Press ESC or ENTER to exit."),
          OdEd::kInpThrowEmpty|OdEd::kGptNoUCS|OdEd::kGptNoOSnap|OdEd::kGptBeginDrag, 
              0, OdString::kEmpty, &tracker));
      pIO->getPoint(OD_T("Press ESC or ENTER to exit."),
          OdEd::kInpThrowEmpty|OdEd::kGptNoUCS|OdEd::kGptNoOSnap|OdEd::kGptEndDrag, 
              0, OdString::kEmpty, &tracker);
      tracker.reset();
    }
    catch(const OdEdCancel)
    {
      break;
    }
  }
}

