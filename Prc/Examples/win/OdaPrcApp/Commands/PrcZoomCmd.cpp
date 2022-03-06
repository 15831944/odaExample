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
#include "PrcZoomCmd.h"
#include "AbstractViewPE.h"


const OdString OdExPrcZoomCmd::groupName() const
{
  return globalName();
}

const OdString OdExPrcZoomCmd::globalName() const
{
  return OD_T("ZOOM");
}

void zoom_window(OdGePoint3d& pt1, OdGePoint3d& pt2, OdGsView* pView)
{
  OdGeMatrix3d xWorldToEye = OdAbstractViewPEPtr(pView)->worldToEye(pView);
  pt1.transformBy(xWorldToEye);
  pt2.transformBy(xWorldToEye);
  OdGeVector3d eyeVec = pt2 - pt1;
  if(OdNonZero(eyeVec.x) && OdNonZero(eyeVec.y))
  {
    OdGePoint3d newPos = pt1 + eyeVec / 2.;
    
    eyeVec.x = fabs(eyeVec.x);
    eyeVec.y = fabs(eyeVec.y);
    
    pView->dolly( newPos.asVector() );
    
    double wf = pView->fieldWidth()  / eyeVec.x;
    double hf = pView->fieldHeight() / eyeVec.y;
    
    pView->zoom(odmin(wf, hf));
  }
}

void zoom_scale(double factor)
{
}

void zoom_extents(OdGsView* pView, OdPrcReferencedBase* pVpObj)
{
  OdAbstractViewPEPtr pVpPE(pView);
  OdGeBoundBlock3d bbox;

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
        bbox.set( extWCS.minPoint(), extWCS.maxPoint() );
        bbox.transformBy( pView->viewingMatrix() );
        bUpdateExtents = false;
      }
    }
  }

  if( bUpdateExtents )
  {
    bool bBboxValid = pVpPE->viewExtents(pView, bbox);
  }

  pVpPE->zoomExtents(pView, &bbox);
}

// Zoom command

class RTZoomTracker : public OdEdPointTracker
{
  OdGsView*   m_pView;
  double      m_base;
  double      m_fw;
  double      m_fh;
public:
  void init(OdGsView* pView, const OdGePoint3d& base)
  {
    m_pView = pView;
    m_fw = pView->fieldWidth();
    m_fh = pView->fieldHeight();
    m_base = (m_pView->projectionMatrix() * m_pView->viewingMatrix() * base).y;
  }

  void setValue(const OdGePoint3d& value)
  {
    OdGeMatrix3d xWorldToNDC = m_pView->projectionMatrix() * m_pView->viewingMatrix();
    OdGePoint3d pt2 = xWorldToNDC * value;
    double fac = 1. + fabs(pt2.y - m_base) * 1.5;
    if(pt2.y > m_base)
      fac = 1./fac;
    m_pView->setView(m_pView->position(),
                     m_pView->target(),
                     m_pView->upVector(),
                     m_fw * fac,
                     m_fh * fac,
                     m_pView->isPerspective() ? OdGsView::kPerspective : OdGsView::kParallel
                    );
  }
  int addDrawables(OdGsView* /*pView*/) { return 1; }
  void removeDrawables(OdGsView* pView) {}
};

void OdExPrcZoomCmd::execute(OdEdCommandContext* pCmdCtx)
{
  OdPrcCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdPrcFilePtr pDb = pDbCmdCtx->database();
  OdSmartPtr<OdEdBaseUserIO> pIO = pDbCmdCtx->userIO();
  
  OdGsView* pView = pDb->getActiveView();
  
  const OdChar* szKeywords = OD_T("All Center Dynamic Extents Previous Scale Window Object");
  OdGePoint3d pt1, pt2;

  try
  {
    pt1 = pIO->getPoint(L"Specify corner of window, enter a scale factor (nX or nXP), or\n"
      L"[All/Center/Dynamic/Extents/Previous/Scale/Window/Object] <real time>:",
      OdEd::kInpThrowEmpty|OdEd::kInpThrowOther|OdEd::kGptNoOSnap, 0, szKeywords);
    
    pt2 = pIO->getPoint(OD_T("Specify opposite corner:"), 
        OdEd::kGptNoUCS|OdEd::kGptRectFrame|OdEd::kGptNoOSnap);
    zoom_window(pt1, pt2, pView);
  }
  catch(const OdEdEmptyInput) // real time
  {
    OdStaticRxObject<RTZoomTracker> tracker;
    for(;;)
    {
      try
      {
        tracker.init(pView, pIO->getPoint(OD_T("Press ESC or ENTER to exit."),
          OdEd::kInpThrowEmpty|OdEd::kGptNoUCS|OdEd::kGptBeginDrag|OdEd::kGptNoOSnap));
        pIO->getPoint(OD_T("Press ESC or ENTER to exit."),
          OdEd::kInpThrowEmpty|OdEd::kGptNoUCS|OdEd::kGptEndDrag|OdEd::kGptNoOSnap, 0, OdString::kEmpty, &tracker);
      }
      catch(const OdEdCancel)
      {
        break;
      }
    }
  }
  catch(const OdEdOtherInput& otherInput) // nX or nXP
  {
    OdChar* pEnd;
    double scale = odStrToD(otherInput.string(), &pEnd);
    if(pEnd > otherInput.string().c_str())
    {
      OdString sEnd(pEnd);
      if(sEnd.iCompare(OD_T("X"))==0)
      {
        pView->zoom(scale);
      }
      else if(!*pEnd)
      {
        pView->zoom(scale);
      }
    }
    pIO->putString(OD_T("Requires a distance, numberX, or option keyword."));
  }
  catch(const OdEdKeyword& kw)
  {
    switch(kw.keywordIndex())
    {
    case 0: // All
      break;
    case 1: // Center
      break;
    case 2: // Dynamic
      break;
    case 3: // Extents
      ::zoom_extents(pView, 0);
      break;
    case 4: // Previous
      break;
    case 5: // Scale
      break;
    case 6: // Window
      pt1 = pIO->getPoint(OD_T("Specify first corner:"),    OdEd::kGptNoUCS|OdEd::kGptNoOSnap);
      pt2 = pIO->getPoint(OD_T("Specify opposite corner:"), OdEd::kGptNoUCS|OdEd::kGptNoOSnap|OdEd::kGptRectFrame);
      ::zoom_window(pt1, pt2, pView);
      break;
    case 7: // Object
      break;
    }
  }

  //pAVD->setView(pVpObj, pView);
}
