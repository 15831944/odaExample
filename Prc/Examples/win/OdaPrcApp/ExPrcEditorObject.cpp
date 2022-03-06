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

#include "PrcCommon.h"
#include "Gi/GiDrawableImpl.h"
#include "Gi/GiWorldDraw.h"
#include "Gs/Gs.h"
#include "Gs/GsBaseVectorizer.h"
#include "ExPrcEditorObject.h"
#include "AbstractViewPE.h"
#include "Ge/GeLine3d.h"

static const int SNAP_SIZE = 10;

// 
// void setWorkingSelectionSet(OdDbCommandContext* pCmdCtx, OdDbSelectionSet* pSSet)
// {
//   pCmdCtx->setArbitraryData(OD_T("OdaMfcApp Working Selection Set"), pSSet);
// }

// OdDbSelectionSetPtr workingSelectionSet(OdDbCommandContext* pCmdCtx)
// {
//   OdDbSelectionSetPtr pRes;
//   if (pCmdCtx)
//   {
//     pRes = pCmdCtx->arbitraryData(OD_T("OdaMfcApp Working Selection Set"));
//     if(pRes.isNull())
//     {
//       pRes = OdDbSelectionSet::createObject(pCmdCtx->database());
//       setWorkingSelectionSet(pCmdCtx, pRes);
//     }
//   }
//   return pRes;
// }


class XFormDrawable : public OdGiDrawableImpl<OdGiDrawable>
{
  OdGiDrawablePtr     m_pDrawable;
  const OdGeMatrix3d* m_pXForm;
protected:
  XFormDrawable() : m_pXForm(0) {}
public:
  static OdGiDrawablePtr createObject(OdGiDrawable* pDrawable, const OdGeMatrix3d& xForm)
  {
    OdSmartPtr<XFormDrawable> pRes = OdRxObjectImpl<XFormDrawable>::createObject();
    pRes->m_pDrawable = pDrawable;
    pRes->m_pXForm = &xForm;
    return pRes;
  }

  OdUInt32 subSetAttributes(OdGiDrawableTraits* ) const
  {
    return kDrawableUsesNesting;
  }

  bool subWorldDraw(OdGiWorldDraw* pWd) const
  {
    OdGiModelTransformSaver mt(pWd->geometry(), *m_pXForm);
    pWd->geometry().draw(m_pDrawable);
    return true;
  }

  void subViewportDraw(OdGiViewportDraw* ) const {}
};


OdExPrcEditorObject::OdExPrcEditorObject()
: m_bSnapOn(true)
, m_pCmdCtx(0)
{
}

void OdExPrcEditorObject::initialize( OdGsDevice* pDevice, OdPrcCommandContext* pCmdCtx )
{
  m_pDevice = pDevice;
  m_pCmdCtx = pCmdCtx;

  m_p2dModel = pDevice->createModel();

  if (!m_p2dModel.isNull())
    m_p2dModel->setRenderType(OdGsModel::kDirect); // Skip Z-buffer for 2d drawables

//  m_gripManager.init( pDevice, m_p2dModel, pCmdCtx, workingSelectionSet );
}

void OdExPrcEditorObject::uninitialize()
{
//   OdDbSelectionSetPtr pSSet = workingSSet();
//   if(pSSet.get())
//   {
//     pSSet->clear();
// //    m_gripManager.selectionSetChanged(pSSet);
//   }
//  m_gripManager.uninit();

  m_pDevice.release();
  m_pCmdCtx = 0;
}

void OdExPrcEditorObject::initSnapping( OdGsView* pView )
{
//  pView->add(&m_osnapMan, m_p2dModel);
}

void OdExPrcEditorObject::uninitSnapping( OdGsView* pView )
{
//  pView->erase(&m_osnapMan);
}

// OdDbSelectionSetPtr OdExPrcEditorObject::workingSSet() const
// {
//   return workingSelectionSet(m_pCmdCtx);
// }

// void OdExPrcEditorObject::setWorkingSSet(OdDbSelectionSet* pSSet)
// {
//   setWorkingSelectionSet(m_pCmdCtx, pSSet);
// }

// void OdExPrcEditorObject::selectionSetChanged()
// {
// //  m_gripManager.selectionSetChanged(workingSSet());
// }

const OdGsView* OdExPrcEditorObject::activeView() const
{
  return m_pDevice->activeView();
}

