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
#include "OdaCommon.h"

#include "RxObjectImpl.h"

#include "ExGsSimpleDevice.h"
#include "GiDumperImpl.h"
#include "GiConveyorGeometryDumper.h"
#include "ColorMapping.h"
#include "toString.h"

#include "daiApplicationInstance.h"

ExGsSimpleDevice::ExGsSimpleDevice()
{
  /**********************************************************************/
  /* Set a palette with a white background.                             */
  /**********************************************************************/  
  const ODCOLORREF* palette = odcmAcadPalette(ODRGB(255, 255, 255));
  OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;

  pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);
  setLogicalPalette(pPalCpy.asArrayPtr(), 256);

  /**********************************************************************/
  /* Set the size of the vectorization window                           */
  /**********************************************************************/  
  onSize(OdGsDCRect(0,100,0,100));
}

OdGsDevicePtr ExGsSimpleDevice::createObject(DeviceType type)
{
  OdGsDevicePtr pRes = OdRxObjectImpl<ExGsSimpleDevice, OdGsDevice>::createObject();
  ExGsSimpleDevice* pMyDev = static_cast<ExGsSimpleDevice*>(pRes.get());

  pMyDev->m_type = type;

  /**********************************************************************/
  /* Create the output geometry dumper                                  */
  /**********************************************************************/  
  pMyDev->m_pDumper = OdGiDumperImpl::createObject();
  
  /**********************************************************************/
  /* Create the destination geometry receiver                           */
  /**********************************************************************/  
  pMyDev->m_pDestGeometry = OdGiConveyorGeometryDumper::createObject(pMyDev->m_pDumper);

  return pRes;
}

/************************************************************************/
/* Creates a new OdGsView object, and associates it with this Device    */
/* object.                                                              */
/*                                                                      */
/* pInfo is a pointer to the Client View Information for this Device    */
/* object.                                                              */
/*                                                                      */
/* bEnableLayerVisibilityPerView specifies that layer visibility        */
/* per viewport is to be supported.                                     */
/************************************************************************/  
OdGsViewPtr ExGsSimpleDevice::createView(const OdGsClientViewInfo* pInfo, 
                                         bool bEnableLayerVisibilityPerView)
{
  /**********************************************************************/
  /* Create a View                                                      */
  /**********************************************************************/
  OdGsViewPtr pView = ExSimpleView::createObject();
  ExSimpleView* pMyView = static_cast<ExSimpleView*>(pView.get());

  /**********************************************************************/
  /* This call is required by DD 1.13+                                  */
  /**********************************************************************/
  pMyView->init(this, pInfo, bEnableLayerVisibilityPerView);

  /**********************************************************************/
  /* Directs the output geometry for the view to the                    */
  /* destination geometry object                                        */
  /**********************************************************************/
  pMyView->output().setDestGeometry(*m_pDestGeometry);

  return (OdGsView*)pMyView;
} 

/************************************************************************/
/* Returns the geometry receiver associated with this object.           */
/************************************************************************/  
OdGiConveyorGeometry* ExGsSimpleDevice::destGeometry()
{
  return m_pDestGeometry;
}

/************************************************************************/
/* Returns the geometry dumper associated with this object.             */
/************************************************************************/  
OdGiDumper* ExGsSimpleDevice::dumper()
{
  return m_pDumper;
}

void ExSimpleView::ownerDrawDc(const OdGePoint3d& origin,
                               const OdGeVector3d& u,
                               const OdGeVector3d& v,
                               const OdGiSelfGdiDrawable* /*pDrawable*/,
                               bool dcAligned,
                               bool allowClipping)
{
  // ownerDrawDc is not conveyor primitive. It means we must take all rendering processings
  // (transforms) by ourselves
  OdGeMatrix3d eyeToOutput = eyeToOutputTransform();
  OdGePoint3d originXformed(eyeToOutput * origin);
  OdGeVector3d uXformed(eyeToOutput * u), vXformed(eyeToOutput * v);

  OdGiDumper* pDumper = device()->dumper();

  pDumper->output(OD_T("ownerDrawDc"));
  
  // It's shown only in 2d mode.
  if(mode() == OdGsView::k2DOptimized)
  {
    pDumper->pushIndent();
    pDumper->output(OD_T("origin xformed"), toString(originXformed));
    pDumper->output(OD_T("u xformed"),      toString(uXformed));
    pDumper->output(OD_T("v xformed"),      toString(vXformed));
    pDumper->output(OD_T("dcAligned"),      toString(dcAligned));//
    pDumper->output(OD_T("allowClipping"),  toString(allowClipping));
    pDumper->popIndent();
  }
}

