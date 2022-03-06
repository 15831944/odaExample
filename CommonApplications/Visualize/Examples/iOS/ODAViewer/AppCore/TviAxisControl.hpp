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

#ifndef OD_TV_AXISCONTROL_H
#define OD_TV_AXISCONTROL_H

#include "TvGsView.h"

/** \details
Class for moving axis
*/
class OdTvUIAxisControl
{
public:
  OdTvUIAxisControl() : m_wcsScaleCoef(1.), m_bIsAttached(false), m_basePoint(OdTvPoint::kOrigin), m_xForm(OdTvMatrix::kIdentity), m_scaleForScaleMatrix(1.){}
  virtual ~OdTvUIAxisControl();

  //initialize
  void init(OdTvGsViewId& parentViewId);

  //attach control to the parent view
  virtual bool attach(const OdTvPoint& wcsPos);

  //returns true if the control is attached
  bool isAttached() const { return m_bIsAttached; }

  //remove control from the parent view
  void detach();

  //scale control according to the current view parameters
  virtual void scale();

  //mouse hover (return true if the highlighting is change)
  bool hover(int x, int y);

  //check that we have selected control
  bool hasSelectedControl() const { return !m_highlightedAxis.isNull(); }

  //start the controlling process
  void start(int x, int y);

  //finish the controlling process
  void finish();

  //get the new transform (method start should be called before)
  virtual bool getTransform(int x, int y, OdTvMatrix& xTrans);

  //highlight the appropriate axis
  void highlight(OdTvEntityId axisId, bool bHighlight);

private:

  //construct the axis geometry
  bool constructAxisGeometry(const OdString& name, const OdTvColorDef& color);

protected:

  //transfer point to WCS
  OdTvPoint toEyeToWorld(int x, int y) const;

  //transfrom + scale
  void applyCurrentTransform();

  // model for temp axis object
  OdTvModelId m_modelId;
  
  // view for display axis object
  OdTvGsViewId m_viewId;

  // view for display axis object
  OdTvGsViewId m_parentViewId;

  //insertion point
  OdTvPoint m_wcsInsertPoint;

  //scale coefficient to transfrom device -> WCS (first time)
  double m_wcsScaleCoef;

  //coefficient for the scale matrix
  double m_scaleForScaleMatrix;

  //indicate whether the control is attached ot not
  bool   m_bIsAttached;

  //currently highlighted axis
  OdTvEntityId m_highlightedAxis;
  OdTvColorDef m_unhighlightedAxisColor;

  // Base point for calculating the transform.
  OdTvPoint m_basePoint;

  // Last transformation.
  OdTvMatrix m_xForm;
};

/** \details
Class for rotation axis
*/
class OdTvUIRotationAxisControl : public OdTvUIAxisControl
{
public:
  OdTvUIRotationAxisControl() : OdTvUIAxisControl(){}
  virtual ~OdTvUIRotationAxisControl();

  //attach control to the parent view
  virtual bool attach(const OdTvPoint& wcsPos, const OdTvVector& uAxis, const OdTvVector& vAxis);

  //get the new transform (method start should be called before)
  virtual bool getTransform(int x, int y, OdTvMatrix& xTrans);

  //scale control according to the current view parameters
  void scale();

  //unhighlight control
  void unhighlight();

  //apply current transform matrix to rotation axis
  void applyTransformToAxis();

private:
  //construct the axis geometry
  bool constructAxisGeometry(const OdString& name, const OdTvColorDef& color, const OdTvVector& uAxis, const OdTvVector& vAxis);

protected:
  OdTvVector m_uAxis;
  OdTvVector m_vAxis;

  double m_dAxisWcsLength;
};

#endif //OD_TV_AXISCONTROL_H