OdGsView* OdExPrcEditorObject::activeView()
{
  return m_pDevice->activeView();
}

const OdGsView* OdExPrcEditorObject::activeTopView() const
{
//   const OdGsView *pView = activeView();
//   if (!m_pCmdCtx->database()->getTILEMODE())
//   {
//     OdDbObjectPtr pVpObj = m_pCmdCtx->database()->activeViewportId().safeOpenObject();
//     OdDbAbstractViewportDataPtr pAVD(pVpObj);
//     if (!pAVD.isNull() && pAVD->gsView(pVpObj))
//       pView = pAVD->gsView(pVpObj);
//   }
//   return pView;
  return 0;
}

OdGsView* OdExPrcEditorObject::activeTopView()
{
//   OdGsView *pView = activeView();
//   if (!m_pCmdCtx->database()->getTILEMODE())
//   {
//     OdDbObjectPtr pVpObj = m_pCmdCtx->database()->activeViewportId().safeOpenObject();
//     OdDbAbstractViewportDataPtr pAVD(pVpObj);
//     if (!pAVD.isNull() && pAVD->gsView(pVpObj))
//       pView = pAVD->gsView(pVpObj);
//   }
//   return pView;
  return 0;
}

OdPrcObjectId OdExPrcEditorObject::activeVpId() const
{
  OdGsClientViewInfo vi;
  ((OdGsView*)activeView())->clientViewInfo(vi);
  return OdPrcObjectId(vi.viewportObjectId);
}

void OdExPrcEditorObject::ucsPlane(OdGePlane& plane) const
{
//   OdDbObjectPtr pVpObj = activeVpId().safeOpenObject();
//   OdDbAbstractViewportDataPtr pAVD(pVpObj);
//   OdGePoint3d ucsOrigin;
//   OdGeVector3d ucsXAxis, ucsYAxis;
//   pAVD->getUcs(pVpObj, ucsOrigin, ucsXAxis, ucsYAxis);
//   double dElevation = pAVD->elevation(pVpObj);
//   if (!OdZero(dElevation))
//   {
//     OdGeVector3d vElevation = ucsXAxis.crossProduct(ucsYAxis) * dElevation;
//     ucsOrigin += vElevation;
//   }
//   plane.set(ucsOrigin, ucsXAxis, ucsYAxis);
}

OdGePoint3d OdExPrcEditorObject::toEyeToWorld(int x, int y) const
{
  OdGePoint3d wcsPt(x, y, 0.0);
  const OdGsView* pView = activeView();
  if (pView->isPerspective())
  {
    wcsPt.z = pView->projectionMatrix()(2,3);
  }
  wcsPt.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
  wcsPt.z =0.;
  // eye CS at this point.

  wcsPt.transformBy(OdAbstractViewPEPtr(pView)->eyeToWorld(pView)); 
  return wcsPt;
}

bool OdExPrcEditorObject::toUcsToWorld(OdGePoint3d& wcsPt) const
{
  const OdGsView* pView = activeView();
  OdGeLine3d line(wcsPt, OdAbstractViewPEPtr(pView)->direction(pView));
  OdGePlane plane;
  ucsPlane(plane);
  return plane.intersectWith(line, wcsPt);
}

OdGePoint3d OdExPrcEditorObject::toScreenCoord(int x, int y) const
{
  OdGePoint3d scrPt(x, y, 0.0);
  const OdGsView* pView = activeView();
  scrPt.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
  scrPt.z =0.;
  return scrPt;
}

OdGePoint3d OdExPrcEditorObject::toScreenCoord(const OdGePoint3d &wcsPt) const
{
  // To DCS
  OdGePoint3d scrPt(wcsPt);
  const OdGsView* pView = activeView();
  OdGsClientViewInfo viewInfo;
  pView->clientViewInfo(viewInfo);
  OdRxObjectPtr pObj = OdPrcObjectId(viewInfo.viewportObjectId).openObject();
  OdAbstractViewPEPtr pVp(pObj);
  OdGeVector3d vecY = pVp->upVector(pObj);
  OdGeVector3d vecZ = pVp->direction(pObj);
  OdGeVector3d vecX = vecY.crossProduct(vecZ).normal();
  OdGeVector2d offset = pVp->viewOffset(pObj);
  OdGePoint3d prTarg = pVp->target(pObj) - vecX * offset.x - vecY * offset.y;
  scrPt.x = vecX.dotProduct(wcsPt - prTarg);
  scrPt.y = vecY.dotProduct(wcsPt - prTarg);
  scrPt.z =0.;
  return scrPt;
}