/************************************************************************/
/* Called by the ODA Platform vectorization framework to update         */
/* the GUI window for this Device object                                */
/*                                                                      */
/* pUpdatedRect specifies a rectangle to receive the region updated     */
/* by this function.                                                    */
/*                                                                      */
/* The override should call the parent version of this function,        */
/* OdGsBaseVectorizeDevice::update().                                   */
/************************************************************************/
void ExGsSimpleDevice::update(OdGsDCRect* pUpdatedRect)
{
  OdGsBaseVectorizeDevice::update(pUpdatedRect);
}

/************************************************************************/
/* Called by each associated view object to set the current RGB draw    */
/* color.                                                               */
/************************************************************************/  
void ExGsSimpleDevice::draw_color(ODCOLORREF color)
{
  dumper()->output(OD_T("draw_color"), toRGBString(color));
}

/************************************************************************/
/* Called by each associated view object to set the current ACI draw    */
/* color.                                                               */
/************************************************************************/  
void ExGsSimpleDevice::draw_color_index(OdUInt16 colorIndex)
{
  dumper()->output(OD_T("draw_color_index"), toString(colorIndex));
}

/************************************************************************/
/* Called by each associated view object to set the current draw        */
/* lineweight and pixel width                                           */
/************************************************************************/  
void ExGsSimpleDevice::draw_lineWidth(OdDb::LineWeight weight, int pixelLineWidth)
{
  dumper()->output(OD_T("draw_lineWidth"));
  dumper()->pushIndent();
  dumper()->output(OD_T("weight"), toString(weight));
  dumper()->output(OD_T("pixelLineWidth"), toString(pixelLineWidth));
  dumper()->popIndent();
}


/************************************************************************/
/* Called by each associated view object to set the current Fill Mode   */
/************************************************************************/  
void ExGsSimpleDevice::draw_fill_mode(OdGiFillType fillMode)
{
  OdString strMode;
  switch (fillMode)
  {
  case kOdGiFillAlways:
    strMode = OD_T("FillAlways");
    break;
  case kOdGiFillNever:
    strMode = OD_T("FillNever");
  }
  dumper()->output(OD_T("draw_fill_mode"), strMode);
}

/************************************************************************/
/* Called by the ODA Platform vectorization framework to give the       */
/* client application a chance to terminate the current                 */
/* vectorization process.  Returning true from this function will       */
/* stop the current vectorization operation.                            */
/************************************************************************/

bool ExSimpleView::regenAbort() const
{
  // return true here to abort the vectorization process
  return false;  
}

/************************************************************************/
/* Called by the ODA Platform vectorization framework to vectorize      */
/* each entity in this view.  This override allows a client             */
/* application to examine each entity before it is vectorized.          */
/* The override should call the parent version of this function,        */
/* OdGsBaseVectorizeView::draw().                                       */
/************************************************************************/

void ExSimpleView::draw(const OdGiDrawable* pDrawable)
{
  OdDAIObjectId id = pDrawable->id();

  OdAnsiString typeName;

  OdDAI::ApplicationInstancePtr daiInstance = OdDAI::ApplicationInstance::cast(pDrawable);
  if (!daiInstance.isNull())
  {
    typeName = daiInstance->getInstanceType()->originalName();
    //if (daiInstance->isKindOf("ifcproduct"))
    //{
    //  OdDAIObjectId ifcProductId = id;
    //  if (ifcProductId.getHandle() == (OdUInt64)NNN)
    //  {
    //    bool breakPoint = true;
    //  }
    //}
  }

  OdString sClassName = toString(pDrawable->isA());
  OdString sInfo = OdString().format(OD_T("%s (#%lu=%hs)"), sClassName.c_str(), (OdUInt64)id.getHandle(), typeName.c_str());

  device()->dumper()->output(OD_T(""));
  device()->dumper()->output(OD_T("Start Drawing ") + sInfo);
  device()->dumper()->pushIndent();

  /**********************************************************************/
  /* The parent class version of this function must be called.          */
  /**********************************************************************/
  OdGsBaseVectorizer::draw(pDrawable);

  device()->dumper()->popIndent();
  device()->dumper()->output(OD_T("End Drawing ") + sClassName);
}

