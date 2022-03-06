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

#ifndef _PRCEditorObject_h_Included_
#define _PRCEditorObject_h_Included_

#include "Ed/EdCommandStack.h"
#include "StaticRxObject.h"

#include "Commands/PrcZoomCmd.h"
#include "Commands/PrcDollyCmd.h"
#include "Commands/PrcOrbit3dCmd.h"

#include "GiGs/PrcGsManager.h"

class OdExPrcEditorObject
{

  OdGsPrcLayoutHelperPtr     m_pDevice;
  bool                    m_bSnapOn;
//  OdStaticRxObject<OSnapManager>
//    m_osnapMan;
//  OdStaticRxObject<OdExGripManager> 
//    m_gripManager;
  OdGsModelPtr            m_p2dModel;
  OdPrcCommandContext*     m_pCmdCtx;

  OdStaticRxObject<OdExPrcZoomCmd>
    m_cmd_ZOOM;
  OdStaticRxObject<OdExPrc3dOrbitCmd>
    m_cmd_3DORBIT;
  OdStaticRxObject<OdExPrcDollyCmd>
    m_cmd_DOLLY;

  void transformSSetBy(const OdGeMatrix3d& xfm);

  const OdGsView* activeView() const;
  OdGsView* activeView();
  const OdGsView* activeTopView() const;
  OdGsView* activeTopView();
  OdPrcObjectId activeVpId() const;
  void ucsPlane(OdGePlane& plane) const;
  void dolly(int x, int y);

public:
  enum _3DViewType
  {
    k3DViewTop,
    k3DViewBottom,
    k3DViewLeft,
    k3DViewRight,
    k3DViewFront,
    k3DViewBack,
    k3DViewSW,
    k3DViewSE,
    k3DViewNE,
    k3DViewNW
  };
  void set3DView(_3DViewType type);
public:
  OdExPrcEditorObject();

  void initialize( OdGsDevice* pDevice, OdPrcCommandContext* pCmdCtx );
  void uninitialize();

//   OdDbSelectionSetPtr workingSSet() const;
//   void setWorkingSSet(OdDbSelectionSet* pSSet);
//   void selectionSetChanged();

  OdGiDrawablePtr snapDrawable() const;
  bool unselect();

  OdEdCommandPtr command(const OdString& sCmdName);

  OdGePoint3d toEyeToWorld(int x, int y) const;
  bool toUcsToWorld(OdGePoint3d& wcsPt) const;
  OdGePoint3d toScreenCoord(int x, int y) const;
  OdGePoint3d toScreenCoord(const OdGePoint3d& wcsPt) const;

  class OleDragCallback
  {
  public:
    virtual bool beginDragCallback(const OdGePoint3d& pt) = 0;
  };
  bool   OnMouseLeftButtonClick       (unsigned int nFlags, int x, int y, OleDragCallback* pDragCallback = 0);
  bool   OnMouseMove                  (unsigned int nFlags, int x, int y);
  bool   OnMouseWheel                 (unsigned int nFlags, int x, int y, short zDelta);
  bool   OnMouseLeftButtonDoubleClick (unsigned int nFlags, int x, int y);
  bool   OnMouseRightButtonDoubleClick(unsigned int nFlags, int x, int y);
  bool   OnCtrlClick();

//  bool hasSelection() const { return (workingSSet()->numEntities()>0); }
  bool isSnapOn() const { return m_bSnapOn; }
  bool snap(OdGePoint3d& pt, const OdGePoint3d* pLastPt);
  unsigned getSnapModes() const;
  void setSnapModes( bool bSnapOn, unsigned modes );
  void resetSnapManager();
  void initSnapping( OdGsView* pView );
  void uninitSnapping( OdGsView* pView );

  inline OdGsModel *gsModel() { return m_p2dModel.get(); }

//   void Recalc_Entity_centers(void)
//   {
// //    m_osnapMan.Recalc_Entity_centers();
//   }
// 
//   void Set_Entity_centers(OdDbDatabasePtr pDb)
//   {
//     //m_osnapMan.Set_Entity_centers(pDb);
//   }

};


// inline OdGiDrawablePtr OdExPrcEditorObject::snapDrawable() const
// {
//   return &m_osnapMan;
// }
// 
// inline void OdExPrcEditorObject::resetSnapManager()
// {
//   m_osnapMan.reset();
// }

#endif //_PRCEditorObject_h_Included_