unsigned OdExPrcEditorObject::getSnapModes() const
{
//  return m_osnapMan.snapModes();
  return 0;
}

void OdExPrcEditorObject::setSnapModes( bool bSnapOn, unsigned dwSnapModes )
{
  m_bSnapOn = bSnapOn;
//  m_osnapMan.setSnapModes( dwSnapModes );
}

OdEdCommandPtr OdExPrcEditorObject::command(const OdString& sCmdName)
{
  if(sCmdName==m_cmd_ZOOM.globalName())
    return &m_cmd_ZOOM;
  if(sCmdName==m_cmd_3DORBIT.globalName())
    return &m_cmd_3DORBIT;
  if(sCmdName==m_cmd_DOLLY.globalName())
    return &m_cmd_DOLLY;
  return OdEdCommandPtr();
}

void OdExPrcEditorObject::set3DView(_3DViewType type)
{
//   OdGePoint3d position, target = OdGePoint3d::kOrigin;
//   OdGeVector3d axis;
//   switch (type)
//   {
//   case k3DViewTop:
//     position = OdGePoint3d::kOrigin + OdGeVector3d::kZAxis;
//     axis = OdGeVector3d::kYAxis;
//     break;
//   case k3DViewBottom:
//     position = OdGePoint3d::kOrigin - OdGeVector3d::kZAxis;
//     axis = OdGeVector3d::kYAxis;
//     break;
//   case k3DViewLeft:
//     position = OdGePoint3d::kOrigin - OdGeVector3d::kXAxis;
//     axis = OdGeVector3d::kZAxis;
//     break;
//   case k3DViewRight:
//     position = OdGePoint3d::kOrigin + OdGeVector3d::kXAxis;
//     axis = OdGeVector3d::kZAxis;
//     break;
//   case k3DViewFront:
//     position = OdGePoint3d::kOrigin - OdGeVector3d::kYAxis;
//     axis = OdGeVector3d::kZAxis;
//     break;
//   case k3DViewBack:
//     position = OdGePoint3d::kOrigin + OdGeVector3d::kYAxis;
//     axis = OdGeVector3d::kZAxis;
//     break;
//   case k3DViewSW:
//     position = OdGePoint3d::kOrigin + OdGeVector3d(-1.0, -1.0, 1.0);
//     axis = OdGeVector3d(0.5, 0.5, 1.0).normal();
//     break;
//   case k3DViewSE:
//     position = OdGePoint3d::kOrigin + OdGeVector3d(1.0, -1.0, 1.0);
//     axis = OdGeVector3d(-0.5, 0.5, 1.0).normal();
//     break;
//   case k3DViewNE:
//     position = OdGePoint3d::kOrigin + OdGeVector3d(1.0, 1.0, 1.0);
//     axis = OdGeVector3d(-0.5, -0.5, 1.0).normal();
//     break;
//   case k3DViewNW:
//     position = OdGePoint3d::kOrigin + OdGeVector3d(-1.0, 1.0, 1.0);
//     axis = OdGeVector3d(0.5, -0.5, 1.0).normal();
//     break;
//   };
// 
//   unselect();
// 
//   OdGsView* pView = activeView();
// 
//   { // #7727
//     OdGsClientViewInfo cliInfo;
//     pView->clientViewInfo(cliInfo);
//     OdDbObjectPtr pObject = OdPrcObjectId(cliInfo.viewportObjectId).safeOpenObject(::kForWrite);
//     OdAbstractViewPEPtr(pObject)->setUcs(pObject, target, axis.crossProduct(position.asVector()), axis);
//   }
// 
//   pView->setView(position, target, axis, pView->fieldWidth(), pView->fieldHeight(),
//     (pView->isPerspective()) ? OdGsView::kPerspective : OdGsView::kParallel);
}

bool OdExPrcEditorObject::snap(OdGePoint3d& pt, const OdGePoint3d* pLastPt)
{
//   if ( m_bSnapOn )
//   {
//     if(m_osnapMan.snap( activeView(), pt, pLastPt ))
//     {
//       if (!m_p2dModel.isNull())
//         m_p2dModel->onModified(&m_osnapMan, (OdGiDrawable*)0);
//       return true;
//     }
//   }
  return false;
}