/************************************************************************/
/* Flushes any queued graphics to the display device.                   */
/************************************************************************/
void ExSimpleView::updateViewport()
{
  /**********************************************************************/
  /* If geometry receiver is a simplifier, we must re-set the draw      */
  /* context for it                                                     */
  /**********************************************************************/
  (static_cast<OdGiGeometrySimplifier*>(device()->destGeometry()))->setDrawContext(drawContext());

#define _NO_CLIPPING
#ifdef _NO_CLIPPING

  OdGsBaseVectorizer::updateViewport();
  return;

#else

  /**********************************************************************/
  /* Comment these functions to get primitives in eye coordinates.      */
  /**********************************************************************/
  OdGeMatrix3d eye2Screen(eyeToScreenMatrix());
  OdGeMatrix3d screen2Eye(eye2Screen.inverse());
  setEyeToOutputTransform(eye2Screen);

  // perform viewport clipping in eye coordinates:

  /**********************************************************************/
  /* Perform viewport clipping in eye coordinates.                      */
  /**********************************************************************/
  m_eyeClip.m_bClippingFront = isFrontClipped();
  m_eyeClip.m_bClippingBack = isBackClipped();
  m_eyeClip.m_dFrontClipZ = frontClip();
  m_eyeClip.m_dBackClipZ = backClip();
  m_eyeClip.m_vNormal = viewDir();
  m_eyeClip.m_ptPoint = target();
  m_eyeClip.m_Points.clear();

  OdGeVector2d halfDiagonal(fieldWidth() / 2.0, fieldHeight() / 2.0);
  
  OdIntArray nrcCounts;
  OdGePoint2dArray nrcPoints;
  viewportClipRegion(nrcCounts, nrcPoints);
  if(nrcCounts.size() == 1) // polygons aren't supported yet
  {
    // polygonal clipping
    int i;
    for(i = 0; i < nrcCounts[0]; i ++)
    {
      OdGePoint3d screenPt(nrcPoints[i].x, nrcPoints[i].y, 0.0);
      screenPt.transformBy(screen2Eye);
      m_eyeClip.m_Points.append(OdGePoint2d(screenPt.x, screenPt.y));
    }
  }
  else
  {
    // rectangular clipping
    m_eyeClip.m_Points.append(OdGePoint2d::kOrigin - halfDiagonal);
    m_eyeClip.m_Points.append(OdGePoint2d::kOrigin + halfDiagonal);
  }

  m_eyeClip.m_xToClipSpace = getWorldToEyeTransform();
  
  pushClipBoundary(&m_eyeClip);

  OdGsBaseVectorizer::updateViewport();

  popClipBoundary();

#endif
} // end ExSimpleView::updateViewport()


/****************************************************************************/
/* Notification function called by the vectorization framework              */
/* whenever the rendering attributes have changed.                          */
/*                                                                          */
/* Retrieves the current vectorization traits from ODA Drawings SDK (color  */
/* lineweight, etc.) and sets them in this device.                          */
/****************************************************************************/
void ExSimpleView::onTraitsModified()
{
  OdGsBaseVectorizer::onTraitsModified();
  const OdGiSubEntityTraitsData& currTraits = effectiveTraits();
  if(currTraits.trueColor().isByColor())
  {
    device()->draw_color(ODTOCOLORREF(currTraits.trueColor()));
  }
  else
  {
    device()->draw_color_index(currTraits.color());
  }

  OdDb::LineWeight lw = currTraits.lineWeight();
  device()->draw_lineWidth(lw, lineweightToPixels(lw));
  device()->draw_fill_mode(currTraits.fillType());

} // end ExSimpleView::onTraitsModified()


void ExSimpleView::beginViewVectorization()
{
  OdGsBaseVectorizer::beginViewVectorization();
  device()->setupSimplifier( &m_pModelToEyeProc->eyeDeviation() );
}

void ExGsSimpleDevice::setupSimplifier(const OdGiDeviation* pDeviation)
{
  m_pDestGeometry->setDeviation(pDeviation);
}


//==========================================================================================