bool OdExPrcEditorObject::unselect()
{
  bool bRes = false;
//   OdDbSelectionSetPtr pSSet = workingSSet();
//   OdDbSelectionSetIteratorPtr pIter = pSSet->newIterator();
//   while ( !pIter->done() )
//   {
//     OdDbEntityPtr pEnt = OdDbEntity::cast(pIter->objectId().openObject());
//     if( pEnt.get() )
//     {
//       pEnt->highlight(false);
//       bRes = true;
//     }
//     pIter->next();
//   }
//   // Don't clear working selection set to prevent previous selection modification
//   //pSSet->clear();
//   pSSet = OdDbSelectionSet::createObject(pSSet->database());
//   setWorkingSelectionSet(m_pCmdCtx, pSSet);
//   m_gripManager.selectionSetChanged(pSSet);
  return bRes;
}

bool OdExPrcEditorObject::OnCtrlClick()
{
  return 0;//m_gripManager.onControlClick();
}

bool OdExPrcEditorObject::OnMouseLeftButtonClick(unsigned int nFlags, int x, int y,
                                              OleDragCallback* pDragCallback)
{
//   bool bShift = (OdEdBaseIO::kShiftIsDown & nFlags) != 0;
//   bool bCtrl = (OdEdBaseIO::kControlIsDown & nFlags) != 0;
//   OdGePoint3d pt = toEyeToWorld(x, y);
// 
// //   if ( m_gripManager.onMouseDown( x, y, bShift ) )
// //     return true;
// 
//   try
//   {
//     // Should be here I guess.
//     if ( pDragCallback && !bShift )
//     {
//       OdDbSelectionSetPtr pWorkSet = workingSSet();
//       OdDbSelectionSetPtr pAtPointSet = OdDbSelectionSet::select( activeVpId(), 1, &pt, OdDbVisualSelection::kPoint, bCtrl ? OdDbVisualSelection::kEnableSubents:OdDbVisualSelection::kDisableSubents );
//       OdDbSelectionSetIteratorPtr pIter = pAtPointSet->newIterator();
//       while( !pIter->done() )
//       {
//         if( pWorkSet->isMember( pIter->objectId() ) && !bCtrl )
//         {
//           pIter.release();
//           break;
//         }
//         pIter->next();
//       }
//       if( pIter.isNull() )
//       {
//         if( pDragCallback->beginDragCallback( pt ) )
//         {
//           // Not good idea to clear selection set if already selected object has been selected, but if selection
//           // set is being cleared - items must be unhighlighted too.
//           //workingSSet()->clear();
//           //selectionSetChanged();
//           unselect();
//           return( true );
//         }
//       }
//     }
//   }
//   catch( const OdError& )
//   {
//     return( false );
//   }
// 
//   OdDbUserIO* pIO = m_pCmdCtx->dbUserIO();
//   pIO->setLASTPOINT( pt );
//   pIO->setPickfirst( 0 );
// 
//   int iOpt = OdEd::kSelPickLastPoint | OdEd::kSelSinglePass | OdEd::kSelLeaveHighlighted | OdEd::kSelAllowInactSpaces;
//   if ( bShift )
//   {
//     if (m_pCmdCtx->database()->appServices()->getPICKADD() > 0)
//       iOpt |= OdEd::kSelRemove;
//   }
//   else
//   {
//     if (m_pCmdCtx->database()->appServices()->getPICKADD() == 0)
//       unselect();
//   }
//   if (bCtrl)
//   {
//     iOpt |= OdEd::kSelAllowSubents;
//   }
// 
//   OdDbSelectionSetPtr pSSet;
//   try
//   {
//     OdSaveState<bool> ss_m_bSnapOn(m_bSnapOn, false);
//     pSSet = pIO->select( OdString::kEmpty, iOpt, workingSSet() );
//     setWorkingSSet( pSSet );
//   }
//   catch( const OdError& )
//   {
//     return( false );
//   }
//   selectionSetChanged();

  return true;
}

bool OdExPrcEditorObject::OnMouseLeftButtonDoubleClick(unsigned int nFlags, int x, int y)
{
//   OdGsView* pView = activeView();
//   m_pDevice->setActiveViewport(OdGePoint2d(x, y));
//   bool bChanged = pView!=activeView();
//   if (bChanged)
//   {
//     // @@@ probably move this code to GsLayoutHelper's?
//     OdDbObjectPtr pObj = activeVpId().safeOpenObject();
//     OdDbDatabase *pDb = pObj->database();
//     if (pDb->getTILEMODE())
//       OdDbViewportTable::cast(pDb->getViewportTableId().safeOpenObject(::kForWrite))->SetActiveViewport(activeVpId());
//     else
//       OdDbLayout::cast(OdDbBlockTableRecord::cast(pDb->getPaperSpaceId().safeOpenObject())->getLayoutId().safeOpenObject(::kForWrite))->setActiveViewportId(activeVpId());
//     unselect();
//   }
//   return bChanged;
  return false;
}

bool OdExPrcEditorObject::OnMouseRightButtonDoubleClick(unsigned int nFlags, int x, int y) 
{
  unselect();

  OdGsView* pView = activeView();

  // set target to center of the scene, keep view direction:
  OdGePoint3d targ = pView->target();

  pView->setView(targ + OdGeVector3d::kZAxis, targ, OdGeVector3d::kYAxis, pView->fieldWidth(), pView->fieldHeight());

  return true;
}

bool OdExPrcEditorObject::OnMouseMove(unsigned int nFlags, int x, int y)
{
  return 0;//m_gripManager.onMouseMove( x, y );
  //  if ( hasSelection() && m_pGripPoints.get() )
  //  {
  //    OdGsView* pView = activeView();
  //    bool bRes = m_pGripPoints->onMouseMove( OdGePoint2d(x, y), pView->worldToDeviceMatrix() );
  //    if( bRes )
  //    {
  //#pragma MARKMESSAGE(Rect of active grip point should be passed in OdGsView::invalidate())
  //      pView->invalidate();
  //    }
  //    return bRes;
  //  }
  //  return false;
}

void OdExPrcEditorObject::dolly(int x, int y) 
{
  OdGsView* pView = activeView();
  OdGeVector3d vec(-x, -y, 0.0);
  vec.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
  pView->dolly(vec);
}

bool OdExPrcEditorObject::OnMouseWheel(unsigned int nFlags, int x, int y, short zDelta)
{
  OdGsView* pView = activeView();

  OdGePoint3d pos(pView->position());
  pos.transformBy(pView->worldToDeviceMatrix());
  // In 2d mode perspective zoom change lens length instead of fieldWidth/fieldHeight. This is non-standart
  // mode. Practically 2d mode can't be perspective.
  if (pView->isPerspective() && pView->mode() == OdGsView::k2DOptimized)
    pos = OdGePoint3d(0.5, 0.5, 0.0).transformBy(pView->screenMatrix());
  int vx, vy;
  vx = (int)OdRound(pos.x);
  vy = (int)OdRound(pos.y);
  vx = x - vx;
  vy = y - vy;
  dolly(-vx, -vy);
  pView->zoom(zDelta > 0 ? 1./.9 : .9);
  dolly(vx, vy);

  if (!m_p2dModel.isNull())
    m_p2dModel->invalidate(activeTopView());
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0

void CDwgViewer::startDragDrop()
{
//   OdDbSelectionSet& ss = static_cast<COdaMfcAppDoc*>(GetDocument())->cmdCtx()->selectionSet();
//   if ( ss.numEntities() )
//   {
//     OdDbSelectionSetPtr tmp = OdDbSelectionSet::createObject(static_cast<COdaMfcAppDoc*>(GetDocument())->m_pDb);
//     static const int SNAP_SIZE = 10;
//     CRect rc( m_startPoint, m_startPoint ); rc.InflateRect(-SNAP_SIZE,SNAP_SIZE);
//     m_editor.selectObjects( getActiveView(), m_layoutId, (OdGsDCPoint*)&rc,2,OdGsView::kCrossing,*tmp);
//     if ( !tmp->numEntities() )
//       return;
// 
//     OdGePoint3d p1,p2;
//     getWorldStartEndPoints(p1,p2);
// 
//     COleDataSource ds; 
//     OdString tmpPath = static_cast<COdaMfcAppDoc*>(GetDocument())->CreateDataSource( ds, p2 );
//     m_interactionMode = kDragDrop;
//     if ( ds.DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_MOVE) != DROPEFFECT_NONE  )
//     {
//       m_editor.unselect( getActiveView() );
//       //OnViewerRegen();
//       RedrawWindow();
//     }
//     m_interactionMode = kNone;
//     DeleteFile( tmpPath );
//   }
}

#endif 
